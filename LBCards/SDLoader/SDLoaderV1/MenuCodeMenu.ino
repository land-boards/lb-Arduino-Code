////////////////////////////////////////////////////////////////////////////////////
// MenuCodeMenu() - Display the example Menu.
// Hardware items required are five buttons (Up, Down, Left, Right and Select) plus a Display.
// The five buttons can be a 5-way switch or 5 individual buttons.
// The five buttons are aggregated into a single variable representing button state.
// The menu operations are typically to have up/down movement through the displayed items.
// Right or select can call submenus (for items which have submenus).
// Left can return to the previous menu.
// Select can execute the selected item.
// Use left and right arrows to indicate submenu availability.
// This menu system is fairly lightweight and is strongly geared towards LCDs.
// This menu system allows for submenus to be called.
// There are corresponding ENUM values for each of the xxx_MENU_PTR values.
// The ENUMs need to be ordered in the same order as they appear in the menu structure.
////////////////////////////////////////////////////////////////////////////////////

#define LCD_COLUMNS 16      // Specific value to the OLED card selected and the font
// Also defines the maximum line length for each displayed line

////////////////////////////////////////////////////////////////////////////////////
// Menu structure - The format of the menu system structure
// Memory size could be improved if the menuString was variable size and
//  used pointers rather than a fixed array but that would increase complexity.
////////////////////////////////////////////////////////////////////////////////////

