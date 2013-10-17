/*
  GVSwATP
  Tests the LEDs on the ATP daughter card when it is mounted above a GVSDuino card.
  Bounce a light across the LEDs.
 */
 
// The LEDs follow
int progLED = 7;
int errLED = 8;
int hbLED = 9;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(progLED, OUTPUT);     
  pinMode(errLED, OUTPUT);     
  pinMode(hbLED, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(progLED, LOW);    // turn the progLED off by making the voltage LOW
  delay(500);               // wait for a second
  digitalWrite(progLED, HIGH);   // turn the progLED on (HIGH is the voltage level)
  digitalWrite(errLED, LOW);    // turn the progLED off by making the voltage LOW
  delay(500);               // wait for a second
  digitalWrite(errLED, HIGH);   // turn the progLED on (HIGH is the voltage level)
  digitalWrite(hbLED, LOW);    // turn the progLED off by making the voltage LOW
  delay(500);               // wait for a second
  digitalWrite(hbLED, HIGH);   // turn the progLED on (HIGH is the voltage level)
}

