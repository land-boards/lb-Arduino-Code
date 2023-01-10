//  ER_MIDI_CV4_02_V2
//    MIDI controller, 4 CV outputs
//
//  Card:
//    http://land-boards.com/blwiki/index.php?title=ER-MIDI-CV4-02
//    Arduino Pro Mini CPU, 5V, 16 MHz
//      ATMega168 or ATMega328
//    (2) MCP4822 Dual DACs
//      0-4.096V swing is ~4 octaves
//    Optisolated MIDI input on TRS connector
//
//  BASED ON HAGIWO MIDI to CV code
//    https://note.com/solder_state/n/n17e028497eba
//    Japanese to English via google translate
//    Changed to be able to play "polyphonic"
//      See POLYPHONIC define below to use polyphonic mode
//      First note to arrive plays until note is done
//      Single GATE out - This limitation is due to a single ADSR in my sythn
//    Uses TRIG and CLK as outs for drums in Beaks (Peaks)
//
// Download steps
//  Unplug MIDI in cable from front panel
//  Connect FTDI card with 1:1 cable
//    Cable does not have +5V connected
//    FTDI card is jumpered for 5V signal levels
//  Download code in Arduino IDE
//  Disconnect FTDI
//  Connect MIDI in cable to front panel
//
// ATMega168 Resources
//  Sketch uses 5304 bytes (36%) of program storage space. Maximum is 14336 bytes.
//  Global variables use 512 bytes (50%) of dynamic memory, leaving 512 bytes for local variables.
//    Maximum is 1024 bytes.


#include <MIDI.h>
#include <SPI.h>    // Communicate with DAC using SPI
MIDI_CREATE_DEFAULT_INSTANCE(); // Enable MIDI Library

///////////////////////////////////////////////////////////////////////
// Configurations

// Can also write in pairs (1&2 oe 3&4) instead of all 4
#define POLYPHONIC   // if polyphonic
//#undef POLYPHONIC      // if not polyphonic

// Use the CLk and TRIG outputs to Beaks (Peaks) control drums
#define DRUM_TRIGGER_OUTS
//#undef DRUM_TRIGGER_OUTS
///////////////////////////////////////////////////////////////////////

// Arduino pin defines
#define LDAC1_PIN 9  // DAC TRANSFER STROBE 1
#define LDAC2_PIN 8  // DAC TRANSFER STROBE 2
#define SS_PIN 10    // SLAVE SELECT PIN
#define CLK_PIN 4    // CLOCK PIN
#define GATE_PIN 5   // GATE PIN
#define TRIG_PIN 6   // TRIGGER PIN

// Uses direct port manipulation to set/clear outputs
//  https://docs.arduino.cc/hacking/software/PortManipulation
//    B (digital pin 8 to 13)
//    C (analog input pins)
//    D (digital pins 0 to 7)
// Macros for the digitalWrite functions
#define SET_CLK_HIGH PORTD = PORTD | 0X10
#define SET_CLK_LOW PORTD = PORTD & 0XEF
#define SET_GATE_HIGH PORTD = PORTD | 0X20
#define SET_GATE_LOW PORTD = PORTD & 0XDF
#define SET_TRIG_HIGH PORTD = PORTD | 0X40
#define SET_TRIG_LOW PORTD = PORTD & 0XBF
#define SET_ALL_CTRLS_LOW PORTD = PORTD & 0X8F
#define SET_LDAC1_HIGH PORTB = PORTB | 0X02
#define SET_LDAC1_LOW PORTB = PORTB & 0XFD
#define SET_LDAC2_HIGH PORTB = PORTB | 0X01
#define SET_LDAC2_LOW PORTB = PORTB & 0XFE
#define SET_SS_HIGH PORTB = PORTB | 0X04
#define SET_SS_LOW PORTB = PORTB & 0XFB

// Control change messages
// https://www.midi.org/specifications-old/item/table-3-control-change-messages-data-bytes-2
#define MIDI_CTRL_ALL_SOUND_OFF 120
#define MIDI_CTRL_ALL_NOTES_OFF 123

int note_no = 0;

int bend_range = 0;
int bend_msb = 0;
int bend_lsb = 0;
long after_bend_pitch = 0;

// Keep the CV values since they are all re-written when any change
uint16_t CV1Val = 0;
uint16_t CV2Val = 0;
uint16_t CV3Val = 0;
uint16_t CV4Val = 0;

