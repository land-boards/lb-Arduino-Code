// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

// M1 is right rear wiring is backwards (by colors)
// M2 is left rear wiring is backwards (by colors)
// M3 is right front wiring is OK (by colors)
// M4 is left front wiring is backwards (by colors)

#include <AFMotor.h>

#include "Ultrasonic.h"

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

Ultrasonic ultrasonic(13,2);
short ranges[5];

//#define SERIAL_DEBUG
#undef SERIAL_DEBUG

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

int UD = 0;
int LR = 0;

int leftSpeed, rightSpeed;
int lastJoystk;

////////////////////////////////////////////////////////////

void stopMotors(void)
{
  int i;
  if ((leftSpeed == 0) && (rightSpeed == 0))
    return;
  else if (leftSpeed == rightSpeed)
  {
      for (i=255; i>=0; i--) 
      {
        motor1.setSpeed(i);
        motor2.setSpeed(i);  
        motor3.setSpeed(i);  
        motor4.setSpeed(i);  
        delay(10);
      }
  }
  else if (leftSpeed > rightSpeed)
  {
      for (i=255; i>=0; i--) 
      {
        motor1.setSpeed(i);
        motor2.setSpeed(i/2);  
        motor3.setSpeed(i);  
        motor4.setSpeed(i/2);  
        delay(10);
      }
  }
  else if (rightSpeed > leftSpeed)
  {
      for (i=255; i>=0; i--) 
      {
        motor1.setSpeed(i/2);
        motor2.setSpeed(i);  
        motor3.setSpeed(i/2);  
        motor4.setSpeed(i);  
        delay(10);
      }
  }
}

void setup() 
{
#ifdef SERIAL_DEBUG
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor Control from a wired joystick!");
#endif

  // turn on motor
//  motor1.setSpeed(200);
//  motor2.setSpeed(200);
//  motor3.setSpeed(200);
//  motor4.setSpeed(200);
 
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  lastJoystk = STOP;
  initRanges();
}

void putNewRange(long newRangeVal)
{
 ranges[0] = ranges[1];
 ranges[1] = ranges[2];
 ranges[2] = ranges[3];
 ranges[3] = ranges[4];
 ranges[4] = newRangeVal;
 return;
}

void initRanges(void)
{
  putNewRange(ultrasonic.Ranging(INC));
  putNewRange(ultrasonic.Ranging(INC));
  putNewRange(ultrasonic.Ranging(INC));
  putNewRange(ultrasonic.Ranging(INC));
  putNewRange(ultrasonic.Ranging(INC));  
}

short getRangeVal(void)
{
  if (ranges[4] == ranges[3])
    return(ranges[4]);
  else if (ranges[4] == ranges[3] + 1)
    return(ranges[3]);
  else if (ranges[4] == ranges[3] -1 )
    return(ranges[3]);
  else if (ranges[4] == ranges[2])
    return(ranges[4]);
  else if (ranges[3] == ranges[2])
    return(ranges[3]);
  else if (ranges[2] == ranges[1])
    return(ranges[2]);
  else return(ranges[4]);
  
}


void loop() 
{
  uint8_t i;

//  if (Serial.available() > 0) {
//    int inByte = Serial.read();

  int inByte;
  int joystkVal;
  
  joystkVal = joystick();
  if (joystkVal == lastJoystk)
    return;
  lastJoystk = joystkVal;
  
  switch (joystkVal)
  {
    case FWD_LEFT:  // go left
    {
      stopMotors();
#ifdef SERIAL_DEBUG
      Serial.println("Left...   ");
#endif
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
      for (i=0; i<255; i++) 
      {
        motor1.setSpeed(i);
        motor2.setSpeed(i/2);  
        motor3.setSpeed(i);  
        motor4.setSpeed(i/2);  
        delay(10);
      }
      leftSpeed = i/2;
      rightSpeed = i;
    }
    break;
    case FWD_RIGHT:  // go right
    {
      stopMotors();
#ifdef SERIAL_DEBUG
      Serial.println("Right...   ");
#endif
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
      for (i=0; i<255; i++) 
      {
        motor1.setSpeed(i/2);
        motor2.setSpeed(i);  
        motor3.setSpeed(i/2);  
        motor4.setSpeed(i);  
        delay(10);
      }
      leftSpeed = i;
      rightSpeed = i/2;
    }
    break;
    case FWD:  // go forward
    {
      stopMotors();
#ifdef SERIAL_DEBUG
      Serial.println("Forward...   ");
#endif
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
      for (i=0; i<255; i++) 
      {
        motor1.setSpeed(i);
        motor2.setSpeed(i);  
        motor3.setSpeed(i);  
        motor4.setSpeed(i);  
        delay(10);
      }
      leftSpeed = i;
      rightSpeed = i;
    }
    break;
    case BK:  // go backward
    case BK_LEFT:
    case BK_RIGHT:
    {
      stopMotors();
#ifdef SERIAL_DEBUG
      Serial.println("Backward...   ");
#endif
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      motor3.run(BACKWARD);
      motor4.run(BACKWARD);
      for (i=0; i<255; i++) 
      {
        motor1.setSpeed(i);
        motor2.setSpeed(i);  
        motor3.setSpeed(i);  
        motor4.setSpeed(i);  
        delay(10);
      }
      leftSpeed = i;
      rightSpeed = i;
    }
    break;
    case STOP:  // go backward
    {
#ifdef SERIAL_DEBUG
      Serial.println("Stopping...   ");
#endif
      stopMotors();
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(RELEASE);
      delay(1000);
      leftSpeed = 0;
      rightSpeed = 0;
     }
     break;
  }
}
