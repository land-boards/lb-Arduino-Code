////////////////////////////////////////////////////////////////////////////
// Example code that exercises the LandBoards_I2CTEMP01 library
////////////////////////////////////////////////////////////////////////////

#include <LandBoards_I2CTEMP01.h>
#include "Wire.h"
#include "LedControl.h"

LandBoards_I2CTEMP01 myTemp;
LedControl lc=LedControl(12,11,10,1);
 
unsigned long delaytime=250;

////////////////////////////////////////////////////////////////////////////
// setup()
////////////////////////////////////////////////////////////////////////////

void setup()
{
  myTemp.begin(0x0);		// Begin communications with the I2C part at address 0
  Serial.begin(115200);
  myTemp.writeConfigRegister(0x00);
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
}
 
/*
 This method will display the characters for the
 word "Arduino" one after the other on digit 0. 
 setRow values
 0x01 = center
 0x02 = upper left
 0x04 =  lower left
 0x08 = bottom
 0x10 = lower right
 0x20 = upper right
 0x40 = top
 */
 
#define CENTER 0x1
#define UL 0x2
#define LL 0x4
#define BOTTOM 0x8
#define LR 0x10
#define UR 0x20
#define TOP 0x40
/*
  This method will scroll all the hexa-decimal
 numbers and letters on the display. You will need at least
 four 7-Segment digits. otherwise it won't really look that good.
 */
void scrollDigits() {
  for(int i=0;i<9;i++) {
    lc.setDigit(0,7,i,false);
    lc.setDigit(0,6,i+1,false);
    lc.setDigit(0,5,i+2,false);
    lc.setDigit(0,4,i+3,false);
    lc.setDigit(0,3,i+4,false);
    lc.setDigit(0,2,i+5,false);
    lc.setDigit(0,1,i+6,false);
    lc.setDigit(0,0,i+7,false);
    delay(delaytime);
  }
  lc.clearDisplay(0);
  delay(delaytime);
}

void writeTempOn7Segment() 
{
  float temperatureInC;
  int tempInt;
  temperatureInC = (9.0 * myTemp.getTemp() / 5.0) + 32.0;
  tempInt = int(temperatureInC);
  int digit1, digit2, digit3, digit4, remainder;

  digit1 = tempInt/100;
  remainder = tempInt - (digit1*100);
  digit2 = remainder/10;
  remainder -= digit2 * 10;
  digit3 = remainder;
  
if (digit1 >= 1)
  lc.setChar(0,7,char(digit1),false);    // L
//  delay(delaytime);
  lc.setChar(0,6,char(digit2),false);    // L
//  delay(delaytime);
  lc.setChar(0,5,char(digit3),true);    // L
  delay(delaytime);
}
////////////////////////////////////////////////////////////////////////////
// loop()
////////////////////////////////////////////////////////////////////////////

void loop()
{
//  readConfigReg();
//  readShadowConfigReg();
//  testTSetReg();
//  testHystReg();
//  testTemp();
//
//  lc.clearDisplay(0);
  delay(delaytime);
  writeTempOn7Segment();
  }

////////////////////////////////////////////////////////////////////////////
// readConfigReg()
////////////////////////////////////////////////////////////////////////////

void readConfigReg(void)
{
  uint8_t configReg;
  configReg = myTemp.readConfigRegister();
  Serial.print("Config register = 0x");
  Serial.println(configReg, HEX);
}

////////////////////////////////////////////////////////////////////////////
// readTemp()
////////////////////////////////////////////////////////////////////////////

void readTemp(void)
{
  Serial.print("Temperature = ");
  Serial.println(myTemp.getTemp());
}

////////////////////////////////////////////////////////////////////////////
// readShadowConfigReg
////////////////////////////////////////////////////////////////////////////

void readShadowConfigReg(void)
{
  uint8_t configShadowReg;
  configShadowReg = myTemp.readShadowConfigRegister();
  Serial.print("Shadow config register value = 0x");
  Serial.println(configShadowReg, HEX);
}

////////////////////////////////////////////////////////////////////////////
// testTSetReg()
////////////////////////////////////////////////////////////////////////////

void testTSetReg(void)
{
  uint16_t tReg;
  myTemp.writeTSetRegister(0xa580);
  tReg = myTemp.readTSetRegister();
  Serial.print("tReg register, wrote: 0xA580, read back 0x");
  Serial.println(tReg, HEX);
}

////////////////////////////////////////////////////////////////////////////
// testTSetReg()
////////////////////////////////////////////////////////////////////////////

void testHystReg(void)
{
  uint16_t tReg;
  myTemp.writeTHystRegister(0x5a00);
  tReg = myTemp.readTHystRegister();
  Serial.print("tHyst register, wrote: 0x5A00, read back 0x");
  Serial.println(tReg, HEX);
}

////////////////////////////////////////////////////////////////////////////
// testTemp() 
////////////////////////////////////////////////////////////////////////////

void testTemp(void)
{
  Serial.println("Setting temperature resolution to 12 bits");
  myTemp.setResolution((uint8_t) TCN75A_RES12BIT);
  delay(500);
  readTemp();
  Serial.println("Setting temperature resolution to 11 bits");
  myTemp.setResolution((uint8_t) TCN75A_RES11BIT);
  delay(500);
  readTemp();
  Serial.println("Setting temperature resolution to 10 bits");
  myTemp.setResolution((uint8_t) TCN75A_RES10BIT);
  delay(500);
  readTemp();
  Serial.println("Setting temperature resolution to 9 bits");
  myTemp.setResolution((uint8_t) TCN75A_RES9BIT);
  delay(500);
  readTemp();
}

