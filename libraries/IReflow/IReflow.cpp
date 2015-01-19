////////////////////////////////////////////////////////////////////////////
//  IReflow.cpp - Library for IReflow
//  Created by Douglas Gilliland. 2013-08-29
//  IReflow is an Leonardo compatible
////////////////////////////////////////////////////////////////////////////

#include "Arduino.h"
#include "IReflow.h"
 
////////////////////////////////////////////////////////////////////////////
// IReflow constructor
////////////////////////////////////////////////////////////////////////////

IReflow::IReflow(void)
{
  initPins();
  return;
}

////////////////////////////////////////////////////////////////////////////
// initPins() - Initialize the pins on the part
////////////////////////////////////////////////////////////////////////////

void IReflow::initPins(void)
{
  pinMode(SSR, OUTPUT);
  pinMode(RED_LITE, OUTPUT);
  pinMode(GRN_LITE, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  digitalWrite(SSR, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(BUZZ, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(RED_LITE, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(GRN_LITE, HIGH);    // turn the LED off by making the voltage LOW
  return;
}

////////////////////////////////////////////////////////////////////////////
// pollKeypad() - Returns the value of the instantenously pressed keys
////////////////////////////////////////////////////////////////////////////

uint8_t IReflow::pollKeypad(void)
{
  unsigned int sensorValue = analogRead(KEYPAD);
  if (sensorValue > 871)    // quick if none is pressed
    return((uint8_t)NONE);  
  else if (sensorValue <= 67)
    return(RIGHT);
  else if (sensorValue <= 214)
    return(UP);
  else if (sensorValue <= 384)
    return(DOWN);
  else if (sensorValue <= 596)
    return(LEFT);
  else
    return(SELECT);
}

////////////////////////////////////////////////////////////////////////////
// waitForKeyRelease() - Stick in the routine as long as the key is pressed
////////////////////////////////////////////////////////////////////////////

void IReflow::waitForKeyRelease(void)
{
  while (analogRead(KEYPAD) <= 871)
    delay(5);
}

////////////////////////////////////////////////////////////////////////////
// getKeyPressed() - Hang around polling the keypad waiting for a key 
//  to be pressed.
// When the key is pressed, hang around waiting for the key to be released.
// Returns the value of the key that was pressed.
////////////////////////////////////////////////////////////////////////////

uint8_t IReflow::getKeyPressed(void)
{
  signed char keyPadVal2;
  keyPadVal2 = pollKeypad();
  if (keyPadVal2 == NONE)
    return((byte)NONE);
  waitForKeyRelease();
  return((byte)keyPadVal2);
}

////////////////////////////////////////////////////////////////////////////
// waitKeyPressed()
////////////////////////////////////////////////////////////////////////////

uint8_t IReflow::waitKeyPressed(void)
{
  signed char keyPadVal3;
  do
  {
    keyPadVal3 = pollKeypad();
  }
  while (keyPadVal3 == NONE);
  delay(5);
  waitForKeyRelease();
  return((byte)keyPadVal3);
}

////////////////////////////////////////////////////////////////////////////
// delayAvailable(int delayTime) - Delay but check the Serial.available flag
// This is useful for places that a delay lasts for a noticable time and
//  there is a reason to break into the delay for serial input.
////////////////////////////////////////////////////////////////////////////

uint8_t IReflow::delayAvailable(int delayTime)
{  
  int delayTimeDiv4;
  delayTimeDiv4 = delayTime >> 2;
  while (delayTimeDiv4 > 0)
  {
    if (pollKeypad() != NONE)
      return((byte)1);
    delay(4);
    delayTimeDiv4--;
  }
  return(0);
}
