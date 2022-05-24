/*

 SWLEDX8_01.ino

  Wiki page for SWLEDX8
    http://land-boards.com/blwiki/index.php?title=SWLEDX8-I2C

  Runs on a 3.3V Arduino Pro Mini
  No 5V to 3.3V level shifting is needed for the I2C port of the OLED
  Arduino Pro Mini has internal EEPROM for parameter storage

*/

#include <Arduino.h>
#include <LandBoards_MCP23017.h>

// defines and enums - Set defines/undefs appropriately

// Gloibal variables

// Constructors

LandBoards_MCP23017 mcp;   // Uses the LandBoards MCP23017 library

// End of constructor list

//setup run once
void setup(void)
{
  uint8_t mcpPortNum;
  mcp.begin(0);      // use default chip offset 0 (Adafruit library adds 0x20)
  for (mcpPortNum=0; mcpPortNum < 8; mcpPortNum++)
    mcp.pinMode(mcpPortNum, INPUT);
  for (mcpPortNum=8; mcpPortNum < 16; mcpPortNum++)
    mcp.pinMode(mcpPortNum, OUTPUT);
    
}

// loop - loops forever
void loop(void)
{
  testSWLEDX8();
}

// Test the SWLEDX8 card
void testSWLEDX8(void)
{
  uint8_t rdWrVal;
  rdWrVal = mcp.readGPIOA();
  mcp.writeOLATB(rdWrVal);
}
