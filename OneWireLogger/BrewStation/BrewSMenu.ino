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

const char * menuHeader     = "*** Brew Station  ***";
const char * menuFooter     = "";

////////////////////////////////////////////////////////////////////////////////////
// Menu structure - used to generate the navigation menus. Format is
// CURR_MENU,MENU_STRING,DISPLAY_ROW,UP_MENU,DOWN_MENU,LEFT_MENU,RIGHT_MENU,select-execute-fcn-name,RETURN_MENU
// CURR_MENU needs to be ordered in the enums to match the order on the screen
////////////////////////////////////////////////////////////////////////////////////

menuStruc menus[] =
{
  BREWSTN_MENU,     "Brew Station >",      2, BREWSTN_MENU,     MANTIME_MENU,     BREWSTN_MENU,     BOIL_MENU,        &nullFcn,     BOIL_MENU,
  MANTIME_MENU,     "Time >",              3, BREWSTN_MENU,     MANTIME_MENU,     MANTIME_MENU,     MANTIME_MENU,     &nullFcn,     DISPTIME_MENU,
  BOIL_MENU,        "< Boil Grains",       2, BOIL_MENU,        COOKHOPS_MENU,    BREWSTN_MENU,     BOIL_MENU,        &boil,        COOKHOPS_MENU,
  COOKHOPS_MENU,    "Cook Hops",           3, BOIL_MENU,        COOKHOPS_MENU,    COOKHOPS_MENU,    COOKHOPS_MENU,    &cookHops,    COOKHOPS_MENU,
  DISPTIME_MENU,    "< Display Time",      2, DISPTIME_MENU,    SETTIME_MENU,     MANTIME_MENU,     DISPTIME_MENU,    &displayTime, DISPTIME_MENU,
  SETTIME_MENU,     "Set Time",            3, DISPTIME_MENU,    SETTIME_MENU,     SETTIME_MENU,     SETTIME_MENU,     &setTime,     SETTIME_MENU,
};

////////////////////////////////////////////////////////////////////////////////////
// Refresh the menu
////////////////////////////////////////////////////////////////////////////////////

int menuRefresh(void)
{
  int nextLine, lastLine;
  tft.fillRect(0,0,127,90,ST7735_BLACK);
  setCursorTFT(0,0);
  tft.setTextColor(ST7735_WHITE,ST7735_RED);
  tft.print(menuHeader);
  textWhiteOnBlack();
  setCursorTFT(15,0);
  tft.print(__DATE__);
  tft.print(" ");
  tft.print(__TIME__);
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
  textWhiteOnBlack();
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
  signed char keyState;
#ifdef SERIAL_OUT
  Serial.println("Waiting for a keypress");
#endif
  keyState = myOneWireLogger.waitKeyPressed();
#ifdef SERIAL_OUT
  Serial.print("menuNav: got");
  Serial.println(keyState);
#endif
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

//////////////////////////////////////////////////////////////////////////////
// void nullFcn(void)
//////////////////////////////////////////////////////////////////////////////

void nullFcn(void) {  }
