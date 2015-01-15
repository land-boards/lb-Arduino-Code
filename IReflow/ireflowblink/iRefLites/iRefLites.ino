/*
 */

#define SW5WAY A0
#define SSR 4
#define DS2 5  // pwmable
#define DS1 6  // pwmable
#define BUZZ 10  // pwmable

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(SSR, OUTPUT);
  pinMode(DS1, OUTPUT);
  pinMode(DS2, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  digitalWrite(SSR, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(BUZZ, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(DS1, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(DS2, LOW);    // turn the LED off by making the voltage LOW
}

void loop() {
  digitalWrite(SSR, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(SSR, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(DS1, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(DS1, HIGH);  // turn the LED off by making the voltage LOW
  digitalWrite(DS2, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(DS2, HIGH);  // turn the LED off by making the voltage LOW
  //  digitalWrite(BUZZ, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(BUZZ, LOW);  // turn the LED off by making the voltage LOW
}


