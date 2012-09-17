/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(0, OUTPUT);     
}

void loop() {
  digitalWrite(0, HIGH);   // set the LED on
  delay(1000);              // wait for a second
  digitalWrite(0, LOW);    // set the LED off
  delay(1000);              // wait for a second
}
