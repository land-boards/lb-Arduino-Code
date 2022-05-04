// TinyPS02 - Read PS/2 Keyboard
// Write Serial data

#include <SoftwareSerial.h>

#define rxPin 3
#define txPin 2

// Set up SoftwareSerial and PS/2 objects
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

void setup() {

  pinMode(rxPin, INPUT_PULLUP);
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);
  
}

void loop() 
{
  char c;
  while (1)
  {
    for (c = 'A'; c <= 'Z'; c++)
      mySerial.write(c);
  }
}
