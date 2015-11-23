////////////////////////////////////////////////////////////////////////////
//  LandBoards_I2CIO8.cpp - Library for I2CIO8-8 card
//  Created by Douglas Gilliland. 2015-11-23
//  I2CIO8-8 is a card which has an MCP23008 8-bit port expander
//	Communication with the card is via I2C Two-wire interface
//  This library allows for both bit access
//  	Bit access (4 bits) via digitalWrite, digitalRead, pinMode
//  Webpage for the card is at:
//	http://land-boards.com/blwiki/index.php?title=I2CIO-8
////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include "LandBoards_I2CIO8.h"

////////////////////////////////////////////////////////////////////////////
// I2CIO8 constructor
////////////////////////////////////////////////////////////////////////////

I2CIO8::I2CIO8(void)
{
	return;
}

////////////////////////////////////////////////////////////////////////////
// begin(void) - Initialize the card
////////////////////////////////////////////////////////////////////////////

void I2CIO8::begin(uint8_t addr)
{
	mcp.begin(addr);
	TWBR = 12;    	// go to 400 KHz I2C speed mode
	mcp.pinMode(LED0,OUTPUT);	// First four bits are LEDs
	mcp.pinMode(LED1,OUTPUT);
	mcp.pinMode(LED2,OUTPUT);
	mcp.pinMode(LED3,OUTPUT);
	mcp.pinMode(H4JUMPER,INPUT);	// Second four bits are input jumpers
	mcp.pinMode(H5JUMPER,INPUT);
	mcp.pinMode(H6JUMPER,INPUT);
	mcp.pinMode(H7JUMPER,INPUT);
	mcp.digitalWrite(LED0,LOW);	// Turn off all of the LEDs
	mcp.digitalWrite(LED1,LOW);
	mcp.digitalWrite(LED2,LOW);
	mcp.digitalWrite(LED0,LOW);
	return;
}

////////////////////////////////////////////////////////////////////////////
// begin(void) - Initialize the card
////////////////////////////////////////////////////////////////////////////

void I2CIO8::begin(void)
{
	mcp.begin(0);
	return;
}

////////////////////////////////////////////////////////////////////////////
// writeLED(uint8_t,uint8_t)
////////////////////////////////////////////////////////////////////////////

void I2CIO8::writeLED(uint8_t bit,uint8_t value)
{
	mcp.digitalWrite(bit, value);
}

////////////////////////////////////////////////////////////////////////////
// readJumper(uint8_t)
////////////////////////////////////////////////////////////////////////////

uint8_t I2CIO8::readJumper(uint8_t bit)
{
	return mcp.digitalRead(bit);
}
////////////////////////////////////////////////////////////////////////////
// digitalWrite(uint8_t bit, uint8_t value)
////////////////////////////////////////////////////////////////////////////

void I2CIO8::digitalWrite(uint8_t bit, uint8_t value)
{
	mcp.digitalWrite(bit, value);
}

////////////////////////////////////////////////////////////////////////////
// uint8_t digitalRead(uint8_t p)
////////////////////////////////////////////////////////////////////////////

uint8_t I2CIO8::digitalRead(uint8_t p)
{
	return mcp.digitalRead(p);
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

void I2CIO8::pinMode(uint8_t p, uint8_t d)
{
	if (d == INPUT)
	{
		mcp.pinMode(p,0);		// Pullup disabled
		mcp.pinMode(p,INPUT);
	}
	else if (d == INPUT_PULLUP)
	{
		mcp.pullUp(p,1);			// Pullup enabled
		mcp.pinMode(p,INPUT);
	}
	else
	{
		mcp.pinMode(p,OUTPUT);
	}
}
