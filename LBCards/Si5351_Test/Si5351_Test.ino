/*

  Si5351_Test.ino

  Minimal sketch to determine minimal memory size.
  Frequency synthesizer is Si5351
  Si5361 driver is from si5351_example at
  https://etherkit.github.io/si5351abb_landing_page.html

  Runs on a 3.3V Arduino Pro Mini
  No 5V to 3.3V level shifting is needed for the I2C ports of the Si5351 and OLED
  SArduino Pro Mini has internal EEPROM for parameter storage
  
*/

#include <Arduino.h>
#include "si5351.h"


// Constructors

Si5351 si5351;
  
// End of constructor list

void setup(void)
{
  // Si8351 initialiation
  si5351.init(SI5351_CRYSTAL_LOAD_6PF, 27000000, 0);
  si5351.set_freq(14000000, SI5351_CLK0);
  si5351.set_freq(12000000, SI5351_CLK1);
  si5351.set_freq(10000000, SI5351_CLK2);
  si5351.update_status();  
  si5351.set_correction(0, SI5351_PLL_INPUT_XO);
  si5351.drive_strength(SI5351_CLK0,SI5351_DRIVE_8MA);
  si5351.drive_strength(SI5351_CLK1,SI5351_DRIVE_8MA);
  si5351.drive_strength(SI5351_CLK2,SI5351_DRIVE_8MA);
}

void loop(void)
{
}
