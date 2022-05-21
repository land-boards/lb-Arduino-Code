/*

  I2C_VFO3.ino

  Wiki page for VFO-003
    http://land-boards.com/blwiki/index.php?title=VFO-003

  Borrowed bits & pieces from all over the place

  Runs on a 3.3V Arduino Pro Mini
  No 5V to 3.3V level shifting is needed for the I2C ports of the Si5351 and OLED
  Arduino Pro Mini has internal EEPROM for parameter storage
  STM32 parts don't have EEPROM - there are tricks to use the Flash for parameter storage
  
  OLED is 128x32 I2C device
  SSD1306 controller
  OLED driver Wiki page
    https://github.com/olikraus/u8g2/wiki
    8x8 font has 16x4 characters
  
  Frequency synthesizer is Si5351
  3 outputs
  74AC14 Buffers to drive 3.3V, 50 Ohm outputs
  Si5361 driver is from si5351_example
    https://etherkit.github.io/si5351abb_landing_page.html
  
*/

#include <Arduino.h>
#include <EEPROM.h>
#include <U8g2lib.h>

// defines and enums - Set defines/undefs appropriately
#define HAS_INTERNAL_EEPROM   // Arduini Pro Mini has internal EEPROM (STM32 does not)

// Rotary encoder pins on the Arduino Pro Mini
#define ROTARY_DATA 2
#define ROTARY_CLK 3
#define encoderSwitch  4

#define U8X8_HAVE_HW_I2C

// EEPROM is used to store initial values
// ATMEGA parts have internal EEPROM

// Gloibal variables

enum ControlsState
{
  NOTHING,
  ENC_SW_PRESSED,
  ENC_UP,
  ENC_DOWN
};


// Constructors
  
U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(U8X8_PIN_NONE);

// End of constructor list

//setup run once
void setup(void)
{
  bool i2c_found;

  u8x8.begin();
  u8x8.setBusClock(100000);   // I2C clock = 400 KHz
  u8x8.clearDisplay();
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  u8x8.draw2x2String(0,0,"Hello");
  delay(1000);
  
  // Rotary encoder initialization
  setupEncoder();
}

// loop - loops forever
void loop(void)
{
  uint8_t ctrlVal = waitForControlChange();
  if (ctrlVal == ENC_UP)
  {
    u8x8.clearDisplay();
    u8x8.draw2x2String(0,0,"UP");
  }
  else if (ctrlVal == ENC_DOWN)
  {
    u8x8.clearDisplay();
    u8x8.draw2x2String(0,0,"DOWN");
  }
  else if (ctrlVal == ENC_SW_PRESSED)
  {
    u8x8.clearDisplay();
    u8x8.draw2x2String(0,0,"PRESSED");
  }
}
