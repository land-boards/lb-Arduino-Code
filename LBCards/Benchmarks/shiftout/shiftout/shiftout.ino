
#define SDAT 7
#define SCLK 8
#define CSN  9

unsigned char dat;

// the setup routine runs once when you press reset:
void setup() 
{
  // initialize the digital pin as an output.
  pinMode(SDAT, OUTPUT);     
  pinMode(SCLK, OUTPUT);
  pinMode(CSN, OUTPUT);
  digitalWrite(SDAT,HIGH);
  digitalWrite(SCLK,HIGH);
  digitalWrite(CSN,HIGH);
  dat = 0;
}

// the loop routine runs over and over again forever:
void loop() 
{
  digitalWrite(CSN,LOW);
  shiftOut(SDAT,SCLK,LSBFIRST,dat);
  digitalWrite(CSN,HIGH);
  dat++;
}

