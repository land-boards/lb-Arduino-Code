///////////////////////////////////////////////////////////////////////
// State-driven menu system using the DFRobot LCD Keypad Shield
///////////////////////////////////////////////////////////////////////

#include <LiquidCrystal.h> 	// "Generic" LCD library
#include <LCDKeypad.h>		// DFRobot LCD Keypad shield library
#include <EEPROM.h>             // EEPROM

///////////////////////////////////////////////////////////////////////
// globals
///////////////////////////////////////////////////////////////////////

LCDKeypad lcd;

signed char menuStateVal;
unsigned char lcdBrightness;

///////////////////////////////////////////////////////////////////////
// enums
///////////////////////////////////////////////////////////////////////

enum MENU_STATE
{
  MENU0,
  MENU1,
  MENU2,
  MENU3,
  MENU4,
};

///////////////////////////////////////////////////////////////////////
// setup() - Run once
///////////////////////////////////////////////////////////////////////

void setup()
{
  unsigned char brightness;

  lcd.begin(16, 2);
  lcd.clear();
  lcdBrightness = EEPROM.read(0);
  setLCDBrightness(lcdBrightness);
  clearLCDLine(0);
  // Display the banner
  lcd.print("Accelerometer   ");
  clearLCDLine(1);
  while (checkIfKeyIsPressed() == false);	// wait for keypress
  while (checkIfKeyIsPressed() == true);	// wait for key no longer pressed
  clearLCDScreen();
}

///////////////////////////////////////////////////////////////////////
// loop()
///////////////////////////////////////////////////////////////////////

void loop()
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
  clearLCDLine(0);
  lcd.print("X=");
  lcd.print(x);
  lcd.print(", Y=");
  lcd.print(y);
  clearLCDLine(1);
  lcd.print("Z=");
  lcd.print(z);
  lcd.print(", a=");
  lcd.print(acc);
  delay(200);
}

