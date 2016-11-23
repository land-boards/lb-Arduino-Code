//////////////////////////////////////////////////////////
// DIGIO32-I2C Factory Test code
// Test each channel
// Read/write EEPROM
//////////////////////////////////////////////////////////

#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include <I2C_eeprom.h>

//////////////////////////////////////////////////////////
// defines follow

#define EE24LC024MAXBYTES 2048/8

// EEPROM base address
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

uint32_t failCount;
uint32_t passCount;
int looping;

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

//////////////////////////////////////////////////////////
// setup()
//////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(9600);
  mcp0.begin(0);
  mcp1.begin(1);
  //  TWBR = 12;    // go to 400 KHz I2C speed mode

  for (uint8_t chip = 0; chip < 2; chip++)
  {
    for (uint8_t port = 0; port < 16; port++)
    {
      mcpPullUp(chip, port, HIGH);
      mcpPinMode(chip, port, INPUT);
    }
  }
  failCount = 0;
  passCount = 0;
  looping = 0;
  Serial.print("Running loopback test...");
  if (loopBackTest() != 0)
    Serial.println("Failed loopback test");
  else
    Serial.println("Passed loopback test");
  if (eepromCheck() != 0)
  {
    Serial.println("Failed eeprom check test");
    Serial.println("Writing EEPROM");
    eepromWrite();
    if (eepromCheck() != 0)
    {
      Serial.println("Failed eeprom check test");
    }
  }
  else
    Serial.println("Passed eeprom check test");
  Serial.println("R=Read EEPROM, W=Write EEPROM, T=Test DIGIOs, L=Loop Test");
}

//////////////////////////////////////////////////////////
// loop()
//////////////////////////////////////////////////////////

void loop()
{
  int incomingByte = 0;   // for incoming serial data
  if (Serial.available() > 0)
  {
    // read the incoming byte:
    incomingByte = Serial.read();
    if ((incomingByte == 'R') || (incomingByte == 'r'))
    {
      eepromRead();
    }
    else if ((incomingByte == 'W') || (incomingByte == 'w'))
    {
      eepromWrite();
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
    else if ((incomingByte == 'B') || (incomingByte == 'b'))
    {
      while (Serial.available() == 0)
      {
        for (uint8_t port = 0; port < 16; port++)
        {
          mcpPinMode(0, port, OUTPUT);
          mcpWrite(0, port, HIGH);
          delay(2);
          mcpWrite(0, port, LOW);
          delay(2);
        }
        for (uint8_t port = 0; port < 16; port++)
        {
          mcpPinMode(1, port, OUTPUT);
          mcpWrite(1, port, HIGH);
          delay(2);
          mcpWrite(1, port, LOW);
          delay(2);
        }
      }
    }
    else
    {
      if (looping == 1)
        looping = 0;
      else
        Serial.println("Unrecognized command");
      Serial.println("\nR=Read EEPROM, W=Write EEPROM, T=Test DIGIOs, L=Loop Test");
    }
  }

  while (Serial.available() > 0)
    Serial.read();

  while ((looping == 1) && (Serial.available() == 0))
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
  }
}

/*
  uint8_t loopBackTest()
*/

uint8_t loopBackTest(void)
{
  uint8_t port;
  uint8_t pass0fail1 = 0;

  for (port = 0; port < 16; port++)
  {
    mcpPinMode(0, port, OUTPUT);
    mcpPinMode(1, port, INPUT);
    mcpPullUp(1, port, HIGH);

    delay(2);
    mcpWrite(0, port, HIGH);
    delay(2);
    if (mcpRead(1, port) != HIGH)
    {
      Serial.print("Error on chip 0");
      Serial.print(" and port ");
      Serial.print(port);
      Serial.println(" Expected High");
      pass0fail1 = 1;
    }
    mcpWrite(0, port, LOW);
    delay(2);
    if (mcpRead(1, port) != LOW)
    {
      Serial.print("Error on chip 0");
      Serial.print(" and port ");
      Serial.print(port);
      Serial.println(" Expected LOW");
      pass0fail1 = 1;
    }
    mcpPinMode(0, port, INPUT);
    delay(2);
  }

  return pass0fail1;
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
  }
}

//////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////

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
  }
}

//////////////////////////////////////////////////////////
// void eepromRead(void)
//////////////////////////////////////////////////////////

void eepromRead(void)
{
  char readBuff[97];
  readBuff[96] = 0;
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

//////////////////////////////////////////////////////////
// void eepromCheck(void)
//////////////////////////////////////////////////////////

uint8_t eepromCheck(void)
{
  char testStr[33];
  char readBuff[97];
  readBuff[96] = 0;
  Serial.print("Checking EEPROM...");

  eeprom.readBlock((const uint16_t) 0, (unsigned char*) readBuff, (const uint16_t) 96);

  //  Serial.print("Testing Family...");
  for (int loopv = 0; loopv < 4; loopv++)
  {
    testStr[loopv] = readBuff[loopv];
  }
  testStr[4] = 0;
  if (strcmp(testStr, "ODAS") != 0)
  {
    //    Serial.println("Family Mismatch");
    return 1;
  }
  //  else
  //    Serial.println("Family match");
  //  Serial.print("Testing Company...");
  for (int loopv = 32; loopv < 48; loopv++)
    testStr[loopv - 32] = readBuff[loopv];
  testStr[33] = 0;
  if (strcmp(testStr, "land-boards.com") != 0)
  {
    //    Serial.println("Company Mismatch");
    return 1;
  }
  //  else
  //    Serial.println("Company match");
  //  Serial.print("Testing Product ID...");
  int loopv = 64;
  do
  {
    testStr[loopv - 64] = readBuff[loopv];
    loopv++;
  }
  while ((readBuff[loopv] != 0) && (loopv < 128));
  testStr[loopv - 64] = 0;
  if (strcmp(testStr, "DIGIO32-I2C") != 0)
  {
    //    Serial.println(testStr);
    //    Serial.println("ProductID Mismatch");
    return 1;
  }
  //  else
  //    Serial.println("Match");
  return 0;
}

//////////////////////////////////////////////////////////
// eepromWrite()
//////////////////////////////////////////////////////////

void eepromWrite(void)
{
  char readBuff[97];
  readBuff[96] = 0;
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
  strcpy(myEep.pstr, "DIGIO32-I2C");

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


