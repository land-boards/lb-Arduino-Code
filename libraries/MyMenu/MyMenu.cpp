////////////////////////////////////////////////////////////////////////////
//  MyMenu.cpp - Library for MyMenu
//  Created by Douglas Gilliland. 2015-03-29
//  MyMenu is a card which has all of the menu parts\
//		OLED pass-thru connector
//		Keypad (Up, Down, Left, Right, Select)
//		(3) LEDs
//		I2C Two-wire interface
//	http://land-boards.com/blwiki/index.php?title=MyMenu
////////////////////////////////////////////////////////////////////////////

#include "MyMenu.h"

#include "Arduino.h"
#include <inttypes.h>

////////////////////////////////////////////////////////////////////////////
// MyMenu constructor
////////////////////////////////////////////////////////////////////////////

MyMenu::MyMenu(void)
{
	mcp.begin();      // use default address 0
	initPins();
	return;
}

////////////////////////////////////////////////////////////////////////////
// initPins() - Initialize the pins on MyMenu card
////////////////////////////////////////////////////////////////////////////

void MyMenu::initPins(void)
{
  digitalWrite(RED_LITE, HIGH);    // LED, HIGH = OFF, LOW = ON
  digitalWrite(GRN_LITE, HIGH);    // LED, HIGH = OFF, LOW = ON
  pinMode(RED_LITE, OUTPUT);
  mcp.pinMode(GRN_LITE, OUTPUT);
  digitalWrite(RED_LITE, LOW);    // LED, HIGH = OFF, LOW = ON
	mcp.pinMode(0, OUTPUT);
	mcp.pinMode(1, OUTPUT);
	mcp.pinMode(2, OUTPUT);
	mcp.pinMode(3, INPUT);
	mcp.pinMode(4, INPUT);
	mcp.pinMode(5, INPUT);
	mcp.pinMode(6, INPUT);
	mcp.pinMode(7, INPUT);

	return;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

void MyMenu::setLED(int ledNum, int val)
{
	mcp.digitalWrite(ledNum, val);
}

////////////////////////////////////////////////////////////////////////////
// pollKeypad() - Returns the value of the instantaneously pressed keys
////////////////////////////////////////////////////////////////////////////

uint8_t MyMenu::pollKeypad(void)
{
	if (mcp.digitalRead(3) == 0)
		return(SELECT);
	else if (mcp.digitalRead(4) == 0)
		return(RIGHT);
	else if (mcp.digitalRead(5) == 0)
		return(DOWN);
	else if (mcp.digitalRead(6) == 0)
		return(UP);
	else if (mcp.digitalRead(7) == 0)
		return(LEFT);
	return(NONE);
}

////////////////////////////////////////////////////////////////////////////
// waitForKeyRelease() - Stick in the routine as long as the key is pressed
////////////////////////////////////////////////////////////////////////////

void MyMenu::waitForKeyRelease(void)
{
	while (pollKeypad() != NONE)
	delay(5);
	return;
}

////////////////////////////////////////////////////////////////////////////
// getKeyPressed() - Hang around polling the keypad waiting for a key 
//  to be pressed.
// When the key is pressed, hang around waiting for the key to be released.
// Returns the value of the key that was pressed.
////////////////////////////////////////////////////////////////////////////

uint8_t MyMenu::getKeyPressed(void)
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

uint8_t MyMenu::waitKeyPressed(void)
{
	uint8_t keyPadVal3;
	do
	{
		keyPadVal3 = pollKeypad();
	}
	while (keyPadVal3 == NONE);
	delay(5);
	waitForKeyRelease();
	return((uint8_t)keyPadVal3);
}

////////////////////////////////////////////////////////////////////////////
// delayAvailable(int delayTime) - Delay but check the Serial.available flag
// This is useful for places that a delay lasts for a noticable time and
//  there is a reason to break into the delay for serial input.
////////////////////////////////////////////////////////////////////////////

uint8_t MyMenu::delayAvailable(int delayTime)
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
