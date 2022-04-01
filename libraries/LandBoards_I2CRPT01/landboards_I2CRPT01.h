////////////////////////////////////////////////////////////////////////////
//  LandBoards_I2CRPT01.h - I2C Bridge PCA9544A Library 
//  Created by Douglas Gilliland. 2015-09-05
//	http://land-boards.com/blwiki/index.php?title=I2C-RPT
////////////////////////////////////////////////////////////////////////////

#ifndef _LandBoards_I2CRPT01_h
#define _LandBoards_I2CRPT01_h

#include <Wire.h>
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

#define I2CRPT01_CH0	0x04
#define I2CRPT01_CH1	0x05
#define I2CRPT01_CH2	0x06
#define I2CRPT01_CH3	0x07
#define I2CRPT01_NONE	0x00

class LandBoards_I2CRPT01
{
  public:
	void begin(uint8_t addr);
	void begin();
    LandBoards_I2CRPT01(void);
    void setI2CChannel(uint8_t);
	uint8_t getI2CChannel(void);
    uint8_t getIntStatus(void);
	// void setIntr(int intNum, int val);
	// void clrIntr(int intNum, int val);
  private:
	uint8_t i2caddr;
	uint8_t ctrl_copy;
	uint8_t read8(uint8_t addr);
	void write8(uint8_t addr, uint8_t data);
};

#endif
