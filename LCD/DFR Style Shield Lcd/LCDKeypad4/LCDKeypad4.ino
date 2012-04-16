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
  lcd.print("MyArdino.pbworks");
  clearLCDLine(1);
  lcd.print(".com");
  while (checkIfKeyIsPressed() == false);	// wait for keypress
  while (checkIfKeyIsPressed() == true);	// wait for key no longer pressed
  clearLCDScreen();
  menuStateVal = MENU0;
}

///////////////////////////////////////////////////////////////////////
// loop()
///////////////////////////////////////////////////////////////////////

void loop()
{
  unsigned char myButtonVal;
  switch (menuStateVal)
  {
    case MENU0:
      clearLCDLine(0);
      lcd.print("> Test Keys");
      clearLCDLine(1);
      lcd.print("Setup");
      myButtonVal = getDebouncedKeypad();
      if (myButtonVal == KEYPAD_DOWN)
        menuStateVal = MENU1;
      else if ((myButtonVal == KEYPAD_RIGHT) || (myButtonVal == KEYPAD_SELECT))
        menuStateVal = MENU2;
      break;
    case MENU1:
      lcd.setCursor(0,0);
      lcd.print("Test Keys       ");
      lcd.setCursor(0,1);
      lcd.print("> Setup         ");
      myButtonVal = getDebouncedKeypad();
      if (myButtonVal == KEYPAD_UP)
        menuStateVal = MENU0;
      else if ((myButtonVal == KEYPAD_RIGHT) || (myButtonVal == KEYPAD_SELECT))
        menuStateVal = MENU3;
      break;
    case MENU2:
      lcd.setCursor(0,0);
      lcd.print("** Test Keys ** ");
      lcd.setCursor(0,1);
      lcd.print("                ");
      while (1)
        testKeypad();
      break;
    case MENU3:
      clearLCDLine(0);
      lcd.print("> Set Brightness");
      clearLCDLine(1);
      myButtonVal = getDebouncedKeypad();
      if ((myButtonVal == KEYPAD_RIGHT) || (myButtonVal == KEYPAD_SELECT))
        menuStateVal = MENU4;
      else if (myButtonVal == KEYPAD_LEFT)
        menuStateVal = MENU1;
      break;
    case MENU4:
      lcd.setCursor(0,0);
      lcd.print("Set brightness  ");
      clearLCDLine(1);
      lcd.print(lcdBrightness);
      myButtonVal = getDebouncedKeypad();
      if (myButtonVal == KEYPAD_UP)
        lcdBrightness+=5;
      else if (myButtonVal == KEYPAD_DOWN)
        lcdBrightness-=5;
      else if (myButtonVal == KEYPAD_LEFT)
        menuStateVal = MENU3;
      else if (myButtonVal == KEYPAD_SELECT)
      { 
        EEPROM.write(0,lcdBrightness);
        menuStateVal = MENU3;
      }
      setLCDBrightness(lcdBrightness);
      break;
  }
}

