//////////////////////////////////////////////////////////////////////////////
//
// dougsGPS - Doug's GPS
//
// Based on adafruit's test code for Adafruit GPS modules
//
// Hardware -
// Board is either an UNO or Screwduino
//    ------> http://myarduino.pbworks.com/w/page/51198530/Screwduino
// GPS hardware is Adafruit's Ultimate GPS module using MTK3339 driver
//    ------> http://www.adafruit.com/products/746
//  This sketch works with the library for the Adafruit 
//  1.8" TFT Breakout w/SD card.
// Using 5-Way switch for display control
//
// Wiring/connections
//   Connect the GPS Power pin to 5V
//   Connect the GPS Ground pin to ground
//   Connect the GPS TX (transmit) pin to Digital 3
//   Connect the GPS RX (receive) pin to Digital 2
//   Connect the 5-Way Switch to Analog 0
//   Connect the Display GND (Power Ground) to Ground
//   Connect the Display SD_CS (Chipselect for TF Card, active low) to pin 7
//   Connect the Display LCD_CS (Chipselect for LCD, active low) to pin 10
//   Connect the Display SCLK (SPI Clock) to Digital pin 13
//   Connect the Display MOSI (SPI Master out Slave in) to Digital pin 11
//   Connect the Display MISO (SPI Master in Slave out) to Digital pin N/C (could be pin 12)
//   Connect the Display RS (Command/Data Selection) to Digital pin 9
//   Connect the Display RESET (LCD controller reset, active low) to Digital pin 8 
//   Connect the Display BKL (LCD back light, active low) to power pin Ground
//   Connect the Display VCC (5V power input) to power pin +5V
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Includes follow
//////////////////////////////////////////////////////////////////////////////

#include <Adafruit_GPS.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <inttypes.h>
#include <SoftwareSerial.h>
#include <Time.h>
#include <Sw5Way.h>
#include <eepromanything.h>    // http://arduino.cc/playground/Code/EEPROMWriteAnything
#include <EEPROM.h> 
#include <SPI.h>

//////////////////////////////////////////////////////////////////////////////
//#defines
//////////////////////////////////////////////////////////////////////////////

//#define SERIAL_DEBUG
#undef SERIAL_DEBUG

//#define DBG_TFT 1
#undef DBG_TFT

//////////////////////////////////////////////////////////////////////////////
// enums follow
//////////////////////////////////////////////////////////////////////////////

enum MENU_STATE_VALUES
{
  MONGPSLOCN_MENU,
  MONGPSCLK_MENU,
  MANWAYPTS_MENU,
  LOGGING_MENU,
  GOTOWAYPTS_MENU,
  DOWNLDWAYS_MENU,
  SETACTWAYS_MENU,
  SHOWWAYPTS_MENU,
  STARTLOGGING_MENU,
  STOPLOGGING_MENU,
  DUMPLOGFILE_MENU,
  CLRLOGFILE_MENU,
};

//////////////////////////////////////////////////////////////////////////////
// defines follow
// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
//////////////////////////////////////////////////////////////////////////////

#define GPSECHO  false
#define RXCOUNTMAX 32
#define cs   10
#define dc   9
#define rst  8

//////////////////////////////////////////////////////////////////////////////
// Global variables follow
//////////////////////////////////////////////////////////////////////////////

// this keeps track of whether we're using the interrupt
// off by default!
boolean usingInterrupt = false;

long timer = millis();

int menuState;

char currentWayPoint;
int rxCount;
char rxBuffer[RXCOUNTMAX];

// decode_results results;  // IR results

float fLat2, fLon2;
float lastLat, lastLon;
float bearing;
float lastAngle;
float lastBearing;
int lastSats;
float lastX, lastY;

struct storeVals
{
  unsigned char myCurrentWayPoint;
  float lats[20], lons[20];
} 
myStoreVals;

struct lastGPSVal
{
  uint8_t hour, minute, seconds, year, month, day;
  uint16_t milliseconds;
  float latitude, longitude, geoidheight, altitude;
  uint8_t satellites;
  float speed, angle, magvariation, HDOP;
  boolean fix;
} 
myGPSStore;

//////////////////////////////////////////////////////////////////////////////
// class initializers
//////////////////////////////////////////////////////////////////////////////

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);

SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);
switch5Way mySwitch;

//////////////////////////////////////////////////////////////////////////////
// setup()
//////////////////////////////////////////////////////////////////////////////

void setup()  
{

  Serial.begin(57600);

  menuState = MONGPSLOCN_MENU;

  tft.initR(INITR_REDTAB);

  EEPROM_readAnything(0,myStoreVals);
  currentWayPoint = myStoreVals.myCurrentWayPoint;

  tft.setTextSize(1);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  tft.print(F("** Doug's GPS v0.8 **"));

  GPSInit();

}

//////////////////////////////////////////////////////////////////////////////
// loop()
//////////////////////////////////////////////////////////////////////////////

void loop()                     // run over and over again
{
  menuRefresh();
  menuNav();
}

//////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////

void debugMsg(char * debugMessage)
{
#ifdef DBG_TFT
  clearLine(15);
  tft.print(debugMessage);
#endif
}

//////////////////////////////////////////////////////////////////////////////
// clearLine(int lineToClear)
//////////////////////////////////////////////////////////////////////////////

void clearLine(int lineToClear)
{
  tft.fillRect(0,lineToClear*10,128,10,ST7735_BLACK);
  setCursorTFT(lineToClear,0);
}

//////////////////////////////////////////////////////////////////////////////////////
// setCursorTFT(int row, int col)
//////////////////////////////////////////////////////////////////////////////////////

void setCursorTFT(int row, int col)
{
  tft.setCursor(col*6, row*10);
}

//////////////////////////////////////////////////////////////////////////////////////
// void drawVector(int angle)
//////////////////////////////////////////////////////////////////////////////////////

void drawVector(float angle)
{
  float angleRad = (angle * 3.141592654 / 180.0);
  float endX = 64 - (43 * sin(angleRad));
  float endY = 110 + (43 * -(cos(angleRad)));
  tft.drawLine(64,110,lastX,lastY,ST7735_BLACK);
  tft.drawLine(64,110,endX,endY,ST7735_WHITE);
  lastX = endX;
  lastY  = endY;
}


