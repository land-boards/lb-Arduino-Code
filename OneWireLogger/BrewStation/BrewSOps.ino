//////////////////////////////////////////////////////////////////////////////
// brewOps - Menu Operations
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// boil() - Step by step from start to boil
//////////////////////////////////////////////////////////////////////////////

void boil(void)
{
  int key;
  int timer;
  unsigned long endTime;
  DateTime now = RTC.now();
  tft.fillScreen(ST7735_BLACK);
  setCursorTFT(0, 0);
  tft.print(F("*** Boil ***"));
  delay(2000);
}

//////////////////////////////////////////////////////////////////////////////
// cookHops()
//////////////////////////////////////////////////////////////////////////////

void steep(void)
{
  int key;
  int timer;
  unsigned long endTime;
  DateTime now = RTC.now();
  tft.fillScreen(ST7735_BLACK);
  setCursorTFT(0, 0);
  tft.print(F("*** Steep ***"));
  delay(2000);  
}

//////////////////////////////////////////////////////////////////////////////
// serLog()
//////////////////////////////////////////////////////////////////////////////

void serLog(void)
{
  uint8_t key;
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  setDisplayCursor(1, 0);
  tft.print("Serial Log: ");
  setDisplayCursor(2, 0);
  tft.print("Sel=Save,Up/Dn=Chng");
  setDisplayCursor(3, 0);
  tft.print("rt/lf=Exit w/o Save");
  while(1)
  {
    setDisplayCursor(1, 12);
    if (IZConfigs.enableSerLog == 0)
    {
      tft.print("Off");
    }
    else
    {
      tft.print("On ");
    }
    key = myOneWireLogger.pollKeypad();
    if (key == SELECT)
    {
      EEPROM_writeAnything(0, IZConfigs);
      setDisplayCursor(2, 0);
      tft.print("Saving.............");
      setDisplayCursor(3, 0);
      tft.print("                   ");
      delay(1500);
      return;
    }
    else if ((key == LEFT) || (key == RIGHT))
    {
      setDisplayCursor(2, 0);
      tft.print("Exiting w/o Saving.");
      setDisplayCursor(3, 0);
      tft.print("                   ");
      delay(1500);
      return;
    }
    else if ((key == UP) || (key == DOWN))
    {
      IZConfigs.enableSerLog ^= 1;
      delay(50);
      while (myOneWireLogger.pollKeypad() != NONE);
    }
  }
}

