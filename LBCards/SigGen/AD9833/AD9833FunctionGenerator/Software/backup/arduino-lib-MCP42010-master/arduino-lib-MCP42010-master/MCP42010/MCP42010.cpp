#include "MCP42010.h"

/**
 * Arduino library for using the MCP42010 digital potentiometer with SPI.
 *
 * Copyright (c) 2015 Stefan Mensink. All right reserved.
 * Find this on Github: https://github.com/mensink/arduino-lib-MCP42010
 *
 * MIT license, all text above must be included in any redistribution
 */

MCP42010::MCP42010(int CS, int CLK, int MOSI) {
  _CS = CS;
  _CLK = CLK;
  _MOSI = MOSI;
  
  pinMode(_CS, OUTPUT);
  pinMode(_CLK, OUTPUT);
  pinMode(_MOSI, OUTPUT);
  digitalWrite(_CLK, LOW);
}

void MCP42010::setPot(byte pot, byte value) {
  digitalWrite(_CS, LOW);
  transferSPI((pot & B11) | B00010000);
  transferSPI(value);
  digitalWrite(_CS, HIGH);
}

void MCP42010::transferSPI(byte data) {
  for (byte i=1; i<=8; i++) {
    digitalWrite(_MOSI, (data >> (8-i)) & 1 ? HIGH : LOW);
    digitalWrite(_CLK, HIGH);
    digitalWrite(_CLK, LOW);
  }
}
