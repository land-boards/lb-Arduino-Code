////////////////////////////////////////////////////////////////////////////
//  MyMenu.cpp - Library for MyMenu
//  Created by Douglas Gilliland. 2015-04-23
//  MyMenu is a card which has all of the menu parts
//		I2C Two-wire interface
//		OLED pass-thru connector
//      MCP23008 I2C Port Expander GPIO
//			Keypad (Up, Down, Left, Right, Select)
//			(3) LEDs
//	http://land-boards.com/blwiki/index.php?title=MyMenu
////////////////////////////////////////////////////////////////////////////

#include "LandBoards_MyMenu.h"

#include <inttypes.h>

////////////////////////////////////////////////////////////////////////////
// MyMenu constructor - As I learned by looking at the Adafruit LiquidCrystal 
// 	I2C library, can't can't call begin from the constructor. 
//	This probably has something to do with the constructor being a global.
//	The begin gets called from the setup code.
////////////////////////////////////////////////////////////////////////////

MyMenu::MyMenu(void)
{
	return;
}

void MyMenu::begin(int portNum)
{
	mcp.begin(portNum);   	// use default address 0	
	TWBR = 12;    	// go to 400 KHz I2C speed mode
	initPins();
}

void MyMenu::begin(void)
{
	mcp.begin();   	// use default address 0	
	TWBR = 12;    	// go to 400 KHz I2C speed mode
	initPins();
}

////////////////////////////////////////////////////////////////////////////
// initPins() - Initialize the pins on MyMenu card
////////////////////////////////////////////////////////////////////////////

void MyMenu::initPins(void)
{
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
	uint8_t readVal;
	readVal = mcp.readGPIO();
	if ((readVal & 0xf8) == 0xf8)
		return(NONE);
	else if ((readVal & 0x08) == 0)
		return(SELECT);
	else if ((readVal & 0x10) == 0)
		return(RIGHT);
	else if ((readVal & 0x20) == 0)
		return(DOWN);
	else if ((readVal & 0x40) == 0)
		return(UP);
	else if ((readVal & 0x80) == 0)
		return(LEFT);
	else
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
// This is useful for places that a delay lasts for a noticeable time and
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
