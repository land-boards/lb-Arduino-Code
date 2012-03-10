#include <LiquidCrystal.h>
#include <LCDKeypad.h>

LCDKeypad lcd;

///////////////////////////////////////////////////////////////////////
// globals
///////////////////////////////////////////////////////////////////////

int menuStateVal;
int lcdBrightness;

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
  int brightness;

  lcd.begin(16, 2);
  lcd.clear();
  // set the LCD brightness
  pinMode(10, OUTPUT);
  lcdBrightness = 150;
  analogWrite(10, lcdBrightness);
  // Go to the first line
  lcd.setCursor(0,0);
  // Display the banner
  lcd.print("MyArdino.pbworks");
  lcd.setCursor(0,1);
  lcd.print(".com            ");
  while (checkIfKeyIsPressed() == false);
  while (checkIfKeyIsPressed() == true);
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,0);
  menuStateVal = MENU0;
}

///////////////////////////////////////////////////////////////////////
// checkIfKeyIsPressed()
///////////////////////////////////////////////////////////////////////

boolean checkIfKeyIsPressed(void)
{
  if (lcd.button()==KEYPAD_NONE)
    return(false);
  else
    return(true);
}

///////////////////////////////////////////////////////////////////////
// getDebouncedKeypad()
// Waits for a key to be pressed. Also, has a fairly simple debounce with
//  the cost that the algorithm sticks around until the key is released.
///////////////////////////////////////////////////////////////////////

int getDebouncedKeypad(void)
{
  int buttonPressed; 
  while((buttonPressed=lcd.button())==KEYPAD_NONE)
    delay(5);
  while(lcd.button()!=KEYPAD_NONE)
    delay(5);
  return buttonPressed;
}
///////////////////////////////////////////////////////////////////////
// testKeypad()
///////////////////////////////////////////////////////////////////////

void testKeypad(void)
{
  int myButtonVal;
  if (checkIfKeyIsPressed() == false)
    return;
  lcd.setCursor(0,1);
  myButtonVal = getDebouncedKeypad();
  switch(myButtonVal)
  {
    case KEYPAD_NONE:
      lcd.print("None   ");
    break;
    case KEYPAD_RIGHT:
      lcd.print("Right  ");
    break;
    case KEYPAD_UP:
      lcd.print("Up     ");
    break;
    case KEYPAD_DOWN:
      lcd.print("Down   ");
    break;
    case KEYPAD_LEFT:
      lcd.print("Left   ");
    break;
    case KEYPAD_SELECT:
      lcd.print("Select ");
    break;
  }
}

///////////////////////////////////////////////////////////////////////
// loop()
///////////////////////////////////////////////////////////////////////

void loop()
{
  int myButtonVal;
  switch (menuStateVal)
  {
    case MENU0:
      lcd.setCursor(0,0);
      lcd.print("> Test Keys     ");
      lcd.setCursor(0,1);
      lcd.print("Setup           ");
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
      lcd.setCursor(0,0);
      lcd.print("> Set Brightness");
      lcd.setCursor(0,1);
      lcd.print("                ");
      myButtonVal = getDebouncedKeypad();
      if ((myButtonVal == KEYPAD_RIGHT) || (myButtonVal == KEYPAD_SELECT))
        menuStateVal = MENU4;
      else if (myButtonVal == KEYPAD_LEFT)
        menuStateVal = MENU1;
      break;
    case MENU4:
      lcd.setCursor(0,0);
      lcd.print("Set brightness  ");
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print(lcdBrightness);
      myButtonVal = getDebouncedKeypad();
      if (myButtonVal == KEYPAD_UP)
        lcdBrightness+=5;
      else if (myButtonVal == KEYPAD_DOWN)
        lcdBrightness-=5;
      else if ((myButtonVal == KEYPAD_LEFT) || (myButtonVal == KEYPAD_SELECT))
        menuStateVal = MENU3;
      analogWrite(10, lcdBrightness);
      break;
  }
}

