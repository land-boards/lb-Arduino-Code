#ifndef LandBoards_DIGIO32_I2C_h
#define LandBoards_DIGIO32_I2C_h

////////////////////////////////////////////////////////////////////////////
//  LandBoards_DIGIO32_I2C - Library for Land Boards DigIO32-I2C card
//  DIGIO32_I2C is a card which has 2 of MCP23017 16-bit port expanders
//	Communication with the card is via I2C Two-wire interface
//  This library allows for both bit access and chip access to the card
//  	Bit access (32 bits) via digitalWrite, digitalRead, pinMode
//		Chip access (16-bits) via writeGPIOAB, readGPIOAB
//  Webpage for the card is at:
//	http://land-boards.com/blwiki/index.php?title=DIGIO32_I2C
////////////////////////////////////////////////////////////////////////////

#include <inttypes.h>
#include "Arduino.h"

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

class LandBoards_DIGIO32I2C
{
  public:
    LandBoards_DIGIO32I2C(void);
	void begin(uint8_t);					// Set the base address
	void digitalWrite(uint8_t,uint8_t);		// Writes to a single bit
	uint8_t digitalRead(uint8_t);			// Reads a single bit
	void pinMode(uint8_t,uint8_t);			// Set the single bit direction (INPUT, INPUT_PULLUP, OUTPUT)
	void writeOLATAB(uint8_t,uint16_t);		// Write to a 16-bit chip
	uint16_t readGPIOAB(uint8_t);			// Read from a 16-bit chip
	uint16_t readOLATAB(uint8_t);			// Read from a 16-bit chip
	void write32(uint32_t);					// Write 32-bits
	uint32_t read32();						// Read 32-bits
  private:
	uint8_t boardBaseAddr;
	uint8_t readRegister(uint8_t chipAddr, uint8_t addr);
	void writeRegister(uint8_t chipAddr, uint8_t addr, uint8_t value);
};

#endif
