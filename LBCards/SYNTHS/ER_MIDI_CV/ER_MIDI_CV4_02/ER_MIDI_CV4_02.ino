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

const int LDAC1_PIN = 9;  // DAC TRANSFER STROBE 1
const int LDAC2_PIN = 8;  // DAC TRANSFER STROBE 2
const int SS_PIN = 10;    // SLAVE SELECT PIN
const int CLK_PIN = 4;    // CLOCK PIN
const int GATE_PIN = 5;   // GATE PIN
const int TRIG_PIN = 6;   // TRIGGER PIN

int note_no = 0;//noteNo=21(A0)～60(A5) total 61, Because it takes a negative value int

int bend_range = 0;
int bend_msb = 0;
int bend_lsb = 0;
long after_bend_pitch = 0;

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

void setup() {
 pinMode(LDAC1_PIN, OUTPUT) ;//DAC trans
 pinMode(SS_PIN, OUTPUT) ;//DAC trans
 pinMode(CLK_PIN, OUTPUT) ;//CLK_OUT
 pinMode(GATE_PIN, OUTPUT) ;//GATE_OUT

 MIDI.begin(1);          // MIDI CH1 to listen

 SPI.begin();
 SPI.setBitOrder(MSBFIRST) ;          // bit order
 SPI.setClockDivider(SPI_CLOCK_DIV4) ;// Clock (CLK) is used for 1/4 of the system clock (16MHz/4)
 SPI.setDataMode(SPI_MODE0) ;         // Clock polarity 0 (LOW)　Clock Phase 0
 delay(10);
 OUT_CV1(0);
 delay(10);
 OUT_MOD1(0);
 delay(10);
 OUT_CV2(0);
 delay(10);
 OUT_MOD2(0);
 delay(50);
}

void loop() {

 //-----------------------------clock_rate setting----------------------------
 clock_rate = analogRead(1);//read knob voltage

// TEST CV OUTPUTS USING POT VALUE TO SET OUTPUT VOLTAGE
 OUT_CV1(0x000 + clock_rate);   // 0-1.25V
 OUT_MOD1(0x400 + clock_rate);  // 1.25-2.5V
 OUT_CV2(0x800 + clock_rate);   // 2.5V-3.75V
 OUT_MOD1(0xC00 + clock_rate);  // 3.75V-5.0V
 
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
       note_no = MIDI.getData1() - 21 ;//note number

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
void OUT_CV1(int cv) {
 digitalWrite(LDAC1_PIN, HIGH) ;
 digitalWrite(SS_PIN, LOW) ;
 SPI.transfer((cv >> 8) | 0x30) ;   // H0x30=OUTA/1x
 SPI.transfer(cv & 0xff) ;
 digitalWrite(SS_PIN, HIGH) ;
 digitalWrite(LDAC1_PIN, LOW) ;
}

// DAC_MOD output 1
void OUT_MOD1(int mod) {
 digitalWrite(LDAC1_PIN, HIGH) ;
 digitalWrite(SS_PIN, LOW) ;
 SPI.transfer((mod >> 8) | 0xB0) ;   // H0xB0=OUTB/1x
 SPI.transfer(mod & 0xff) ;
 digitalWrite(SS_PIN, HIGH) ;
 digitalWrite(LDAC1_PIN, LOW) ;
}

// DAC_CV output 2
void OUT_CV2(int cv) {
 digitalWrite(LDAC2_PIN, HIGH) ;
 digitalWrite(SS_PIN, LOW) ;
 SPI.transfer((cv >> 8) | 0x30) ;   // H0x30=OUTA/1x
 SPI.transfer(cv & 0xff) ;
 digitalWrite(SS_PIN, HIGH) ;
 digitalWrite(LDAC2_PIN, LOW) ;
}

// DAC_MOD output 2
void OUT_MOD2(int mod) {
 digitalWrite(LDAC2_PIN, HIGH) ;
 digitalWrite(SS_PIN, LOW) ;
 SPI.transfer((mod >> 8) | 0xB0) ;   // H0xB0=OUTB/1x
 SPI.transfer(mod & 0xff) ;
 digitalWrite(SS_PIN, HIGH) ;
 digitalWrite(LDAC2_PIN, LOW) ;
}
