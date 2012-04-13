/*
 MultiI2CAdafruit - Multi I/O Card using Adadfruit style of LCD.
 Supported functions are:
 TMP36A - Temperature sensor
 MMA7361 - Accelerometer
 IR Sensor
 */

//////////////////////////////////////////////////////////////
// Includes follow
/////////////////////////////////////////////////////////////

#include "Wire.h"
#include "LiquidCrystal.h"
#include <IRremote.h>
#include "Ultrasonic.h"

//////////////////////////////////////////////////////////////
// enums follow
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

enum MENU_STATES
{
  MENU0 = 0,
  MENU0B,
  MENU0C,
  MENU1,
  MENU1B,
  MENU1C,
  MENU2,
  MENU2B,
  MENU2C,
  MENU5,
  MENU6,
  MENU6B,
  MENU7,
  MENU7B,
  MENU7C,
};

//////////////////////////////////////////////////////////////
// Global variables follow
//////////////////////////////////////////////////////////////

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

int stateMachineVal; 

// Connect via i2c, default address #0 (A0-A2 not jumpered)

LiquidCrystal lcd(0);

Ultrasonic ultrasonic(13,4);

short ranges[5];

//////////////////////////////////////////////////////////////
// setup() -
/////////////////////////////////////////////////////////////

void setup() {
  // set up the LCD's number of rows and columns:
  lcd.begin(16, 2);
  irrecv.enableIRIn(); // Start the receiver
  initRanges();
  stateMachineVal = MENU6;
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
  case MENU6:
    {
      // Print a message to the LCD.
      lcd.setCursor(0,0);
      lcd.print("*Doug's Arduino*");
      lcd.setCursor(0,1);
      lcd.print("Any key to cont.");
      stateMachineVal = MENU6B;
    }
    break;
  case MENU6B:
    {
      if (irVal != NOKEY)
        stateMachineVal = MENU0;
    }
    break;
  case MENU0:
    lcd.setCursor(0,0);
    lcd.print("> Accelerometer ");
    lcd.setCursor(0,1);
    lcd.print("Temperature     ");
    stateMachineVal = MENU0B;
    break;
  case MENU0B:
    {
      if (irVal != NOKEY)
      {
        if (irVal == RIGHT)
        {
          stateMachineVal = MENU1;
        }
        else if (irVal == LEFT)
        {
          stateMachineVal = MENU6;
        }
        else if (irVal == PAUSE)
          stateMachineVal = MENU0C;
      }
    }
    break;
  case MENU0C:
    if (irVal != NOKEY)
    {
      stateMachineVal = MENU0;
    }
    else
      accel();
    break;
  case MENU1:
    {
      lcd.setCursor(0,0);
      lcd.print("Accelerometer   ");
      lcd.setCursor(0,1);
      lcd.print("> Temperature   ");
      stateMachineVal = MENU1B;
      break;
    }
  case MENU1B:
    if (irVal != NOKEY)
    {
      if (irVal == RIGHT)
        stateMachineVal = MENU2;
      else if (irVal == LEFT)
        stateMachineVal = MENU0;
      else if (irVal == PAUSE)
        stateMachineVal = MENU1C;
    }
    break;
  case MENU1C:
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
  case MENU2:
    lcd.setCursor(0,0);
    lcd.print("Temperature     ");
    lcd.setCursor(0,1);
    lcd.print("> IR Keys       ");
    stateMachineVal = MENU2B;
    break;
  case MENU2B:
    {
      if (irVal != NOKEY)
      {
         if (irVal == LEFT)
          stateMachineVal = MENU1;
        else if (irVal == RIGHT)
          stateMachineVal = MENU7;
        else if (irVal == PAUSE)
          stateMachineVal = MENU2C;
      }
    }
    break;
  case MENU2C:
    if (irVal != NOKEY)
    {
      stateMachineVal = MENU2;
    }
    else
      testIRKeys();
    break;
  case MENU5:
    if (irVal != NOKEY)
    {
      stateMachineVal = MENU2;
    }
    break;
  case MENU7:
    lcd.setCursor(0,0);
    lcd.print("IR Keys         ");
    lcd.setCursor(0,1);
    lcd.print("> Ultrasonic    ");
    stateMachineVal = MENU7B;
    break;
  case MENU7B:
    {
      if (irVal != NOKEY)
      {
         if (irVal == LEFT)
          stateMachineVal = MENU2;
        else if (irVal == PAUSE)
        {
          lcd.setCursor(0,0);
          lcd.print("Ultrasonic range");
          stateMachineVal = MENU7C;
        }
      }
    }
    break;
  case MENU7C:
    {
      lcd.setCursor(0,1);
      putNewRange(ultrasonic.Ranging(INC));
      lcd.print(getRangeVal());
      lcd.print(" in            ");
    }
    if (irVal != NOKEY)
      stateMachineVal = MENU7;
    break;
  }
}

//////////////////////////////////////////////////////////////
// checkIR - Check the IR input and convert from the value to the key.
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
// accel - Display the accelerometer values
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

///////////////////////////////////////////////////////////////////////
// testIRKeys(
///////////////////////////////////////////////////////////////////////

void testIRKeys(void)
{
  lcd.setCursor(0,0);
  lcd.print("IR KEY Testing  ");
  lcd.setCursor(0,1);
  lcd.print("                ");
}

void putNewRange(long newRangeVal)
{
 ranges[0] = ranges[1];
 ranges[1] = ranges[2];
 ranges[2] = ranges[3];
 ranges[3] = ranges[4];
 ranges[4] = newRangeVal;
 return;
}

void initRanges(void)
{
  putNewRange(ultrasonic.Ranging(INC));
  putNewRange(ultrasonic.Ranging(INC));
  putNewRange(ultrasonic.Ranging(INC));
  putNewRange(ultrasonic.Ranging(INC));
  putNewRange(ultrasonic.Ranging(INC));  
}

short getRangeVal(void)
{
  if (ranges[4] == ranges[3])
    return(ranges[4]);
  else if (ranges[4] == ranges[3] + 1)
    return(ranges[3]);
  else if (ranges[4] == ranges[3] -1 )
    return(ranges[3]);
  else if (ranges[4] == ranges[2])
    return(ranges[4]);
  else if (ranges[3] == ranges[2])
    return(ranges[3]);
  else if (ranges[2] == ranges[1])
    return(ranges[2]);
  else return(ranges[4]);
  
}

