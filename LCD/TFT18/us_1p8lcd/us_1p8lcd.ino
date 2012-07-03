l///////////////////////////////////////////////////////////////////
//  This is a sketch for a 1.8" SPI display. 
//  This sketch works with the library for the Adafruit 
//  1.8" TFT Breakout w/SD card.
//  This display uses SPI to communicate, 5 pins are used to
//  interface with the display and I do use the RESET line.
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// includes - 
///////////////////////////////////////////////////////////////////

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include "Wire.h"
#include "LiquidCrystal.h"
#include "Ultrasonic.h"

Ultrasonic ultrasonic(6,5);


///////////////////////////////////////////////////////////////////
// Hardware pins
///////////////////////////////////////////////////////////////////

#define cs   10
#define dc   9
#define rst  8

///////////////////////////////////////////////////////////////////
// Uses the hardware SPI pins (for UNO sclk = 13 and sid = 11) 
// and pin 10 are outputs. 
///////////////////////////////////////////////////////////////////

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);

short ranges[5];

///////////////////////////////////////////////////////////////////
// setup() - 
///////////////////////////////////////////////////////////////////

void setup(void)
{
//  Serial.begin(9600);
  tft.initR(INITR_REDTAB);
  tft.setTextSize(1);
  tft.fillScreen(ST7735_BLACK);
  setCursorTFT(0, 0);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  tft.print("Distance");
  initRanges();
  }

void putNewRange(long newRangeVal)
{
 ranges[0] = ranges[1];
 ranges[1] = ranges[2];
 ranges[2] = ranges[3];
 ranges[3] = ranges[4];
 ranges[4] = newRangeVal;
 return;
}

void initRanges(void)
{
  putNewRange(ultrasonic.Ranging(INC));
  putNewRange(ultrasonic.Ranging(INC));
  putNewRange(ultrasonic.Ranging(INC));
  putNewRange(ultrasonic.Ranging(INC));
  putNewRange(ultrasonic.Ranging(INC));  
}

short getRangeVal(void)
{
  if (ranges[4] == ranges[3])
    return(ranges[4]);
  else if (ranges[4] == ranges[3] + 1)
    return(ranges[3]);
  else if (ranges[4] == ranges[3] -1 )
    return(ranges[3]);
  else if (ranges[4] == ranges[2])
    return(ranges[4]);
  else if (ranges[3] == ranges[2])
    return(ranges[3]);
  else if (ranges[2] == ranges[1])
    return(ranges[2]);
  else return(ranges[4]);
  
}

///////////////////////////////////////////////////////////////////
// setCursorTFT(int row, int col)
///////////////////////////////////////////////////////////////////

void setCursorTFT(int row, int col)
{
	tft.setCursor(row*8, col*8);
}

///////////////////////////////////////////////////////////////////
// loop() - 
///////////////////////////////////////////////////////////////////

void loop() 
{
  setCursorTFT(0,1);
  putNewRange(ultrasonic.Timing());
  tft.print(getRangeVal());
  tft.print("   ");
}


