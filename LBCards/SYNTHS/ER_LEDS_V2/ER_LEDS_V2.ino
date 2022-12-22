// ER_LEDS_V2 NeoPixel driving Eurorack LED strip
// Pots
//  RV1 - controls mode of operation
//  RV2 - controls intensity of LEDs (most modes)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// NeoPixel string pin
#define LED_PIN    9

// 104 HP fits 17 LEDs
#define LED_COUNT 17

// Keep track of the current mode as a global
uint8_t mode;

// Add more modes here if desired
enum modesList
{
  RGBSTRIP,
  THEATRESTRIP,
  THEATRERAINBOW,
  ALLWHITE
};

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)


// setup() function -- runs once at startup --------------------------------

void setup() 
{
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  mode = (analogRead(A0) >> 8) & 0x3;
}

// setMode() - RV2 controls the mode with deadband
// deadband eliminates pot noise
// Range is in quarters of rotation, if different number of modes change constants
#define DEADBAND 6
void setMode()
{
  uint16_t modeI = analogRead(A0);
  if ((0 <= modeI) && (modeI < (256 - DEADBAND)))
    mode = RGBSTRIP;
  else if ((256 <= modeI) && (modeI < (512 - DEADBAND)))
    mode = THEATRESTRIP;
  else if ((512 <= modeI) && (modeI < (768 - DEADBAND)))
    mode = THEATRERAINBOW;
  else if ((768 <= modeI) && (modeI  < 1023))
    mode = ALLWHITE;
  return;
}

// loop() function -- runs repeatedly as long as board is on ---------------

void loop()
{
  uint16_t brt = analogRead(A1);
  brt >>= 2;

  // Fill along the length of the strip in various colors...
  setMode();
  if (mode == RGBSTRIP)
  {
    brt = analogRead(A1);
    brt >>= 2;
    colorWipe(strip.Color(brt,   0,   0), 50); // Red
    if (mode != RGBSTRIP)
      return;
    brt = analogRead(A1);
    brt >>= 2;
    colorWipe(strip.Color(  0, brt,   0), 50); // Green
    if (mode != RGBSTRIP)
      return;
    brt = analogRead(A1);
    brt >>= 2;
    colorWipe(strip.Color(  0,   0, brt), 50); // Blue
  }
  else if (mode == THEATRESTRIP)
  {
    // Do a theater marquee effect in various colors...
    brt = analogRead(A1);
    brt >>= 2;
    theaterChase(strip.Color(brt, brt, brt), 50); // White, half brightness
    setMode();
    if (mode != THEATRESTRIP)
      return;
    brt = analogRead(A1);
    brt >>= 2;
    theaterChase(strip.Color(brt,   0,   0), 50); // Red, half brightness
    setMode();
    if (mode != THEATRESTRIP)
      return;
    brt = analogRead(A1);
    brt >>= 2;
    theaterChase(strip.Color(  0, brt,   0), 50); // Green, half brightness
    setMode();
    if (mode != THEATRESTRIP)
      return;
    brt = analogRead(A1);
    brt >>= 2;
    theaterChase(strip.Color(  0,   0, brt), 50); // Blue, half brightness
  }
  else if (mode == THEATRERAINBOW)
  {
    rainbow(10);             // Flowing rainbow cycle along the whole strip
    theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
  }
  else if (mode == ALLWHITE)
  {
    allWhite(10, brt);
  }
}


// Some functions of our own for creating animated effects -----------------

//enum modesList
//{
//  RGBSTRIP,
//  THEATRESTRIP,
//  THEATRERAINBOW,
//  ALLWHITE
//};

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
    setMode();
    if (mode != RGBSTRIP)
      return;
  }
}

void allWhite(int wait, uint8_t brt)
{
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, strip.Color(brt, brt, brt));         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
  }
  delay(wait);                           //  Pause for a moment
}


// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait)
{
  for (int b = 0; b < 3; b++) { //  'b' counts from 0 to 2...
    strip.clear();         //   Set all pixels in RAM to 0 (off)
    // 'c' counts up from 'b' to end of strip in steps of 3...
    for (int c = b; c < strip.numPixels(); c += 3) {
      strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      setMode();
      if (mode != THEATRESTRIP)
        return;
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
    setMode();
    if (mode != THEATRESTRIP)
      return;
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this loop:
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
    strip.rainbow(firstPixelHue);
    // Above line is equivalent to:
    // strip.rainbow(firstPixelHue, 1, 255, 255, true);
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
    setMode();
    if (mode != 2)
      return;
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for (int b = 0; b < 3; b++) { //  'b' counts from 0 to 2...
    strip.clear();         //   Set all pixels in RAM to 0 (off)
    // 'c' counts up from 'b' to end of strip in increments of 3...
    for (int c = b; c < strip.numPixels(); c += 3) {
      // hue of pixel 'c' is offset by an amount to make one full
      // revolution of the color wheel (range 65536) along the length
      // of the strip (strip.numPixels() steps):
      int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
      uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
      strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      setMode();
      if (mode != THEATRERAINBOW)
        return;
    }
    strip.show();                // Update strip with new contents
    delay(wait);                 // Pause for a moment
    firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    setMode();
    if (mode != THEATRERAINBOW)
      return;
  }
}
