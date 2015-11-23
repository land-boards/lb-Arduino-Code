#include <Adafruit_NeoPixel.h>

#define PIN 3

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  colorWipe(strip.Color(0, 0, 0), 50); // Red
  strip.show(); // Initialize all pixels to 'off'
}

void loop() 
{
int wait = 100;
  strip.setPixelColor(0,80,0,0);
      strip.show();
      delay(wait);
      strip.setPixelColor(0,0,0,0);
      
      strip.setPixelColor(1,80,0,0);
      strip.show();
      delay(wait);
      strip.setPixelColor(1,0,0,0);

      strip.setPixelColor(2,80,0,0);
      strip.show();
      delay(wait);
      strip.setPixelColor(2,0,0,0);

      strip.setPixelColor(3,80,0,0);
      strip.show();
      delay(wait);
      strip.setPixelColor(3,0,0,0);

      strip.setPixelColor(4,80,0,0);
      strip.show();
      delay(wait);
      strip.setPixelColor(4,0,0,0);

      strip.setPixelColor(5,80,0,0);
      strip.show();
      delay(wait);
      strip.setPixelColor(5,0,0,0);

      strip.setPixelColor(6,80,0,0);
      strip.show();
      delay(wait);
      strip.setPixelColor(6,0,0,0);

      strip.setPixelColor(7,80,0,0);
      strip.show();
      delay(wait);
      strip.setPixelColor(7,0,0,0);

      strip.setPixelColor(6,80,0,0);
      strip.show();
      delay(wait);
      strip.setPixelColor(6,0,0,0);

      strip.setPixelColor(5,80,0,0);
      strip.show();
      delay(wait);
      strip.setPixelColor(5,0,0,0);

      strip.setPixelColor(4,80,0,0);
      strip.show();
      delay(wait);
      strip.setPixelColor(4,0,0,0);

      strip.setPixelColor(3,80,0,0);
      strip.show();
      delay(wait);
      strip.setPixelColor(3,0,0,0);

      strip.setPixelColor(2,80,0,0);
      strip.show();
      delay(wait);
      strip.setPixelColor(2,0,0,0);

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
  }
}