// When multiple notes are ON and one of the notes is turned off,
//   the last note ON does not disappear.
unsigned long gateTimer1 = 0;  // Timer for gate output
#ifdef POLYPHONIC
unsigned long gateTimer2 = 0;  // Timer for gate output
unsigned long gateTimer3 = 0;  // Timer for gate output
unsigned long gateTimer4 = 0;  // Timer for gate output
#endif

byte clock_count = 0;
byte clock_max = 24;//clock_max change by knob setting
byte clock_on_time = 0;
int clock_rate = 0;//knob CVin

// Flags/values for note tracking
bool noteOnFlag1;    // True if note is being played
#ifdef POLYPHONIC
bool noteOnFlag2;    // True if note is being played
bool noteOnFlag3;    // True if note is being played
bool noteOnFlag4;    // True if note is being played
#endif
int8_t noteOnVal;  // MIDI note being played value
int8_t pianoNoteOnVal1;  // MIDI note being played value
#ifdef POLYPHONIC
int8_t pianoNoteOnVal2;  // MIDI note being played value
int8_t pianoNoteOnVal3;  // MIDI note being played value
int8_t pianoNoteOnVal4;  // MIDI note being played value
#endif
int8_t noteOffVal; // Used to check the note being turned off is the right one

// V/OCT LSB for DAC
// ER-VCO-03 characteristics
//  PITCH ADJ knob roughly centered
//  0V = 93.08 Hz (roughly F2)
//  1V = 179 Hz (G3)
//  1.52V = 261 Hz (C4)
//  2V = 365 Hz (G4)
//  3V = 722 Hz (G5)
//  4V = 1.45 KHz (G6)
//  5V = 3.05 KHz (G7)
// Max output voltage of this card is 4.096V (4 octaves)
//  1mV per DAC count
// 12 notes per octave = 1/12V per note = 83.333 mV
// Steps are in 83.333 mV
// Table counts up by integer steps - rounded 83.333 mV
// Generated table in spreadsheet
const uint16_t cv[50] = {
  0,   83,  167,  250,  333,  417,  500,  583,  667,  750,  833,  917,
  1000, 1083, 1167, 1250, 1333, 1417, 1500, 1583, 1667, 1750, 1833, 1917,
  2000, 2083, 2167, 2250, 2333, 2417, 2500, 2583, 2667, 2750, 2833, 2917,
  3000, 3083, 3167, 3250, 3333, 3417, 3500, 3583, 3667, 3750, 3833, 3917,
  4000, 4083
};

// setup()

void setup()
{
  pinMode(LDAC1_PIN, OUTPUT);   //DAC1 transfer strobe
  pinMode(LDAC2_PIN, OUTPUT);   //DAC2 transfer strobe
  pinMode(SS_PIN, OUTPUT);      //DAC Slave Select
  SET_LDAC1_HIGH;
  SET_LDAC2_HIGH;

  pinMode(CLK_PIN, OUTPUT);     // CLK_OUT
  pinMode(TRIG_PIN, OUTPUT);    // TRIG_OUT
  pinMode(GATE_PIN, OUTPUT);    // GATE_OUT
  SET_ALL_CTRLS_LOW;

  MIDI.begin(1);          // Listen to MIDI Channel 1

  SPI.begin();                        // Set up SPI for DAC transfers
  SPI.setBitOrder(MSBFIRST);          // bit order
  SPI.setClockDivider(SPI_CLOCK_DIV4);// Clock (CLK) is used for 1/4 of the system clock (16MHz/4)
  SPI.setDataMode(SPI_MODE0);         // Clock polarity 0 (LOW)　Clock Phase 0
  // Set the CV values
  CV1Val = 0;
  CV2Val = 0;
  CV3Val = 0;
  CV4Val = 0;
  // Write out the initial CV values
  outCVs();
  noteOnFlag1 = false;
#ifdef POLYPHONIC
  noteOnFlag2 = false;
  noteOnFlag3 = false;
  noteOnFlag4 = false;
#endif
  noteOnVal = 0;
  delay(50);  // For grins
  //  Serial.begin(9600);
}

#define DAC_LOWEST_NOTE 43    // G2 is MIDI note 43

