// Menu System for the VFO

enum MenuStateValues
{
  SET_STEP_SIZE,
  SET_FREQ,
  SELECT_VFO,
  VFO_ON_OFF,
  SET_CAL_FACTOR,
  SAVE_INIT_VALS
};

//enum ControlsState
//{
//  NOTHING,
//  ENC_SW_PRESSED,
//  ENC_UP,
//  ENC_DOWN
//};

MenuStateValues menuState = SET_FREQ;

void printCalFactor(void)
{
  char buffer[14];
  itoa(calFactor, buffer, 10);
  printStringToOLED(buffer);
}

void setCalFactor(void)
{
  uint8_t controlVal;
  printCalFactor();
  while (1)
  {
    controlVal = waitForControlChange();
    if (controlVal == ENC_SW_PRESSED)
      return;
   else if (controlVal == ENC_UP)
    {
      calFactor += 1;
      si5351.set_correction(calFactor, SI5351_PLL_INPUT_XO);
      printCalFactor();
    }
    else if (controlVal == ENC_DOWN)
    {
      calFactor -= 1;
      si5351.set_correction(calFactor, SI5351_PLL_INPUT_XO);
      printCalFactor();
    }
  }
}

void saveInitValuesToEEPROM(void)
{
  #ifdef HAS_INTERNAL_EEPROM
    storeEEPROM();
    printStringToOLED("Stored");
    delay(1000);
  #endif
}

//
void printVFOFreq(void)
{
  if (currentVFONumber == 0)
    displayFreqInKHzOnOLED(float(VFO_0_Freq / 100ULL));
  else if (currentVFONumber == 1)
    displayFreqInKHzOnOLED(float(VFO_1_Freq / 100ULL));
  else if (currentVFONumber == 2)
    displayFreqInKHzOnOLED(float(VFO_2_Freq / 100ULL));
}

//
void setVFOFreq(void)
{
  uint8_t controlVal;
  printVFOFreq();
  while (1)
  {
    controlVal = waitForControlChange();
    if (controlVal == ENC_SW_PRESSED)
      return;
    else if (controlVal == ENC_UP)
    {
      if (currentVFONumber == 0)
      {
        VFO_0_Freq += stepSize; // count up by step size
        if (VFO_0_Freq > 4000000000ULL)
          VFO_0_Freq = 4000000000ULL; // Limit top of range
        si5351.set_freq(VFO_0_Freq, SI5351_CLK0);
      }
      else if (currentVFONumber == 1)
      {
        VFO_1_Freq += stepSize; // count up by step size
        if (VFO_1_Freq > 4000000000ULL)
          VFO_1_Freq = 4000000000ULL; // Limit top of range
        si5351.set_freq(VFO_1_Freq, SI5351_CLK1);
      }
      else if (currentVFONumber == 2)
      {
        VFO_2_Freq += stepSize; // count up by step size
        if (VFO_2_Freq > 4000000000ULL)
          VFO_2_Freq = 4000000000ULL; // Limit top of range
        si5351.set_freq(VFO_2_Freq, SI5351_CLK2);
      }
    }
    else if (controlVal == ENC_DOWN)
    {
      if (currentVFONumber == 0)
      {
        VFO_0_Freq -= stepSize; // count down by step size
        if ((VFO_0_Freq < 1000000ULL) || (VFO_0_Freq > 4000000000ULL))
          VFO_0_Freq = 1000000ULL;
        si5351.set_freq(VFO_0_Freq, SI5351_CLK0);
      }
      else if (currentVFONumber == 1)
      {
        VFO_1_Freq -= stepSize; // count down by step size
        if ((VFO_1_Freq < 1000000ULL) || (VFO_1_Freq > 4000000000ULL))
          VFO_1_Freq = 1000000ULL;
        si5351.set_freq(VFO_1_Freq, SI5351_CLK1);
      }
      else if (currentVFONumber == 2)
      {
        VFO_2_Freq -= stepSize; // count down by step size
        if ((VFO_2_Freq < 1000000ULL) || (VFO_2_Freq > 4000000000ULL))
          VFO_2_Freq = 1000000ULL;
        si5351.set_freq(VFO_2_Freq, SI5351_CLK2);
      }
    }
    printVFOFreq();
  }
}

