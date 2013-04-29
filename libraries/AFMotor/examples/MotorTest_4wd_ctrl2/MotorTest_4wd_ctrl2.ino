/////////////////////////////////////////////////////////////
// AFMotor 4WD card test software
// Controls the 4WD car from the keyboard
/////////////////////////////////////////////////////////////
// M1 is right rear wiring is backwards (by colors)
// M2 is left rear wiring is backwards (by colors)
// M3 is right front wiring is OK (by colors)
// M4 is left front wiring is backwards (by colors)
// Reversed wiring to make it work, but keeping it documented
/////////////////////////////////////////////////////////////

#include <AFMotor.h>

//#define DEBUG
#undef DEBUG

// Instantiate the four motors
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

// Left and Right Current speed variables
// Need to keep track of the current speeds for stopping (to
//   ramp down evenly)
int leftSpeed, rightSpeed;

/////////////////////////////////////////////////////////////
// stopMotors()
// Ramps down motor speed twice as quickly as the acceleration
// If the 4WD is currently turning, keep turning
// If the 4WD is currently stopped, do nothing.
/////////////////////////////////////////////////////////////

void stopMotors(void)
{
  int i;
#ifdef DEBUG
  Serial.println("Received stop command");
  Serial.print("Left Speed = ");
  Serial.println(leftSpeed);
  Serial.print("Right Speed = ");
  Serial.println(rightSpeed);
#endif
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
        delay(5);
      }
  }
  else if (leftSpeed > rightSpeed)
  {
      for (i=255; i>=0; i--) 
      {
        motor1.setSpeed(i/2);
        motor2.setSpeed(i);  
        motor3.setSpeed(i/2);  
        motor4.setSpeed(i);  
        delay(5);
      }
  }
  else if (rightSpeed > leftSpeed)
  {
      for (i=255; i>=0; i--) 
      {
        motor1.setSpeed(i);
        motor2.setSpeed(i/2);  
        motor3.setSpeed(i);  
        motor4.setSpeed(i/2);  
        delay(5);
      }
  }
}

/////////////////////////////////////////////////////////////
// setup() - Startup code displays the menu
/////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor Control from keyboard!");
  Serial.println("a=left, s=stop, d = right, w=forward, x=reverse");
  Serial.println("Hit [Enter] after character");
}

/////////////////////////////////////////////////////////////
// loop() - Loop code checks keyboard and operates on key
/////////////////////////////////////////////////////////////

void loop() {
  uint8_t i;
  if (Serial.available() > 0) {
    int inByte = Serial.read();
  switch (inByte)
  {
    case 'a':  // go left
    case 'A':
    {
      stopMotors();
      Serial.println("Left...   ");
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
    case 'd':  // go right
    case 'D':
    {
      stopMotors();
      Serial.println("Right...   ");
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
    case 'w':  // go forward
    case 'W':
    {
      stopMotors();
      Serial.println("Forward...   ");
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
    case 'x':  // go backward
    case 'X':
    {
      stopMotors();
      Serial.println("Backward...   ");
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
    case 's':  // go backward
    case 'S':
    {
      Serial.println("Stopping...   ");
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
}