struct menuStruc                      // The ENUMs for the *_MENU_PTR values must preceed this
{
  uint8_t CURRENT_MENU_PTR;          // The current menu item
  char    menuString[LCD_COLUMNS + 1]; // The string that gets displayed for that menu line
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
  //MENUITEMS enum,  "string",   LINE, UP enum,       DOWN enum,     Left enum,     right enum,    select fcn,     menu selection after function,
  TOP_MENU_L01,   "File SEND",      1, TOP_MENU_L01,  TOP_MENU_L02,  TOP_MENU_L01,  TOP_MENU_L01,  &fileSend,      TOP_MENU_L01,
  TOP_MENU_L02,   "File RECEIVE",   2, TOP_MENU_L01,  TOP_MENU_L03,  TOP_MENU_L02,  TOP_MENU_L02,  &fileReceive,   TOP_MENU_L01,
  TOP_MENU_L03,   "Config COM",     3, TOP_MENU_L02,  TOP_MENU_L04,  TOP_MENU_L03,  TOP_MENU_L03,  &nullFcn,       COMM_MENU_L01,
  TOP_MENU_L04,   "SD Info",        4, TOP_MENU_L03,  TOP_MENU_L05,  TOP_MENU_L04,  TOP_MENU_L04,  &SDInfo,        TOP_MENU_L01,
  TOP_MENU_L05,   "Tests",          5, TOP_MENU_L04,  TOP_MENU_L05,  TOP_MENU_L05,  TOP_MENU_L05,  &nullFcn,       TEST_MENU_L01,
  // COMM Menu
  COMM_MENU_L01,  "BAUD Rate",      1, COMM_MENU_L01, COMM_MENU_L02, COMM_MENU_L01, COMM_MENU_L01, &nullFcn,       BAUD_MENU_L01,
  COMM_MENU_L02,  "Handshake",      2, COMM_MENU_L01, COMM_MENU_L03, COMM_MENU_L02, COMM_MENU_L02, &nullFcn,       HAND_MENU_L01,
  COMM_MENU_L03,  "Return to top",  3, COMM_MENU_L02, COMM_MENU_L03, COMM_MENU_L03, COMM_MENU_L03, &nullFcn,       TOP_MENU_L01,
  // COMM Menu
  BAUD_MENU_L01,  "300 Baud",       1, BAUD_MENU_L01, BAUD_MENU_L02, BAUD_MENU_L01, BAUD_MENU_L01, &baud_300,      BAUD_MENU_L05,
  BAUD_MENU_L02,  "1200 Baud",      2, BAUD_MENU_L01, BAUD_MENU_L03, BAUD_MENU_L02, BAUD_MENU_L02, &baud_1200,     BAUD_MENU_L05,
  BAUD_MENU_L03,  "9600 Baud",      3, BAUD_MENU_L02, BAUD_MENU_L04, BAUD_MENU_L03, BAUD_MENU_L03, &baud_9600,     BAUD_MENU_L05,
  BAUD_MENU_L04,  "115,200 Baud",   4, BAUD_MENU_L03, BAUD_MENU_L05, BAUD_MENU_L04, BAUD_MENU_L04, &baud_115k,     BAUD_MENU_L05,
  BAUD_MENU_L05,  "Return to top",  5, BAUD_MENU_L04, BAUD_MENU_L05, BAUD_MENU_L05, BAUD_MENU_L05, &nullFcn,       TOP_MENU_L01,
  // Handshrke
  HAND_MENU_L01,  "No handshake",   1, HAND_MENU_L01, HAND_MENU_L02, HAND_MENU_L01, HAND_MENU_L01, &no_hanksh,     HAND_MENU_L04,
  HAND_MENU_L02,  "Use RTS/CTS",    2, HAND_MENU_L01, HAND_MENU_L03, HAND_MENU_L02, HAND_MENU_L02, &hw_hansh,      HAND_MENU_L04,
  HAND_MENU_L03,  "Use XON/XOFF",   3, HAND_MENU_L02, HAND_MENU_L04, HAND_MENU_L03, HAND_MENU_L03, &x_hansh,       HAND_MENU_L04,
  HAND_MENU_L04,  "Return to top",  4, HAND_MENU_L03, HAND_MENU_L04, HAND_MENU_L04, HAND_MENU_L04, &nullFcn,       TOP_MENU_L01,
  // Test Menu
  TEST_MENU_L01,  "Test LEDs",      1, TEST_MENU_L01, TEST_MENU_L02, TEST_MENU_L01, TEST_MENU_L01, &testLEDsFcn,   TEST_MENU_L03,
  TEST_MENU_L02,  "Test Buttons",   2, TEST_MENU_L01, TEST_MENU_L03, TEST_MENU_L02, TEST_MENU_L02, &testButtons,   TEST_MENU_L03,
  TEST_MENU_L03,  "Return to top",  3, TEST_MENU_L02, TEST_MENU_L03, TEST_MENU_L03, TEST_MENU_L03, &nullFcn,       TOP_MENU_L01
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
// Debounced by polling every 10 mS
////////////////////////////////////////////////////////////////////////////////////

void menuNav(void)
{
  uint8_t keyState;
//  keyState = myIReflow.waitKeyPressed();
  keyState = menuCard.waitKeyPressed();
  switch(keyState)
  {
  case UP:
    menuState = menus[menuState].UP_MENU_PTR;
    while(menuCard.pollKeypad() == UP)
      delay(10);
    break;
  case DOWN:
    menuState = menus[menuState].DOWN_MENU_PTR;
    while(menuCard.pollKeypad() == DOWN)
      delay(10);
    break;
  case LEFT:
    menuState = menus[menuState].LEFT_MENU_PTR;
    while(menuCard.pollKeypad() == LEFT)
      delay(10);
    break;
  case RIGHT:
    menuState = menus[menuState].RIGHT_MENU_PTR;
    while(menuCard.pollKeypad() == RIGHT)
      delay(10);
    break;
  case SELECT:
    // run the selected function
    void (*foo)(void);
    foo = menus[menuState].pt2Function;
    foo();
    menuState = menus[menuState].SEL_MENU_PTR;
    while(menuCard.pollKeypad() == SELECT)
      delay(10);
    break;
  }
}

//////////////////////////////////////////////////////////////////////////////
// void nullFcn(void) - Special function which does nothing
//////////////////////////////////////////////////////////////////////////////

void nullFcn(void)
{
//  u8x8.clear();
//  delay(100);
//  u8x8.drawString(0,1,"In nullFcn()");  // Do nothing 
//  delay(2000);
}

//////////////////////////////////////////////////////////////////////////////
// pressButtonToContinue()
//////////////////////////////////////////////////////////////////////////////

void pressButtonToContinue()
{
  while (menuCard.pollKeypad() == NONE);
  while (menuCard.pollKeypad() != NONE);
  delay(10);  
}
