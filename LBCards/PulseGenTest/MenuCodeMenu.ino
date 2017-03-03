////////////////////////////////////////////////////////////////////////////////////
// MenuCodeMenu() - PulseGenerator Tester Menu
// Uses MyMenu with an OLED card
////////////////////////////////////////////////////////////////////////////////////

#define LCD_COLUMNS 14      // Specific value to the OLED card selected and the font
                            // Also defines the maximum line length for each displayed line

////////////////////////////////////////////////////////////////////////////////////
// Menu structure - The format of the menu system structure
// Memory size could be improved if the menuString was variable size and 
//  used pointers rather than a fixed array but that would increase complexity.
////////////////////////////////////////////////////////////////////////////////////

struct menuStruc                      // The ENUMs for the *_MENU_PTR values must preceed this
{
  uint8_t CURRENT_MENU_PTR;          // The current menu item
  char    menuString[LCD_COLUMNS+1]; // The string that gets displayed for that menu line
  uint8_t rowNumber;                 // The row that the string gets displayed on the LCD
  uint8_t UP_MENU_PTR;               // What menu gets highlighted when the up arrow is pressed
  uint8_t DOWN_MENU_PTR;             // What menu gets highlighted when the down arrow is pressed
  uint8_t LEFT_MENU_PTR;             // What menu gets highlighted when the left arrow is pressed
  uint8_t RIGHT_MENU_PTR;            // What menu gets highlighted when the right arrow is pressed
  void (*pt2Function)(void);         // Name of the function which gets called when select is pressed
  uint8_t SEL_MENU_PTR;              // Menu to display after the selected function complets
};

////////////////////////////////////////////////////////////////////////////////////
// Menu structure - used to generate the navigation menus. Format is
// CURR_MENU,MENU_STRING,DISPLAY_ROW,UP_MENU,DOWN_MENU,LEFT_MENU,RIGHT_MENU,select-execute-fcn-name,RETURN_MENU
// CURR_MENU needs to be ordered in the enums to match the order on the screen
// DISPLAY_ROW starts with 2 since there is a banner at the top of the display
////////////////////////////////////////////////////////////////////////////////////

menuStruc menus[] = 
{
  FIRST_LINE_MENU,  "Test PulseGen", 1, FIRST_LINE_MENU,  FOURTH_LINE_MENU, FIRST_LINE_MENU,  FIRST_LINE_MENU, &testPulseGen, FIRST_LINE_MENU,
  FOURTH_LINE_MENU, "Check Tester",  2, FIRST_LINE_MENU,  FOURTH_LINE_MENU, FOURTH_LINE_MENU, FSTL_TESTS_MENU, &nullFcn,      FSTL_TESTS_MENU,
  FSTL_TESTS_MENU,  "Test LEDs",     1, FSTL_TESTS_MENU,  SCND_TESTS_MENU,  FIRST_LINE_MENU,  FSTL_TESTS_MENU, &testLEDsFcn,  FIRST_LINE_MENU,
  SCND_TESTS_MENU,  "Test Buttons",  2, FSTL_TESTS_MENU,  SCND_TESTS_MENU,  SCND_TESTS_MENU,  SCND_TESTS_MENU, &testButtons,  FIRST_LINE_MENU
};

////////////////////////////////////////////////////////////////////////////////////
// Refresh the menu 
// The special thing about this is that it prints the lines above the selected line first
// then it prints the lines below the selected lines. For some reason this feels natural.
////////////////////////////////////////////////////////////////////////////////////

void menuRefresh(void)
{
  uint8_t nextLine, lastLine;
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  u8x8.setInverseFont(1);
  u8x8.drawString(0,menus[menuState].rowNumber - 1,menus[menuState].menuString);
  u8x8.setInverseFont(0);
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  lastLine = menuState;
  // display the lines above the selected line first
  while ((menus[lastLine].UP_MENU_PTR != menus[lastLine].CURRENT_MENU_PTR) && (menus[menuState].rowNumber != 1))
  {
    lastLine = menus[lastLine].UP_MENU_PTR;
    u8x8.drawString(0,menus[lastLine].rowNumber - 1, menus[lastLine].menuString);
  }
  nextLine = menuState;
  // next display the lines below the selected line
  while (menus[nextLine].DOWN_MENU_PTR != menus[nextLine].CURRENT_MENU_PTR)
  {
    nextLine = menus[nextLine].DOWN_MENU_PTR;
    u8x8.drawString(0, menus[nextLine].rowNumber - 1, menus[nextLine].menuString);
  }
}

////////////////////////////////////////////////////////////////////////////////////
// menuNav - Uses the joystick switch to move around the menu
////////////////////////////////////////////////////////////////////////////////////

void menuNav(void)
{
  uint8_t keyState;
  keyState = menuCard.waitKeyPressed();
  switch(keyState)
  {
  case UP:
    menuState = menus[menuState].UP_MENU_PTR;
    while(menuCard.pollKeypad() == UP);
    break;
  case DOWN:
    menuState = menus[menuState].DOWN_MENU_PTR;
    while(menuCard.pollKeypad() == DOWN);
    break;
  case LEFT:
    menuState = menus[menuState].LEFT_MENU_PTR;
    while(menuCard.pollKeypad() == LEFT);
    break;
  case RIGHT:
    menuState = menus[menuState].RIGHT_MENU_PTR;
    while(menuCard.pollKeypad() == RIGHT);
    break;
  case SELECT:
    // run the selected function
    void (*foo)(void);
    foo = menus[menuState].pt2Function;
    foo();
    menuState = menus[menuState].SEL_MENU_PTR;
    while(menuCard.pollKeypad() == SELECT);
    break;
  }
}

//////////////////////////////////////////////////////////////////////////////
// void nullFcn(void) - Special function which does nothing
//////////////////////////////////////////////////////////////////////////////

void nullFcn(void) {  }

