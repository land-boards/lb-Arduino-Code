/*
  Based on Blink from the Arduino sketch
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

#define LED_PORT 2

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(LED_PORT, OUTPUT);     
}

void loop() 
{
  digitalWrite(LED_PORT, HIGH);   // set the LED on
  delay(1000);                    // wait for a second
  digitalWrite(LED_PORT, LOW);    // set the LED off
  delay(1000);                    // wait for a second
}
