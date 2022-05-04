// TinyPS02 - Read PS/2 Keyboard
// Write Serial data

#include <SoftwareSerial.h>
#include <PS2Keyboard.h>

const int DataPin = 0;
const int IRQpin =  1;

#define rxPin 3
#define txPin 2

// Set up SoftwareSerial and PS/2 objects
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
PS2Keyboard keyboard;

void setup() {

  pinMode(rxPin, INPUT_PULLUP);
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);
  
  keyboard.begin(DataPin, IRQpin);
}

void loop() 
{
  char c;
  while (1)
  {
    for (c = 'A'; c <= 'Z'; c++)
      mySerial.write(c);
  }
//  if (keyboard.available()) 
//  {
//    
//    // read the next key
//    char c = keyboard.read();
//    mySerial.write(c);
//  }
}
