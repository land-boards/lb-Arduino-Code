#include <I2C_eeprom.h>

#define EE24LC024MAXBYTES 2048/8

// EEPROM base address
#define DEVICEADDRESS (0x50)

#define TEST_ADDR 100

// this must start on a page boundary!
#define TEST_PAGE_ADDR 0
#define SHORT_BUFFER_LEN 4

// this tests multi-page writes
#define LONG_BUFFER_LEN 64
// make sure it's aligned on a page boundary
#define LONG_TEST_PAGE_ADDR (max(16, TEST_PAGE_ADDR + SHORT_BUFFER_LEN))

I2C_eeprom eeprom(DEVICEADDRESS, EE24LC024MAXBYTES);

struct eep_vals
{
  char signature[4]; // "ODAS" in ASCII
  byte fmt_version;  // EEPROM data format version (0x00 reserved, 0x01 = first version)
  byte rsvd;         // set to 0
  short numatoms;    // set to 2
  long eeplen;       // set to 96 dec
  char uuid[16];     // "0000000000000000" in ASCII
  short pid;         // See PID table
  char vslen;        // set to 32 dec
  char pslen;        // set to 32 dec
  char vstr[32];     // Vendor Null terminated String
  char pstr[32];     // Product Null terminated String
};

//////////////////////////////////////////////////////////
// void eepromRead(void)
//////////////////////////////////////////////////////////

void eepromRead(void)
{
  char readBuff[97];
  ODASTSTR_I2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  eeprom.begin();
  //  Serial.println(F("Reading EEPROM"));
  delay(10);

  eeprom.readBlock((const uint16_t) 0, (unsigned char*) readBuff, (const uint16_t) 96);
  readBuff[96] = 0;

  Serial.print(F("Family  = "));
  for (int loopv = 0; loopv < 4; loopv++)
    Serial.print(readBuff[loopv]);
  Serial.println("");
  Serial.print(F("Company = "));
  for (int loopv = 32; loopv < 48; loopv++)
    Serial.print(readBuff[loopv]);
  Serial.println("");
  Serial.print(F("Product = "));
  int loopv = 64;
  do
  {
    Serial.print(readBuff[loopv++]);
  }
  while ((readBuff[loopv] != 0) && (loopv < 128));
  //  Serial.println("\n\rDone reading EPROM");
}

//////////////////////////////////////////////////////////
// eepromWrite()
// Globals:
//    boardType
//////////////////////////////////////////////////////////

void eepromWrite(void)
{
  char readBuff[97];
  ODASTSTR_I2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  if (boardType > NOEEPROMAFTER)
  {
    Serial.println("No EEPROM on this board");
    return;
  }
  readBuff[96] = 0;
  Serial.println(F("Writing EEPROM"));
  eeprom.begin();
  eep_vals myEep;

  Serial.println(F("Initializing eep buffer"));
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
  myEep.pid = boardType;
  myEep.vslen = 32;
  myEep.pslen = 32;
  strcpy(myEep.vstr, "land-boards.com");
  switch (boardType)
  {
    case DIGIO16I2C_CARD:
      strcpy(myEep.pstr, "DIGIO16-I2C");
      break;
    case DIGIO128_CARD:
      strcpy(myEep.pstr, "DIGIO-128");
      break;
    case DIGIO128_64_CARD:
      strcpy(myEep.pstr, "DIGIO-128/64");
      break;
    case OPTOIN8I2C_CARD:
      strcpy(myEep.pstr, "OptoIn8-I2C");
      break;
    case OPTOOUT8I2C_CARD:
      strcpy(myEep.pstr, "OptoOut8-I2C");
      break;
    case DIGIO32I2C_CARD:
      strcpy(myEep.pstr, "DIGIO32-I2C");
      break;
    case PROTO16I2C_CARD:
      strcpy(myEep.pstr, "PROTO16-I2C");
      break;
    case ODASPSOC5_CARD:
      strcpy(myEep.pstr, "ODAS-PSOC5");
      break;
    case ODASRELAY16_CARD:
      strcpy(myEep.pstr, "ODAS-RELAY16");
      break;
    case NEW_CARD:
      strcpy(myEep.pstr, "TBD");
      break;
  }
  Serial.print(F("len of buffer="));
  Serial.println(sizeof(myEep));

  eeprom.writeBlock(0, (uint8_t*) myEep.signature, 96);
  Serial.println(F("reading block"));
  delay(10);

  eeprom.readBlock((const uint16_t) 0, (unsigned char*) readBuff, (const uint16_t) 96);

  Serial.print(F("Family="));
  for (int loopv = 0; loopv < 4; loopv++)
    Serial.print(readBuff[loopv]);
  Serial.println("");
  Serial.print(F("Company="));
  for (int loopv = 32; loopv < 48; loopv++)
    Serial.print(readBuff[loopv]);
  Serial.println("");
  Serial.print(F("Product="));
  int loopv = 64;
  do
  {
    Serial.print(readBuff[loopv++]);
  }
  while ((readBuff[loopv] != 0) && (loopv < 128));
  Serial.println("");
}

