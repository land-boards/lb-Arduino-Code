//  ER_MIDI_CV4_04_TEST_DACs
//
//  Test the DACs
//    Read Pot
//    Send in 4 scales to CV1-CV4 outputs
//    CV1 = 0-1.23V
//    CV2 = 1.024-2.047V
//    CV3 = 2.048-3.071V
//    CV4 - 3.072-4.095V
//  Tests the 3 Digital Outputs
//    Counter bits sent out on CLK, TRIG, GATE lines
//
//  Card:
//    http://land-boards.com/blwiki/index.php?title=ER-MIDI-CV4-02
//
//  BASED ON HAGIWO MIDI to CV code
//    https://note.com/solder_state/n/n17e028497eba
//    Japanese to English via google translate
//  Differences:
//    0-4.096V = 4 OCTAVES

#include  <SPI.h>//DAC for communication

#define LDAC1_PIN 9  // DAC TRANSFER STROBE 1
#define LDAC2_PIN 8  // DAC TRANSFER STROBE 2
#define SS_PIN 10    // SLAVE SELECT PIN
#define CLK_PIN 4    // CLOCK PIN
#define GATE_PIN 5   // GATE PIN
#define TRIG_PIN 6   // TRIGGER PIN

uint16_t CV1Val = 0;
uint16_t CV2Val = 0;
uint16_t CV3Val = 0;
uint16_t CV4Val = 0;

int clock_rate = 0;//knob CVin
uint8_t clkCount;

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

  SPI.begin();
  SPI.setBitOrder(MSBFIRST);          // bit order
  SPI.setClockDivider(SPI_CLOCK_DIV4);// Clock (CLK) is used for 1/4 of the system clock (16MHz/4)
  SPI.setDataMode(SPI_MODE0);         // Clock polarity 0 (LOW)　Clock Phase 0
  delay(50);
}

void loop() 
{
  //-----------------------------clock_rate setting----------------------------
  // TEST CV OUTPUTS USING POT VALUE TO SET OUTPUT VOLTAGE
    clock_rate = analogRead(1);//read knob voltage
    // 4.096V = Full scale output
    // 1mV per count
    CV1Val = 0x0000 + clock_rate;
    CV2Val = 0x0400 + clock_rate;
    CV3Val = 0x0800 + clock_rate;
    CV4Val = 0x0C00 + clock_rate;
    outCVs();
    delay(10);
    clkCount++;
    if ((clkCount & 0x01) == 0x01)
      digitalWrite(CLK_PIN, LOW);
    else
      digitalWrite(CLK_PIN, HIGH);
    if ((clkCount & 0x02) == 0x02)
      digitalWrite(TRIG_PIN, LOW);
    else
      digitalWrite(TRIG_PIN, HIGH);
    if ((clkCount & 0x04) == 0x04)
      digitalWrite(GATE_PIN, LOW);
    else
      digitalWrite(GATE_PIN, HIGH);
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
