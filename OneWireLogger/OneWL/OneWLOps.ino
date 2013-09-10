//////////////////////////////////////////////////////////////////////////////
// OneWLOps() - Run the 1 Wire Interface
//////////////////////////////////////////////////////////////////////////////

void do1Wire(void)
{
  int key;
  tft.fillScreen(ST7735_BLACK);
  textWhiteOnBlack();
  setCursorTFT(0,0);
  tft.print("Do 1 Wire");
  do
  {
    key = myOneWireLogger.pollKeypad();
  }
 while (key == NONE); 
}

