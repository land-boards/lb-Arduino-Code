/*

 IReflowv01.ino
 
*/

#include "Wire.h"
#include <SPI.h>

#include "IReflow.h"
#include "MyMenu.h"

#include "U8glib.h"
#include "Adafruit_MAX31855.h"

#define CS   9
Adafruit_MAX31855 thermocouple(CS);

//////////////////////////////////////////////////////////////////////////////
// enums follow
//////////////////////////////////////////////////////////////////////////////

enum MENUITEMS
{
  FIRST_LINE_MENU,
  SECOND_LINE_MENU,
  THIRD_LINE_MENU,
  FIRST_SUB_MENU,
  SECOND_SUB_MENU,
};

//////////////////////////////////////////////////////////////////////////////
// Global variables follow
//////////////////////////////////////////////////////////////////////////////

uint8_t menuState;              // Menu State variable

IReflow myIReflow;
MyMenu menuCard;

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK);

void setup(void) 
{
  menuState = FIRST_LINE_MENU;  // Set up the init menu state
  myIReflow.redLED(LOW);
  delay(250);
  myIReflow.redLED(HIGH);
  myIReflow.greenLED(LED_ON);
  delay(100);
  myIReflow.greenLED(LED_OFF);
  displayInit();                // Hardware specific function to set up the display
}

void loop(void) 
{
  u8g.firstPage();  
  do 
  {
    menuRefresh();
  } 
  while( u8g.nextPage() );

  menuNav();
}


