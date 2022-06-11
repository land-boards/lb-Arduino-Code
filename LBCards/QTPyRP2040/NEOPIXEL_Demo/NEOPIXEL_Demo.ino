// NEOPIXEL demo
// Some weird colors in the demo

#include <Adafruit_NeoPixel.h>
 
int NeopixelPower = 11;
int NeopixelData  = 12;
#define NUMPIXELS 1
 
Adafruit_NeoPixel pixels(NUMPIXELS, NeopixelData, NEO_GRB + NEO_KHZ800);
 
void setup() {
  pixels.begin();
  pinMode(NeopixelPower,OUTPUT);
  digitalWrite(NeopixelPower, HIGH);
 
}
 
void loop() { 
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(15, 25, 205));
  delay(400);
  pixels.show();
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(103, 25, 205));
  delay(400);
  pixels.show();
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(233, 242, 205));
  delay(400);
  pixels.show();
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(233, 23, 23));
  delay(400);
  pixels.show();
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(12, 66, 101));
  delay(400);
  pixels.show();
  delay(500);
 
}
