// vfoMenu
// Menu System for VFO-003 card
// 
// 128x32 OLED Screen is 16 col, 4 row
// Print in 16x16 font for short menus
// Print in 8x8 font for short menus and some options screens
//
// Rotary encoder scrolls between options
// Press encoder button to select

uint8_t topMenuCurrentLine, level2MenuCurrentLine;

//  initMenu()
//  Set to top lines of each menu at startup
void initMenu(void)
{
  topMenuCurrentLine = 0;
  level2MenuCurrentLine = 0; 
}

//  vfoMenu() -  Top level menu
//  Control, Setup
void vfoMenu(void)
{
  ControlsState controlVal;
  u8x8.clearDisplay();
  displayTopMenuOption();
  controlVal = waitForControlChange();
  if (controlVal == ENC_UP)
  {
    if (topMenuCurrentLine == 0)
      topMenuCurrentLine = 1;
    else if (topMenuCurrentLine == 1)
      topMenuCurrentLine = 2;
  }
  else if (controlVal == ENC_DOWN)
  {
    if (topMenuCurrentLine == 1)
      topMenuCurrentLine = 0;
    else if (topMenuCurrentLine == 2)
      topMenuCurrentLine = 1;
  }
  else if (controlVal == ENC_SW_PRESSED)
  {
    if (topMenuCurrentLine == 0)
      controlMenu();
    else if (topMenuCurrentLine == 1)
      clkCtrlMenu();
    else if (topMenuCurrentLine == 2)
      setupMenu();
  }
}

// displayTopMenuOption()
// Operate, Clk Config, Setup
void displayTopMenuOption(void)
{
   if (topMenuCurrentLine == 0)
      u8x8.setInverseFont(1);
   u8x8.drawString(0,0,"Operate");
   u8x8.setInverseFont(0);
   if (topMenuCurrentLine == 1)
      u8x8.setInverseFont(1);
   u8x8.drawString(0,1,"Clk Config");
   u8x8.setInverseFont(0);
   if (topMenuCurrentLine == 2)
      u8x8.setInverseFont(1);
   u8x8.drawString(0,2,"Setup");
   u8x8.setInverseFont(0);
}

// Display Control Menu - Controls screen
// Set Freq, Select Clk, Step Size, Return
void displayControlMenu(void)
{
  u8x8.clearDisplay();
  if (level2MenuCurrentLine == 0)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,0,"Set Freq");
  u8x8.setInverseFont(0);
  if (level2MenuCurrentLine == 1)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,1,"Select Clk");
  u8x8.setInverseFont(0);
  if (level2MenuCurrentLine == 2)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,2,"Step Size");
  u8x8.setInverseFont(0);
  if (level2MenuCurrentLine == 3)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,3,"Return");
  u8x8.setInverseFont(0);
}

// Display Clock Control Menu
void displayClkCtrlMenu(void)
{
  u8x8.clearDisplay();
  if (level2MenuCurrentLine == 0)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,0,"Clk Mult 1x/4x");
  u8x8.setInverseFont(0);
  if (level2MenuCurrentLine == 1)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,1,"Return");
  u8x8.setInverseFont(0);
}

//  Clock Control Menu
// Set 1x_4x, return
void clkCtrlMenu(void)
{
  ControlsState controlVal;
  level2MenuCurrentLine = 0;
  while(1)
  {
    displayClkCtrlMenu();
    controlVal = waitForControlChange();
    if (controlVal == ENC_UP)
    {
      if (level2MenuCurrentLine < 3)
        level2MenuCurrentLine += 1;
    }
    else if (controlVal == ENC_DOWN)
    {
      if (level2MenuCurrentLine > 0)
        level2MenuCurrentLine -= 1;
    }
    else if (controlVal == ENC_SW_PRESSED)
    {
      if (level2MenuCurrentLine == 0)
        setVFO1x4x();
      else if (level2MenuCurrentLine == 1)
        return;
    }
  }
}

// Control Menu
// Set VFO Freq, Select VFO, Set VFO Step Size, Return
void controlMenu(void)
{
  ControlsState controlVal;
  level2MenuCurrentLine = 0;
  while(1)
  {
    displayControlMenu();
    controlVal = waitForControlChange();
    if (controlVal == ENC_UP)
    {
      if (level2MenuCurrentLine < 3)
        level2MenuCurrentLine += 1;
    }
    else if (controlVal == ENC_DOWN)
    {
      if (level2MenuCurrentLine > 0)
        level2MenuCurrentLine -= 1;
    }
    else if (controlVal == ENC_SW_PRESSED)
    {
      if (level2MenuCurrentLine == 0)
        setVFOFreq();
      else if (level2MenuCurrentLine == 1)
        selectVFO();
      else if (level2MenuCurrentLine == 2)
        setVFOStepSize();
      else if (level2MenuCurrentLine == 3)
        return;
    }
  }
}

// VFO Off/On, Calibrate, Save Defaults, Return
void displaySetupMenu(void)
{
 u8x8.clearDisplay();
  if (level2MenuCurrentLine == 0)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,0,"VFO Off/On");
  u8x8.setInverseFont(0);
  if (level2MenuCurrentLine == 1)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,1,"Calibrate");
  u8x8.setInverseFont(0);
  if (level2MenuCurrentLine == 2)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,2,"Save Defaults");
  u8x8.setInverseFont(0);
  if (level2MenuCurrentLine == 3)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,3,"Return");
  u8x8.setInverseFont(0);
}

// Setup menu
void setupMenu(void)
{
  ControlsState controlVal;
  level2MenuCurrentLine = 0;
  while(1)
  {
    displaySetupMenu();
    controlVal = waitForControlChange();
    if (controlVal == ENC_UP)
    {
      if (level2MenuCurrentLine < 3)
        level2MenuCurrentLine += 1;
    }
    else if (controlVal == ENC_DOWN)
    {
      if (level2MenuCurrentLine > 0)
        level2MenuCurrentLine -= 1;
    }
    else if (controlVal == ENC_SW_PRESSED)
    {
      if (level2MenuCurrentLine == 0)
        toggleVFOOnOff();
      else if (level2MenuCurrentLine == 1)
        setCalFactor();
      else if (level2MenuCurrentLine == 2)
        saveInitValuesToEEPROM();
      else if (level2MenuCurrentLine == 3)
        return;
    }
  }
}
