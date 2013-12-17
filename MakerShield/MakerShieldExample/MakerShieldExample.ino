/*
 MakerShieldLibrary
 
 This provides the functions to access the hardware on the MakerShield. 
 */

#define POT_PORT A0
#define LED_PORT 

void setup()  { 
  // declare pin 9 to be an output:
  pinMode(9, OUTPUT);
} 

void loop()  
{ 
  // set the brightness of pin 9:
  analogWrite(9, map((analogRead(A0)),0,1023,0,255));
}
