//////////////////////////////////////////////////////////////////////////
// FourWD_js_usonic - Four Wheel Drive with Joystick and Ultrasonic sensor
// Analog Joystick
// Ultrasonic Sensor
//////////////////////////////////////////////////////////////////////////

#include <AFMotor.h>

#include "Ultrasonic.h"

#define SERIAL_DEBUG
#undef SERIAL_DEBUG
#define SERIAL_DEBUG_USONIC
#undef SERIAL_DEBUG_USONIC
#undef SERIAL_DEBUG_JOYSTICK
#undef SERIAL_DEBUG_CTLR
#undef SERIAL_DEBUG_MOTORS

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

Ultrasonic ultrasonic(13,2);

short ranges[5];

int leftSpeed, rightSpeed;
int currentMotorState;

enum ROBOT_DIR
{
  STOP = 0,
  FWD_RIGHT,
  FWD_LEFT,
  FWD,
  BK_RIGHT,
  BK_LEFT,
  BK, 
};

enum US_STOP_GO
{
  US_STOP = 0,
  US_RUN,
};

//////////////////////////////////////////////////////////////////////////
// setup() 
//////////////////////////////////////////////////////////////////////////

void setup() 
{
#ifdef SERIAL_DEBUG
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor Control from a wired joystick with ultrasonic stopping!");
#endif
  initMotors();  // Set up the motors
  initRanges();  // Set up the ultrasonic
}

//////////////////////////////////////////////////////////////////////////
// loop()
//////////////////////////////////////////////////////////////////////////

void loop() 
{
  byte joystkVal = joystick();
  if (checkUsonic(12) == US_RUN)
  {
    if (joystkVal == currentMotorState)
      return;
#ifdef SERIAL_DEBUG_CTLR
        Serial.println("US run - changing state");
#endif
    commandMotors(joystkVal);
  }
  else
  {
    if (currentMotorState == STOP)
    {
      if ((joystkVal == BK) || (joystkVal == BK_LEFT) || (joystkVal == BK_RIGHT))
      {
#ifdef SERIAL_DEBUG_CTLR
        Serial.println("US stop - going back");
#endif
        commandMotors(joystkVal);
      }
      else
        stopMotors();      
    }
    else if ((joystkVal != BK) && (joystkVal != BK_LEFT) && (joystkVal != BK_RIGHT))
      stopMotors();
  }
}


