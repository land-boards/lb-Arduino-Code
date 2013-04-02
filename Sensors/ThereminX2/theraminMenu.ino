////////////////////////////////////////////////////////////
// testMenu() - 
////////////////////////////////////////////////////////////

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
  THEREMIN_MENU,    "Run Theremin",     2, THEREMIN_MENU,    CALIBR_MENU,     THEREMIN_MENU,    THEREMIN_MENU,   &theremin,   THEREMIN_MENU,
  CALIBR_MENU,      "Calibrate IR",     3, THEREMIN_MENU,    CAL_LEV_MENU,    CALIBR_MENU,      CALIBR_MENU,     &calibIR,    CALIBR_MENU,
  CAL_LEV_MENU,     "Calibrate Level",  4, CALIBR_MENU,      VIEWCAL_MENU,    CAL_LEV_MENU,     CAL_LEV_MENU,    &calibLevel, CAL_LEV_MENU,
  VIEWCAL_MENU,     "View Calibr",      5, CAL_LEV_MENU,     TESTKEYPAD_MENU, VIEWCAL_MENU,     VIEWCAL_MENU,    &viewCal,    VIEWCAL_MENU,
  TESTKEYPAD_MENU,  "Test Keypad",      6, VIEWCAL_MENU,     TESTIR_MENU,     TESTKEYPAD_MENU,  TESTKEYPAD_MENU, &testKeyPad, TESTKEYPAD_MENU,
  TESTIR_MENU,      "Test IR distance", 7, TESTKEYPAD_MENU,  SETVOL_MENU,     TESTIR_MENU,      TESTIR_MENU,     &testIR,     TESTIR_MENU,
  SETVOL_MENU,      "Set Volume",       8, TESTIR_MENU,      SETFRQ_MENU,     SETVOL_MENU,      SETVOL_MENU,     &setVol,     SETVOL_MENU,
  SETFRQ_MENU,      "Set Frequency",    9, SETVOL_MENU,      SETFRQ_MENU,     SETFRQ_MENU,      SETFRQ_MENU,     &setFreq,    SETFRQ_MENU,
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
    keyState = myMiniDuino.pollKeypad();
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
    keyState = myMiniDuino.pollKeypad();
  }
  while (keyState != NONE);
}

////////////////////////////////////////////////////////////
// displayMenuLine
////////////////////////////////////////////////////////////

void displayMenuLine(int row, int fontColor, int backgroundColor, char * menuString, int selected)
{
  setCursorTFT(row,0);
  tft.setTextColor(fontColor,backgroundColor);
  tft.print(menuString);
  return;
}

