/*
  LED_Tesr_ActiveLOW8
  
 */

unsigned char DS1 = 6;
unsigned char DS2 = 7;
unsigned char DS3 = 8;
unsigned char DS4 = 9;
unsigned char DS5 = 10;
unsigned char DS6 = 11;
unsigned char DS7 = 12;
unsigned char DS8 = 13;
unsigned char DS9 = 3;
unsigned char DS10 = 2;
unsigned char DS11 = 14;
unsigned char DS12 = 15;
unsigned char DS13 = 16;
unsigned char DS14 = 17;
unsigned char DS15 = 18;
unsigned char DS16 = 19;
int delayTime = 175;


// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(DS1, OUTPUT);
  digitalWrite(DS1, HIGH);
  pinMode(DS2, OUTPUT);
  digitalWrite(DS2, HIGH);
  pinMode(DS3, OUTPUT);
  digitalWrite(DS3, HIGH);
  pinMode(DS4, OUTPUT);
  digitalWrite(DS4, HIGH);
  pinMode(DS5, OUTPUT);
  digitalWrite(DS5, HIGH);
  pinMode(DS6, OUTPUT);
  digitalWrite(DS6, HIGH);
  pinMode(DS7, OUTPUT);
  digitalWrite(DS7, HIGH);
  pinMode(DS8, OUTPUT);
  digitalWrite(DS8, HIGH);
  pinMode(DS9, OUTPUT);
  pinMode(DS10, OUTPUT);
  pinMode(DS11, OUTPUT);
  pinMode(DS12, OUTPUT);
  pinMode(DS13, OUTPUT);
  pinMode(DS14, OUTPUT);
  pinMode(DS15, OUTPUT);
  pinMode(DS16, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(DS1, LOW);   // turn the LED on (LOW is the voltage level)
  delay(delayTime);               // wait for a second
  digitalWrite(DS1, HIGH);    // turn the LED off by making the voltage HIGH
  digitalWrite(DS2, LOW);   // turn the LED on (LOW is the voltage level)
  delay(delayTime);               // wait for a second
  digitalWrite(DS2, HIGH);    // turn the LED off by making the voltage HIGH
  digitalWrite(DS3, LOW);   // turn the LED on (LOW is the voltage level)
  delay(delayTime);               // wait for a second
  digitalWrite(DS3, HIGH);    // turn the LED off by making the voltage HIGH
  digitalWrite(DS4, LOW);   // turn the LED on (LOW is the voltage level)
  delay(delayTime);               // wait for a second
  digitalWrite(DS4, HIGH);    // turn the LED off by making the voltage HIGH
  digitalWrite(DS5, LOW);   // turn the LED on (LOW is the voltage level)
  delay(delayTime);               // wait for a second
  digitalWrite(DS5, HIGH);    // turn the LED off by making the voltage HIGH
  digitalWrite(DS6, LOW);   // turn the LED on (LOW is the voltage level)
  delay(delayTime);               // wait for a second
  digitalWrite(DS6, HIGH);    // turn the LED off by making the voltage HIGH
  digitalWrite(DS7, LOW);   // turn the LED on (LOW is the voltage level)
  delay(delayTime);               // wait for a second
  digitalWrite(DS7, HIGH);    // turn the LED off by making the voltage HIGH
  digitalWrite(DS8, LOW);   // turn the LED on (LOWHIGHHIGHHIGH is the voltage level)
  delay(delayTime);               // wait for a second
  digitalWrite(DS8, HIGH);    // turn the LED off by making the voltage HIGH

  digitalWrite(DS9, HIGH);   // turn the LED on (LOWHIGHHIGHHIGH is the voltage level)
  delay(delayTime);               // wait for a second
  digitalWrite(DS9, LOW);    // turn the LED off by making the voltage HIGH
  digitalWrite(DS10, HIGH);   // turn the LED on (LOWHIGHHIGHHIGH is the voltage level)
  delay(delayTime);               // wait for a second
  digitalWrite(DS10, LOW);    // turn the LED off by making the voltage HIGH

  digitalWrite(DS11, HIGH);   // turn the LED on (LOWHIGHHIGHHIGH is the voltage level)
  delay(delayTime);               // wait for a second
  digitalWrite(DS11, LOW);    // turn the LED off by making the voltage HIGH
  digitalWrite(DS12, HIGH);   // turn the LED on (LOWHIGHHIGHHIGH is the voltage level)
  delay(delayTime);               // wait for a second
  digitalWrite(DS12, LOW);    // turn the LED off by making the voltage HIGH
  digitalWrite(DS13, HIGH);   // turn the LED on (LOWHIGHHIGHHIGH is the voltage level)
  delay(delayTime);               // wait for a second
  digitalWrite(DS13, LOW);    // turn the LED off by making the voltage HIGH
  digitalWrite(DS14, HIGH);   // turn the LED on (LOWHIGHHIGHHIGH is the voltage level)
  delay(delayTime);               // wait for a second
  digitalWrite(DS14, LOW);    // turn the LED off by making the voltage HIGH
  digitalWrite(DS15, HIGH);   // turn the LED on (LOWHIGHHIGHHIGH is the voltage level)
  delay(delayTime);               // wait for a second
  digitalWrite(DS15, LOW);    // turn the LED off by making the voltage HIGH
  digitalWrite(DS16, HIGH);   // turn the LED on (LOWHIGHHIGHHIGH is the voltage level)
  delay(delayTime);               // wait for a second
  digitalWrite(DS16, LOW);    // turn the LED off by making the voltage HIGH
}

