////////////////////////////////////////////////////////////////////////////
//  I2CIO8Example.cpp - Example code for I2CIO8-8 card
//  Created by Douglas Gilliland. 2015-11-23
//  Code reads jumpers and writes the jumper values to the LEDs
//  I2CIO8-8 is a card which has an MCP23008 8-bit port expander
//	Communication with the card is via I2C Two-wire interface
//  Webpage for the card is at:
//	http://land-boards.com/blwiki/index.php?title=I2CIO-8
// Updated 2019-02-28 - Added STM32F1 support
////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <LandBoards_I2CIO8.h>

LandBoards_I2CIO8 MyI2CIO8;

////////////////////////////////////////////////////////////////////////////
// setup() - 
////////////////////////////////////////////////////////////////////////////

void setup()
{
  MyI2CIO8.begin(0x20);     // use default address 0x20
}

////////////////////////////////////////////////////////////////////////////
// loop() - 
////////////////////////////////////////////////////////////////////////////

void loop()
{
  uint8 lastJumpers = 0;
  uint8 allJumpers = 0;
  while(1)
  {
    allJumpers = MyI2CIO8.readAllJumpers();
    if (lastJumpers != allJumpers)
    {
      if ((lastJumpers & 1) != (allJumpers & 1))
        MyI2CIO8.writeLED(LED0, allJumpers & 1);
      if ((lastJumpers & 2) != (allJumpers & 2))
        MyI2CIO8.writeLED(LED1, (allJumpers >> 1) & 1);
      if ((lastJumpers & 4) != (allJumpers & 4))
        MyI2CIO8.writeLED(LED2, (allJumpers >> 2) & 1);
      if ((lastJumpers & 8) != (allJumpers & 8))
        MyI2CIO8.writeLED(LED3, (allJumpers >> 3) & 1);
      lastJumpers = allJumpers;
    }
    //delay(250);
  }
}
