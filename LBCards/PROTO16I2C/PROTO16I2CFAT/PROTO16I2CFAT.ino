//////////////////////////////////////////////////////////
// PROTO16I2CFAT : PROTO16-I2C EEPROM Exercise code
// Uses the Serial port to display a menu
//////////////////////////////////////////////////////////
// 2019-03-03 - Tested with STM32F1 Blue Pill
//////////////////////////////////////////////////////////

#include "LandBoards_MCP23017.h"

LandBoards_MCP23017 mcp;   // Uses the Adafruit MCP23017 library - globals

//////////////////////////////////////////////////////////
// setup()
//////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(9600);     // 9600 baud serial connection
  mcp.begin(0);          // Instantate MCP23017 chip
  Serial.println("\nR=Read EEPROM, W=Write EEPROM");
}

//////////////////////////////////////////////////////////
// loop()
//////////////////////////////////////////////////////////

void loop()
{
  int incomingByte = 0;   // for incoming serial data
  if (Serial.available() > 0) // If there is serial data present
  {
    incomingByte = Serial.read();     // read the incoming byte:
    if ((incomingByte == 'R') || (incomingByte == 'r'))
    {
      eepromRead();
    }
    else if ((incomingByte == 'W') || (incomingByte == 'w'))
    {
      eepromWrite();
    }
    else
    {
      Serial.println("Unrecognized command");
      Serial.println("\nR=Read EEPROM, W=Write EEPROM");
    }
    while (Serial.available() > 0)    // Flush extra read data (CR-LF extras)
      Serial.read();
  }
}
