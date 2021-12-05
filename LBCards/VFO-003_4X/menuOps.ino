// Menu Functions

#define MIN_FREQ 1000000ULL
#define MAX_FREQ 4000000000ULL

// Set VFO Frequency
void setVFOFreq(void)
{
  uint8_t controlVal;
  printVFOFreq();
  while (1)
  {
    controlVal = waitForControlChange();
    if (controlVal == ENC_SW_PRESSED)
      return;
    else if (controlVal == ENC_DOWN)
    {
      if (currentVFONumber == 0)
      {
        VFO_0_Freq -= stepSize; // count down by step size
        if ((VFO_0_Freq < MIN_FREQ) || (VFO_0_Freq > MAX_FREQ))
          VFO_0_Freq = stepSize;
        if (VFO_0_1x4x == VFO_1X)
          si5351.set_freq((uint64_t)VFO_0_Freq, SI5351_CLK0);
        else
          si5351.set_freq((uint64_t)VFO_0_Freq << 2, SI5351_CLK0);
      }
      else if (currentVFONumber == 1)
      {
        VFO_1_Freq -= stepSize; // count down by step size
        if ((VFO_1_Freq < MIN_FREQ) || (VFO_1_Freq > MAX_FREQ))
          VFO_1_Freq = stepSize;
        if (VFO_1_1x4x == VFO_1X)
          si5351.set_freq((uint64_t)VFO_1_Freq, SI5351_CLK1);
        else
          si5351.set_freq((uint64_t)VFO_1_Freq << 2, SI5351_CLK1);
      }
      else if (currentVFONumber == 2)
      {
        VFO_2_Freq -= stepSize; // count down by step size
        if ((VFO_2_Freq < MIN_FREQ) || (VFO_2_Freq > MAX_FREQ))
          VFO_2_Freq = stepSize;
        if (VFO_2_1x4x == VFO_1X)
          si5351.set_freq((uint64_t)VFO_2_Freq, SI5351_CLK2);
        else
          si5351.set_freq((uint64_t)VFO_2_Freq << 2, SI5351_CLK2);
      }
    }
    else if (controlVal == ENC_UP)
    {
      if (currentVFONumber == 0)
      {
        VFO_0_Freq += stepSize; // count up by step size
        if (VFO_0_Freq > MAX_FREQ)
          VFO_0_Freq = MAX_FREQ; // Limit top of range
        if (VFO_0_1x4x == VFO_1X)
          si5351.set_freq((uint64_t)VFO_0_Freq, SI5351_CLK0);
        else
          si5351.set_freq((uint64_t)VFO_0_Freq << 2, SI5351_CLK0);
      }
      else if (currentVFONumber == 1)
      {
        VFO_1_Freq += stepSize; // count up by step size
        if (VFO_1_Freq > MAX_FREQ)
          VFO_1_Freq = MAX_FREQ; // Limit top of range
        if (VFO_1_1x4x == VFO_1X)
          si5351.set_freq((uint64_t)VFO_1_Freq, SI5351_CLK1);
        else
          si5351.set_freq((uint64_t)VFO_1_Freq << 2, SI5351_CLK1);
      }
      else if (currentVFONumber == 2)
      {
        VFO_2_Freq += stepSize; // count up by step size
        if (VFO_2_Freq > MAX_FREQ)
          VFO_2_Freq = MAX_FREQ; // Limit top of range
        if (VFO_2_1x4x == VFO_1X)
          si5351.set_freq((uint64_t)VFO_2_Freq, SI5351_CLK2);
        else
          si5351.set_freq((uint64_t)VFO_2_Freq << 2, SI5351_CLK2);
      }
    }
    printVFOFreq();
  }
}

// Display Frequency on OLED
void displayFreqOnOLED(float freq)
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
    u8x8.draw2x2String(0, 0, "CLK0");
  else if (currentVFONumber == 1)
    u8x8.draw2x2String(0, 0, "CLK1");
  else if (currentVFONumber == 2)
    u8x8.draw2x2String(0, 0, "CLK2");
  u8x8.drawString(0, 3, outBuffer);
}

