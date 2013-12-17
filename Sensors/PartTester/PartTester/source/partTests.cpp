#include "PartTester_main.h"


void testKeyPad(void)
{
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Testing Keypad");
    setCursorTFT(1,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Hold SELECT to exit");
      long loopCount = 0;
      int key;
      tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
      while (loopCount < 100)
      {
        key = myMiniDuino.pollKeypad();
        setCursorTFT(2,0);
        switch (key)
        {
        case NONE:
          tft.print("NONE  ");
          loopCount = 0;
          break;
        case LEFT:
          tft.print("LEFT  ");
          loopCount = 0;
          break;
        case RIGHT:
          tft.print("RIGHT ");
          loopCount = 0;
          break;
        case UP:
          tft.print("UP    ");
          loopCount = 0;
          break;
        case DOWN:
          tft.print("DOWN  ");
          loopCount = 0;
          break;
        case SELECT:
          tft.print("SELECT");
          loopCount++;
          break;
        }
      }
      setCursorTFT(3,0);
      tft.print("EXITING, release Sel");
      while (myMiniDuino.pollKeypad() == SELECT);
}

void test1Wire(void)
{
  
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Testing 1-Wire");
    do
    {
    read1Wire();
    }
    while (myMiniDuino.pollKeypad() == NONE);
    while (myMiniDuino.pollKeypad() != NONE);
}

void testTmp36(void)
{
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Testing TMP36A");
      setCursorTFT(1,0);
      int tmpAna;
      do
      {
      tmpAna = analogRead(ANALOGIN1);
      tft.print(tmpAna);
      tft.print("   ");
      }
    while (myMiniDuino.pollKeypad() == NONE);
    while (myMiniDuino.pollKeypad() != NONE);
}

void testLDR(void)
{
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Testing LDR");
    do
    {
      setCursorTFT(1,0);
      int tmpAna;
      tmpAna = analogRead(ANALOGIN1);
      tft.print(tmpAna);
      tft.print("   ");
    }
    while (myMiniDuino.pollKeypad() == NONE);
    while (myMiniDuino.pollKeypad() != NONE);
}

void testLED(void)
{
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Testing LED");
    pinMode(DIGIO6, OUTPUT);
    do
    {
      setCursorTFT(1,0);
      digitalWrite(DIGIO6, HIGH);   // turn the LED off
//      if (myMiniDuino.delayAvailable(1000) != 0)
      digitalWrite(DIGIO6, LOW);    // turn the LED on
//      if (myMiniDuino.delayAvailable(1000) != 0)
    }
    while (myMiniDuino.pollKeypad() == NONE);
    while (myMiniDuino.pollKeypad() != NONE);
    digitalWrite(DIGIO6, HIGH);
  
}

void testRelay(void)
{
    tft.fillScreen(ST7735_BLACK);
    setCursorTFT(0,0);
    tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
    tft.print("Testing Relays");
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    do
    {
      setCursorTFT(1,0);
      digitalWrite(2, LOW);    // turn the LED on
      if (myMiniDuino.delayAvailable(1000) != 0)
        break;
      digitalWrite(2, HIGH);   // turn the LED off
      if (myMiniDuino.delayAvailable(1000) != 0)
        break;
      digitalWrite(3, LOW);    // turn the LED on
      if (myMiniDuino.delayAvailable(1000) != 0)
        break;
      digitalWrite(3, HIGH);   // turn the LED off
      if (myMiniDuino.delayAvailable(1000) != 0)
        break;
    }
    while (myMiniDuino.pollKeypad() == NONE);
    while (myMiniDuino.pollKeypad() != NONE);
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
  }



