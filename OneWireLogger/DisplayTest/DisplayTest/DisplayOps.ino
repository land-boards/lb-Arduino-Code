//////////////////////////////////////////////////////////////////////////////
// menuOps - Menu Operations
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// testKeyPad() - Verify keypad works.
// All directions plus select display the direction.
// Holding select for longer than a few seconds will exit this test
//////////////////////////////////////////////////////////////////////////////

void testKpd(void)
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
    key = myOneWireLogger.pollKeypad();
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
  while (myOneWireLogger.pollKeypad() == SELECT);
}

//////////////////////////////////////////////////////////////////////////////
// do1Wire() - Run the 1 Wire Interface
//////////////////////////////////////////////////////////////////////////////

void do1Wire(void)
{
  int key;
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  setCursorTFT(0,0);
  tft.print("Do 1 Wire");
  do
  {
    key = myOneWireLogger.pollKeypad();
  }
 while (key == NONE); 
}

//////////////////////////////////////////////////////////////////////////////
// setBLt() - Set the backlight level
//////////////////////////////////////////////////////////////////////////////

void setBLt(void)
{
  int key;
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  setCursorTFT(0,0);
  tft.print("Set Backlight");
  do
  {
    key = myOneWireLogger.pollKeypad();
    delay(200);
    if ((key == DOWN) && (IZConfigs.bll <= 250))
      IZConfigs.bll += 10;
    else if ((key == UP) && (IZConfigs.bll >= 10))
      IZConfigs.bll -= 10;
    analogWrite(BACKLIGHT, IZConfigs.bll);
    setCursorTFT(1,0);
    tft.print("    ");
    setCursorTFT(1,0);
    tft.print(250-IZConfigs.bll);
  }
 while (key != SELECT);
// EEPROM_writeAnything(0, IZConfigs);

}


//////////////////////////////////////////////////////////////////////////////
// void nullFcn(void)
//////////////////////////////////////////////////////////////////////////////

void nullFcn(void) {  }

//////////////////////////////////////////////////////////////////////////////
// void loadConfig(void)
//////////////////////////////////////////////////////////////////////////////

void loadConfig(void)
{
  int key;
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  setCursorTFT(0,0);
  tft.print("Load Config.");
  do
  {
    key = myOneWireLogger.pollKeypad();
    delay(200);
  }
 while (key != SELECT);
}

//////////////////////////////////////////////////////////////////////////////
// void storeConfig(void)
//////////////////////////////////////////////////////////////////////////////

void storeConfig(void)
{
  int key;
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  setCursorTFT(0,0);
  tft.print("Store Config.");
  do
  {
    key = myOneWireLogger.pollKeypad();
    delay(200);
  }
 while (key != SELECT);
}

