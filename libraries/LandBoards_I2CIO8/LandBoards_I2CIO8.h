////////////////////////////////////////////////////////////////////////////
//  landboards_I2CIO8.h - Library for Land Boards I2CIO-8 card
//  Created by Douglas Gilliland. 2015-11-23
////////////////////////////////////////////////////////////////////////////
// Card has an MCP23008 chip
// This library uses the Adafruit MCP23008 library
// This library encapsulates the Adafruit library into a card level library
//  Webpage for the card is at:
//	http://land-boards.com/blwiki/index.php?title=I2CIO-8
////////////////////////////////////////////////////////////////////////////

#ifndef LandBoards_I2CIO8_h
#define LandBoards_I2CIO8_h

#include "Arduino.h"
#include <inttypes.h>
//#include "Wire.h"
#include "Adafruit_MCP23008.h"

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

////////////////////////////////////////////////////////////////////////////
// I2C Ports
//	MCP23017 0x20-0x27
////////////////////////////////////////////////////////////////////////////

class I2CIO8
{
  public:
    I2CIO8(void);
	void begin(void);
	void begin(uint8_t);
	void writeLED(uint8_t,uint8_t);			// Writes to a single LED
	uint8_t readJumper(uint8_t);			// Reads a single Jumper
	void digitalWrite(uint8_t, uint8_t);
	void pinMode(uint8_t, uint8_t);
  private:
	Adafruit_MCP23008 mcp;
	uint8_t digitalRead(uint8_t);
};

#endif
