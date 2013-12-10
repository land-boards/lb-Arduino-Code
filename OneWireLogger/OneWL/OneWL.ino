//////////////////////////////////////////////////////////////////////////////
//  OneWL - One-Wire Data Logger.
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Includes follow
//////////////////////////////////////////////////////////////////////////////

#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>
#include <OneWire.h>
#include <SD.h>
#include <OneWireLogger.h>
#include "RTClib.h"
#include <Adafruit_GFX.h>      // Core graphics library
#include <Adafruit_ST7735.h>   // Hardware-specific library
#include <EEPROMAnything.h>    // EEPROM anything

//////////////////////////////////////////////////////////////////////////////
// defines follow
//////////////////////////////////////////////////////////////////////////////

//#define SERIAL_OUT
#undef SERIAL_OUT

// Display specific colors

#define	TFT_RED      0x001F    // Colors are reversed on my display from Adafruit
#define	TFT_BLUE     0xF800
#define TFT_HEIGHT   16        // TFT is 16 lines tall

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
  APPENDSD_MENU,
  CREATENEW_MENU,
  NEWFILE_MENU,
  LOAD_MENU,
  STORE_MENU,
  SDERASE_MENU,
  SDLIST_MENU,
  SDEN_MENU,
  DSDIS_MENU,
};

enum TIMESET
{
  VIEW_YEAR,
  VIEW_MONTH,
  VIEW_DAY,
  VIEW_HOUR,
  VIEW_MIN,
  VIEW_SEC,
  SET_YEAR,
  SET_MONTH,
  SET_DAY,
  SET_HOUR,
  SET_MINUTE,
  SET_SEC,
  SAVE_TIME,
  EXIT_TIME,
};

//////////////////////////////////////////////////////////////////////////////
// Global variables follow
//////////////////////////////////////////////////////////////////////////////

uint8_t menuState;  // Used to implement the menuing state machine

uint8_t sensorNumber;
uint8_t sensorAddr;
uint8_t firstRun;
float temps1Wire[32];
float fahrenheit;

uint16_t currYear;
uint8_t currMonth, currDay, currHour, currMin, currSec;

// Board Configuration stored in EEPROM
struct IZ_Cfgs
{
  uint8_t bll;       // Backlight level
  uint8_t enableSD;  // Enable the SD card
} 
IZConfigs;

// class initializers - most initialize hardware

OneWireLogger myOneWireLogger;
Adafruit_ST7735 tft = Adafruit_ST7735(LCD_CS, LCD_DC, LCD_RST);  // HW SPI
OneWire  ds(ONE_WIRE);  // on pin 
RTC_DS1307 RTC;
DateTime setRTCTime;

//////////////////////////////////////////////////////////////////////////////
// the setup routine runs once when you press reset:
//////////////////////////////////////////////////////////////////////////////

void setup() 
{
#ifdef SERIAL_OUT
  Serial.begin(57600);
  Serial.print(F("1-Wire Logger"));
#endif
  // EEPROM access
  EEPROM_readAnything(0, IZConfigs);

  // TFT init
  analogWrite(BACKLIGHT, IZConfigs.bll);
  tft.initR(INITR_REDTAB);    // I actually have a black tab on my part
  clearDisplay();
  if (IZConfigs.enableSD != 0)
  {
    if (!SD.begin(SD_CS)) 
    {
      tft.print(F("SD card missing"));
      setDisplayCursor(1, 0);
      tft.print(F("Disabling check"));
      setDisplayCursor(2, 0);
      tft.print(F("Power cycle"));
      sdDisable();
      EEPROM_writeAnything(0, IZConfigs);
      myOneWireLogger.delayAvailable(2000);
    }
  }

  // RTC init starts up the I2C wire interface
  Wire.begin();
  RTC.begin();
  if (! RTC.isrunning() )
  {
    tft.print("Replace RTC Battery");
    RTC.adjust(DateTime(__DATE__, __TIME__));   
  }
  myOneWireLogger.delayAvailable(1000);
  sensorNumber = 0;

  // Set up the init menu state
  menuState = LOGGER_MENU;
}

//////////////////////////////////////////////////////////////////////////////////////
// loop - runs over and over again forever:
//////////////////////////////////////////////////////////////////////////////////////

void loop() 
{
  menuRefresh();
  menuNav();
}

