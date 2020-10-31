/*

  VFO_Si5351.ino

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
#include "si5351.h"

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

Si5351 si5351;

// enum si5351_drive {SI5351_DRIVE_2MA, SI5351_DRIVE_4MA, SI5351_DRIVE_6MA, SI5351_DRIVE_8MA};

si5351_drive VFO_0_Drive = SI5351_DRIVE_4MA;
si5351_drive VFO_1_Drive = SI5351_DRIVE_4MA;
si5351_drive VFO_2_Drive = SI5351_DRIVE_4MA;

enum VFO_ON_OFF
{
  VFO_OFF,
  VFO_ON
};

unsigned long VFO_0_Freq = 1400000000ULL;
unsigned long VFO_1_Freq = 1200000000ULL;
unsigned long VFO_2_Freq = 1000000000ULL;

uint8_t VFO_O_OnOff = VFO_ON;
uint8_t VFO_1_OnOff = VFO_ON;
uint8_t VFO_2_OnOff = VFO_ON;

uint8_t currentVFONumber = 0;
int32_t calFactor = 0;

#define STEP_1_HZ     100ULL
#define STEP_10_HZ    1000ULL
#define STEP_100_HZ   10000ULL
#define STEP_1_KHZ    100000ULL
#define STEP_10_KHZ   1000000ULL
#define STEP_100_KHZ  10000000ULL
#define STEP_1_MHZ    100000000ULL
#define STEP_10_MHZ   1000000000ULL

// Gloibal variables
uint32_t stepSize = STEP_1_MHZ;

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

//unsigned long VFO_0_Freq = 1400000000ULL;
//unsigned long VFO_1_Freq = 1200000000ULL;
//unsigned long VFO_2_Freq = 1000000000ULL;
//
//uint32_t stepSize = STEP_1_MHZ;
//int32_t calFactor = 0;
//
//uint8_t VFO_O_OnOff = VFO_ON;
//uint8_t VFO_1_OnOff = VFO_ON;
//uint8_t VFO_2_OnOff = VFO_ON;
//
//uint8_t currentVFONumber = 0;

#define FREQ0_OFFSET 0
#define FREQ1_OFFSET 4
#define FREQ2_OFFSET 8
#define STEPSIZE_OFFSET 12
#define CALVAL_OFFSET 16
#define VFO0ONOFF_OFFSET 20
#define VFO1ONOFF_OFFSET 21
#define VFO2ONOFF_OFFSET 22
#define VFONUMBER_OFFSET 23
#define MAGICNUMBER_OFFSET 24

void loadEEPROM(void)
{
  VFO_0_Freq = EEPROM.get(FREQ0_OFFSET,VFO_0_Freq);
  VFO_1_Freq = EEPROM.get(FREQ1_OFFSET,VFO_1_Freq);
  VFO_2_Freq = EEPROM.get(FREQ2_OFFSET,VFO_2_Freq);
  stepSize = EEPROM.get(STEPSIZE_OFFSET,stepSize);
  calFactor = EEPROM.get(CALVAL_OFFSET,calFactor);
  VFO_O_OnOff = EEPROM.get(VFO0ONOFF_OFFSET,VFO_O_OnOff);
  VFO_1_OnOff = EEPROM.get(VFO1ONOFF_OFFSET,VFO_1_OnOff);
  VFO_2_OnOff = EEPROM.get(VFO2ONOFF_OFFSET,VFO_2_OnOff);
  currentVFONumber = EEPROM.get(VFONUMBER_OFFSET,currentVFONumber);
}

void storeEEPROM(void)
{
  uint8_t magicNumber = 0x5a;
  EEPROM.put(FREQ0_OFFSET,VFO_0_Freq);
  EEPROM.put(FREQ1_OFFSET,VFO_1_Freq);
  EEPROM.put(FREQ2_OFFSET,VFO_2_Freq);
  EEPROM.put(STEPSIZE_OFFSET,stepSize);
  EEPROM.put(CALVAL_OFFSET,calFactor);
  EEPROM.put(VFO0ONOFF_OFFSET,VFO_O_OnOff);
  EEPROM.put(VFO1ONOFF_OFFSET,VFO_1_OnOff);
  EEPROM.put(VFO2ONOFF_OFFSET,VFO_2_OnOff);
  EEPROM.put(VFONUMBER_OFFSET,currentVFONumber);
  EEPROM.put(MAGICNUMBER_OFFSET,magicNumber);
}

void checkEEPROM(void)
{
  uint8_t magicNumber = 0x5a;
  #ifdef HAS_INTERNAL_EEPROM
    if (EEPROM.get(MAGICNUMBER_OFFSET,magicNumber) == 0x5a)
      loadEEPROM();
    else
      storeEEPROM();
  #endif
}

void setup(void)
{
  bool i2c_found;

  checkEEPROM();
  
  u8g2.begin();
  
  Serial.begin(9600);

  // Si8351 initialiation
  i2c_found = si5351.init(SI5351_CRYSTAL_LOAD_10PF, 0, 0);
  if (!i2c_found)
  {
    Serial.println("Device not found on I2C bus!");
  }

  // Set CLK0 to output 14 MHz
  si5351.set_freq(VFO_0_Freq, SI5351_CLK0);

  // Set CLK1 to output 12 MHz
  si5351.set_freq(VFO_1_Freq, SI5351_CLK1);

  // Set CLK2 to output 10 MHz
  si5351.set_freq(VFO_2_Freq, SI5351_CLK2);

  // Query a status update and wait a bit to let the Si5351 populate the
  // status flags correctly.
  si5351.update_status();
  
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
