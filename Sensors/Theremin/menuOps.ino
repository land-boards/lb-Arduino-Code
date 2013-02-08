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
    tft.print("     ");
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
  setCursorTFT(2,0);
  tft.print(loopCount);
  do
  {
    key = myMiniDuino.pollKeypad();
    setCursorTFT(2,0);
    switch (key)
    {
    case UP:
      if (loopCount < 127)
        loopCount++;
      break;
    case DOWN:
      if (loopCount > 0)
        loopCount--;
      break;
    case SELECT:
      tft.print("SELECT");
      break;
    }
    tft.print(loopCount);
    tft.print("  ");
    vol128 = loopCount;
    freq128 = 63;
    setHVPots();
    delay(200);
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
  setCursorTFT(2,0);
  tft.print(loopCount);
  do
  {
    key = myMiniDuino.pollKeypad();
    setCursorTFT(2,0);
    switch (key)
    {
    case UP:
      if (loopCount < 127)
        loopCount++;
      break;
    case DOWN:
      if (loopCount > 0)
        loopCount--;
      break;
    case SELECT:
      tft.print("SELECT");
      break;
    }
    tft.print(loopCount);
    tft.print("  ");
    freq128 = loopCount;
    vol128 = 63;
    setHVPots();
    delay(200);
  }
  while (key != SELECT);
  setCursorTFT(3,0);
  tft.print("EXITING, release Sel");
  while (myMiniDuino.pollKeypad() != NONE);

}

//////////////////////////////////////////////////////////////////////////////
// calibIR() - Calibrate the IR sensors
//////////////////////////////////////////////////////////////////////////////

void calibIR(void)
{
  int volLo, volHi, freqLo, freqHi;
  int keyVal;
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  setCursorTFT(0,0);
  tft.print("Calibrating IR");
  setCursorTFT(1,0);
  tft.print("Hover vol lo - ");
  delay(3000);
  volLo = analogRead(ANALOGIN1);
  tft.print(volLo);
  setCursorTFT(2,0);
  tft.print("Hover vol hi - ");
  delay(3000);
  volHi = analogRead(ANALOGIN1);
  tft.print(volHi);
  setCursorTFT(3,0);
  tft.print("Hover freq lo - ");
  delay(3000);
  freqLo = analogRead(ANALOGIN2);
  tft.print(freqLo);
  setCursorTFT(4,0);
  tft.print("Hover freq hi - ");
  delay(3000);
  freqHi = analogRead(ANALOGIN2);
  tft.print(freqHi);
  setCursorTFT(6,0);
  tft.print("Calibration Complete");
  setCursorTFT(7,0);
  tft.print("Right to Save");
  setCursorTFT(8,0);
  tft.print("Other to exit");
  
  keyVal = myMiniDuino.pollKeypad();
  while (keyVal == NONE)
    keyVal = myMiniDuino.pollKeypad();
  if (keyVal == RIGHT)
  {
    IRConfigs.freqLoEE = freqLo;
    IRConfigs.freqHiEE = freqHi;
    IRConfigs.volLoEE = volLo;
    IRConfigs.volHiEE = volHi;
    setCursorTFT(9,0);
    tft.print("Saving...");
    EEPROM_writeAnything(0, IRConfigs);
  }
  setCursorTFT(7,0);
  tft.print("                ");
  setCursorTFT(8,0);
  tft.print("                ");
  setCursorTFT(9,0);
  tft.print("                ");
  
}

void theremin(void)
{
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  setCursorTFT(0,0);
  tft.print("Theremin");
  while (myMiniDuino.pollKeypad() != NONE);
  int keyVal = myMiniDuino.pollKeypad();
  while (keyVal == NONE)
  {
    getSetVolFreq();
    setCursorTFT(1,0);
    tft.print(vol128);
    tft.print("  ");
    tft.print(freq128);    
    tft.print("  ");
    keyVal = myMiniDuino.pollKeypad();
  }
}

void viewCal(void)
{
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  setCursorTFT(0,0);
  tft.print("IR Calibration");
  setCursorTFT(1,0);
  tft.print("Hover vol Lo - ");
  tft.print(IRConfigs.volLoEE);
  setCursorTFT(2,0);
  tft.print("Hover vol Hi - ");
  tft.print(IRConfigs.volHiEE);
  setCursorTFT(3,0);
  tft.print("Hover freq Lo - ");
  tft.print(IRConfigs.freqLoEE);
  setCursorTFT(4,0);
  tft.print("Hover freq Hi - ");
  tft.print(IRConfigs.freqHiEE);
  setCursorTFT(5,0);
  tft.print("Select to exit");
  while (myMiniDuino.pollKeypad() == NONE);
}

