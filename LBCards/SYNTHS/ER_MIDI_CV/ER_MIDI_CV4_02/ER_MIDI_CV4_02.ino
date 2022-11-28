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
//const long cv[61] = {
//  0,  68, 137,  205,  273,  341,  410,  478,  546,  614,  683,  751,
//  819,  887,  956,  1024, 1092, 1161, 1229, 1297, 1365, 1434, 1502, 1570,
//  1638, 1707, 1775, 1843, 1911, 1980, 2048, 2116, 2185, 2253, 2321, 2389,
//  2458, 2526, 2594, 2662, 2731, 2799, 2867, 2935, 3004, 3072, 3140, 3209,
//  3277, 3345, 3413, 3482, 3550, 3618, 3686, 3755, 3823, 3891, 3959, 4028, 4095
//};
// 
const long cv[60] = {
  0,    83,   152,  220,  288,  356,  425,  493,  561,  629,  698,  766,
  834,  903,  971,  1039, 1107, 1176, 1244, 1312, 1380, 1449, 1517, 1585,
  1653, 1722, 1790, 1858, 1927, 1995, 2063, 2131, 2200, 2268, 2336, 2404,
  2473, 2541, 2609, 2677, 2746, 2814, 2882, 2951, 3019, 3087, 3155, 3224,
  3292, 3360, 3428, 3497, 3565, 3633, 3701, 3770, 3838, 3906, 3975, 4043
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
  CV1Val = 0;
  CV2Val = 0;
  CV3Val = 0;
  CV4Val = 0;
  outCVs();
  delay(50);
}

void loop() {

  //-----------------------------clock_rate setting----------------------------
  clock_rate = analogRead(1);//read knob voltage

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
//        note_no = MIDI.getData1() - 21; //note number
        note_no = MIDI.getData1() - 43;   //note number lowest on ER-VCO-03

        if (note_no < 0) {
          note_no = 0;
        }
        else if (note_no >= 60) {
          note_no = 60;
        }

        CV1Val = cv[note_no];
        outCVs();
        digitalWrite(GATE_PIN, HIGH); //Gate to HIGH
        break;

      case midi::NoteOff://NoteOff After
        note_on_count --;
        if (note_on_count == 0) {
          digitalWrite(GATE_PIN, LOW); //Gate to LOW
        }
        break;

      case midi::ControlChange:
        CV2Val = MIDI.getData2() << 5;
        outCVs();
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