//
void printVFONumber(void)
{
  if (currentVFONumber == 0)
    printStringToOLED("VFO CLK0");
  else if (currentVFONumber == 1)
    printStringToOLED("VFO CLK1");
  else if (currentVFONumber == 2)
    printStringToOLED("VFO CLK2");
}

void selectVFO(void)
{
  uint8_t controlVal;
  printVFONumber();
  while (1)
  {
    controlVal = waitForControlChange();
    if (controlVal == ENC_SW_PRESSED)
      return;
    else if (controlVal == ENC_UP)
    {
      if (currentVFONumber == 0)
        currentVFONumber = 1;
      else if (currentVFONumber == 1)
        currentVFONumber = 2;
    }
    else if (controlVal == ENC_DOWN)
    {
      if (currentVFONumber == 2)
        currentVFONumber = 1;
      else if (currentVFONumber == 1)
        currentVFONumber = 0;
    }
    printVFONumber();
  }
}

void printVFOOnOff(void)
{
  if (currentVFONumber == 0)
  {
    if (VFO_O_OnOff == VFO_ON)
      printStringToOLED("VFO CLK0 On");
    else
      printStringToOLED("VFO CLK0 Off");
  }
  else if (currentVFONumber == 1)
  {
    if (VFO_1_OnOff == VFO_ON)
      printStringToOLED("VFO CLK1 On");
    else
      printStringToOLED("VFO CLK1 Off");
  }
  else if (currentVFONumber == 2)
  {
    if (VFO_2_OnOff == VFO_ON)
      printStringToOLED("VFO CLK2 On");
    else
      printStringToOLED("VFO CLK2 Off");
  }
}

void toggleVFOOnOff(void)
{
  uint8_t controlVal;
  printVFOOnOff();
  while (1)
  {
    controlVal = waitForControlChange();
    if (controlVal == ENC_SW_PRESSED)
      return;
    else if (controlVal == ENC_UP)
    {
      if (currentVFONumber == 0)
      {
        VFO_O_OnOff = VFO_ON;
        si5351.output_enable(SI5351_CLK0, 1);
      }
      else if (currentVFONumber == 1)
      {
        VFO_1_OnOff = VFO_ON;
        si5351.output_enable(SI5351_CLK1, 1);
      }
      else if (currentVFONumber == 2)
        VFO_2_OnOff = VFO_ON;
      si5351.output_enable(SI5351_CLK2, 1);
    }
    else if (controlVal == ENC_DOWN)
    {
      if (currentVFONumber == 0)
      {
        VFO_O_OnOff = VFO_OFF;
        si5351.output_enable(SI5351_CLK0, 0);
      }
      else if (currentVFONumber == 1)
      {
        VFO_1_OnOff = VFO_OFF;
        si5351.output_enable(SI5351_CLK1, 0);
      }
      else if (currentVFONumber == 2)
      {
        VFO_2_OnOff = VFO_OFF;
        si5351.output_enable(SI5351_CLK2, 0);
      }
    }
    printVFOOnOff();
  }
}

void printStepSize(void)
{
  if (stepSize == STEP_1_HZ)
    printStringToOLED("Step 1 Hz");
  else if (stepSize == STEP_10_HZ)
    printStringToOLED("Step 10 Hz");
  else if (stepSize == STEP_100_HZ)
    printStringToOLED("Step 100 Hz");
  else if (stepSize == STEP_1_KHZ)
    printStringToOLED("Step 1 KHz");
  else if (stepSize == STEP_10_KHZ)
    printStringToOLED("Step 10 KHz");
  else if (stepSize == STEP_100_KHZ)
    printStringToOLED("Step 100 KHz");
  else if (stepSize == STEP_1_MHZ)
    printStringToOLED("Step 1 MHz");
  else if (stepSize == STEP_10_MHZ)
    printStringToOLED("Step 10 MHz");
  return;
}

