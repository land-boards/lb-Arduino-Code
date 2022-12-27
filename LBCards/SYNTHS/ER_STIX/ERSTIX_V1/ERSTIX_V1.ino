/*
  ERSTIX_V1
  Very basic Euclidian Gate Generator.
  RV1 controls (OUT 1).
    CCW = Always on OUT1A.
    CW = Always on OUT1B.
    Middle = 50% odds.
  RV2 controle (OUT 2).
    CCW = Always on OUT1A.
    CW = Always on OUT1B.
    Middle = 50% odds.
*/

#define INTLB 1
#define EXTLB 2

uint8_t state = INTLB;

#define RANDOM_POT_1 A1
#define RANDOM_POT_2 A2
//#define MODE1 A0
//#define MODE2 A3
#define GATE_IN 3
#define LED2A 4
#define LED2B 5
#define OUT2B 6
#define NORM 7
#define OUT1B 8
#define LED1B 9
#define LED1A 10
#define OUT1A 11
#define OUT2A 12

// Comment out one of the two next lines for Serial debug messages
//#define DEBUG_SERIAL
#undef DEBUG_SERIAL

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
#ifdef DEBUG_SERIAL
  Serial.begin(9600);   // for debug
#endif
  pinMode(GATE_IN, INPUT_PULLUP);
  pinMode(LED2A, OUTPUT);
  pinMode(LED2B, OUTPUT);
  pinMode(OUT2B, OUTPUT);
  pinMode(NORM, OUTPUT);      // Not used in V1
  pinMode(OUT1B, OUTPUT);
  pinMode(LED1B, OUTPUT);
  pinMode(LED1A, OUTPUT);
  pinMode(OUT1A, OUTPUT);
  pinMode(OUT2A, OUTPUT);
#ifdef DEBUG_SERIAL
  Serial.println("Finished setup");
#endif

}

//#define LED1A 10
//#define LED1B 9
//#define LED2A 4
//#define LED2B 5
//#define NORM 7
//#define OUT1A 11
//#define OUT1B 8
//#define OUT2A 12
//#define OUT2B 6

void waitForGATEEdge()
{
#ifdef DEBUG_SERIAL
  Serial.println("Wait for GATE rising edge");
#endif
  while (digitalRead(GATE_IN) == HIGH);
  while (digitalRead(GATE_IN) == LOW);
}

#define DEADBAND 10

// the loop routine runs over and over again forever:
void loop()
{
  uint16_t random1, random2;
  uint16_t val1, val2;
  bool p1, p2;
  // Calculate p1
  int RV1val = analogRead(RANDOM_POT_1);
  if (RV1val < DEADBAND)
    RV1val = DEADBAND;
  else if (RV1val > 1023 - DEADBAND)
    RV1val = 1023 - DEADBAND;
  val1 = map(RV1val, DEADBAND, 1023 - DEADBAND, 0, 99);
  random1 = random(100);
  if (val1 <= random1)
    p1 = true;
  else
    p1 = false;
  // Calculate p2
  int RV2val = analogRead(RANDOM_POT_2);
  if (RV2val < DEADBAND)
    RV2val = DEADBAND;
  else if (RV2val > 1023 - DEADBAND)
    RV2val = 1023 - DEADBAND;
  val2 = map(RV2val, DEADBAND, 1023 - DEADBAND, 0, 99);
  random2 = random(100);
  if (val2 <= random2)
    p2 = true;
  else
    p2 = false;
  // print out the value you read:
#ifdef DEBUG_SERIAL
  Serial.print(RV1val);
  Serial.print(", ");
  Serial.println(RV2val);
#endif
  waitForGATEEdge();
  if (p1)
  {
    digitalWrite(OUT1A,HIGH);
    digitalWrite(OUT1B,LOW);
  }
  else
  {
    digitalWrite(OUT1A,LOW);
    digitalWrite(OUT1B,HIGH);
  }
  if (p2)
  {
    digitalWrite(OUT2A,HIGH);
    digitalWrite(OUT2B,LOW);
  }
  else
  {
    digitalWrite(OUT2A,LOW);
    digitalWrite(OUT2B,HIGH);
  }
  while (digitalRead(GATE_IN) == HIGH);
  digitalWrite(OUT1A,LOW);
  digitalWrite(OUT1B,LOW);
  digitalWrite(OUT2A,LOW);
  digitalWrite(OUT2B,LOW);

}
