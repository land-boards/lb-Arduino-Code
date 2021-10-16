// Menu Operations
//  Frequency
//  Cal factor

// printCalFactor
// Calibration facts are in 0.1 Hz steps
// Adjust frequency at 40.000,000 MHz (highest freq supported by this software)
// Use 8 digit frequency counter to adjust
void printCalFactor(void)
{
  char buffer[14];
  itoa(calFactor/10, buffer, 10);
  u8x8.clearDisplay();
  u8x8.draw2x2String(0,0,"Cal val");
  u8x8.draw2x2String(0,2,buffer);
}

// setCalFactor
// Adjust calibration factor by 0.1 Hz (more than precise enough but could be 0.01Hz if needed)
// TXCO is pretty accurate and does not need a lot of adjustment
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
      calFactor += 10;
      si5351.set_correction(calFactor, SI5351_PLL_INPUT_XO);
      printCalFactor();
    }
    else if (controlVal == ENC_DOWN)
    {
      calFactor -= 10;
      si5351.set_correction(calFactor, SI5351_PLL_INPUT_XO);
      printCalFactor();
    }
  }
}

// saveInitValuesToEEPROM
void saveInitValuesToEEPROM(void)
{
  #ifdef HAS_INTERNAL_EEPROM
    storeEEPROM();
    u8x8.clearDisplay();
    u8x8.draw2x2String(0,1,"Stored");
    delay(1000);
  #endif
}

void displayFreqInKHzOnOLED(float freq)
{
  char inBuffer[10];
  char outBuffer[15];
  uint8_t buffOff;
  if (freq >= 10000000)
  {
    // Adda a comma below the MHz digits
    // 0123456789012
    // 10000000
    // 10,000.000 KHz
    dtostrf(freq, 8, 0, inBuffer);
    outBuffer[0] = inBuffer[0];
    outBuffer[1] = inBuffer[1];
    outBuffer[2] = '.';
    outBuffer[3] = inBuffer[2];
    outBuffer[4] = inBuffer[3];
    outBuffer[5] = inBuffer[4];
    outBuffer[6] = ',';
    outBuffer[7] = inBuffer[5];
    outBuffer[8] = inBuffer[6];
    outBuffer[9] = inBuffer[7];
    outBuffer[10] = ' ';
    outBuffer[11] = 'M';
    outBuffer[12] = 'H';
    outBuffer[13] = 'z';
    outBuffer[14] = 0;
  }
  else if (freq >= 1000000)
  {
    // Adda a comma below the MHz digits
    // 0123456789012
    // 1000000
    // 1,000.00 KHz
    dtostrf(freq, 7, 0, inBuffer);
    outBuffer[0] = inBuffer[0];
    outBuffer[1] = '.';
    outBuffer[2] = inBuffer[1];
    outBuffer[3] = inBuffer[2];
    outBuffer[4] = inBuffer[3];
    outBuffer[5] = ',';
    outBuffer[6] = inBuffer[4];
    outBuffer[7] = inBuffer[5];
    outBuffer[8] = inBuffer[6];
    outBuffer[9] = ' ';
    outBuffer[10] = 'M';
    outBuffer[11] = 'H';
    outBuffer[12] = 'z';
    outBuffer[13] = 0;
  }
  else if (freq >= 100000)
  {
    // 0123456789012
    // 100000
    // 100.000 KHz
    dtostrf(freq, 6, 0, inBuffer);
    outBuffer[0] = inBuffer[0];
    outBuffer[1] = inBuffer[1];
    outBuffer[2] = inBuffer[2];
    outBuffer[3] = '.';
    outBuffer[4] = inBuffer[3];
    outBuffer[5] = inBuffer[4];
    outBuffer[6] = inBuffer[5];
    outBuffer[7] = ' ';
    outBuffer[8] = 'K';
    outBuffer[9] = 'H';
    outBuffer[10] = 'z';
    outBuffer[11] = 0;
  }
  else if (freq >= 10000)
  {
    // 0123456789012
    // 10000
    // 10.000 KHz
    dtostrf(freq, 5, 0, inBuffer);
    outBuffer[0] = inBuffer[0];
    outBuffer[1] = inBuffer[1];
    outBuffer[2] = '.';
    outBuffer[3] = inBuffer[2];
    outBuffer[4] = inBuffer[3];
    outBuffer[5] = inBuffer[4];
    outBuffer[6] = ' ';
    outBuffer[7] = 'K';
    outBuffer[8] = 'H';
    outBuffer[9] = 'z';
    outBuffer[10] = 0;
  }
  else if (freq >= 1000)
  {
    // 0123456789012
    // 1000
    // 1.000 KHz
    dtostrf(freq, 4, 0, inBuffer);
    outBuffer[0] = inBuffer[0];
    outBuffer[1] = ',';
    outBuffer[2] = inBuffer[1];
    outBuffer[3] = inBuffer[2];
    outBuffer[4] = inBuffer[3];
    outBuffer[5] = ' ';
    outBuffer[6] = 'K';
    outBuffer[7] = 'H';
    outBuffer[8] = 'z';
    outBuffer[9] = 0;
  }
  else if (freq >= 100)
  {
    // 0123456789012
    // 100
    // 100 Hz
    dtostrf(freq, 3, 0, inBuffer);
    outBuffer[0] = inBuffer[0];
    outBuffer[1] = inBuffer[1];
    outBuffer[2] = inBuffer[2];
    outBuffer[3] = ' ';
    outBuffer[4] = 'H';
    outBuffer[5] = 'z';
    outBuffer[6] = 0;
  }
  else if (freq >= 10)
  {
    // 0123456789012
    // 10
    // 10 Hz
    dtostrf(freq, 2, 0, inBuffer);
    outBuffer[0] = inBuffer[0];
    outBuffer[1] = inBuffer[1];
    outBuffer[2] = ' ';
    outBuffer[3] = 'H';
    outBuffer[4] = 'z';
    outBuffer[5] = 0;
  }
  else
  {
    // 0123456789012
    // 1
    // 1 Hz
    dtostrf(freq, 1, 0, inBuffer);
    outBuffer[0] = inBuffer[0];
    outBuffer[1] = ' ';
    outBuffer[2] = 'H';
    outBuffer[3] = 'z';
    outBuffer[3] = 0;
  }
  u8x8.clearDisplay();
   if (currentVFONumber == 0)
    u8x8.drawString(0,0,"Set CLK0");
   else if (currentVFONumber == 1)
    u8x8.drawString(0,0,"Set CLK1");
   else if (currentVFONumber == 2)
    u8x8.drawString(0,0,"Set CLK2");
  u8x8.drawString(0,2, outBuffer);
}

