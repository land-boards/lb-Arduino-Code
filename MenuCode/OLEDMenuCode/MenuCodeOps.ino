//////////////////////////////////////////////////////////////////////////////
// MenuCodeOps() - Run the IReflow Menu Functions
//////////////////////////////////////////////////////////////////////////////

void runProfileFcn(void)
{
  menuCard.setLED(2, HIGH);
  u8g.firstPage();
  do
  {
    setDisplayCursor(0, 0);
    u8g.print(F("Running"));
    setDisplayCursor(1, 0);
    u8g.print(F("profile"));
  }
  while ( u8g.nextPage() );
  delay(500);
  menuCard.setLED(2, LOW);
}

void monTempFcn(void)
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
      u8g.print(F("Temp="));
      u8g.print(myTemp);
    }
    while ( u8g.nextPage() );
    delay(10);
    keyState = menuCard.pollKeypad();
  }
  while (keyState != SELECT);
  menuCard.setLED(0, LOW);
}

void LeadFreeFcn(void)
{
  u8g.firstPage();
  do
  {
    setDisplayCursor(1, 0);
    u8g.print(F("Lead free"));
    setDisplayCursor(2, 0);
    u8g.print(F("profile"));
    setDisplayCursor(3, 0);
    u8g.print(F("selected"));
  }
  while ( u8g.nextPage() );
  delay(2000);
  delay(500);
}

void LeadFcn(void)
{
  u8g.firstPage();
  do
  {
    setDisplayCursor(1, 0);
    u8g.print(F("Lead profile"));
    setDisplayCursor(2, 0);
    u8g.print(F("selected"));
  }
  while ( u8g.nextPage() );
  delay(2000);
  delay(500);
}

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