// Print VFO Frequency
void printVFOFreq(void)
{
  if (currentVFONumber == 0)
    displayFreqOnOLED(float(VFO_0_Freq / 100ULL));
  else if (currentVFONumber == 1)
    displayFreqOnOLED(float(VFO_1_Freq / 100ULL));
  else if (currentVFONumber == 2)
    displayFreqOnOLED(float(VFO_2_Freq / 100ULL));
}

// Set VFO Step Size
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
        stepSize = STEP_5_HZ;
      else if (stepSize == STEP_5_HZ)
        stepSize = STEP_10_HZ;
      else if (stepSize == STEP_10_HZ)
        stepSize = STEP_50_HZ;
      else if (stepSize == STEP_50_HZ)
        stepSize = STEP_100_HZ;
      else if (stepSize == STEP_100_HZ)
        stepSize = STEP_500_HZ;
      else if (stepSize == STEP_500_HZ)
        stepSize = STEP_1_KHZ;
      else if (stepSize == STEP_1_KHZ)
        stepSize = STEP_5_KHZ;
      else if (stepSize == STEP_5_KHZ)
        stepSize = STEP_10_KHZ;
      else if (stepSize == STEP_10_KHZ)
        stepSize = STEP_50_KHZ;
      else if (stepSize == STEP_50_KHZ)
        stepSize = STEP_100_KHZ;
      else if (stepSize == STEP_100_KHZ)
        stepSize = STEP_500_KHZ;
      else if (stepSize == STEP_500_KHZ)
        stepSize = STEP_1_MHZ;
      else if (stepSize == STEP_1_MHZ)
        stepSize = STEP_5_MHZ;
      else if (stepSize == STEP_5_MHZ)
        stepSize = STEP_10_MHZ;
    }
    else if (controlVal == ENC_DOWN)
    {
      if (stepSize == STEP_5_HZ)
        stepSize = STEP_1_HZ;
      else if (stepSize == STEP_10_HZ)
        stepSize = STEP_5_HZ;
      else if (stepSize == STEP_50_HZ)
        stepSize = STEP_10_HZ;
      else if (stepSize == STEP_100_HZ)
        stepSize = STEP_50_HZ;
      else if (stepSize == STEP_500_HZ)
        stepSize = STEP_100_HZ;
      else if (stepSize == STEP_1_KHZ)
        stepSize = STEP_500_HZ;
      else if (stepSize == STEP_5_KHZ)
        stepSize = STEP_1_KHZ;
      else if (stepSize == STEP_10_KHZ)
        stepSize = STEP_5_KHZ;
      else if (stepSize == STEP_50_KHZ)
        stepSize = STEP_10_KHZ;
      else if (stepSize == STEP_100_KHZ)
        stepSize = STEP_50_KHZ;
      else if (stepSize == STEP_500_KHZ)
        stepSize = STEP_100_KHZ;
      else if (stepSize == STEP_1_MHZ)
        stepSize = STEP_500_KHZ;
      else if (stepSize == STEP_5_MHZ)
        stepSize = STEP_1_MHZ;
      else if (stepSize == STEP_10_MHZ)
        stepSize = STEP_5_MHZ;
    }
    printStepSize();
  }
}

