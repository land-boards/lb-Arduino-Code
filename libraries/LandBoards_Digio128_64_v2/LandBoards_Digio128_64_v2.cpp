////////////////////////////////////////////////////////////////////////////
//  LandBoards_Digio128V2.cpp - Library for Land Boards DigIO-128 card
//  Created by Douglas Gilliland. 2017-06-05
//  Digio-128 is a card which has 8 of MCP23017 16-bit port expanders
//	Communication with the card is via I2C Two-wire interface
//  This library allows for both bit access and chip access to the card
//  	Bit access (128 bits) via digitalWrite, digitalRead, pinMode
//		Chip access (16-bits) via writeGPIOAB, readGPIOAB
//  Webpage for the card is at:
//	http://land-boards.com/blwiki/index.php?title=DIGIO-128
////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <inttypes.h>

#include "LandBoards_digio128_64_V2.h"

////////////////////////////////////////////////////////////////////////////
// Digio128 constructor - has no address since the card uses all 0x20-0x27
////////////////////////////////////////////////////////////////////////////

Digio128_64::Digio128_64(void)
{
	return;
}

////////////////////////////////////////////////////////////////////////////
// begin(void) - Initialize the card
// Sets all bits to inputs
// Consumes 8 of I2C Addresses (no selection)
////////////////////////////////////////////////////////////////////////////

void Digio128_64::begin(void)
{
	boardBaseAddr = MCP23017_ADDRESS;
#if defined(ARDUINO_ARCH_AVR)
	TWBR = 12;    	// go to 400 KHz I2C speed mode
#endif
	for (uint8_t chipNum = 0; chipNum < CHIP_COUNT_D128_64; chipNum++)	// Set all pins to input by default
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
// void digitalWrite(uint8_t bit, uint8_t value) - write to a bit
////////////////////////////////////////////////////////////////////////////

void Digio128_64::digitalWrite(uint8_t bit, uint8_t wrVal)
{
	uint8_t regAdr;
	uint8_t chipAddr;
	uint8_t rdVal;
	chipAddr = ((bit & CHIP_MASK_D128_64) >> CHIP_SHIFT);
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
// uint8_t digitalRead(uint8_t bit)
////////////////////////////////////////////////////////////////////////////

uint8_t Digio128_64::digitalRead(uint8_t bit)
{
	uint8_t regAdr;
	uint8_t chipAddr;
	uint8_t rdVal;
	chipAddr = ((bit & CHIP_MASK_D128_64) >> CHIP_SHIFT);
	if ((bit & 0x08) == 0)
		regAdr = MCP23017_GPIOA;
	else
		regAdr = MCP23017_GPIOB;
	rdVal = readRegister(chipAddr,regAdr);
	return ((rdVal>>(bit&0x7))&0x1);
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

void Digio128_64::pinMode(uint8_t bit, uint8_t value)
{
	uint8_t puRegAdr;	// Pull-up register address
	uint8_t dirRegAdr;	// Direction register address
	uint8_t chipAddr;	// Which MCP23017 chip?
	uint8_t rdPuVal;	// Value of the pull-up register
	uint8_t rdDirVal;	// Value of the direction register
	uint8_t changeBit;	// The bit that changes in the register
	changeBit = 1 << (bit & 0x7);
	chipAddr = ((bit & CHIP_MASK_D128_64) >> CHIP_SHIFT);
	// Serial.print("chipAddr: 0x");
	// Serial.print(chipAddr,HEX);
	// Serial.println("");
	// Serial.print("bit: 0x");
	// Serial.print(bit,HEX);
	// Serial.println("");
	// Serial.print("value: 0x");
	// Serial.print(value,HEX);
	// Serial.println("");
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
// void writeGPIOAB(chip,baData) - Write 16-bits of data at a time
// There are eight chips on the card
////////////////////////////////////////////////////////////////////////////

void Digio128_64::writeGPIOAB(uint8_t chip, uint16_t baData)
{
	writeRegister(chip,MCP23017_OLATA,((baData>>8)&0xff));
	writeRegister(chip,MCP23017_OLATB,(baData&0xff));
}

////////////////////////////////////////////////////////////////////////////
// uint16_t readGPIOAB(chip)
////////////////////////////////////////////////////////////////////////////

uint16_t Digio128_64::readGPIOAB(uint8_t chip)
{
	return ((readRegister(chip,(MCP23017_GPIOB))<<8)|(readRegister(chip,MCP23017_GPIOA)));
}

////////////////////////////////////////////////////////////////////////////
// uint8_t Digio32::readRegister(uint8_t chipAddr, uint8_t regAddr)
////////////////////////////////////////////////////////////////////////////

uint8_t Digio128_64::readRegister(uint8_t chipAddr, uint8_t regAddr)
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

void Digio128_64::writeRegister(uint8_t chipAddr, uint8_t regAddr, uint8_t value)
{
	Wire.beginTransmission(boardBaseAddr + chipAddr);
	Wire.write(regAddr);
	Wire.write(value);
	Wire.endTransmission();
}
