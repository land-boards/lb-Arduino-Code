/*
  LED_Tesr_ActiveLOW8
  
 */

int DS1 = 6;
int DS2 = 7;
int DS3 = 8;
int DS4 = 9;
int DS5 = 10;
int DS6 = 11;
int DS7 = 12;
int DS8 = 13;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(DS1, OUTPUT);
  pinMode(DS2, OUTPUT);
  pinMode(DS3, OUTPUT);
  pinMode(DS4, OUTPUT);
  pinMode(DS5, OUTPUT);
  pinMode(DS6, OUTPUT);
  pinMode(DS7, OUTPUT);
  pinMode(DS8, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(DS1, LOW);   // turn the LED on (LOW is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(DS1, HIGH);    // turn the LED off by making the voltage HIGH
  digitalWrite(DS2, LOW);   // turn the LED on (LOW is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(DS2, HIGH);    // turn the LED off by making the voltage HIGH
  digitalWrite(DS3, LOW);   // turn the LED on (LOW is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(DS3, HIGH);    // turn the LED off by making the voltage HIGH
  digitalWrite(DS4, LOW);   // turn the LED on (LOW is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(DS4, HIGH);    // turn the LED off by making the voltage HIGH
  digitalWrite(DS5, LOW);   // turn the LED on (LOW is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(DS5, HIGH);    // turn the LED off by making the voltage HIGH
  digitalWrite(DS6, LOW);   // turn the LED on (LOW is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(DS6, HIGH);    // turn the LED off by making the voltage HIGH
  digitalWrite(DS7, LOW);   // turn the LED on (LOW is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(DS7, HIGH);    // turn the LED off by making the voltage HIGH
  digitalWrite(DS8, LOW);   // turn the LED on (LOWHIGHHIGHHIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(DS8, HIGH);    // turn the LED off by making the voltage HIGH
}