// printVFOFreq
void printVFOFreq(void)
{
  if (currentVFONumber == 0)
    displayFreqInKHzOnOLED(float(VFO_0_Freq / 100ULL));
  else if (currentVFONumber == 1)
    displayFreqInKHzOnOLED(float(VFO_1_Freq / 100ULL));
  else if (currentVFONumber == 2)
    displayFreqInKHzOnOLED(float(VFO_2_Freq / 100ULL));
}

// setVFOFreq
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

// printVFONumber
void printVFONumber(void)
{
  u8x8.clearDisplay();
  if (currentVFONumber == 0)
    u8x8.draw2x2String(0,1,"CLK0");
  else if (currentVFONumber == 1)
    u8x8.draw2x2String(0,1,"CLK1");
  else if (currentVFONumber == 2)
    u8x8.draw2x2String(0,1,"CLK2");
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
  u8x8.clearDisplay();
  if (currentVFONumber == 0)
  {
    if (VFO_O_OnOff == VFO_ON)
      u8x8.draw2x2String(0,1,"CLK0 On");
    else
      u8x8.draw2x2String(0,1,"CLK0 Off");
  }
  else if (currentVFONumber == 1)
  {
    if (VFO_1_OnOff == VFO_ON)
      u8x8.draw2x2String(0,1,"CLK1 On");
    else
      u8x8.draw2x2String(0,1,"CLK1 Off");
  }
  else if (currentVFONumber == 2)
  {
    if (VFO_2_OnOff == VFO_ON)
      u8x8.draw2x2String(0,1,"CLK2 On");
    else
      u8x8.draw2x2String(0,1,"CLK2 Off");
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
  u8x8.clearDisplay();
  if (stepSize == STEP_1_HZ)
    u8x8.drawString(0,0,"Step 1 Hz");
  else if (stepSize == STEP_10_HZ)
    u8x8.drawString(0,0,"Step 10 Hz");
  else if (stepSize == STEP_100_HZ)
    u8x8.drawString(0,0,"Step 100 Hz");
  else if (stepSize == STEP_1_KHZ)
    u8x8.drawString(0,0,"Step 1 KHz");
  else if (stepSize == STEP_10_KHZ)
    u8x8.drawString(0,0,"Step 10 KHz");
  else if (stepSize == STEP_100_KHZ)
    u8x8.drawString(0,0,"Step 100 KHz");
  else if (stepSize == STEP_1_MHZ)
    u8x8.drawString(0,0,"Step 1 MHz");
  else if (stepSize == STEP_10_MHZ)
    u8x8.drawString(0,0,"Step 10 MHz");
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
