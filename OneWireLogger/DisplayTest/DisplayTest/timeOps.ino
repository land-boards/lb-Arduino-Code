//////////////////////////////////////////////////////////////////////////////
// timeOps - Menu operations relating to the Real Time Clock
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// void displayTime(void)
//////////////////////////////////////////////////////////////////////////////

void displayTime(void)
{
  int key;
  tft.fillScreen(ST7735_BLACK);
  tft.setTextSize(2);
  setCursorTFT(1, 0);
  DateTime now = RTC.now();
  tft.print(now.year(), DEC);
  tft.print('/');
  tft.print(now.month(), DEC);
  tft.print('/');
  tft.print(now.day(), DEC);
  setCursorTFT(4, 0);
  tft.print(' ');
  tft.print(now.hour(), DEC);
  tft.print(':');
  tft.print(now.minute(), DEC);
  tft.print(':');
  tft.print(now.second(), DEC);
  tft.setTextSize(1);
  delay(1500);
  do
  {
    key = myOneWireLogger.pollKeypad();
    delay(20);
  }
 while (key == NONE);
 do
 {
   key = myOneWireLogger.pollKeypad();
   delay(20);
 }
 while (key != NONE);

}

//////////////////////////////////////////////////////////////////////////////
// void setTime(void)
//////////////////////////////////////////////////////////////////////////////

void setTime(void)
{
  DateTime now = RTC.now();
  tft.print(now.year(), DEC);
  tft.print('/');
  tft.print(now.month(), DEC);
  tft.print('/');
  tft.print(now.day(), DEC);
  setCursorTFT(4, 0);
  tft.print(' ');
  tft.print(now.hour(), DEC);
  tft.print(':');
  tft.print(now.minute(), DEC);
  tft.print(':');
  tft.print(now.second(), DEC);
  
}

