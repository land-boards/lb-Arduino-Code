////////////////////////////////////////////////////////////////////////////
//  LandBoards_I2CRPT01.cpp - I2C Bridge PCA9544A Library 
//  Created by Douglas Gilliland. 2015-09-05
//  LandBoards_I2CRPT01
//	http://land-boards.com/blwiki/index.php?title=I2C-RPT
////////////////////////////////////////////////////////////////////////////

#include "LandBoards_I2CRPT01.h"
#include <avr/pgmspace.h>
#include <inttypes.h>

LandBoards_I2CRPT01::LandBoards_I2CRPT01()
{
	
}

////////////////////////////////////////////////////////////////////////////
// begin(uint8_t addr) - 
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CRPT01::begin(uint8_t addr) 
{
	i2caddr = PCA9544A_ADDRESS | (addr & 0x7);
	Wire.begin();
#if defined(ARDUINO_ARCH_AVR)
	TWBR = 12;    			// go to 400 KHz I2C speed mode
#elif defined(ARDUINO_ARCH_STM32F1)
	Wire.setClock(400000);	// 400KHz speed
#else
  #error “This library only supports boards with an AVR or SAM processor.”
#endif
	ctrl_copy = 0;  // ctrl reg initialized 
	Wire.beginTransmission(i2caddr);
	Wire.write((byte)ctrl_copy);
	Wire.endTransmission();
}

////////////////////////////////////////////////////////////////////////////
// begin(void) - 
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CRPT01::begin(void)
{	
	begin(0);
}

////////////////////////////////////////////////////////////////////////////
// setI2CChannel() - 
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CRPT01::setI2CChannel(uint8_t chNum)
{
	if (chNum > 3)
		return;
	ctrl_copy = 0x04 | (chNum&0x7);
	Wire.beginTransmission(i2caddr);
	Wire.write((byte)ctrl_copy);
	Wire.endTransmission();
	return;
}

////////////////////////////////////////////////////////////////////////////
// getCurrentChannel(void) 
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_I2CRPT01::getI2CChannel(void)
{
	Wire.requestFrom(i2caddr, 1);
	return (Wire.read() & 0x3);
}

////////////////////////////////////////////////////////////////////////////
// getIntStatus
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_I2CRPT01::getIntStatus(void)
{
	Wire.requestFrom(i2caddr, 1);
	return ((Wire.read() >> 4) & 0xf);
}
