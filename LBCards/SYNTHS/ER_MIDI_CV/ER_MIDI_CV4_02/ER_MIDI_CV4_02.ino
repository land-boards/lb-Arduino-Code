//  ER_MIDI_CV4_02
//
//  Card:
//    http://land-boards.com/blwiki/index.php?title=ER-MIDI-CV4-02
//
//  BASED ON HAGIWO MIDI to CV code
//    https://note.com/solder_state/n/n17e028497eba
//    Japanese to English via google translate

#include <MIDI.h>
#include  <SPI.h>//DAC for communication
MIDI_CREATE_DEFAULT_INSTANCE(); // USB-MIDI Enable Library

#define LDAC1_PIN 9  // DAC TRANSFER STROBE 1
#define LDAC2_PIN 8  // DAC TRANSFER STROBE 2
#define SS_PIN 10    // SLAVE SELECT PIN
#define CLK_PIN 4    // CLOCK PIN
#define GATE_PIN 5   // GATE PIN
#define TRIG_PIN 6   // TRIGGER PIN

int note_no = 0;  //noteNo=21(A0)～60(A5) total 61, Because it takes a negative value int

int bend_range = 0;
int bend_msb = 0;
int bend_lsb = 0;
long after_bend_pitch = 0;

uint16_t CV1Val = 0;
uint16_t CV2Val = 0;
uint16_t CV3Val = 0;
uint16_t CV4Val = 0;

byte note_on_count = 0;//When multiple notes are ON and one of the notes is turned off, the last note ON does not disappear.
unsigned long trigTimer = 0;//for gate ratch

byte clock_count = 0;
byte clock_max = 24;//clock_max change by knob setting
byte clock_on_time = 0;
int clock_rate = 0;//knob CVin

// V/OCT LSB for DAC
const long cv[61] = {
  0,  68, 137,  205,  273,  341,  410,  478,  546,  614,  683,  751,
  819,  887,  956,  1024, 1092, 1161, 1229, 1297, 1365, 1434, 1502, 1570,
  1638, 1707, 1775, 1843, 1911, 1980, 2048, 2116, 2185, 2253, 2321, 2389,
  2458, 2526, 2594, 2662, 2731, 2799, 2867, 2935, 3004, 3072, 3140, 3209,
  3277, 3345, 3413, 3482, 3550, 3618, 3686, 3755, 3823, 3891, 3959, 4028, 4095
};

// setup()

void setup() {
  pinMode(LDAC1_PIN, OUTPUT);//DAC trans
  pinMode(LDAC2_PIN, OUTPUT);//DAC trans
  pinMode(SS_PIN, OUTPUT);//DAC trans
  digitalWrite(LDAC1_PIN, HIGH);
  digitalWrite(LDAC2_PIN, HIGH);

  pinMode(CLK_PIN, OUTPUT);//CLK_OUT
  pinMode(GATE_PIN, OUTPUT);//GATE_OUT
  digitalWrite(CLK_PIN, LOW);
  digitalWrite(TRIG_PIN, LOW);
  digitalWrite(GATE_PIN, LOW);

  MIDI.begin(1);          // MIDI CH1 to listen

  SPI.begin();
  SPI.setBitOrder(MSBFIRST);          // bit order
  SPI.setClockDivider(SPI_CLOCK_DIV4);// Clock (CLK) is used for 1/4 of the system clock (16MHz/4)
  SPI.setDataMode(SPI_MODE0);         // Clock polarity 0 (LOW)　Clock Phase 0
  OUT_CV1(0);
  OUT_MOD1(0);
  OUT_CV2(0);
  OUT_MOD2(0);
  delay(50);
}

