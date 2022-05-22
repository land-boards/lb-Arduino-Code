/*

  OLED_Test.ino

  Wiki page for Arduino In A Box
    http://land-boards.com/blwiki/index.php?title=ArduinoInABox

  Runs on a 3.3V Arduino Pro Mini
  No 5V to 3.3V level shifting is needed for the I2C port of the OLED
  Arduino Pro Mini has internal EEPROM for parameter storage

  OLED is 128x32 I2C device
  SSD1306 controller
  OLED driver Wiki page
    https://github.com/olikraus/u8g2/wiki
    8x8 font has 16x4 characters

*/

#include <Arduino.h>
#include <U8g2lib.h>

// defines and enums - Set defines/undefs appropriately

// Rotary encoder pins on the Arduino Pro Mini
#define ROTARY_DATA 2
#define ROTARY_CLK 3
#define encoderSwitch  4

#define U8X8_HAVE_HW_I2C

// Gloibal variables

enum ControlsState
{
  NOTHING,
  ENC_SW_PRESSED,
  ENC_UP,
  ENC_DOWN
};

#define TOP_PORT 17
#define DELAY_TIME 250

// Constructors

U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(U8X8_PIN_NONE);

// End of constructor list

//setup run once
void setup(void)
{
  uint8_t outPort;
  u8x8.begin();
  u8x8.setBusClock(400000);   // I2C clock = 400 KHz
  u8x8.clearDisplay();
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  u8x8.draw2x2String(0, 0, "Hello");
  delay(1000);

  // Rotary encoder initialization
  setupEncoder();

  // Make all other pins HIGH
  for (outPort = 5; outPort <= TOP_PORT;  outPort++)
    pinMode(outPort, OUTPUT);
}

// loop - loops forever
void loop(void)
{
  uint8_t outPort;
  for (outPort = 5; outPort <= TOP_PORT;  outPort++)
  {
    digitalWrite(outPort, HIGH);
    delay(DELAY_TIME);
    digitalWrite(outPort, LOW);
  }
}
