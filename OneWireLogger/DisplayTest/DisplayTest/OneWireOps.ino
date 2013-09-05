//////////////////////////////////////////////////////////////////////////////
// do1Wire() - Run the 1 Wire Interface
//////////////////////////////////////////////////////////////////////////////

void do1Wire(void)
{
  int key;
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  setCursorTFT(0,0);
  tft.print("Do 1 Wire");
  do
  {
    key = myOneWireLogger.pollKeypad();
  }
 while (key == NONE); 
}

