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

//////////////////////////////////////////////////////////////////////////////
// cfg18b20()
//////////////////////////////////////////////////////////////////////////////

void cfg18b20(void)
{
    uint8_t i;
  uint8_t data[12];
  uint8_t addr[8];

  if ( !ds.search(addr)) 
  {
    ds.reset_search();
    delay(250);
    firstRun=0;
    sensorNumber=0;
    return;
  }

  firstRun=0;

  if (OneWire::crc8(addr, 7) != addr[7]) 
  {
    return;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);         // start conversion, with parasite power on at the end
  delay(750);               // maybe 750ms is enough, maybe not

  ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  for ( i = 0; i < 9; i++) 
  {           // we need 9 bytes
    data[i] = ds.read();
  }
  
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  tft.print("Dump scratchpad");
  for ( i = 0; i < 9; i++) 
  {           // dump the scratchpad
    setDisplayCursor(i+1, 0);
    if ((data[i] & 0xf0) == 0)
      tft.print("0");
    tft.print(data[i],HEX);
    tft.print(" ");
  }
  while (myOneWireLogger.pollKeypad() == NONE);  
}

