// Menu System for the VFO

enum MenuStateValues
{
  SET_STEP_SIZE,
  SET_FREQ,
  VFO_ON_OFF,
  WAVEFORM_VAL,
  SAVE_INIT_VALS
};

enum ControlsState
{
  NOTHING,
  ENC_SW_PRESSED,
  ENC_UP,
  ENC_DOWN
};

MenuStateValues menuState = SET_FREQ;

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
  displayFreqInKHzOnOLED(float(VFO_0_Freq));
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
      VFO_0_Freq += stepSize; // count up by step size
      if (VFO_0_Freq > 12500000ULL)
        VFO_0_Freq   = 12500000ULL; // Limit top of range
      gen.SetFrequency(REG0, float(VFO_0_Freq));
    }
    else if (controlVal == ENC_DOWN)
    {
      VFO_0_Freq -= stepSize; // count down by step size
      if ((VFO_0_Freq < 1) || (VFO_0_Freq > 12500000ULL))
        VFO_0_Freq    = 1;
      gen.SetFrequency(REG0, float(VFO_0_Freq));
    }
    printVFOFreq();
  }
}

void printVFOOnOff(void)
{
  if (VFO_O_OnOff == VFO_ON)
    printStringToOLED("VFO On");
  else
    printStringToOLED("VFO Off");
}

void toggleVFOOnOff(void)
{
  uint8_t controlVal;
  while (1)
  {
    printVFOOnOff();
    controlVal = waitForControlChange();
    if (controlVal == ENC_SW_PRESSED)
      return;
    else if (controlVal == ENC_UP)
    {
      VFO_O_OnOff = VFO_ON;
      gen.EnableOutput(true);
    }
    else if (controlVal == ENC_DOWN)
    {
      VFO_O_OnOff = VFO_OFF;
      gen.EnableOutput(false);
    }
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
  else
    printStringToOLED("Error");
  return;
}

void setVFOStepSize(void)
{
  uint8_t controlVal;
  while (1)
  {
    printStepSize();
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
    }
  }
}

void displayWaveformType(void)
{
  if (waveformType == SINE_WAVE_TYPE)
    printStringToOLED("Sinewave");
  else if (waveformType == TRIANGLE_WAVE_TYPE)
    printStringToOLED("Trianglewave");
  else if (waveformType == SQUARE_WAVE_TYPE)
    printStringToOLED("Squarewave");
  else if (waveformType == HALF_SQUARE_WAVE_TYPE)
    printStringToOLED("Halfsqwave");
  else
    printStringToOLED("error");
}

void setWaveformType(void)
{
  uint8_t controlVal;
  while (1)
  {
    displayWaveformType();
    controlVal = waitForControlChange();
    if (controlVal == ENC_SW_PRESSED)
      return;
    else if (controlVal == ENC_UP)
    {
      if (waveformType == SINE_WAVE_TYPE)
      {
        waveformType = TRIANGLE_WAVE_TYPE;
        gen.ApplySignal(TRIANGLE_WAVE,REG0,float(VFO_0_Freq));
      }
      else if (waveformType == TRIANGLE_WAVE_TYPE)
      {
        waveformType = SQUARE_WAVE_TYPE;
        gen.ApplySignal(SQUARE_WAVE,REG0,float(VFO_0_Freq));
      }
      else if (waveformType == SQUARE_WAVE_TYPE)
      {
        waveformType = HALF_SQUARE_WAVE_TYPE;
        gen.ApplySignal(HALF_SQUARE_WAVE,REG0,float(VFO_0_Freq));
      }
    }
    else if (controlVal == ENC_DOWN)
    {
      if (waveformType == HALF_SQUARE_WAVE_TYPE)
      {
        waveformType = SQUARE_WAVE_TYPE;
        gen.ApplySignal(SQUARE_WAVE,REG0,float(VFO_0_Freq));
      }
      else if (waveformType == SQUARE_WAVE_TYPE)
      {
        waveformType = TRIANGLE_WAVE_TYPE;
        gen.ApplySignal(TRIANGLE_WAVE,REG0,float(VFO_0_Freq));
      }
      else if (waveformType == TRIANGLE_WAVE_TYPE)
      {
        waveformType = SINE_WAVE_TYPE;
        gen.ApplySignal(SINE_WAVE,REG0,float(VFO_0_Freq));
      }
    }
  }
}

void displayTopMenuOption()
{
  if (menuState == SET_STEP_SIZE)
    printStringToOLED("Set Step Size");
  else if (menuState == SET_FREQ)
    printStringToOLED("Set Freq");
  else if (menuState == VFO_ON_OFF)
    printStringToOLED("VFO On/Off");
  else if (menuState == WAVEFORM_VAL)
    printStringToOLED("Set waveform");
  else if (menuState == SAVE_INIT_VALS)
    printStringToOLED("Save defaults");
}

//enum WAVEFORM_TYPE
//{
//  SINE_WAVE_TYPE,
//  TRIANGLE_WAVE_TYPE,
//  SQUARE_WAVE_TYPE,
//  HALF_SQUARE_WAVE_TYPE
//};
//
//WAVEFORM_TYPE waveformType;

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
      else if (menuState == VFO_ON_OFF)
        toggleVFOOnOff();
      else if (menuState == WAVEFORM_VAL)
        setWaveformType();
      else if (menuState == SAVE_INIT_VALS)
        saveInitValuesToEEPROM();
    }
    else if (controlVal == ENC_UP)
    {
      if (menuState == SET_STEP_SIZE)
        menuState = SET_FREQ;
      else if (menuState == SET_FREQ)
        menuState = VFO_ON_OFF;
      else if (menuState == VFO_ON_OFF)
        menuState = WAVEFORM_VAL;
      else if (menuState == WAVEFORM_VAL)
        menuState = SAVE_INIT_VALS;
    }
    else if (controlVal == ENC_DOWN)
    {
      if (menuState == SAVE_INIT_VALS)
        menuState = WAVEFORM_VAL;
      else if (menuState == WAVEFORM_VAL)
        menuState = VFO_ON_OFF;
      else if (menuState == VFO_ON_OFF)
        menuState = SET_FREQ;
      else if (menuState == SET_FREQ)
        menuState = SET_STEP_SIZE;
    }
  }
}

uint8_t checkControls()
{
  int encoderDelta = 0;
  if (checkSwitch() == 1)
    return ENC_SW_PRESSED;
  pollEncoder();
  encoderDelta = getEncoderDelta();
  if (encoderDelta == 0)
    return (NOTHING);
  else if (encoderDelta == 1)
    return (ENC_UP);
  else if (encoderDelta == -1)
    return (ENC_DOWN);
  return (NOTHING);
}

// Wait around for an encoder change
uint8_t waitForControlChange(void)
{
  uint8_t controlVal;
  while (1)
  {
    do
    {
      controlVal = checkControls();
    }
    while (controlVal == NOTHING);
    return (controlVal);
  }
}
