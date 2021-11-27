/*

  I2C_VFO3_4x.ino
  Based on I2C_VFO3.ino
  Adds 4x clock function for use in IQ radios

  Wiki page for VFO-003
    http://land-boards.com/blwiki/index.php?title=VFO-003

  Borrowed bits & pieces from all over the place

  Runs on a 3.3V Arduino Pro Mini
  Don't need a 5V to 3.3V level shifter for the I2C interfaces of the Si5351 and OLED
  Arduino Pro Mini has internal EEPROM for parameter storage
  Using Arduino instead of STM32 cards since STM32 parts don't have EEPROM - there are tricks to use the Flash for parameter storage

  Menus on 128x32 OLED
  SSD1306 I2C controller
  OLED I2C driver Wiki page
    https://github.com/olikraus/u8g2/wiki
    8x8 font has 16x4 characters in 128x32 display

  Frequency synthesizer is Si5351A
  3 outputs
  74AC14 Buffers on VFO-003 drive 3.3V, 50 Ohm outputs
  Frequencies are in 1/100th of a Hz
  32-bit frequency values are 2^32/100 = 42.95 MHz max
  Convert 32-bit values using cast (uint64_t) to set higher frequencies
  Si5361 driver is from si5351_example
    https://etherkit.github.io/si5351abb_landing_page.html

*/

// Includes
#include <Arduino.h>
#include <EEPROM.h>
#include "si5351.h"
#include <U8g2lib.h>

// Defines
// defines and enums - Set defines/undefs appropriately
#define HAS_INTERNAL_EEPROM   // Arduini Pro Mini has internal EEPROM (STM32 does not)

// Rotary encoder pins on the Arduino Pro Mini
#define ROTARY_DATA 2
#define ROTARY_CLK 3
#define encoderSwitch  4

#define U8X8_HAVE_HW_I2C

#define STEP_1_HZ     100ULL
#define STEP_5_HZ     500ULL
#define STEP_10_HZ    1000ULL
#define STEP_50_HZ    5000ULL
#define STEP_100_HZ   10000ULL
#define STEP_500_HZ   50000ULL
#define STEP_1_KHZ    100000ULL
#define STEP_5_KHZ    500000ULL
#define STEP_10_KHZ   1000000ULL
#define STEP_50_KHZ   5000000ULL
#define STEP_100_KHZ  10000000ULL
#define STEP_500_KHZ  50000000ULL
#define STEP_1_MHZ    100000000ULL
#define STEP_5_MHZ    500000000ULL
#define STEP_10_MHZ   1000000000ULL

// enums
enum VFO_ON_OFF
{
  VFO_OFF,
  VFO_ON
};

enum VFO_1X_4X
{
  VFO_1X,
  VFO_4X
};

// EEPROM is used to store initial values
// ATMEGA parts have internal EEPROM - STM32 parts don't have internal EEPROM

// Global variables
unsigned long VFO_0_Freq;
unsigned long VFO_1_Freq;
unsigned long VFO_2_Freq;

uint32_t stepSize;
int32_t calFactor;

uint8_t VFO_0_OnOff;
uint8_t VFO_1_OnOff;
uint8_t VFO_2_OnOff;

uint8_t VFO_0_1x4x;
uint8_t VFO_1_1x4x;
uint8_t VFO_2_1x4x;

uint8_t currentVFONumber;

uint8_t magicNumber;

// Constructors
Si5351 si5351;
U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(U8X8_PIN_NONE);

//setup run once at reset/power-up
void setup(void)
{
  bool i2c_found;

  checkEEPROM();

  u8x8.begin();
  u8x8.setBusClock(400000);   // I2C clock = 400 KHz
  u8x8.clearDisplay();
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  u8x8.draw2x2String(0, 0, "VFO4X");
  initMenu();
  delay(1000);

  // Si8351 initialiation
  i2c_found = si5351.init(SI5351_CRYSTAL_LOAD_6PF, 27000000, 0);
  if (!i2c_found)
  {
    u8x8.clearDisplay();
    u8x8.drawString(0, 0, "I2C Fail");
    while (1);
  }

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
  // Needed because of the 74AC14 drivers which invert the clocks
  // Keeps card from driving DC output
  si5351.set_clock_disable(SI5351_CLK0, SI5351_CLK_DISABLE_HIGH);
  si5351.set_clock_disable(SI5351_CLK1, SI5351_CLK_DISABLE_HIGH);
  si5351.set_clock_disable(SI5351_CLK2, SI5351_CLK_DISABLE_HIGH);

  // Rotary encoder initialization
  setupEncoder();
}

// loop - loops forever
void loop(void)
{
  vfoTopLevelMenuOps();
}
