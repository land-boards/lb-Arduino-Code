////////////////////////////////////////////////////////////////////////////
//  LandBoards_IReflow.h - Library for LandBoards_IReflow Shield
//  Created by Douglas Gilliland. 2012-07-27
////////////////////////////////////////////////////////////////////////////
// Pin assignments as referenced to the LandBoards_IReflow Board
// 
////////////////////////////////////////////////////////////////////////////

#ifndef LandBoards_IReflow_h
#define LandBoards_IReflow_h

#include "Arduino.h"

////////////////////////////////////////////////////////////////////////////////////
// enums follow
////////////////////////////////////////////////////////////////////////////////////

// enum KEY_PRESSES
// {
  // NONE,
  // RIGHT,
  // UP,
  // DOWN,
  // LEFT,
  // SELECT,
// };

////////////////////////////////////////////////////////////////////////////
// I/O Pins on the Arduino UNO as used by the Board
// Ports/Leo Functions/Connections
// PF0(ADC0) = Analog Input 5 = SW5WAY
// PB3 = MISO
// PB2 = MOSI
// PB1 = SCK
////////////////////////////////////////////////////////////////////////////

#define SSR 4
#define GRN_LITE 5   // pwmable
#define RED_LITE 6   // pwmable
#define BUZZ 10      // pwmable

// #define KEYPAD      A0

#define LCD_ROWS 5
#define LCD_COLUMNS 13

#define LED_ON LOW
#define LED_OFF HIGH

class LandBoards_IReflow
{
  public:
    LandBoards_IReflow(void);
    // uint8_t pollKeypad(void);
    // void waitForKeyRelease(void);
    // uint8_t getKeyPressed(void);
    // uint8_t waitKeyPressed(void);
    // uint8_t delayAvailable(int delayTime);
	void redLED(int);
	void greenLED(int);
  private:
    void initPins(void);
};

#endif
