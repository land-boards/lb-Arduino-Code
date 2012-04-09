/*
 * Displays text sent over the serial port (e.g. from the Serial Monitor) on
 * an attached LCD.
 */

//////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////

// include the library code:
#include "Wire.h"
#include "LiquidCrystal.h"
#include <IRremote.h>

//////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////

enum IR_VALUES
{
  NOKEY = 0,
  CHMINUS,
  CH,
  CHPLUS,
  LEFT,
  RIGHT,
  PAUSE,
  MINUS,
  PLUS,
  EQ,
  ZEROKEY,
  V100PLUS,
  V200PLUS,
  ONEKEY,
  TWOKEY,
  THREEKEY,
  FOURKEY,
  FIVEKEY,
  SIXKEY,
  SEVENKEY,
  EIGHTKEY,
  NINEKEY,
};

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

int stateMachineVal;

// Connect via i2c, default address #0 (A0-A2 not jumpered)
LiquidCrystal lcd(0);

//////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////

enum MENU_STATES
{
  MENU0 = 0,
  MENU1,
  MENU2,
  MENU3,
  MENU4,
  MENU5,
  MENU6,
};

//////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////

void setup() {
  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("*Doug's Arduino*");
  lcd.setCursor(0,1);
  lcd.print("Any key to cont.");
  irrecv.enableIRIn(); // Start the receiver
  stateMachineVal = MENU0;
}

//////////////////////////////////////////////////////////////
// loop()
/////////////////////////////////////////////////////////////

void loop() 
{
  int irVal;
  irVal = checkIR();
  switch (stateMachineVal)
  {
  case MENU0:
    if (irVal != NOKEY)
    {
      lcd.setCursor(0,0);
      lcd.print("> Accelerometer ");
      lcd.setCursor(0,1);
      lcd.print("Temperature     ");
      if (irVal == RIGHT)
      {
        lcd.setCursor(0,0);
        lcd.print("Accelerometer   ");
        lcd.setCursor(0,1);
        lcd.print("> Temperature   ");
        stateMachineVal = MENU1;
      }
      else if (irVal == PAUSE)
        stateMachineVal = MENU3;
    }
    break;
  case MENU1:
    if (irVal != NOKEY)
    {
      if (irVal == RIGHT)
        stateMachineVal = MENU2;
      else if (irVal == LEFT)
        stateMachineVal = MENU0;
      else if (irVal == PAUSE)
        stateMachineVal = MENU4;
    }
    break;
  case MENU2:
    if (irVal == RIGHT)
    {
      lcd.setCursor(0,0);
      lcd.print("Temperature     ");
      lcd.setCursor(0,1);
      lcd.print("> IR Keys       ");
    }
    else if (irVal == PAUSE)
      stateMachineVal = MENU5;
    else if (irVal == LEFT)
      stateMachineVal = MENU1;
    break;  
  case MENU3:
    if (irVal != NOKEY)
    {
      stateMachineVal = MENU0;
    }
    else
      accel();
    break;
  case MENU4:
    if (irVal != NOKEY)
    {
      stateMachineVal = MENU1;
    }
    else
    {
      lcd.setCursor(0,0);
      lcd.print("Temperature     ");
      readTMP36(0);
    }
    break;
  case MENU5:
    if (irVal != NOKEY)
    {
      stateMachineVal = MENU2;
    }
    break;
  }
}

//////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////

int checkIR()
{
  int retVal;
  if (irrecv.decode(&results)) 
  {
    if (results.value != 0xffffffff)
    {
      //      Serial.print(results.value, HEX);
      //      Serial.print("=");
      if (results.value == 0xFFA25D)
        retVal = CHMINUS;
      else if (results.value == 0xFF629D)
        retVal = CH;
      else if (results.value == 0xFFE21D)
        retVal = CHPLUS;
      else if (results.value == 0xFF22DD)
        retVal = LEFT;
      else if (results.value == 0xFF02FD)
        retVal = RIGHT;
      else if (results.value == 0xFFC23D)
        retVal = PAUSE;
      else if (results.value == 0xFFE01F)
        retVal = MINUS;
      else if (results.value == 0xFFA857)
        retVal = PLUS;
      else if (results.value == 0xFF906F)
        retVal = EQ;
      else if (results.value == 0xFF6897)
        retVal = ZEROKEY;
      else if (results.value == 0xFF9867)
        retVal = V100PLUS;
      else if (results.value == 0xFFB04F)
        retVal = V200PLUS;
      else if (results.value == 0xFF30CF)
        retVal = ONEKEY;
      else if (results.value == 0xFF18E7)
        retVal = TWOKEY;
      else if (results.value == 0xFF7A85)
        retVal = THREEKEY;
      else if (results.value == 0xFF10EF)
        retVal = FOURKEY;
      else if (results.value == 0xFF38C7)
        retVal = FIVEKEY;
      else if (results.value == 0xFF5AA5)
        retVal = SIXKEY;
      else if (results.value == 0xFF42BD)
        retVal = SEVENKEY;
      else if (results.value == 0xFF4AB5)
        retVal = EIGHTKEY;
      else if (results.value == 0xFF52AD)
        retVal = NINEKEY;
      else
        retVal = NOKEY;
    }
    irrecv.resume(); // Receive the next value
  }
  return(retVal);
}

//////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////

void accel(void)
{
  signed int x,y,z;
  signed long acc;
  x = analogRead(A1);
  y = analogRead(A2);
  z = analogRead(A3);
  x -= 313;
  y -= 356;
  z -= 280;
  acc = sqrt((x*x)+(y*y)+(z*z));
  acc -= 161;
  lcd.setCursor(0,0);
  lcd.print("X=");
  lcd.print(x);
  lcd.print(", Y=");
  lcd.print(y);
  lcd.print("      ");
  lcd.setCursor(0,1);
  lcd.print("Z=");
  lcd.print(z);
  lcd.print(", a=");
  lcd.print(acc);
  lcd.print("      ");
//  delay(200);
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


