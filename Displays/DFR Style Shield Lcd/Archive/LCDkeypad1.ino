#include <LiquidCrystal.h>
#include <LCDKeypad.h>

LCDKeypad lcd;

int menuStateVal;

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
  analogWrite(10, 150);
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
  menuStateVal = MENU1;
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
  lcd.setCursor(0,0);
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

enum MENU_STATE
{
  MENU0,
  MENU1,
  MENU2,
  MENU3,
};

///////////////////////////////////////////////////////////////////////
// loop()
///////////////////////////////////////////////////////////////////////

void loop()
{
  switch (menuStateVal)
  {
    case MENU0:
      lcd.setCursor(0,0);
      lcd.print("> Test Keys     ");
      lcd.setCursor(0,1);
      lcd.print("Setup           ");
      myButtonVal = getDebouncedKeypad();
      break;
    case MENU1:
    break;
    case MENU2:
    break;
    case MENU3:
    break;
  }
}

