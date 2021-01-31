////////////////////////////////////////////////////////////////////////////
//  LandBoards_I2CTEMP01.cpp - I2C Temperature Library
//  Created by Douglas Gilliland. 2015-11-24
//	http://land-boards.com/blwiki/index.php?title=I2C-TEMP-01
////////////////////////////////////////////////////////////////////////////

#include "Wire.h"
#include <avr/pgmspace.h>
#include <inttypes.h>
#include "LandBoards_I2CTEMP01.h"

////////////////////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////////////////////

LandBoards_I2CTEMP01::LandBoards_I2CTEMP01()
{
	return;
}

////////////////////////////////////////////////////////////////////////////
// begin(uint8_t addr) - 
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CTEMP01::begin(uint8_t addr) 
{
	i2cAddrOffset = addr & 0x7;
	configShadow = 0;

	Wire.begin();
#if defined(ARDUINO_ARCH_AVR)
	TWBR = 12;    			// go to 400 KHz I2C speed mode
#elif defined(ARDUINO_ARCH_STM32)
	Wire.setClock(400000);	// 400KHz speed
#else
  #error “This library only supports boards with an AVR or STM processor.”
#endif	
	Wire.beginTransmission(TCN75A_BASEADDR | i2cAddrOffset);// Start I2C connection
	Wire.write((uint8_t)TCN75A_CONFIG);           			// Register Point to config register
	Wire.endTransmission();           						// Command to read bytes
	Wire.beginTransmission(TCN75A_BASEADDR | i2cAddrOffset);// Start I2C connection
	Wire.write((uint8_t)configShadow);	           			// Clear the config shadow
	Wire.endTransmission();           						// Command to read bytes
}

////////////////////////////////////////////////////////////////////////////
// begin(void) - 
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CTEMP01::begin(void)
{
	begin(0);
}

////////////////////////////////////////////////////////////////////////////
// getTemp() - Get the temperature
////////////////////////////////////////////////////////////////////////////

float LandBoards_I2CTEMP01::getTemp(void)
{
  uint16_t tempValue;
  float temp=.0;
  float sign=1.;
  tempValue = read16BitReg(TCN75A_TEMPREG);
  if (tempValue & 0x8000)
  {
	  sign = -1.;
	  tempValue = ~tempValue;
  }
  temp = (sign*((float)(tempValue&0x7fff)) / 256.0);
  return(temp);
}

////////////////////////////////////////////////////////////////////////////
// readShadowConfigRegister() - Read from the Config register
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_I2CTEMP01::readShadowConfigRegister(void)
{
	return(configShadow);
}

////////////////////////////////////////////////////////////////////////////
// readConfigRegister() - Read from the Config register
////////////////////////////////////////////////////////////////////////////

uint8_t LandBoards_I2CTEMP01::readConfigRegister(void)
{
	Wire.beginTransmission(TCN75A_BASEADDR | i2cAddrOffset);// Start I2C connection
	Wire.write((uint8_t)TCN75A_CONFIG);           			// Register Point to config register
	Wire.endTransmission();           						// Command to read bytes
	Wire.requestFrom(TCN75A_BASEADDR | i2cAddrOffset, 1);	// Read
	configShadow = Wire.read();
	return(configShadow);										// Read control register
}

////////////////////////////////////////////////////////////////////////////
// writeConfigRegister(ctrlVal) - Write ctrlVal to the Config register
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CTEMP01::writeConfigRegister(uint8_t ctrlVal)
{
	configShadow = ctrlVal;
	Wire.beginTransmission(TCN75A_BASEADDR | i2cAddrOffset);	// Start I2C connection
	Wire.write((uint8_t)TCN75A_CONFIG);           			// Register Point to first register
	Wire.write((uint8_t)configShadow);           			// Register Point to first register
	Wire.endTransmission();           						// Command to read bytes
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

uint16_t LandBoards_I2CTEMP01::readTSetRegister(void)
{
	return(read16BitReg(TCN75A_SET));
}

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CTEMP01::writeTSetRegister(uint16_t setVal)
{
	write16BitReg(TCN75A_SET, setVal);
}

////////////////////////////////////////////////////////////////////////////
// setResolution(res) - Set resolution to one of these values
// #define TCN75A_RES9BIT 0x00
// #define TCN75A_RES10BIT 0x40
// #define TCN75A_RES11BIT 0x20
// #define TCN75A_RES12BIT 0x60
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CTEMP01::setResolution(uint8_t res)
{
	configShadow = readConfigRegister();
	configShadow &= TCN75A_RESMASK;
	configShadow |= res;
	writeConfigRegister(configShadow);
}

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////

uint16_t LandBoards_I2CTEMP01::readTHystRegister(void)
{
	return(read16BitReg(TCN75A_THYST));
}

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CTEMP01::writeTHystRegister(uint16_t hystVal)
{
	write16BitReg((uint8_t)TCN75A_THYST, (uint16_t)hystVal);
}

////////////////////////////////////////////////////////////////////////////
// void write16BitReg(uint16_t wrReg, setVal)
////////////////////////////////////////////////////////////////////////////

void LandBoards_I2CTEMP01::write16BitReg(uint8_t wrReg, uint16_t setVal)
{
	Wire.beginTransmission(TCN75A_BASEADDR | i2cAddrOffset);// Start I2C connection
	Wire.write((uint8_t)wrReg);			           			// Register Point to first register
	Wire.write((uint8_t)(setVal>>8));           			// Register Point to first register
	Wire.write((uint8_t)(setVal& 0xff));           			// Register Point to first register
	Wire.endTransmission();           						// Command to read bytes
}

////////////////////////////////////////////////////////////////////////////
// uint16_t read16BitReg(uint8_t wrReg)
////////////////////////////////////////////////////////////////////////////

uint16_t LandBoards_I2CTEMP01::read16BitReg(uint8_t wrReg)
{
	uint16_t retVal = 0;
	Wire.beginTransmission(TCN75A_BASEADDR | i2cAddrOffset);// Start I2C connection
	Wire.write((uint8_t)wrReg);           					// Register Point to config register
	Wire.endTransmission();           						// Command to read bytes
	Wire.requestFrom(TCN75A_BASEADDR | i2cAddrOffset, 2);	// Read
	retVal = Wire.read();
	retVal <<= 8;
	retVal |= Wire.read();
	return(retVal);
}
