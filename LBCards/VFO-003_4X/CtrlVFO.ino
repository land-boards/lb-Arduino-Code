// VFO Control

void setupVFO(void)
{
  // Set CLK0
  if (VFO_0_1x4x == VFO_1X)
    si5351.set_freq((uint64_t)VFO_0_Freq, SI5351_CLK0);
  else
    si5351.set_freq((uint64_t)VFO_0_Freq * 4, SI5351_CLK0);

  // Set CLK1
  if (VFO_1_1x4x == VFO_1X)
    si5351.set_freq((uint64_t)VFO_1_Freq, SI5351_CLK1);
  else
    si5351.set_freq((uint64_t)VFO_1_Freq * 4, SI5351_CLK1);

  // Set CLK2
  if (VFO_2_1x4x == VFO_1X)
    si5351.set_freq((uint64_t)VFO_2_Freq, SI5351_CLK2);
  else
    si5351.set_freq((uint64_t)VFO_2_Freq * 4, SI5351_CLK2);

  // Query a status update and wait a bit to let the Si5351 populate the
  // status flags correctly.
  si5351.update_status();

  // Set the calibration factor
  si5351.set_correction(calFactor, SI5351_PLL_INPUT_XO);

  // Set all of the drive strengths to 8 mA (max)
  si5351.drive_strength(SI5351_CLK0, SI5351_DRIVE_8MA);
  si5351.drive_strength(SI5351_CLK1, SI5351_DRIVE_8MA);
  si5351.drive_strength(SI5351_CLK2, SI5351_DRIVE_8MA);

  // Clocks need to be high when they are disabled
  // Needed because 74AC14 drivers on VFO-002 invert the clocks
  // Keeps card from driving DC output
  si5351.set_clock_disable(SI5351_CLK0, SI5351_CLK_DISABLE_HIGH);
  si5351.set_clock_disable(SI5351_CLK1, SI5351_CLK_DISABLE_HIGH);
  si5351.set_clock_disable(SI5351_CLK2, SI5351_CLK_DISABLE_HIGH);

  if (VFO_0_OnOff == VFO_ON)
    si5351.output_enable(SI5351_CLK0, 1);
  else
    si5351.output_enable(SI5351_CLK0, 0);

  if (VFO_1_OnOff == VFO_ON)
    si5351.output_enable(SI5351_CLK1, 1);
  else
    si5351.output_enable(SI5351_CLK1, 0);

  if (VFO_2_OnOff == VFO_ON)
    si5351.output_enable(SI5351_CLK2, 1);
  else
    si5351.output_enable(SI5351_CLK2, 0);
}
