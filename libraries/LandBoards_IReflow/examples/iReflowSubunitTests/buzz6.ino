/*
  Buzzer and LED test
 */

int loopCount;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize output.
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
