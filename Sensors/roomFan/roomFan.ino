/*
  roomFan
 Reads an LDR on analog input pin 0.
 Reads a 1-wire temp sensor in pin X.
 */

#define DEBUG

#define RELAY_PIN 8
#define DARK_THR 500

enum FAN_VALS
{
  FAN_OFF,
  FAN_ON,
};

int fanState;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
#ifdef DEBUG
  Serial.begin(9600);
#endif
  pinMode(RELAY_PIN, OUTPUT);
  fanState = FAN_OFF;
  setFan(fanState);
}

void setFan(int fanVal)
{
  if (fanVal == FAN_OFF)
    digitalWrite(RELAY_PIN, HIGH);
  else
    digitalWrite(RELAY_PIN, LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
#ifdef DEBUG
  Serial.println(sensorValue);
#endif

  if ((fanState == FAN_OFF) && (sensorValue > DARK_THR+20))
  {
    fanState = FAN_ON;
#ifdef DEBUG
    Serial.println("Turning fan on");
#endif
    setFan(FAN_ON);
  }
  else if ((fanState == FAN_ON) && (sensorValue < DARK_THR-20))
  {
    fanState = FAN_OFF;
#ifdef DEBUG
    Serial.println("Turning fan off");
#endif
    setFan(FAN_OFF);
  }
  delay(2500);        // delay in between reads for stability
}

