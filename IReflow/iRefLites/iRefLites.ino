/* iRefLites - cycle through the LEDs on the IReflow board.
 */

#define SW5WAY A0
#define SSR 4
#define GRN_LITE 5   // pwmable
#define RED_LITE 6   // pwmable
#define BUZZ 10      // pwmable

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(SSR, OUTPUT);
  pinMode(RED_LITE, OUTPUT);
  pinMode(GRN_LITE, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  digitalWrite(SSR, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(BUZZ, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(RED_LITE, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(GRN_LITE, LOW);    // turn the LED off by making the voltage LOW
}

void loop() {
  digitalWrite(SSR, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(SSR, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(RED_LITE, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(RED_LITE, HIGH);  // turn the LED off by making the voltage LOW
  digitalWrite(GRN_LITE, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(GRN_LITE, HIGH);  // turn the LED off by making the voltage LOW
  //  digitalWrite(BUZZ, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(BUZZ, LOW);  // turn the LED off by making the voltage LOW
}

