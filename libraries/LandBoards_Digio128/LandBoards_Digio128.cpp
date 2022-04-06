////////////////////////////////////////////////////////////////////////////
//  LandBoards_Digio128.cpp - Library for Digio-128 card
//  Created by Douglas Gilliland. 2015-11-23
//  Digio-128 is a card which has 8 of MCP23017 16-bit port expanders
//	Communication with the card is via I2C Two-wire interface
//  This library allows for both bit access and chip access to the card
//  	Bit access (128 bits) via digitalWrite, digitalRead, pinMode
//		Chip access (16-bits) via writeGPIOAB, readGPIOAB
//  Webpage for the card is at:
//	http://land-boards.com/blwiki/index.php?title=DIGIO-128
//	Uses Adafruit library
////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <inttypes.h>

#include "LandBoards_digio128.h"

////////////////////////////////////////////////////////////////////////////
// Digio128 constructor - has no address since the card uses all 0x20-0x27
////////////////////////////////////////////////////////////////////////////

Digio128::Digio128(void)
{
	return;
}

////////////////////////////////////////////////////////////////////////////
// begin(void) - Initialize the card
// Sets all bits to inputs
////////////////////////////////////////////////////////////////////////////

void Digio128::begin(void)
{
	mcp0.begin(0);
	mcp1.begin(1);
	mcp2.begin(2);
	mcp3.begin(3);
	mcp4.begin(4);
	mcp5.begin(5);
	mcp6.begin(6);
	mcp7.begin(7);
#if defined(ARDUINO_ARCH_AVR)
	TWBR = 12;    			// go to 400 KHz I2C speed mode
#elif defined(STM32F1)
	Wire.setClock(400000);	// 400KHz speed
#elif defined(STM32F4)
	Wire.setClock(400000);	// 400KHz speed
#else
  #error “This library only supports boards with an AVR or STM processor.”
#endif
	for (uint8_t pinNum = 0; pinNum < 16; pinNum++)	// Set all pins to input by default
	{
		mcp0.pinMode(pinNum, INPUT);
		mcp1.pinMode(pinNum, INPUT);
		mcp2.pinMode(pinNum, INPUT);
		mcp3.pinMode(pinNum, INPUT);
		mcp4.pinMode(pinNum, INPUT);
		mcp5.pinMode(pinNum, INPUT);
		mcp6.pinMode(pinNum, INPUT);
		mcp7.pinMode(pinNum, INPUT);
	}

	return;
}

////////////////////////////////////////////////////////////////////////////
// digitalWrite(uint8_t bit, uint8_t value)
////////////////////////////////////////////////////////////////////////////

void Digio128::digitalWrite(uint8_t p, uint8_t value)
{
	uint8_t chip, bit;
	chip = (p >> 4) & 0x7;
	bit = p & 0xf;
	switch (chip)
	{
		case 0:
			mcp0.digitalWrite(bit, value);
			break;
		case 1:
			mcp1.digitalWrite(bit, value);
			break;
		case 2:
			mcp2.digitalWrite(bit, value);
			break;
		case 3:
			mcp3.digitalWrite(bit, value);
			break;
		case 4:
			mcp4.digitalWrite(bit, value);
			break;
		case 5:
			mcp5.digitalWrite(bit, value);
			break;
		case 6:
			mcp6.digitalWrite(bit, value);
			break;
		case 7:
			mcp7.digitalWrite(bit, value);
			break;
	}
}

////////////////////////////////////////////////////////////////////////////
// uint8_t digitalRead(uint8_t p)
////////////////////////////////////////////////////////////////////////////

