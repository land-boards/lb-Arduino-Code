//////////////////////////////////////////////////////////////////////////////
// timeOps - Menu operations relating to the Real Time Clock
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////

void printLeadingZero(unsigned char checkNum)
{
  if (checkNum < 10)
   tft.print(F("0")); 
}

//////////////////////////////////////////////////////////////////////////////
// showTimeOnLine() - Refresh the time screen and highlight the selected position
//////////////////////////////////////////////////////////////////////////////

int showTimeOnLine(int highlightPosition)
{
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);

  setCursorTFT(1, 0);
  tft.print(currYear);
  tft.print("/");
  printLeadingZero(currMonth);
  tft.print(currMonth);
  tft.print("/");
  printLeadingZero(currDay);
  tft.print(currDay);
  tft.print("/");
  printLeadingZero(currHour);
  tft.print(currHour);
  tft.print(":");
  printLeadingZero(currMin);
  tft.print(currMin);
  tft.print(":");
  printLeadingZero(currSec);
  tft.print(currSec);
  setCursorTFT(2, 0);
  tft.print("SAVE");
  setCursorTFT(3, 0);
  tft.print("EXIT");
  switch (highlightPosition)
  {
    case VIEW_YEAR:
    {
      tft.setTextColor(ST7735_WHITE,ST7735_RED);
      setCursorTFT(1, 0);
      tft.print(currYear);
    }
    break; 
    case VIEW_MONTH:
    {
      tft.setTextColor(ST7735_WHITE,ST7735_RED);
      setCursorTFT(1, 5);
      printLeadingZero(currMonth);
      tft.print(currMonth);
    }
    break;
    case VIEW_DAY:
    {
      tft.setTextColor(ST7735_WHITE,ST7735_RED);
      setCursorTFT(1, 8);
      printLeadingZero(currDay);
      tft.print(currDay);
    }
    break;
    case VIEW_HOUR:
    {
      tft.setTextColor(ST7735_WHITE,ST7735_RED);
      setCursorTFT(1, 11);
      printLeadingZero(currHour);
      tft.print(currHour);
    }
    break;
    case VIEW_MIN:
    {
      tft.setTextColor(ST7735_WHITE,ST7735_RED);
      setCursorTFT(1, 14);
      printLeadingZero(currMin);
      tft.print(currMin);
    }
    break;
    case VIEW_SEC:
    {
      tft.setTextColor(ST7735_WHITE,ST7735_RED);
      setCursorTFT(1, 17);
      printLeadingZero(currSec);
      tft.print(currSec);
    }
    break;
    case SET_YEAR:
    {
      tft.setTextColor(ST7735_WHITE,ST7735_BLUE);
      setCursorTFT(1, 0);
      tft.print(currYear);
    }
    break;
    case SET_MONTH:
    {
      tft.setTextColor(ST7735_WHITE,ST7735_BLUE);
      setCursorTFT(1, 5);
      printLeadingZero(currMonth);
      tft.print(currMonth);
    }
    break;
    case SET_DAY:
    {
      tft.setTextColor(ST7735_WHITE,ST7735_BLUE);
      setCursorTFT(1, 8);
      printLeadingZero(currDay);
      tft.print(currDay);
    }
    break;
    case SET_HOUR:
    {
      tft.setTextColor(ST7735_WHITE,ST7735_BLUE);
      setCursorTFT(1, 11);
      printLeadingZero(currHour);
      tft.print(currHour);
    }
    break;
    case SET_MINUTE:
    {
      tft.setTextColor(ST7735_WHITE,ST7735_BLUE);
      setCursorTFT(1, 14);
      printLeadingZero(currMin);
      tft.print(currMin);
    }
    break;
    case SET_SEC:
    {
      tft.setTextColor(ST7735_WHITE,ST7735_BLUE);
      setCursorTFT(1, 17);
      printLeadingZero(currSec);
      tft.print(currSec);
    }
    break;
    case SAVE_TIME:
    {
      tft.setTextColor(ST7735_WHITE,ST7735_RED);
      setCursorTFT(2, 0);
      tft.print(F("SAVE"));
    }
    break;
    case EXIT_TIME:
    {
      tft.setTextColor(ST7735_WHITE,ST7735_RED);
      setCursorTFT(3, 0);
      tft.print(F("EXIT"));
    }
    break;
  }
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  return(highlightPosition);
}

