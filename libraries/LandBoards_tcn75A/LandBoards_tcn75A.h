////////////////////////////////////////////////////////////////////////////
//  landboards_pca9544a.h - I2C Bridge PCA9544A Library 
//  Created by Douglas Gilliland. 2015-09-05
//	http://land-boards.com/blwiki/index.php?title=I2C-RPT
////////////////////////////////////////////////////////////////////////////

#ifndef _landboards_pca9544a_h
#define _landboards_pca9544a_h

#include <inttypes.h>
#include "Arduino.h"

////////////////////////////////////////////////////////////////////////////////////
// enums follow
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
// I2C Ports
////////////////////////////////////////////////////////////////////////////

#define PCA9544A_ADDRESS 0x70
#define PCA9544A_CTRLREG 0x00

class landboards_pca9544a
{
  public:
	void begin(uint8_t addr);
	void begin();
    landboards_pca9544a(void);
    uint8_t setI2CChannel(void);
    void setI2CChannel(uint8_t);
    uint8_t getIntStatus(void);
//	void setIntr(int intNum, int val);
//	void clrIntr(int intNum, int val);
  private:
	uint8_t i2cAddrOffset;
	uint8_t ctrl_copy;
	uint8_t read8(uint8_t addr);
	void write8(uint8_t addr, uint8_t data);
};

#endif
