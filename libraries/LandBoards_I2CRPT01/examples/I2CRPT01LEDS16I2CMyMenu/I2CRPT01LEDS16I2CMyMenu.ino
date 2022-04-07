// DIGIO16-I2C Example code
// Make all 16 lines outputs
// Blink each line, one at a time

#include <inttypes.h>
#include <string.h>

#include <Wire.h>
#include "LandBoards_MyMenu.h"
#include "U8glib.h"
#include <I2C_eeprom.h>

#include "Adafruit_MCP23017.h"
#include "LandBoards_I2CRPT01.h"

Adafruit_MCP23017 mcp0;

LandBoards_I2CRPT01 mux;

#define LCD_COLUMNS 13
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

I2C_eeprom eeprom(DEVICEADDRESS, EE24LC024MAXBYTES);

//////////////////////////////////////////////////////////////////////////////////
// Instantiations
//////////////////////////////////////////////////////////////////////////////////

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK);

LandBoards_MyMenu menuCard;

//I2C_eeprom eeprom(DEVICEADDRESS, EE24LC024MAXBYTES);

//////////////////////////////////////////////////////////////////////////////////
// Global variables follow
//////////////////////////////////////////////////////////////////////////////////

uint8_t menuState;              // Menu State variable

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


#define SEL_DIGIO16 0
#define SEL_OLED 3

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////

void setup() 
{
  mux.begin(0);         // 0x70 is the mux card address
  mux.setI2CChannel(SEL_DIGIO16);
  mcp0.begin(1);      // use default address 0
  menuState = FIRST_LINE_MENU;  // Set up the init menu state
  mux.setI2CChannel(SEL_OLED);
  displayInit();                // Hardware specific function to set up the display
  menuCard.begin(1);            // pass the address of the mcp23008 on the menu card

  displayInit();
//  u8g.setFont(u8g_font_unifont);
  setDisplayCursor(0, 0);
  u8g.firstPage();
  do
  {
    u8g.drawStr( 0, 11, "Hello Doug!");
  }
  while ( u8g.nextPage() );
  delay(250);

  uint8_t chip;
  uint8_t port;

  mux.setI2CChannel(SEL_DIGIO16);
  for (chip = 0; chip < 1; chip++)
  {
    for (port = 0; port < 16; port++)
    {
      mcp0.pinMode(port, OUTPUT);
    }
  }
  mux.setI2CChannel(SEL_OLED);
}

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////

// flip the pin #0 up and down

void loop() {
 u8g.firstPage();  
  do 
  {
    menuRefresh();
  } 
  while( u8g.nextPage() );

  menuNav();

}


void testit(void)
{
  uint8_t chip;
  uint8_t port;

  for (port = 0; port < 16; port++)
  {
    mcp0.digitalWrite(port, HIGH);
    delay(250);
    mcp0.digitalWrite(port, LOW);
    //      delay(250);
  }
}
