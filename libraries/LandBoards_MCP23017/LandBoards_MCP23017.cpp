////////////////////////////////////////////////////////////////////////////
//  LandBoards_MCP23017.cpp - Library for MCP23017
//  Created by Douglas Gilliland. 2019-03-03
//	Base address of the part is set one of eight addresses
//	2019-03-03 - Added support for STM32F1 "blus pill" boards
////////////////////////////////////////////////////////////////////////////
//	Library class supports multiple types of access:
//		Arduino-ish (bit) oriented
//      Byte oriented
//      I2C Low Level Driver (I2C register access)oriented
////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <Arduino.h>
#include <inttypes.h>

#include "LandBoards_MCP23017.h"

////////////////////////////////////////////////////////////////////////////
// LandBoards_MCP23017 constructor - has no address since the card uses all 0x20-0x27
////////////////////////////////////////////////////////////////////////////

LandBoards_MCP23017::LandBoards_MCP23017(void)
{
	boardBaseAddr = MCP23017_ADDRESS;
	return;
}

////////////////////////////////////////////////////////////////////////////
// begin(baseAddr) - Initialize the part
// Sets all bits to inputs
// Sets the global baseAddress - board base address register
////////////////////////////////////////////////////////////////////////////

void LandBoards_MCP23017::begin(uint8_t baseAddr)
{
	boardBaseAddr = MCP23017_ADDRESS + (baseAddr&7);	// baseAddr set by jumpers
	Wire.begin();
#if defined(ARDUINO_ARCH_AVR)
	TWBR = 12;    			// go to 400 KHz I2C speed mode
#elif defined(STM32F1)
	Wire.setClock(400000);	// 400KHz speed
#elif defined(STM32F4)
	Wire.setClock(400000);	// 400KHz speed
#else
  #error “This library only supports boards with an AVR or STM processor.”
#endif
	writeRegister(MCP23017_IODIRA, 0xff);		// bits are all inputs
	writeRegister(MCP23017_GPPUA, 0x00);		// Turn off pullups
	writeRegister(MCP23017_IODIRB, 0xff);		// bits are all inputs
	writeRegister(MCP23017_GPPUB, 0x00);		// Turn off pullups
	return;
}

////////////////////////////////////////////////////////////////////////////
// void digitalWrite(uint8_t bit, uint8_t wrVal) - write to a bit
////////////////////////////////////////////////////////////////////////////

void LandBoards_MCP23017::digitalWrite(uint8_t bit, uint8_t wrVal)
{
	uint8_t regAdr;
	uint8_t rdVal;
	if ((bit & 0x08) == 0)
		regAdr = MCP23017_OLATA;
	else
		regAdr = MCP23017_OLATB;
	rdVal = readRegister(regAdr);
	if (wrVal == 0)
		rdVal &= ~(1 << (bit&0x7));
	else
		rdVal |= (1 << (bit&0x7));
	writeRegister(regAdr, rdVal);
}

////////////////////////////////////////////////////////////////////////////
// uint8_t digitalRead(uint8_t p) - read back a bit
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_MCP23017::digitalRead(uint8_t bit)
{
	uint8_t regAdr;
	uint8_t rdVal;
	if ((bit & 0x08) == 0)
		regAdr = MCP23017_GPIOA;
	else
		regAdr = MCP23017_GPIOB;
	rdVal = readRegister(regAdr);
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

void LandBoards_MCP23017::pinMode(uint8_t bit, uint8_t value)
{
	uint8_t puRegAdr;	// Pull-up register address
	uint8_t dirRegAdr;	// Direction register address
	uint8_t rdPuVal;	// Value of the pull-up register
	uint8_t rdDirVal;	// Value of the direction register
	uint8_t changeBit;	// The bit that changes in the register
	changeBit = 1 << (bit & 0x7);
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
	rdPuVal = readRegister(puRegAdr);		// Read the previous pull-up reg value
	rdDirVal = readRegister(dirRegAdr);	// Read the previous direction reg value
	if (value == INPUT_PULLUP)		// 
	{
		rdPuVal  |= changeBit;
		writeRegister(puRegAdr,rdPuVal);
		rdDirVal |= changeBit;
		writeRegister(dirRegAdr,rdDirVal);
	}
	else if (value == INPUT)
	{
		rdPuVal &= ~changeBit;
		writeRegister(puRegAdr,rdPuVal);
		rdDirVal |= changeBit;
		writeRegister(dirRegAdr,rdDirVal);
	}
	else if (value == OUTPUT)
	{
		rdDirVal &= ~changeBit;
		writeRegister(dirRegAdr,rdDirVal);
	}
} 

////////////////////////////////////////////////////////////////////////////
// void writeGPIOAB(baData) - Write 16-bits of data at a time
// There are two chips on the card
////////////////////////////////////////////////////////////////////////////

void LandBoards_MCP23017::writeGPIOAB(uint16_t baData)
{
	writeRegister(MCP23017_GPIOB,(baData>>8)&0xff);
	writeRegister(MCP23017_GPIOA,baData&0xff);
}

////////////////////////////////////////////////////////////////////////////
// void writeOLATAB(baData) - Write 16-bits of data at a time
// There are two chips on the card
////////////////////////////////////////////////////////////////////////////

void LandBoards_MCP23017::writeOLATAB(uint16_t baData)
{
	writeRegister(MCP23017_OLATB,(baData>>8)&0xff);
	writeRegister(MCP23017_OLATA,baData&0xff);
}

////////////////////////////////////////////////////////////////////////////
// uint16_t readGPIOAB(chip) - Read 16-bits at a time
////////////////////////////////////////////////////////////////////////////

uint16_t LandBoards_MCP23017::readGPIOAB()
{
	return (((readRegister(MCP23017_GPIOB)<<8)&0xff)|(readRegister(MCP23017_GPIOA)&0xff));
}

////////////////////////////////////////////////////////////////////////////
// uint16_t readOLATAB(chip) - Read 16-bits at a time
////////////////////////////////////////////////////////////////////////////

uint16_t LandBoards_MCP23017::readOLATAB()
{
	return (((readRegister(MCP23017_OLATB)<<8)&0xff00)|(readRegister(MCP23017_OLATA)&0xff));
}

////////////////////////////////////////////////////////////////////////////
// uint8_t LandBoards_MCP23017::readRegister(uint8_t  uint8_t regAddr)
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_MCP23017::readRegister(uint8_t regAddr)
{
	Wire.beginTransmission(boardBaseAddr);
	Wire.write(regAddr);
	Wire.endTransmission();
	Wire.requestFrom(boardBaseAddr,  1);
	return Wire.read();
}
	
////////////////////////////////////////////////////////////////////////////
// void LandBoards_MCP23017::writeRegister(uint8_t  uint8_t regAddr, uint8_t value)
////////////////////////////////////////////////////////////////////////////

void LandBoards_MCP23017::writeRegister(uint8_t regAddr, uint8_t value)
{
	Wire.beginTransmission(boardBaseAddr);
	Wire.write(regAddr);
	Wire.write(value);
	Wire.endTransmission(1);
}

////////////////////////////////////////////////////////////////////////////
// void LandBoards_MCP23017::checkI2CAddr() - Check that a device is present
// Returns	0:success
// 			1:data too long to fit in transmit buffer
//			2:received NACK on transmit of address
//			3:received NACK on transmit of data
//			4:other error
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_MCP23017::checkI2CAddr(void)
{
	Wire.beginTransmission(boardBaseAddr);
	return(Wire.endTransmission());
}
