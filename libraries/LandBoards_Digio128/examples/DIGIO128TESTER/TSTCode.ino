////////////////////////////////////////////////////////////////////////////////
// Other Test Related Code
////////////////////////////////////////////////////////////////////////////////

#include "LandBoards_Digio128.h"
#include "DIGIO128TESTER-DEFS.h"

////////////////////////////////////////////////////////////////////////////////
// blinkFailLedForever() - Puts an LED on the last port which indicates failure
// Break out by hitting a key
////////////////////////////////////////////////////////////////////////////////

void blinkFailLedForever(void)
{
  while (Serial.available() > 0)
    Serial.read();
  while (1)
  {
    Dio128.pinMode(127, OUTPUT);
    Dio128.digitalWrite(127, HIGH);
    delay(500);
    Dio128.digitalWrite(127, LOW);
    delay(500);
    if (Serial.available())
      return;
  }
}
