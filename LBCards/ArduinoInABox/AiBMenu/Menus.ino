/*
   Menus - Menu code

*/

//
void doTopLevelMenu(void)
{
  uint8_t selectedMenuLine = 0;
  uint8_t ctrlVal;
  while (1)
  {
    displayTopMenu(selectedMenuLine);
    ctrlVal = waitForControlChange();
    if ((ctrlVal == ENC_UP) and (selectedMenuLine < 3))
      selectedMenuLine++;
    else if ((ctrlVal == ENC_DOWN) and (selectedMenuLine > 0))
      selectedMenuLine--;
    else if (ctrlVal == ENC_SW_PRESSED)
      runSelectedTop(selectedMenuLine);
  }
}

//
void displayTopMenu(uint8_t activeLineNum)
{
  u8x8.clearDisplay();
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  if (activeLineNum == 0)
    u8x8.setInverseFont(1);
  else
    u8x8.setInverseFont(0);
  u8x8.drawString(0, 0, "Blink LEds");
  if (activeLineNum == 1)
    u8x8.setInverseFont(1);
  else
    u8x8.setInverseFont(0);
  u8x8.drawString(0, 1, "Line 2");
  if (activeLineNum == 2)
    u8x8.setInverseFont(1);
  else
    u8x8.setInverseFont(0);
  u8x8.drawString(0, 2, "Line 3");
  if (activeLineNum == 3)
    u8x8.setInverseFont(1);
  else
    u8x8.setInverseFont(0);
  u8x8.drawString(0, 3, "Line 4");
}

//
void runSelectedTop(uint8_t activeLineNum)
{
  if (activeLineNum == 0)
  {
    blinkAll();
  }
  else if (activeLineNum == 0)
  {
    delay(500);
  }
  else if (activeLineNum == 0)
  {
    delay(500);
  }
  else if (activeLineNum == 0)
  {
    delay(500);
  }
}
