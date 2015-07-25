// DIGIO-16 Example code
// Make all 128 lines outputs
// Blink each line, one at a time

#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 mcp0;
Adafruit_MCP23017 mcp1;
Adafruit_MCP23017 mcp2;
Adafruit_MCP23017 mcp3;
Adafruit_MCP23017 mcp4;
Adafruit_MCP23017 mcp5;
Adafruit_MCP23017 mcp6;
Adafruit_MCP23017 mcp7;
  
void setup() {  
  mcp0.begin(0);      // use default address 0
  mcp1.begin(1);      // use default address 0
  mcp2.begin(2);      // use default address 0
  mcp3.begin(3);      // use default address 0
  mcp4.begin(4);      // use default address 0
  mcp5.begin(5);      // use default address 0
  mcp6.begin(6);      // use default address 0
  mcp7.begin(7);      // use default address 0
  TWBR = 12;    // go to 400 KHz I2C speed mode

  uint8_t chip;
  uint8_t port;
  
  for (chip = 0; chip < 8; chip++)
  {
    for (port = 0; port < 16; port++)
    {
      mcpPinMode(chip, port, OUTPUT);
    }
  }
}

// flip the pin #0 up and down

void loop() {

  uint8_t chip;
  uint8_t port;
  
  for (chip = 0; chip < 8; chip++)
  {
    for (port = 0; port < 16; port++)
    {
      mcpWrite(chip, port, HIGH);
      delay(100);
      mcpWrite(chip, port, LOW);
    }
  }
}

/* mcpWrite(chipNum, chNum, val)
  Write a value to a pin.
  chipNum is from 0-7
  chNum is from 0-15
  val is LOW or HIGH
*/
void mcpWrite(uint8_t chipNum, uint8_t chNum, uint8_t val)
{
  switch (chipNum)
  {
  case 0:
    mcp0.digitalWrite(chNum, val);
    break;
  case 1:
    mcp1.digitalWrite(chNum, val);
    break;
  case 2:
    mcp2.digitalWrite(chNum, val);
    break;
  case 3:
    mcp3.digitalWrite(chNum, val);
    break;
  case 4:
    mcp4.digitalWrite(chNum, val);
    break;
  case 5:
    mcp5.digitalWrite(chNum, val);
    break;
  case 6:
    mcp6.digitalWrite(chNum, val);
    break;
  case 7:
    mcp7.digitalWrite(chNum, val);
    break;
  }  
}

/* mcpPinMode(chipNum, chNum, val)
  Set the pin to be an input or output.
  chipNum is from 0-7
  chNum is from 0-15
  val is INPUT or OUTPUT
*/
void mcpPinMode(uint8_t chipNum, uint8_t chNum, uint8_t val)
{
  switch (chipNum)
  {
  case 0:
    mcp0.pinMode(chNum, val);
    break;
  case 1:
    mcp1.pinMode(chNum, val);
    break;
  case 2:
    mcp2.pinMode(chNum, val);
    break;
  case 3:
    mcp3.pinMode(chNum, val);
    break;
  case 4:
    mcp4.pinMode(chNum, val);
    break;
  case 5:
    mcp5.pinMode(chNum, val);
    break;
  case 6:
    mcp6.pinMode(chNum, val);
    break;
  case 7:
    mcp7.pinMode(chNum, val);
    break;
  }  
}

/* mcpPullUp(chipNum, chNum, val)
  Set the pull up for a channel.
  chipNum is from 0-7
  chNum is from 0-15
  val is HIGH to turn on pull up and LOW to turn off pullup
*/
void mcpPullUp(uint8_t chipNum, uint8_t chNum, uint8_t val)
{
  switch (chipNum)
  {
  case 0:
    mcp0.pullUp(chNum, val);
    break;
  case 1:
    mcp1.pullUp(chNum, val);
    break;
  case 2:
    mcp2.pullUp(chNum, val);
    break;
  case 3:
    mcp3.pullUp(chNum, val);
    break;
  case 4:
    mcp4.pullUp(chNum, val);
    break;
  case 5:
    mcp5.pullUp(chNum, val);
    break;
  case 6:
    mcp6.pullUp(chNum, val);
    break;
  case 7:
    mcp7.pullUp(chNum, val);
    break;
  }  
}

/* mcpRead(chipNum, chNum)
  Reads a channel.
  chipNum is from 0-7
  chNum is from 0-15
  Returns the value of the pin
*/
uint8_t mcpRead(uint8_t chipNum, uint8_t chNum)
{
  switch (chipNum)
  {
    case 0:
      return(mcp0.digitalRead(chNum));
      break;
    case 1:
      return(mcp1.digitalRead(chNum));
      break;
    case 2:
      return(mcp2.digitalRead(chNum));
      break;
    case 3:
      return(mcp3.digitalRead(chNum));
      break;
    case 4:
      return(mcp4.digitalRead(chNum));
      break;
    case 5:
      return(mcp5.digitalRead(chNum));
      break;
    case 6:
      return(mcp6.digitalRead(chNum));
      break;
    case 7:
      return(mcp7.digitalRead(chNum));
      break;
  }
}
