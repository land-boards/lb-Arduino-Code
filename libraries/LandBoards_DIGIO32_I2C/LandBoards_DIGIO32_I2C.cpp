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
// begin(void) - Initialize the card
// Sets all bits to inputs
////////////////////////////////////////////////////////////////////////////

void Digio32::begin(uint8_t baseAddr)
{
	mcp0.begin((baseAddr&7));
	mcp1.begin((baseAddr&7)+1);
	TWBR = 12;    	// go to 400 KHz I2C speed mode
    for (uint8_t port = 0; port < 16; port++)
    {
      mcp0.pinMode(port, INPUT);
      mcp1.pinMode(port, INPUT);
    }
	return;
}

////////////////////////////////////////////////////////////////////////////
// digitalWrite(uint8_t bit, uint8_t value)
////////////////////////////////////////////////////////////////////////////

void Digio32::digitalWrite(uint8_t bit, uint8_t value)
{
	int chip;
	chip = bit >> 4;
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
// uint8_t digitalRead(uint8_t p)
////////////////////////////////////////////////////////////////////////////

uint8_t Digio32::digitalRead(uint8_t p)
{
	int chip, bit;
	chip = bit >> 4;
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
// uint8_t PinMode(port, direction)
// Arduino.h defines for direction are:
//	#define INPUT 0x0
//	#define OUTPUT 0x1
//	#define INPUT_PULLUP 0x2
// Adafruit's pinMode implementation only supports INPUT and OUTPUT
// This implementation supports INPUT_PULLUP with separate calls to Adafruit
// This eliminates the separate pullup function
////////////////////////////////////////////////////////////////////////////

void Digio32::pinMode(uint8_t p, uint8_t d)
{
	int chip, bit;
	chip = p >> 4;
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
// void writeGPIOAB(chip,baData)
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
// uint16_t readGPIOAB(chip)
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
