////////////////////////////////////////////////////////////////////////////
// LED-18
// 
// This code works with the LED-18 board.
// The wiki page for the board is at:
//   http://land-boards.com/blwiki/index.php?title=LED-18
//
// This code reads an external variable resistor, scales the resistor 
// to 0-100 and writes out the value of the resistor to a PWM pin.
// This code runs on an ATTiny85.
////////////////////////////////////////////////////////////////////////////

int led = 0;           // LED pin
int potPin = 1;        // Pot pin

////////////////////////////////////////////////////////////////////////////
// setup() - Configures the LED line to be an output
//  setup is run once at the start.
////////////////////////////////////////////////////////////////////////////

void setup()  
{
  pinMode(led, OUTPUT);
} 

////////////////////////////////////////////////////////////////////////////
// loop() - reads the pot and returns 10-bits (0-1023). 
// It then scales that from 10-bits to 8-bits (0-255).
// The value is then fed to the PWM output which goes to the LED drivers.
////////////////////////////////////////////////////////////////////////////

void loop()  
{
  int brightness = 0;    // Variable which contains how bright the LED is
  brightness = analogRead(potPin);  // read the pot
  analogWrite(led, brightness>>2);  // scale and write out to LED driver pin
  // wait for 30 milliseconds to see the dimming effect    
  delay(30);                            
}

