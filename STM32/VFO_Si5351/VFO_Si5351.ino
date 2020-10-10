/*

  VFO_Si5351.ino

BITS AND PECES FROM ALL OVER THE PLACE
*/

#include <Arduino.h>
#include <U8g2lib.h>
#include "si5351.h"

//#define U8X8_HAVE_HW_I2C
//#undef U8X8_HAVE_HW_SPI

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

Si5351 si5351;

/*
  U8g2lib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.
    
*/

// Please UNCOMMENT one of the contructor lines below
// U8g2 Contructor List (Frame Buffer)
// The complete list is available here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp
// Please update the pin numbers according to your setup. Use U8X8_PIN_NONE if the reset pin is not connected

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);  // STM32, Ebay OLED

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

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_ncenB14_tr); // 14 Pixel tall font
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void displayFreq(float freq) {
  char buffer[14];
  dtostrf(freq/1000.0,9,3,buffer);
  // Adda a comma below the MHz digits
  buffer[7] = buffer[6];
  buffer[6] = buffer[5];
  buffer[5] = buffer[4];
  buffer[4] = buffer[3];
  buffer[3] = buffer[2];
  buffer[2] = ',';
  buffer[8] = ' ';
  buffer[9] = 'K';
  buffer[10] = 'H';
  buffer[11] = 'z';
  buffer[12] = 0;
//  buffer[9] = buffer[8];
//  buffer[8] = buffer[7];
//  buffer[7] = ',';
//  buffer[10] = 0;
  u8g2.drawStr( 0, 0, buffer);
}

void setup(void) {
  bool i2c_found;
  u8g2.begin();
  Serial.begin(9600);
  setupEncoder();
  i2c_found = si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0);
  if(!i2c_found)
  {
    Serial.println("Device not found on I2C bus!");
  }

  // Set CLK0 to output 14 MHz
  si5351.set_freq(1400000000ULL, SI5351_CLK0);

  // Set CLK1 to output 175 MHz
  si5351.set_ms_source(SI5351_CLK1, SI5351_PLLB);
  si5351.set_freq_manual(17500000000ULL, 70000000000ULL, SI5351_CLK1);

  // Query a status update and wait a bit to let the Si5351 populate the
  // status flags correctly.
  si5351.update_status();
  delay(500);
}

extern volatile int encoder0Pos;

void loop(void) {
  unsigned long freqInt = 1400000000ULL;
  int EncVal = encoder0Pos;   // get initial encoder position
  int delta = 0;
  Serial.print("Init encVal ");
  Serial.print(EncVal);
  Serial.print("\n");
  float freq = float(freqInt/100ULL);
  // Read the Status Register and print it every 10 seconds
  si5351.update_status();
  Serial.print("SYS_INIT: ");
  Serial.print(si5351.dev_status.SYS_INIT);
  Serial.print("  LOL_A: ");
  Serial.print(si5351.dev_status.LOL_A);
  Serial.print("  LOL_B: ");
  Serial.print(si5351.dev_status.LOL_B);
  Serial.print("  LOS: ");
  Serial.print(si5351.dev_status.LOS);
  Serial.print("  REVID: ");
  Serial.println(si5351.dev_status.REVID);

  while(1)
  {
    u8g2.clearBuffer();
    u8g2_prepare();
    si5351.set_freq(freqInt, SI5351_CLK0);
    displayFreq(freq);
    u8g2.sendBuffer();
    EncVal = encoder0Pos;
   if (EncVal == 0)
    {
      delta = 0;
    }
    else if (EncVal < 0)
    {
      delta = -1;
      Serial.print("delta ");
      Serial.print(delta);
      Serial.print("\n");
    }
    else if (EncVal > 0)
    {
      delta = 1;
      Serial.print("delta ");
      Serial.print(delta);
      Serial.print("\n");
    }
    encoder0Pos = 0;
    if (delta != 0)
    {
      if (freqInt > 1435000000ULL)
        freqInt = 1435000000ULL;
      else if (freqInt < 1400000000ULL)
        freqInt = 1400000000ULL;
      freq = float(freqInt/100ULL);
      freqInt += (delta*10000ULL); // count up by 100 Hz
    }
  }
}
