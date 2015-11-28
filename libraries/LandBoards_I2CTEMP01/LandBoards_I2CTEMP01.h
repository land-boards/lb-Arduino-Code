////////////////////////////////////////////////////////////////////////////
//  landboards_TCN75A.cpp - I2C Temperature Library
//  Created by Douglas Gilliland. 2015-11-24
//	http://land-boards.com/blwiki/index.php?title=I2C-TEMP-01
////////////////////////////////////////////////////////////////////////////

#ifndef _LandBoards_I2CTEMP01_h
#define _LandBoards_I2CTEMP01_h

#include <Wire.h>
#include <inttypes.h>
#include "Arduino.h"

////////////////////////////////////////////////////////////////////////////////////
// enums follow
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
// I2C Ports
////////////////////////////////////////////////////////////////////////////

#define TCN75A_BASEADDR 0x48
#define TCN75A_TEMPREG 0x00
#define TCN75A_CONFIG 0x01
#define TCN75A_THYST 0x02
#define TCN75A_SET 0x03

#define TCN75A_ONESHOT 0x80
#define TCN75A_RESOL 0x60
#define TCN75A_FAULTQUEUE 0x18
#define TCN75A_ALERTPOL 0x04
#define TCN75A_COMP0INT1 0x02
#define TCN75A_SHUTDOWN 0x01

#define TCN75A_RES9BIT 0x00
#define TCN75A_RES10BIT 0x40
#define TCN75A_RES11BIT 0x20
#define TCN75A_RES12BIT 0x60
#define TCN75A_RESMASK 0x9f

class LandBoards_I2CTEMP01
{
  public:
    LandBoards_I2CTEMP01(void);
	void begin(uint8_t);
	void begin();
    float getTemp(void);
	uint8_t readConfigRegister(void);
	uint8_t readShadowConfigRegister(void);
	void writeConfigRegister(uint8_t);
	void writeTSetRegister(uint16_t);
	uint16_t readTSetRegister(void);
	void setResolution(uint8_t);
	void writeTHystRegister(uint16_t);
	uint16_t readTHystRegister(void);
  private:
	uint8_t i2cAddrOffset;
	uint8_t configShadow;
	void write16BitReg(uint8_t, uint16_t);
	uint16_t read16BitReg(uint8_t);
};

#endif