//////////////////////////////////////////////////////////////////////////////
// void setTime(void)
//////////////////////////////////////////////////////////////////////////////

void setTime(void)
{
  DateTime now;
  signed char key;
  int timeStat = VIEW_YEAR;
  clearTFT();
  tft.print(F("YYYY MM DD HH MM SS"));
  // read the rtc
  setRTCTime = RTC.now();
  currYear = setRTCTime.year();
  currMonth = setRTCTime.month();
  currDay = setRTCTime.day();
  currHour = setRTCTime.hour();
  currMin = setRTCTime.minute();
  currSec = setRTCTime.second();
  showTimeOnLine(VIEW_YEAR);
  setCursorTFT(5, 0);
  tft.print(F("Arrows to chose"));
  setCursorTFT(6, 0);
  tft.print(F("Select to edit"));

  do
  {
    key = myOneWireLogger.pollKeypad();
    if (key != NONE)
    {
      switch (timeStat)
      {
        case VIEW_YEAR:
        {
          switch (key)
          {
            case DOWN:
              timeStat = showTimeOnLine(SAVE_TIME);
              break;
            case RIGHT:
              timeStat = showTimeOnLine(VIEW_MONTH);
              break;
            case SELECT:
              timeStat = showTimeOnLine(SET_YEAR);
              break;
          }
        }
        break;
        case VIEW_MONTH:
        {
          switch (key)
          {
            case DOWN:
              timeStat = showTimeOnLine(SAVE_TIME);
              break;
            case RIGHT:
              timeStat = showTimeOnLine(VIEW_DAY);
              break;
            case LEFT:
              timeStat = showTimeOnLine(VIEW_YEAR);
              break;
            case SELECT:
              timeStat = showTimeOnLine(SET_MONTH);
              break;
          }
        }
        break;
        case VIEW_DAY:
        {
          switch (key)
          {
            case DOWN:
              timeStat = showTimeOnLine(SAVE_TIME);
              break;
            case RIGHT:
              timeStat = showTimeOnLine(VIEW_HOUR);
              break;
            case LEFT:
              timeStat = showTimeOnLine(VIEW_MONTH);
              break;
            case SELECT:
              timeStat = showTimeOnLine(SET_DAY);
              break;
          }
        }
        break;
        case VIEW_HOUR:
        {
          switch (key)
          {
            case DOWN:
              timeStat = showTimeOnLine(SAVE_TIME);
              break;
            case RIGHT:
              timeStat = showTimeOnLine(VIEW_MIN);
              break;
            case LEFT:
              timeStat = showTimeOnLine(VIEW_DAY);
              break;
            case SELECT:
              timeStat = showTimeOnLine(SET_HOUR);
              break;
          }
        }
        break;
        case VIEW_MIN:
        {
          switch (key)
          {
            case DOWN:
              timeStat = showTimeOnLine(SAVE_TIME);
              break;
            case RIGHT:
              timeStat = showTimeOnLine(VIEW_SEC);
              break;
            case LEFT:
              timeStat = showTimeOnLine(VIEW_HOUR);
              break;
            case SELECT:
              timeStat = showTimeOnLine(SET_MINUTE);
              break;
          }
        }
        break;
        case VIEW_SEC:
        {
          switch (key)
          {
            case DOWN:
              timeStat = showTimeOnLine(SAVE_TIME);
              break;
            case LEFT:
              timeStat = showTimeOnLine(VIEW_MIN);
              break;
            case SELECT:
              timeStat = showTimeOnLine(SET_SEC);
              break;
          }
        }
        break;
        case SET_YEAR:
        {
          timeStat = showTimeOnLine(SET_YEAR);
          do
          {
            key = myOneWireLogger.pollKeypad();
            switch (key)
            {
            case UP: 
              currYear++;
              timeStat = showTimeOnLine(SET_YEAR);
              delay(250);
              break;
            case DOWN:
              currYear--;
              timeStat = showTimeOnLine(SET_YEAR);
              delay(250);
              break;
            }
          }
          while (myOneWireLogger.pollKeypad() != SELECT);
          timeStat = showTimeOnLine(VIEW_YEAR);
        }
        break;
      case SET_MONTH:
        {
          timeStat = showTimeOnLine(SET_MONTH);
          do
          {
            key = myOneWireLogger.pollKeypad();
            switch (key)
            {
            case UP: 
              if (currMonth < 12)
                currMonth++;
              timeStat = showTimeOnLine(SET_MONTH);
              delay(250);
              break;
            case DOWN:
              if (currMonth > 1)
                currMonth--;
              timeStat = showTimeOnLine(SET_MONTH);
              delay(250);
              break;
            }
          }
          while (myOneWireLogger.pollKeypad() != SELECT);
          timeStat = showTimeOnLine(VIEW_MONTH);
        }
        break;
      case SET_DAY:
        {
          timeStat = showTimeOnLine(SET_DAY);
          do
          {
            key = myOneWireLogger.pollKeypad();
            switch (key)
            {
            case UP: 
              if (currDay < 31)
                currDay++;
              timeStat = showTimeOnLine(SET_DAY);
              delay(250);
              break;
            case DOWN:
              if (currDay > 1)
                currDay--;
              timeStat = showTimeOnLine(SET_DAY);
              delay(250);
              break;
            }
          }
          while (myOneWireLogger.pollKeypad() != SELECT);
          timeStat = showTimeOnLine(VIEW_DAY);
       }
        break;
      case SET_HOUR:
        {
          timeStat = showTimeOnLine(SET_HOUR);
          do
          {
            key = myOneWireLogger.pollKeypad();
            switch (key)
            {
            case UP: 
              if (currHour < 23)
                currHour++;
              timeStat = showTimeOnLine(SET_HOUR);
              delay(250);
              break;
            case DOWN:
              if (currHour > 0)
                currHour--;
              timeStat = showTimeOnLine(SET_HOUR);
              delay(250);
              break;
            }
          }
          while (myOneWireLogger.pollKeypad() != SELECT);
          timeStat = showTimeOnLine(VIEW_HOUR);
        }
        break;
      case SET_MINUTE:
        {
          timeStat = showTimeOnLine(SET_MINUTE);
          do
          {
            key = myOneWireLogger.pollKeypad();
            switch (key)
            {
            case UP: 
              if (currMin < 59)
                currMin++;
              timeStat = showTimeOnLine(SET_MINUTE);
              delay(250);
              break;
            case DOWN:
              if (currMin > 0)
                currMin--;
              timeStat = showTimeOnLine(SET_MINUTE);
              delay(250);
              break;
            }
          }
          while (myOneWireLogger.pollKeypad() != SELECT);
          timeStat = showTimeOnLine(VIEW_MIN);
        }
        break;
      case SET_SEC:
        {
          timeStat = showTimeOnLine(SET_SEC);
          do
          {
            key = myOneWireLogger.pollKeypad();
            switch (key)
            {
            case UP: 
              if (currSec < 59)
                currSec++;
              timeStat = showTimeOnLine(SET_SEC);
              delay(250);
              break;
            case DOWN:
              if (currSec > 0)
                currSec--;
              timeStat = showTimeOnLine(SET_SEC);
              delay(250);
              break;
            }
          }
          while (myOneWireLogger.pollKeypad() != SELECT);
          timeStat = showTimeOnLine(VIEW_SEC);
        }
        break;
      case SAVE_TIME:
        {
          if (key == DOWN)
          {
            timeStat = showTimeOnLine(EXIT_TIME);
          }
          else if (key == UP)
          {
            timeStat = showTimeOnLine(VIEW_YEAR);
          }
          else if (key == SELECT)
          {
            // TBD add save routine here
            RTC.adjust(DateTime(currYear,currMonth, currDay, currHour, currMin, currSec));
            return;
          }
        }
        break;
      case EXIT_TIME:
        {
          if (key == UP)
          {
            timeStat = showTimeOnLine(SAVE_TIME);
          }
          else if (key == SELECT)
            return;
        }
        break;
      }
      do
        key = myOneWireLogger.pollKeypad();
      while (key != NONE);
    }
    myOneWireLogger.delayAvailable(50);
  }
  while (key == NONE);
}

