////////////////////////////////////////////////////////////////////////
// I2CRPT_I2CIO8Cylon Example code
// Blink each line, one at a time - cylon style
////////////////////////////////////////////////////////////////////////
// Hardware
//  Arduino NANO Breakout board
//    http://land-boards.com/blwiki/index.php?title=NANO-BKOUT
//  or STM32 Blue Pill board
//    http://land-boards.com/blwiki/index.php?title=STM32
//  I2C Repeater
//    http://land-boards.com/blwiki/index.php?title=I2C-RPT
//  I2CIO-8 - I2C Expander with 4 LEDs
//    http://land-boards.com/blwiki/index.php?title=I2CIO-8
////////////////////////////////////////////////////////////////////////
// 2019-03-03 - Tested with SMT32F103C Blue Pill
////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include "LandBoards_I2CIO8.h"
#include "LandBoards_I2CRPT01.h"

LandBoards_I2CIO8 myI2CIO8;
LandBoards_I2CRPT01 mux;

////////////////////////////////////////////////////////////////////////
//  setup()
////////////////////////////////////////////////////////////////////////

void setup() 
{
  uint8_t port;
  
  mux.begin(0);   // start the mux
  mux.setI2CChannel(0);
  myI2CIO8.begin(0);      // use default address 0

  for (port = 0; port < 4; port++)
    myI2CIO8.pinMode(port, OUTPUT);
}

////////////////////////////////////////////////////////////////////////
//  loop()
//  flip the pin #0 up and down
////////////////////////////////////////////////////////////////////////

void loop() 
{
  uint8_t port;

  for (port = 0; port < 4; port++)
  {
    myI2CIO8.writeLED(port, HIGH);
    delay(250);
    myI2CIO8.writeLED(port, LOW);
  }
  for (port = 2; port > 0; port--)
  {
    myI2CIO8.writeLED(port, HIGH);
    delay(250);
    myI2CIO8.writeLED(port, LOW);
  }
}
