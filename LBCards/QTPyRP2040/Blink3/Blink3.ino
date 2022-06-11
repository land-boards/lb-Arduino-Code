/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

// Low to illuminate LED
const int redLEDPin =  17;
const int greenLEDPin =  16;
const int blueLEDPin =  25;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize LEDs digital pins as outputs.
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  // Trun off LEDs
  digitalWrite(redLEDPin, HIGH);
  digitalWrite(greenLEDPin, HIGH);
  digitalWrite(blueLEDPin, HIGH);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(redLEDPin, LOW);     // turn the red LED on
  delay(1000);                      // wait for a second
  digitalWrite(redLEDPin, HIGH);    // turn the red LED off
  digitalWrite(greenLEDPin, LOW);   // turn the green LED on
  delay(1000);                      // wait for a second
  digitalWrite(greenLEDPin, HIGH);  // turn the green LED off
  digitalWrite(blueLEDPin, LOW);    // turn the blue LED on
  delay(1000);                      // wait for a second
  digitalWrite(blueLEDPin, HIGH);   // turn the blue LED off
}
