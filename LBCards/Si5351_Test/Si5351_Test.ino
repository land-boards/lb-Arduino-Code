/*

  I2C_VFO3.ino

  Wiki page for VFO-003
  http://land-boards.com/blwiki/index.php?title=VFO-003

  Borrowed bits & pieces from all over the place

  Runs on a 3.3V Arduino Pro Mini
  No 5V to 3.3V level shifting is needed for the I2C ports of the Si5351 and OLED
  SArduino Pro Mini has internal EEPROM for parameter storage
  
  OLED is 128x32 I2C device
  SSD1306 controller
  OLED driver Wiki page
  https://github.com/olikraus/u8g2/wiki
  
  Frequency synthesizer is Si5351
  3 outputs
  74AC14 Buffers to crive 50 Ohm outputs
  Si5361 driver is from si5351_example at
  https://etherkit.github.io/si5351abb_landing_page.html
  
*/

#include <Arduino.h>
#include "si5351.h"


// Constructors

Si5351 si5351;
  
// End of constructor list

void setup(void)
{
  unsigned long VFO_0_Freq;
  unsigned long VFO_1_Freq;
  unsigned long VFO_2_Freq;
  bool i2c_found;
  VFO_0_Freq = 14000000;
  VFO_0_Freq = 14000000;
  VFO_0_Freq = 14000000;
  // Si8351 initialiation
  si5351.init(SI5351_CRYSTAL_LOAD_6PF, 27000000, 0);
  si5351.set_freq(VFO_0_Freq, SI5351_CLK0);
  si5351.set_freq(VFO_1_Freq, SI5351_CLK1);
  si5351.set_freq(VFO_2_Freq, SI5351_CLK2);
  si5351.update_status();  
  si5351.set_correction(0, SI5351_PLL_INPUT_XO);
  si5351.drive_strength(SI5351_CLK0,SI5351_DRIVE_8MA);
  si5351.drive_strength(SI5351_CLK1,SI5351_DRIVE_8MA);
  si5351.drive_strength(SI5351_CLK2,SI5351_DRIVE_8MA);
}

void loop(void)
{
}
