//////////////////////////////////////////////////////////////////////////////
// MenuCodeOps() - Customize this code for the specific operations
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// runThingFcn() - Run the main thing itself
//////////////////////////////////////////////////////////////////////////////

void runThingFcn(void)
{
  menuCard.setLED(2, HIGH);
  u8g.firstPage();
  do
  {
    setDisplayCursor(0, 0);
    u8g.print(F("Running"));
    setDisplayCursor(1, 0);
    u8g.print(F("Thing"));
  }
  while ( u8g.nextPage() );
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
  menuCard.setLED(0, HIGH);
  do
  {
    u8g.firstPage();
    do
    {
      setDisplayCursor(0, 0);
      u8g.print(F("Monitoring"));
    }
    while ( u8g.nextPage() );
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
  u8g.firstPage();
  do
  {
    setDisplayCursor(1, 0);
    u8g.print(F("Selected"));
    setDisplayCursor(2, 0);
    u8g.print(F("Option1"));
  }
  while ( u8g.nextPage() );
  delay(2000);
}

//////////////////////////////////////////////////////////////////////////////
// Opt2Fcn() - Example of setting a second option flag
//////////////////////////////////////////////////////////////////////////////

void Opt2Fcn(void)
{
  u8g.firstPage();
  do
  {
    setDisplayCursor(1, 0);
    u8g.print(F("Selected"));
    setDisplayCursor(2, 0);
    u8g.print(F("Option2"));
  }
  while ( u8g.nextPage() );
  delay(2000);
}

//////////////////////////////////////////////////////////////////////////////
// testButtons() - Test the MyMenu system buttons
//////////////////////////////////////////////////////////////////////////////

void testButtons(void)
{
  uint8_t keyState;
  u8g.firstPage();
  do
  {
    setDisplayCursor(0, 0);
    u8g.print(F("Button tests"));
    setDisplayCursor(1, 0);
    u8g.print(F("Press button"));
    setDisplayCursor(2, 0);
    u8g.print(F("Select=exit"));
  }
  while ( u8g.nextPage() );
  do
  {
    delay(100);
    keyState = menuCard.pollKeypad();
    switch (keyState)
    {
      case RIGHT:
        printString("Right button");
        break;
      case LEFT:
        printString("Left Button");
        break;
      case UP:
        printString("Up button");
        break;
      case DOWN:
        printString("Down button");
        break;
    }
  }
  while (keyState != SELECT);
}

//////////////////////////////////////////////////////////////////////////////
// printString() - Specific function to print a single status string
// Used by the testButtons function specifically
// Clears screen before printing the string
//////////////////////////////////////////////////////////////////////////////

void printString(char * myString)
{
  u8g.firstPage();
  do
  {
    setDisplayCursor(0, 0);
    u8g.print(myString);
  }
  while ( u8g.nextPage() );
}

//////////////////////////////////////////////////////////////////////////////
// testLEDsFcn() - Test the MyMenu system LEDs
//////////////////////////////////////////////////////////////////////////////

void testLEDsFcn(void)
{
  u8g.firstPage();
  do
  {
    setDisplayCursor(0, 0);
    u8g.print(F("Running"));
    setDisplayCursor(1, 0);
    u8g.print(F("LED Tests"));
  }
  while ( u8g.nextPage() );
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

