//  ER_MIDI_CV4_02
//    MIDI controller, 4 CV outputs
//
//  Card:
//    http://land-boards.com/blwiki/index.php?title=ER-MIDI-CV4-02
//    Arduino Pro Mini CPU, 5V, 16 MHz
//    (2) MCP4822 Dual DACs
//    Optisolated MIDI input on TRS connector
//
//  BASED ON HAGIWO MIDI to CV code
//    https://note.com/solder_state/n/n17e028497eba
//    Japanese to English via google translate
//    Changed to play single note only
//      First note to arrive plays until note is done
//
// Download steps
//  Unplug MIDI in cable from front panel
//  Connect FTDI card with 1:1 cable
//  Download code in Arduino IDE
//  Disconnect FTDI
//  Connect MIDI in cable to front panel
//

#include <MIDI.h>
#include <SPI.h>    // Communicate with DAC using SPI
MIDI_CREATE_DEFAULT_INSTANCE(); // Enable USB-MIDI Library

// Arduino pin defines
#define LDAC1_PIN 9  // DAC TRANSFER STROBE 1
#define LDAC2_PIN 8  // DAC TRANSFER STROBE 2
#define SS_PIN 10    // SLAVE SELECT PIN
#define CLK_PIN 4    // CLOCK PIN
#define GATE_PIN 5   // GATE PIN
#define TRIG_PIN 6   // TRIGGER PIN

// https://www.midi.org/specifications-old/item/table-3-control-change-messages-data-bytes-2
#define MIDI_CTRL_ALL_SOUND_OFF 120
#define MIDI_CTRL_ALL_NOTES_OFF 123

int note_no = 0;  //noteNo=21(A0)～60(A5) total 61, Because it takes a negative value int

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
// This needs improvement
//byte note_on_count = 0;
unsigned long trigTimer = 0;  // Timer for gate output

byte clock_count = 0;
byte clock_max = 24;//clock_max change by knob setting
byte clock_on_time = 0;
int clock_rate = 0;//knob CVin

// Flags/values for note tracking
bool noteOnFlag;    // True if note is being played
uint8_t noteOnVal;  // MIDI note being played value 
uint8_t noteOffVal; // Used to check the note being turned off is the right one

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
const long cv[50] = {
   0,   83,  167,  250,  333,  417,  500,  583,  667,  750,  833,  917,
1000, 1083, 1167, 1250, 1333, 1417, 1500, 1583, 1667, 1750, 1833, 1917,
2000, 2083, 2167, 2250, 2333, 2417, 2500, 2583, 2667, 2750, 2833, 2917,
3000, 3083, 3167, 3250, 3333, 3417, 3500, 3583, 3667, 3750, 3833, 3917,
4000, 4083
};

// setup()

void setup() {
  pinMode(LDAC1_PIN, OUTPUT);   //DAC1 transfer strobe
  pinMode(LDAC2_PIN, OUTPUT);   //DAC2 transfer strobe
  pinMode(SS_PIN, OUTPUT);      //DAC Slave Select
  digitalWrite(LDAC1_PIN, HIGH);
  digitalWrite(LDAC2_PIN, HIGH);

  pinMode(CLK_PIN, OUTPUT);     // CLK_OUT
  pinMode(TRIG_PIN, OUTPUT);    // TRIG_OUT
  pinMode(GATE_PIN, OUTPUT);    //GATE_OUT
  digitalWrite(CLK_PIN, LOW);
  digitalWrite(TRIG_PIN, LOW);
  digitalWrite(GATE_PIN, LOW);

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
  noteOnFlag = false;
  noteOnVal = 0;
  delay(50);  // For grins
}

