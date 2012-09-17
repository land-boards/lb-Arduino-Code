/////////////////////////////////////////////////////////////////////
// tinyFan - Control an inlet fan using an ATtiny85.
// Hardware Inputs:
//   "Pin" 1 - LDR.
//   "Pin" 4 - 1-wire temp sensor.
// Hardware Outputs:
//   "Pin" 3 - Relay output.
/////////////////////////////////////////////////////////////////////

#include <Time.h>

/////////////////////////////////////////////////////////////////////
// defines
/////////////////////////////////////////////////////////////////////

#define RELAY_PIN 3
#define LDR_PIN 1
#define DARK_THR 500
#define LOW_TEMP 62.0
#define DARK_HYST 20

/////////////////////////////////////////////////////////////////////
// enums
/////////////////////////////////////////////////////////////////////

enum FAN_VALS
{
  FAN_OFF,
  FAN_ON,
};

/////////////////////////////////////////////////////////////////////
// variables
/////////////////////////////////////////////////////////////////////

extern float fahrenheit;
float tempHysteresis;

int fanState;
int yesterdaysLDRHigh;
int yesterdaysLDRLow;
int todaysLDRHigh;
int todaysLDRLow;
int useLDR;

/////////////////////////////////////////////////////////////////////
// setup()
/////////////////////////////////////////////////////////////////////

// the setup routine runs once when you press reset:
void setup() 
{
  pinMode(RELAY_PIN, OUTPUT);
  fanState = FAN_OFF;
  setFan(fanState);
  useLDR = DARK_THR;
  todaysLDRHigh = analogRead(LDR_PIN);
  todaysLDRLow = todaysLDRHigh;
  tempHysteresis = 1.0;
}

/////////////////////////////////////////////////////////////////////
// setFan()
/////////////////////////////////////////////////////////////////////

void setFan(int fanVal)
{
  if (fanVal == FAN_OFF)
    digitalWrite(RELAY_PIN, HIGH);
  else
    digitalWrite(RELAY_PIN, LOW);
}

/////////////////////////////////////////////////////////////////////
// loop()
/////////////////////////////////////////////////////////////////////

void loop() 
{
  // read the input on analog pin 1
  int sensorValue = analogRead(LDR_PIN);
  if (sensorValue > todaysLDRHigh)
    todaysLDRHigh = sensorValue;
  else if (sensorValue < todaysLDRLow)
    todaysLDRLow = sensorValue;

  if ((fanState == FAN_OFF) && (sensorValue > useLDR + DARK_HYST) && (fahrenheit > (LOW_TEMP+tempHysteresis)))
  {
    fanState = FAN_ON;
    setFan(FAN_ON);
  }
  else if (((fanState == FAN_ON) && (sensorValue < useLDR - DARK_HYST)) || (fahrenheit < (LOW_TEMP+tempHysteresis)))
  {
    fanState = FAN_OFF;
    setFan(FAN_OFF);
  }
  delay(1500);        // delay in between reads for stability
  read1Wire();
  if (day() > 1)
  {
    setTime(0);
    yesterdaysLDRHigh = todaysLDRHigh;
    yesterdaysLDRLow = todaysLDRLow;
    todaysLDRLow = sensorValue;
    todaysLDRHigh = sensorValue;
    useLDR = (yesterdaysLDRHigh + yesterdaysLDRLow) / 2;
  }
}

