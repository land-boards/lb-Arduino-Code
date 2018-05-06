////////////////////////////////////////////////////////////////////////////
//  LandBoards_DIGIO32_I2C.cpp - Library for DIGIO32_I2C card
//  Created by Douglas Gilliland. 2017-06-05
//  DIGIO32_I2C is a card which has 2 of MCP23017 16-bit port expanders
//	Communication with the card is via I2C Two-wire interface
//  This library allows for both bit access and chip access to the card
//  	Bit access (32 bits) via digitalWrite, digitalRead, pinMode
//		Chip access (16-bits) via writeOLATAB, readGPIOAB
//  Webpage for the card is at:
//	http://land-boards.com/blwiki/index.php?title=DIGIO32_I2C
//	Base address of the card is set by jumpers to one of four addresses
////////////////////////////////////////////////////////////////////////////
//	Library class supports multiple types of access:
//		Arduino-ish (bit) oriented
//      Byte oriented
//      I2C Low Level Driver (I2C register access)oriented
////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <Arduino.h>
#include <inttypes.h>

#include <LandBoards_DIGIO32_I2C.h>

////////////////////////////////////////////////////////////////////////////
// Digio32 constructor - has no address since the card uses all 0x20-0x27
////////////////////////////////////////////////////////////////////////////

Digio32::Digio32(void)
{
	return;
}

////////////////////////////////////////////////////////////////////////////
// begin(baseAddr) - Initialize the card
// Sets all bits to inputs
// Sets the global baseAddress - board base address register
////////////////////////////////////////////////////////////////////////////

void Digio32::begin(uint8_t baseAddr)
{
	boardBaseAddr = MCP23017_ADDRESS + baseAddr;	// baseAddr set by jumpers
	TWBR = 12;    	// go to 400 KHz I2C speed mode
	for (uint8_t chipNum = 0; chipNum < CHIP_COUNT; chipNum++)	// Set all pins to input by default
	{
		// writeRegister(uint8_t chipAddr, uint8_t regAddr, uint8_t value);
		writeRegister(chipNum, MCP23017_IODIRA, 0xff);		// bits are all inputs
		writeRegister(chipNum, MCP23017_GPPUA, 0x00);		// Turn off pullups
		writeRegister(chipNum, MCP23017_IODIRB, 0xff);		// bits are all inputs
		writeRegister(chipNum, MCP23017_GPPUB, 0x00);		// Turn off pullups
	}
	return;
}

////////////////////////////////////////////////////////////////////////////
// void digitalWrite(uint8_t bit, uint8_t wrVal) - write to a bit
////////////////////////////////////////////////////////////////////////////

void Digio32::digitalWrite(uint8_t bit, uint8_t wrVal)
{
	uint8_t regAdr;
	uint8_t chipAddr;
	uint8_t rdVal;
	chipAddr = ((bit & CHIP_MASK) >> CHIP_SHIFT);
	if ((bit & 0x08) == 0)
		regAdr = MCP23017_OLATA;
	else
		regAdr = MCP23017_OLATB;
	rdVal = readRegister(chipAddr,regAdr);
	if (wrVal == 0)
		rdVal &= ~(1 << (bit&0x7));
	else
		rdVal |= (1 << (bit&0x7));
	writeRegister(chipAddr, regAdr, rdVal);
}

////////////////////////////////////////////////////////////////////////////
// uint8_t digitalRead(uint8_t p) - read back a bit
////////////////////////////////////////////////////////////////////////////

uint8_t Digio32::digitalRead(uint8_t bit)
{
	uint8_t regAdr;
	uint8_t chipAddr;
	uint8_t rdVal;
	chipAddr = ((bit & CHIP_MASK) >> CHIP_SHIFT);
	if ((bit & 0x08) == 0)
		regAdr = MCP23017_GPIOA;
	else
		regAdr = MCP23017_GPIOB;
	rdVal = readRegister(chipAddr,regAdr);
	return ((rdVal>>(bit&7))&0x01);
}

////////////////////////////////////////////////////////////////////////////
// void PinMode(port, direction)- Set the direction of a bit (INPUT, OUTPUT, INPUT_PULLUP)
// Arduino.h defines for direction are:
//	#define INPUT 0x0
//	#define OUTPUT 0x1
//	#define INPUT_PULLUP 0x2
// This function only changes the direction of one bit at a time
// This function affects the pull-up and direction registers in the MCP23017
// Pull-up bit - 1=use pull-up on input, 0=don't use pull-up
// Direction bit - 1=Input, 0=Output
////////////////////////////////////////////////////////////////////////////

