/////////////////////////////////////////////////////////////////////////
// I2CRPTST Example code
// I2C-RPI-01 as UUT
// http://land-boards.com/blwiki/index.php?title=I2C-RPT#Factory_Test_Procedure
// Uses GVSDuino (Arduino UNO compatible)
// http://land-boards.com/blwiki/index.php?title=GVSDuino
// 4x I2CIO-8 cards - I2C addressable card with 4 LEDs and 4 jumpers
// http://land-boards.com/blwiki/index.php?title=I2CIO-8
// Blink 4 LEDs on each I2CIO-8 card, one at a time
// Wiring to GVSDuino
//  I2C - A4 (SDA), A5 (SCL)
//  INTR from I2C-RPT-01 = D9
//  LED = D8
//  Connects to J5 on UUT
/////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <LandBoards_I2CIO8.h>
#include "landboards_pca9544a.h"

I2CIO8 myI2CIO80;
I2CIO8 myI2CIO81;
I2CIO8 myI2CIO82;
I2CIO8 myI2CIO83;

landboards_pca9544a mux;

#define INTRPIN 9
#define INTRLED 8

/////////////////////////////////////////////////////////////////////////
// setup()
/////////////////////////////////////////////////////////////////////////

void setup()
{
  uint8_t port;
  Serial.begin(9600);

  mux.begin(0);   // start the mux
  mux.setI2CChannel(0);
  myI2CIO80.begin(0);      // use default address 0
  mux.setI2CChannel(1);
  myI2CIO81.begin(0);      // use default address 0
  mux.setI2CChannel(2);
  myI2CIO82.begin(0);      // use default address 0
  mux.setI2CChannel(3);
  myI2CIO83.begin(0);      // use default address 0
  pinMode(INTRPIN, INPUT);
  pinMode(INTRLED, OUTPUT);
}

/////////////////////////////////////////////////////////////////////////
// pollMuxIntrReg(void)
/////////////////////////////////////////////////////////////////////////

void pollMuxIntrReg(void)
{
  if (digitalRead(INTRPIN) == 1)
  {
    return;
  }
  digitalWrite(INTRLED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(INTRLED, LOW);    // turn the LED off by making the voltage LOW
  Serial.print("Intr");
  uint8_t intStatus = mux.getIntStatus();
  if ((intStatus & 0x1) == 0x1)
  {
    mux.setI2CChannel(0);
    Serial.print("Card #0 - Jumpers = ");
    Serial.println(myI2CIO80.readAllJumpers());
  }
  if ((intStatus & 0x2) == 0x2)
  {
    mux.setI2CChannel(1);
    Serial.print("Card #1 - Jumpers = ");
    Serial.println(myI2CIO81.readAllJumpers());
  }
  if ((intStatus & 0x4) == 0x4)
  {
    mux.setI2CChannel(2);
    Serial.print("Card #2 - Jumpers = ");
    Serial.println(myI2CIO82.readAllJumpers());
  }
  if ((intStatus & 0x8) == 0x8)
  {
    mux.setI2CChannel(3);
    Serial.print("Card #3 - Jumpers = ");
    Serial.println(myI2CIO83.readAllJumpers());
  }
}

/////////////////////////////////////////////////////////////////////////
// loop()
/////////////////////////////////////////////////////////////////////////

void loop()
{
  uint8_t port;

  mux.setI2CChannel(0);
  for (port = 0; port < 4; port++)
  {
    myI2CIO80.writeLED(port, HIGH);
    delay(250);
    myI2CIO80.writeLED(port, LOW);
  }
  pollMuxIntrReg();
  mux.setI2CChannel(1);
  for (port = 0; port < 4; port++)
  {
    myI2CIO81.writeLED(port, HIGH);
    delay(250);
    myI2CIO81.writeLED(port, LOW);
  }
  pollMuxIntrReg();
  mux.setI2CChannel(2);
  for (port = 0; port < 4; port++)
  {
    myI2CIO82.writeLED(port, HIGH);
    delay(250);
    myI2CIO82.writeLED(port, LOW);
  }
  pollMuxIntrReg();
  mux.setI2CChannel(3);
  for (port = 0; port < 4; port++)
  {
    myI2CIO82.writeLED(port, HIGH);
    delay(250);
    myI2CIO82.writeLED(port, LOW);
  }
  pollMuxIntrReg();
}

