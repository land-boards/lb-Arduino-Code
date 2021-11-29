// VFO Top Level Menu Options - Menu System for VFO-003 card
// 
// 128x32 OLED Screen is 16 col, 4 row
// Print in 8x8 font
//
// Rotary encoder moves between options
// Press encoder button to select

/* Menu Structure - Function Names
    Top Level - vfoTopLevelMenuOps() / displayTopMenuOps()
        Operate - operateMenuOps() / displayOperateMenuOps()
            Set Freq - setVFOFreq() / displayFreqOnOLED() / printVFOFreq()
            Step Size - setVFOStepSize() / printStepSize()
            Band - setBandVal() / printBand()
            Return
         Clk Config - clkConfigMenuOps() / displayClkConfigMenuOps()
            Select Clk - selectVFO() / printVFONumber()
            VFO Off/On - toggleVFOOnOff() / printVFOOnOff()
            Clk Mult 1x/4x - setVFO1x4x() / printVFO1x4x()
            Return
         Setup - setupMenuOps() / displaySetupMenuOps()
            Calibrate - setCalFactor() / printCalFactor()
            Save Defaults - saveInitValuesToEEPROM()
            Return
*/

uint8_t topMenuCurrentLine, level2MenuCurrentLine;

//  initMenu()
//  Set to top lines of each menu at startup
void initMenu(void)
{
  topMenuCurrentLine = 0;
  level2MenuCurrentLine = 0; 
}

//  Top level menu
//  Ooperate, Clk Config, Setup
void vfoTopLevelMenuOps(void)
{
  ControlsState controlVal;
  u8x8.clearDisplay();
  displayTopMenuOps();
  controlVal = waitForControlChange();
  if (controlVal == ENC_UP)
  {
    if (topMenuCurrentLine < 3)
      topMenuCurrentLine += 1;
  }
  else if (controlVal == ENC_DOWN)
  {
    if (topMenuCurrentLine > 0)
      topMenuCurrentLine -= 1;
  }
  else if (controlVal == ENC_SW_PRESSED)
  {
    if (topMenuCurrentLine == 0)
      operateMenuOps();
    else if (topMenuCurrentLine == 1)
      clkConfigMenuOps();
    else if (topMenuCurrentLine == 2)
      setupMenuOps();
    else if (topMenuCurrentLine == 3)
      memoryOps();
  }
}

// Display Top Menu
// Operate, Clk Config, Setup
void displayTopMenuOps(void)
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
   if (topMenuCurrentLine == 3)
      u8x8.setInverseFont(1);
   u8x8.drawString(0,3,"Memories");
   u8x8.setInverseFont(0);
}

// Clock Config Menu
// Set VFO Freq, Select VFO, Set VFO Step Size, Return
void operateMenuOps(void)
{
  ControlsState controlVal;
  level2MenuCurrentLine = 0;
  while(1)
  {
    displayOperateMenuOps();
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
        setVFOStepSize();
      else if (level2MenuCurrentLine == 2)
        setBandVal();
      else if (level2MenuCurrentLine == 3)
        return;
    }
  }
}

// Display Ooperate  Menu - Controls screen
// Set Freq, Step Size, Return
void displayOperateMenuOps(void)
{
  u8x8.clearDisplay();
  if (level2MenuCurrentLine == 0)
    u8x8.setInverseFont(1);
  u8x8.drawString(0,0,"Set Freq");
  u8x8.setInverseFont(0);
  if (level2MenuCurrentLine == 1)
    u8x8.setInverseFont(1);
  u8x8.drawString(0,1,"Step Size");
  u8x8.setInverseFont(0);
  if (level2MenuCurrentLine == 2)
    u8x8.setInverseFont(1);
  u8x8.drawString(0,2,"Set Band");
  u8x8.setInverseFont(0);
  if (level2MenuCurrentLine == 3)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,3,"Return");
  u8x8.setInverseFont(0);
}

//  Clock Config Menu
// Select Clk, VFO Off/ON, Clk Mult 1x_4x, Return
void clkConfigMenuOps(void)
{
  ControlsState controlVal;
  level2MenuCurrentLine = 0;
  while(1)
  {
    displayClkConfigMenuOps();
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
        selectVFO();
      else if (level2MenuCurrentLine == 1)
        toggleVFOOnOff();
      else if (level2MenuCurrentLine == 2)
        setVFO1x4x();
      else if (level2MenuCurrentLine == 3)
        return;
    }
  }
}

// Display Clock Config Menu
void displayClkConfigMenuOps(void)
{
  u8x8.clearDisplay();
  if (level2MenuCurrentLine == 0)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,0,"Select Clk");
  u8x8.setInverseFont(0);
  if (level2MenuCurrentLine == 1)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,1,"VFO Off/On");
  u8x8.setInverseFont(0);
  if (level2MenuCurrentLine == 2)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,2,"Clk Mult 1x/4x");
  u8x8.setInverseFont(0);
  if (level2MenuCurrentLine == 3)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,3,"Return");
  u8x8.setInverseFont(0);
}

// Setup menu Ooperatioons
void setupMenuOps(void)
{
  ControlsState controlVal;
  level2MenuCurrentLine = 0;
  while(1)
  {
    displaySetupMenuOps();
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
        setCalFactor();
      else if (level2MenuCurrentLine == 1)
        saveInitValuesToEEPROM();
      else if (level2MenuCurrentLine == 2)
        displayCtrlOps();
      else if (level2MenuCurrentLine == 3)
        return;
    }
  }
}

// Display Setup Menu Operations
// Calibrate, Save Defaults, Return
void displaySetupMenuOps(void)
{
 u8x8.clearDisplay();
  if (level2MenuCurrentLine == 0)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,0,"Calibrate");
  u8x8.setInverseFont(0);
  if (level2MenuCurrentLine == 1)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,1,"Save Defaults");
  u8x8.setInverseFont(0);
  if (level2MenuCurrentLine == 2)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,2,"Display On/Off");
  u8x8.setInverseFont(0);
  if (level2MenuCurrentLine == 3)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,3,"Return");
  u8x8.setInverseFont(0);
}

// Memory Options
// There are 8 memories
// Memories can read read/written
void memoryOps(void)
{
  uint8_t controlVal;
  printMemoryOps();
  level2MenuCurrentLine = 0;
  while(1)
  {
    printMemoryOps();
    controlVal = waitForControlChange();
    if (controlVal == ENC_UP)
    {
      if (level2MenuCurrentLine < 2)
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
        loadMemoryOps();
      else if (level2MenuCurrentLine == 1)
        storeMemoryOps();
      else if (level2MenuCurrentLine == 2)
        return;
    }
    printMemoryOps();
  }
}

// Print the memory options
void printMemoryOps(void)
{
  u8x8.clearDisplay();
  if (level2MenuCurrentLine == 0)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,0,"Load Memory");
  u8x8.setInverseFont(0);
  if (level2MenuCurrentLine == 1)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,1,"Store Memory");
  u8x8.setInverseFont(0);
  if (level2MenuCurrentLine == 2)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,2,"Return");
  u8x8.setInverseFont(0);
}
