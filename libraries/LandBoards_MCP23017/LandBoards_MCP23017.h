#ifndef LandBoards_MCP23017_h
#define LandBoards_MCP23017_h

////////////////////////////////////////////////////////////////////////////
//  LandBoards_MCP23017 - Library for Land Boards MCP23017 chip
//	Communication with the card is via I2C Two-wire interface
//  This library allows for both bit access and chip access to the card
//		Chip access (16-bits) via writeGPIOAB, readGPIOAB
////////////////////////////////////////////////////////////////////////////

#include <inttypes.h>
#include "Arduino.h"
#include <Wire.h>

#define MCP23017_ADDRESS 0x20

// registers
#define MCP23017_IODIRA 0x00
#define MCP23017_IPOLA 0x02
#define MCP23017_GPINTENA 0x04
#define MCP23017_DEFVALA 0x06
#define MCP23017_INTCONA 0x08
#define MCP23017_IOCONA 0x0A
#define MCP23017_GPPUA 0x0C
#define MCP23017_INTFA 0x0E
#define MCP23017_INTCAPA 0x10
#define MCP23017_GPIOA 0x12
#define MCP23017_OLATA 0x14


#define MCP23017_IODIRB 0x01
#define MCP23017_IPOLB 0x03
#define MCP23017_GPINTENB 0x05
#define MCP23017_DEFVALB 0x07
#define MCP23017_INTCONB 0x09
#define MCP23017_IOCONB 0x0B
#define MCP23017_GPPUB 0x0D
#define MCP23017_INTFB 0x0F
#define MCP23017_INTCAPB 0x11
#define MCP23017_GPIOB 0x13
#define MCP23017_OLATB 0x15

#define CHIP_SHIFT 0x04
#define CHIP_MASK 0x10
#define CHIP_COUNT 2

////////////////////////////////////////////////////////////////////////////////////
// enums follow
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// I2C Ports
//	MCP23017 0x20-0x21 (or any offset of 2)
////////////////////////////////////////////////////////////////////////////

class LandBoards_MCP23017
{
  public:
    LandBoards_MCP23017(void);
	void begin(uint8_t);					// Set the base address
	void digitalWrite(uint8_t,uint8_t);		// Writes to a single bit
	uint8_t digitalRead(uint8_t);			// Reads a single bit
	void pinMode(uint8_t,uint8_t);			// Set the single bit direction (INPUT, INPUT_PULLUP, OUTPUT)
	void writeOLATAB(uint16_t);		// Write to a 16-bit chip
	void writeGPIOAB(uint16_t);		// Write to a 16-bit chip
	uint16_t readGPIOAB();			// Read from a 16-bit chip
	uint16_t readOLATAB();			// Read from a 16-bit chip
	uint8_t checkI2CAddr(void);				// Check card present 
  private:
	uint8_t boardBaseAddr;
	uint8_t readRegister(uint8_t addr);
	void writeRegister(uint8_t addr, uint8_t value);
};

#endif
