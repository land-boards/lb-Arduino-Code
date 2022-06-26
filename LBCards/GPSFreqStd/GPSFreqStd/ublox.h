/*********************************************************************
ublox GPS library
Created by Andre Eisenbach for SCULLCOM Hobby Electronics
*********************************************************************/

#ifndef __UBLOX_H
#define __UBLOX_H

#include <SoftwareSerial.h>

class UBloxGPS
{
public:
  UBloxGPS(uint8_t pin_rx, uint8_t pin_tx);

  void writeFrequency(uint32_t freq);

private:
  SoftwareSerial ss_;
};

#endif // __UBLOX_H
