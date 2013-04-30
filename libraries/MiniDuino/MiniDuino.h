////////////////////////////////////////////////////////////////////////////
//  MiniDuino.h - Library for Zachary Shield
//  Created by Douglas Gilliland. 2012-07-27
////////////////////////////////////////////////////////////////////////////
// Pin assignments as referenced to the Zachary ProtoShield
// Arduino Port  Connector  Function
// D0            J4-4       FTDI Transmit/Arduino Receive
// D1            J4-5       FTDI Receive/Arduino Transmit
// D2            J3-3       GPSRx
// D3            J3-4       GPSTx
// D4            J6-2       Digital Input
// D5            J6-3       Digital Input
// D6            J6-4       Digital Input
// D7            J1-9       SD Card Chip Select
// D8            J1-3       LCD Reset
// D9            J1-4       LCD Register Select (DC or RS)
// D10           J1-8       LCD Chip Select
// D11           J1-6       LCD MOSI 
// D12           J1-5       LCD MISO
// D13           J1-7       LCD SCK
// A0            J2-3       Keypad
// A1            J5-4       Values (such as temperature) set potentiometer wiper
// A2            J5-5       Analog Input
// A3            J5-6       Analog Input
// A4 (SDA)      J7-3       I2C SDA LCD
// A5 (SCK)      J7-4       I2C SCK LCD
////////////////////////////////////////////////////////////////////////////

#ifndef MiniDuino_h
#define MiniDuino_h

#include "Arduino.h"

////////////////////////////////////////////////////////////////////////////////////
// enums follow
////////////////////////////////////////////////////////////////////////////////////

enum KEY_PRESSES
{
  NONE = -1,
  RIGHT = 0,
  UP = 1,
  DOWN = 2,
  LEFT = 3,
  SELECT = 4,
};

////////////////////////////////////////////////////////////////////////////
// I/O Pins on the Arduino UNO as used by the Zachduino shield
////////////////////////////////////////////////////////////////////////////

#define GPSRX       2
#define GPSTX       3
#define DIGIO4      4
#define DIGIO5      5
#define DIGIO6      6
#define SD_CD       7
#define LCD_RST     8
#define LCD_DC      9 
#define LCD_CS      10
#define LCD_MOSI    11
#define LCD_MISO    12
#define LCD_SCK     13
#define KEYPAD      A0
#define ANALOGIN1   A1
#define ANALOGIN2   A2
#define ANALOGIN3   A3
#define SDATA       A4
#define SDCLK       A5

class MiniDuino
{
  public:
    MiniDuino(void);
    signed char pollKeypad(void);
    signed char delayAvailable(int delayTime);
  private:
    void waitForKeyRelease(void);
    signed char getKeyPressed(void);
    signed char waitKeyPressed(void);
    void initPins(void);
};

#endif
