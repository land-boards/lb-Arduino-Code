//////////////////////////////////////////////////////////////////////////////
// timeOps - Menu operations relating to the Real Time Clock
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////

enum timeState_t
{
  SET_YEAR,
  SET_MONTH,
  SET_DAY,
  SET_HOUR,
  SET_MIN,
  SET_SEC,
  SAVE_TIME,
  EXIT_TIME,
} 
;

//////////////////////////////////////////////////////////////////////////////
// void setTime(void)
//////////////////////////////////////////////////////////////////////////////

void setTime(void)
{
  signed char key;
  int currYear, currMonth, currDay, currHour, currMin, currSec;
  timeState_t timeStat = SET_YEAR;
  tft.fillScreen(ST7735_BLACK);
  tft.fillScreen(ST7735_BLACK);
  // read the rtc
  DateTime now = RTC.now();
  currYear = now.year();
  currMonth = now.month();
  currDay = now.day();
  currHour = now.hour();
  currMin = now.minute();
  currSec = now.second();

  setCursorTFT(1, 0);
  tft.print(currYear, DEC);
  tft.print(':');
  setCursorTFT(2, 0);
  if (currMonth < 10)
    tft.print('0');
  tft.print(currMonth, DEC);
  tft.print(" :");
  setCursorTFT(3, 0);
  if (currDay < 10)
    tft.print('0');
  tft.print(currDay, DEC);
  tft.print("  :");
  setCursorTFT(4, 0);
  if (currHour < 10)
    tft.print('0');
  tft.print(currHour, DEC);
  tft.print("  :");
  setCursorTFT(5, 0);
  if (currMin < 10)
    tft.print('0');
  tft.print(currMin, DEC);
  tft.print("  :");
  setCursorTFT(6, 0);
  if (currSec < 10)
    tft.print('0');
  tft.print(currSec, DEC);
  tft.print("  :");
  setCursorTFT(7, 0);
  tft.print("SAVE:");
  setCursorTFT(8, 0);
  tft.print(F("Exit:"));

  setCursorTFT(1, 5);
  tft.print("<");

  do
  {
    key = myOneWireLogger.pollKeypad();
    if (key != NONE)
    {
      switch (timeStat)
      {
      case SET_YEAR:
        {
          if (key == DOWN)
          {
            setCursorTFT(1, 5);
            tft.print("  ");
            setCursorTFT(2, 5);
            tft.print("<");
            timeStat = SET_MONTH;
          }
          else if (key == SELECT)
          {
            setCursorTFT(1, 0);
            tft.print(currYear);
            while(myOneWireLogger.pollKeypad() == SELECT);
            do
            {
              key = myOneWireLogger.pollKeypad();
              switch (key)
              {
              case UP: 
                currYear++;
                break;
              case DOWN:
                currYear--;
                break;
              }
              setCursorTFT(1, 0);
              tft.print(currYear);
              delay(250);
            }
            while (myOneWireLogger.pollKeypad() != SELECT);
          }
          break;
        }
      case SET_MONTH:
        {
          if (key == DOWN)
          {
            setCursorTFT(2, 5);
            tft.print(" ");
            setCursorTFT(3, 5);
            tft.print("<");
            timeStat = SET_DAY;
          }
          else if (key == UP)
          {
            setCursorTFT(1, 5);
            tft.print("<");
            setCursorTFT(2, 5);
            tft.print(" ");
            timeStat = SET_YEAR;
          }
          break;
        }
      case SET_DAY:
        {
          if (key == DOWN)
          {
            setCursorTFT(3, 5);
            tft.print(" ");
            setCursorTFT(4, 5);
            tft.print("<");
            timeStat = SET_HOUR;
          }
          else if (key == UP)
          {
            setCursorTFT(2, 5);
            tft.print("<");
            setCursorTFT(3, 5);
            tft.print(" ");
            timeStat = SET_MONTH;
          }
          break;
        }
      case SET_HOUR:
        {
          if (key == DOWN)
          {
            setCursorTFT(4, 5);
            tft.print(" ");
            setCursorTFT(5, 5);
            tft.print("<");
            timeStat = SET_MIN;
          }
          else if (key == UP)
          {
            setCursorTFT(3, 5);
            tft.print("<");
            setCursorTFT(4, 5);
            tft.print(" ");
            timeStat = SET_DAY;
          }
          break;
        }
      case SET_MIN:
        {
          if (key == DOWN)
          {
            setCursorTFT(5, 5);
            tft.print(" ");
            setCursorTFT(6, 5);
            tft.print("<");
            timeStat = SET_SEC;
          }
          else if (key == UP)
          {
            setCursorTFT(4, 5);
            tft.print("<");
            setCursorTFT(5, 5);
            tft.print(" ");
            timeStat = SET_HOUR;
          }
          break;
        }
      case SET_SEC:
        {
          if (key == DOWN)
          {
            setCursorTFT(6, 5);
            tft.print(" ");
            setCursorTFT(7, 5);
            tft.print("<");
            timeStat = SAVE_TIME;
          }
          else if (key == UP)
          {
            setCursorTFT(5, 5);
            tft.print("<");
            setCursorTFT(6, 5);
            tft.print(" ");
            timeStat = SET_MIN;
          }
          break;
        }
      case SAVE_TIME:
        {
          if (key == DOWN)
          {
            setCursorTFT(7, 5);
            tft.print(" ");
            setCursorTFT(8, 5);
            tft.print("<");
            timeStat = EXIT_TIME;
          }
          else if (key == UP)
          {
            setCursorTFT(6, 5);
            tft.print("<");
            setCursorTFT(7, 5);
            tft.print(" ");
            timeStat = SET_SEC; 
          }
          else if (key == SELECT)
          {
            return;
          }
          break;
        }
      case EXIT_TIME:
        {
          if (key == UP)
          {
            setCursorTFT(7, 5);
            tft.print("<");
            setCursorTFT(8, 5);
            tft.print(" ");
            timeStat = SAVE_TIME;
          }
          else if (key == SELECT)
            return;
          break;
        }
      }
      do
        key = myOneWireLogger.pollKeypad();
      while (key != NONE);
    }
    delay(100);
  }
  while (key == NONE);
}

