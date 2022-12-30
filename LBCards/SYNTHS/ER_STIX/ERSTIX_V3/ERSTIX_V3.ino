/*
  ERSTIX_V3 GATE "Random" Generator.
  Similar in concept to Mutable Instrumentd Branches.
  J1 is GATE in.
  J2 is p() OUT1A/N outputs
  RV1 coin toss OUT 1.
    CCW = Always on OUT1A.
    CW = Always on OUT1B.
    Middle = 50% odds OUT1A or OUT1B.
  RV2 coin toss OUT 2.
    CCW = Always on OUT2A.
    CW = Always on OUT2B.
    Middle = 50% odds OUT2A or OUT2B.
  RV3 = Dependent/Independent Select
    7-12 o'clock = OUT1 and OUT2 are independent
    12-5 o'clock = OUT1 and OUT2 are dependent
  RV4 = Mode OUT2
    7-9 o'clock  = Normal Mode coin toss chooses one of OUTxA or OUTxB
    9-12 o'clock = Coin toss OUTxA, OUTxB individually
    12-3 o'clock = Ping pong or Sequential
    3-5 o'clock = Always drive OUTxA and OUTxB
*/

#define INTLB 1
#define EXTLB 2

//uint8_t state = INTLB;

#define RANDOM_POT_1 A1
#define RANDOM_POT_2 A2
#define MODE1 A0
#define MODE2 A3
#define GATE_IN 3
#define LED2A 4
#define LED2B 5
#define NORM 7
#define LED1B 9
#define LED1A 10
#define OUT1A 11
#define OUT1B 8
#define OUT2A 12
#define OUT2B 6

#define SET_OUT1A PORTB = PORTB | 0x08
#define SET_OUT1B PORTB = PORTB | 0X01
#define SET_OUT2A PORTB = PORTB | 0X10
#define SET_OUT2B PORTD = PORTD | 0X40

// Comment out one of the two next lines for Serial debug messages
//#define DEBUG_SERIAL
#undef DEBUG_SERIAL

uint8_t ping1, ping2, seqCount;

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
  ping1 = 0;
  ping2 = 0;
  seqCount = 0;
}

#define GATE_PIN_BIT 0x08

#define DEADBAND 10     // POT deadband to eliminate noise at end of pots

// Read the Mode pots
// Allows pots to be used as a mode select
// Returns mode
uint8_t getMode()
{
  uint16_t mode1, mode2, mode;
  mode1 = analogRead(MODE1);
  mode2 = analogRead(MODE2);
  mode1 >>= 7;
  mode1 &= 0x04;
  mode2 >>= 8;
  mode2 &= 0x03;
  mode = mode1 | mode2;
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
  RVval = constrain(RVval, DEADBAND, 1023 - DEADBAND);
  val = map(RVval, DEADBAND, 1023 - DEADBAND, 0, 999);
  randomNum = random(1000);
  if (val <= randomNum)
    prob = true;
  else
    prob = false;
  return (prob);
}

