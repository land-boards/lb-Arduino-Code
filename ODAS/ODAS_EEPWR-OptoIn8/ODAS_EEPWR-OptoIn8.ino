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
  SERIAL_DEBUG.begin(57600);
  char readBuff[97];
  readBuff[96] = 0;
  while (!SERIAL_DEBUG); // wait for SERIAL_DEBUG port to connect. Needed for Leonardo only
  eeprom.begin();
  eep_vals myEep;
  
  Serial.println("Initializing eep buffer");
  myEep.signature[0] = 'O';
  myEep.signature[1] = 'D';
  myEep.signature[2] = 'A';
  myEep.signature[3] = 'S';
  myEep.fmt_version = 0x01;
  myEep.rsvd = 0;
  myEep.numatoms = 0x2;
  myEep.eeplen = 96;
  myEep.uuid[0] = '0';  // Serial number
  myEep.uuid[1] = '0';
  myEep.uuid[2] = '0';
  myEep.uuid[3] = '0';
  myEep.uuid[4] = '0';
  myEep.uuid[5] = '0';
  myEep.uuid[6] = '0';
  myEep.uuid[7] = '0';
  myEep.uuid[8] = '0';
  myEep.uuid[9] = '0';
  myEep.uuid[10] = '0';
  myEep.uuid[11] = '0';
  myEep.uuid[12] = '0';
  myEep.uuid[13] = '0';
  myEep.uuid[14] = '0';
  myEep.uuid[15] = '0';
  myEep.pid = 0x03;
  myEep.vslen = 32;
  myEep.pslen = 32;
  strcpy(myEep.vstr,"land.boards.com");
  strcpy(myEep.pstr,"OptoIn8-I2C");
  
  Serial.print("len of buffer=");
  Serial.println(sizeof(myEep));
    
  eeprom.writeBlock(0, (const uint8_t*) myEep.signature, 96);
  Serial.println("reading block");
  delay(10);
    
  eeprom.readBlock((const uint16_t) 0, (unsigned char*) readBuff, (const uint16_t) 96);
  
  Serial.print("readBuff len=");
  Serial.println(sizeof(readBuff));
  Serial.print("read back=");
  Serial.println(readBuff);
  for (int loopv = 0; loopv < 97; loopv++)
    Serial.print(readBuff[loopv]);
}

void loop()
{
}
