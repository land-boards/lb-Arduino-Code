// TinyPS04 - Clock out
// 2 mS
// If wrong, need to download bootloader

#define txPin 2

void setup() 
{
  pinMode(txPin, OUTPUT);
}

void loop() 
{
  digitalWrite(txPin,HIGH);
  delay(2);
  digitalWrite(txPin,LOW);
  delay(2);
}