void loop() {

  //-----------------------------clock_rate setting----------------------------
  // CLK ADJ knob has 4 clock divisor ranges
  clock_rate = analogRead(1);//read knob voltage

  if (clock_rate < 256)
  {
    clock_max = 24;//slow
  }
  else if (clock_rate < 512 && clock_rate >= 256)
  {
    clock_max = 12;
  }
  else if (clock_rate < 768 && clock_rate >= 512)
  {
    clock_max = 6;
  }
  else if (clock_rate >= 768)
  {
    clock_max = 3;//fast
  }

  //----------------------------- GATE signal ----------------------------
//  if (note_on_count != 0) {
//    if ((millis() - trigTimer <= 20) && (millis() - trigTimer > 10)) {
//      digitalWrite(GATE_PIN, LOW);
//    }
//    if ((trigTimer > 0) && (millis() - trigTimer > 20)) {
//      digitalWrite(GATE_PIN, HIGH);
//    }
//  }

  //-----------------------------midi operation----------------------------
  if (MIDI.read()) {               // When a signal enters Channel 1
    MIDI.setInputChannel(1);
    switch (MIDI.getType()) {

      // https://www.inspiredacoustics.com/en/MIDI_note_numbers_and_center_frequencies
      case midi::NoteOn://NoteOn After
        //note_on_count ++;
        if (noteOnFlag == false)
        {
          noteOnVal = MIDI.getData1();

          trigTimer = millis();
          //        note_no = MIDI.getData1() - 21; //note number
          // lowest note number on ER-VCO-03 w/ pot centered
          note_no = noteOnVal - 43;   // G2 is MIDI note 43

          if (note_no < 0)
          {
            note_no = 0;
          }
          else if (note_no >= 49) // Just a bit more than 4 octaves A#6/Bb6 = Highest note
          {
            note_no = 49;
          }

          CV1Val = cv[note_no];
          outCVs();
          digitalWrite(GATE_PIN, HIGH); //Gate to HIGH
          noteOnFlag = true;
        }
        break;

      case midi::NoteOff://NoteOff After
//        note_on_count --;
        noteOffVal = MIDI.getData1();
        if (noteOffVal == noteOnVal)
        {
          digitalWrite(GATE_PIN, LOW); //Gate to LOW
          noteOnFlag = false;
        }

        break;

      case midi::ControlChange:
        uint8_t changeVal = MIDI.getData2();
        if ((changeVal == MIDI_CTRL_ALL_NOTES_OFF) || (changeVal == MIDI_CTRL_ALL_SOUND_OFF))
        {
          digitalWrite(GATE_PIN, LOW); //Gate to LOW
          CV1Val = 0;
          CV2Val = 0;
          CV3Val = 0;
          CV4Val = 0;
          outCVs();
          noteOnFlag = false;
        }
        break;

      case midi::Clock:
        clock_count ++;

        if (clock_count >= clock_max) {
          clock_count = 0;
        }

        if (clock_count == 1) {
          digitalWrite(CLK_PIN, HIGH);
        }
        else if (clock_count != 1) {
          digitalWrite(CLK_PIN, LOW);
        }
        break;

      case midi::Stop:
        clock_count = 0;
        digitalWrite(GATE_PIN, LOW); //Gate to LOW
        break;

      case midi::PitchBend:
        bend_lsb = MIDI.getData1();//LSB
        bend_msb = MIDI.getData2();//MSB
        bend_range = bend_msb; //0 to 127

        if (bend_range > 64)
        {
          after_bend_pitch = cv[note_no] + cv[note_no] * (bend_range - 64) * 4 / 10000;
          CV1Val = after_bend_pitch;
          outCVs();
        }

        else if (bend_range < 64)
        {
          after_bend_pitch = cv[note_no] - cv[note_no] * (64 - bend_range) * 4 / 10000;
          CV1Val = after_bend_pitch;
          outCVs();
        }
        break;
    }
  }
}

// All 4 DACs need to be written, since the two DAC parts share one single SPI SS line
void outCVs()
{
  uint8_t CV1High, CV1Low;
  uint8_t CV2High, CV2Low;
  uint8_t CV3High, CV3Low;
  uint8_t CV4High, CV4Low;
  CV1High = CV1Val >> 8 | 0x10;
  CV1Low =  CV1Val & 0xff;
  CV2High = CV2Val >> 8 | 0x90;
  CV2Low =  CV2Val & 0xff;
  CV3High = CV3Val >> 8 | 0x10;
  CV3Low =  CV3Val & 0xff;
  CV4High = CV4Val >> 8 | 0x90;
  CV4Low =  CV4Val & 0xff;
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(CV1High);   // H0x30=OUTA/1x
  SPI.transfer(CV1Low);
  digitalWrite(SS_PIN, HIGH);
  delayMicroseconds(2);
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(CV2High);   // H0x30=OUTA/1x
  SPI.transfer(CV2Low);
  digitalWrite(SS_PIN, HIGH);
  delayMicroseconds(2);
  digitalWrite(LDAC1_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(LDAC1_PIN, HIGH);
  delayMicroseconds(2);

  digitalWrite(SS_PIN, LOW);
  SPI.transfer(CV3High);   // H0x30=OUTA/1x
  SPI.transfer(CV3Low);
  digitalWrite(SS_PIN, HIGH);
  delayMicroseconds(2);
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(CV4High);   // H0x30=OUTA/1x
  SPI.transfer(CV4Low);
  digitalWrite(SS_PIN, HIGH);
  delayMicroseconds(2);
  digitalWrite(LDAC2_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(LDAC2_PIN, HIGH);
  delayMicroseconds(2);
}
