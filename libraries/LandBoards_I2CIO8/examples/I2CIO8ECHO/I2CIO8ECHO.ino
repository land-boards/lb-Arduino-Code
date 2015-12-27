/////////////////////////////////////////////////////////////////////////////////////////////
// Read (4) input jumpers and wriye out to (4) LEDs 
// Hardware used
// I2CIO-8 card
//  http://land-boards.com/blwiki/index.php?title=I2CIO-8
// GVSDuino (Arduino Uno Compatible)
//  http://land-boards.com/blwiki/index.php?title=GVSDuino
// Cables
//  4-pin to 2x3 pin connects I2CIO-8 (SDA,SCL,GND,VCC) to GVSDuino (A4,A5,GND,VCC) (female)
/////////////////////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include "Adafruit_MCP23008.h"

#define INTPOLACTHI 0x02

Adafruit_MCP23008 mcp;

void setup()
{
  mcp.begin();      // use default address 0
  TWBR = 12;      // go to 400 KHz I2C speed mode
  for (int loopCnt = 0; loopCnt < 4; loopCnt++)
    mcp.pinMode(loopCnt, OUTPUT);
  for (int loopCnt = 4; loopCnt < 8; loopCnt++)
    mcp.pinMode(loopCnt, INPUT);
    mcpwrite8(MCP23008_IOCON,INTPOLACTHI);
}

//

void loop()
{
char theChar;

theChar = read8(MCP23008_GPIO);
mcpwrite8(MCP23008_OLAT,theChar>>4);
mcpwrite8(MCP23008_IPOL,0xf0);
mcpwrite8(MCP23008_GPINTEN,0xf0);
delay(500);
}

void mcpwrite8(uint8_t addr, uint8_t data) {
  Wire.beginTransmission(0x20);
  Wire.write((byte)addr);
  Wire.write((byte)data);
  Wire.endTransmission();
}

uint8_t read8(uint8_t addr) {
  Wire.beginTransmission(0x20);
  Wire.write((byte)addr);  
  Wire.endTransmission();
  Wire.requestFrom(0x20, 1);

  return Wire.read();
}

