////////////////////////////////////////////////////////////////////////////////////
// DisplayTestMenu() - Display the Test Menu.
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// Menu structure
////////////////////////////////////////////////////////////////////////////////////

struct menuStruc
{
  int CURRENT_MENU_PTR;
  char menuString[21];
  int rowNumber;
  int UP_MENU_PTR;
  int DOWN_MENU_PTR;
  int LEFT_MENU_PTR;
  int RIGHT_MENU_PTR;
  void (*pt2Function)(void);
  int SEL_MENU_PTR;
};

const char * menuHeader     = "** Test Menu **";

////////////////////////////////////////////////////////////////////////////////////
// Menu structure - used to generate the navigation menus. Format is
// CURR_MENU,MENU_STRING,DISPLAY_ROW,UP_MENU,DOWN_MENU,LEFT_MENU,RIGHT_MENU,select-execute-fcn-name,RETURN_MENU
// CURR_MENU needs to be ordered in the enums to match the order on the screen
////////////////////////////////////////////////////////////////////////////////////

menuStruc menus[] = 
{
  LOGGER_MENU,      "Run Logger",          2, LOGGER_MENU,      TSTKPD_MENU,      LOGGER_MENU,      LOGGER_MENU,     &do1Wire,     LOGGER_MENU,
  TSTKPD_MENU,      "Test Keypad",         3, LOGGER_MENU,      BACKLITE_MENU,    TSTKPD_MENU,      TSTKPD_MENU,     &testKpd,     TSTKPD_MENU,
  BACKLITE_MENU,    "Set Backlight Level", 4, TSTKPD_MENU,      LOADSTOR_MENU,    BACKLITE_MENU,    BACKLITE_MENU,   &setBLt,      BACKLITE_MENU,
  LOADSTOR_MENU,    "Load/Store Config",   5, BACKLITE_MENU,    LOADSTOR_MENU,    LOADSTOR_MENU,    LOAD_MENU,       &nullFcn,     LOAD_MENU,
  LOAD_MENU,        "Load Config",         2, LOAD_MENU,        STORE_MENU,       LOADSTOR_MENU,    LOAD_MENU,       &loadConfig,  LOAD_MENU,
  STORE_MENU,       "Store Config",        3, LOAD_MENU,        STORE_MENU,       STORE_MENU,       STORE_MENU,      &storeConfig, STORE_MENU,
};

////////////////////////////////////////////////////////////////////////////////////
// Refresh the menu
////////////////////////////////////////////////////////////////////////////////////

int menuRefresh(void)
{
  int nextLine, lastLine;
  tft.fillRect(0,0,127,70,ST7735_BLACK);
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
// menuNav - Uses the joystick switch to move around the menu
////////////////////////////////////////////////////////////////////////////////////

int menuNav(void)
{
  int keyState;
  do
  {
    keyState = myOneWireLogger.pollKeypad();
  }
  while (keyState == NONE);
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
    keyState = myOneWireLogger.pollKeypad();
  }
  while (keyState != NONE);
}

////////////////////////////////////////////////////////////////////////////////////
// displayMenuLine
////////////////////////////////////////////////////////////////////////////////////

void displayMenuLine(int row, int fontColor, int backgroundColor, char * menuString, int selected)
{
  setCursorTFT(row,0);
  tft.setTextColor(fontColor,backgroundColor);
  tft.print(menuString);
  return;
}


