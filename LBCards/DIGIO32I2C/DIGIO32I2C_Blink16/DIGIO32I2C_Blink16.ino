// DIGIO32-I2C Example code
// Make all 32 lines outputs
// Blink each line, one at a time

#include "LandBoards_DIGIO32I2C.h"

LandBoards_DIGIO32I2C Dio32;

void setup() {
  Dio32.begin(0);      // use default address 0
  uint8_t port;
  for (port = 0; port < 32; port++)
    Dio32.pinMode(port, OUTPUT);
}

// flip the pin #0 up and down

void loop() 
{
  uint8_t port;
  for (port = 0; port < 32; port++)
  {
    Dio32.digitalWrite(port, HIGH);
    delay(250);
    Dio32.digitalWrite(port, LOW);
  }
}