// the loop routine runs over and over again forever:
void loop()
{
  uint16_t mode;
  bool p1 = false;
  bool p2 = false;
  bool p3 = false;
  bool p4 = false;
  uint8_t randomChannel;

  // Determine the mode of operation
  mode = getMode();
  // Calculate p1, p2
  if (mode == 0)
  {
    p1 = calculateProbability(RANDOM_POT_1);
    p3 = calculateProbability(RANDOM_POT_2);
  }
  else if (mode == 1)
  {
    p1 = calculateProbability(RANDOM_POT_1);
    p2 = calculateProbability(RANDOM_POT_1);
    p3 = calculateProbability(RANDOM_POT_2);
    p4 = calculateProbability(RANDOM_POT_2);
  }
  else if (mode == 2)
  {
    p1 = calculateProbability(RANDOM_POT_1);
    p3 = calculateProbability(RANDOM_POT_2);
  }
  else if (mode == 3)
  {
    p1 = calculateProbability(RANDOM_POT_1);
    p3 = calculateProbability(RANDOM_POT_2);
  }
  else if (mode == 4)
  {
    p1 = calculateProbability(RANDOM_POT_1);
    randomChannel = random(4);
  }
  else if (mode == 5)
  {
    p1 = calculateProbability(RANDOM_POT_1);
    p3 = calculateProbability(RANDOM_POT_2);
  }
  else if (mode == 6)
  {
    p1 = calculateProbability(RANDOM_POT_1);
    p3 = calculateProbability(RANDOM_POT_2);
  }
  // optionally print out the value you read
#ifdef DEBUG_SERIAL
  Serial.print("mode=");
  Serial.print(mode);
  Serial.print(", p(1)=");
  Serial.print(p1);
  Serial.print(", p(2)=");
  Serial.print(p2);
  Serial.print(", p(3)=");
  Serial.print(p3);
  Serial.print(", p(4)=");
  Serial.println(p4);
#endif
  //  waitForGATEEdge();
  // Wait for GATE edge
  while ((PIND & GATE_PIN_BIT) == 0x00);    // Directly read port pin for low latency
  while ((PIND & GATE_PIN_BIT) == 0x08);
  if (mode == 0)
  {
    if (p1)
      SET_OUT1A;
    else
      SET_OUT1B;
    if (p3)
      SET_OUT2A;
    else
      SET_OUT2B;
  }
  else if (mode == 1)
  {
    if (p1)
      SET_OUT1A;
    if (p2)
      SET_OUT1B;
    if (p3)
      SET_OUT2A;
    if (p4)
      SET_OUT2B;
  }
  else if (mode == 2)
  {
    if (p1)
    {
      if (ping1 == 0)
      {
        SET_OUT1A;
        ping1 = 1;
      }
      else if (ping1 == 1)
      {
        SET_OUT1B;
        ping1 = 0;
      }
    }
    if (p3)
    {
      if (ping2 == 0)
      {
        SET_OUT2A;
        ping2 = 1;
      }
      else if (ping2 == 1)
      {
        SET_OUT2B;
        ping2 = 0;
      }
    }
  }
  else if (mode == 3)
  {
    if (p1)
    {
      SET_OUT1A;
      SET_OUT1B;
    }
    if (p3)
    {
      SET_OUT2A;
      SET_OUT2B;
    }
  }
  else if (mode == 4)
  {
    if (p1)
    {
      if (randomChannel == 0)
        SET_OUT1A;
      else if (randomChannel == 1)
        SET_OUT1B;
      else if (randomChannel == 2)
        SET_OUT2A;
      else if (randomChannel == 3)
        SET_OUT2B;
    }
  }
  else if (mode == 5)
  {
    if (p1)
    {
      if (p3)
      {
        SET_OUT1A;
        SET_OUT1B;
      }
      else
      {
        SET_OUT2A;
        SET_OUT2B;
      }
    }
  }
  else if (mode == 6)
  {
    if (seqCount < 2)
    {
      if (p1)
      {
        if (seqCount == 0)
        {
          SET_OUT1A;
        }
        else if (seqCount == 1)
        {
          SET_OUT1B;
        }
        seqCount++;
      }
    }
    else
    {
      if (p3)
      {
        if (seqCount == 2)
        {
          SET_OUT2A;
        }
        else if (seqCount == 3)
        {
          SET_OUT2B;
        }
        seqCount++;
        if (seqCount >= 4)
          seqCount = 0;
      }
    }
  }
  else if (mode == 7)
  {
    SET_OUT1A;
    SET_OUT1B;
    SET_OUT2A;
    SET_OUT2B;
  }
  // Handle LEDs after setting GATEs for lowest latency
  if (p1)
  {
    digitalWrite(LED1A, HIGH);
  }
  else
  {
    digitalWrite(LED1B, HIGH);
  }
  if (p2)
  {
    digitalWrite(LED2A, HIGH);
  }
  else
  {
    digitalWrite(LED2B, HIGH);
  }
  // Leave GATES on until input gate is removed
  while ((PIND & GATE_PIN_BIT) == 0x00);
  // Turn off OUT1, OUT2 GATEs
  PORTB = PORTB & 0xe6;
  PORTD = PORTD & 0xbf;
  // Turn off LEDs
  digitalWrite(LED1A, LOW);
  digitalWrite(LED1B, LOW);
  digitalWrite(LED2A, LOW);
  digitalWrite(LED2B, LOW);
}
