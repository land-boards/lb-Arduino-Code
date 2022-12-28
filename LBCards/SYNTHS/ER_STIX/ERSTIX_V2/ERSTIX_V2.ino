/*
  ERSTIX_VD & 0x08) == 0x08);Generator.
  Similar in concept to Mutable Instrumentd Branches.
  J1 is GATE in.
  J2 is p() OUT1A/N outputs 
  RV1 controls (OUT 1).
    CCW = Always on OUT1A.
    CW = Always on OUT1B.
    Middle = 50% odds.
  RV2 controle (OUT 2).
    CCW = Always on OUT1A.
    CW = Always on OUT1B.
    Middle = 50% odds.
  RV3 = Mode OUT1
    7-12 o'clock = Normal Mode drives only OUT1A or OUT1B
    12-5 o'clock = Drives both OUT1A and OUT1B
  RV4 = Mode OUT2
    7-12 o'clock = Normal Mode drives only OUT2A or OUT2B
    12-5 o'clock = Drive both OUT2A and OUT2B
*/

#define INTLB 1
#define EXTLB 2

uint8_t state = INTLB;

#define RANDOM_POT_1 A1
#define RANDOM_POT_2 A2
#define MODE1 A0
#define MODE2 A3
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

// Wait for GATE active edge
// GATE is active low
// GATE is on Pin 3 in D register 
void waitForGATEEdge()
{
#ifdef DEBUG_SERIAL
  Serial.println("Wait for GATE rising edge");
#endif
//  while (digitalRead(GATE_IN) == LOW);
//  while (digitalRead(GATE_IN) == HIGH);
  while ((PIND & 0x08) == 0x00);
  while ((PIND & 0x08) == 0x08);
#ifdef DEBUG_SERIAL
  Serial.println("Got GATE rising edge");
#endif
}

#define DEADBAND 10     // POT deadband to eliminate noise at end of pots

// Read the Mode pot(s)
// Allows a pot to be used as a mode select
// Returns mode
uint8_t getMode(uint8_t port)
{
  uint16_t mode = analogRead(port);
  mode >>= 9;
  mode &= 0x1;
#ifdef DEBUG_SERIAL
  Serial.print("getMode() - Mode = ");
  Serial.println(mode);
#endif
  return (mode);
}

// Calculate the probability based in RV1, RV2 Pots (or J2 input for OUT 1)
// Returns true or false
bool calculateProbability(uint8_t port)
{
  uint16_t val;
  uint16_t randomNum;
  bool prob;
  int RVval = analogRead(port);
  // adjust for end bands
  RVval = constrain(RVval,DEADBAND,1023-DEADBAND);
//  if (RVval < DEADBAND)
//    RVval = DEADBAND;
//  else if (RVval > 1023 - DEADBAND)
//    RVval = 1023 - DEADBAND;
  val = map(RVval, DEADBAND, 1023 - DEADBAND, 0, 99);
  randomNum = random(100);
  if (val <= randomNum)
    prob = true;
  else
    prob = false;
  return(prob);
}

// the loop routine runs over and over again forever:
void loop()
{
  uint16_t mode1, mode2;
  bool p1, p2;
  // Determine the mode of operation
  mode1 = getMode(MODE1);
  mode2 = getMode(MODE2);
  // Calculate p1, p2
  p1 = calculateProbability(RANDOM_POT_1);
  p2 = calculateProbability(RANDOM_POT_2);
  // optionally print out the value you read
#ifdef DEBUG_SERIAL
  Serial.print(p1);
  Serial.print(", ");
  Serial.println(p2);
#endif
  waitForGATEEdge();
  if (mode1 == 0)
  {
    if (p1)
    {
      digitalWrite(OUT1A, HIGH);
    }
    else
    {
      digitalWrite(OUT1B, HIGH);
    }
  }
  else if (mode1 == 1)
  {
    if (p1)
    {
      digitalWrite(OUT1A, HIGH);
      digitalWrite(OUT1B, HIGH);
    }
  }
  if (mode2 == 0)
  {
    if (p2)
    {
      digitalWrite(OUT2A, HIGH);
    }
    else
    {
      digitalWrite(OUT2B, HIGH);
    }
  }
  else if (mode2 == 1)
  {
    if (p2)
    {
      digitalWrite(OUT2A, HIGH);
      digitalWrite(OUT2B, HIGH);
    }
  }
  // Handle LEDs after setting GATEs for lowest latency
  if (p1)
  {
    digitalWrite(LED1A, HIGH);
    digitalWrite(LED1B, LOW);
  }
  else
  {
    digitalWrite(LED1A, LOW);
    digitalWrite(LED1B, HIGH);
  }
  if (p2)
  {
    digitalWrite(LED2A, HIGH);
    digitalWrite(LED2B, LOW);
  }
  else
  {
    digitalWrite(LED2A, LOW);
    digitalWrite(LED2B, HIGH);
  }
  // Leave GATES on until input gate is removed
  while (digitalRead(GATE_IN) == LOW);
  // Turn off GATEs
  digitalWrite(OUT1A, LOW);
  digitalWrite(OUT1B, LOW);
  digitalWrite(OUT2A, LOW);
  digitalWrite(OUT2B, LOW);
  // Turn off LEDs
  digitalWrite(LED1A, LOW);
  digitalWrite(LED1B, LOW);
  digitalWrite(LED2A, LOW);
  digitalWrite(LED2B, LOW);

}
