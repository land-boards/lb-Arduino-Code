/*
  BlinkenLights BLACK-PILL-HUB LEDs blink
*/


// the setup routine runs once when you press reset:
void setup() 
{
  pinMode(PC13, OUTPUT);
  pinMode(PC14, OUTPUT);
  pinMode(PC15, OUTPUT);
  pinMode(PA0, OUTPUT);
  pinMode(PA1, OUTPUT);
  pinMode(PA2, OUTPUT);
  pinMode(PA3, OUTPUT);
  pinMode(PA4, OUTPUT);
  pinMode(PA5, OUTPUT);
  pinMode(PA6, OUTPUT);
  pinMode(PA7, OUTPUT);
  pinMode(PB0, OUTPUT);
  pinMode(PB1, OUTPUT);
  pinMode(PB10, OUTPUT);
  
  pinMode(PB12, OUTPUT);
  pinMode(PB13, OUTPUT);
  pinMode(PB14, OUTPUT);
  pinMode(PB15, OUTPUT);
  pinMode(PA8, OUTPUT);
  pinMode(PA15, OUTPUT);
  pinMode(PB3, OUTPUT);
  pinMode(PB4, OUTPUT);
  pinMode(PB5, OUTPUT);
  pinMode(PB9, OUTPUT);
}


// the loop routine runs over and over again forever:
void loop() 
{
  int delayTime = 250;
  digitalWrite(PC13, 1);
  delay(delayTime);
  digitalWrite(PC13, 0);
  digitalWrite(PC14, 1);
  delay(delayTime);
  digitalWrite(PC14, 0);
  digitalWrite(PC15, 1);
  delay(delayTime);
  digitalWrite(PC15, 0);
  digitalWrite(PA0, 1);
  delay(delayTime);
  digitalWrite(PA0, 0);
  digitalWrite(PA1, 1);
  delay(delayTime);
  digitalWrite(PA1, 0);
  digitalWrite(PA2, 1);
  delay(delayTime);
  digitalWrite(PA2, 0);
  digitalWrite(PA3, 1);
  delay(delayTime);
  digitalWrite(PA3, 0);
  digitalWrite(PA4, 1);
  delay(delayTime);
  digitalWrite(PA4, 0);
  digitalWrite(PA5, 1);
  delay(delayTime);
  digitalWrite(PA5, 0);
  digitalWrite(PA6, 1);
  delay(delayTime);
  digitalWrite(PA6, 0);
  digitalWrite(PA7, 1);
  delay(delayTime);
  digitalWrite(PA7, 0);
  digitalWrite(PB0, 1);
  delay(delayTime);
  digitalWrite(PB0, 0);
  digitalWrite(PB1, 1);
  delay(delayTime);
  digitalWrite(PB1, 0);
  digitalWrite(PB10, 1);
  delay(delayTime);
  digitalWrite(PB10, 0);
  
  digitalWrite(PB12, 1);
  delay(delayTime);
  digitalWrite(PB12, 0);
  digitalWrite(PB13, 1);
  delay(delayTime);
  digitalWrite(PB13, 0);
  digitalWrite(PB14, 1);
  delay(delayTime);
  digitalWrite(PB14, 0);
  digitalWrite(PB15, 1);
  delay(delayTime);
  digitalWrite(PB15, 0);
  digitalWrite(PA8, 1);
  delay(delayTime);
  digitalWrite(PA8, 0);
  digitalWrite(PA15, 1);
  delay(delayTime);
  digitalWrite(PA15, 0);
  digitalWrite(PB3, 1);
  delay(delayTime);
  digitalWrite(PB3, 0);
  digitalWrite(PB4, 1);
  delay(delayTime);
  digitalWrite(PB4, 0);
  digitalWrite(PB5, 1);
  delay(delayTime);
  digitalWrite(PB5, 0);
  digitalWrite(PB9, 1);
  delay(delayTime);
  digitalWrite(PB9, 0);
}
