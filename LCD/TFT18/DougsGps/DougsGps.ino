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
// Using IR Sensor for display control
//
// Wiring/connections
//   Connect the GPS Power pin to 5V
//   Connect the GPS Ground pin to ground
//   Connect the GPS TX (transmit) pin to Digital 3
//   Connect the GPS RX (receive) pin to Digital 2
//   Connect the IR receiver to Digital 11
//  This display uses SPI to communicate, 5 pins are used to
//  interface with the display and I do use the RESET line.
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Includes follow
//////////////////////////////////////////////////////////////////////////////

#include <Adafruit_GPS.h>
#include "Wire.h"
#include <inttypes.h>
#include <SoftwareSerial.h>
#include <Time.h>  
#include <IRremote.h>
#include <eepromanything.h>
#include <EEPROM.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

//////////////////////////////////////////////////////////////////////////////
//#define SERIAL_OUT
//////////////////////////////////////////////////////////////////////////////

//#define SERIAL_OUT
#undef SERIAL_OUT

//////////////////////////////////////////////////////////////////////////////
// enums follow
//////////////////////////////////////////////////////////////////////////////

enum IR_VALUES
{
  NOKEY = 0,
  CHMINUS,
  CH,
  CHPLUS,
  LEFT,
  RIGHT,
  PAUSE,
  MINUS,
  PLUS,
  EQ,
  ZEROKEY,
  V100PLUS,
  V200PLUS,
  ONEKEY,
  TWOKEY,
  THREEKEY,
  FOURKEY,
  FIVEKEY,
  SIXKEY,
  SEVENKEY,
  EIGHTKEY,
  NINEKEY,
};

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
//////////////////////////////////////////////////////////////////////////////

// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO  false
#define RXCOUNTMAX 32
#define cs   10
#define dc   9
#define rst  8

//////////////////////////////////////////////////////////////////////////////
// Global variables follow
//////////////////////////////////////////////////////////////////////////////

SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);
Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);

// this keeps track of whether we're using the interrupt
// off by default!
boolean usingInterrupt = false;

unsigned long timer = millis();

int menuState;

char currentWayPoint;
int rxCount;
char rxBuffer[RXCOUNTMAX];

int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;

float fLat2, fLon2;

struct storeVals
{
  unsigned char myCurrentWayPoint;
  float lats[20], lons[20];
} 
myStoreVals;


//////////////////////////////////////////////////////////////////////////////
// setup()
//////////////////////////////////////////////////////////////////////////////

void setup()  
{
  Serial.begin(9600);

  GPSInit();

  menuState = MENU0;

  tft.initR(INITR_REDTAB);

  irrecv.enableIRIn(); // Start the receiver

  EEPROM_readAnything(0,myStoreVals);
  currentWayPoint = myStoreVals.myCurrentWayPoint;

  tft.setTextSize(1);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
}

//////////////////////////////////////////////////////////////////////////////
// loop()
//////////////////////////////////////////////////////////////////////////////

void loop()                     // run over and over again
{
  geocacheMenu();
}

//////////////////////////////////////////////////////////////////////////////
// loop()
//////////////////////////////////////////////////////////////////////////////

void clearLine(int lineToClear)
{
  setCursorTFT(lineToClear,0);
  tft.print("                    ");
  setCursorTFT(lineToClear,0);
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
//
//////////////////////////////////////////////////////////////////////////////

void setFArray(int wayPointNum, float latF, float longF)
{
  myStoreVals.lats[wayPointNum] = latF;
  myStoreVals.lons[wayPointNum] = longF;
}

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////

void dumpFArray(void)
{
}

//////////////////////////////////////////////////////////////////////////////////////
// bearing and distance calculations from gerard's coobro geo code base
//////////////////////////////////////////////////////////////////////////////////////

int calc_bearing(float flat1, float flon1, float flat2, float flon2)
{
  float calc;
  float bear_calc; 

  float x = 69.1 * (flat2 - flat1);
  float y = 69.1 * (flon2 - flon1) * cos(flat1/57.3);

  calc=atan2(y,x);
  bear_calc= degrees(calc);

  if(bear_calc<=1)
  {
    bear_calc=360+bear_calc;
  }
  return bear_calc;
} 

//////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////

unsigned long calc_dist(float flat1, float flon1, float flat2, float flon2)
{
  float dist_calc=0;
  float dist_calc2=0;
  float diflat=0;
  float diflon=0;

  diflat=radians(flat2-flat1);
  flat1=radians(flat1);
  flat2=radians(flat2);
  diflon=radians((flon2)-(flon1));

  dist_calc = (sin(diflat/2.0)*sin(diflat/2.0));
  dist_calc2= cos(flat1);
  dist_calc2*=cos(flat2);
  dist_calc2*=sin(diflon/2.0);
  dist_calc2*=sin(diflon/2.0);
  dist_calc +=dist_calc2;

  dist_calc=(2*atan2(sqrt(dist_calc),sqrt(1.0-dist_calc)));

  dist_calc*=6371000.0; //Converting to meters
  return dist_calc;
}

void setCursorTFT(int row, int col)
{
  tft.setCursor(col*5, row*10);
}

