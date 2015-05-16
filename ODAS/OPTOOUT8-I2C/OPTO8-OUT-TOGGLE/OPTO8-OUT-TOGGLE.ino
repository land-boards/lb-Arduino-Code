//

#include <Wire.h>
#include "Adafruit_MCP23008.h"

Adafruit_MCP23008 mcp;

void setup()
{
  int loopCnt;
  mcp.begin();      // use default address 0
  TWBR = 12;      // go to 400 KHz I2C speed mode
  for (loopCnt = 0; loopCnt < 8; loopCnt++)
    mcp.pinMode(loopCnt, OUTPUT);
  for (loopCnt = 4; loopCnt < 12; loopCnt++)
    pinMode(loopCnt, INPUT_PULLUP);
}

// flip the pin #0 up and down

void loop()
{
  int loopCnt;
  delay(100);

  for (loopCnt = 0; loopCnt < 8; loopCnt++)
  {
    mcp.digitalWrite(loopCnt, HIGH);
    Serial.println(digitalRead(loopCnt+4));
    mcp.digitalWrite(loopCnt, LOW);
    Serial.println(digitalRead(loopCnt+4));
  }
}

