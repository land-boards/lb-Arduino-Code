////////////////////////////////////////////////////////////////////////////
//  LandBoards_DIGIO32_I2C.cpp - Library for DIGIO32_I2C card
//  Created by Douglas Gilliland. 2016-10-26
//  DIGIO32_I2C is a card which has 2 of MCP23017 16-bit port expanders
//	Communication with the card is via I2C Two-wire interface
//  This library allows for both bit access and chip access to the card
//  	Bit access (32 bits) via digitalWrite, digitalRead, pinMode
//		Chip access (16-bits) via writeGPIOAB, readGPIOAB
//  Webpage for the card is at:
//	http://land-boards.com/blwiki/index.php?title=DIGIO32_I2C
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
////////////////////////////////////////////////////////////////////////////

void Digio32::begin(uint8_t baseAddr)
{
	boardBaseAddr = MCP23017_ADDRESS + baseAddr;
	TWBR = 12;    	// go to 400 KHz I2C speed mode
   	for (uint8_t port = 0; port < 32; port++)
      pinMode(port, INPUT);
	return;
}

////////////////////////////////////////////////////////////////////////////
// void digitalWrite(uint8_t bit, uint8_t value) - write to a bit
////////////////////////////////////////////////////////////////////////////

void Digio32::digitalWrite(uint8_t bit, uint8_t value)
{
	uint8_t regAdr;
	uint8_t chipAddr;
	uint8_t rdVal;
	if ((bit & 0x10) == 0x00)
		chipAddr = 0x00;
	else
		chipAddr = 0x01;
	if (bit & 0x08 == 0)
		regAdr = MCP23017_OLATA;
	else
		regAdr = MCP23017_OLATB;
	rdVal = readRegister(chipAddr,regAdr);
	if (value == 0)
		rdVal &= (~1 << bit);
	else
		rdVal |= (1 << bit);
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
	if ((bit & 0x10) == 0x00)
		chipAddr = 0x00;
	else
		chipAddr = 0x01;
	if (bit & 0x08 == 0)
		regAdr = MCP23017_GPIOA;
	else
		regAdr = MCP23017_GPIOB;
	rdVal = readRegister(chipAddr,regAdr);
	return rdVal;
}

////////////////////////////////////////////////////////////////////////////
// void PinMode(port, direction)- Set the direction of a bit (INPUT, OUTPUT, INPUT_PULLUP)
// Arduino.h defines for direction are:
//	#define INPUT 0x0
//	#define OUTPUT 0x1
//	#define INPUT_PULLUP 0x2
////////////////////////////////////////////////////////////////////////////

void Digio32::pinMode(uint8_t bit, uint8_t value)
{
	uint8_t puRegAdr;
	uint8_t dirRegAdr;
	uint8_t chipAddr;
	uint8_t rdPuVal;
	uint8_t rdDirVal;
	if ((bit & 0x10) == 0x00)
		chipAddr = boardBaseAddr + 0x00;
	else
		chipAddr = boardBaseAddr + 0x01;
	if (bit & 0x08 == 0)
	{
		puRegAdr = MCP23017_GPPUA;
		dirRegAdr = MCP23017_IODIRA;
	}
	else
	{
		puRegAdr = MCP23017_GPPUB;
		dirRegAdr = MCP23017_IODIRB;
	}
	rdPuVal = readRegister(chipAddr,puRegAdr);
	rdDirVal = readRegister(chipAddr,dirRegAdr);
	if (value == INPUT_PULLUP)
	{
		rdPuVal |= (1 << bit);
		rdDirVal |= (1 << bit);
	}
	else if (value == INPUT)
	{
		rdPuVal &= (~1 << bit);
		rdDirVal |= (1 << bit);
	}
	else if (value == OUTPUT)
	{
		rdPuVal &= (~1 << bit);
		rdDirVal &= (~1 << bit);
	}
	writeRegister(chipAddr,puRegAdr,rdPuVal);
	writeRegister(chipAddr,dirRegAdr,rdDirVal);
}

////////////////////////////////////////////////////////////////////////////
// void writeGPIOAB(chip,baData) - Write 16-bits of data at a time
////////////////////////////////////////////////////////////////////////////

void Digio32::writeGPIOAB(uint8_t chip, uint16_t baData)
{
	switch (chip)
	{
		case 0:
			writeRegister(0,MCP23017_GPIOA,baData>>8);
			writeRegister(0,MCP23017_GPIOB,baData&0xff);
			break;
		case 1:
			writeRegister(1,MCP23017_GPIOA,baData>>8);
			writeRegister(1,MCP23017_GPIOB,baData&0xff);
			break;
	}
}

////////////////////////////////////////////////////////////////////////////
// uint16_t readGPIOAB(chip) - Read 16-bits at a time
////////////////////////////////////////////////////////////////////////////

uint16_t Digio32::readGPIOAB(uint8_t chip)
{
	switch (chip)
	{
		case 0:
			return ((readRegister(0,MCP23017_GPIOA)<<8)|readRegister(0,MCP23017_GPIOA));
			break;
		case 1:
			return ((readRegister(1,MCP23017_GPIOA)<<8)|readRegister(1,MCP23017_GPIOA));
			break;
	}
}

////////////////////////////////////////////////////////////////////////////
// void write32(uint8_t,uint32_t) - Write 32-bits
////////////////////////////////////////////////////////////////////////////

void Digio32::write32(uint32_t longVal)
{
	writeGPIOAB(0,(uint16_t)(longVal&0xffff));
	writeGPIOAB(1,(uint16_t)(longVal>>16));
}

////////////////////////////////////////////////////////////////////////////
// uint32_t readGPIO32(void) - Read 32-bits
////////////////////////////////////////////////////////////////////////////

uint32_t Digio32::read32(void)
{
	uint32_t longReadVal = 0;
	longReadVal = (readGPIOAB(1) << 16) | readGPIOAB(0);
	return longReadVal;
}

////////////////////////////////////////////////////////////////////////////
// uint8_t Digio32::readRegister(uint8_t chipAddr, uint8_t regAddr)
////////////////////////////////////////////////////////////////////////////

uint8_t Digio32::readRegister(uint8_t chipAddr, uint8_t regAddr)
{
	Wire.beginTransmission(MCP23017_ADDRESS + boardBaseAddr + chipAddr);
	Wire.write(regAddr);
	Wire.endTransmission();
	Wire.requestFrom(MCP23017_ADDRESS + boardBaseAddr + chipAddr, 1);
	return Wire.read();
}
	
////////////////////////////////////////////////////////////////////////////
// void Digio32::writeRegister(uint8_t chipAddr, uint8_t regAddr, uint8_t value)
////////////////////////////////////////////////////////////////////////////

void Digio32::writeRegister(uint8_t chipAddr, uint8_t regAddr, uint8_t value)
{
	Wire.beginTransmission(MCP23017_ADDRESS + boardBaseAddr + chipAddr);
	Wire.write(regAddr);
	Wire.write(value);
	Wire.endTransmission();
}
