// DIGIO16-I2C Example code
// Make all 16 lines outputs
// Blink each line, one at a time

#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 mcp0;

void setup() {
  mcp0.begin(0);      // use default address 0
  TWBR = 12;    // go to 400 KHz I2C speed mode

  uint8_t chip;
  uint8_t port;

  for (chip = 0; chip < 1; chip++)
  {
    for (port = 0; port < 16; port++)
    {
      mcp0.pinMode(port, OUTPUT);
    }
  }
}

// flip the pin #0 up and down

void loop() {

  uint8_t chip;
  uint8_t port;

  for (port = 0; port < 16; port++)
  {
    mcp0.digitalWrite(port, HIGH);
    delay(250);
    mcp0.digitalWrite(port, LOW);
    //      delay(250);
  }
}

