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
	mcp0.begin((baseAddr&7));
	mcp1.begin((baseAddr&7)+1);
	TWBR = 12;    	// go to 400 KHz I2C speed mode
    // for (uint8_t port = 0; port < 16; port++)
    // {
      // mcp0.pinMode(port, INPUT);
      // mcp1.pinMode(port, INPUT);
    // }
	return;
}

////////////////////////////////////////////////////////////////////////////
// void digitalWrite(uint8_t bit, uint8_t value) - write to a bit
////////////////////////////////////////////////////////////////////////////

void Digio32::digitalWrite(uint8_t bit, uint8_t value)
{
	int chip;
	chip = (bit >> 4) & 0x1;
	switch (chip)
	{
		case 0:
			mcp0.digitalWrite(bit & 0xf, value);
			break;
		case 1:
			mcp1.digitalWrite(bit & 0xf, value);
			break;
	}
}

////////////////////////////////////////////////////////////////////////////
// uint8_t digitalRead(uint8_t p) - read back a bit
////////////////////////////////////////////////////////////////////////////

uint8_t Digio32::digitalRead(uint8_t p)
{
	int chip, bit;
	chip = (bit >> 4) & 0x1;
	bit = p & 0xf;
	switch (chip)
	{
		case 0:
			return mcp0.digitalRead(bit);
			break;
		case 1:
			return mcp1.digitalRead(bit);
			break;
	}
}

////////////////////////////////////////////////////////////////////////////
// void PinMode(port, direction)- Set the direction of a bit (INPUT, OUTPUT, INPUT_PULLUP)
// Arduino.h defines for direction are:
//	#define INPUT 0x0
//	#define OUTPUT 0x1
//	#define INPUT_PULLUP 0x2
////////////////////////////////////////////////////////////////////////////

void Digio32::pinMode(uint8_t p, uint8_t d)
{
	int chip, bit;
	chip = (bit >> 4) & 0x1;
	bit = p & 0xf;
	switch (chip)
	{
		case 0:
			if (d == INPUT_PULLUP)
			{
				mcp0.pullUp(bit,1);			// Pullup enabled
				mcp0.pinMode(bit,INPUT);
			}
			else if (d == INPUT)
			{
				mcp0.pinMode(bit,0);		// Pullup disabled
				mcp0.pinMode(bit,INPUT);
			}
			else
			{
				mcp0.pinMode(bit,OUTPUT);
			}
			break;
		case 1:
			if (d == INPUT_PULLUP)
			{
				mcp1.pullUp(bit,1);
				mcp1.pinMode(bit,INPUT);
			}
			else if (d == INPUT)
			{
				mcp1.pinMode(bit,0);
				mcp1.pinMode(bit,INPUT);
			}
			else
			{
				mcp1.pinMode(bit,OUTPUT);
			}
			break;
	}
}

////////////////////////////////////////////////////////////////////////////
// void writeGPIOAB(chip,baData) - Write 16-bits of data at a time
////////////////////////////////////////////////////////////////////////////

void Digio32::writeGPIOAB(uint8_t chip, uint16_t baData)
{
	switch (chip)
	{
		case 0:
			mcp0.writeGPIOAB(baData);
			break;
		case 1:
			mcp1.writeGPIOAB(baData);
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
			return mcp0.readGPIOAB();
			break;
		case 1:
			return mcp1.readGPIOAB();
			break;
	}
}

////////////////////////////////////////////////////////////////////////////
// void write32(uint8_t,uint32_t) - Write 32-bits
////////////////////////////////////////////////////////////////////////////

void Digio32::write32(uint32_t longVal)
{
	mcp0.writeGPIOAB((uint16_t)(longVal&0xffff));
	mcp1.writeGPIOAB((uint16_t)(longVal>>16));
}

////////////////////////////////////////////////////////////////////////////
// uint32_t readGPIO32(void) - Read 32-bits
////////////////////////////////////////////////////////////////////////////

uint32_t Digio32::read32(void)
{
	uint32_t longReadVal = 0;
	longReadVal = (mcp1.readGPIOAB() << 16) | mcp0.readGPIOAB();
	return longReadVal;
}
