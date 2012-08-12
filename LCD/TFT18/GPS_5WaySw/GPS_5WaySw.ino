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
//#define SERIAL_OUT
//////////////////////////////////////////////////////////////////////////////

//#define SERIAL_OUT
#undef SERIAL_OUT

#define DBG_TFT 1  

//////////////////////////////////////////////////////////////////////////////
// enums follow
//////////////////////////////////////////////////////////////////////////////

enum MENUITEMS
{
  MENU0,
  MENU0B,
  MENU0C,
  MENU1,
  MENU1B,
  MENU1C,
  MENU2,
  MENU2B,
  MENU2C,
  MENU3,
  MENU3B,
  MENU3C,
  MENU3D,
  MENU4,
  MENU4B,
  MENU4C,
  MENU5,
  MENU5B,
  MENU5C,
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
} myStoreVals;

struct lastGPSVal
{
  uint8_t hour, minute, seconds, year, month, day;
  uint16_t milliseconds;
  float latitude, longitude, geoidheight, altitude;
  uint8_t satellites;
  float speed, angle, magvariation, HDOP;
  boolean fix;
} myGPSStore;

//////////////////////////////////////////////////////////////////////////////
// class initializers
//////////////////////////////////////////////////////////////////////////////

SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);
Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);
switch5Way mySwitch;

//////////////////////////////////////////////////////////////////////////////
// setup()
//////////////////////////////////////////////////////////////////////////////

void setup()  
{

#ifdef SERIAL_OUT
  Serial.begin(9600);
#endif

  menuState = MENU0;

  tft.initR(INITR_REDTAB);

  EEPROM_readAnything(0,myStoreVals);
  currentWayPoint = myStoreVals.myCurrentWayPoint;

  tft.setTextSize(1);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);

  GPSInit();

}

//////////////////////////////////////////////////////////////////////////////
// loop()
//////////////////////////////////////////////////////////////////////////////

void loop()                     // run over and over again
{
  geocacheMenu();
}

//////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////

void debugMsg(char * debugMessage)
{
    clearLine(15);
    tft.print(debugMessage);
}

//////////////////////////////////////////////////////////////////////////////
// parseRxBuffer - save waypoints - rxBuffer[]
// Order is ww=aa.aaaa,ooo.ooo
// ww is the way point number
// aa.aaaa is the latitude
// 000.000 is the longitude
//////////////////////////////////////////////////////////////////////////////

int parseRxBuffer(void)
{
  int lineOffset;
  int floatStringOffset;
  char floatBuff[10];
  int wayPointNum;
  float latF, longF;
  if (rxBuffer[1] == '=')  //waypoints from 0-9
  {
    wayPointNum = rxBuffer[0] - '0';
    lineOffset = 2;
  }
  else if (rxBuffer[2] == '=')  // waypoints from 10-19
  {
    wayPointNum = ((rxBuffer[0] - '0') * 10);
    wayPointNum += (rxBuffer[1] - '0');
    lineOffset = 3;
  }
  else
    return(-1);
  floatStringOffset = 0;
  while (rxBuffer[lineOffset] != ',')
  {
    floatBuff[floatStringOffset++] = rxBuffer[lineOffset++];
  }
  floatBuff[floatStringOffset] = 0;
  latF=atof(floatBuff);
  lineOffset++;
  floatStringOffset = 0;
  while (rxBuffer[lineOffset] != 0)
  {
    floatBuff[floatStringOffset++] = rxBuffer[lineOffset++];
  }
  floatBuff[floatStringOffset] = 0;
  longF=atof(floatBuff);
  if ((wayPointNum >= 0) && (wayPointNum <= 19)) 
    setFArray(wayPointNum,latF,longF);
  else
    return(-2);
  return(0);
}

//////////////////////////////////////////////////////////////////////////////
// Set the lat long values in the buffer to the Geocache values
//////////////////////////////////////////////////////////////////////////////

void setFArray(int wayPointNum, float latF, float longF)
{
  myStoreVals.lats[wayPointNum] = latF;
  myStoreVals.lons[wayPointNum] = longF;
}

//////////////////////////////////////////////////////////////////////////////
// clearLine(int lineToClear)
//////////////////////////////////////////////////////////////////////////////

void clearLine(int lineToClear)
{
  setCursorTFT(lineToClear,0);
  tft.print("                     ");
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
  float endX = 64 + (43 * sin(angleRad));
  float endY = 110 + (43 * -(cos(angleRad)));
  tft.drawLine(64,110,lastX,lastY,ST7735_BLACK);
  tft.drawLine(64,110,endX,endY,ST7735_WHITE);
  lastX = endX;
  lastY  = endY;
}

