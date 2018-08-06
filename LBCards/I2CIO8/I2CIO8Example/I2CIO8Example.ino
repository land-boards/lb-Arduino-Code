////////////////////////////////////////////////////////////////////////////
//  I2CIO8Example.cpp - Example code for I2CIO8-8 card
//  Created by Douglas Gilliland. 2015-11-23
//  I2CIO8-8 is a card which has an MCP23008 8-bit port expander
//	Communication with the card is via I2C Two-wire interface
//  Webpage for the card is at:
//	http://land-boards.com/blwiki/index.php?title=I2CIO-8
////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <LandBoards_I2CIO8.h>

LandBoards_I2CIO8 MyI2CIO8;

////////////////////////////////////////////////////////////////////////////
// setup() - 
////////////////////////////////////////////////////////////////////////////

void setup()
{
  MyI2CIO8.begin(0);     // use default address 0
  //  TWBR = 12;          // go to 400 KHz I2C speed mode
  pinMode(13, OUTPUT);
}

////////////////////////////////////////////////////////////////////////////
// loop() - 
////////////////////////////////////////////////////////////////////////////

void loop()
{
  MyI2CIO8.writeLED(LED0, MyI2CIO8.readJumper(H4JUMPER));
  MyI2CIO8.writeLED(LED1, MyI2CIO8.readJumper(H5JUMPER));
  MyI2CIO8.writeLED(LED2, MyI2CIO8.readJumper(H6JUMPER));
  MyI2CIO8.writeLED(LED3, MyI2CIO8.readJumper(H7JUMPER));
}

