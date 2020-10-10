/*

  VFO_Si5351.ino

  Borrowed bits pieces from all over the place
*/

#include <Arduino.h>
#include <U8g2lib.h>
#include "si5351.h"

#define encoderSwitch  PA7

#define U8X8_HAVE_HW_I2C
//#undef U8X8_HAVE_HW_SPI

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

Si5351 si5351;

// Gloibal variables
unsigned long stepSize;

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

void setup(void) {
  bool i2c_found;
  
  u8g2.begin();
  
  Serial.begin(9600);

  // Si8351 initialiation
  i2c_found = si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0);
  if (!i2c_found)
  {
    Serial.println("Device not found on I2C bus!");
  }

  // Set CLK0 to output 14 MHz
  si5351.set_freq(1400000000ULL, SI5351_CLK0);

  // Set CLK1 to output 175 MHz
  //  si5351.set_ms_source(SI5351_CLK1, SI5351_PLLB);
  //  si5351.set_freq_manual(17500000000ULL, 70000000000ULL, SI5351_CLK1);

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
  unsigned long freqInt = 1400000000ULL;
  float freq = float(freqInt / 100ULL);
  int encoderDelta = 0;
  
  stepSize = 10000ULL;
//  si5351.update_status();
  si5351.set_freq(freqInt, SI5351_CLK0);
  displayFreqInKHzOnOLED(freq);
  u8g2.sendBuffer();

  while (1)
  {
    pollEncoder();
    encoderDelta = getEncoderDelta();
    if (encoderDelta != 0)
    {
      freqInt += (encoderDelta * stepSize); // count up/dowb by 100 Hz
      if (freqInt > 1435000000ULL)
        freqInt = 1435000000ULL;
      else if (freqInt < 1400000000ULL)
        freqInt = 1400000000ULL;
      freq = float(freqInt / 100ULL);
      si5351.set_freq(freqInt, SI5351_CLK0);
      displayFreqInKHzOnOLED(freq);
     }
    if (checkSwitch() == 1)
    {
      vfoMenu();
      displayFreqInKHzOnOLED(freq);
    }
  }
}
