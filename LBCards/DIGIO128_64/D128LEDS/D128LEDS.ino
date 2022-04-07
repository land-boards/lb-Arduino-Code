// DIGIO-16 Example code
// Make all 128 lines outputs
// Blink each line, one at a time

#include "LandBoards_Digio128V2.h"

LandBoards_Digio128_64 Dio128;
  
void setup() 
{
	uint8_t port;
	Dio128.begin();
	for (port = 0; port < 64; port++)
	{
		Dio128.pinMode(port,OUTPUT);
	}
}

// flip each of the pins up and down

void loop() {
  uint8_t port;
  
	for (port = 0; port < 64; port++)
	{
		Dio128.digitalWrite(port, HIGH);
		delay(100);
		Dio128.digitalWrite(port, LOW);
	}
}
