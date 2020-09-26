#ifndef MCP42010_h
#define MCP42010_h

#include <Arduino.h>

/**
 * Arduino library for using the MCP42010 digital potentiometer with SPI.
 *
 * Copyright (c) 2015 Stefan Mensink. All right reserved.
 * Find this on Github: https://github.com/mensink/arduino-lib-MCP42010
 *
 * MIT license, all text above must be included in any redistribution
 */

class MCP42010 {
  public:
	// These are the pins used to connect to the chip
    MCP42010(int CS, int CLK, int MOSI);
	// Sets the given pot (1 or 2) to a given value (0-255)
    void setPot(byte pot, byte value);
  private:
    void transferSPI(byte data);
    int _CS, _CLK, _MOSI;
};

#endif
