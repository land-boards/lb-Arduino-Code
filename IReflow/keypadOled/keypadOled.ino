/*

 keypadOled.ino
 
 */

#include "IReflow.h"
#include "U8glib.h"

//////////////////////////////////////////////////////////////////////////////
// enums follow
//////////////////////////////////////////////////////////////////////////////

enum MENUITEMS
{
  FIRST_LINE_MENU,
  SECOND_LINE_MENU,
  THIRD_LINE_MENU,
  FIRST_SUB_MENU,
};

//////////////////////////////////////////////////////////////////////////////
// Global variables follow
//////////////////////////////////////////////////////////////////////////////

uint8_t menuState;              // Menu State variable

IReflow myIReflow;

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK);


void setup(void) 
{
  displayInit();                // Hardware specific function to set up the display
  menuState = FIRST_LINE_MENU;  // Set up the init menu state
}

void loop(void) 
{
  u8g.firstPage();  
  do 
  {
    menuRefresh();
  } 
  while( u8g.nextPage() );

  // rebuild the picture after some delay
//  delay(50);

  menuNav();
}


