/*********************************************************************

  10MHz GPS linked Frequency Standard

  UBLOX Module

  Wiki page for Arduino In A Box
    http://land-boards.com/blwiki/index.php?title=ArduinoInABox

  Runs on a 3.3V Arduino Pro Mini
  No 5V to 3.3V level shifting is needed for the I2C port of the OLED
  Arduino Pro Mini has internal EEPROM for parameter storage

  OLED is 128x32 I2C device
  SSD1306 controller
  OLED driver Wiki page
    https://github.com/olikraus/u8g2/wiki/u8x8reference
    8x8 font has 16x4 characters
    https://github.com/olikraus/u8g2/wiki/fntlist8x8

  Adapted from original by SCULLCOM Hobby Electronics
  http://www.scullcom.uk/design-build-a-gps-locked-frequency-standard-part-4/

*********************************************************************/

#include <Arduino.h>
#include <U8g2lib.h>
#include "ublox.h"

// defines and enums - Set defines/undefs appropriately

#define PIN_GPS_RX    255 //was 14 changed to 255 a nonexsistent pin number used to free up a pin
#define PIN_GPS_TX    15  //to GPS module RX pin

// Rotary encoder pins on the Arduino Pro Mini
#define ROTARY_DATA 2
#define ROTARY_CLK 3
#define encoderSwitch  4

#define U8X8_HAVE_HW_I2C

// Constructors

U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(U8X8_PIN_NONE);

UBloxGPS gps(PIN_GPS_RX, PIN_GPS_TX);   //PIN_GPS_TX is connected to the RX pin on the GPS module.

SoftwareSerial GPSreceiver (14, 255); //14 (A0) is RX in on Arduino connected to GPS TX pin. 255 a nonexsistent pin number used to free up a pin

// Gloibal variables

enum ControlsState
{
  NOTHING,
  ENC_SW_PRESSED,
  ENC_UP,
  ENC_DOWN
};

long StartFreq = 10000000;   //sets initial frequency of locked GPS frequency at 1MHz
long SetFreq = 0;
float NewFreq = StartFreq;
float CurrentFrequency = 0;

String sats;        //number of satellites detected
String GPGGAdata;   //satellte data string from GPS module
String FreqStatus;  //used to print Frequency locked if applicable
int satNum;         //number of satellites detected as an interger

String range;       //frequency range for display either MHz, KHz or Hz
int decimalPlaces;  //number of decimal places used dependant on range

void setup()
{

  Serial.begin(57600);
  GPSreceiver.begin(9600);

  u8x8.begin();
  u8x8.setBusClock(400000);   // I2C clock = 400 KHz
  u8x8.clearDisplay();
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  // Draw with 2x font
  u8x8.draw2x2String(0, 0, "Arduino");
  u8x8.draw2x2String(0, 2, "in a Box");
  delay(1000);

  // Rotary encoder initialization
  setupEncoder();

}

void loop()
{
  u8x8.clearDisplay();
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  // Draw with 2x font
  u8x8.draw2x2String(0, 0, "Waiting");
  u8x8.draw2x2String(0, 2, "for lock");
  while (waitForLock() == 0);
  u8x8.clearDisplay();
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  // Draw with 2x font
  u8x8.draw2x2String(0, 0, "Locked");
  delay(1000);
  gps.writeFrequency(StartFreq); //sets start up frequency when locked
  while (1);
}

// waitForLock()
uint8_t waitForLock(void)
{
  uint8_t locked = 0;
  char gpsin[8] = "$GPGGA,";            //define a character string “$GPGGA,”
  
  GPSreceiver.flush();                  //clear any data which may be in the Serial Buffer
  if (GPSreceiver.available())          //if any GPS data is available
  {
    GPSreceiver.read();                 //read GPS serial data streams if available
  }
  if (GPSreceiver.find(gpsin))
  { //if serial data starts with the characters “$GPGGA,”
    GPGGAdata = GPSreceiver.readStringUntil('\n');   //read data until a carriage return
    sats = GPGGAdata.substring(39, 41); //extract number of satellites data
  }

  satNum = sats.toInt();              //convert sats string to an integeter so as to remove leading zero
  if (satNum > 0)
  {
    FreqStatus = "Frequency Locked";  //if satellites detected the status string = “Frequency Locked”
    locked = 1;
  }
  else
  {
    FreqStatus = "                ";  //16 spaces to clear line if no lock
     locked = 0;
  }

  Serial.print(GPGGAdata);          //These serial print lines are for testing using Serial Monitor
  Serial.println();                 //full GPGGA data sentence and then carriage return
  Serial.print("Satellite = ");
  Serial.print(satNum);
  Serial.println();
  Serial.print(FreqStatus);
  Serial.println();
  return (locked);
  }
