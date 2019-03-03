////////////////////////////////////////////////////////////////////////////
//  LandBoards_MCP23008.cpp - Library for MCP23008 cards
//  Created by Douglas Gilliland. 2015-11-23
//	Communication with the card is via I2C Two-wire interface
//	Part datasheet:
//	https://www.microchip.com/wwwproducts/en/MCP23008
//	Land Boards Products are sold at:
//	https://www.tindie.com/stores/land_boards/
//	2019-03-01 - Added support for STM32F1 "blus pill" boards
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

#include "LandBoards_MCP23008.h"

////////////////////////////////////////////////////////////////////////////
// LandBoards_MCP23008 constructor
////////////////////////////////////////////////////////////////////////////

LandBoards_MCP23008::LandBoards_MCP23008(void)
{
	return;
}

////////////////////////////////////////////////////////////////////////////
// begin(addr) - Initialize the card
// addr - can be either the 0x20-0x27 or 0x00-0x07
// Based on the following functions
// https://www.arduino.cc/en/Reference/WireBegin
////////////////////////////////////////////////////////////////////////////

void LandBoards_MCP23008::begin(uint8_t addr)
{
	i2caddr = MCP23008_ADDRESS + (addr&7);
	Wire.begin();			// Join I2C as a master (void = master)
#if defined(ARDUINO_ARCH_AVR)
	TWBR = 12;    			// go to 400 KHz I2C speed mode
#elif defined(ARDUINO_ARCH_STM32F1)
	Wire.setClock(400000);	// 400KHz speed
#else
  #error “This library only supports boards with an AVR or SAM processor.”
#endif
	write8(MCP23008_IODIR,0xff);	// set to all inputs
	write8(MCP23008_GPIO, 0x00);	// preset output bits to 0
	write8(MCP23008_INTCON,0x00);	// Interrupt control
	write8(MCP23008_IPOL,0x00);		// Input polarity
	write8(MCP23008_GPINTEN,0x00);	// Interrupt on change off
	read8(MCP23008_GPIO);			// Clear port change interrupt line
	return;
}

////////////////////////////////////////////////////////////////////////////
// begin(void) - Initialize the card
// If called without an address, assumes address is first part
//	"Default" I2C Address is 0x20
////////////////////////////////////////////////////////////////////////////

void LandBoards_MCP23008::begin(void)
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

void LandBoards_MCP23008::pinMode(uint8_t bit, uint8_t d)
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
////////////////////////////////////////////////////////////////////////////

void LandBoards_MCP23008::pullUp(uint8_t bit, uint8_t d) 
{
	uint8_t gppuCopy;
	uint8_t dupGppu;
	bit &= 7;
	gppuCopy = read8(MCP23008_GPPU);
	// set the pin and direction
	if (d == HIGH) {
		gppuCopy |= 1 << bit; 
	} else {
		gppuCopy &= ~(1 << bit);
	}
	// write the new pullup value only if there was a change
	if (gppuCopy != dupGppu)
		write8(MCP23008_GPPU, gppuCopy);
}

////////////////////////////////////////////////////////////////////////////
//  uint8_t digitalWrite(uint8_t, uint8_t)
////////////////////////////////////////////////////////////////////////////

void LandBoards_MCP23008::digitalWrite(uint8_t bit, uint8_t d) 
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

uint8_t LandBoards_MCP23008::digitalRead(uint8_t bit)
{
	bit &= 7;
	return (read8(MCP23008_GPIO) >> bit) & 0x1;
}

////////////////////////////////////////////////////////////////////////////
// writeOLAT(uint8_t value)
////////////////////////////////////////////////////////////////////////////

void LandBoards_MCP23008::writeOLAT(uint8_t value)
{
	write8(MCP23008_OLAT,value);
}

////////////////////////////////////////////////////////////////////////////
// readOLAT(void)
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_MCP23008::readOLAT(void)
{
	return (read8(MCP23008_OLAT));
}

////////////////////////////////////////////////////////////////////////////
// uint8_t read8(addr) 
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_MCP23008::read8(uint8_t addr) 
{
	Wire.beginTransmission(i2caddr);
	Wire.write((uint8_t)addr);	
	Wire.endTransmission();
	Wire.requestFrom(i2caddr, 1);
	return (uint8_t)Wire.read();
}

////////////////////////////////////////////////////////////////////////////
// void LandBoards_MCP23008::write8(addr, data) 
////////////////////////////////////////////////////////////////////////////

void LandBoards_MCP23008::write8(uint8_t addr, uint8_t data) 
{
	Wire.beginTransmission(i2caddr);
	Wire.write((uint8_t)addr);
	Wire.write((uint8_t)data);
	Wire.endTransmission();
}
