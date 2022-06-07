/*
  SDLoaderV1.ino - 
  Based on the Land Boards, LLC menu system.
  This code runs on a standard Arduino or Arduino compatible card.
  This code uses the MyMenu card by Land Boards, LLC.
  MyMenu card is I2C based and has 5 buttons, 3 LEDs and an OLED display.
  http://land-boards.com/blwiki/index.php?title=MyMenu

  Original Author: Land Boards, LLC
*/

#include <Arduino.h>
#include "Wire.h"               // Arduino I2C library
#include "LandBoards_MyMenu.h"  // MyMenu card library handles switches and LEDs
#include "U8x8lib.h"            // Direct 8x8 buffer-less mode

//////////////////////////////////////////////////////////////////////////////
// enums for the menu system follow
// Each item represents an individual line on the screen and provides a unique
// identifier number for each menu item.
// These enums can be named anything, but there has to be one per line.
// This table needs to exactly match the first element in the menuStruc menus[].
//////////////////////////////////////////////////////////////////////////////

enum MENUITEMS              // MenuCode Customizable section
{
  TOP_MENU_L01,
  TOP_MENU_L02,
  TOP_MENU_L03,
  TOP_MENU_L04,
  TOP_MENU_L05,
  //
  COMM_MENU_L01,
  COMM_MENU_L02,
  COMM_MENU_L03,
  COMM_MENU_L04,
  //
  BAUD_MENU_L01,
  BAUD_MENU_L02,
  BAUD_MENU_L03,
  BAUD_MENU_L04,
  BAUD_MENU_L05,
  //
  HAND_MENU_L01,
  HAND_MENU_L02,
  HAND_MENU_L03,
  HAND_MENU_L04,
  //
  TEST_MENU_L01,
  TEST_MENU_L02,
  TEST_MENU_L03
};

enum HANDSHAKE_TYPE
{
  NO_HANDSHAKE,
  HW_HANDSHAKE,
  XON_XOFF_HANDSHAKE
};

//////////////////////////////////////////////////////////////////////////////
// Global variables follow
//////////////////////////////////////////////////////////////////////////////

uint8_t menuState;           // Menu State variable which holds the currently selected menu lin

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);   // OLEDs without Reset of the Display

LandBoards_MyMenu menuCard;                // MyMenu card by Land Boards, LLC

uint8_t comInit;
uint8_t USBSerInit;
uint32_t baudRate;
HANDSHAKE_TYPE handshakeType = NO_HANDSHAKE;

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////

void setup(void)
{
  menuState = TOP_MENU_L01;  // Set up the init menu state - Menu should show the first line selected
  menuCard.begin(0);            // pass the address of the mcp23008 on the menu card
  u8x8.setI2CAddress(0x78);
  u8x8.begin();
  Wire.setClock(400000);  // 400KHz speed
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.draw2x2String(1,2,"SD LDR");
  u8x8.draw2x2String(1,5,"v1.0");
  comInit = 0;
  USBSerInit = 0;
  baudRate = 300;
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
