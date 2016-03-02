/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>
#include <SPI.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(2,3);

const int slaveSelectPin = 10;

//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
  // set the slaveSelectPin as an output:
  pinMode (slaveSelectPin, OUTPUT);
  // initialize SPI:
  SPI.begin(); 
}

long oldPosition  = -999;

void loop() {
  long newPosition = myEnc.read()>>2;
  if (newPosition < 0)
  {
    myEnc.write(0);
    newPosition = 0;
  }
  if (newPosition > 128)
  {
    myEnc.write(512);
    newPosition = 128;
  }
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
    digitalPotWrite(0, newPosition);
  }
}

int digitalPotWrite(int address, int value) {
  // take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin,LOW);
  //  send in the address and value via SPI:
  SPI.transfer(address);
  SPI.transfer(value);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin,HIGH); 
}
