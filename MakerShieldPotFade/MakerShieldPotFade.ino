/*
 MakerShieldFade 
 This example reads the pot on the MakerShield
 and writes out value to LED.
*/

void setup()
{
  pinMode(9, OUTPUT);
} 

void loop()  
{ 
  analogWrite(9, map((analogRead(A0)),0,1023,0,255));
}
