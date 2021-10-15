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
#include <EEPROM.h>
#include "si5351.h"
#include <U8g2lib.h>

// defines and enums - Set defines/undefs appropriately
#define HAS_INTERNAL_EEPROM   // Arduini Pro Mini has internal EEPROM (STM32 does not)

// Rotary encoder pins on the Arduino Pro Mini
#define ROTARY_DATA 2
#define ROTARY_CLK 3
#define encoderSwitch  4

#define U8X8_HAVE_HW_I2C

#define STEP_1_HZ     100ULL
#define STEP_10_HZ    1000ULL
#define STEP_100_HZ   10000ULL
#define STEP_1_KHZ    100000ULL
#define STEP_10_KHZ   1000000ULL
#define STEP_100_KHZ  10000000ULL
#define STEP_1_MHZ    100000000ULL
#define STEP_10_MHZ   1000000000ULL

enum VFO_ON_OFF
{
  VFO_OFF,
  VFO_ON
};

// EEPROM is used to store initial values
// ATMEGA parts have internal EEPROM

// Gloibal variables

uint32_t stepSize;

unsigned long VFO_0_Freq;
unsigned long VFO_1_Freq;
unsigned long VFO_2_Freq;

uint8_t VFO_O_OnOff;
uint8_t VFO_1_OnOff;
uint8_t VFO_2_OnOff;

uint8_t currentVFONumber;
uint8_t magicNumber;
int32_t calFactor;

// Constructors

Si5351 si5351;
  
U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(U8X8_PIN_NONE);

// End of constructor list

void setup(void)
{
  bool i2c_found;

  checkEEPROM();
  
  u8x8.begin();

  u8x8.setFont(u8x8_font_victoriabold8_r);
  u8x8.drawString(0,0,"VFO-003");
  
  // Si8351 initialiation
  i2c_found = si5351.init(SI5351_CRYSTAL_LOAD_6PF, 27000000, 0);
  if (!i2c_found)
  {
     u8x8.drawString(0,0,"I2C Fail");
     while(1);
  }

  // Set CLK0
  si5351.set_freq(VFO_0_Freq, SI5351_CLK0);
  
  // Set CLK1
  si5351.set_freq(VFO_1_Freq, SI5351_CLK1);

  // Set CLK2
  si5351.set_freq(VFO_2_Freq, SI5351_CLK2);

  // Query a status update and wait a bit to let the Si5351 populate the
  // status flags correctly.
  si5351.update_status();  

  // Set the calibration factor
  si5351.set_correction(calFactor, SI5351_PLL_INPUT_XO);

  // Set all of the drive strengths to 8 mA (max)
  si5351.drive_strength(SI5351_CLK0,SI5351_DRIVE_8MA);
  si5351.drive_strength(SI5351_CLK1,SI5351_DRIVE_8MA);
  si5351.drive_strength(SI5351_CLK2,SI5351_DRIVE_8MA);

  // Clocks need to be high when they are disabled
  // Needed because of the 74AC14 drivers which invert the clocks
  // Keeps card from driving DC output
  si5351.set_clock_disable(SI5351_CLK0,SI5351_CLK_DISABLE_HIGH);
  si5351.set_clock_disable(SI5351_CLK1,SI5351_CLK_DISABLE_HIGH);
  si5351.set_clock_disable(SI5351_CLK2,SI5351_CLK_DISABLE_HIGH);
 
  // Rotary encoder initialization
  setupEncoder();
}

void loop(void)
{
    vfoMenu();
}
