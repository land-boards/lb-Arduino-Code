//////////////////////////////////////////////////////////////////////////////
// menuOps - Menu Operations
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// testKeyPad() - Verify keypad works
//////////////////////////////////////////////////////////////////////////////

void testKeyPad(void)
{
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Testing Keypad");
    setCursorTFT(1,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Hold SELECT to exit");
      long loopCount = 0;
      int key;
      tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
      while (loopCount < 100)
      {
        key = myMiniDuino.pollKeypad();
        setCursorTFT(2,0);
        switch (key)
        {
        case NONE:
          tft.print("NONE  ");
          loopCount = 0;
          break;
        case LEFT:
          tft.print("LEFT  ");
          loopCount = 0;
          break;
        case RIGHT:
          tft.print("RIGHT ");
          loopCount = 0;
          break;
        case UP:
          tft.print("UP    ");
          loopCount = 0;
          break;
        case DOWN:
          tft.print("DOWN  ");
          loopCount = 0;
          break;
        case SELECT:
          tft.print("SELECT");
          loopCount++;
          break;
        }
      }
      setCursorTFT(3,0);
      tft.print("EXITING, release Sel");
      while (myMiniDuino.pollKeypad() == SELECT);
}

//////////////////////////////////////////////////////////////////////////////
// testIR() - Test the IR
//////////////////////////////////////////////////////////////////////////////

void testIR(void)
{
    tft.fillScreen(ST7735_BLACK);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    setCursorTFT(0,0);
    tft.print("Testing IR Sensors");
      setCursorTFT(1,0);
      int tmpAna1;
      int tmpAna2;
      do
      {
      tmpAna1 = analogRead(ANALOGIN1);
      tmpAna2 = analogRead(ANALOGIN2);
      setCursorTFT(2,0);
      tft.print(tmpAna1);
      tft.print(" ");
      tft.print(tmpAna2);
      }
    while (myMiniDuino.pollKeypad() == NONE);
    while (myMiniDuino.pollKeypad() != NONE);
    tft.fillScreen(ST7735_BLACK);
}

//////////////////////////////////////////////////////////////////////////////
// setVol() - Set the volume
//////////////////////////////////////////////////////////////////////////////

void setVol(void)
{
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Setting the volume");
    setCursorTFT(1,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Up/Down");
      long loopCount = 0;
      int key;
      tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
      do
      {
        key = myMiniDuino.pollKeypad();
        setCursorTFT(2,0);
        switch (key)
        {
        case UP:
          tft.print(loopCount);
          if (loopCount < 127)
            loopCount++;
          break;
        case DOWN:
          tft.print(loopCount);
          if (loopCount > 0)
            loopCount--;
          break;
        case SELECT:
          tft.print("SELECT");
          break;
        }
        volumeValue = loopCount;
        freqValue = 63;
        setHVPots();
        delay(100);
      }
      while (key != SELECT);
      setCursorTFT(3,0);
      tft.print("EXITING, release Sel");
      while (myMiniDuino.pollKeypad() != NONE);

}

//////////////////////////////////////////////////////////////////////////////
// setFreq() - Set the frequency
//////////////////////////////////////////////////////////////////////////////

void setFreq(void)
{
  
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Setting the frequency");
    setCursorTFT(1,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Up/Down");
      long loopCount = 0;
      int key;
      tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
      do
      {
        key = myMiniDuino.pollKeypad();
        setCursorTFT(2,0);
        switch (key)
        {
        case UP:
          tft.print(loopCount);
          if (loopCount < 127)
            loopCount++;
          break;
        case DOWN:
          tft.print(loopCount);
          if (loopCount > 0)
            loopCount--;
          break;
        case SELECT:
          tft.print("SELECT");
          break;
        }
        freqValue = loopCount;
        volumeValue = 63;
        setHVPots();
        delay(100);
      }
      while (key != SELECT);
      setCursorTFT(3,0);
      tft.print("EXITING, release Sel");
      while (myMiniDuino.pollKeypad() != NONE);

}

