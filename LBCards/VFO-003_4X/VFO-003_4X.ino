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
      16 chars/line x 4 lines

  Frequency synthesizer is Si5351A
  3 outputs
  74AC14 Buffers on VFO-003 drive 3.3V, 50 Ohm outputs
  Frequencies are in 1/100th of a Hz
  32-bit frequency values are 2^32/100 = 42.95 MHz max
  Convert 32-bit values using cast (uint64_t) to set higher frequencies
  1x or 4x selectable
  QRP Labe Receiver module LO uses 4x clock
  Si5351 driver is from si5351_example
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

// Band selection enums
// Works with Switched Relay card
enum BAND_SEL_VALS
{
  BAND_80M_CW,
  BAND_80M_SSB,
  BAND_40M_CW,
  BAND_40M_SSB,
  BAND_20M_CW,
  BAND_20M_SSB,
  BAND_15M_CW,
  BAND_15M_SSB,
  BAND_10M_CW,
  BAND_10M_SSB
};

// EEPROM is used to store initial values
// ATMEGA parts have internal EEPROM - STM32 parts don't have internal EEPROM

// Global variables
// Loaded from EEPROM at power up
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
uint8_t bandNumber;

uint8_t magicNumber;

// Constructors
Si5351 si5351;
U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(U8X8_PIN_NONE);

//setup run once at reset/power-up
void setup(void)
{
  bool i2c_found;
  // Initialize the VFO-003 hardware
  loadInitEEPROM();           // Load EEPROM
  initBandSwitch();           // Band Switch initialization
  initMenu();                 // Menu initialization
  setupEncoder();             // Rotary encoder initialization
  u8x8.begin();               // OLED initialization
  u8x8.setBusClock(100000);   // I2C clock = 100 KHz

  u8x8.clearDisplay();
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  u8x8.draw2x2String(0, 0, "VFO4X");

  // Si8351 initialiation
  i2c_found = si5351.init(SI5351_CRYSTAL_LOAD_6PF, 27000000, 0);
  if (!i2c_found)
  {
    u8x8.clearDisplay();
    u8x8.drawString(0, 0, "I2C Fail");
    while (1);
  }
  delay(1000);
  setupVFO();
}

// loop - loops forever
void loop(void)
{
  vfoTopLevelMenuOps();
}
