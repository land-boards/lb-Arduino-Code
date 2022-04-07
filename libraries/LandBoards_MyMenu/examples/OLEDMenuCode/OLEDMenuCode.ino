/*
  OLEDMenuCode.ino - This code is the Land Boards, LLC menu system.
  This code runs on a standard Arduino or Arduino compatible card.
  This code uses the MyMenu card by Land Boards, LLC.
  MyMenu card is I2C based and has 5 buttons, 3 LEDs and an OLED display.
  http://land-boards.com/blwiki/index.php?title=MyMenu

  Menu code with "small" menu plus MyMenu library plus U8Glib (OLED library) uses
    11,990 bytes of program space (37% of Arduino UNO space)
    682 bytes of data RAM space (33% of Arduino UNO space)

  Original Author: Land Boards, LLC
*/

#include "Wire.h"                 // Arduino I2C library
#include "LandBoards_MyMenu.h"    // MyMenu card library handles switches and LEDs
#include "U8glib.h"               // OLED library

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

#define LCD_COLUMNS 14      // Specific value to the OLED card selected and the font
                            // Also defines the maximum line length for each displayed line

//////////////////////////////////////////////////////////////////////////////
// Global variables follow
//////////////////////////////////////////////////////////////////////////////

uint8_t menuState;           // Menu State variable which holds the currently selected menu lin

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK);    // OLED Library

LandBoards_MyMenu menuCard;                // MyMenu card by Land Boards, LLC

void setup(void) 
{
  menuState = FIRST_LINE_MENU;  // Set up the init menu state - Menu should show the first line selected
  displayInit();                // Hardware specific function to set up the display
  menuCard.begin(1);            // pass the address of the mcp23008 on the menu card
 #if defined(ARDUINO_ARCH_AVR)
	TWBR = 12;    			// go to 400 KHz I2C speed mode
#elif defined(ARDUINO_ARCH_STM32F1)
	Wire.setClock(400000);	// 400KHz speed
#elif defined(STM32F4)
	Wire.setClock(400000);	// 400KHz speed
#else
  #error “This library only supports boards with an AVR or STM processors.”
#endif
}

//////////////////////////////////////////////////////////////////////////////
// With the MyMenu system the loop gets simplified to two basic functions
// One of the functions refreshes the screen.
// The other function for button presses and navigates the screens.
//////////////////////////////////////////////////////////////////////////////

void loop(void) 
{
  u8g.firstPage();      // This is the way that the u8g library works. Seems strange
  do 
  {
    menuRefresh();      // Refresh the screen
  } 
  while( u8g.nextPage() );

  menuNav();            // Check the buttons and navigate the screens
}

