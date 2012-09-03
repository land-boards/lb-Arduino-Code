// Test code for Adafruit GPS modules using MTK3329/MTK3339 driver
//
// This code turns on the LOCUS built-in datalogger. The datalogger
// turns off when power is lost, so you MUST turn it on every time
// you want to use it!
//
// Tested and works great with the Adafruit Ultimate GPS module
// using MTK33x9 chipset
//    ------> http://www.adafruit.com/products/746
// Pick one up today at the Adafruit electronics shop 
// and help support open source hardware & software! -ada

#include <Adafruit_GPS.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <Sw5Way.h>
#include <SPI.h>

// these are for Arduino 1.0
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2);

// if using Arduino v23 or earlier, uncomment these
// two lines and comment out the above. You will
// need to install NewSoftSerial
//  #include <NewSoftSerial.h>
//  NewSoftSerial mySerial(3, 2);

// Connect the GPS Power pin to 5V
// Connect the GPS Ground pin to ground
// Connect the GPS TX (transmit) pin to Digital 3
// Connect the GPS RX (receive) pin to Digital 2
Adafruit_GPS GPS(&mySerial);

// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO  false

// this keeps track of whether we're using the interrupt
// off by default!
boolean usingInterrupt = false;

#define cs   10
#define dc   9
#define rst  8

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);
switch5Way mySwitch;


void setup()  
{    
  // connect at 115200 so we can read the GPS fast enuf and
  // also spit it out
  Serial.begin(115200);

  tft.initR(INITR_REDTAB);
  tft.setTextSize(1);
  tft.fillScreen(ST7735_BLACK);
  setCursorTFT(0, 0);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);


  tft.print("GPS logger");


  // 9600 NMEA is the default baud rate for MTK - some use 4800
  GPS.begin(9600);

  // You can adjust which sentences to have the module emit, below
  // Default is RMC + GGA
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // Default is 1 Hz update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

  // the nice thing about this code is you can have a timer0 interrupt go off
  // every 1 millisecond, and read data from the GPS for you. that makes the
  // loop code a heck of a lot easier!
  useInterrupt(true);

  while (true) 
  {
    setCursorTFT(1,0);
    tft.print("Starting logging...");
    if (GPS.LOCUS_StartLogger()) 
    {
      setCursorTFT(2,0);
      tft.println(" STARTED!");
      break;
    } 
    else 
    {
      setCursorTFT(2,0);
      tft.println(" no response :(");
    }
  }
}



void loop()                     // run over and over again
{
  delay(1000);

  if (GPS.LOCUS_ReadStatus()) 
  {
    setCursorTFT(3,0);
    tft.print("Log #"); 
    tft.print(GPS.LOCUS_serial, DEC);
    setCursorTFT(4,0);
    if (GPS.LOCUS_type == LOCUS_OVERLAP)
      tft.print(",Overlap,");
    else if (GPS.LOCUS_type == LOCUS_FULLSTOP)
      tft.print(",Full Stop,Logging");

    setCursorTFT(5,0);
    if (GPS.LOCUS_mode & 0x1) tft.print("AlwysLoc");
    if (GPS.LOCUS_mode & 0x2) tft.print(",FixOnly");
    setCursorTFT(6,0);
    if (GPS.LOCUS_mode & 0x4) tft.print("Normal");
    if (GPS.LOCUS_mode & 0x8) tft.print(",Interval");
    setCursorTFT(7,0);
    if (GPS.LOCUS_mode & 0x10) tft.print("Distance");
    if (GPS.LOCUS_mode & 0x20) tft.print(",Speed");

    setCursorTFT(8,0);
    tft.print("Cont-"); 
    tft.print(GPS.LOCUS_config);
    tft.print(",Intvl-"); 
    tft.print(GPS.LOCUS_interval);
    setCursorTFT(9,0);
    tft.print("Dist-"); 
    tft.print(GPS.LOCUS_distance);
    tft.print(",Spd-"); 
    tft.print(GPS.LOCUS_speed);
    setCursorTFT(10,0);
    tft.print("Stat-"); 
    if (GPS.LOCUS_status) 
      tft.print(" LOGGING,");
    else 
      tft.print(" OFF, ");
    setCursorTFT(11,0);
    tft.print(GPS.LOCUS_records); 
    tft.print(" Recs,");
    tft.print(GPS.LOCUS_percent); 
    tft.print("% Used"); 
  }
}

/******************************************************************/
// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
  if (GPSECHO)
    if (c) UDR0 = c;  
  // writing direct to UDR0 is much much faster than Serial.print 
  // but only one character can be written at a time. 

}

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } 
  else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

//////////////////////////////////////////////////////////////////////////////////////
// setCursorTFT(int row, int col)
//////////////////////////////////////////////////////////////////////////////////////

void setCursorTFT(int row, int col)
{
  tft.setCursor(col*6, row*10);
}

