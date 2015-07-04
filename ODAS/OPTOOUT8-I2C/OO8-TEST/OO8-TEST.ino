// OO8-TEST
// Test the OptoOut8-I2C card
// Uses GVSDuino card
// Uses MyMenu card
// https://code.google.com/p/u8glib/wiki/u8glib?tm=6

#include <Wire.h>
#include "Adafruit_MCP23008.h"

#include "MyMenu.h"
#include "U8glib.h"

#include <inttypes.h>
#include <string.h>

Adafruit_MCP23008 mcpOO8;

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK);

MyMenu menuCard;

uint8_t menuState;              // Menu State variable

unsigned long testCount;
unsigned long passCount;
unsigned long failCount;

//////////////////////////////////////////////////////////////////////////////
// enums follow
//////////////////////////////////////////////////////////////////////////////

enum MENUITEMS
{
  FIRST_LINE_MENU,
  SECOND_LINE_MENU,
  THIRD_LINE_MENU
};

//////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////

void setup()
{
  int loopCnt;
  menuState = FIRST_LINE_MENU;  // Set up the init menu state
  mcpOO8.begin();      // use default address 0
  displayInit();                // Hardware specific function to set up the display
  menuCard.begin();
  TWBR = 12;
  for (loopCnt = 0; loopCnt < 8; loopCnt++)
    mcpOO8.pinMode(loopCnt, OUTPUT);
  for (loopCnt = 3; loopCnt < 11; loopCnt++)
    pinMode(loopCnt, INPUT);
  testCount = 0;
  passCount = 0;
  failCount = 0;
  u8g.setColorIndex(1);  // default color
  u8g.setFont(u8g_font_unifont);
  setDisplayCursor(0, 0);
  u8g.firstPage();
  do
  {
    u8g.drawStr( 0, 11, "Hello Doug!");
  }
  while ( u8g.nextPage() );
}

//

void setDisplayCursor(uint8_t row, uint8_t col)
{
  u8g.setPrintPos( col * 9, row * 13 + 13);
}

//

void loop()
{
  int loopCnt;
  unsigned char digRdVal;
  int pass1Fail0;
  delay(100);
  testCount++;
  pass1Fail0 = 1;
  for (loopCnt = 0; loopCnt < 8; loopCnt++)
  {
    mcpOO8.digitalWrite(loopCnt, HIGH);
    delayMicroseconds(15);
    digRdVal = digitalRead(loopCnt + 3);
    if (digRdVal != HIGH)
      pass1Fail0 = 0;
    mcpOO8.digitalWrite(loopCnt, LOW);
    delayMicroseconds(15);
    digRdVal = digitalRead(loopCnt + 3);
    if (digRdVal != LOW)
      pass1Fail0 = 0;
  }
  if (pass1Fail0 == 1)
    passCount++;
  else
    failCount++;
  u8g.firstPage();
  do
  {
    setDisplayCursor(0, 0);
    u8g.print("Pass=");
    u8g.print(passCount);
    setDisplayCursor(1, 0);
    u8g.print("Fail=");
    u8g.print(failCount);
  }
  while ( u8g.nextPage() );
}

