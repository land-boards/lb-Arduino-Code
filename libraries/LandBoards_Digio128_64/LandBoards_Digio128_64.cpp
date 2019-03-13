////////////////////////////////////////////////////////////////////////////
//  LandBoards_Digio128_64.cpp - Library for Land Boards DigIO-128 card
//  Created by Douglas Gilliland. 2017-06-05
//  Digio-128 is a card which has 8 of MCP23017 16-bit port expanders
//	Communication with the card is via I2C Two-wire interface
//	Part datasheet:
//	https://www.microchip.com/wwwproducts/en/MCP23017
//  Boards are for sale at:
//	https://www.tindie.com/products/land_boards/
//  Webpage for the card is at:
//	http://land-boards.com/blwiki/index.php?title=DIGIO-128
//	2019-03-02 - Added support for STM32F1 "blus pill" boards
////////////////////////////////////////////////////////////////////////////
//	Library class supports multiple types of access:
//		Arduino (bit) oriented
//      Byte oriented
//      I2C Low Level Driver (I2C register access)oriented
//	https://playground.arduino.cc/Main/WireLibraryDetailedReference

#include <Arduino.h>
#include <Wire.h>
#include <inttypes.h>

#include "LandBoards_Digio128_64.h"

////////////////////////////////////////////////////////////////////////////
// Digio128 constructor - has no address since the card uses all 0x20-0x27
////////////////////////////////////////////////////////////////////////////

LandBoards_Digio128_64::LandBoards_Digio128_64(void)
{
	return;
}

////////////////////////////////////////////////////////////////////////////
// begin(void) - Initialize the card
// Sets all bits to inputs
// Consumes 4 of I2C Addresses (no selection)
// DIGIO-128 Card specific I/O configuration
// Based on the following functions
// https://www.arduino.cc/en/Reference/WireBegin
////////////////////////////////////////////////////////////////////////////

void LandBoards_Digio128_64::begin(void)
{
	i2caddr = MCP23017_ADDRESS;
	Wire.begin();			// Join I2C as a master (void = master)
#if defined(ARDUINO_ARCH_AVR)
	TWBR = 12;    			// go to 400 KHz I2C speed mode
#elif defined(ARDUINO_ARCH_STM32F1)
	Wire.setClock(400000);	// 400KHz speed
#else
  #error “This library only supports boards with an AVR or SAM processor.”
#endif
	for (uint8_t chipNum = 0; chipNum < CHIP_COUNT_D128_64; chipNum++)	// Set all pins to input by default
	{
		write8(chipNum, MCP23017_IODIRA, 0xff);		// bits are all inputs
		write8(chipNum, MCP23017_GPPUA, 0x00);		// Turn off pullups
		write8(chipNum, MCP23017_GPIOA, 0x00);	// preset output bits to 0
		write8(chipNum, MCP23017_INTCONA,0x00);	// Interrupt control
		write8(chipNum, MCP23017_IPOLA,0x00);		// Special input polarity values for card
		write8(chipNum, MCP23017_GPINTENA,0xff);	// Special interrupt on change values for card
		write8(chipNum, MCP23017_IODIRB, 0xff);		// bits are all inputs
		write8(chipNum, MCP23017_GPPUB, 0x00);		// Turn off pullups
		write8(chipNum, MCP23017_GPIOB, 0x00);	// preset output bits to 0
		write8(chipNum, MCP23017_INTCONB,0x00);	// Interrupt control
		write8(chipNum, MCP23017_IPOLB,0x00);		// Special input polarity values for card
		write8(chipNum, MCP23017_GPINTENB,0xff);	// Special interrupt on change values for card
	}
	return;
}

////////////////////////////////////////////////////////////////////////////
// void PinMode(port, direction) - Set the direction of a bit (INPUT, OUTPUT, INPUT_PULLUP)
// Arduino.h defines for direction are:
//	#define INPUT 0x0
//	#define OUTPUT 0x1
//	#define INPUT_PULLUP 0x2
// This function only changes the direction of one bit at a time
// This function affects the pull-up and direction registers in the MCP23017
// Pull-up bit - 1=use pull-up on input, 0=don't use pull-up
// Direction bit - 1=Input, 0=Output
////////////////////////////////////////////////////////////////////////////

