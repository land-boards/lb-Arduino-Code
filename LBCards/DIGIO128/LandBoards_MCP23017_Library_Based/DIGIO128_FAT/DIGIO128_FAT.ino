//////////////////////////////////////////////////////////
// DIGIO128_FAT Factory Acceptance Tests
// Loopback code
// Test each channel
// Read/write EEPROM
//////////////////////////////////////////////////////////

#include "I2C_eeprom.h"
#include "LandBoards_MCP23017.h"

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

LandBoards_MCP23017 mcp0;
LandBoards_MCP23017 mcp1;
LandBoards_MCP23017 mcp2;
LandBoards_MCP23017 mcp3;
LandBoards_MCP23017 mcp4;
LandBoards_MCP23017 mcp5;
LandBoards_MCP23017 mcp6;
LandBoards_MCP23017 mcp7;

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
#if defined(ARDUINO_ARCH_AVR)
  TWBR = 12;          // go to 400 KHz I2C speed mode
#elif defined(ARDUINO_ARCH_STM32F1)
  Wire.setClock(400000);  // 400KHz speed
#else
  #error “This library only supports boards with an AVR or SAM processor.”
#endif

  for (uint8_t chip = 0; chip < 8; chip++)
  {
    for (uint8_t port = 0; port < 16; port++)
    {
      mcpPinMode(chip, port, INPUT_PULLUP);
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
      mcpPinMode(chip + 1, 15 - port,INPUT);
      
      delay(2);
      mcpWrite(chip, port, HIGH);
      delay(2);
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
      delay(2);
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
      delay(2);
    }
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
      return(mcp0.digitalRead(chNum));
      break;
    case 1:
      return(mcp1.digitalRead(chNum));
      break;
    case 2:
      return(mcp2.digitalRead(chNum));
      break;
    case 3:
      return(mcp3.digitalRead(chNum));
      break;
    case 4:
      return(mcp4.digitalRead(chNum));
      break;
    case 5:
      return(mcp5.digitalRead(chNum));
      break;
    case 6:
      return(mcp6.digitalRead(chNum));
      break;
    case 7:
      return(mcp7.digitalRead(chNum));
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
  if (strcmp(testStr, "DIGIO-128") != 0)
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
  strcpy(myEep.pstr, "DIGIO-128");

  Serial.print("len of buffer=");
  Serial.println(sizeof(myEep));

  eeprom.writeBlock(0, (uint8_t*) myEep.signature, 96);
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
