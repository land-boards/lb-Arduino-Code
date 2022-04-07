////////////////////////////////////////////////////////////////////////////
//  LandBoards_I2CRPT08.cpp - I2C Bridge PCA9548A Library 
//  Created by Douglas Gilliland. 2015-09-05
//  LandBoards_I2CRPT08
//	http://land-boards.com/blwiki/index.php?title=I2C-RPT
////////////////////////////////////////////////////////////////////////////

#include "LandBoards_I2CRPT08.h"
#include <Wire.h>
#include <avr/pgmspace.h>
#include <inttypes.h>

LandBoards_I2CRPT08::LandBoards_I2CRPT08()
{
}

////////////////////////////////////////////////////////////////////////////
// begin(uint8_t addr) - 
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CRPT08::begin(uint8_t addr) 
{
	i2caddr = I2CRPT08_ADDRESS | (addr & 0x7);
	Wire.begin();
#if defined(ARDUINO_ARCH_AVR)
	TWBR = 12;    			// go to 400 KHz I2C speed mode
#elif defined(ARDUINO_ARCH_STM32F1)
	Wire.setClock(400000);	// 400KHz speed
#elif defined(ARDUINO_ARCH_STM32F4)
	Wire.setClock(400000);	// 400KHz speed
#else
  #error “This library only supports boards with an AVR or STM processor.”
#endif
	ctrl_copy = 0;  // ctrl reg initialized 
	Wire.beginTransmission(i2caddr);
	Wire.write((byte)ctrl_copy);
	Wire.endTransmission();
}

////////////////////////////////////////////////////////////////////////////
// begin(void) - 
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CRPT08::begin(void)
{	
	begin(0);
}

////////////////////////////////////////////////////////////////////////////
// setI2CChannel() - 
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CRPT08::setI2CChannel(uint8_t chNum, uint8_t enableFlag)
{
	uint8_t bitToWrite;
	chNum &= 0x07;
	bitToWrite = 1 << chNum;
	if (enableFlag == 1)
		ctrl_copy |= bitToWrite;
	else
		ctrl_copy &= ~bitToWrite;
	Wire.beginTransmission(i2caddr);
	Wire.write((byte)ctrl_copy);
	Wire.endTransmission();
	return;
}

////////////////////////////////////////////////////////////////////////////
// getCurrentChannel(void) 
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_I2CRPT08::getI2CChannel(void)
{
	Wire.requestFrom(i2caddr, 1);
	return (Wire.read());
}
