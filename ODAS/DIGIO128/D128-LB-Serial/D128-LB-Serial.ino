// DIGIO-16 Loopback code
// Test each channel

#include <Wire.h>
#include "Adafruit_MCP23017.h"
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

Adafruit_MCP23017 mcp0;
Adafruit_MCP23017 mcp1;
Adafruit_MCP23017 mcp2;
Adafruit_MCP23017 mcp3;
Adafruit_MCP23017 mcp4;
Adafruit_MCP23017 mcp5;
Adafruit_MCP23017 mcp6;
Adafruit_MCP23017 mcp7;

uint32_t failCount;
uint32_t passCount;

I2C_eeprom eeprom(DEVICEADDRESS, EE24LC024MAXBYTES);

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

int looping;

void setup()
{
  Serial.begin(9600);
  mcp0.begin(0);      // use default address 0
  mcp1.begin(1);      // use default address 0
  mcp2.begin(2);      // use default address 0
  mcp3.begin(3);      // use default address 0
  mcp4.begin(4);      // use default address 0
  mcp5.begin(5);      // use default address 0
  mcp6.begin(6);      // use default address 0
  mcp7.begin(7);      // use default address 0
  TWBR = 12;    // go to 400 KHz I2C speed mode

  uint8_t chip;
  uint8_t port;

  for (chip = 0; chip < 8; chip++)
  {
    for (port = 0; port < 16; port++)
    {
      mcpPinMode(chip, port, INPUT);
    }
  }
  failCount = 0;
  passCount = 0;
  looping = 0;
  Serial.println("R=Read EEPROM, W=Write EEPROM, T=Test DIGIOs, L=Loop Test");
}

void loop()
{
  char readBuff[97];
  readBuff[96] = 0;
  int incomingByte = 0;   // for incoming serial data
  if (Serial.available() > 0)
  {
    // read the incoming byte:
    incomingByte = Serial.read();
    if ((incomingByte == 'R') || (incomingByte == 'r'))
    {
      Serial.println("Reading EEPROM");
      delay(10);

      eeprom.readBlock((const uint16_t) 0, (unsigned char*) readBuff, (const uint16_t) 96);

      Serial.print("Family=");
      for (int loopv = 0; loopv < 4; loopv++)
        Serial.print(readBuff[loopv]);
      Serial.println("");
      Serial.print("Company=");
      for (int loopv = 32; loopv < 48; loopv++)
        Serial.print(readBuff[loopv]);
      Serial.println("");
      Serial.print("Product=");
      int loopv = 64;
      do
      {
        Serial.print(readBuff[loopv++]);
      }
      while ((readBuff[loopv] != 0) && (loopv < 128));
      Serial.println("");
    }
    else if ((incomingByte == 'W') || (incomingByte == 'w'))
    {
      Serial.println("Writing EEPROM");
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
      myEep.pid = 0x02;
      myEep.vslen = 32;
      myEep.pslen = 32;
      strcpy(myEep.vstr, "land-boards.com");
      strcpy(myEep.pstr, "DIGIO128");

      Serial.print("len of buffer=");
      Serial.println(sizeof(myEep));

      eeprom.writeBlock(0, (const uint8_t*) myEep.signature, 96);
      Serial.println("reading block");
      delay(10);

      eeprom.readBlock((const uint16_t) 0, (unsigned char*) readBuff, (const uint16_t) 96);

      Serial.print("Family=");
      for (int loopv = 0; loopv < 4; loopv++)
        Serial.print(readBuff[loopv]);
      Serial.println("");
      Serial.print("Company=");
      for (int loopv = 32; loopv < 48; loopv++)
        Serial.print(readBuff[loopv]);
      Serial.println("");
      Serial.print("Product=");
      int loopv = 64;
      do
      {
        Serial.print(readBuff[loopv++]);
      }
      while ((readBuff[loopv] != 0) && (loopv < 128));
      Serial.println("");
    }
    else if ((incomingByte == 'T') || (incomingByte == 't'))
    {
      if (loopBackTest() == 0)
        passCount++;
      else
        failCount++;

      Serial.print("Loopback Test PASS = ");
      Serial.print(passCount);
      Serial.print(", FAIL = ");
      Serial.println(failCount);
    }
    else if ((incomingByte == 'L') || (incomingByte == 'l'))
    {
      looping = 1;
    }
    else
      looping = 0;
  }
  if (looping == 1)
  {
    if (loopBackTest() == 0)
      passCount++;
    else
      failCount++;

    Serial.print("Loopback Test PASS = ");
    Serial.print(passCount);
    Serial.print(", FAIL = ");
    Serial.println(failCount);
  }
}

