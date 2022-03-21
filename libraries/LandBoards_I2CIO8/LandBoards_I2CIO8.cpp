////////////////////////////////////////////////////////////////////////////
//  LandBoards_I2CIO8.cpp - Library for LandBoards_I2CIO8-8 card
//  Created by Douglas Gilliland. 2015-11-23
//  LandBoards_I2CIO8-8 is a card which has an MCP23008 8-bit port expander
//	Communication with the card is via I2C Two-wire interface
//	Part datasheet:
//	https://www.microchip.com/wwwproducts/en/MCP23008
//  Webpage for the card is at:
//	http://land-boards.com/blwiki/index.php?title=I2CIO-8
//  Board is for sale at:
//	https://www.tindie.com/products/land_boards/i2c-demo-board-mcp23008-i2cio-8/
//	Base address of the card is set by jumpers to one of eight addresses
//	2019-02-28 - Added support for STM32F1 "blus pill" boards
//  Library is based on LandBoards_MCP23008 library
//		https://github.com/land-boards/lb-Arduino-Code/tree/master/libraries/LandBoards_MCP23008
//		Added card specific functions
////////////////////////////////////////////////////////////////////////////
// D0-D3 are LEDs D0-D3
// D4-D7 are H5-H8 jumpers
////////////////////////////////////////////////////////////////////////////
//	Library class supports multiple types of access:
//		Arduino (bit) oriented
//      Byte oriented
//      I2C Low Level Driver (I2C register access)oriented
//	https://playground.arduino.cc/Main/WireLibraryDetailedReference
////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <Wire.h>
#include <inttypes.h>

#include "LandBoards_I2CIO8.h"

////////////////////////////////////////////////////////////////////////////
// LandBoards_I2CIO8 constructor
////////////////////////////////////////////////////////////////////////////

LandBoards_I2CIO8::LandBoards_I2CIO8(void)
{
	i2caddr = MCP23008_ADDRESS;
	return;
}

////////////////////////////////////////////////////////////////////////////
// begin(addr) - Initialize the card
// addr - can be either the 0x20-0x27 or 0x00-0x07
// I2CIO8 Card specific I/O configuration
// Based on the following functions
// https://www.arduino.cc/en/Reference/WireBegin
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CIO8::begin(uint8_t addr)
{
	i2caddr = MCP23008_ADDRESS + (addr&7);	// foolproof it
	Wire.begin();			// Join I2C as a master (void = master)
#if defined(ARDUINO_ARCH_AVR)
	TWBR = 12;    			// go to 400 KHz I2C speed mode
#elif defined(ARDUINO_ARCH_STM32)
	Wire.setClock(400000);	// 400KHz speed
#else
  #error “This library only supports boards with an AVR or STM processors.”
#endif
	write8(MCP23008_IODIR,0xf0);	// Special values for card (4 in/4 out)
	write8(MCP23008_GPIO, 0x00);	// preset output bits to 0
	write8(MCP23008_INTCON,0x00);	// Interrupt control
	write8(MCP23008_IOCON,0x00);	// Set interrupt polarity
	write8(MCP23008_IPOL,0xf0);		// Special input polarity values for card
	write8(MCP23008_GPINTEN,0xf0);	// Special interrupt on change values for card
	read8(MCP23008_GPIO);			// Clear port change interrupt line
	return;
}

////////////////////////////////////////////////////////////////////////////
// begin(void) - Initialize the card
// If called without an address, assumes address is first part
//	"Default" I2C Address is 0x20
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CIO8::begin(void)
{
	begin(0);		// called without address, assume 0x20 address
	return;
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

void LandBoards_I2CIO8::pinMode(uint8_t bit, uint8_t d)
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

void LandBoards_I2CIO8::pullUp(uint8_t bit, uint8_t d) 
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

void LandBoards_I2CIO8::digitalWrite(uint8_t bit, uint8_t d) 
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

uint8_t LandBoards_I2CIO8::digitalRead(uint8_t bit)
{
	bit &= 7;
	return (read8(MCP23008_GPIO) >> bit) & 0x1;
}

////////////////////////////////////////////////////////////////////////////
// writeOLAT(uint8_t value)- write out an entire byte
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CIO8::writeOLAT(uint8_t value)
{
	write8(MCP23008_OLAT,value);
}

////////////////////////////////////////////////////////////////////////////
// readGPIO(void)
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_I2CIO8::readGPIO(void)
{
	return (read8(MCP23008_GPIO));
}

////////////////////////////////////////////////////////////////////////////
// uint8_t read8(regAddr) 
// https://www.arduino.cc/en/Reference/WireRequestFrom
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_I2CIO8::read8(uint8_t regAddr) 
{
	Wire.beginTransmission(i2caddr);
	Wire.write((uint8_t)regAddr);	
	Wire.endTransmission();
	Wire.requestFrom(i2caddr, 1);		// get 1 byte
	return (uint8_t)Wire.read();
}

////////////////////////////////////////////////////////////////////////////
// void LandBoards_I2CIO8::write8(regAddr, value) 
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CIO8::write8(uint8_t regAddr, uint8_t value) 
{
	Wire.beginTransmission(i2caddr);
	Wire.write((uint8_t)regAddr);
	Wire.write((uint8_t)value);
	Wire.endTransmission();
}

////////////////////////////////////////////////////////////////////////////
// writeLED(bit,value)
// D0-D3 are LEDs D0-D3
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CIO8::writeLED(uint8_t bit,uint8_t value)
{
	digitalWrite(bit, value);
}

////////////////////////////////////////////////////////////////////////////
// readAllJumpers()
// D4-D7 are H5-H8 jumpers
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_I2CIO8::readAllJumpers(void)
{
	return ((read8(MCP23008_GPIO) & 0xf0) >> 4);
}

////////////////////////////////////////////////////////////////////////////
// readJumper(uint8_t)
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_I2CIO8::readJumper(uint8_t bit)
{
	return digitalRead(bit);
}
