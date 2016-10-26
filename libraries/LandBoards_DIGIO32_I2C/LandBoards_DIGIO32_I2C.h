////////////////////////////////////////////////////////////////////////////
//  LandBoards_DIGIO32_I2C - Library for Land Boards DigIO-128 card
//  Created by Douglas Gilliland. 2015-11-23
////////////////////////////////////////////////////////////////////////////
// Card has 8x MCP23017 chips
// This library uses the Adafruit MCP23017 library
// This library encapsulates the Adafruit library into a card level library
////////////////////////////////////////////////////////////////////////////

#ifndef LandBoards_DIGIO32_I2C_h
#define LandBoards_DIGIO32_I2C_h

#include <inttypes.h>
#include "Adafruit_MCP23017.h"
#include "Arduino.h"

////////////////////////////////////////////////////////////////////////////////////
// enums follow
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
// I2C Ports
//	MCP23017 0x20-0x21 (or any offset of 2)
////////////////////////////////////////////////////////////////////////////

class DIGIO32_I2C
{
  public:
    DIGIO32_I2C(void);
	void begin(uint8_t);					// Set the base address
	void digitalWrite(uint8_t,uint8_t);		// Writes to a single bit
	uint8_t digitalRead(uint8_t);			// Reads a single bit
	void pinMode(uint8_t,uint8_t);			// Set the single bit direction (INPUT, INPUT_PULLUP, OUTPUT)
	void writeGPIOAB(uint8_t,uint16_t);		// Write to a 16-bit chip
	uint16_t readGPIOAB(uint8_t);			// Read from a 16-bit chip
  private:
	Adafruit_MCP23017 mcp0;
	Adafruit_MCP23017 mcp1;
};

#endif
