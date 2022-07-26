// LBLED7Segment.ino
// Scroll Land-Boards across the LEDs on 8-digits MAX7219 

#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 Arduino UNO pin 12 is connected to the DataIn 
 Arduino UNO pin 11 is connected to the CLK 
 Arduino UNO pin 10 is connected to LOAD 
 Connector Power/Ground
 We have only a single MAX72XX.
 */
 
LedControl lc=LedControl(12,11,10,1);

/* we always wait a bit between updates of the display */
unsigned long delaytime=250;

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
  lc.setChar(0,7,'l',false);    // L
  delay(delaytime);
  lc.setRow(0,6,0x7d);          // a
  delay(delaytime);
  lc.setRow(0,5,0x15);          // n
  delay(delaytime);
  lc.setChar(0,4,'d',false);    // d
  delay(delaytime);
  lc.setRow(0,3,(CENTER));      // -
  delay(delaytime*4);
  lc.clearDisplay(0);
  lc.setChar(0,7,'b',false);    // b
  delay(delaytime);
  lc.setRow(0,6,(LL|CENTER|BOTTOM|LR));          // o
  delay(delaytime);
  lc.setRow(0,5,0x7d);          // a
  delay(delaytime);
  lc.setRow(0,4,(LL|CENTER));          // r
  delay(delaytime);
  lc.setChar(0,3,'d',false);    // d
  delay(delaytime);
  lc.setRow(0,2 ,(BOTTOM|LR|CENTER|UL|TOP));          // S
  delay(delaytime*4);
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
