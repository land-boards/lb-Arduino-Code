// DIGIO32I2C_Blink
// DIGIO32-I2C Example code
// Blink LED

#include "LandBoards_DIGIO32I2C.h"

LandBoards_DIGIO32I2C Dio32;

void setup()
{
  Dio32.begin(0);
  Dio32.pinMode(0,OUTPUT);
}

// flip the pin #0 up and down

void loop() 
{
    Dio32.digitalWrite(0, HIGH);
    delay(250);
    Dio32.digitalWrite(0, LOW);
    delay(250);
}
