#include <SPI.h>

const int CS = 8;
static uint8_t cnt = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("AD9833 Test");

  SPI.setClockDivider(SPI_CLOCK_DIV128);
  pinMode(CS, OUTPUT);
  SPI.begin();
  SPI.setDataMode(SPI_MODE2);
 
  AD9833reset();
}

void loop() 
{
  AD9833setFrequency(cnt);
  cnt++;
  delay(1000);
}

void AD9833reset()
{
  writeToAD9833(0x0100);
}

void AD9833setFrequency(uint8_t cnt)
{
  // 制御ワード
  writeToAD9833(0x2000);
  // 14LSBs
  writeToAD9833(0x4000);
  // 14MSBs
  writeToAD9833(0x4000 + cnt);
}

void writeToAD9833(uint16_t data)
{
  digitalWrite(CS, LOW);
  SPI.transfer16(data);
  digitalWrite(CS, HIGH);
}
