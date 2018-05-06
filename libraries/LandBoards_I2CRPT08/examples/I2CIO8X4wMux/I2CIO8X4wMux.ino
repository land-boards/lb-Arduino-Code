// I2CIO8X4wMux Example code
// Uses Arduino UNO or compatible
// 8x I2CIO-8 cards
// I2C-RPI-08 as UUT
// Blink first LED on each I2CIO-8 card , one at a time

#include <Wire.h>
#include <LandBoards_I2CIO8.h>
#include "LandBoards_I2CRPT08.h"

LandBoards_I2CIO8 myI2CIO80;
LandBoards_I2CIO8 myI2CIO81;
LandBoards_I2CIO8 myI2CIO82;
LandBoards_I2CIO8 myI2CIO83;
LandBoards_I2CIO8 myI2CIO84;
LandBoards_I2CIO8 myI2CIO85;
LandBoards_I2CIO8 myI2CIO86;
LandBoards_I2CIO8 myI2CIO87;

LandBoards_I2CRPT08 mux;

void setup()
{
  uint8_t port;

  mux.begin(0);   // start the mux
  mux.setI2CChannel(0,1);
  myI2CIO80.begin(0);      // use default address 0
  mux.setI2CChannel(0,0);
  mux.setI2CChannel(1,1);
  myI2CIO81.begin(0);      // use default address 0
  mux.setI2CChannel(1,0);
  mux.setI2CChannel(2,1);
  myI2CIO82.begin(0);      // use default address 0
  mux.setI2CChannel(2,0);
  mux.setI2CChannel(3,1);
  myI2CIO83.begin(0);      // use default address 0
  mux.setI2CChannel(3,0);
  mux.setI2CChannel(4,1);
  myI2CIO84.begin(0);      // use default address 0
  mux.setI2CChannel(4,0);
  mux.setI2CChannel(5,1);
  myI2CIO85.begin(0);      // use default address 0
  mux.setI2CChannel(5,0);
  mux.setI2CChannel(6,1);
  myI2CIO86.begin(0);      // use default address 0
  mux.setI2CChannel(6,0);
  mux.setI2CChannel(7,1);
  myI2CIO87.begin(0);      // use default address 0
  mux.setI2CChannel(7,0);
}

// flip the pin #0 up and down

void loop()
{
  mux.setI2CChannel(0,1);
  myI2CIO80.writeLED(0, HIGH);
  delay(250);
  myI2CIO80.writeLED(0, LOW);
  mux.setI2CChannel(0,0);
  mux.setI2CChannel(1,1);
  myI2CIO81.writeLED(0, HIGH);
  delay(250);
  myI2CIO81.writeLED(0, LOW);
  mux.setI2CChannel(1,0);
  mux.setI2CChannel(2,1);
  myI2CIO82.writeLED(0, HIGH);
  delay(250);
  myI2CIO82.writeLED(0, LOW);
  mux.setI2CChannel(2,0);
  mux.setI2CChannel(3,1);
  myI2CIO83.writeLED(0, HIGH);
  delay(250);
  myI2CIO83.writeLED(0, LOW);
  mux.setI2CChannel(3,0);
  mux.setI2CChannel(4,1);
  myI2CIO84.writeLED(0, HIGH);
  delay(250);
  myI2CIO84.writeLED(0, LOW);
  mux.setI2CChannel(4,0);
  mux.setI2CChannel(5,1);
  myI2CIO85.writeLED(0, HIGH);
  delay(250);
  myI2CIO85.writeLED(0, LOW);
  mux.setI2CChannel(5,0);
  mux.setI2CChannel(6,1);
  myI2CIO86.writeLED(0, HIGH);
  delay(250);
  myI2CIO86.writeLED(0, LOW);
  mux.setI2CChannel(6,0);
  mux.setI2CChannel(7,1);
  myI2CIO87.writeLED(0, HIGH);
  delay(250);
  myI2CIO87.writeLED(0, LOW);
  mux.setI2CChannel(7,0);
}

