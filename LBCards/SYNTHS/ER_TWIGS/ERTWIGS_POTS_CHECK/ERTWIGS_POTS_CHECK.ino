/*
  ERTWIGS_POTS_CHECK
  Read the Pots and digital outputs on the ER-TWIGS card.
  Prints the values that were read to the monitor.
*/

#define INTLB 1
#define EXTLB 2

uint8_t state = INTLB;

#define RANDOM_POT_1 A1
#define RANDOM_POT_2 A2
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

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(GATE_IN, INPUT_PULLUP);
  pinMode(LED2A, OUTPUT);
  pinMode(LED2B, OUTPUT);
  pinMode(OUT2B, OUTPUT);
  pinMode(NORM, OUTPUT);
  pinMode(OUT1B, OUTPUT);
  pinMode(LED1B, OUTPUT);
  pinMode(LED1A, OUTPUT);
  pinMode(OUT1A, OUTPUT);
  pinMode(OUT2A, OUTPUT);
}

void pulsePin(int thePin)
{
  digitalWrite(thePin, HIGH);
  delay(1);
  digitalWrite(thePin, LOW);
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

// the loop routine runs over and over again forever:
void loop()
{
  // read the inputs on analog pins 1,2
  int RV1val = analogRead(RANDOM_POT_1);
  int RV2val = analogRead(RANDOM_POT_2);
  // print out the value you read:
  Serial.print(RV1val);
  Serial.print(", ");
  Serial.println(RV2val);
  delay(10);        // delay in between reads for stability
  pulsePin(OUT1A);
  pulsePin(OUT1B);
  pulsePin(OUT2A);
  pulsePin(OUT2B);
  pulsePin(LED1A);
  pulsePin(LED1B);
  pulsePin(LED2A);
  pulsePin(LED2B);
  // One of the below 2 tests will fail
  // Loopback internal NORM to GATE
  if (state == INTLB)
  {
    digitalWrite(NORM, HIGH);
    delay(1);
    if (digitalRead(GATE_IN) != LOW)
    {
      Serial.println("NORM loopback error expected LOW");
      state = EXTLB;
      delay(1000);
    }
    digitalWrite(NORM, LOW);
    delay(1);
    if (digitalRead(GATE_IN) != HIGH)
    {
      Serial.println("NORM loopback expected HIGH");
      state = EXTLB;
      delay(1000);
    }
  }
  // External loopback
  if (state == EXTLB)
  {
    digitalWrite(OUT1A, HIGH);
    if (digitalRead(GATE_IN) != LOW)
    {
      Serial.println("OUT1 to GATE loopback error expected LOW");
      state = INTLB;
      delay(1000);
    }
    digitalWrite(OUT1A, LOW);
    if (digitalRead(GATE_IN) != HIGH)
    {
      Serial.println("OUT1 to GATE loopback error expected LOW");
      state = INTLB;
      delay(1000);
    }
  }
}
