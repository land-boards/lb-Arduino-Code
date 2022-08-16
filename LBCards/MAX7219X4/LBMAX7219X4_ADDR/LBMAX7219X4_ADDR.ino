// LBMAX7219X4_ADDR.ino
// Addressable Hexadecimal display
// Arduino Example code
//
// MAX7219X4 card
//  http://land-boards.com/blwiki/index.php?title=MAX7219X4
//  Four rows with 8 digits per row
//  3.3V signal levels
//
// Arduino In a Box
//  http://land-boards.com/blwiki/index.php?title=ArduinoInABox
//  3.3V signal levels
//  8 MHz Arduino Pro Mini
//  Card also provides 5V on J9-1 (VRAW header)
//  5V on DC jack
//

#include "LedControl.h"

/*
 Arduino UNO pin 12 is connected to the DataIn 
 Arduino UNO pin 11 is connected to the CLK 
 Arduino UNO pin 10 is connected to CS
 Connector Power/Ground
 */

#define DATAIN_PIN 12
#define CLK_PIN 11
#define CS_PIN 10
#define NUM_DEVICES 4
 
LedControl lc=LedControl(DATAIN_PIN,CLK_PIN,CS_PIN,NUM_DEVICES);

/* we always wait a bit between updates of the display */
unsigned long delaytime=75;

void setup()
{
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
   Serial.begin(9600);
  lc.shutdown(0,false);
  lc.shutdown(1,false);
  lc.shutdown(2,false);
  lc.shutdown(3,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  lc.setIntensity(1,8);
  lc.setIntensity(2,8);
  lc.setIntensity(3,8);
  /* and clear the display */
}

/*
 This method will display the characters for the word "Land-boards". 
 setRow values
 0x01 = center
 0x02 = upper left
 0x04 =  lower left
 0x08 = bottom
 0x10 = lower right
 0x20 = upper right
 0x40 = top
 */
 
#define CENTER 0x1
#define UL 0x2
#define LL 0x4
#define BOTTOM 0x8
#define LR 0x10
#define UR 0x20
#define TOP 0x40

// Clear the display
void clearDigits()
{
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
}

// 8 columns, 4 rows
// rowVal = 0 is top row in display
// colVal = 0 = left character
void writeHexDigit(uint8_t rowVal, uint8_t colVal, uint8_t digitVal)
{
    lc.setDigit(3-rowVal,7-colVal,digitVal,false);    // e
}

void loop()
{
  int row, col;
  clearDigits();
  for (row=0; row<4; row++)
  {
    for (col=0; col<8; col++)
    {
      writeHexDigit(row, col, (((row<<3) + col) & 0xf));
      delay(delaytime);
    }
  }
  delay(delaytime*20);
  clearDigits();
  delay(delaytime*10);
  for (row=0; row<4; row++)
  {
    for (col=0; col<8; col++)
    {
      writeHexDigit(row, col, (((row<<3) + col) & 0xf));
    }
  }
  delay(delaytime*20);
  clearDigits();
  delay(delaytime*10);
  for (row=0; row<4; row++)
  {
    for (col=0; col<8; col++)
    {
      writeHexDigit(row, col, 8);
    }
  }
  delay(delaytime*20);
  clearDigits();
  delay(delaytime*10);
}
