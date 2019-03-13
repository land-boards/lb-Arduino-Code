// DIGIO-16 Loopback code
// Tests port-to-port loopback
// Reports any failures

#include "LandBoards_Digio128V2.h"

Digio128 Dio128;
  
void setup()
{
	Serial.begin(9600);
	Dio128.begin();
}

// flip the pin #0 up and down

void loop()
{
  if (loopBackTest() == 0)
    Serial.println("Loopback Test PASS");
  else
    Serial.println("Loopback Test FAILED");
}

uint8_t loopBackTest(void)
{
  uint8_t port;
  uint8_t pass0fail1 = 0;
    for (port = 0; port < 128; port++)
    {
      Dio128.pinMode(port, OUTPUT);
      Dio128.pinMode(15 - port,INPUT);
      
      delay(2);
      Dio128.digitalWrite(port, HIGH);
      delay(2);
      if (Dio128.digitalRead(15 - port) != HIGH)
      {
        Serial.print("Error on port ");
        Serial.print(port);
        Serial.println(" Expected High");
        pass0fail1 = 1;
      }
      Dio128.digitalWrite(port, LOW);
      delay(2);
      if (Dio128.digitalRead(15 - port) != LOW)
      {
        Serial.print("Error on port ");
        Serial.print(port);
        Serial.println(" Expected LOW");
        pass0fail1 = 1;
      }
      Dio128.pinMode(port, INPUT);
      delay(2);
    }
    return pass0fail1;
}