void Digio32::pinMode(uint8_t bit, uint8_t value)
{
	uint8_t puRegAdr;	// Pull-up register address
	uint8_t dirRegAdr;	// Direction register address
	uint8_t chipAddr;	// Which MCP23017 chip?
	uint8_t rdPuVal;	// Value of the pull-up register
	uint8_t rdDirVal;	// Value of the direction register
	uint8_t changeBit;	// The bit that changes in the register
	changeBit = 1 << (bit & 0x7);
	chipAddr = ((bit & CHIP_MASK) >> CHIP_SHIFT);
	if ((bit & 0x08) == 0)	// A registers
	{
		puRegAdr = MCP23017_GPPUA;
		dirRegAdr = MCP23017_IODIRA;
	}
	else					// B registers
	{
		puRegAdr = MCP23017_GPPUB;
		dirRegAdr = MCP23017_IODIRB;
	}
	rdPuVal = readRegister(chipAddr,puRegAdr);		// Read the previous pull-up reg value
	rdDirVal = readRegister(chipAddr,dirRegAdr);	// Read the previous direction reg value
	if (value == INPUT_PULLUP)		// 
	{
		rdPuVal  |= changeBit;
		writeRegister(chipAddr,puRegAdr,rdPuVal);
		rdDirVal |= changeBit;
		writeRegister(chipAddr,dirRegAdr,rdDirVal);
	}
	else if (value == INPUT)
	{
		rdPuVal &= ~changeBit;
		writeRegister(chipAddr,puRegAdr,rdPuVal);
		rdDirVal |= changeBit;
		writeRegister(chipAddr,dirRegAdr,rdDirVal);
	}
	else if (value == OUTPUT)
	{
		rdDirVal &= ~changeBit;
		writeRegister(chipAddr,dirRegAdr,rdDirVal);
	}
} 

////////////////////////////////////////////////////////////////////////////
// void writeOLATAB(chip,baData) - Write 16-bits of data at a time
// There are two chips on the card
////////////////////////////////////////////////////////////////////////////

void Digio32::writeOLATAB(uint8_t chip, uint16_t baData)
{
	writeRegister(chip,MCP23017_OLATB,(baData>>8)&0xff);
	writeRegister(chip,MCP23017_OLATA,baData&0xff);
}

////////////////////////////////////////////////////////////////////////////
// uint16_t readGPIOAB(chip) - Read 16-bits at a time
////////////////////////////////////////////////////////////////////////////

uint16_t Digio32::readGPIOAB(uint8_t chip)
{
	return (((readRegister(chip,MCP23017_GPIOB)<<8)&0xff)|(readRegister(chip,MCP23017_GPIOA)&0xff));
}

////////////////////////////////////////////////////////////////////////////
// uint16_t readOLATAB(chip) - Read 16-bits at a time
////////////////////////////////////////////////////////////////////////////

uint16_t Digio32::readOLATAB(uint8_t chip)
{
	return (((readRegister(chip,MCP23017_OLATB)<<8)&0xff00)|(readRegister(chip,MCP23017_OLATA)&0xff));
}

////////////////////////////////////////////////////////////////////////////
// void write32(uint8_t,uint32_t) - Write 32-bits
////////////////////////////////////////////////////////////////////////////

void Digio32::write32(uint32_t longVal)
{
	writeOLATAB(0,(uint16_t)(longVal&0xffff));
	writeOLATAB(1,(uint16_t)(longVal>>16));
}

////////////////////////////////////////////////////////////////////////////
// uint32_t readGPIO32(void) - Read 32-bits
////////////////////////////////////////////////////////////////////////////

uint32_t Digio32::read32(void)
{
	uint32_t longReadVal = 0;
	longReadVal = ((readGPIOAB(1) << 16) | readGPIOAB(0));
	return longReadVal;
}

////////////////////////////////////////////////////////////////////////////
// uint8_t Digio32::readRegister(uint8_t chipAddr, uint8_t regAddr)
////////////////////////////////////////////////////////////////////////////

uint8_t Digio32::readRegister(uint8_t chipAddr, uint8_t regAddr)
{
	Wire.beginTransmission(boardBaseAddr + chipAddr);
	Wire.write(regAddr);
	Wire.endTransmission();
	Wire.requestFrom(boardBaseAddr + chipAddr, 1);
	return Wire.read();
}
	
////////////////////////////////////////////////////////////////////////////
// void Digio32::writeRegister(uint8_t chipAddr, uint8_t regAddr, uint8_t value)
////////////////////////////////////////////////////////////////////////////

void Digio32::writeRegister(uint8_t chipAddr, uint8_t regAddr, uint8_t value)
{
	Wire.beginTransmission(boardBaseAddr + chipAddr);
	Wire.write(regAddr);
	Wire.write(value);
	Wire.endTransmission(1);
}
