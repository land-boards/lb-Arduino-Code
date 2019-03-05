//////////////////////////////////////////////////////////////////////////////////////////
//  DIGIO128_DigitalReadSerial
//  Reads digital input bit 0 from DIGIO-128 and prints the result to the Serial Monitor
// http://land-boards.com/blwiki/index.php?title=DIGIO-128
//////////////////////////////////////////////////////////////////////////////////////////

#include "LandBoards_Digio128V2.h"

LandBoards_Digio128V2 Dio128;

#define BIT_TO_READ 0

// the setup routine runs once when you press reset:
void setup() 
{
  Serial.begin(9600);   // initialize serial communication at 9600 bits per second:
  Dio128.begin();
  Dio128.pinMode(BIT_TO_READ,INPUT_PULLUP);   // make the pushbutton's pin an input:
}

// the loop routine runs over and over again forever:
void loop() 
{
  int pinState = Dio128.digitalRead(BIT_TO_READ); // read the input pin:
  Serial.println(pinState);                     // print out the state of the button:
  delay(1);                                     // delay in between reads for stability
}
