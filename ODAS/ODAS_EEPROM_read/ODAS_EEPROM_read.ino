// ODAS_EEPROM

#include <Wire.h>
#include <I2C_eeprom.h>

#define EE24LC024MAXBYTES 2048/8

// EEPROM nase address
#define DEVICEADDRESS (0x50)

#define TEST_ADDR 16

// this must start on a page boundary!
#define TEST_PAGE_ADDR 0
#define SHORT_BUFFER_LEN 4

// this tests multi-page writes
#define LONG_BUFFER_LEN 64
// make sure it's aligned on a page boundary
#define LONG_TEST_PAGE_ADDR (max(16, TEST_PAGE_ADDR + SHORT_BUFFER_LEN))

#define SERIAL_DEBUG Serial

I2C_eeprom eeprom(DEVICEADDRESS, EE24LC024MAXBYTES);

// https://github.com/raspberrypi/hats/blob/master/eeprom-format.md

struct eep_vals
{
  char signature[4];
  byte fmt_version;
  byte rsvd;
  short numatoms;
  long eeplen;
  char uuid[16];
  short pid;
  char vslen;
  char pslen;
  char vstr[32];
  char pstr[32];
};

  void setup()
{
  eep_vals readEE;

  SERIAL_DEBUG.begin(57600);

  while (!SERIAL_DEBUG); // wait for SERIAL_DEBUG port to connect. Needed for Leonardo only

  eeprom.begin();

  eeprom.readBlock((const uint16_t) 0, (uint8_t*) readEE.signature, (const uint16_t) 96);

  Serial.print("Signature=");
  Serial.print(readEE.signature[0]);
  Serial.print(readEE.signature[1]);
  Serial.print(readEE.signature[2]);
  Serial.println(readEE.signature[3]);
  Serial.print("ProductID=");
  Serial.println(readEE.pid,HEX);
  Serial.print("Vendor=");
  Serial.println(readEE.vstr);
  Serial.print("Product=");
  Serial.println(readEE.pstr);
}

void loop()
{
}
