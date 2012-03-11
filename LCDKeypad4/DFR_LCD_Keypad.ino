///////////////////////////////////////////////////////////////////////
// clearLCDScreen()
///////////////////////////////////////////////////////////////////////

void clearLCDScreen(void)
{
  clearLCDLine(1);
  clearLCDLine(0);
  return;
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

void setLCDBrightness(int lcdBright)
{
  pinMode(10, OUTPUT);	  // set the LCD brightness
  analogWrite(10, lcdBright);
  return;
}

///////////////////////////////////////////////////////////////////////
// clearLCDLine()
///////////////////////////////////////////////////////////////////////

void clearLCDLine(int lineToClear)
{
  lcd.setCursor(0,lineToClear);
  lcd.print("                ");
  lcd.setCursor(0,lineToClear);
  return;
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
  clearLCDLine(1);
  myButtonVal = getDebouncedKeypad();
  switch(myButtonVal)
  {
    case KEYPAD_NONE:
      lcd.print("None");
    break;
    case KEYPAD_RIGHT:
      lcd.print("Right");
    break;
    case KEYPAD_UP:
      lcd.print("Up");
    break;
    case KEYPAD_DOWN:
      lcd.print("Down");
    break;
    case KEYPAD_LEFT:
      lcd.print("Left");
    break;
    case KEYPAD_SELECT:
      lcd.print("Select");
    break;
  }
}

