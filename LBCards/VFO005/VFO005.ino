/*

  VFO005.ino

  http://land-boards.com/blwiki/index.php?title=HW-9_VFO

  OLED is 128x32 I2C device
  Si5351 is on a custom board
  Runs on Blue Pill Hub so no 5V to 3.3V level shifting is needed

  Borrowed bits pieces from all over the place
  Si6361 driver is from si5351_example
  https://etherkit.github.io/si5351abb_landing_page.html
  Copyright (C) 2015 - 2016 Jason Milldrum <milldrum@gmail.com>

*/

#include <Arduino.h>
#include <EEPROM.h>
#include <U8g2lib.h>
#include <AD9833.h>
#include <digitalWriteFast.h>

// EEPROM is used to store initial values
// STM3232 parts have no internal EEPROM
// ATMEGA parts have internal EEPROM
// Set defines/undefs appropriately
#define HAS_INTERNAL_EEPROM
//#undef HAS_INTERNAL_EEPROM

#define encoderSwitch  4

#define U8X8_HAVE_HW_I2C

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define FNC_PIN 10       // Can be any digital IO pin

AD9833 gen(FNC_PIN);       // Defaults to 25MHz internal reference frequency

enum VFO_ON_OFF
{
  VFO_OFF,
  VFO_ON
};

uint8_t VFO_O_OnOff;

long VFO_0_Freq;

#define STEP_1_HZ     1ULL
#define STEP_10_HZ    10ULL
#define STEP_100_HZ   100ULL
#define STEP_1_KHZ    1000ULL
#define STEP_10_KHZ   10000ULL
#define STEP_100_KHZ  100000ULL
#define STEP_1_MHZ    1000000ULL

// Gloibal variables
uint32_t stepSize;

enum WAVEFORM_TYPE
{
  SINE_WAVE_TYPE,
  TRIANGLE_WAVE_TYPE,
  SQUARE_WAVE_TYPE,
  HALF_SQUARE_WAVE_TYPE
};

WAVEFORM_TYPE waveformType;

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);  // STM32, Ebay OLED

// Leave other SSD1306 constructors just in case
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
  checkEEPROM();

  Serial.begin(9600);

  u8g2.begin();
  delay(100);
  u8g2_prepare();
  u8g2.clearBuffer();
  u8g2.drawStr(0, 10, "VFO-005");
  u8g2.sendBuffer();
  delay(500);

  gen.Begin();
  if (waveformType == HALF_SQUARE_WAVE_TYPE)
    gen.ApplySignal(HALF_SQUARE_WAVE, REG0, float(VFO_0_Freq));
  else if (waveformType == SQUARE_WAVE_TYPE)
    gen.ApplySignal(SQUARE_WAVE, REG0, float(VFO_0_Freq));
  else if (waveformType == TRIANGLE_WAVE_TYPE)
    gen.ApplySignal(TRIANGLE_WAVE, REG0, float(VFO_0_Freq));
  else if (waveformType == SINE_WAVE_TYPE)
    gen.ApplySignal(SINE_WAVE, REG0, float(VFO_0_Freq));
  gen.EnableOutput(VFO_O_OnOff);

  // Encoder initialization
  pinMode(encoderSwitch, INPUT_PULLUP);
  setupEncoder();
  delay(100);
}

void loop(void)
{
  while (1)
  {
    vfoMenu();
  }
}
