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
// getTemp() - Set the temperature
////////////////////////////////////////////////////////////////////////////

float landboards_TCN75A::getTemp(void)
{
  uint8_t upperByte, lowerByte;
  float temp=.0;
  Wire.beginTransmission(TCN75A_BASEADDR | i2cAddrOffset);	// Start I2C connection
  Wire.write((uint8_t)TCN75A_TEMPREG);           			// Register Point to first register
  Wire.endTransmission();           						// Command to read bytes
  Wire.requestFrom(TCN75A_BASEADDR | i2cAddrOffset, 2);     // Read first two bytes
  upperByte = Wire.read();                  				// Read the temp upper
  lowerByte = Wire.read();                  				// Read the temp lower
  if (upperByte>127)            // check for below zero degrees
  {
    temp=((upperByte-128)*-1);
    if (lowerByte==128)         // check for 0.5 fraction
    {
      temp-=0.5;
    }
  }
  else                   // it must be above zero degrees
  {
    temp=upperByte;
    if (lowerByte==128)         // check for 0.5 fraction
    {
      temp+=0.5;
    }
  }
  return(temp);
}

////////////////////////////////////////////////////////////////////////////
// readControlRegister() - Read from the control register
////////////////////////////////////////////////////////////////////////////

uint8_t readControlRegister(void)
{
	return(0);
}
