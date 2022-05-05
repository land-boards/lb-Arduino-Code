// TinyPS05 - Read PS/2 Keyboard, pulse serial out on receive char

#include <SoftwareSerial.h>
#include <PS2Keyboard_ATT85.h>

const int DataPin = 0;
const int IRQpin =  1;

//#define rxPin 3
#define txPin 2

// Set up PS/2 object
PS2Keyboard_ATT85 keyboard;

void setup() {

  pinMode(txPin, OUTPUT);
  keyboard.begin(DataPin, IRQpin);
}

void loop() {
  char c;
  if (keyboard.available()) 
  {
    c = keyboard.read();    // read the next key
    digitalWrite(txPin,HIGH);
    delay(10);
    digitalWrite(txPin,LOW);
  }
}
