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
  tft.print(F("*** Start to Boil ***"));
  setCursorTFT(1, 0);
  tft.print(F("2.5G H2O > pot"));
  setCursorTFT(2, 0);
  tft.print(F("Grains > pot"));
  setCursorTFT(3, 0);
  tft.print(F("Heat near high"));
  setCursorTFT(4, 0);
  tft.print(F("Down key to start"));
  while (myOneWireLogger.waitKeyPressed() != DOWN);
  setCursorTFT(5, 0);
  tft.print(F("Waiting for 20 mins"));
  endTime = now.unixtime() + (2*6);
  while (now.unixtime() < endTime)
  {
    setCursorTFT(6, 0);
    tft.print(F("                    "));
    setCursorTFT(6, 0);
    now = RTC.now();
    tft.print((int)(now.unixtime() - endTime));
    tft.print(" secs left");
    delay(750);
  }
  setCursorTFT(7, 0);
  tft.print(F("Set heat to max"));
  setCursorTFT(8, 0);
  tft.print(F("Waiting for boil"));
  while (myOneWireLogger.waitKeyPressed() != DOWN);
  setCursorTFT(9, 0);
  tft.print(F("Turn off heat"));
  setCursorTFT(10, 0);
  tft.print(F("Add malt(s)"));
  setCursorTFT(11, 0);
  tft.print(F("Add 60 min hop(s)"));
  while (myOneWireLogger.waitKeyPressed() != DOWN);
  tft.fillScreen(ST7735_BLACK);
}

//////////////////////////////////////////////////////////////////////////////
// cookHops()
//////////////////////////////////////////////////////////////////////////////

void cookHops(void)
{
  
}

//////////////////////////////////////////////////////////////////////////////
// textWhiteOnBlack() - 
//////////////////////////////////////////////////////////////////////////////

void textWhiteOnBlack(void)
{
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
}

//////////////////////////////////////////////////////////////////////////////////////
// setCursorTFT(int row, int col)
//////////////////////////////////////////////////////////////////////////////////////

void setCursorTFT(int row, int col)
{
  tft.setCursor(col*6, row*10);
}