void loop() {

  //-----------------------------clock_rate setting----------------------------
  clock_rate = analogRead(1);//read knob voltage

  // TEST CV OUTPUTS USING POT VALUE TO SET OUTPUT VOLTAGE
  while (1)
  {
    clock_rate = analogRead(1);//read knob voltage
    CV1Val = 0x0000 + clock_rate;
    CV2Val = 0x0400 + clock_rate;
    CV3Val = 0x0800 + clock_rate;
    CV4Val = 0x0C00 + clock_rate;
    outCVs();
//    OUT_CV1(0x000 + clock_rate);   // 0-1.25V
//    delay(1);
//    OUT_MOD1(0x400 + clock_rate);  // 1.25-2.5V
//    delay(1);
//    OUT_CV2(0x800 + clock_rate);   // 2.5V-3.75V
//    delay(1);
//    OUT_MOD2(0xC00 + clock_rate);  // 3.75V-5.0V
    delay(10);
  }
  if (clock_rate < 256) {
    clock_max = 24;//slow
  }
  else if (clock_rate < 512 && clock_rate >= 256) {
    clock_max = 12;
  }
  else if (clock_rate < 768 && clock_rate >= 512) {
    clock_max = 6;
  }
  else if (clock_rate >= 768) {
    clock_max = 3;//fast
  }

  //-----------------------------gate ratch----------------------------
  if (note_on_count != 0) {
    if ((millis() - trigTimer <= 20) && (millis() - trigTimer > 10)) {
      digitalWrite(GATE_PIN, LOW);
    }
    if ((trigTimer > 0) && (millis() - trigTimer > 20)) {
      digitalWrite(GATE_PIN, HIGH);
    }
  }

  //-----------------------------midi operation----------------------------
  if (MIDI.read()) {               // When a signal enters Channel 1
    MIDI.setInputChannel(1);
    switch (MIDI.getType()) {

      case midi::NoteOn://NoteOn After
        note_on_count ++;
        trigTimer = millis();
        note_no = MIDI.getData1() - 21;//note number

        if (note_no < 0) {
          note_no = 0;
        }
        else if (note_no >= 61) {
          note_no = 60;
        }

        digitalWrite(GATE_PIN, HIGH); //Gate to HIGH
        OUT_CV1(cv[note_no]);//V/OCT LSB for DAC See also
        break;


      case midi::NoteOff://NoteOff After
        note_on_count --;
        if (note_on_count == 0) {
          digitalWrite(GATE_PIN, LOW); //Gate to LOW
        }
        break;


      case midi::ControlChange:
        OUT_MOD1( MIDI.getData2() << 5); //0-4095
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

        if (bend_range > 64) {
          after_bend_pitch = cv[note_no] + cv[note_no] * (bend_range - 64) * 4 / 10000;
          OUT_CV1(after_bend_pitch);
        }

        else if (bend_range < 64) {
          after_bend_pitch = cv[note_no] - cv[note_no] * (64 - bend_range) * 4 / 10000;
          OUT_CV1(after_bend_pitch);
        }
        break;
    }
  }
}

// DAC_CV output 1
void OUT_CV1(int cv)
{
  uint8_t hiVal = (cv >> 8) | 0x10;
  uint8_t loVal = cv & 0xff;
  cv &= 0x0FFF;
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(hiVal);   // H0x30=OUTA/1x
  SPI.transfer(loVal);
  digitalWrite(SS_PIN, HIGH);
//  SPI.endTransaction();
//  delay(2);
  delayMicroseconds(20);
  digitalWrite(LDAC1_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(LDAC1_PIN, HIGH);
}

// DAC_MOD output 1
void OUT_MOD1(int mod)
{
  mod &= 0x0FFF;
  digitalWrite(SS_PIN, LOW);
  SPI.transfer((mod >> 8) | 0x90);   // H0xB0=OUTB/1x
  SPI.transfer(mod & 0xff);
  digitalWrite(SS_PIN, HIGH);
//  SPI.endTransaction();
//  delay(2);
  delayMicroseconds(20);
  digitalWrite(LDAC1_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(LDAC1_PIN, HIGH);
}

// DAC_CV output 2
void OUT_CV2(int cv)
{
  cv &= 0x0FFF;
  digitalWrite(SS_PIN, LOW);
  SPI.transfer((cv >> 8) | 0x10);   // H0x30=OUTA/1x
  SPI.transfer(cv & 0xff);
  digitalWrite(SS_PIN, HIGH);
//  SPI.endTransaction();
//  delay(2);
  delayMicroseconds(20);
  digitalWrite(LDAC2_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(LDAC2_PIN, HIGH);
}

// DAC_MOD output 2
void OUT_MOD2(int mod)
{
  mod &= 0x0FFF;
  digitalWrite(SS_PIN, LOW);
  SPI.transfer((mod >> 8) | 0x90);   // H0xB0=OUTB/1x
  SPI.transfer(mod & 0xff);
  digitalWrite(SS_PIN, HIGH);
//  SPI.endTransaction();
//  delay(2);
  digitalWrite(LDAC2_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(LDAC2_PIN, HIGH);
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
