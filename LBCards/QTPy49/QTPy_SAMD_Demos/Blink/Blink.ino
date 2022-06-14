#include <Adafruit_NeoPixel.h>

// create a pixel strand with 1 pixel on PIN_NEOPIXEL
Adafruit_NeoPixel pixels(1, PIN_NEOPIXEL);

void setup() {
    pixels.begin();  // initialize the pixel
}

void loop() {
    // set the first pixel #0 to red
    pixels.setPixelColor(0, pixels.Color(31, 0, 0));
    // and write the data
    pixels.show();
  
    delay(1000);
    
    // turn off the pixel
    pixels.clear();
    pixels.show();
  
    delay(1000);
}