void setVFOStepSize(void)
{
  uint8_t controlVal;
  printStepSize();
  while (1)
  {
    controlVal = waitForControlChange();
    if (controlVal == ENC_SW_PRESSED)
      return;
    else if (controlVal == ENC_UP)
    {
      if (stepSize == STEP_1_HZ)
        stepSize = STEP_10_HZ;
      else if (stepSize == STEP_10_HZ)
        stepSize = STEP_100_HZ;
      else if (stepSize == STEP_100_HZ)
        stepSize = STEP_1_KHZ;
      else if (stepSize == STEP_1_KHZ)
        stepSize = STEP_10_KHZ;
      else if (stepSize == STEP_10_KHZ)
        stepSize = STEP_100_KHZ;
      else if (stepSize == STEP_100_KHZ)
        stepSize = STEP_1_MHZ;
      else if (stepSize == STEP_1_MHZ)
        stepSize = STEP_10_MHZ;
    }
    else if (controlVal == ENC_DOWN)
    {
      if (stepSize == STEP_10_HZ)
        stepSize = STEP_1_HZ;
      else if (stepSize == STEP_100_HZ)
        stepSize = STEP_10_HZ;
      else if (stepSize == STEP_1_KHZ)
        stepSize = STEP_100_HZ;
      else if (stepSize == STEP_10_KHZ)
        stepSize = STEP_1_KHZ;
      else if (stepSize == STEP_100_KHZ)
        stepSize = STEP_10_KHZ;
      else if (stepSize == STEP_1_MHZ)
        stepSize = STEP_100_KHZ;
      else if (stepSize == STEP_10_MHZ)
        stepSize = STEP_1_MHZ;
    }
    printStepSize();
  }

}

void displayTopMenuOption()
{
  if (menuState == SET_STEP_SIZE)
    printStringToOLED("Set Step Size");
  else if (menuState == SET_FREQ)
    printStringToOLED("Set Freq");
  else if (menuState == SELECT_VFO)
    printStringToOLED("Select VFO");
  else if (menuState == VFO_ON_OFF)
    printStringToOLED("VFO On/Off");
  else if (menuState == SET_CAL_FACTOR)
    printStringToOLED("Set Cal Value");
  else if (menuState == SAVE_INIT_VALS)
    printStringToOLED("Save defaults");
}

// Menu options
// Menu is entered by pressing encoder button
void vfoMenu(void)
{
  uint8_t controlVal;
  while (1)
  {
    displayTopMenuOption();
    controlVal = waitForControlChange();
    if (controlVal == ENC_SW_PRESSED)
    {
      if (menuState == SET_STEP_SIZE)
        setVFOStepSize();
      else if (menuState == SET_FREQ)
        setVFOFreq();
      else if (menuState == SELECT_VFO)
        selectVFO();
      else if (menuState == VFO_ON_OFF)
        toggleVFOOnOff();
      else if (menuState == SET_CAL_FACTOR)
        setCalFactor();
      else if (menuState == SAVE_INIT_VALS)
        saveInitValuesToEEPROM();
    }
    else if (controlVal == ENC_UP)
    {
      if (menuState == SET_STEP_SIZE)
        menuState = SET_FREQ;
      else if (menuState == SET_FREQ)
        menuState = SELECT_VFO;
      else if (menuState == SELECT_VFO)
        menuState = VFO_ON_OFF;
      else if (menuState == VFO_ON_OFF)
        menuState = SET_CAL_FACTOR;
      else if (menuState == SET_CAL_FACTOR)
        menuState = SAVE_INIT_VALS;
    }
    else if (controlVal == ENC_DOWN)
    {
      if (menuState == SAVE_INIT_VALS)
        menuState = SET_CAL_FACTOR;
      else if (menuState == SET_CAL_FACTOR)
        menuState = VFO_ON_OFF;
      else if (menuState == VFO_ON_OFF)
        menuState = SELECT_VFO;
      else if (menuState == SELECT_VFO)
        menuState = SET_FREQ;
      else if (menuState == SET_FREQ)
        menuState = SET_STEP_SIZE;
    }
  }
}
