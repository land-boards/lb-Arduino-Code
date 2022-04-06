// DIGIO16I2C_Blink
// DIGIO-16 Example code
// Blink LED

#include "LandBoards_MCP23017.h"

LandBoards_MCP23017 mcp0;

void setup()
{
  mcp0.begin(0);
  mcp0.pinMode(0,OUTPUT);
}

// flip the pin #0 up and down

void loop() 
{
    mcp0.digitalWrite(0, HIGH);
    delay(250);
    mcp0.digitalWrite(0, LOW);
    delay(250);
}
