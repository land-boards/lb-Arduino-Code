//////////////////////////////////////////////////////////////////////////////////
// D16-TEST
// Test the DigIO16-I2C card
// Uses GVSDuino card
// Uses MyMenu card
// https://code.google.com/p/u8glib/wiki/u8glib?tm=6
//////////////////////////////////////////////////////////////////////////////////

#include <inttypes.h>
#include <string.h>

#include <Wire.h>
#include "MyMenu.h"
#include "U8glib.h"
#include <I2C_eeprom.h>

#include "Adafruit_MCP23017.h"

#define EE24LC024MAXBYTES 2048/8

// EEPROM nase address
#define DEVICEADDRESS (0x50)

#define TEST_ADDR 16

// this must start on a page boundary!
#define TEST_PAGE_ADDR 0
#define SHORT_BUFFER_LEN 4

// this tests multi-page writes
#define LONG_BUFFER_LEN 64
// make sure it's aligned on a page boundary
#define LONG_TEST_PAGE_ADDR (max(16, TEST_PAGE_ADDR + SHORT_BUFFER_LEN))

#define SERIAL_DEBUG Serial

#define LCD_COLUMNS 13

//////////////////////////////////////////////////////////////////////////////////
// Instantiations
//////////////////////////////////////////////////////////////////////////////////

Adafruit_MCP23017 mcp0;

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK);

MyMenu menuCard;

I2C_eeprom eeprom(DEVICEADDRESS, EE24LC024MAXBYTES);

//////////////////////////////////////////////////////////////////////////////////
// Global variables follow
//////////////////////////////////////////////////////////////////////////////////

uint8_t menuState;              // Menu State variable

unsigned long testCount;
unsigned long passCount;
unsigned long failCount;

struct eep_vals
{
  char signature[4];
  byte fmt_version;
  byte rsvd;
  short numatoms;
  long eeplen;
  char uuid[16];
  short pid;
  char vslen;
  char pslen;
  char vstr[32];
  char pstr[32];
};

//////////////////////////////////////////////////////////////////////////////
// enums follow
//////////////////////////////////////////////////////////////////////////////

enum MENUITEMS
{
  FIRST_LINE_MENU,
  SECOND_LINE_MENU,
  THIRD_LINE_MENU,
  FOURTH_LINE_MENU,
  FSTL_TESTS_MENU,
  SCND_TESTS_MENU
};

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////

void setup()
{
  uint8_t port;
  menuState = FIRST_LINE_MENU;  // Set up the init menu state
  mcp0.begin(0);      // use default address 0
  displayInit();                // Hardware specific function to set up the display
  menuCard.begin(1);            // pass the address of the mcp23008 on the menu card
  initTests();
  displayInit();
  setDisplayCursor(0, 0);
  TWBR = 12;                    // 400 KHz I2C
    for (port = 0; port < 16; port++)
      mcp0.pinMode(port, OUTPUT);
  u8g.firstPage();
  do
  {
    u8g.drawStr( 0, 11, "Hello Doug!");
  }
  while ( u8g.nextPage() );
  delay(250);
}

//////////////////////////////////////////////////////////////////////////////////////
// initTests
//////////////////////////////////////////////////////////////////////////////////////

void initTests(void)
{
  testCount = 0;
  passCount = 0;
  failCount = 0;
}

//////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////

void loop()
{
  u8g.firstPage();
  do
  {
    menuRefresh();
  }
  while ( u8g.nextPage() );

  menuNav();
}

