#include <Wire.h>
#include "Adafruit_MCP23008.h"

Adafruit_MCP23008 mcp;

void setup()
{
  Serial.begin(57600);
  mcp.begin();      // use default address 0

  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  mcp.pinMode(0, INPUT);
  mcp.pinMode(1, INPUT);
  mcp.pinMode(2, INPUT);
  mcp.pinMode(3, INPUT);
  mcp.pinMode(4, INPUT);
  mcp.pinMode(5, INPUT);
  mcp.pinMode(6, INPUT);
  mcp.pinMode(7, INPUT);
  mcp.pullUp(0, HIGH);  // turn on a 100K pullup internally
  mcp.pullUp(1, HIGH);  // turn on a 100K pullup internally
  mcp.pullUp(2, HIGH);  // turn on a 100K pullup internally
  mcp.pullUp(3, HIGH);  // turn on a 100K pullup internally
  mcp.pullUp(4, HIGH);  // turn on a 100K pullup internally
  mcp.pullUp(5, HIGH);  // turn on a 100K pullup internally
  mcp.pullUp(6, HIGH);  // turn on a 100K pullup internally
  mcp.pullUp(7, HIGH);  // turn on a 100K pullup internally
}

unsigned char readOptoIn8(void)
{
  unsigned char rval;
  rval = mcp.digitalRead(0) & 0x1;
  rval <<= 1;
  rval |= mcp.digitalRead(1) & 0x1;
  rval <<= 1;
  rval |= mcp.digitalRead(2) & 0x1;
  rval <<= 1;
  rval |= mcp.digitalRead(3) & 0x1;
  rval <<= 1;
  rval |= mcp.digitalRead(4) & 0x1;
  rval <<= 1;
  rval |= mcp.digitalRead(5) & 0x1;
  rval <<= 1;
  rval |= mcp.digitalRead(6) & 0x1;
  rval <<= 1;
  rval |= mcp.digitalRead(7) & 0x1;
  return rval;
}

void loop()
{
  for (int loopVal = 4; loopVal < 12; loopVal++)
  {
    digitalWrite(loopVal, LOW);
    //  delay(1);
    Serial.print("Wrote LOW to channel  ");
    Serial.print(loopVal - 3);
    Serial.print(", read back  ");
    Serial.println(readOptoIn8(), HEX);
    digitalWrite(loopVal, HIGH);
    //  delay(1);
    Serial.print("Wrote HIGH to channel ");
    Serial.print(loopVal - 3);
    Serial.print(", read back  ");
    Serial.println(readOptoIn8(), HEX);
    digitalWrite(loopVal, LOW);
  }
}
