////////////////////////////////////////////////////////////////////////////
//  LandBoards_I2CIO8.h - Library for Land Boards I2CIO-8 card
//  Created by Douglas Gilliland. 2015-11-23
////////////////////////////////////////////////////////////////////////////
// Card has an MCP23008 chip
//  Webpage for the card is at:
//	http://land-boards.com/blwiki/index.php?title=I2CIO-8
// 2019-02-28 - Added support for STN32F1 "blue pill" board
////////////////////////////////////////////////////////////////////////////

#ifndef LandBoards_I2CIO8_h
#define LandBoards_I2CIO8_h

#include "Arduino.h"
#include <inttypes.h>

////////////////////////////////////////////////////////////////////////////
// enums follow
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// defines follow
////////////////////////////////////////////////////////////////////////////

#define LED0		0x00
#define LED1		0x01
#define LED2		0x02
#define LED3		0x03
#define H4JUMPER	0x04
#define H5JUMPER	0x05
#define H6JUMPER	0x06
#define H7JUMPER	0x07

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

class LandBoards_I2CIO8
{
  public:
    LandBoards_I2CIO8(void);
	void begin(void);
	void begin(uint8_t);
	void writeLED(uint8_t,uint8_t);			// Writes to a single LED
	uint8_t readJumper(uint8_t);			// Reads a single Jumper
	uint8_t readAllJumpers(void);
	void pinMode(uint8_t, uint8_t);
  private:
	void digitalWrite(uint8_t, uint8_t);
	uint8_t digitalRead(uint8_t);
	uint8_t boardBaseAddr;
	void pullUp(uint8_t, uint8_t);
	void write8(uint8_t addr, uint8_t data);
	uint8_t read8(uint8_t addr);
};

#endif
