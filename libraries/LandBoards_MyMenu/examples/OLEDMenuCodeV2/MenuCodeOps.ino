//////////////////////////////////////////////////////////////////////////////
// MenuCodeOps() - Customize this code for the specific operations
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// runThingFcn() - Run the main thing itself
//////////////////////////////////////////////////////////////////////////////

void runThingFcn(void)
{
  clearDisplay();
  menuCard.setLED(2, HIGH);
  u8x8.drawString(0,2,"Running Thing");  // write something to the internal memory
  delay(500);
  menuCard.setLED(2, LOW);
}

//////////////////////////////////////////////////////////////////////////////
// runMonFcn() - Run the monitoring function
//////////////////////////////////////////////////////////////////////////////

void runMonFcn(void)
{
  double myTemp;
  uint8_t keyState;
  clearDisplay();
  menuCard.setLED(0, HIGH);
  do
  {
    u8x8.drawString(0,2,"Monitoring");  // write something to the internal memory
    delay(10);
    keyState = menuCard.pollKeypad();
  }
  while (keyState != SELECT);
  menuCard.setLED(0, LOW);
}

//////////////////////////////////////////////////////////////////////////////
// Opt1Fcn() - Example of setting an option flag
//////////////////////////////////////////////////////////////////////////////

void Opt1Fcn(void)
{
  clearDisplay();
  u8x8.drawString(0,1,"Selected");  // write something to the internal memory
  u8x8.drawString(0,2,"Option1");  // write something to the internal memory
  delay(2000);
}

//////////////////////////////////////////////////////////////////////////////
// Opt2Fcn() - Example of setting a second option flag
//////////////////////////////////////////////////////////////////////////////

void Opt2Fcn(void)
{
  clearDisplay();
  u8x8.drawString(0,1,"Selected");  // write something to the internal memory
  u8x8.drawString(0,2,"Option2");  // write something to the internal memory
  delay(2000);
}

//////////////////////////////////////////////////////////////////////////////
// testButtons() - Test the MyMenu system buttons
//////////////////////////////////////////////////////////////////////////////

void testButtons(void)
{
  clearDisplay();
  uint8_t keyState;
  u8x8.drawString(0,1,"Button tests");  // write something to the internal memory
  u8x8.drawString(0,2,"Press button");  // write something to the internal memory
  u8x8.drawString(0,3,"Select=exit");  // write something to the internal memory

  do
  {
    delay(100);
    keyState = menuCard.pollKeypad();
    switch (keyState)
    {
      case RIGHT:
        u8x8.drawString(0,4,"Right button");  // write something to the internal memory
        break;
      case LEFT:
        u8x8.drawString(0,4,"Left Button ");  // write something to the internal memory
        break;
      case UP:
        u8x8.drawString(0,4,"Up Button   ");  // write something to the internal memory
        break;
      case DOWN:
        u8x8.drawString(0,4,"Down Button ");  // write something to the internal memory
        break;
    }
  }
  while (keyState != SELECT);
}

//////////////////////////////////////////////////////////////////////////////
// testLEDsFcn() - Test the MyMenu system LEDs
//////////////////////////////////////////////////////////////////////////////

void testLEDsFcn(void)
{
  clearDisplay();
  u8x8.drawString(0,1,"Running");  // write something to the internal memory
  u8x8.drawString(0,2,"LED Tests");  // write something to the internal memory
  u8x8.drawString(0,3,"Select=exit");  // write something to the internal memory
  menuCard.setLED(0, HIGH);
  delay(500);
  menuCard.setLED(0, LOW);
  menuCard.setLED(1, HIGH);
  delay(500);
  menuCard.setLED(1, LOW);
  menuCard.setLED(2, HIGH);
  delay(500);
  menuCard.setLED(2, LOW);
}

