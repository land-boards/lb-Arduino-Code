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
  pinMode(DS2, OUTPUT);
  pinMode(DS3, OUTPUT);
  pinMode(DS4, OUTPUT);
  pinMode(DS5, OUTPUT);
  pinMode(DS6, OUTPUT);
  pinMode(DS7, OUTPUT);
  pinMode(DS8, OUTPUT);
  pinMode(DS9, OUTPUT);
  pinMode(DS10, OUTPUT);
  pinMode(DS11, OUTPUT);
  pinMode(DS12, OUTPUT);
  pinMode(DS13, OUTPUT);
  pinMode(DS14, OUTPUT);
  pinMode(DS15, OUTPUT);
  pinMode(DS16, OUTPUT);
}

void pulseChannel(unsigned char chNum)
{
  digitalWrite(chNum, HIGH);
  delay(delayTime);               // wait for a second
  digitalWrite(chNum, LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  pulseChannel(DS1);
  pulseChannel(DS2);
  pulseChannel(DS3);
  pulseChannel(DS4);
  pulseChannel(DS5);
  pulseChannel(DS6);
  pulseChannel(DS7);
  pulseChannel(DS8);
  pulseChannel(DS9);
  pulseChannel(DS10);
  pulseChannel(DS11);
  pulseChannel(DS12);
  pulseChannel(DS13);
  pulseChannel(DS14);
  pulseChannel(DS15);
  pulseChannel(DS16);
}