// Print Step Size
void printStepSize(void)
{
  u8x8.clearDisplay();
  u8x8.draw2x2String(0, 0, "Stp Size");
  if (stepSize == STEP_1_HZ)
    u8x8.draw2x2String(0, 2, "1 Hz");
  else if (stepSize == STEP_5_HZ)
    u8x8.draw2x2String(0, 2, "5 Hz");
  else if (stepSize == STEP_10_HZ)
    u8x8.draw2x2String(0, 2, "10 Hz");
  else if (stepSize == STEP_50_HZ)
    u8x8.draw2x2String(0, 2, "50 Hz");
  else if (stepSize == STEP_100_HZ)
    u8x8.draw2x2String(0, 2, "100 Hz");
  else if (stepSize == STEP_500_HZ)
    u8x8.draw2x2String(0, 2, "500 Hz");
  else if (stepSize == STEP_1_KHZ)
    u8x8.draw2x2String(0, 2, "1 KHz");
  else if (stepSize == STEP_5_KHZ)
    u8x8.draw2x2String(0, 2, "5 KHz");
  else if (stepSize == STEP_10_KHZ)
    u8x8.draw2x2String(0, 2, "10 KHz");
  else if (stepSize == STEP_50_KHZ)
    u8x8.draw2x2String(0, 2, "50 KHz");
  else if (stepSize == STEP_100_KHZ)
    u8x8.draw2x2String(0, 2, "100 KHz");
  else if (stepSize == STEP_500_KHZ)
    u8x8.draw2x2String(0, 2, "500 KHz");
  else if (stepSize == STEP_1_MHZ)
    u8x8.draw2x2String(0, 2, "1 MHz");
  else if (stepSize == STEP_5_MHZ)
    u8x8.draw2x2String(0, 2, "5 MHz");
  else if (stepSize == STEP_10_MHZ)
    u8x8.draw2x2String(0, 2, "10 MHz");
  return;
}

// Set the Band
// Fast way to get to the start of a band
void setBandVal(void)
{
  uint8_t controlVal;
  printBand();
  while (1)
  {
    controlVal = waitForControlChange();
    if (controlVal == ENC_SW_PRESSED)
    {
      setCurrentFreq();
      return;
    }
    else if (controlVal == ENC_UP)
    {
      if (bandNumber < BAND_10M_SSB)
        bandNumber += 1;
    }
    else if (controlVal == ENC_DOWN)
    {
      if (bandNumber > BAND_80M_CW)
        bandNumber -= 1;
    }
    setBandSwitch();
    printBand();
  }
}

// Print the Band Number
// 10/15/20/40/80M bands
// CW or SSB
void printBand(void)
{
  u8x8.clearDisplay();
  u8x8.draw2x2String(0, 0, "BAND SEL");
  if (bandNumber == BAND_80M_CW)
    u8x8.draw2x2String(0, 2, "80M CW");
  else if (bandNumber == BAND_80M_SSB)
    u8x8.draw2x2String(0, 2, "80M SSB");
  else if (bandNumber == BAND_40M_CW)
    u8x8.draw2x2String(0, 2, "40M CW");
  else if (bandNumber == BAND_40M_SSB)
    u8x8.draw2x2String(0, 2, "40M SSB");
  else if (bandNumber == BAND_20M_CW)
    u8x8.draw2x2String(0, 2, "20M CW");
  else if (bandNumber == BAND_20M_SSB)
    u8x8.draw2x2String(0, 2, "20M SSB");
  else if (bandNumber == BAND_15M_CW)
    u8x8.draw2x2String(0, 2, "15M CW");
  else if (bandNumber == BAND_15M_SSB)
    u8x8.draw2x2String(0, 2, "15M SSB");
  else if (bandNumber == BAND_10M_CW)
    u8x8.draw2x2String(0, 2, "10M CW");
  else if (bandNumber == BAND_10M_SSB)
    u8x8.draw2x2String(0, 2, "10M SSB");
}

