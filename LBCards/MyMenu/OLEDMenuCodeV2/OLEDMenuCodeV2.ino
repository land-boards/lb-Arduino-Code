/*
  OLEDMenuCode.ino - This code is the Land Boards, LLC menu system.
  This code runs on a standard Arduino or Arduino compatible card.
  This code uses the MyMenu card by Land Boards, LLC.
  MyMenu card is I2C based and has 5 buttons, 3 LEDs and an OLED display.
  http://land-boards.com/blwiki/index.php?title=MyMenu

  Menu code with "small" menu plus MyMenu library plus U8G2lib (OLED library) uses
    8,354 bytes (25%) of program space (37% of Arduino UNO space)
    794 bytes (38%) of dynamic memory (38% of Arduino UNO space)

  Original Author: Land Boards, LLC
*/

#include <Arduino.h>
#include "Wire.h"                 // Arduino I2C library
#include "LandBoards_MyMenu.h" // MyMenu card library handles switches and LEDs
#include "U8x8lib.h"              // Direct 8x8 buffer-less mode

//////////////////////////////////////////////////////////////////////////////
// enums for the menu system follow
// Each item represents an individual line on the screen and provides a unique
// identifier number for each menu item.
// These enums can be named anything, but there has to be one per line.
// This table needs to exactly match the first element in the menuStruc menus[].
//////////////////////////////////////////////////////////////////////////////

enum MENUITEMS              // MenuCode Customizable section
{
  FIRST_LINE_MENU,
  SECOND_LINE_MENU,
  THIRD_LINE_MENU,
  FOURTH_LINE_MENU,
  FIRST_SUB_MENU,
  SECOND_SUB_MENU,
  FSTL_TESTS_MENU,
  SCND_TESTS_MENU
};


//////////////////////////////////////////////////////////////////////////////
// Global variables follow
//////////////////////////////////////////////////////////////////////////////

uint8_t menuState;           // Menu State variable which holds the currently selected menu lin

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE, SCL, SDA);   // OLEDs without Reset of the Display

LandBoards_MyMenu menuCard;                // MyMenu card by Land Boards, LLC

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////

void setup(void)
{
  menuState = FIRST_LINE_MENU;  // Set up the init menu state - Menu should show the first line selected
  menuCard.begin(1);            // pass the address of the mcp23008 on the menu card
  u8x8.setI2CAddress(0x78);
  u8x8.begin();
  TWBR = 12;                    // 400 KHz I2C
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.draw2x2String(0,2,"MyMenu");
  u8x8.draw2x2String(0, 4, "   v2");
  delay(2000);
}

//////////////////////////////////////////////////////////////////////////////
// With the MyMenu system the loop gets simplified to two basic functions
// One of the functions refreshes the screen.
// The other function for button presses and navigates the screens.
//////////////////////////////////////////////////////////////////////////////

void loop(void)
{
  u8x8.clear();
  menuRefresh();      // Refresh the screen
  menuNav();            // Check the buttons and navigate the screens
}
