
///////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////

// include the library code:
#include "Wire.h"
#include "LiquidCrystal.h"

// Connect via i2c, default address #0 (A0-A2 not jumpered)
LiquidCrystal lcd(0);

///////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////

void setup() {
  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("* Temp Monitor *");
}

///////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////

void loop() 
{
  readTMP36(0);
  delay(500);
}

///////////////////////////////////////////////////////////////////////
// TMP36 sensor is analog
///////////////////////////////////////////////////////////////////////

void readTMP36(int channelNumber)
{
  float celsius, fahrenheit;
    int sensorValue;
  switch (channelNumber)
  {
    case 0:
      sensorValue = analogRead(A0);
      break;
    case 1:
      sensorValue = analogRead(A1);
      break;
    case 2:
      sensorValue = analogRead(A2);
      break;
    case 3:
      sensorValue = analogRead(A3);
      break;
    case 4:
      sensorValue = analogRead(A4);
      break;
    case 5:
      sensorValue = analogRead(A5);
      break;
  }
  float sensorFloat;
  sensorFloat = sensorValue*5.0/1024.0;
  sensorFloat = sensorFloat - 0.5;
  sensorFloat = sensorFloat * 100.0;
  fahrenheit = sensorFloat * 1.8 + 32.0;
  lcd.setCursor(0,1);
  lcd.print("TMP36-");
  lcd.print(channelNumber, DEC);
  lcd.print(" = ");
  lcd.print(fahrenheit, DEC);
//  lcd.println(" deg F");
}

