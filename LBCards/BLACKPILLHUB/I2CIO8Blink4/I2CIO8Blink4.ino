//

#include <Wire.h>
#include "Adafruit_MCP23008.h"

#define IODIR 0x0
#define IPOL 0x1
#define GPINTEN 0x2
#define DEFVAL 0x3
#define INTCON 0x4
#define IOCON 0x5
#define INTPOLACTHI 0x02
#define GPPU 0x6
#define INTF 0x7
#define INTCAP 0x8
#define GPIO 0x9
#define OLAT 0xa

Adafruit_MCP23008 mcp;

void setup()
{
  mcp.begin();      // use default address 0
#if defined(ARDUINO_ARCH_AVR)
  TWBR = 12;          // go to 400 KHz I2C speed mode
#elif defined(ARDUINO_ARCH_STM32)
  Wire.setClock(400000);  // 400KHz speed
#endif
  for (int loopCnt = 0; loopCnt < 4; loopCnt++)
    mcp.pinMode(loopCnt, OUTPUT);
  for (int loopCnt = 4; loopCnt < 8; loopCnt++)
    mcp.pinMode(loopCnt, INPUT);
    mcpwrite8(IOCON,INTPOLACTHI);
}

//

void loop()
{
  mcp.digitalWrite(3, LOW);
  mcp.digitalWrite(0, HIGH);
  delay(500);
  mcp.digitalWrite(0, LOW);
  mcp.digitalWrite(1, HIGH);
  delay(500);
  mcp.digitalWrite(1, LOW);
  mcp.digitalWrite(2, HIGH);
  delay(500);
  mcp.digitalWrite(2, LOW);
  mcp.digitalWrite(3, HIGH);
  delay(500);
}

void mcpwrite8(uint8_t addr, uint8_t data) {
  Wire.beginTransmission(0x20);
  Wire.write((byte)addr);
  Wire.write((byte)data);
  Wire.endTransmission();
}
