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
  uint8_t CURRENT_MENU_PTR;          // The current menu item
  char    menuString[LCD_COLUMNS+1]; // The string that gets displayed
  uint8_t rowNumber;                 // The row that the string gets displayed on the LCD
  uint8_t UP_MENU_PTR;               // What menu gets highlighted when the up arrow is pressed
  uint8_t DOWN_MENU_PTR;             // What menu gets highlighted when the down arrow is pressed
  uint8_t LEFT_MENU_PTR;             // What menu gets highlighted when the left arrow is pressed
  uint8_t RIGHT_MENU_PTR;            // What menu gets highlighted when the right arrow is pressed
  void (*pt2Function)(void);      // Name of the function which gets called when select is pressed
  uint8_t SEL_MENU_PTR;              // Menu to display after the selected function complets
};

////////////////////////////////////////////////////////////////////////////////////
// Menu structure - used to generate the navigation menus. Format is
// CURR_MENU,MENU_STRING,DISPLAY_ROW,UP_MENU,DOWN_MENU,LEFT_MENU,RIGHT_MENU,select-execute-fcn-name,RETURN_MENU
// CURR_MENU needs to be ordered in the enums to match the order on the screen
////////////////////////////////////////////////////////////////////////////////////
  
menuStruc menus[] = 
{
  LOG2SCRN_MENU,    "Log to screen",      2, LOG2SCRN_MENU,    LOG2SD_MENU,    LOG2SCRN_MENU,    LOG2SCRN_MENU,   &do1WireLCD,  LOG2SCRN_MENU,
  LOG2SD_MENU,      "Log to SD card",     3, LOG2SCRN_MENU,    LOG2USB_MENU,   LOG2SD_MENU,      LOG2SD_MENU,     &appendSD,    LOG2SD_MENU,
  LOG2USB_MENU,     "Log to USB Serial",  4, LOG2SD_MENU,      LOG2USB_MENU,   LOG2USB_MENU,     LOG2USB_MENU,    &do1WireUSB,  LOG2USB_MENU,
};

////////////////////////////////////////////////////////////////////////////////////
// Refresh the menu
////////////////////////////////////////////////////////////////////////////////////

void menuRefresh(void)
{
  uint8_t nextLine, lastLine;
  clearTFT();
  tft.setTextColor(ST7735_WHITE,TFT_RED);
  tft.print("*** 1-Wire Logger ***");
  textWhiteOnBlack();
  setCursorTFT(15,0);
  tft.print(__DATE__);
  tft.print(" ");
  tft.print(__TIME__);
#ifdef SERIAL_DEBUG
  Serial.print(F("menuState="));
  Serial.print(menuState);
  Serial.print(F(",String="));
  Serial.print(menus[menuState].menuString);
  Serial.print(F(",RowNumber = "));
  Serial.println(menus[menuState].rowNumber);
#endif
  setCursorTFT((menus[menuState].rowNumber)-1,0);
  tft.setTextColor(ST7735_WHITE,TFT_BLUE);
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
  uint8_t keyState;
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

