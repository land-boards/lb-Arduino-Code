////////////////////////////////////////////////////////////////////////////
//  LandBoards_MyMenu.h - Library for LandBoards_MyMenu Shield
//  Created by Douglas Gilliland. 2015-04-21
////////////////////////////////////////////////////////////////////////////
// MCP23008 expander pin assignments are -
//  0 = LED D3
//	1 = LED D2
//	2 = LED D1
//	3 = SELECT
//	4 = RIGHT
//	5 = DOWN
//	6 = UP
//	7 = LEFT
////////////////////////////////////////////////////////////////////////////

#ifndef LandBoards_MyMenu_g2_h
#define LandBoards_MyMenu_g2_h

#include <inttypes.h>
#include <Adafruit_MCP23008.h>
#include "Arduino.h"

////////////////////////////////////////////////////////////////////////////////////
// enums follow
////////////////////////////////////////////////////////////////////////////////////

enum KEY_PRESSES
{
  NONE,
  RIGHT,
  UP,
  DOWN,
  LEFT,
  SELECT,
};

////////////////////////////////////////////////////////////////////////////
// I2C Ports
//	OLED 0x78 (typical)
//	MCP23008 0x20
////////////////////////////////////////////////////////////////////////////

class LandBoards_MyMenu
{
  public:
    LandBoards_MyMenu(void);
    uint8_t pollKeypad(void);
    void waitForKeyRelease(void);
    uint8_t getKeyPressed(void);
    uint8_t waitKeyPressed(void);
    uint8_t delayAvailable(int delayTime);
	void setLED(int ledNum, int val);
	void begin(int);
	void begin();
  private:
    void initPins(void);
	Adafruit_MCP23008 mcp;
};

#endif
