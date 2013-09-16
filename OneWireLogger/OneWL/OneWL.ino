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

enum 
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

int menuState;  // Used to implement the menuing state machine

unsigned char sensorNumber;
unsigned char sensorAddr;
unsigned char firstRun;
float temps1Wire[32];

OneWire  ds(ONE_WIRE);  // on pin 
unsigned char sensNum;
float fahrenheit;

uint16_t currYear;
uint8_t currMonth, currDay, currHour, currMin, currSec;

// Board Configuration stored in EEPROM
struct IZ_Cfgs
{
  unsigned char bll;       // Backlight level
  unsigned char enableSD;  // Enable the SD card
} 
IZConfigs;

// class initializers
Adafruit_ST7735 tft = Adafruit_ST7735(LCD_CS, LCD_DC, LCD_RST);
OneWireLogger myOneWireLogger;
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
  tft.initR(INITR_REDTAB);
  clearTFT();
  if (IZConfigs.enableSD != 0)
  {
    if (!SD.begin(SD_CS)) 
    {
      tft.print(F("SD card missing"));
      setCursorTFT(1, 0);
      tft.print(F("Disable check"));
      setCursorTFT(2, 0);
      tft.print(F("Power cycle"));
      sdDisable();
      EEPROM_writeAnything(0, IZConfigs);
      myOneWireLogger.delayAvailable(2000);
    }
  }

  // RTC init starts up the wire interface (TWI/I2C I/F)
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

