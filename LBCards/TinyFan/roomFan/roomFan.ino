/////////////////////////////////////////////////////////////////////
// roomFan - Control an inlet fan.
// Hardware Inputs:
//   Analog 1 - LDR.
//   Digital 6 - 1-wire temp sensor.
// Hardware Outputs:
//   Digital 2 - Relay output.
/////////////////////////////////////////////////////////////////////

#include <TimeLib.h>

/////////////////////////////////////////////////////////////////////
// defines
/////////////////////////////////////////////////////////////////////

#define DEBUG 1
//#undef DEBUG

#define RELAY_PIN 2
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
  // initialize serial communication at 9600 bits per second:
#ifdef DEBUG
  Serial.begin(9600);
#endif
  pinMode(RELAY_PIN, OUTPUT);
  fanState = FAN_OFF;
  setFan(fanState);
  useLDR = DARK_THR;
  todaysLDRHigh = analogRead(A1);
  todaysLDRLow = todaysLDRHigh;
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
  int sensorValue = analogRead(A1);
  // print out the value you read:
#ifdef DEBUG
  Serial.print("LDR ");
  Serial.println(sensorValue);
#endif

  if (sensorValue > todaysLDRHigh)
  {
    todaysLDRHigh = sensorValue;
  }
  else if (sensorValue < todaysLDRLow)
  {
    todaysLDRLow = sensorValue;
  }

  if ((fanState == FAN_OFF) && (sensorValue > useLDR + DARK_HYST) && (fahrenheit > LOW_TEMP))
  {
    fanState = FAN_ON;
#ifdef DEBUG
    Serial.println("Turning fan on");
#endif
    setFan(FAN_ON);
  }
  else if (((fanState == FAN_ON) && (sensorValue < useLDR - DARK_HYST)) || (fahrenheit < LOW_TEMP))
  {
    fanState = FAN_OFF;
#ifdef DEBUG
    Serial.println("Turning fan off");
#endif
    setFan(FAN_OFF);
  }
  delay(1500);        // delay in between reads for stability
  read1Wire();
#ifdef DEBUG
  Serial.print("Temp ");
  Serial.println(fahrenheit);
  digitalClockDisplay();
#endif
  if (day() > 1)
  {
#ifdef DEBUG
    Serial.println("crossed 1 day");
    Serial.println("reset time");
    Serial.print("todaysLDRHigh = ");
    Serial.println(todaysLDRHigh);
    Serial.print("todaysLDRLow = ");
    Serial.println(todaysLDRLow);
    Serial.print("useLDR = ");
    Serial.println(useLDR);
#endif
    setTime(0);
    yesterdaysLDRHigh = todaysLDRHigh;
    yesterdaysLDRLow = todaysLDRLow;
    todaysLDRLow = sensorValue;
    todaysLDRHigh = sensorValue;
    useLDR = (yesterdaysLDRHigh + yesterdaysLDRLow) / 2;
  }
}

/////////////////////////////////////////////////////////////////////
// digitalClockDisplay()
/////////////////////////////////////////////////////////////////////

void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year());
  Serial.println();
}

/////////////////////////////////////////////////////////////////////
// printDigits(int digits)
/////////////////////////////////////////////////////////////////////

void printDigits(int digits)
{
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}


