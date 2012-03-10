//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
// M1 is right rear wiring is backwards (by colors)
// M2 is left rear wiring is backwards (by colors)
// M3 is right front wiring is OK (by colors)
// M4 is left front wiring is backwards (by colors)

void initMotors(void)
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  
}

int commandMotors(byte motorCommand)
{
    switch (motorCommand)
    {
    case FWD_LEFT:  // go left
      forwardLeft();
      break;
    case FWD_RIGHT:  // go right
      forwardRight();
      break;
    case FWD:  // go forward
      forward();
      break;
    case BK:  // go backward
      back();
      break;
    case BK_LEFT:
      backLeft();
      break;
    case BK_RIGHT:
      backRight();
      break;
    case STOP:  // go backward
      {
#ifdef SERIAL_DEBUG_MOTORS
        Serial.println("Stopping...   ");
#endif
        stopMotors();
      }
      break;
    }
  }

//////////////////////////////////////////////////////////////////////////
// stopMotors() - Ramps down motors speeds
//////////////////////////////////////////////////////////////////////////

void stopMotors(void)
{
  int i;
  if ((leftSpeed == 0) && (rightSpeed == 0))
    return;
  else if (leftSpeed == rightSpeed)
  {
    for (i=255; i>=0; i-=10) 
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
    for (i=255; i>=0; i-=10) 
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
    for (i=255; i>=0; i-=10) 
    {
      motor1.setSpeed(i/2);
      motor2.setSpeed(i);  
      motor3.setSpeed(i/2);  
      motor4.setSpeed(i);  
      delay(10);
    }
  }
  motor1.setSpeed(0);
  motor2.setSpeed(0);  
  motor3.setSpeed(0);  
  motor4.setSpeed(0);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

  leftSpeed = 0;
  rightSpeed = 0;
  currentMotorState = STOP;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

void forwardLeft(void)
{
  uint8_t i;
  stopMotors();
#ifdef SERIAL_DEBUG_MOTORS
  Serial.println("Left...   ");
#endif
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  for (i=0; i<255; i+=5) 
  {
    motor1.setSpeed(i);
    motor2.setSpeed(i/2);  
    motor3.setSpeed(i);  
    motor4.setSpeed(i/2);  
    delay(10);
  }
  leftSpeed = i/2;
  rightSpeed = i;
  currentMotorState = FWD_LEFT;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

void forwardRight(void)
{
  uint8_t i;
  stopMotors();
#ifdef SERIAL_DEBUG_MOTORS
  Serial.println("Right...   ");
#endif
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  for (i=0; i<255; i+=5) 
  {
    motor1.setSpeed(i/2);
    motor2.setSpeed(i);  
    motor3.setSpeed(i/2);  
    motor4.setSpeed(i);  
    delay(10);
  }
  leftSpeed = i;
  rightSpeed = i/2;
  currentMotorState = FWD_RIGHT;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

void forward(void)
{
  uint8_t i;
  stopMotors();
#ifdef SERIAL_DEBUG_MOTORS
  Serial.println("Forward...   ");
#endif
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  for (i=0; i<255; i+=5) 
  {
    motor1.setSpeed(i);
    motor2.setSpeed(i);  
    motor3.setSpeed(i);  
    motor4.setSpeed(i);  
    delay(10);
  }
  leftSpeed = i;
  rightSpeed = i;
  currentMotorState = FWD;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

void back(void)
{
  uint8_t i;
  stopMotors();
#ifdef SERIAL_DEBUG_MOTORS
  Serial.println("Backward...   ");
#endif
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  for (i=0; i<255; i+=5) 
  {
    motor1.setSpeed(i);
    motor2.setSpeed(i);  
    motor3.setSpeed(i);  
    motor4.setSpeed(i);  
    delay(10);
  }
  leftSpeed = i;
  rightSpeed = i;
  currentMotorState = BK;
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void backRight(void)
{
  uint8_t i;
  stopMotors();
#ifdef SERIAL_DEBUG_MOTORS
  Serial.println("Backward...   ");
#endif
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  for (i=0; i<255; i+=5) 
  {
    motor1.setSpeed(i/2);
    motor2.setSpeed(i);  
    motor3.setSpeed(i/2);  
    motor4.setSpeed(i);  
    delay(10);
  }
  leftSpeed = i;
  rightSpeed = i/2;
  currentMotorState = BK_RIGHT;
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void backLeft(void)
{
  uint8_t i;
  stopMotors();
#ifdef SERIAL_DEBUG_MOTORS
  Serial.println("Backward...   ");
#endif
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  for (i=0; i<255; i+=5) 
  {
    motor1.setSpeed(i);
    motor2.setSpeed(i/2);  
    motor3.setSpeed(i);  
    motor4.setSpeed(i/2);  
    delay(10);
  }
  leftSpeed = i/2;
  rightSpeed = i;
  currentMotorState = BK_LEFT;
}

