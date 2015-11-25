////////////////////////////////////////////////////////////////////////////
//  landboards_TCN75A.cpp - I2C Temperature Library
//  Created by Douglas Gilliland. 2015-11-24
//	http://land-boards.com/blwiki/index.php?title=I2C-TEMP-01
////////////////////////////////////////////////////////////////////////////

#include "Wire.h"
#include <avr/pgmspace.h>
#include <inttypes.h>
#include "landboards_TCN75A.h"

////////////////////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////////////////////

landboards_TCN75A::landboards_TCN75A()
{
	return;
}

////////////////////////////////////////////////////////////////////////////
// begin(uint8_t addr) - 
////////////////////////////////////////////////////////////////////////////

void landboards_TCN75A::begin(uint8_t addr) 
{
	i2cAddrOffset = addr & 0x7;
	configShadow = 0;

	Wire.begin();

	Wire.beginTransmission(TCN75A_BASEADDR | i2cAddrOffset);// Start I2C connection
	Wire.write((uint8_t)TCN75A_CONFIG);           			// Register Point to config register
	Wire.endTransmission();           						// Command to read bytes
	Wire.beginTransmission(TCN75A_BASEADDR | i2cAddrOffset);// Start I2C connection
	Wire.write((uint8_t)configShadow);	           			// Clear the config shadow
	Wire.endTransmission();           						// Command to read bytes
	TWBR = 12;
}

////////////////////////////////////////////////////////////////////////////
// begin(void) - 
////////////////////////////////////////////////////////////////////////////

void landboards_TCN75A::begin(void)
{
	begin(0);
}

////////////////////////////////////////////////////////////////////////////
// getTemp() - Get the temperature
////////////////////////////////////////////////////////////////////////////

float landboards_TCN75A::getTemp(void)
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

uint8_t landboards_TCN75A::readShadowConfigRegister(void)
{
	return(configShadow);
}

////////////////////////////////////////////////////////////////////////////
// readConfigRegister() - Read from the Config register
////////////////////////////////////////////////////////////////////////////

uint8_t landboards_TCN75A::readConfigRegister(void)
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

void landboards_TCN75A::writeConfigRegister(uint8_t ctrlVal)
{
	configShadow = ctrlVal;
	Wire.beginTransmission(TCN75A_BASEADDR | i2cAddrOffset);	// Start I2C connection
	Wire.write((uint8_t)TCN75A_CONFIG);           			// Register Point to first register
	Wire.write((uint8_t)configShadow);           			// Register Point to first register
	Wire.endTransmission();           						// Command to read bytes
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

uint16_t landboards_TCN75A::readTSetRegister(void)
{
	return(read16BitReg(TCN75A_SET));
}

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////

void landboards_TCN75A::writeTSetRegister(uint16_t setVal)
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

void landboards_TCN75A::setResolution(uint8_t res)
{
	configShadow = readConfigRegister();
	configShadow &= TCN75A_RESMASK;
	configShadow |= res;
	writeConfigRegister(configShadow);
}

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////

uint16_t landboards_TCN75A::readTHystRegister(void)
{
	return(read16BitReg(TCN75A_THYST));
}

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////

void landboards_TCN75A::writeTHystRegister(uint16_t hystVal)
{
	write16BitReg((uint8_t)TCN75A_THYST, (uint16_t)hystVal);
}

////////////////////////////////////////////////////////////////////////////
// void write16BitReg(uint16_t wrReg, setVal)
////////////////////////////////////////////////////////////////////////////

void landboards_TCN75A::write16BitReg(uint8_t wrReg, uint16_t setVal)
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

uint16_t landboards_TCN75A::read16BitReg(uint8_t wrReg)
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
