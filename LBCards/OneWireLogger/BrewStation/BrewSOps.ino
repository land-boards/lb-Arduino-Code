//////////////////////////////////////////////////////////////////////////////
// brewOps - Menu Operations
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// steep()
//////////////////////////////////////////////////////////////////////////////

void steep(void)
{
  uint8_t key, timerStarted = 0;
  int32_t startTime, endTime, currentTime;
  //, remainingTime;
  clearDisplay();
  tft.setTextSize(3);
  tft.print(F("*Steep*"));
  do
  {
    readNext1Wire();
    if (sensorNumber > 0)
    {
      if (temps1Wire[sensorNumber-1] < 150.0)  // Steep starts at 150 degrees F
      {
        timerStarted = 0;
        setDisplayCursor(sensorNumber+2,0);
        tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
        tft.print(F("       "));
        tft.setTextColor(ST7735_BLACK,ST7735_WHITE);
        tft.fillRect(0,64,128,72,ST7735_WHITE);
      }
      else if (temps1Wire[sensorNumber-1] < 165.0)  // Steep is lower than 165 deg F
      {
        if (timerStarted == 0)
        {
          startTime = millis() / 1000;
          endTime = startTime + (20*60); // time is 1200 seconds 20*60
          timerStarted = 1;
        }
        setDisplayCursor(sensorNumber+2,0);
        currentTime = millis() / 1000;
        if (currentTime <= endTime)
          tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
        else
          tft.setTextColor(ST7735_WHITE, ST7735_RED);
        tft.print(currentTime - endTime);
        tft.print(F(" s"));
        if ((currentTime - endTime) < 1000)
          tft.print(F(" "));
        else if ((currentTime - endTime) < 100)
          tft.print(F("  "));
        else if ((currentTime - endTime) < 10)
          tft.print(F("  "));
        tft.setTextColor(ST7735_WHITE,ST7735_BLUE);
        tft.fillRect(0,64,128,72,ST7735_BLUE);
      }
      else    // Overtemp gest shows as white characters on a red background
      {
        tft.setTextColor(ST7735_WHITE,ST7735_RED);
        tft.fillRect(0,64,128,72,ST7735_RED);
      }
      setDisplayCursor(sensorNumber+8,0);
      if (temps1Wire[sensorNumber-1] < 100.0)
        tft.print(F(" "));
      tft.print(temps1Wire[sensorNumber-1]);
      tft.print(F("F "));
    }
    myOneWireLogger.delayAvailable(250);
    key = myOneWireLogger.pollKeypad();
  }
  while (key == NONE);
  tft.setTextSize(1);
  tft.fillScreen(ST7735_BLACK);
}

//////////////////////////////////////////////////////////////////////////////
// boil() - Step by step from start to boil
//////////////////////////////////////////////////////////////////////////////

void boil(void)
{
  uint8_t key;
  clearDisplay();
  tft.setTextSize(3);
  tft.print(F("*Boil*"));
  do
  {
    readNext1Wire();
    if (sensorNumber > 0)
    {
      if (temps1Wire[sensorNumber-1] < 190.0)
      {
        tft.setTextColor(ST7735_BLACK,ST7735_WHITE);
        tft.fillRect(0,64,128,80,ST7735_WHITE);
      }
      else if (temps1Wire[sensorNumber-1] < 204.0)
      {
        tft.setTextColor(ST7735_WHITE,ST7735_BLUE);
        tft.fillRect(0,64,128,80,ST7735_BLUE);
      }
      else
      {
        tft.setTextColor(ST7735_WHITE,ST7735_RED);
        tft.fillRect(0,64,128,80,ST7735_RED);
      }
      setDisplayCursor(sensorNumber+8,0);
      if (temps1Wire[sensorNumber-1] < 100.0)
        tft.print(" ");
      tft.print(temps1Wire[sensorNumber-1]);
      tft.print(F("F "));
    }
    myOneWireLogger.delayAvailable(250);
    key = myOneWireLogger.pollKeypad();
  }
  while (key == NONE);
  tft.setTextSize(1);
  tft.fillScreen(ST7735_BLACK);
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

