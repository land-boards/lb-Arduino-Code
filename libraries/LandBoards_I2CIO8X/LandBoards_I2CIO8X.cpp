////////////////////////////////////////////////////////////////////////////
//  LandBoards_I2CIO8X.cpp - Library for I2CIO-8X card
//  Created by Douglas Gilliland. 2017-01-09
//  I2CIO-8X is a card which has an MCP23008 8-bit port expander
//	Communication with the card is via I2C Two-wire interface
//  This library allows for bit access
//  	Bit access via digitalWrite, digitalRead, pinMode
//  Webpage for the card is at:
//	http://land-boards.com/blwiki/index.php?title=I2CIO-8X
////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <Wire.h>

#include "LandBoards_I2CIO8X.h"

////////////////////////////////////////////////////////////////////////////
// I2CIO8 constructor
////////////////////////////////////////////////////////////////////////////

LandBoards_I2CIO8X::LandBoards_I2CIO8X(void)
{
	begin(0);
}

////////////////////////////////////////////////////////////////////////////
// begin(addr) - Initialize the card
// Passed: addr offset (0x0-0x7) or base address (0x20-0x27)
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CIO8X::begin(uint8_t addr)
{
	i2caddr = MCP23008_ADDRESS | (addr & 0x7);

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
	write8(MCP23008_IODIR,0xff);	// All inputs
	write8(MCP23008_GPIO, 0x00);	// Default low
	write8(MCP23008_INTCON,0x00);	// Int on change from rev val
	write8(MCP23008_IPOL,0x00);		// Non-inverted outputs
	write8(MCP23008_GPINTEN,0x00);	// Mask off int on change
	read8(MCP23008_GPIO);			// Read to clear int change vals
	return;
}

////////////////////////////////////////////////////////////////////////////
// begin(void) - Initialize the card
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CIO8X::begin(void)
{
	begin(0);
	return;
}

////////////////////////////////////////////////////////////////////////////
// readAllJumpers()
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_I2CIO8X::readAllJumpers(void)
{
	return (read8(MCP23008_GPIO));
}

////////////////////////////////////////////////////////////////////////////
// readJumper(uint8_t)
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_I2CIO8X::readJumper(uint8_t bit)
{
	return digitalRead(bit);
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

void LandBoards_I2CIO8X::pinMode(uint8_t bit, uint8_t d)
{
	uint8_t iodir;
	uint8_t dupIodir;
	bit &= 7;
	iodir = read8(MCP23008_IODIR);
	dupIodir = iodir;
	if ((d == INPUT)   || (d == INPUT_PULLUP))
		iodir |= (1 << bit); 
	else 
		iodir &= ~(1 << bit);
	if (iodir != dupIodir)		// Only do the write if there was a change
		write8(MCP23008_IODIR, iodir);
	if (d == INPUT)
		pullUp(bit,LOW);		// Pullup disabled
	else if (d == INPUT_PULLUP)
		pullUp(bit,HIGH);		// Pullup enabled
}

////////////////////////////////////////////////////////////////////////////
//  uint8_t pullUp(bit, d)
// Arduino.h defines for direction are:
//	#define INPUT 0x0
//	#define OUTPUT 0x1
//	#define INPUT_PULLUP 0x2
// This eliminates the separate pullup function
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CIO8X::pullUp(uint8_t bit, uint8_t d) 
{
	uint8_t gppuCopy;
	uint8_t dupGppu;
	bit &= 7;
	gppuCopy = read8(MCP23008_GPPU);
	// set the pin and direction
	if (d == HIGH)
		gppuCopy |= 1 << bit; 
	else
		gppuCopy &= ~(1 << bit);
	// write the new GPIO
	if (gppuCopy != dupGppu)
		write8(MCP23008_GPPU, gppuCopy);
}

////////////////////////////////////////////////////////////////////////////
//  uint8_t digitalWrite(uint8_t, uint8_t)
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CIO8X::digitalWrite(uint8_t bit, uint8_t d) 
{
	uint8_t gpioCopy;
	bit &= 7;
	gpioCopy = read8(MCP23008_OLAT);
	if (d == HIGH)
		gpioCopy |= 1 << bit;
	else
		gpioCopy &= ~(1 << bit);
	write8(MCP23008_OLAT, gpioCopy);
}

////////////////////////////////////////////////////////////////////////////
//  uint8_t digitalRead(bit)
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_I2CIO8X::digitalRead(uint8_t bit)
{
	bit &= 7;
	return (read8(MCP23008_GPIO) >> bit) & 0x1;
}

////////////////////////////////////////////////////////////////////////////
// writeOLAT(uint8_t value)- write out an entire byte
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CIO8X::writeOLAT(uint8_t value)
{
	write8(MCP23008_OLAT,value);
}

////////////////////////////////////////////////////////////////////////////
// readGPIO(void)
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_I2CIO8X::readGPIO(void)
{
	return (read8(MCP23008_GPIO));
}

////////////////////////////////////////////////////////////////////////////
// uint8_t read8(regAddr) 
// https://www.arduino.cc/en/Reference/WireRequestFrom
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_I2CIO8X::read8(uint8_t regAddr) 
{
	Wire.beginTransmission(i2caddr);
	Wire.write((uint8_t)regAddr);	
	Wire.endTransmission();
	Wire.requestFrom(i2caddr, 1);		// get 1 byte
	return (uint8_t)Wire.read();
}

////////////////////////////////////////////////////////////////////////////
// void LandBoards_I2CIO8X::write8(regAddr, value) 
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CIO8X::write8(uint8_t regAddr, uint8_t value) 
{
	Wire.beginTransmission(i2caddr);
	Wire.write((uint8_t)regAddr);
	Wire.write((uint8_t)value);
	Wire.endTransmission();
}
