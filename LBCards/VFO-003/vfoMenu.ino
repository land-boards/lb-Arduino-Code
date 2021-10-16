// vfoMenu
// Menu System for VFO-003
// Rotary encoder scrolls between options
// Press encoder button to select

enum MenuStateValues
{
  SET_STEP_SIZE,
  SET_FREQ,
  SELECT_VFO,
  VFO_ON_OFF,
  SET_CAL_FACTOR,
  SAVE_INIT_VALS
};

uint8_t topMenuCurrentLine, level2MenuCurrentLine;

void initMenu(void)
{
  topMenuCurrentLine = 0;
  level2MenuCurrentLine = 0; 
}

// Default start up menu
MenuStateValues menuState = SET_FREQ;

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
  }
  else if (controlVal == ENC_DOWN)
  {
    if (topMenuCurrentLine == 1)
      topMenuCurrentLine = 0;
  }
  else if (controlVal == ENC_SW_PRESSED)
  {
    if (topMenuCurrentLine == 0)
      controlMenu();
    else if (topMenuCurrentLine == 1)
      setupMenu();
  }
}

// Freq, VFO Number, Step Size, Return
void displayControlMenu(void)
{
  u8x8.clearDisplay();
  if (level2MenuCurrentLine == 0)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,0,"Set Freq");
  u8x8.setInverseFont(0);
  if (level2MenuCurrentLine == 1)
      u8x8.setInverseFont(1);
  u8x8.drawString(0,1,"Select  Clk");
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

// displayTopMenuOption()
void displayTopMenuOption(void)
{
   if (topMenuCurrentLine == 0)
      u8x8.setInverseFont(1);
   u8x8.draw2x2String(0,0,"Control");
   u8x8.setInverseFont(0);
   if (topMenuCurrentLine == 1)
      u8x8.setInverseFont(1);
   u8x8.draw2x2String(0,2,"Setup");
   u8x8.setInverseFont(0);
}
