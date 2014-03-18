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
  tft.print(F("Backlight Adj"));
  setDisplayCursor(1,0);
  tft.print(F("Sel=Save, rt/lf=exit"));
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
    tft.print("    ");
    setDisplayCursor(0,14);
    tft.print((100*(250-IZConfigs.bll))/250);
    tft.print("%");
  }
  while ((key != SELECT) && (key != RIGHT) && (key != LEFT));
  if (key == SELECT)
  {
    EEPROM_writeAnything(0, IZConfigs);
    setDisplayCursor(1,0);
    tft.print(F("Saving Config......."));
    delay(1500);
  }
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

//////////////////////////////////////////////////////////////////////////////
// textWhiteOnBlack() - 
//////////////////////////////////////////////////////////////////////////////

void textWhiteOnBlack(void)
{
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
}

//////////////////////////////////////////////////////////////////////////////////////
// setCursorTFT(int row, int col)
//////////////////////////////////////////////////////////////////////////////////////

void setCursorTFT(int row, int col)
{
  tft.setCursor(col*6, row*10);
}

