#include <Wire.h>
#include "Adafruit_MCP23008.h"

Adafruit_MCP23008 mcp;

void setup()
{
  int loopVal;
  Serial.begin(57600);
  mcp.begin();      // use default address 0

  for (loopVal = 4; loopVal < 12; loopVal++)
  {
    digitalWrite(loopVal, LOW);
    pinMode(loopVal, OUTPUT);
  }
  for (loopVal = 0; loopVal < 8; loopVal++)
  {
    mcp.pinMode(loopVal, INPUT);
    mcp.pullUp(loopVal, HIGH);  // turn on a 100K pullup internally
  }
}

unsigned char readOptoIn8(void)
{
  int loopVal;
  unsigned int rval = 0;
  for (loopVal = 0; loopVal < 8; loopVal++)
  {
    rval |= mcp.digitalRead(loopVal) & 0x1;
    rval <<= 1;
  }
  return rval>>1;
}

void loop()
{
  unsigned char readVal;
  int testPass = 1;
  int testBit = 0x1;
  for (int loopVal = 4; loopVal < 12; loopVal++)
  {
    digitalWrite(loopVal, LOW);
    readVal = readOptoIn8();
    if ((readVal & testBit) != testBit)
    {
      Serial.println("ERR");
      testPass = 0;
    }
    digitalWrite(loopVal, HIGH);
    readVal = readOptoIn8();
    if ((readVal & testBit) == testBit)
    {
      testPass = 0;
    }
    testBit <<= 1;
  }
  if (testPass == 0)
    Serial.println("Test failed");
  else
    Serial.println("Test passed");
}

