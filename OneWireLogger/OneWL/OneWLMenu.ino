////////////////////////////////////////////////////////////////////////////////////
// OneWLMenu() - Display the One Wire Menu.
// Hardware required are five buttons (Up, Down, Left, Right and Select) plus an LCD.
// The five buttons can be a 5-way switch.
// The menu operations are typically to have up/down move through the displayed items.
// Right or select can call submenus.
// Left can return to the previous menu.
// Select can execute the selected item.
// Use left and right arrows to indicate submenu availability.
// This menu system is fairly lightweight and is strongly geared towards LCDs.
// This menu system allows for submenus to be called from the first menu.
// There are corresponding ENUM values for each of the *_MENU_PTR values.
// The ENUMs need to be ordered in the same order as they appear in the menu structure.
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// Menu structure - The format of the menu system
// Memory size could be improved if the menuString was variable size and 
//  used pointers rather than a fixed array but that would increase complexity.
////////////////////////////////////////////////////////////////////////////////////

struct menuStruc                  // The ENUMs for the *_MENU_PTR values must preceed this
{
  char CURRENT_MENU_PTR;          // The current menu item
  char menuString[LCD_COLUMNS+1]; // The string that gets displayed
  char rowNumber;                 // The row that the string gets displayed on the LCD
  char UP_MENU_PTR;               // What menu gets highlighted when the up arrow is pressed
  char DOWN_MENU_PTR;             // What menu gets highlighted when the down arrow is pressed
  char LEFT_MENU_PTR;             // What menu gets highlighted when the left arrow is pressed
  char RIGHT_MENU_PTR;            // What menu gets highlighted when the right arrow is pressed
  void (*pt2Function)(void);      // Name of the function which gets called when select is pressed
  char SEL_MENU_PTR;              // Menu to display after the selected function complets
};

const char * menuFooter;

////////////////////////////////////////////////////////////////////////////////////
// Menu structure - used to generate the navigation menus. Format is
// CURR_MENU,MENU_STRING,DISPLAY_ROW,UP_MENU,DOWN_MENU,LEFT_MENU,RIGHT_MENU,select-execute-fcn-name,RETURN_MENU
// CURR_MENU needs to be ordered in the enums to match the order on the screen
////////////////////////////////////////////////////////////////////////////////////

menuStruc menus[] = 
{
  LOGGER_MENU,      "Log to screen",       2, LOGGER_MENU,      LOG2SD_MENU,      LOGGER_MENU,      LOGGER_MENU,     &do1Wire,     LOGGER_MENU,
  LOG2SD_MENU,      "Log to SD card > ",   3, LOGGER_MENU,      LOADSTOR_MENU,    LOG2SD_MENU,      APPENDSD_MENU,   &nullFcn,     APPENDSD_MENU,
  LOADSTOR_MENU,    "Load/Store Config >", 4, LOG2SD_MENU,      SDCARD_MENU,      LOADSTOR_MENU,    LOAD_MENU,       &nullFcn,     LOAD_MENU,
  SDCARD_MENU,      "Manage SD Card >",    5, LOADSTOR_MENU,    MANTIME_MENU,     SDCARD_MENU,      SDERASE_MENU,    &nullFcn,     SDERASE_MENU,
  MANTIME_MENU,     "Manage RealTimeClk",  6, SDCARD_MENU,      BACKLITE_MENU,    MANTIME_MENU,     MANTIME_MENU,    &setTime,     MANTIME_MENU,
  BACKLITE_MENU,    "Set Backlight Level", 7, MANTIME_MENU,     BACKLITE_MENU,    BACKLITE_MENU,    BACKLITE_MENU,   &setBLt,      STORE_MENU,
  APPENDSD_MENU,    "< Append to file",    2, APPENDSD_MENU,    CREATENEW_MENU,   LOG2SD_MENU,      APPENDSD_MENU,   &appendSD,    APPENDSD_MENU,
  CREATENEW_MENU,   "Create new file",     3, APPENDSD_MENU,    CREATENEW_MENU,   CREATENEW_MENU,   CREATENEW_MENU,  &createSD,    CREATENEW_MENU,
  NEWFILE_MENU,     "New file",            3, APPENDSD_MENU,    NEWFILE_MENU,     NEWFILE_MENU,     NEWFILE_MENU,    &newfileSD,   NEWFILE_MENU,
  LOAD_MENU,        "< Load Config",       2, LOAD_MENU,        STORE_MENU,       LOADSTOR_MENU,    LOAD_MENU,       &loadConfig,  LOAD_MENU,
  STORE_MENU,       "Store Config",        3, LOAD_MENU,        STORE_MENU,       STORE_MENU,       STORE_MENU,      &storeConfig, STORE_MENU,
  SDERASE_MENU,     "< Erase SD Card",     2, SDERASE_MENU,     SDLIST_MENU,      SDCARD_MENU,      SDERASE_MENU,    &sdErase,     SDERASE_MENU,
  SDLIST_MENU,      "List SD card files",  3, SDERASE_MENU,     SDEN_MENU,        SDLIST_MENU,      SDLIST_MENU,     &sdList,      SDLIST_MENU,
  SDEN_MENU,        "Enable SD card",      4, SDLIST_MENU,      DSDIS_MENU,       SDEN_MENU,        SDEN_MENU,       &sdEnable,    SDEN_MENU,
  DSDIS_MENU,       "Disable SD card",     5, SDEN_MENU,        DSDIS_MENU,       DSDIS_MENU,       DSDIS_MENU,      &sdDisable,   DSDIS_MENU,
};

////////////////////////////////////////////////////////////////////////////////////
// Refresh the menu
////////////////////////////////////////////////////////////////////////////////////

void menuRefresh(void)
{
  int nextLine, lastLine;
  tft.fillRect(0,0,127,89,ST7735_BLACK);
  setCursorTFT(0,0);
  tft.setTextColor(ST7735_WHITE,ST7735_RED);
  tft.print("*** 1-Wire Logger ***");
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

void menuNav(void)
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

//////////////////////////////////////////////////////////////////////////////
// void nullFcn(void)
//////////////////////////////////////////////////////////////////////////////

void nullFcn(void) {  }

