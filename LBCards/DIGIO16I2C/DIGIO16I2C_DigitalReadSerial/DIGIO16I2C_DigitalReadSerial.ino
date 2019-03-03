//////////////////////////////////////////////////////////////////////////////////////////
//  DIGIO16I2C_DigitalReadSerial
//  Reads digital input bit 0 from DIGIO16 and prints the result to the Serial Monitor
//  This example code is in the public domain.
//  http://www.arduino.cc/en/Tutorial/DigitalReadSerial
//////////////////////////////////////////////////////////////////////////////////////////
// Digital pin has a pushbutton attached to it. Give it a name:
//////////////////////////////////////////////////////////////////////////////////////////

#include "LandBoards_MCP23017.h"

LandBoards_MCP23017 mcp0;

#define BIT_TO_READ 0

// the setup routine runs once when you press reset:
void setup() 
{
  Serial.begin(9600);   // initialize serial communication at 9600 bits per second:
  mcp0.begin(0);
  mcp0.pinMode(BIT_TO_READ,INPUT_PULLUP);   // make the pushbutton's pin an input:
}

// the loop routine runs over and over again forever:
void loop() 
{
  int pinState = mcp0.digitalRead(BIT_TO_READ); // read the input pin:
  Serial.println(pinState);                     // print out the state of the button:
  delay(1);                                     // delay in between reads for stability
}
