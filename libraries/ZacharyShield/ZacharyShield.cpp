////////////////////////////////////////////////////////////////////////////
//  ZacharyShield.cpp - Library for Zachary Shield
//  Created by Douglas Gilliland. 2012-04-20
//  Advanced Acoustic Concepts
////////////////////////////////////////////////////////////////////////////

#include "Arduino.h"
#include "ZacharyShield.h"
#include <SoftwareServo.h>

#undef SERIAL_DEBUG_ZSHIELD

SoftwareServo servo1;
SoftwareServo servo2;

////////////////////////////////////////////////////////////////////////////
// ZacharyShield - Constructor
////////////////////////////////////////////////////////////////////////////

ZacharyShield::ZacharyShield(void)
{
	initPins();
}

////////////////////////////////////////////////////////////////////////////
// pollKeypad() - Returns the value of the pressed keys
////////////////////////////////////////////////////////////////////////////

signed char ZacharyShield::pollKeypad(void)
{
#ifdef SERIAL_DEBUG_ZSHIELD
  Serial.println("Reached pollKeypad()");
#endif
  unsigned int sensorValue = analogRead(A0);
#ifdef SERIAL_DEBUG_ZSHIELD
  Serial.print("Switch Value = ");
  Serial.println(sensorValue);
#endif
  if (sensorValue > 871)    // quick if none is pressed
    return((byte)NONE);  
  else if (sensorValue <= 67)
    return((byte)RIGHT);
  else if (sensorValue <= 214)
    return((byte)UP);
  else if (sensorValue <= 384)
    return((byte)DOWN);
  else if (sensorValue <= 596)
    return((byte)LEFT);
  else
    return((byte)SELECT);
}

////////////////////////////////////////////////////////////////////////////
// waitForKeyRelease() - Stick in the routine as long as the key is pressed
////////////////////////////////////////////////////////////////////////////

void ZacharyShield::waitForKeyRelease(void)
{
  while (analogRead(A0) <= 871)
    delay(5);
}

////////////////////////////////////////////////////////////////////////////
// getKeyPressed() - get the value of the pressed key
// Does some key debouncing.
////////////////////////////////////////////////////////////////////////////

signed char ZacharyShield::getKeyPressed(void)
{
  signed char keyPadVal2;
  keyPadVal2 = pollKeypad();
  if (keyPadVal2 == NONE)
    return((signed char)NONE);
  waitForKeyRelease();
  return((signed char)keyPadVal2);
}

////////////////////////////////////////////////////////////////////////////
// waitKeyPressed() - Wait until a key is pressed
////////////////////////////////////////////////////////////////////////////

signed char ZacharyShield::waitKeyPressed(void)
{
  signed char keyPadVal3;
  do
  {
    keyPadVal3 = pollKeypad();
  }
  while (keyPadVal3 == NONE);
  delay(5);
  waitForKeyRelease();
  return((signed char)keyPadVal3);
}

////////////////////////////////////////////////////////////////////////////
// delayAvailable(int delayTime) - Delay but check the Serial.available flag
// This is useful for places that a delay lasts for a noticable time and
//  there is a reason to break into the delay for serial input.
////////////////////////////////////////////////////////////////////////////

signed char ZacharyShield::delayAvailable(int delayTime)
{  
  int delayTimeDiv5;
  delayTimeDiv5 = delayTime / 5;
  while (delayTimeDiv5 > 0)
  {
    if (pollKeypad() != NONE)
      return((signed char)1);
    delay(5);
    delayTimeDiv5--;
  }
  return((signed char)0);
}

////////////////////////////////////////////////////////////////////////////
// initPins() - Initialize the pins
////////////////////////////////////////////////////////////////////////////

void ZacharyShield::initPins(void)
{
  // Starts with all relays in normal (unenergized) state
  digitalWrite(RELAY1PIN,HIGH);
  digitalWrite(RELAY2PIN,HIGH);
  digitalWrite(RELAY3PIN,HIGH);
  digitalWrite(RELAY4PIN,HIGH);
  // Set up relay output pins
  pinMode(RELAY1PIN,OUTPUT);
  pinMode(RELAY2PIN,OUTPUT);
  pinMode(RELAY3PIN,OUTPUT);
  pinMode(RELAY4PIN,OUTPUT);
  // Starts with LEDs off
  redLED(LEDOFF);
  yellowLED(LEDOFF);
  greenLED(LEDOFF);
  pinMode(REDLEDPIN,OUTPUT);
  pinMode(YELLEDPIN,OUTPUT);
  pinMode(GRNLEDPIN,OUTPUT);
  // Set up servo output pins
  pinMode(SERVO_1,OUTPUT);
  pinMode(SERVO_2,OUTPUT);
  return;
}

////////////////////////////////////////////////////////////////////////////
// setServo1(value) - where value goes from 0-255;
////////////////////////////////////////////////////////////////////////////

void ZacharyShield::setServo1(unsigned char servoValue)
{
	servo1.write(servoValue);
	return;
}

////////////////////////////////////////////////////////////////////////////
// setServo2(value) - where value goes from 0-255;
////////////////////////////////////////////////////////////////////////////

void ZacharyShield::setServo2(unsigned char servoValue)
{
	servo2.write(servoValue);
	return;
}

////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////

void ZacharyShield::redLED(LEDVAL ledValue)
{
	if (ledValue == LEDOFF)
		digitalWrite(REDLEDPIN,HIGH);
	else
		digitalWrite(REDLEDPIN,LOW);
	return;
}

////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////

void ZacharyShield::greenLED(LEDVAL ledValue)
{
	if (ledValue == LEDOFF)
		digitalWrite(GRNLEDPIN,HIGH);
	else
		digitalWrite(GRNLEDPIN,LOW);
	return;
}

////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////

void ZacharyShield::yellowLED(LEDVAL ledValue)
{
	if (ledValue == LEDOFF)
		digitalWrite(YELLEDPIN,HIGH);
	else
		digitalWrite(YELLEDPIN,LOW);
	return;
}