//////////////////////////////////////////////////////////
//  uint8_t detectBoardInEeprom(void)
//    Detect the board type
//    If the board has an EEPROM that is already programmed
//  Globals
//    boardType variable set to match
//  Returns
//    0 : Board has an already programmed EEPROM
//    1 : Board has an unprogrammed EEPROM
//    2 : Board does not have an EEPROM
//////////////////////////////////////////////////////////

uint8_t detectBoardInEeprom(void)
{
  char testStr[66];
  char readBuff[97];
  ODASTSTR_I2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  Serial.print(F("Checking if EEPROM is present on UUT..."));
  if (checkI2CAddr(0x50) != 0)
  {
    Serial.println(F("EEPROM is not present on UUT"));
    return 2;
  }
  else
    Serial.println(F("EEPROM is present on UUT"));
  eeprom.begin();
  Serial.print(F("Checking EEPROM for board type..."));
  delay(10);
  eeprom.readBlock((const uint16_t) 0, (unsigned char*) &readBuff[0], (const uint16_t) 96);
  readBuff[96] = 0;

  //  Serial.print("Testing Family...");
  for (int loopv = 0; loopv < 4; loopv++)
  {
    testStr[loopv] = readBuff[loopv];
  }
  testStr[4] = 0;
  if (strcmp(testStr, "ODAS") != 0)
  {
    Serial.println(F("Board signature error in EEPROM on UUT"));
    //    Serial.print(F("Expected ODAS, got "));
    //    Serial.println((char*)testStr);
    //    for (int loopv = 0; loopv < 4; loopv++)
    //      Serial.print(readBuff[loopv]);
    return 1;
  }
  for (int loopv = 32; loopv < 48; loopv++)
    testStr[loopv - 32] = readBuff[loopv];
  testStr[16] = 0;
  if (strcmp(testStr, "land-boards.com") != 0)
  {
    Serial.println(F("Company Mismatch"));
    return 1;
  }
  int loopv = 64;
  do
  {
    testStr[loopv - 64] = readBuff[loopv];
    loopv++;
  }
  while ((readBuff[loopv] != 0) && (loopv < 128));
  testStr[loopv - 64] = 0;
  if (strcmp(testStr, "DIGIO32-I2C") == 0)
  {
    boardType = DIGIO32I2C_CARD;
    Serial.println(F("Detected DIGIO32-I2C board"));
    return 0;
  }
  else if (strcmp(testStr, "DIGIO16-I2C") == 0)
  {
    boardType = DIGIO16I2C_CARD;
    Serial.println(F("Detected DIGIO16-I2C board"));
    return 0;
  }
  else if (strcmp(testStr, "OptoIn8-I2C") == 0)
  {
    boardType = OPTOIN8I2C_CARD;
    Serial.println(F("Detected OptoIn8-I2C board"));
    return 0;
  }
  else if (strcmp(testStr, "OptoOut8-I2C") == 0)
  {
    boardType = OPTOOUT8I2C_CARD;
    Serial.println(F("Detected OptoOut8-I2C board"));
    return 0;
  }
  else if (strcmp(testStr, "DIGIO-128") == 0)
  {
    boardType = DIGIO128_CARD;
    Serial.println(F("Detected DIGIO-128 board"));
    return 0;
  }
  else if (strcmp(testStr, "DIGIO-128/64") == 0)
  {
    boardType = DIGIO128_64_CARD;
    Serial.println(F("Detected DIGIO-128/64 board"));
    return 0;
  }
  else if (strcmp(testStr, "PROTO16-I2C") == 0)
  {
    boardType = PROTO16I2C_CARD;
    Serial.println(F("Detected PROTO16-I2C board"));
    return 0;
  }
  else if (strcmp(testStr, "ODAS-PSOC5") == 0)
  {
    boardType = ODASPSOC5_CARD;
    Serial.println(F("Detected ODAS-PSOC5 board"));
    return 0;
  }
  else if (strcmp(testStr, "ODAS-RELAY16") == 0)
  {
    boardType = ODASRELAY16_CARD;
    Serial.println(F("Detected ODAS-RELAY16 board"));
    return 0;
  }
  Serial.print(F("Did not find board match"));
  Serial.println((char*)testStr);
  return 1;
}
