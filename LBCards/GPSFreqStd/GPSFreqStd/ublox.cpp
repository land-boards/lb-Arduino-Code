/*********************************************************************
ublox GPS library
Created by Andre Eisenbach for SCULLCOM Hobby Electronics
*********************************************************************/

#include "ublox.h"

#include <stdint.h>
#include <string.h> // for memset()

namespace
{
  struct GPS_TP5_MSG
  {
    uint8_t   header1;
    uint8_t   header2;
    uint8_t   message_class;
    uint8_t   message_id;
    uint16_t  length;
    uint8_t   timepulse_idx;
    uint8_t   version;
    uint16_t  reserved;
    int16_t   antenna_cable_delay;
    int16_t   rf_group_delay;
    uint32_t  frequency_unlocked;
    uint32_t  frequency_locked;
    uint32_t  duty_cycle_unlocked;
    uint32_t  duty_cycle_locked;
    uint32_t  user_delay;
    uint32_t  flags;
    uint16_t  checksum;
  } __attribute__((packed));

  const uint16_t GPS_TP5_ACTIVE           = 0x01;
  const uint16_t GPS_TP5_SYNC_TO_GNSS     = 0x02;
  const uint16_t GPS_TP5_LOCKED_OTHER_SET = 0x04;
  const uint16_t GPS_TP5_IS_FREQUENCY     = 0x08;
  const uint16_t GPS_TP5_IS_LENGTH        = 0x10;
  const uint16_t GPS_TP5_ALIGN_TO_TOW     = 0x20;
  const uint16_t GPS_TP5_POLARITY_RISING  = 0x40;

  const uint32_t GPS_TP5_DUTY_CYCLE_50    = 0x80000000;
  
  uint16_t calculateChecksum(uint8_t *p, size_t len)
  {
    uint8_t ck_a = 0;
    uint8_t ck_b = 0;
    while (len--)
    {
      ck_a = ck_a + *p++;
      ck_b = ck_b + ck_a;
    }
    return ck_a | (ck_b << 8);
  }
}

UBloxGPS::UBloxGPS(uint8_t pin_rx, uint8_t pin_tx) : ss_(SoftwareSerial(pin_rx, pin_tx))
{
  ss_.begin(9600);
}

void UBloxGPS::writeFrequency(uint32_t freq)
{
  GPS_TP5_MSG msg;
  memset(&msg, 0, sizeof(msg));

  msg.header1 = 0xB5;
  msg.header2 = 0x62;
  msg.message_class = 0x06;
  msg.message_id = 0x31;
  msg.length = 32;
  msg.version = 1;
  msg.antenna_cable_delay = 50;
  msg.frequency_unlocked = 3333;
  msg.duty_cycle_unlocked = GPS_TP5_DUTY_CYCLE_50;
  msg.duty_cycle_locked = GPS_TP5_DUTY_CYCLE_50;
  msg.flags = GPS_TP5_ACTIVE | GPS_TP5_SYNC_TO_GNSS | GPS_TP5_LOCKED_OTHER_SET | GPS_TP5_IS_FREQUENCY;

  msg.frequency_locked = freq;
  msg.checksum = calculateChecksum(((uint8_t*)&msg) + 2, 4 + msg.length);
  for (uint16_t i=0; i<sizeof(msg); i++)
    printf("i=%d, val = %02x\r\n",i,(char)msg[i]);
  return;


  ss_.write((char*)&msg, sizeof(msg));
}
