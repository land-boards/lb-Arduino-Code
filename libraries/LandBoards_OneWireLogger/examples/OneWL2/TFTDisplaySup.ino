//////////////////////////////////////////////////////////////////////////////
// TFTDisplaySup - Display Support Functions
// Maps generic "Display" functions to the actual device used
// This instance is for the 1.8" TFT LCD color display
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// setBLt() - Set the display backlight level
// Assumes that the backlight is controlled from an Analog Output pin
// Brightness is PWM controlled
//////////////////////////////////////////////////////////////////////////////

void setBLt(void)
{
  uint8_t key;
  clearDisplay();
  tft.print(F("Set Bklt"));
  setDisplayCursor(1,0);
  tft.print(F("Sel=Save"));
  do
  {
    key = myOneWireLogger.pollKeypad();
    delay(100);   // allows for holding the up or down key continuously
    if ((key == DOWN) && (IZConfigs.bll <= 250))
      IZConfigs.bll += 5;
    else if ((key == UP) && (IZConfigs.bll >= 5))
      IZConfigs.bll -= 5;
    analogWrite(BACKLIGHT, IZConfigs.bll);
    setDisplayCursor(0,14);
    tft.print(F("    "));
    setDisplayCursor(0,14);
    tft.print((100*(250-IZConfigs.bll))/250);
    tft.print(F("%"));
  }
  while (key != SELECT);
}

//////////////////////////////////////////////////////////////////////////////////////
// setDisplayCursor(int row, int col) - Sets the cursor to a specific point on the display
//////////////////////////////////////////////////////////////////////////////////////

void setDisplayCursor(uint8_t row, uint8_t col)
{
  tft.setCursor(col*6, row*10);
}

//////////////////////////////////////////////////////////////////////////////////////
// clearDisplay() - 
// Clears the entire display
// Sets the cursor to the top of the screen
// Sets the text color to White on Black
// Sets the text size to the smallish size
//////////////////////////////////////////////////////////////////////////////////////

void clearDisplay(void)
{
  tft.fillScreen(ST7735_BLACK);
  setDisplayCursor(0,0);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  tft.setTextSize(1);
}

//////////////////////////////////////////////////////////////////////////////////////
// setBannerTextColor - Sets the color of the banner printed at the top of the screen
//////////////////////////////////////////////////////////////////////////////////////

void setBannerTextColor(void)
{
  tft.setTextColor(ST7735_WHITE,TFT_RED);
}

//////////////////////////////////////////////////////////////////////////////////////
// setUnselectedTextColor() - Sets the color of the text for non-selected text
//////////////////////////////////////////////////////////////////////////////////////

void setUnselectedTextColor(void)
{
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
}

//////////////////////////////////////////////////////////////////////////////////////
// setSelectedTextColor() - Sets the color of the text for selected (current menu selection) text
//////////////////////////////////////////////////////////////////////////////////////

void setSelectedTextColor(void)
{
  tft.setTextColor(ST7735_WHITE,TFT_BLUE);
}

