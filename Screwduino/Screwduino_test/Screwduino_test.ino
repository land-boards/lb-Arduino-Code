/*
  LED_Tesr_ActiveLOW8
  
 */

unsigned char DS1 = 2;
unsigned char DS2 = 3;
unsigned char DS3 = 4;
unsigned char DS4 = 5;
unsigned char DS5 = 6;
unsigned char DS6 = 7;
unsigned char DS7 = 8;
unsigned char DS8 = 9;
unsigned char DS9 = 10;
unsigned char DS10 = 11;
unsigned char DS11 = 12;
unsigned char DS12 = 13;
unsigned char DS13 = 14;
unsigned char DS14 = 15;
unsigned char DS15 = 16;
unsigned char DS16 = 17;
unsigned char DS17 = 18;
unsigned char DS18 = 19;
int delayTime = 125;


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
  pinMode(DS17, OUTPUT);
  pinMode(DS18, OUTPUT);
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
  pulseChannel(DS17);
  pulseChannel(DS18);
}

