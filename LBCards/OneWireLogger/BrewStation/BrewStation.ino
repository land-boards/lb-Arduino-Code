//////////////////////////////////////////////////////////////////////////////
// BrewStation - BrewStation running on the One-Wire Data Logger Board.
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Includes follow
//////////////////////////////////////////////////////////////////////////////

#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>
#include <OneWire.h>
#include <SD.h>
#include "RTClib.h"
#include <LandBoards_OneWireLogger.h>     // One Wire Logger
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
  STEEP_MENU,
  BOIL_MENU,
  THERMO_MENU,
  SERLOG_MENU,
  SETTIME_MENU,
  SETBKLT_MENU,
  CFG18B20_MENU,
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

int menuState;  // Used to implement the menuing state machine

uint8_t sensorNumber;
uint8_t sensorAddr;
uint8_t firstRun;
float temps1Wire[32];
float fahrenheit;

// Board Configuration stored in EEPROM
struct IZ_Cfgs
{
  int bll;           // Backlight level
  int enableSerLog;  // Enable Serial Logging
  int initializedEE;  // Initialized EE
} 
IZConfigs;

uint16_t currYear;
uint8_t currMonth, currDay, currHour, currMin, currSec;

// class initializers
LandBoards_OneWireLogger myOneWireLogger;
Adafruit_ST7735 tft = Adafruit_ST7735(LCD_CS, LCD_DC, LCD_RST);
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
  Serial.print(F("Brew Station"));
#endif
// EEPROM access
  EEPROM_readAnything(0, IZConfigs);

// Steep menu is first run
  menuState = STEEP_MENU;

// TFT init
  if (IZConfigs.initializedEE != 0xbaba)
  {
    IZConfigs.bll == 0x55;
    analogWrite(BACKLIGHT, IZConfigs.bll);
    IZConfigs.initializedEE = 0xbaba;
    EEPROM_writeAnything(0, IZConfigs);
  }
  else
  {
  if (IZConfigs.bll == 0xff)  // Verify the backlight isn't off
    analogWrite(BACKLIGHT, 0);
  else
    analogWrite(BACKLIGHT, IZConfigs.bll);
  }
  tft.initR(INITR_BLACKTAB);
  tft.setTextSize(1);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  textWhiteOnBlack();

// RTC init
  Wire.begin();  
  RTC.begin();
  if (! RTC.isrunning() )
  {
    tft.print(F("RTC-Setting time!"));
    RTC.adjust(DateTime(__DATE__, __TIME__));   }
    delay(1000);
}

//////////////////////////////////////////////////////////////////////////////////////
// loop - Menuing system has two functions, refresh and navigate
//////////////////////////////////////////////////////////////////////////////////////

void loop() 
{
  menuRefresh();
  menuNav();
}
