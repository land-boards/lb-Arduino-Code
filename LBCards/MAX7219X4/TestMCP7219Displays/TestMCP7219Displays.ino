// TestMCP7219Displays
//
// This uses two displays.
//

#include <Arduino.h>
#include <MAX72XX.h>    // https://github.com/abaskin/MAX72XX

constexpr uint8_t latchPin = 10;  // change to reflect your latchPin
constexpr uint8_t numDevices = 2; // the number of devices

// for hardware SPI
// create the object for the device chain
//MAX72XX dispChain(latchPin, numDevices);

// for software SPI
constexpr uint8_t dataPin = 12;   // change to reflect your dataPin
constexpr uint8_t clockPin = 11;  // change to reflect your clockPin
MAX72XX dispChain(dataPin, clockPin, latchPin, numDevices);

void setup() {
  int i;
  dispChain.setIntensity(2); // set the intensity for all the devices
  for (i=1; i < 15; i++)
    dispChain.writeDigitRaw(0x7i,"A");
}

void loop() {

}
