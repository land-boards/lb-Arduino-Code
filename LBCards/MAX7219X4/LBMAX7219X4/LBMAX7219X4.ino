// LBMAX7219X4.ino
// Displays Land-Boards across the LEDs on 8-digits MAX7219
// First "LAND-", "BOARDS", "PRESENTS", "CARDS..."

#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 Arduino UNO pin 12 is connected to the DataIn 
 Arduino UNO pin 11 is connected to the CLK 
 Arduino UNO pin 10 is connected to CS
 Connector Power/Ground
 We have only a single MAX72XX.
 */

#define DATAIN_PIN 12
#define CLK_PIN 11
#define CS_PIN 10
#define NUM_DEVICES 4
 
LedControl lc=LedControl(DATAIN_PIN,CLK_PIN,CS_PIN,NUM_DEVICES);

/* we always wait a bit between updates of the display */
unsigned long delaytime=75;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
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
 
void writeLandBoardsOn7Seg() 
{
  lc.setChar(0,31,'l',false);    // L
  delay(delaytime);
  lc.setChar(0,30,'a',false);    // A
  delay(delaytime);
  lc.setChar(0,29,'n',false);    // n
  delay(delaytime);
  lc.setChar(0,28,'d',false);    // d
  delay(delaytime);
  lc.setChar(0,27,'-',false);    // -
  delay(delaytime);
  lc.setChar(0,23,'b',false);    // b
  delay(delaytime);
  lc.setChar(0,22,'o',false);    // o
  delay(delaytime);
  lc.setChar(0,21,'a',false);    // A
  delay(delaytime);
  lc.setRow(0,20,(LL|CENTER));          // r
  delay(delaytime);
  lc.setChar(0,19,'d',false);    // d
  delay(delaytime);
  lc.setRow(0,18 ,(BOTTOM|LR|CENTER|UL|TOP));          // S
  delay(delaytime);
  lc.setChar(0,15,'p',false);    // P
  delay(delaytime);
  lc.setRow(0,14,(LL|CENTER));          // r
  delay(delaytime);
  lc.setDigit(0,13,0xe,false);    // e
  delay(delaytime);
  lc.setRow(0,12,(BOTTOM|LR|CENTER|UL|TOP));          // S
  delay(delaytime);
  lc.setDigit(0,11,0xe,false);    // e
  delay(delaytime);
  lc.setChar(0,10,'n',false);    // n
  delay(delaytime);
  lc.setRow(0,9,(UL|LL|BOTTOM|CENTER));          // t
  delay(delaytime);
  lc.setRow(0,8,(BOTTOM|LR|CENTER|UL|TOP));          // S
  delay(delaytime);
  lc.setDigit(0,7,0xc,false);    // c
  delay(delaytime);
  lc.setDigit(0,6,0xa,false);    // a
  delay(delaytime);
  lc.setRow(0,5,(LL|CENTER));          // r
  delay(delaytime);
  lc.setDigit(0,4,0xd,false);    // a
  delay(delaytime);
  lc.setRow(0,3,(BOTTOM|LR|CENTER|UL|TOP));          // S
  delay(delaytime);
  lc.setChar(0,2,' ',true);    // period
  delay(delaytime);
  lc.setChar(0,1,' ',true);    // period
  delay(delaytime);
  lc.setChar(0,0,' ',true);    // period
  delay(delaytime*5);
  lc.clearDisplay(0);
  delay(delaytime*20);
} 

/*
  This method will scroll the display.
 */
void scrollDigits() {
  for(int i=0;i<9;i++) {
    lc.setDigit(0,7,i,false);
    lc.setDigit(0,6,i+1,false);
    lc.setDigit(0,5,i+2,false);
    lc.setDigit(0,4,i+3,false);
    lc.setDigit(0,3,i+4,false);
    lc.setDigit(0,2,i+5,false);
    lc.setDigit(0,1,i+6,false);
    lc.setDigit(0,0,i+7,false);
    delay(delaytime);
  }
  lc.clearDisplay(0);
  delay(delaytime);
}

void loop() { 
  lc.clearDisplay(0);
  delay(delaytime);
  writeLandBoardsOn7Seg();
//  scrollDigits();
}
