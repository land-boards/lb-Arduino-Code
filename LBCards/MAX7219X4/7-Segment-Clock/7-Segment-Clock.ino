// 
//
// This uses two displays.
// Decimal points are used to separate the time and date fields.
// It takes around four seconds for the time to sync with the ntp server.
//

#include <Arduino.h>
#include <MAX72XX.h>

constexpr uint8_t latchPin = 9;  // change to reflect your latchPin
constexpr uint8_t numDevices = 2; // the number of devices

// for hardware SPI
// create the object for the device chain
//MAX72XX dispChain(latchPin, numDevices);

// for software SPI
constexpr uint8_t dataPin = 11;   // change to reflect your dataPin
constexpr uint8_t clockPin = 13;  // change to reflect your clockPin
MAX72XX dispChain(dataPin, clockPin, latchPin, numDevices);

void setup() {
  dispChain.setIntensity(6); // set the intensity for all the devices
//  dispChain.update();
}

void loop() {

}
