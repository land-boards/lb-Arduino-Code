// DIGIO128 Example code
// Make all 128 lines outputs
// Blink each line, one at a time

#include "LandBoards_Digio128V2.h"

LandBoards_Digio128V2 Dio32;

void setup() {
  Dio32.begin();      // use default address 0
  uint8_t port;
  for (port = 0; port < 128; port++)
    Dio32.pinMode(port, OUTPUT);
}

// flip the pin #0 up and down

void loop() 
{
  uint8_t port;
  for (port = 0; port < 128; port++)
  {
    Dio32.digitalWrite(port, HIGH);
    delay(250);
    Dio32.digitalWrite(port, LOW);
  }
}
