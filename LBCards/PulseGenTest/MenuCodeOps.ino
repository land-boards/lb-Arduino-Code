//////////////////////////////////////////////////////////////////////////////
// MenuCodeOps() - Customize this code for the specific operations
//////////////////////////////////////////////////////////////////////////////

void errorScreen(void)
{
  u8x8.draw2x2String(0, 2, "CONNECT"); // write something to the internal memory
  u8x8.draw2x2String(0, 4, "ERROR!"); // write something to the internal memory
  delay(50);
}

//////////////////////////////////////////////////////////////////////////////
// checkStuck(void)
//////////////////////////////////////////////////////////////////////////////

int checkStuck(void)
{
  int readVal, highVal, lowVal;
  lowVal = analogRead(A0);
  highVal = lowVal;
  for (int loopCount = 0; loopCount < 20; loopCount++)
  {
    readVal = analogRead(A0);
    if (readVal> highVal)
      highVal = readVal;
    else if (readVal < lowVal)
      lowVal = readVal;
  }
  if ((lowVal < 300) && (highVal > 300))
    return(0);
  else
  {
    errorScreen();
    delay(50);
    return(1);
  }
}

//////////////////////////////////////////////////////////////////////////////
// int waitForHigh(void)
// Returns 0 if High is detected
// Returns -1 if High was not detected
//////////////////////////////////////////////////////////////////////////////

int waitForHigh(void)
{
  int sampleCount;
  sampleCount = 0;
  while (analogRead(A0) > 200)    // If it starts high wait till it goes low
  {
    sampleCount++;
    if (sampleCount > 20)
      return(-1);
  }
  sampleCount = 0;
  while (analogRead(A0) < 100)  // pause while low
  {
    sampleCount++;
    if (sampleCount > 20)
      return(-1);
  }
  return(0);
}

//////////////////////////////////////////////////////////////////////////////
// int waitForLow(void)
//////////////////////////////////////////////////////////////////////////////

int waitForLow(void)
{
  int sampleCount;
  sampleCount = 0;
  while (analogRead(A0) < 100)  // Pause if starts High
  {
    sampleCount++;
    if (sampleCount > 20)
      return(-1);
  }
  sampleCount = 0;
  while (analogRead(A0) > 100)  // pause while high
  {
    sampleCount++;
    if (sampleCount > 20)
      return(-1);
  }
  return(0);
}

//////////////////////////////////////////////////////////////////////////////
// int countHigh(void)
//////////////////////////////////////////////////////////////////////////////

int countHigh(void)
{
  int sampleCount = 0;
  while (analogRead(A0) > 100)  // pause while high
  {
    sampleCount++;
    if (sampleCount > 20)
      return(-1);
  }
  return(sampleCount);
}

//////////////////////////////////////////////////////////////////////////////
// int countLow(void)
//////////////////////////////////////////////////////////////////////////////

int countLow(void)
{
  int sampleCount = 0;
  while (analogRead(A0) < 100)  // pause while high
  {
    sampleCount++;
    if (sampleCount > 20)
      return(-1);
  }
  return(sampleCount);
}

//////////////////////////////////////////////////////////////////////////////
// testPulseGen() - Run the main thing itself
//////////////////////////////////////////////////////////////////////////////

void testPulseGen(void)
{
  uint8_t keyState;
  int keyLev;
  int sensorLoValue;
  int sensorHiValue;
  int hiCount = 0;
  int loCount = 0;
  int caughtError = 0;

  menuCard.setLED(2, HIGH);
  do
  {
    u8x8.clear();
    if (checkStuck() != 1)
    {
      caughtError = 0;
      if (waitForLow() == -1)
        caughtError = 1;
      sensorLoValue = analogRead(A0);
      loCount = countLow();
      if (waitForHigh() == -1)
        caughtError = 1;
      sensorHiValue = analogRead(A0);
      hiCount = countHigh();
      if (caughtError == 0)
      {
        u8x8.setCursor(0, 0);
        u8x8.print(F("Low Count="));
        u8x8.print(loCount);
        u8x8.print("   ");
        u8x8.setCursor(0, 1);
        u8x8.print(F("High Count="));
        u8x8.print(hiCount);
        u8x8.print("   ");
        u8x8.setCursor(0, 2);
        u8x8.print(F("Low V="));
        u8x8.print(sensorLoValue);
        u8x8.print("   ");
        u8x8.setCursor(0, 3);
        u8x8.print(F("High V="));
        u8x8.print(sensorHiValue);
        u8x8.print("   ");
      }
      delay(250);
    }
    keyState = menuCard.pollKeypad();
  }
  while (keyState != SELECT);
  menuCard.setLED(2, LOW);
}

//////////////////////////////////////////////////////////////////////////////
// runMonFcn() - Run the monitoring function
//////////////////////////////////////////////////////////////////////////////

void runMonFcn(void)
{
  double myTemp;
  uint8_t keyState;
  u8x8.clear();
  menuCard.setLED(0, HIGH);
  do
  {
    u8x8.setCursor(0, 0);
    u8x8.print(F("Monitoring"));
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
  u8x8.clear();
  u8x8.drawString(0, 1, "Selected"); // write something to the internal memory
  u8x8.drawString(0, 2, "Option1"); // write something to the internal memory
  delay(2000);
}

//////////////////////////////////////////////////////////////////////////////
// Opt2Fcn() - Example of setting a second option flag
//////////////////////////////////////////////////////////////////////////////

void Opt2Fcn(void)
{
  u8x8.clear();
  u8x8.drawString(0, 1, "Selected"); // write something to the internal memory
  u8x8.drawString(0, 2, "Option2"); // write something to the internal memory
  delay(2000);
}

//////////////////////////////////////////////////////////////////////////////
// testButtons() - Test the MyMenu system buttons
//////////////////////////////////////////////////////////////////////////////

void testButtons(void)
{
  u8x8.clear();
  uint8_t keyState;
  u8x8.drawString(0, 1, "Button tests"); // write something to the internal memory
  u8x8.drawString(0, 2, "Press button"); // write something to the internal memory
  u8x8.drawString(0, 3, "Select=exit"); // write something to the internal memory

  do
  {
    delay(100);
    keyState = menuCard.pollKeypad();
    switch (keyState)
    {
      case RIGHT:
        u8x8.drawString(0, 4, "Right button"); // write something to the internal memory
        break;
      case LEFT:
        u8x8.drawString(0, 4, "Left Button "); // write something to the internal memory
        break;
      case UP:
        u8x8.drawString(0, 4, "Up Button   "); // write something to the internal memory
        break;
      case DOWN:
        u8x8.drawString(0, 4, "Down Button "); // write something to the internal memory
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
  u8x8.clear();
  u8x8.drawString(0, 1, "Running"); // write something to the internal memory
  u8x8.drawString(0, 2, "LED Tests"); // write something to the internal memory
  u8x8.drawString(0, 3, "Select=exit"); // write something to the internal memory
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