// The main loop
void loop()
{
  //-----------------------------clock_rate setting----------------------------
  // CLK ADJ knob has 4 clock divisor ranges
  clock_rate = analogRead(1);//read knob voltage

  if (clock_rate < 256)
    clock_max = 24;//slow
  else if (clock_rate < 512 && clock_rate >= 256)
    clock_max = 12;
  else if (clock_rate < 768 && clock_rate >= 512)
    clock_max = 6;
  else if (clock_rate >= 768)
    clock_max = 3;//fast

  //-----------------------------midi operation----------------------------
  if (MIDI.read())      // When a signal enters Channel 1
  {
    // http://fortyseveneffects.github.io/arduino_midi_library/a00033.html#gad58d4850a613045caeb9499dd05615ef
    MIDI.setInputChannel(1);
    // http://fortyseveneffects.github.io/arduino_midi_library/a00033.html#ga751630ff3b0829f0de19ea724999df25
    switch (MIDI.getType())
    {
      // https://www.inspiredacoustics.com/en/MIDI_note_numbers_and_center_frequencies
      case midi::NoteOn://NoteOn After
        //note_on_count ++;
        noteOnVal = MIDI.getData1();
        // Drum triggers on GATE/CLK outputs
        // Bottom 6 keys of 61 key keyboard
#ifdef DRUM_TRIGGER_OUTS
        if (noteOnVal <= 39)
        {
          SET_CLK_HIGH;
          delay(1);
          SET_CLK_LOW;
        }
        else if (noteOnVal < 43)
        {
          SET_TRIG_HIGH;
          delay(1);
          SET_TRIG_LOW;
        }
        else
#endif
        {
          if (noteOnFlag1 == false)
          {
            gateTimer1 = millis();
            // note_no = MIDI.getData1() - 21; //note number
            // lowest note number on ER-VCO-03 w/ pot centered
            note_no = noteOnVal - DAC_LOWEST_NOTE;   // G2 is MIDI note 43
            if (note_no < 0)
              note_no = 0;
            else if (note_no >= 49) // Just a bit more than 4 octaves A#6/Bb6 = Highest note
              note_no = 49;
            else
            {
              CV1Val = cv[note_no];
              outCVs_1_2();
              SET_GATE_HIGH;
              noteOnFlag1 = true;
              pianoNoteOnVal1 = noteOnVal;
            }
          }
#ifdef POLYPHONIC
          else if (noteOnFlag2 == false)
          {
            gateTimer2 = millis();
            //        note_no = MIDI.getData1() - 21; //note number
            // lowest note number on ER-VCO-03 w/ pot centered
            note_no = noteOnVal - 43;   // G2 is MIDI note 43
            if (note_no < 0)
              note_no = 0;
            else if (note_no >= 49) // Just a bit more than 4 octaves A#6/Bb6 = Highest note
              note_no = 49;
            else
            {
              CV2Val = cv[note_no];
              outCVs_1_2();
              SET_GATE_HIGH;
              noteOnFlag2 = true;
              pianoNoteOnVal2 = noteOnVal;
            }
          }
          else if (noteOnFlag3 == false)
          {
            gateTimer3 = millis();
            //        note_no = MIDI.getData1() - 21; //note number
            // lowest note number on ER-VCO-03 w/ pot centered
            note_no = noteOnVal - 43;   // G2 is MIDI note 43
            if (note_no < 0)
              note_no = 0;
            else if (note_no >= 49) // Just a bit more than 4 octaves A#6/Bb6 = Highest note
              note_no = 49;
            else
            {
              CV3Val = cv[note_no];
              outCVs_3_4();
              SET_GATE_HIGH;
              noteOnFlag3 = true;
              pianoNoteOnVal3 = noteOnVal;
            }
          }
          else if (noteOnFlag4 == false)
          {
            gateTimer4 = millis();
            //        note_no = MIDI.getData1() - 21; //note number
            // lowest note number on ER-VCO-03 w/ pot centered
            note_no = noteOnVal - 43;   // G2 is MIDI note 43
            if (note_no < 0)
              note_no = 0;
            else if (note_no >= 49) // Just a bit more than 4 octaves A#6/Bb6 = Highest note
              note_no = 49;
            else
            {
              CV4Val = cv[note_no];
              outCVs_3_4();
              SET_GATE_HIGH;
              noteOnFlag4 = true;
              pianoNoteOnVal4 = noteOnVal;
            }
          }
#endif
        }
        break;

      case midi::NoteOff://NoteOff After
        //        note_on_count --;
        noteOffVal = MIDI.getData1();
        if ((noteOffVal == pianoNoteOnVal1) && noteOnFlag1)
          noteOnFlag1 = false;
#ifdef POLYPHONIC
        else if ((noteOffVal == pianoNoteOnVal2) && noteOnFlag2)
          noteOnFlag2 = false;
        else if ((noteOffVal == pianoNoteOnVal3) && noteOnFlag3)
          noteOnFlag3 = false;
        else if ((noteOffVal == pianoNoteOnVal4) && noteOnFlag4)
          noteOnFlag4 = false;
        if (!noteOnFlag1 & !noteOnFlag2 & !noteOnFlag3 & !noteOnFlag4)
          SET_GATE_LOW;
#endif
#ifndef POLYPHONIC
        if (!noteOnFlag1)
          SET_GATE_LOW;
#endif
        break;

      case midi::ControlChange:
        uint8_t changeVal = MIDI.getData2();
        if ((changeVal == MIDI_CTRL_ALL_NOTES_OFF) || (changeVal == MIDI_CTRL_ALL_SOUND_OFF))
        {
          SET_ALL_CTRLS_LOW;
          // Set all the flags in case there is a lingering note
          noteOnFlag1 = false;
#ifdef POLYPHONIC
          noteOnFlag2 = false;
          noteOnFlag3 = false;
          noteOnFlag4 = false;
#endif
        }
        break;

      case midi::Clock:
        // Clock is "overloaded" output when drums are on TRIG and CLk
#ifndef DRUM_TRIGGER_OUTS
        clock_count ++;

        if (clock_count >= clock_max)
          clock_count = 0;

        if (clock_count == 1)
          SET_CLK_HIGH;
        else if (clock_count != 1)
          SET_CLK_LOW;
#endif
        break;

      case midi::Stop:
#ifndef DRUM_TRIGGER_OUTS
        clock_count = 0;
        SET_CLK_LOW;
#endif
        break;

      case midi::PitchBend:
        bend_lsb = MIDI.getData1();//LSB
        bend_msb = MIDI.getData2();//MSB
        bend_range = bend_msb; //0 to 127

        if (bend_range > 64)
        {
          after_bend_pitch = cv[note_no] + cv[note_no] * (bend_range - 64) * 4 / 10000;
          CV1Val = after_bend_pitch;
          outCVs_1_2();
        }
        else if (bend_range < 64)
        {
          after_bend_pitch = cv[note_no] - cv[note_no] * (64 - bend_range) * 4 / 10000;
          CV1Val = after_bend_pitch;
          outCVs_1_2();
        }
        break;
    }
  }
}

