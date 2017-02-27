//////////////////////////////////////////////////////////////////////////////
// MenuCodeOps() - Run the IReflow Menu Functions
//////////////////////////////////////////////////////////////////////////////

void runProfileFcn(void)
{
  double myTemp;
  double goalTemp;
  uint8_t keyState;
  menuCard.setLED(1, HIGH);
  setTime(0);
  time_t t = now();
  do
  {
    myTemp = thermocouple.readCelsius();
    setDisplayCursor(0, 0);
    u8x8.print(F("Meas="));
    u8x8.print(myTemp);
    if (profileSelected == LEAD_FREE)
    {
      goalTemp = getDesiredTempLeadFree(60 * minute(t) + second(t));
    }
    else if (profileSelected == LEADED)
    {
      goalTemp = getDesiredTempLeaded(60 * minute(t) + second(t));
    }
    else
    {
      goalTemp = -10.0;
    }
    setDisplayCursor(1, 0);
    u8x8.print(F("Goal="));
    u8x8.print(goalTemp);
    setDisplayCursor(2, 0);
    if (myTemp > goalTemp)
    {
      u8x8.print(F("SSR=Off"));
      digitalWrite(SSR, LOW);
      menuCard.setLED(2, LOW);
    }
    else
    {
      u8x8.print(F("SSR=On"));
      digitalWrite(SSR, HIGH);
      menuCard.setLED(2, HIGH);
    }
    setDisplayCursor(3, 0);
    u8x8.print(F("Time="));
    u8x8.print((60 * minute(t)) + second(t));
    delay(100);
    t = now();
    keyState = menuCard.pollKeypad();
  }
  while ( (keyState != SELECT) && (t < 600));
  digitalWrite(SSR, LOW);
  menuCard.setLED(1, LOW);
  menuCard.setLED(2, LOW);
}

void monTempFcn(void)
{
  double myTemp;
  uint8_t keyState;
  menuCard.setLED(0, HIGH);
  setTime(0);
  time_t t = now();
  do
  {
      myTemp = thermocouple.readCelsius();
      setDisplayCursor(0, 0);
      u8x8.print(F("Temp="));
      u8x8.print(myTemp);
      setDisplayCursor(1, 0);
      u8x8.print((60 * minute(t)) + second(t));
    delay(100);
    t = now();
    keyState = menuCard.pollKeypad();
  }
  while (keyState != SELECT);
  menuCard.setLED(0, LOW);
}

void LeadFreeFcn(void)
{
  profileSelected = LEAD_FREE;
  digitalWrite(GRN_LITE, LOW);
    setDisplayCursor(1, 0);
    u8x8.print(F("Lead free"));
    setDisplayCursor(2, 0);
    u8x8.print(F("profile"));
    setDisplayCursor(3, 0);
    u8x8.print(F("selected"));
  delay(2000);
  delay(500);
  digitalWrite(GRN_LITE, HIGH);
}

void LeadFcn(void)
{
  profileSelected = LEADED;
  digitalWrite(GRN_LITE, LOW);
    setDisplayCursor(1, 0);
    u8x8.print(F("Lead profile"));
    setDisplayCursor(2, 0);
    u8x8.print(F("selected"));
  delay(2000);
  delay(500);
  digitalWrite(GRN_LITE, HIGH);
}

void testButtons(void)
{
  uint8_t keyState;
  setDisplayCursor(0, 0);
  u8x8.print(F("Button tests"));
  setDisplayCursor(1, 0);
  u8x8.print(F("Press button"));
  setDisplayCursor(2, 0);
  u8x8.print(F("Select=exit"));
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
  setDisplayCursor(0, 0);
  u8x8.print(myString);
}

void testLEDsFcn(void)
{
  setDisplayCursor(0, 0);
  u8x8.print(F("Running"));
  setDisplayCursor(1, 0);
  u8x8.print(F("LED Tests"));
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