// Set the currently sellected frequency
// Set step size to 100 Hz for CW and 1 KHz for SSN
void setCurrentFreq(void)
{
  uint64_t freqVal;     // Start of band
  if (bandNumber == BAND_80M_CW)
  {
    freqVal = 350000000ULL;
    stepSize = STEP_100_HZ;
  }
  else if (bandNumber == BAND_80M_SSB)
  {
    freqVal = 360000000ULL;
    stepSize = STEP_1_KHZ;
  }
  else if (bandNumber == BAND_40M_CW)
  {
    freqVal = 700000000ULL;
    stepSize = STEP_100_HZ;
  }
  else if (bandNumber == BAND_40M_SSB)
  {
    freqVal = 712500000ULL;
    stepSize = STEP_1_KHZ;
  }
  else if (bandNumber == BAND_20M_CW)
  {
    freqVal = 1400000000ULL;
    stepSize = STEP_100_HZ;
  }
  else if (bandNumber == BAND_20M_SSB)
  {
    freqVal = 1415000000ULL;
    stepSize = STEP_1_KHZ;
  }
  else if (bandNumber == BAND_15M_CW)
  {
    freqVal = 2100000000ULL;
    stepSize = STEP_100_HZ;
  }
  else if (bandNumber == BAND_15M_SSB)
  {
    freqVal = 2120000000ULL;
    stepSize = STEP_1_KHZ;
  }
  else if (bandNumber == BAND_10M_CW)
  {
    freqVal = 2800000000ULL;
    stepSize = STEP_100_HZ;
  }
  else if (bandNumber == BAND_10M_SSB)
  {
    freqVal = 2830000000ULL;
    stepSize = STEP_1_KHZ;
  }
  if (currentVFONumber == 0)
  {
    VFO_0_Freq = freqVal;
    if (VFO_0_1x4x == VFO_1X)
      si5351.set_freq((uint64_t)VFO_0_Freq, SI5351_CLK0);
    else
      si5351.set_freq((uint64_t)VFO_0_Freq << 2, SI5351_CLK0);
  }
  else if (currentVFONumber == 1)
  {
    VFO_1_Freq = freqVal;
    if (VFO_1_1x4x == VFO_1X)
      si5351.set_freq((uint64_t)VFO_1_Freq, SI5351_CLK1);
    else
      si5351.set_freq((uint64_t)VFO_1_Freq << 2, SI5351_CLK1);
  }
  else if (currentVFONumber == 2)
  {
    VFO_2_Freq = freqVal;
    if (VFO_2_1x4x == VFO_1X)
      si5351.set_freq((uint64_t)VFO_2_Freq, SI5351_CLK2);
    else
      si5351.set_freq((uint64_t)VFO_2_Freq << 2, SI5351_CLK2);
  }
}

// Seloect the current VFO 0-2
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
      if (currentVFONumber < 2)
        currentVFONumber += 1;
    }
    else if (controlVal == ENC_DOWN)
    {
      if (currentVFONumber > 1)
        currentVFONumber -= 1;
    }
    printVFONumber();
  }
}

// Print current VFO Number select
void printVFONumber(void)
{
  u8x8.clearDisplay();
  u8x8.draw2x2String(0, 0, "CLK SEL");
  if (currentVFONumber == 0)
    u8x8.draw2x2String(0, 2, "CLK0");
  else if (currentVFONumber == 1)
    u8x8.draw2x2String(0, 2, "CLK1");
  else if (currentVFONumber == 2)
    u8x8.draw2x2String(0, 2, "CLK2");
}

