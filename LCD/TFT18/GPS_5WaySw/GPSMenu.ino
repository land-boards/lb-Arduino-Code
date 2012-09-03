////////////////////////////////////////////////////////////
// geocacheMenu() - 
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// Menu structure
////////////////////////////////////////////////////////////////////////////////////

struct menuStruc
{
  int CURRENT_MENU_PTR;
  char menuString[20];
  int rowNumber;
  int UP_MENU_PTR;
  int DOWN_MENU_PTR;
  int LEFT_MENU_PTR;
  int RIGHT_MENU_PTR;
  void (*pt2Function)(void);
  int SEL_MENU_PTR;
};

////////////////////////////////////////////////////////////////////////////////////
// Menu structure - used to generate the navigation menus. Format is
// CURR_MENU,MENU_STRING,DISPLAY_ROW,UP_MENU,DOWN_MENU,LEFT_MENU,RIGHT_MENU,select-execute-fcn-name,RETURN_MENU
////////////////////////////////////////////////////////////////////////////////////

menuStruc menus[] = 
{
  MONGPSLOCN_MENU,   "Show Location",       2, MONGPSLOCN_MENU,   MONGPSCLK_MENU,   MONGPSLOCN_MENU, MONGPSLOCN_MENU,   &readGPS,  MONGPSLOCN_MENU,
  MONGPSCLK_MENU,    "Clock",               3, MONGPSLOCN_MENU,   MANWAYPTS_MENU,   MONGPSCLK_MENU,  MONGPSCLK_MENU,    &GPSClock, MONGPSCLK_MENU,
  MANWAYPTS_MENU,    "Waypoint Menu",       4, MONGPSCLK_MENU,    LOGGING_MENU,     MANWAYPTS_MENU,  GOTOWAYPTS_MENU,   &nullFcn,  GOTOWAYPTS_MENU,
  LOGGING_MENU,      "Logging Menu",        5, MANWAYPTS_MENU,    LOGGING_MENU,     LOGGING_MENU,    STARTLOGGING_MENU, &nullFcn,  STARTLOGGING_MENU,
  GOTOWAYPTS_MENU,   "Go to Waypoint",      2, GOTOWAYPTS_MENU,   DOWNLDWAYS_MENU,  MANWAYPTS_MENU,  GOTOWAYPTS_MENU,   &goWays,   GOTOWAYPTS_MENU,
  DOWNLDWAYS_MENU,   "Download Waypoints",  3, GOTOWAYPTS_MENU,   SETACTWAYS_MENU,  MANWAYPTS_MENU,  DOWNLDWAYS_MENU,   &dlWays,   DOWNLDWAYS_MENU,
  SETACTWAYS_MENU,   "Set Active Waypoint", 4, DOWNLDWAYS_MENU,   SHOWWAYPTS_MENU,  MANWAYPTS_MENU,  SETACTWAYS_MENU,   &setWay,   SETACTWAYS_MENU,
  SHOWWAYPTS_MENU,   "Show Waypoints",      5, SETACTWAYS_MENU,   SHOWWAYPTS_MENU,  MANWAYPTS_MENU,  SHOWWAYPTS_MENU,   &shWays,   SHOWWAYPTS_MENU,
  STARTLOGGING_MENU, "Start Log",           2, STARTLOGGING_MENU, STOPLOGGING_MENU, LOGGING_MENU,    STARTLOGGING_MENU, &startLog, STARTLOGGING_MENU,
  STOPLOGGING_MENU,  "Stop Log",            3, STARTLOGGING_MENU, DUMPLOGFILE_MENU, LOGGING_MENU,    STOPLOGGING_MENU,  &stopLog,  STOPLOGGING_MENU,
  DUMPLOGFILE_MENU,  "Dump Log",            4, STOPLOGGING_MENU,  CLRLOGFILE_MENU,  LOGGING_MENU,    DUMPLOGFILE_MENU,  &dumpLog,  DUMPLOGFILE_MENU,
  CLRLOGFILE_MENU,   "Clear Log",           5, DUMPLOGFILE_MENU,  CLRLOGFILE_MENU,  LOGGING_MENU,    CLRLOGFILE_MENU,   &clrLog,  CLRLOGFILE_MENU,
};

////////////////////////////////////////////////////////////////////////////////////
// Refresh the menu
////////////////////////////////////////////////////////////////////////////////////

int menuRefresh(void)
{
  int nextLine, lastLine;
  tft.fillRect(0,10,128,80,ST7735_BLACK);
#ifdef SERIAL_DEBUG
  Serial.print(F("menuState = "));
  Serial.print(menuState);
  Serial.print(F(",String="));
  Serial.print(menus[menuState].menuString);
  Serial.print(F(",RowNumber = "));
  Serial.println(menus[menuState].rowNumber);
#endif
  setCursorTFT((menus[menuState].rowNumber)-1,0);
  tft.setTextColor(ST7735_WHITE,ST7735_BLUE);
  tft.print(menus[menuState].menuString);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  lastLine = menuState;
  while ((menus[lastLine].UP_MENU_PTR != menus[lastLine].CURRENT_MENU_PTR) && (menus[menuState].rowNumber != 1))
  {
    lastLine = menus[lastLine].UP_MENU_PTR;
    setCursorTFT(menus[lastLine].rowNumber-1,0);
    tft.print(menus[lastLine].menuString);
#ifdef SERIAL_DEBUG
    Serial.print(F("UP-1"));
    Serial.println(menus[lastLine].menuString);
#endif
  }
  nextLine = menuState;
  while (menus[nextLine].DOWN_MENU_PTR != menus[nextLine].CURRENT_MENU_PTR)
  {
    nextLine = menus[nextLine].DOWN_MENU_PTR;
    setCursorTFT(menus[nextLine].rowNumber-1,0);
    tft.print(menus[nextLine].menuString);
#ifdef SERIAL_DEBUG
    Serial.print(F("Down,"));
    Serial.print(menus[nextLine].menuString);
    Serial.print(F(",nextLine="));
    Serial.println(nextLine);
#endif
  }
}

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////

void nullFcn(void)
{

}

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////

int menuNav(void)
{
  int keyState;
  do
  {
    keyState = mySwitch.checkKeypad();
  }
  while (keyState == NOKEY);
  switch(keyState)
  {
  case UP:
    menuState = menus[menuState].UP_MENU_PTR;
    break;
  case DOWN:
    menuState = menus[menuState].DOWN_MENU_PTR;
    break;
  case LEFT:
    menuState = menus[menuState].LEFT_MENU_PTR;
    break;
  case RIGHT:
    menuState = menus[menuState].RIGHT_MENU_PTR;
    break;
  case SELECT:
    // run the selected function
    void (*foo)(void);
    foo = menus[menuState].pt2Function;
    foo();
    menuState = menus[menuState].SEL_MENU_PTR;
    break;
  }
  do
  {
    delay(10);
    keyState = mySwitch.checkKeypad();
  }
  while (keyState != NOKEY);
}

