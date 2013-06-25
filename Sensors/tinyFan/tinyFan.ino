/////////////////////////////////////////////////////////////////////
// tinyFan - Control an inlet fan using an ATtiny85.
// Hardware
//  TinyDuino85 - http://dougspcbdesigns.pbworks.com/w/page/57711962/TinyDuino85
//  LDR - http://dougspcbdesigns.pbworks.com/w/page/55048594/LDRSensor
//  DS18B20 Temp Sensor - http://dougspcbdesigns.pbworks.com/w/page/55033825/DS18S20
// Inputs:
//   "Pin" 1 - LDR.
//   "Pin" 4 - 1-wire temp sensor.
// Outputs:
//   "Pin" 3 - Relay output.
/////////////////////////////////////////////////////////////////////

#include <Time.h>

/////////////////////////////////////////////////////////////////////
// defines
/////////////////////////////////////////////////////////////////////

#define RELAY_PIN 3
#define LDR_PIN 1
#define DARK_THR 500
#define LOW_TEMP 60.0
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

void setup() 
{
  pinMode(RELAY_PIN, OUTPUT);
  setTime(0);
  setFan(FAN_ON);
  delay(5000);        // delay in between reads for stability
  setFan(FAN_OFF);
  delay(1000);        // delay in between reads for stability
  useLDR = DARK_THR;
  todaysLDRHigh = analogRead(LDR_PIN);
  todaysLDRLow = todaysLDRHigh - DARK_HYST;
  tempHysteresis = 2.0;
  read1Wire();
  delay(1000);
  read1Wire();
  delay(1000);
}

/////////////////////////////////////////////////////////////////////
// setFan()
/////////////////////////////////////////////////////////////////////

void setFan(int fanVal)
{
  if (fanVal == FAN_OFF)
  {
    digitalWrite(RELAY_PIN, HIGH);
    fanState = FAN_OFF;
  }
  else
  {
    digitalWrite(RELAY_PIN, LOW);
    fanState = FAN_ON;
  }
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

  read1Wire();
  delay(1000);
  read1Wire();
  delay(1000);
  if ((fanState == FAN_OFF) && (sensorValue > useLDR + DARK_HYST) && (fahrenheit > (LOW_TEMP+tempHysteresis)))
  {
    setFan(FAN_ON);
  }
  else if (((fanState == FAN_ON) && (sensorValue < useLDR - DARK_HYST)) || (fahrenheit < (LOW_TEMP+tempHysteresis)))
  {
    setFan(FAN_OFF);
  }
  for (long i=0; i<15*60; i++)
	delay(1000);        // delay in between reads for stability
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

