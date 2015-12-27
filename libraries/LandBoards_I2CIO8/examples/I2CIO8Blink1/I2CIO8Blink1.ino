/////////////////////////////////////////////////////////////////////////////////////////////
// Blink an LED
//
// Hardware used
// I2CIO-8 card
//  http://land-boards.com/blwiki/index.php?title=I2CIO-8
// GVSDuino (Arduino Uno Compatible)
//  http://land-boards.com/blwiki/index.php?title=GVSDuino
// Cables
/////////////////////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include "Adafruit_MCP23008.h"

Adafruit_MCP23008 mcp;

void setup()
{
  mcp.begin();      // use default address 0
  TWBR = 12;      // go to 400 KHz I2C speed mode
  for (int loopCnt = 0; loopCnt < 4; loopCnt++)
    mcp.pinMode(loopCnt, OUTPUT);
}

//

void loop()
{
  mcp.digitalWrite(0, HIGH);
  delay(500);
  mcp.digitalWrite(0, LOW);
  delay(500);
}

