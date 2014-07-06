/*
 OptoProbe
 Checks the input line for changes and lights one of two lights if the input changes.
*/

// Predefined pin numbers
int ledHi = 2;
int ledPulse = 4;
int optoIn = 3;

int lastRead;  // keep the last pin number

// Set up the LEDs as outputs and pull up the input line (useful when there is no opto card)
void setup() {                
  // initialize the digital pin as an output.
  pinMode(ledHi, OUTPUT);
  pinMode(ledPulse, OUTPUT);
  pinMode(optoIn, INPUT_PULLUP);
  lastRead = digitalRead(optoIn);   // prime the last read of the opto in
}

// loop repeatedly reads the opto line and compares it to the previous read
// if the line changed and went low, light the LOW LED for 250 mS
// if the line changed and went high, light the HIGH LED for 250 mS

void loop() 
{
  int readVal;
  readVal = digitalRead(optoIn);   // read the input line
  if (readVal != lastRead)         // check if the line changed
  {
    digitalWrite(ledHi,readVal);
    digitalWrite(ledPulse, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(250);                    // wait for a second
    digitalWrite(ledPulse, LOW);   // if the line went from high to low
    lastRead = readVal;
  }   
//  digitalWrite(ledHi, LOW);        // turn the LED off by making the voltage LOW
//  digitalWrite(ledLo, LOW);        // turn the LED off by making the voltage LOW
  delay(100);                      // wait for a 1/10 second
}

