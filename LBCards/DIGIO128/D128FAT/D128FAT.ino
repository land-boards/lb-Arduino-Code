//////////////////////////////////////////////////////////
// DIGIO-128 Loopback code
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
Adafruit_MCP23017 mcp2;
Adafruit_MCP23017 mcp3;
Adafruit_MCP23017 mcp4;
Adafruit_MCP23017 mcp5;
Adafruit_MCP23017 mcp6;
Adafruit_MCP23017 mcp7;

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
  mcp2.begin(2);
  mcp3.begin(3);
  mcp4.begin(4);
  mcp5.begin(5);
  mcp6.begin(6);
  mcp7.begin(7);
  TWBR = 12;    // go to 400 KHz I2C speed mode

  for (uint8_t chip = 0; chip < 8; chip++)
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
    else
    {
      if (looping == 1)
        looping = 0;
      else
        Serial.println("Unrecognized command");
      Serial.println("\nR=Read EEPROM, W=Write EEPROM, T=Test DIGIOs, L=Loop Test");
    }
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

