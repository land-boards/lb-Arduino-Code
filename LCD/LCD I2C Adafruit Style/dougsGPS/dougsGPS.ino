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
// LCD is Newhaven Displays NHD-0420D3Z-NSW-BBW available from Digikey
//    ------> http://parts.digikey.com/1/parts/2399832-lcd-serial-4x20-side-wht-bklt-nhd-0420d3z-nsw-bbw.html
// LCD is also available from Mouser:
//    ------> http://www.mouser.com/ProductDetail/Newhaven-Display/NHD-0420D3Z-NSW-BBW/?qs=sGAEpiMZZMt7dcPGmvnkBqgJ77dQR2sz%252bTAd1I
// Using IR Sensor for display control
//
// Wiring/connections
//   Connect the GPS Power pin to 5V
//   Connect the GPS Ground pin to ground
//   Connect the GPS TX (transmit) pin to Digital 3
//   Connect the GPS RX (receive) pin to Digital 2
//   Connect the IR receiver to Digital 11
//   Connect the LCD to A4/A5 (I2C interface)
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//#define SERIAL_OUT
//////////////////////////////////////////////////////////////////////////////

#undef SERIAL_OUT

//////////////////////////////////////////////////////////////////////////////
// Includes follow
//////////////////////////////////////////////////////////////////////////////

#include <Adafruit_GPS.h>
#include "Wire.h"
#include <inttypes.h>
#include <LCDi2cNHD.h>                    
#include <SoftwareSerial.h>
#include <Time.h>  
#include <IRremote.h>

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

//////////////////////////////////////////////////////////////////////////////
// defines follow
//////////////////////////////////////////////////////////////////////////////

// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO  false

//////////////////////////////////////////////////////////////////////////////
// Global variables follow
//////////////////////////////////////////////////////////////////////////////

SoftwareSerial mySerial(3, 2);

Adafruit_GPS GPS(&mySerial);

// this keeps track of whether we're using the interrupt
// off by default!
boolean usingInterrupt = false;

LCDi2cNHD lcd = LCDi2cNHD(4,20,0x50>>1,0);

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

unsigned long timer = millis();

int menuState;

char currentWayPoint;

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
  MENU4,
  MENU4B,
  MENU4C,
};

//////////////////////////////////////////////////////////////////////////////
// setup()
//////////////////////////////////////////////////////////////////////////////

void setup()  
{
  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out
#ifdef SERIAL_OUT
  Serial.begin(115200);
  Serial.println("Adafruit GPS library basic test!");
#endif

  GPSInit();

  irrecv.enableIRIn(); // Start the receiver
  menuState = MENU0;
  currentWayPoint = 0;

  lcd.init();
}

//////////////////////////////////////////////////////////////////////////////
// loop()
//////////////////////////////////////////////////////////////////////////////

