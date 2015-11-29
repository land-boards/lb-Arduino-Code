////////////////////////////////////////////////////////////////////////////
// Example code that exercises the LandBoards_I2CTEMP01 library
////////////////////////////////////////////////////////////////////////////

#include <LandBoards_I2CTEMP01.h>
#include "Wire.h"
#include "LedControl.h"

#define CENTER 0x1
#define UL 0x2
#define LL 0x4
#define BOTTOM 0x8
#define LR 0x10
#define UR 0x20
#define TOP 0x40

LandBoards_I2CTEMP01 myTemp;
LedControl lc = LedControl(12, 11, 10, 1);

unsigned long delaytime = 250;

////////////////////////////////////////////////////////////////////////////
// setup()
////////////////////////////////////////////////////////////////////////////

void setup()
{
  myTemp.begin(0x0);		// Begin communications with the I2C part at address 0
  Serial.begin(115200);
  myTemp.writeConfigRegister(0x00);
  myTemp.setResolution((uint8_t) TCN75A_RES12BIT);
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
}

////////////////////////////////////////////////////////////////////////////
/*
  This method will scroll all the hexa-decimal
 numbers and letters on the display. You will need at least
 four 7-Segment digits. otherwise it won't really look that good.
 */
 ////////////////////////////////////////////////////////////////////////////

void scrollDigits() {
  for (int i = 0; i < 9; i++) {
    lc.setDigit(0, 7, i, false);
    lc.setDigit(0, 6, i + 1, false);
    lc.setDigit(0, 5, i + 2, false);
    lc.setDigit(0, 4, i + 3, false);
    lc.setDigit(0, 3, i + 4, false);
    lc.setDigit(0, 2, i + 5, false);
    lc.setDigit(0, 1, i + 6, false);
    lc.setDigit(0, 0, i + 7, false);
    delay(delaytime);
  }
  lc.clearDisplay(0);
  delay(delaytime);
}

////////////////////////////////////////////////////////////////////////////
// void writeTempOn7Segment(void)
////////////////////////////////////////////////////////////////////////////

void writeTempOn7Segment(void)
{
  float temperatureInC;
  int digit1, digit2, digit3, digit4, remainder;
  int tempInt;
  temperatureInC = 10.0 * ((9.0 * myTemp.getTemp() / 5.0) + 32.0);
  tempInt = int(temperatureInC);

  digit1 = tempInt / 1000;
  remainder = tempInt - (digit1 * 1000);
  digit2 = remainder / 100;
  remainder -= digit2 * 100;
  digit3 = remainder / 10;
  remainder -= digit3 * 10;

  if (digit1 >= 1)
    lc.setChar(0, 7, char(digit1), false); // 100's digit
  lc.setChar(0, 6, char(digit2), false);
  lc.setChar(0, 5, char(digit3), true);
  lc.setChar(0, 4, char(remainder), false);
  lc.setRow(0, 2, UL|LL|CENTER|TOP);
  delay(delaytime);
}

////////////////////////////////////////////////////////////////////////////
// loop()
////////////////////////////////////////////////////////////////////////////

void loop()
{
  //  lc.clearDisplay(0);
  delay(delaytime);
  writeTempOn7Segment();
}

