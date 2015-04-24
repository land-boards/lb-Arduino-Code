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
    u8g.print("Running");
    setDisplayCursor(1, 0);
    u8g.print("profile");
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
      myTemp = thermocouple.readCelsius();
      setDisplayCursor(0, 0);
      u8g.print("Temp=");
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
  digitalWrite(GRN_LITE, LOW);
  u8g.firstPage();
  do
  {
    setDisplayCursor(1, 0);
    u8g.print("Lead free");
    setDisplayCursor(2, 0);
    u8g.print("profile");
    setDisplayCursor(3, 0);
    u8g.print("selected");
  }
  while ( u8g.nextPage() );
  delay(2000);
  delay(500);
  digitalWrite(GRN_LITE, HIGH);
}

void LeadFcn(void)
{
  digitalWrite(GRN_LITE, LOW);
  u8g.firstPage();
  do
  {
    setDisplayCursor(1, 0);
    u8g.print("Lead profile");
    setDisplayCursor(2, 0);
    u8g.print("selected");
  }
  while ( u8g.nextPage() );
  delay(2000);
  delay(500);
  digitalWrite(GRN_LITE, HIGH);
}

void testButtons(void)
{
  uint8_t keyState;
  u8g.firstPage();
  do
  {
    setDisplayCursor(0, 0);
    u8g.print("Button tests");
    setDisplayCursor(1, 0);
    u8g.print("Press button");
    setDisplayCursor(2, 0);
    u8g.print("Select=exit");
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
    u8g.print("Running");
    setDisplayCursor(1, 0);
    u8g.print("LED Tests");
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


