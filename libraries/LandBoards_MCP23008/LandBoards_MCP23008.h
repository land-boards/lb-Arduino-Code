////////////////////////////////////////////////////////////////////////////
//  LandBoards_MCP23008.h - Library for Land Boards I2CIO-8 card
//  Created by Douglas Gilliland. 2015-11-23
////////////////////////////////////////////////////////////////////////////
// Card has an MCP23008 chip
//  Webpage for a card is at:
//	http://land-boards.com/blwiki/index.php?title=I2CIO-8
// 2019-03-03 - Added support for STM32F1 "blue pill" board
////////////////////////////////////////////////////////////////////////////

#ifndef LandBoards_MCP23008_h
#define LandBoards_MCP23008_h

#include "Arduino.h"
#include <inttypes.h>

////////////////////////////////////////////////////////////////////////////
// enums follow
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// defines follow
////////////////////////////////////////////////////////////////////////////

#define MCP23008_ADDRESS 0x20
#define MCP23008_IODIR 0x00
#define MCP23008_IPOL 0x01
#define MCP23008_GPINTEN 0x02
#define MCP23008_DEFVAL 0x03
#define MCP23008_INTCON 0x04
#define MCP23008_IOCON 0x05
#define MCP23008_GPPU 0x06
#define MCP23008_INTF 0x07
#define MCP23008_INTCAP 0x08
#define MCP23008_GPIO 0x09
#define MCP23008_OLAT 0x0A

////////////////////////////////////////////////////////////////////////////
// I2C Ports
//	MCP23017 0x20-0x27
////////////////////////////////////////////////////////////////////////////

class LandBoards_MCP23008
{
  public:
    LandBoards_MCP23008(void);
	void begin(void);
	void begin(uint8_t);
	void pinMode(uint8_t, uint8_t);
	void digitalWrite(uint8_t, uint8_t);
	uint8_t digitalRead(uint8_t);
	void pullUp(uint8_t, uint8_t);
	void writeOLAT(uint8_t);
	uint8_t readGPIO(void);
  private:
	uint8_t i2caddr;
	void write8(uint8_t addr, uint8_t data);
	uint8_t read8(uint8_t addr);
};

#endif
