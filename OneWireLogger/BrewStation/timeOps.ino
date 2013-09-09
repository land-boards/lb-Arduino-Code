//////////////////////////////////////////////////////////////////////////////
// timeOps - Menu operations relating to the Real Time Clock
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// void displayTime(void)
//////////////////////////////////////////////////////////////////////////////

void displayTime(void)
{
  int key;
  int lastSecond;
  tft.fillScreen(ST7735_BLACK);
  tft.setTextSize(2);
  DateTime now = RTC.now();
  do
  {
    lastSecond = now.second();
    tft.fillRect(0,8,127,63,ST7735_BLACK);
    setCursorTFT(1, 0);
    tft.print(now.year(), DEC);
    tft.print('/');
    tft.print(now.month(), DEC);
    tft.print('/');
    tft.print(now.day(), DEC);
    setCursorTFT(4, 0);
    tft.print(now.hour(), DEC);
    tft.print(':');
    if (now.minute() < 10)
      tft.print("0");
    tft.print(now.minute(), DEC);
    tft.print(':');
    if (now.second() < 10)
      tft.print("0");
    tft.print(now.second(), DEC);
    while (now.second() == lastSecond)
      now = RTC.now();
    key = myOneWireLogger.pollKeypad();
  }
  while (key == NONE);
  do
  {
    key = myOneWireLogger.pollKeypad();
    delay(20);
  }
  while (key != NONE);
  tft.setTextSize(1);
}

//////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////

enum editModes
{
  EDITYEAR,
  EDITMONTH,
  EDITDAY,
  EDITHOUR,
  EDITMINUTE,
  EDITSECOND,
};

//////////////////////////////////////////////////////////////////////////////
// void setTime(void)
//////////////////////////////////////////////////////////////////////////////

void setTime(void)
{
  int key;
  int cursX, cursY;
  int rtcYear, rtcMonth, rtcDay, rtcHour, rtcMinute, rtcSecond;
  int timeState = EDITYEAR;
  int blockOffOn = 1;
  DateTime now = RTC.now();  // Snapshot the date at the start
  rtcYear = now.year();
  rtcMonth = now.month();
  rtcDay = now.day();
  rtcHour = now.hour();
  rtcMinute = now.minute();
  rtcSecond = now.second();
  tft.fillScreen(ST7735_BLACK);
  setCursorTFT(1, 0);
  tft.print(F("YYYY = "));
  tft.print(rtcYear, DEC);
  setCursorTFT(2, 0);
  tft.print(F("MM   = "));
  tft.print(rtcMonth, DEC);
  setCursorTFT(3, 0);
  tft.print(F("DD =   "));
  tft.print(rtcDay, DEC);
  setCursorTFT(4, 0);
  tft.print(F("HH =   "));
  tft.print(rtcHour, DEC);
  setCursorTFT(5, 0);
  tft.print(F("MM =   "));
  tft.print(rtcMinute, DEC);
  setCursorTFT(6, 0);
  tft.print(F("SS =   "));
  tft.print(rtcSecond, DEC);
  setCursorTFT(7, 0);
  tft.print(F("Save and Exit"));
  setCursorTFT(8, 0);
  tft.print(F("Exit without saving"));
  cursX = 1;
  cursY = 11;
  do
  {
    setCursorTFT(cursX, cursY);
    blockOffOn ^= 0x1;
    if (blockOffOn == 0)
      
    key = myOneWireLogger.pollKeypad();
  }
  while (key == NONE);
  do
  {
    key = myOneWireLogger.pollKeypad();
    delay(20);
  } 
  while (key != NONE);
}


