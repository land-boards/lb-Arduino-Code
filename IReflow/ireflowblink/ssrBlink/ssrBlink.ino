/*
 */

#define SSR 4
#define SW5WAY A0
#define DS2 5
#define DS1 6
#define BUZZ 

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(SSR, OUTPUT);
  pinMode(DS1, OUTPUT);
  pinMode(DS2, OUTPUT);
  digitalWrite(SSR, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(DS2, LOW);    // turn the LED off by making the voltage LOW
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(SSR, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(SSR, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(DS2, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(DS2, HIGH);    // turn the LED off by making the voltage LOW
}
