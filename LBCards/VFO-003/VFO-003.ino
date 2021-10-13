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
#include <U8g2lib.h>
#include "si5351.h"

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
  
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);  // Ebay OLED

// Leave other SSD1306 constructors just in case different display is used
//U8G2_SSD1306_128X32_WINSTAR_F_HW_I2C u8g2(U8G2_R0,  U8X8_PIN_NONE);   // STM32
//U8G2_SSD1306_128X32_WINSTAR_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);   // pin remapping with ESP8266 HW I2C
//U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);  // Adafruit ESP8266/32u4/ARM Boards + FeatherWing OLED
//U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);   // pin remapping with ESP8266 HW I2C
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* SCL=PB6*/ PB6, /* SDA=PB7=*/ PB7, /* reset=*/ U8X8_PIN_NONE);
//U8G2_SSD1306_64X32_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//U8G2_SSD1306_64X32_1F_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//U8G2_SSD1306_96X16_ER_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   // EastRising 0.69" OLED
//U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   // EastRising 0.42" OLED
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//U8G2_NULL u8g2(U8G2_R0);	// null device, a 8x8 pixel display which does nothing
//U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 12, /* dc=*/ 4, /* reset=*/ 6);	// Arduboy (Production, Kickstarter Edition)
//U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8G2_SSD1306_128X64_NONAME_F_3W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* reset=*/ 8);
//U8G2_SSD1306_128X64_NONAME_F_3W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* reset=*/ 8);
//U8G2_SSD1306_128X64_ALT0_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   // same as the NONAME variant, but may solve the "every 2nd line skipped" problem
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* reset=*/ 8);
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 16, /* data=*/ 17, /* reset=*/ U8X8_PIN_NONE);   // ESP32 Thing, pure SW emulated I2C
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 16, /* data=*/ 17);   // ESP32 Thing, HW I2C with pin remapping
//U8G2_SSD1306_128X64_NONAME_F_6800 u8g2(U8G2_R0, 13, 11, 2, 3, 4, 5, 6, A4, /*enable=*/ 7, /*cs=*/ 10, /*dc=*/ 9, /*reset=*/ 8);
//U8G2_SSD1306_128X64_NONAME_F_8080 u8g2(U8G2_R0, 13, 11, 2, 3, 4, 5, 6, A4, /*enable=*/ 7, /*cs=*/ 10, /*dc=*/ 9, /*reset=*/ 8);
//U8G2_SSD1306_128X64_VCOMH0_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);	// same as the NONAME variant, but maximizes setContrast() range
//U8G2_SSD1306_64X48_ER_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   // EastRising 0.66" OLED breakout board, Uno: A4=SDA, A5=SCL, 5V powered
//U8G2_SSD1306_48X64_WINSTAR_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// End of constructor list

void setup(void)
{
  bool i2c_found;

  checkEEPROM();
  
  u8g2.begin();

  printStringToOLED("VFO-003");
  
  // Si8351 initialiation
  i2c_found = si5351.init(SI5351_CRYSTAL_LOAD_6PF, 27000000, 0);
  if (!i2c_found)
  {
     printStringToOLED("I2C Fail");
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
 
  // Rotary encoder initialization
  setupEncoder();
}

void loop(void)
{
    vfoMenu();
}
