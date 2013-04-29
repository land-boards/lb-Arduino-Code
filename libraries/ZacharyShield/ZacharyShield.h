////////////////////////////////////////////////////////////////////////////
//  ZacharyShield.h - Library for Zachary Shield
//  Created by Douglas Gilliland. 2012-04-20
//  Advanced Acoustic Concepts
////////////////////////////////////////////////////////////////////////////
// Pin assignments as referenced to the Zachary ProtoShield
// Arduino Port  Connector  Function
// D0, D1        N/C		Used by USB serial port
// D2            J17-4      Aux connector
// D3            J15-1      SERVO_1
// D4            J17-3      Aux connector
// D5            J1-3       Relay 3 (N/A)
// D6            J1-2       Relay 4 (N/A)
// D6 (alt)      J14-1      SERVO_2
// D7            J17-2      Aux connector
// D8                       Red LED
// D9                       Yellow LED
// D10                      Green LED
// D11           J14-1      One-Wire DQ
// D12           J1-4       Relay 2 (N/A)
// D13           J1-5       Relay 1 (N/A)
// A0            J8-J12     Switches
//                          J8 = Right
//                          J9 = Up
//                          J10 = Down
//                          J11 = Left
//                          J12 = Select
// A1            J3-2       Values (such as temperature) set potentiometer wiper
// A2            J18-2      Analog Inputs
// A3            J18-3      Analog Inputs
// A4 (SDA)      J7-3       I2C SDA LCD
// A5 (SCK)      J7-4       I2C SCK LCD
////////////////////////////////////////////////////////////////////////////

#ifndef ZacharyShield_h
#define ZacharyShield_h

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

#define J17PIN4   2
#define SERVO_1   3
#define J17PIN3   4
#define RELAY3PIN 5
#define RELAY4PIN 6
#define SERVO_2   6
#define J17PIN2   7
#define GRNLEDPIN 8
#define YELLEDPIN 9
#define REDLEDPIN 10
#define ONEWIREPIN 11
#define RELAY2PIN 12
#define RELAY1PIN 13
#define SWITCHES A0
#define POTVAL   A1
#define J18PIN2  A2
#define J18PIN3  A3
#define SDATA    A4
#define SDCLK    A5

enum LEDVAL
{
	LEDOFF,
	LEDON,
};

class ZacharyShield
{
  public:
    ZacharyShield(void);
	signed char pollKeypad(void);
	signed char delayAvailable(int);
	void redLED(LEDVAL);
	void greenLED(LEDVAL);
	void yellowLED(LEDVAL);
	void setServo1(unsigned char);
	void setServo2(unsigned char);
	signed char getKeyPressed(void);
	signed char waitKeyPressed(void);
  private:
	void waitForKeyRelease(void);
	void initPins(void);
};

#endif