uint8_t loopBackTest(void)
{
  uint8_t chip;
  uint8_t port;
  uint8_t pass0fail1 = 0;
  for (chip = 0; chip < 8; chip += 2)
  {
    for (port = 0; port < 16; port++)
    {
      mcpPinMode(chip, port, OUTPUT);
      mcpPinMode(chip + 1, 15 - port, INPUT);

      delay(1);
      mcpWrite(chip, port, HIGH);
      delay(1);
      if (mcpRead(chip + 1, 15 - port) != HIGH)
      {
        Serial.print("Error on chip ");
        Serial.print(chip);
        Serial.print(" and port ");
        Serial.print(port);
        Serial.println(" Expected High");
        pass0fail1 = 1;
      }
      mcpWrite(chip, port, LOW);
      delay(1);
      if (mcpRead(chip + 1, 15 - port) != LOW)
      {
        Serial.print("Error on chip ");
        Serial.print(chip);
        Serial.print(" and port ");
        Serial.print(port);
        Serial.println(" Expected LOW");
        pass0fail1 = 1;
      }
      mcpPinMode(chip, port, INPUT);
      delay(1);
    }
    return pass0fail1;
  }
}

/* mcpWrite(chipNum, chNum, val)
  Write a value to a pin.
  chipNum is from 0-7
  chNum is from 0-15
  val is LOW or HIGH
*/
void mcpWrite(uint8_t chipNum, uint8_t chNum, uint8_t val)
{
  switch (chipNum)
  {
    case 0:
      mcp0.digitalWrite(chNum, val);
      break;
    case 1:
      mcp1.digitalWrite(chNum, val);
      break;
    case 2:
      mcp2.digitalWrite(chNum, val);
      break;
    case 3:
      mcp3.digitalWrite(chNum, val);
      break;
    case 4:
      mcp4.digitalWrite(chNum, val);
      break;
    case 5:
      mcp5.digitalWrite(chNum, val);
      break;
    case 6:
      mcp6.digitalWrite(chNum, val);
      break;
    case 7:
      mcp7.digitalWrite(chNum, val);
      break;
  }
}

/* mcpPinMode(chipNum, chNum, val)
  Set the pin to be an input or output.
  chipNum is from 0-7
  chNum is from 0-15
  val is INPUT or OUTPUT
*/
void mcpPinMode(uint8_t chipNum, uint8_t chNum, uint8_t val)
{
  switch (chipNum)
  {
    case 0:
      mcp0.pinMode(chNum, val);
      break;
    case 1:
      mcp1.pinMode(chNum, val);
      break;
    case 2:
      mcp2.pinMode(chNum, val);
      break;
    case 3:
      mcp3.pinMode(chNum, val);
      break;
    case 4:
      mcp4.pinMode(chNum, val);
      break;
    case 5:
      mcp5.pinMode(chNum, val);
      break;
    case 6:
      mcp6.pinMode(chNum, val);
      break;
    case 7:
      mcp7.pinMode(chNum, val);
      break;
  }
}

/* mcpPullUp(chipNum, chNum, val)
  Set the pull up for a channel.
  chipNum is from 0-7
  chNum is from 0-15
  val is HIGH to turn on pull up and LOW to turn off pullup
*/
void mcpPullUp(uint8_t chipNum, uint8_t chNum, uint8_t val)
{
  switch (chipNum)
  {
    case 0:
      mcp0.pullUp(chNum, val);
      break;
    case 1:
      mcp1.pullUp(chNum, val);
      break;
    case 2:
      mcp2.pullUp(chNum, val);
      break;
    case 3:
      mcp3.pullUp(chNum, val);
      break;
    case 4:
      mcp4.pullUp(chNum, val);
      break;
    case 5:
      mcp5.pullUp(chNum, val);
      break;
    case 6:
      mcp6.pullUp(chNum, val);
      break;
    case 7:
      mcp7.pullUp(chNum, val);
      break;
  }
}

/* mcpRead(chipNum, chNum)
  Reads a channel.
  chipNum is from 0-7
  chNum is from 0-15
  Returns the value of the pin
*/
uint8_t mcpRead(uint8_t chipNum, uint8_t chNum)
{
  switch (chipNum)
  {
    case 0:
      return (mcp0.digitalRead(chNum));
      break;
    case 1:
      return (mcp1.digitalRead(chNum));
      break;
    case 2:
      return (mcp2.digitalRead(chNum));
      break;
    case 3:
      return (mcp3.digitalRead(chNum));
      break;
    case 4:
      return (mcp4.digitalRead(chNum));
      break;
    case 5:
      return (mcp5.digitalRead(chNum));
      break;
    case 6:
      return (mcp6.digitalRead(chNum));
      break;
    case 7:
      return (mcp7.digitalRead(chNum));
      break;
  }
}

