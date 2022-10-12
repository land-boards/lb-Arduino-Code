#include <MIDI.h>
#include  <SPI.h>//DAC通信用
MIDI_CREATE_DEFAULT_INSTANCE(); //MIDIライブラリを有効

const int LDAC = 9;//SPI trans setting
int note_no = 0;//noteNo=21(A0)～60(A5) total 61,マイナスの値を取るのでint

int bend_range = 0;
int bend_msb = 0;
int bend_lsb = 0;
long after_bend_pitch = 0;

byte note_on_count = 0;//複数のノートがONかつ、いずれかのノートがOFFしたときに、最後のノートONが消えないようにする。
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
 pinMode(LDAC, OUTPUT) ;//DAC trans
 pinMode(SS, OUTPUT) ;//DAC trans
 pinMode(4, OUTPUT) ;//CLK_OUT
 pinMode(5, OUTPUT) ;//GATE_OUT

 MIDI.begin(1);          // MIDI CH1をlisten

 SPI.begin();
 SPI.setBitOrder(MSBFIRST) ;          // bit order
 SPI.setClockDivider(SPI_CLOCK_DIV4) ;// クロック(CLK)をシステムクロックの1/4で使用(16MHz/4)
 SPI.setDataMode(SPI_MODE0) ;         // クロック極性０(LOW)　クロック位相０
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
     digitalWrite(5, LOW);
   }
   if ((trigTimer > 0) && (millis() - trigTimer > 20)) {
     digitalWrite(5, HIGH);
   }
 }

 //-----------------------------midi operation----------------------------
 if (MIDI.read()) {               // チャンネル1に信号が入ってきたら
   MIDI.setInputChannel(1);
   switch (MIDI.getType()) {

     case midi::NoteOn://NoteOnしたら
       note_on_count ++;
       trigTimer = millis();
       note_no = MIDI.getData1() - 21 ;//note number

       if (note_no < 0) {
         note_no = 0;
       }
       else if (note_no >= 61) {
         note_no = 60;
       }

       digitalWrite(5, HIGH); //GateをHIGH
       OUT_CV(cv[note_no]);//V/OCT LSB for DACを参照
       break;


     case midi::NoteOff://NoteOffしたら
       note_on_count --;
       if (note_on_count == 0) {
         digitalWrite(5, LOW); //GateをLOW
       }
       break;


     case midi::ControlChange:
       OUT_MOD( MIDI.getData2() << 5); //0-4095
       break;


     case midi::Clock:
       clock_count ++;

       if (clock_count >= clock_max) {
         clock_count = 0;
       }

       if (clock_count == 1) {
         digitalWrite(4, HIGH);
       }
       else if (clock_count != 1) {
         digitalWrite(4, LOW);
       }
       break;


     case midi::Stop:
       clock_count = 0;
       digitalWrite(5, LOW); //GateをLOW
       break;


     case midi::PitchBend:
       bend_lsb = MIDI.getData1();//LSB
       bend_msb = MIDI.getData2();//MSB
       bend_range = bend_msb; //0 to 127

       if (bend_range > 64) {
         after_bend_pitch = cv[note_no] + cv[note_no] * (bend_range - 64) * 4 / 10000;
         OUT_CV(after_bend_pitch);
       }

       else if (bend_range < 64) {
         after_bend_pitch = cv[note_no] - cv[note_no] * (64 - bend_range) * 4 / 10000;
         OUT_CV(after_bend_pitch);
       }
       break;


   }
 }
}


//DAC_CV output
void OUT_CV(int cv) {
 digitalWrite(LDAC, HIGH) ;
 digitalWrite(SS, LOW) ;
 SPI.transfer((cv >> 8) | 0x30) ;   // H0x30=OUTA/1x
 SPI.transfer(cv & 0xff) ;
 digitalWrite(SS, HIGH) ;
 digitalWrite(LDAC, LOW) ;
}

//DAC_MOD output
void OUT_MOD(int mod) {
 digitalWrite(LDAC, HIGH) ;
 digitalWrite(SS, LOW) ;
 SPI.transfer((mod >> 8) | 0xB0) ;   // H0xB0=OUTB/1x
 SPI.transfer(mod & 0xff) ;
 digitalWrite(SS, HIGH) ;
 digitalWrite(LDAC, LOW) ;
}