uint8_t Digio128::digitalRead(uint8_t p)
{
	int chip, bit;
	chip = p >> 4;
	bit = p & 0xf;
	switch (chip)
	{
		case 0:
			return mcp0.digitalRead(bit);
			break;
		case 1:
			return mcp1.digitalRead(bit);
			break;
		case 2:
			return mcp2.digitalRead(bit);
			break;
		case 3:
			return mcp3.digitalRead(bit);
			break;
		case 4:
			return mcp4.digitalRead(bit);
			break;
		case 5:
			return mcp5.digitalRead(bit);
			break;
		case 6:
			return mcp6.digitalRead(bit);
			break;
		case 7:
			return mcp7.digitalRead(bit);
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

void Digio128::pinMode(uint8_t p, uint8_t d)
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
		case 2:
			if (d == INPUT_PULLUP)
			{
				mcp2.pullUp(bit,1);
				mcp2.pinMode(bit,INPUT);
			}
			else if (d == INPUT)
			{
				mcp2.pinMode(bit,0);
				mcp2.pinMode(bit,INPUT);
			}
			else
			{
				mcp2.pinMode(bit,OUTPUT);
			}
			break;
		case 3:
			if (d == INPUT_PULLUP)
			{
				mcp3.pullUp(bit,1);
				mcp3.pinMode(bit,INPUT);
			}
			else if (d == INPUT)
			{
				mcp3.pinMode(bit,0);
				mcp3.pinMode(bit,INPUT);
			}
			else
			{
				mcp3.pinMode(bit,OUTPUT);
			}
			break;
		case 4:
			if (d == INPUT_PULLUP)
			{
				mcp4.pullUp(bit,1);
				mcp4.pinMode(bit,INPUT);
			}
			else if (d == INPUT)
			{
				mcp4.pinMode(bit,0);
				mcp4.pinMode(bit,INPUT);
			}
			else
			{
				mcp4.pinMode(bit,OUTPUT);
			}
			break;
		case 5:
			if (d == INPUT_PULLUP)
			{
				mcp5.pullUp(bit,1);
				mcp5.pinMode(bit,INPUT);
			}
			else if (d == INPUT)
			{
				mcp5.pinMode(bit,0);
				mcp5.pinMode(bit,INPUT);
			}
			else
			{
				mcp5.pinMode(bit,OUTPUT);
			}
			break;
		case 6:
			if (d == INPUT_PULLUP)
			{
				mcp6.pullUp(bit,1);
				mcp6.pinMode(bit,INPUT);
			}
			else if (d == INPUT)
			{
				mcp6.pinMode(bit,0);
				mcp6.pinMode(bit,INPUT);
			}
			else
			{
				mcp6.pinMode(bit,OUTPUT);
			}
			break;
		case 7:
			if (d == INPUT_PULLUP)
			{
				mcp7.pullUp(bit,1);
				mcp7.pinMode(bit,INPUT);
			}
			else if (d == INPUT)
			{
				mcp7.pinMode(bit,0);
				mcp7.pinMode(bit,INPUT);
			}
			else
			{
				mcp7.pinMode(bit,OUTPUT);
			}
			break;
	}
}

////////////////////////////////////////////////////////////////////////////
// void writeGPIOAB(chip,baData)
////////////////////////////////////////////////////////////////////////////

void Digio128::writeGPIOAB(uint8_t chip, uint16_t baData)
{
	switch (chip)
	{
		case 0:
			mcp0.writeGPIOAB(baData);
			break;
		case 1:
			mcp1.writeGPIOAB(baData);
			break;
		case 2:
			mcp2.writeGPIOAB(baData);
			break;
		case 3:
			mcp3.writeGPIOAB(baData);
			break;
		case 4:
			mcp4.writeGPIOAB(baData);
			break;
		case 5:
			mcp5.writeGPIOAB(baData);
			break;
		case 6:
			mcp6.writeGPIOAB(baData);
			break;
		case 7:
			mcp7.writeGPIOAB(baData);
			break;
	}
}

////////////////////////////////////////////////////////////////////////////
// uint16_t readGPIOAB(chip)
////////////////////////////////////////////////////////////////////////////

uint16_t Digio128::readGPIOAB(uint8_t chip)
{
	switch (chip)
	{
		case 0:
			return mcp0.readGPIOAB();
			break;
		case 1:
			return mcp1.readGPIOAB();
			break;
		case 2:
			return mcp2.readGPIOAB();
			break;
		case 3:
			return mcp3.readGPIOAB();
			break;
		case 4:
			return mcp4.readGPIOAB();
			break;
		case 5:
			return mcp5.readGPIOAB();
			break;
		case 6:
			return mcp6.readGPIOAB();
			break;
		case 7:
			return mcp7.readGPIOAB();
			break;
	}
}