void LandBoards_Digio128_64::pinMode(uint8_t bit, uint8_t value)
{
	uint8_t puRegAdr;	// Pull-up register address
	uint8_t dirRegAdr;	// Direction register address
	uint8_t chipAddr;	// Which MCP23017 chip?
	uint8_t rdPuVal;	// Value of the pull-up register
	uint8_t rdDirVal;	// Value of the direction register
	uint8_t changeBit;	// The bit that changes in the register
	changeBit = 1 << (bit & 0x7);
	chipAddr = ((bit & CHIP_MASK_D128_64) >> CHIP_SHIFT);
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
	rdPuVal = read8(chipAddr,puRegAdr);		// Read the previous pull-up reg value
	rdDirVal = read8(chipAddr,dirRegAdr);	// Read the previous direction reg value
	if (value == INPUT_PULLUP)		// 
	{
		rdPuVal  |= changeBit;
		write8(chipAddr,puRegAdr,rdPuVal);
		rdDirVal |= changeBit;
		write8(chipAddr,dirRegAdr,rdDirVal);
	}
	else if (value == INPUT)
	{
		rdPuVal &= ~changeBit;
		write8(chipAddr,puRegAdr,rdPuVal);
		rdDirVal |= changeBit;
		write8(chipAddr,dirRegAdr,rdDirVal);
	}
	else if (value == OUTPUT)
	{
		rdDirVal &= ~changeBit;
		write8(chipAddr,dirRegAdr,rdDirVal);
	}
}

////////////////////////////////////////////////////////////////////////////
// void digitalWrite(uint8_t bit, uint8_t value) - write to a bit
////////////////////////////////////////////////////////////////////////////

void LandBoards_Digio128_64::digitalWrite(uint8_t bit, uint8_t wrVal)
{
	uint8_t regAdr;
	uint8_t chipAddr;
	uint8_t rdVal;
	chipAddr = ((bit & CHIP_MASK_D128_64) >> CHIP_SHIFT);
	if ((bit & 0x08) == 0)
		regAdr = MCP23017_OLATA;
	else
		regAdr = MCP23017_OLATB;
	rdVal = read8(chipAddr,regAdr);
	if (wrVal == 0)
		rdVal &= ~(1 << (bit&0x7));
	else
		rdVal |= (1 << (bit&0x7));
	write8(chipAddr, regAdr, rdVal);
}

////////////////////////////////////////////////////////////////////////////
// uint8_t digitalRead(uint8_t bit)
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_Digio128_64::digitalRead(uint8_t bit)
{
	uint8_t regAdr;
	uint8_t chipAddr;
	uint8_t rdVal;
	chipAddr = ((bit & CHIP_MASK_D128_64) >> CHIP_SHIFT);
	if ((bit & 0x08) == 0)
		regAdr = MCP23017_GPIOA;
	else
		regAdr = MCP23017_GPIOB;
	rdVal = read8(chipAddr,regAdr);
	return ((rdVal>>(bit&0x7))&0x1);
}

////////////////////////////////////////////////////////////////////////////
// void writeOLAT(chip,baData) - Write 16-bits of data at a time
// There are eight chips on the card
////////////////////////////////////////////////////////////////////////////

void LandBoards_Digio128_64::writeOLAT(uint8_t chip, uint16_t baData)
{
	write8(chip,MCP23017_OLATA,((baData>>8)&0xff));
	write8(chip,MCP23017_OLATB,(baData&0xff));
}

////////////////////////////////////////////////////////////////////////////
// uint16_t readGPIOAB(chip)
////////////////////////////////////////////////////////////////////////////

uint16_t LandBoards_Digio128_64::readGPIOAB(uint8_t chip)
{
	return ((read8(chip,(MCP23017_GPIOB))<<8)|(read8(chip,MCP23017_GPIOA)));
}

////////////////////////////////////////////////////////////////////////////
// uint8_t Digio32::read8(uint8_t chipAddr, uint8_t regAddr)
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_Digio128_64::read8(uint8_t chipAddr, uint8_t regAddr)
{
	Wire.beginTransmission(i2caddr + chipAddr);
	Wire.write(regAddr);
	Wire.endTransmission();
	Wire.requestFrom(i2caddr + chipAddr, 1);
	return Wire.read();
}
	
////////////////////////////////////////////////////////////////////////////
// void Digio32::write8(uint8_t chipAddr, uint8_t regAddr, uint8_t value)
////////////////////////////////////////////////////////////////////////////

void LandBoards_Digio128_64::write8(uint8_t chipAddr, uint8_t regAddr, uint8_t value)
{
	Wire.beginTransmission(i2caddr + chipAddr);
	Wire.write(regAddr);
	Wire.write(value);
	Wire.endTransmission();
}
