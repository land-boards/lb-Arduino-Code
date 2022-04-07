////////////////////////////////////////////////////////////////////////////
//  LandBoards_MCP423X.cpp - Library for MCP23008 cards
//  Created by Douglas Gilliland. 2022-04-05
//	Communication with the card is via SPI interface
//		https://www.arduino.cc/reference/en/language/functions/communication/spi/
//	Part datasheet:
//	http://ww1.microchip.com/downloads/en/DeviceDoc/22060b.pdf
//	Land Boards Products are sold at:
//	https://www.tindie.com/stores/land_boards/
////////////////////////////////////////////////////////////////////////////
//	Library class supports multiple types of access:
//		Arduino (bit) oriented
//      Byte oriented
////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <inttypes.h>

#include "LandBoards_MCP423X.h"

////////////////////////////////////////////////////////////////////////////
// LandBoards_MCP423X constructor
////////////////////////////////////////////////////////////////////////////

LandBoards_MCP423X::LandBoards_MCP423X(void)
{
	return;
}

////////////////////////////////////////////////////////////////////////////
//	begin
//	Passed:
//		slvSel - Slave Select pin number
////////////////////////////////////////////////////////////////////////////

void LandBoards_MCP423X::begin(uint8_t slvSel)
{
  //Set pin directions for SS
  slaveSelectPin = slvSel;
  pinMode(slaveSelectPin, OUTPUT);
  //Initialize SPI
  SPI.begin();
  return;
}

////////////////////////////////////////////////////////////////////////////
// begin(addr) - Initialize the card
////////////////////////////////////////////////////////////////////////////

void LandBoards_MCP423X::begin(void)
{
#if defined(ARDUINO_ARCH_AVR)
	slaveSelectPin = 10;
#elif defined(ARDUINO_ARCH_STM32F1)
	slaveSelectPin = PA15;
#elif defined(ARDUINO_ARCH_STM32F4)
	slaveSelectPin = PA4;
#else
  #error "This library only supports boards with an AVR or STM32F1, STM32F4 processor."
#endif
	begin(slaveSelectPin);
	return;
}

////////////////////////////////////////////////////////////////////////////
//  uint8_t digitalWrite(uint8_t, uint8_t)
////////////////////////////////////////////////////////////////////////////

void LandBoards_MCP423X::writePot(uint8_t reg, uint8_t level)
{
  digitalWrite(slaveSelectPin, LOW);	// Set the given SS pin low
  SPI.transfer(reg);   					// Choose the resistor to write to
  SPI.transfer(level);  				// Set the pot (0-128)
  digitalWrite(slaveSelectPin, HIGH);	// Set the given SS pin high again
}
