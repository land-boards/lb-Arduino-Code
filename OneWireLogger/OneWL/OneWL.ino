//////////////////////////////////////////////////////////////////////////////
//  OneWL - One-Wire Data Logger.
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Includes follow
//////////////////////////////////////////////////////////////////////////////

#include <SPI.h>
#include <EEPROM.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;
#include <OneWireLogger.h>
#include <Adafruit_GFX.h>      // Core graphics library
#include <Adafruit_ST7735.h>   // Hardware-specific library
#include <eepromanything.h>    // EEPROM anything

//////////////////////////////////////////////////////////////////////////////
// defines follow
//////////////////////////////////////////////////////////////////////////////

//#define SERIAL_OUT
#undef SERIAL_OUT

//////////////////////////////////////////////////////////////////////////////
// enums follow
//////////////////////////////////////////////////////////////////////////////

enum MENUITEMS
{
  LOGGER_MENU,
  LOG2SD_MENU,
  LOADSTOR_MENU,
  SDCARD_MENU,
  MANTIME_MENU,
  BACKLITE_MENU,
  TSTKPD_MENU,
  APPENDSD_MENU,
  CREATENEW_MENU,
  NEWFILE_MENU,
  LOAD_MENU,
  STORE_MENU,
  DISPTIME_MENU,
  SETTIME_MENU,
  SDERASE_MENU,
  SDLIST_MENU,
  SDEN_MENU,
  DSDIS_MENU,
};

//////////////////////////////////////////////////////////////////////////////
// Global variables follow
//////////////////////////////////////////////////////////////////////////////

int menuState;  // Used to implement the menuing state machine

// Board Configuration stored in EEPROM
struct IZ_Cfgs
{
  int bll;       // Backlight level
  int enableSD;  // Enable the SD card
} 
IZConfigs;

// class initializers
Adafruit_ST7735 tft = Adafruit_ST7735(LCD_CS, LCD_DC, LCD_RST);
OneWireLogger myOneWireLogger;

//////////////////////////////////////////////////////////////////////////////
// the setup routine runs once when you press reset:
//////////////////////////////////////////////////////////////////////////////

void setup() 
{
#ifdef SERIAL_OUT
  Serial.begin(57600);
  Serial.print("One Wire Logger");
#endif
// EEPROM access
  EEPROM_readAnything(0, IZConfigs);

// Set up the init menu state
  menuState = LOGGER_MENU;

// TFT init
  analogWrite(BACKLIGHT, IZConfigs.bll);
  tft.initR(INITR_REDTAB);
  tft.setTextSize(1);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  textWhiteOnBlack();
  if (IZConfigs.enableSD != 0)
  {
    if (!SD.begin(SD_CS)) 
    {
      tft.print(F("SD card not present"));
      setCursorTFT(1, 0);
      tft.print(F("Disabling check"));
      setCursorTFT(2, 0);
      tft.print(F("Power cycle unit"));
      sdDisable();
      EEPROM_writeAnything(0, IZConfigs);
      delay(2000);
    }
  }

// RTC init
  Wire.begin();  
  RTC.begin();
  if (! RTC.isrunning() )
  {
    tft.print("RTC-Setting time!");
    RTC.adjust(DateTime(__DATE__, __TIME__));   }
    delay(1000);
}

//////////////////////////////////////////////////////////////////////////////////////
// loop - runs over and over again forever:
//////////////////////////////////////////////////////////////////////////////////////

void loop() 
{

  menuRefresh();
  menuNav();
}
