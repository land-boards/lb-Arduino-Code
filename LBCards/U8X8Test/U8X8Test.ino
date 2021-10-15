// https://github.com/olikraus/u8g2/wiki/u8x8reference#c-example

#include <Arduino.h>
#include <SPI.h>
#include <U8x8lib.h>

#define U8X8_HAVE_HW_I2C

U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(U8X8_PIN_NONE);

void setup() {
  // put your setup code here, to run once:
  u8x8.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  u8x8.setFont(u8x8_font_victoriabold8_r);
  u8x8.drawString(0,0,"Hello World!");
  delay(1000);

}