void loop()                     // run over and over again
{
  int pressedKey = checkIR();
  switch (menuState)
  {
  case MENU0:
    lcd.setCursor(0,0);
    lcd.print("** Doug's GPS v01 **");
    delay(200);
    lcd.setCursor(1,0);
    lcd.print("> Monitor GPS Loc'n ");
    lcd.setCursor(2,0);
    lcd.print("Monitor Clock       ");
    lcd.setCursor(3,0);
    lcd.print("Download  Waypoints ");
    menuState = MENU0B;
    break;
  case MENU0B:
    if (pressedKey != NOKEY)
    {
      if (pressedKey == PAUSE)
      {
        clearLine(2);
        clearLine(3);
        menuState = MENU0C;
      }
      else if (pressedKey == RIGHT)
        menuState = MENU1;
    }
    break;
  case MENU0C:
    if (pressedKey != NOKEY)
      menuState = MENU0;
    readGPS();
    break;
  case MENU1:
    lcd.setCursor(1,0);
    lcd.print("> Monitor Clock     ");
    lcd.setCursor(2,0);
    lcd.print("Download  Waypoints ");
    lcd.setCursor(3,0);
    lcd.print("Go to Waypoint      ");
    menuState = MENU1B;
    break;
  case MENU1B:
    if (pressedKey != NOKEY)
    {
      if (pressedKey == PAUSE)
      {
        clearLine(2);
        clearLine(3);
        menuState = MENU1C;
      }
      else if (pressedKey == LEFT)
        menuState = MENU0;
      else if (pressedKey == RIGHT)
        menuState = MENU2;
    }
    break;
  case MENU1C:
    if (pressedKey != NOKEY)
      menuState = MENU1;
    GPSClock();
    break;
  case MENU2:
    lcd.setCursor(1,0);
    lcd.print("Monitor Clock       ");
    lcd.setCursor(2,0);
    lcd.print("> Download Waypoints");
    lcd.setCursor(3,0);
    lcd.print("Go to Waypoint      ");
    menuState = MENU2B;
    break;
  case MENU2B:
    if (pressedKey != NOKEY)
    {
      if (pressedKey == PAUSE)
      {
        clearLine(2);
        clearLine(3);
        menuState = MENU2C;
      }
      else if (pressedKey == LEFT)
        menuState = MENU1;
      else if (pressedKey == RIGHT)
        menuState = MENU3;
    }
    break;
  case MENU2C:
    if (pressedKey != NOKEY)
      menuState = MENU2;
    lcd.setCursor(1,0);
    lcd.print("Downloading WAYPNTS ");
    break;
  case MENU3:
    lcd.setCursor(1,0);
    lcd.print("Monitor Clock       ");
    lcd.setCursor(2,0);
    lcd.print("Download  Waypoints ");
    lcd.setCursor(3,0);
    lcd.print("> Go to Waypoint    ");
    menuState = MENU3B;
    break;
  case MENU3B:
    if (pressedKey != NOKEY)
    {
      if (pressedKey == PAUSE)
      {
        lcd.setCursor(1,0);
        lcd.print("Going to Waypoint   ");
        clearLine(2);
        clearLine(3);
        menuState = MENU3C;
      }
      else if (pressedKey == LEFT)
        menuState = MENU2;
      else if (pressedKey == RIGHT)
        menuState = MENU4;
    }
    break;
  case MENU3C:
    if (pressedKey != NOKEY)
      menuState = MENU3;
    break;
  case MENU4:
    lcd.setCursor(1,0);
    lcd.print("Download  Waypoints ");
    lcd.setCursor(2,0);
    lcd.print("Go to Waypoint      ");
    lcd.setCursor(3,0);
    lcd.print("> Set Active Waypnt ");
    menuState = MENU4B;
    break;
  case MENU4B:
    if (pressedKey != NOKEY)
    {
      if (pressedKey == PAUSE)
      {
        lcd.setCursor(1,0);
        lcd.print("Select WayPoint     ");
        clearLine(2);
        clearLine(3);
      lcd.setCursor(2,0);
      lcd.print(currentWayPoint, DEC);
        menuState = MENU4C;
      }
      else if (pressedKey == LEFT)
        menuState = MENU3;
    }
    break;
  case MENU4C:
    {
      if (pressedKey != NOKEY)
      {
        switch(pressedKey)
        {
        case LEFT:
          menuState = MENU4;
          break;
        case PLUS:
          if (currentWayPoint < 9)
            currentWayPoint++;
          break;
        case MINUS:
          if (currentWayPoint > 0)
          currentWayPoint--;
          break;
        case ZEROKEY:
          currentWayPoint = 0;
          break;
        case ONEKEY:
          currentWayPoint = 1;
          break;
        case TWOKEY:
          currentWayPoint = 2;
          break;
        case THREEKEY:
          currentWayPoint = 3;
          break;
        case FOURKEY:
          currentWayPoint = 4;
          break;
        case FIVEKEY:
          currentWayPoint = 5;
          break;
        case SIXKEY:
          currentWayPoint = 6;
          break;
        case SEVENKEY:
          currentWayPoint = 7;
          break;
        case EIGHTKEY:
          currentWayPoint = 8;
          break;
        case NINEKEY:
          currentWayPoint = 9;
          break;
        }
      clearLine(2);
      lcd.setCursor(2,0);
      lcd.print(currentWayPoint, DEC);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
// loop()
//////////////////////////////////////////////////////////////////////////////

void clearLine(int lineToClear)
{
  lcd.setCursor(lineToClear,0);
  lcd.print("                    ");
}




