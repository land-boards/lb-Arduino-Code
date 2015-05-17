//

#include <Wire.h>
#include "Adafruit_MCP23008.h"

Adafruit_MCP23008 mcp;

unsigned long testCount;
unsigned long passCount;
unsigned long failCount;

void setup()
{
  int loopCnt;
  Serial.begin(57600);
  mcp.begin();      // use default address 0
  TWBR = 12;      // go to 400 KHz I2C speed mode
  for (loopCnt = 0; loopCnt < 8; loopCnt++)
    mcp.pinMode(loopCnt, OUTPUT);
  for (loopCnt = 4; loopCnt < 12; loopCnt++)
    pinMode(loopCnt, INPUT);
  testCount = 0;
  passCount = 0;
  failCount = 0;
  
}

// 

void loop()
{
  int loopCnt;
  unsigned char digRdVal;
  int pass1Fail0;
  delay(100);
  testCount++;
  pass1Fail0 = 1;
  for (loopCnt = 0; loopCnt < 8; loopCnt++)
  {
    mcp.digitalWrite(loopCnt, HIGH);
    delayMicroseconds(15);
    digRdVal = digitalRead(loopCnt+4);
    if (digRdVal != HIGH)
      pass1Fail0 = 0;
    mcp.digitalWrite(loopCnt, LOW);
    delayMicroseconds(15);
    digRdVal = digitalRead(loopCnt+4);
    if (digRdVal != LOW)
      pass1Fail0 = 0;
  }
  if (pass1Fail0 == 1)
    passCount++;
   else
     failCount++;
   Serial.print("Pass Count = ");
   Serial.print(passCount);
   Serial.print(", Fail Count = ");
   Serial.println(failCount);
}

