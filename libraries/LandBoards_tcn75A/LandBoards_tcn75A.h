////////////////////////////////////////////////////////////////////////////
//  landboards_TCN75A.h - I2C Bridge TCN75A Library 
//  Created by Douglas Gilliland. 2015-09-05
//	http://land-boards.com/blwiki/index.php?title=I2C-RPT
////////////////////////////////////////////////////////////////////////////

#ifndef _landboards_TCN75A_h
#define _landboards_TCN75A_h

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

class landboards_TCN75A
{
  public:
    landboards_TCN75A(void);
	void begin(uint8_t);
	void begin();
    float getTemp(void);
	uint8_t readControlRegister(void);
	void setResolution(uint8_t);
	void setOneShot(void);
  private:
	uint8_t i2cAddrOffset;
	uint8_t configShadow;
};

#endif