// Toggle off/on current VFO
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
        VFO_0_OnOff = VFO_ON;
        si5351.output_enable(SI5351_CLK0, 1);
      }
      else if (currentVFONumber == 1)
      {
        VFO_1_OnOff = VFO_ON;
        si5351.output_enable(SI5351_CLK1, 1);
      }
      else if (currentVFONumber == 2)
      {
        VFO_2_OnOff = VFO_ON;
        si5351.output_enable(SI5351_CLK2, 1);
      }
    }
    else if (controlVal == ENC_DOWN)
    {
      if (currentVFONumber == 0)
      {
        VFO_0_OnOff = VFO_OFF;
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

// Print VFO to On or Off
void printVFOOnOff(void)
{
  u8x8.clearDisplay();
  if (currentVFONumber == 0)
  {
    if (VFO_0_OnOff == VFO_ON)
      u8x8.draw2x2String(0, 1, "CLK0 On");
    else
      u8x8.draw2x2String(0, 1, "CLK0 Off");
  }
  else if (currentVFONumber == 1)
  {
    if (VFO_1_OnOff == VFO_ON)
      u8x8.draw2x2String(0, 1, "CLK1 On");
    else
      u8x8.draw2x2String(0, 1, "CLK1 Off");
  }
  else if (currentVFONumber == 2)
  {
    if (VFO_2_OnOff == VFO_ON)
      u8x8.draw2x2String(0, 1, "CLK2 On");
    else
      u8x8.draw2x2String(0, 1, "CLK2 Off");
  }
}

// Print 1X or 4X
void printVFO1x4x(void)
{
  u8x8.clearDisplay();
  if (currentVFONumber == 0)
  {
    if (VFO_0_1x4x == VFO_1X)
      u8x8.draw2x2String(0, 1, "CLK0 1X");
    else
      u8x8.draw2x2String(0, 1, "CLK0 4X");
  }
  else if (currentVFONumber == 1)
  {
    if (VFO_1_1x4x == VFO_1X)
      u8x8.draw2x2String(0, 1, "CLK1 1X");
    else
      u8x8.draw2x2String(0, 1, "CLK1 4X");
  }
  else if (currentVFONumber == 2)
  {
    if (VFO_2_1x4x == VFO_1X)
      u8x8.draw2x2String(0, 1, "CLK2 1X");
    else
      u8x8.draw2x2String(0, 1, "CLK2 4X");
  }
}

// Set current VFO to 1X or 4X
void setVFO1x4x(void)
{
  uint8_t controlVal;
  printVFO1x4x();
  while (1)
  {
    controlVal = waitForControlChange();
    if (controlVal == ENC_SW_PRESSED)
      return;
    else if (controlVal == ENC_DOWN)
    {
      if (currentVFONumber == 0)
      {
        VFO_0_1x4x = VFO_1X;
        si5351.set_freq((uint64_t)VFO_0_Freq, SI5351_CLK0);
      }
      else if (currentVFONumber == 1)
      {
        VFO_1_1x4x = VFO_1X;
        si5351.set_freq((uint64_t)VFO_1_Freq, SI5351_CLK1);
      }
      else if (currentVFONumber == 2)
      {
        VFO_2_1x4x = VFO_1X;
        si5351.set_freq((uint64_t)VFO_2_Freq, SI5351_CLK2);
      }
    }
    else if (controlVal == ENC_UP)
    {
      if (currentVFONumber == 0)
      {
        VFO_0_1x4x = VFO_4X;
        si5351.set_freq((uint64_t)VFO_0_Freq << 2, SI5351_CLK0);
      }
      else if (currentVFONumber == 1)
      {
        VFO_1_1x4x = VFO_4X;
        si5351.set_freq((uint64_t)VFO_1_Freq << 2, SI5351_CLK1);
      }
      else if (currentVFONumber == 2)
      {
        VFO_2_1x4x = VFO_4X;
        si5351.set_freq((uint64_t)VFO_2_Freq << 2, SI5351_CLK2);
      }
    }
    printVFO1x4x();
  }
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

// printCalFactor
// Calibration facts are in 0.1 Hz steps
// Adjust frequency at 40.000,000 MHz (highest freq supported by this software)
// Use 8 digit frequency counter to adjust
void printCalFactor(void)
{
  char buffer[14];
  itoa(calFactor / 10, buffer, 10);
  u8x8.clearDisplay();
  u8x8.draw2x2String(0, 0, "Cal val");
  u8x8.draw2x2String(0, 2, buffer);
}

// Save Init Values To EEPROM
void saveInitValuesToEEPROM(void)
{
#ifdef HAS_INTERNAL_EEPROM
  storeEEPROM();
  u8x8.clearDisplay();
  u8x8.draw2x2String(0, 1, "Stored");
  delay(1000);
#endif
}

// Memory Operations
void storeMemoryOps(void)
{
  uint8_t controlVal;
  uint8_t currentMemory = 0;
  printMemoryNumber(currentMemory);
  while (1)
  {
    controlVal = waitForControlChange();
    if (controlVal == ENC_SW_PRESSED)
    {
      if (currentMemory < 8)
        storeMemory(currentMemory);
      return;
    }
    else if (controlVal == ENC_UP)
    {
      if (currentMemory < 8)
        currentMemory += 1;
    }
    else if (controlVal == ENC_DOWN)
    {
      if (currentMemory > 0)
        currentMemory -= 1;
    }
    printMemoryNumber(currentMemory);
  }
}

// Load Memory Operations
void loadMemoryOps(void)
{
  uint8_t controlVal;
  uint8_t currentMemory = 0;
  printMemoryNumber(currentMemory);
  while (1)
  {
    controlVal = waitForControlChange();
    if (controlVal == ENC_SW_PRESSED)
    {
      if (currentMemory < 8)
        loadMemory(currentMemory);
      return;
    }
    else if (controlVal == ENC_UP)
    {
      if (currentMemory < 8)
        currentMemory += 1;
    }
    else if (controlVal == ENC_DOWN)
    {
      if (currentMemory > 0)
        currentMemory -= 1;
    }
    printMemoryNumber(currentMemory);
  }
}

// Print the memory number
void printMemoryNumber(uint8_t memNum)
{
  u8x8.clearDisplay();
  if (memNum == 0)
    u8x8.draw2x2String(0, 0, "Mem 0");
  else if (memNum == 1)
    u8x8.draw2x2String(0, 0, "Mem 1");
  else if (memNum == 2)
    u8x8.draw2x2String(0, 0, "Mem 2");
  else if (memNum == 3)
    u8x8.draw2x2String(0, 0, "Mem 3");
  else if (memNum == 4)
    u8x8.draw2x2String(0, 0, "Mem 4");
  else if (memNum == 5)
    u8x8.draw2x2String(0, 0, "Mem 5");
  else if (memNum == 6)
    u8x8.draw2x2String(0, 0, "Mem 6");
  else if (memNum == 7)
    u8x8.draw2x2String(0, 0, "Mem 7");
  else if (memNum == 8)
    u8x8.draw2x2String(0, 0, "Exit");
}

// Set Display On/Off
// Off = less RF noise from the OLED Display
void displayCtrlOps(void)
{
  uint8_t controlVal;
  uint8_t off0On1Exit2=0;
  printDisplayCtrl(off0On1Exit2);
  while (1)
  {
    controlVal = waitForControlChange();
    if (controlVal == ENC_SW_PRESSED)
    {
      if (off0On1Exit2 == 0)
        u8x8.setPowerSave(0);
      else if (off0On1Exit2 == 1)
        u8x8.setPowerSave(1);
      if (off0On1Exit2 == 2)
      {
        u8x8.setPowerSave(0);
        return;
      }
    }
    else if (controlVal == ENC_UP)
    {
      if (off0On1Exit2 < 2)
        off0On1Exit2 += 1;
      if (off0On1Exit2 != 1)
        u8x8.setPowerSave(0);
      else
        u8x8.setPowerSave(1);
    }
    else if (controlVal == ENC_DOWN)
    {
      if (off0On1Exit2 > 0)
        off0On1Exit2 -= 1;
      if (off0On1Exit2 != 1)
        u8x8.setPowerSave(0);
      else
        u8x8.setPowerSave(1);
    }
    printDisplayCtrl(off0On1Exit2);
  }
}

// Print Display control options
void printDisplayCtrl(uint8_t off0On1)
{
  u8x8.clearDisplay();
  u8x8.draw2x2String(0, 0, "Disp Ctl");
  if (off0On1 == 0)
     u8x8.draw2x2String(0, 2, "On");
  else if (off0On1 == 1)
     u8x8.draw2x2String(0, 2, "Off");
  else if (off0On1 == 2)
     u8x8.draw2x2String(0, 2, "Exit");
}
