/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

int loopCount;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(5, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW); 
  loopCount = 0;
}


// the loop function runs over and over again forever
void loop() {
  digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(5, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
  loopCount++;
  if (loopCount >= 5)
  {
    digitalWrite(10, HIGH);
  loopCount = 0;
  delay(1000);              // wait for a second
  digitalWrite(10, LOW); 
  }
}