void outCVs_1_2()
{
  uint8_t CV1High, CV1Low;
  uint8_t CV2High, CV2Low;
  CV1High = CV1Val >> 8 | 0x10;
  CV1Low =  CV1Val & 0xff;
  CV2High = CV2Val >> 8 | 0x90;
  CV2Low =  CV2Val & 0xff;
  SET_SS_LOW;
  SPI.transfer(CV1High);   // 0x30=OUTA/1x
  SPI.transfer(CV1Low);
  SET_SS_HIGH;
  delayMicroseconds(2);
  SET_SS_LOW;
  SPI.transfer(CV2High);   // 0x30=OUTA/1x
  SPI.transfer(CV2Low);
  SET_SS_HIGH;
  delayMicroseconds(2);
  SET_LDAC1_LOW;
  delayMicroseconds(2);
  SET_LDAC1_HIGH;
  delayMicroseconds(2);
}

void outCVs_3_4()
{
  uint8_t CV3High, CV3Low;
  uint8_t CV4High, CV4Low;
  CV3High = CV3Val >> 8 | 0x10;
  CV3Low =  CV3Val & 0xff;
  CV4High = CV4Val >> 8 | 0x90;
  CV4Low =  CV4Val & 0xff;
  SET_SS_LOW;
  SPI.transfer(CV3High);   // 0x30=OUTA/1x
  SPI.transfer(CV3Low);
  SET_SS_HIGH;
  delayMicroseconds(2);
  SET_SS_LOW;
  SPI.transfer(CV4High);   // 0x30=OUTA/1x
  SPI.transfer(CV4Low);
  SET_SS_HIGH;
  delayMicroseconds(2);
  SET_LDAC2_LOW;
  delayMicroseconds(2);
  SET_LDAC2_HIGH;
  delayMicroseconds(2);
}

// All 4 DACs need to be written, since the two DAC parts share one single SPI SS line
void outCVs()
{
  outCVs_1_2();
  outCVs_3_4();
}
