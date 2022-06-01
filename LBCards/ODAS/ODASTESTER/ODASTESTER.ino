//////////////////////////////////////////////////////////
// ODASTESTER - Land Boards LLC Factory Test code
//    http://land-boards.com/blwiki/index.php?title=Arduino_Based_Test_Station
// Test each Land Boards LLC card that can be tested
// Read/write EEPROM if there is one
// Auto-detect card types
//////////////////////////////////////////////////////////
// Hardware
//  Black Pill Hub card
//    http://land-boards.com/blwiki/index.php?title=BLACK-PILL-HUB
//  DIGIO32-I2C 32 bit I2C card
//    http://land-boards.com/blwiki/index.php?title=DIGIO32-I2C
//  LED-32 card
//    http://land-boards.com/blwiki/index.php?title=LED-32
//  Card specific cable sets
//  DB25 and DB37 ribbin cable adapters
//    http://land-boards.com/blwiki/index.php?title=DB37RIBBON
//    http://land-boards.com/blwiki/index.php?title=DB25RIBBON
//////////////////////////////////////////////////////////
// Serial USB connection
//  Running puTTY
//  9600 baud
//////////////////////////////////////////////////////////

#include <LandBoards_DIGIO32I2C.h>
#include <LandBoards_Digio128V2.h>
#include <LandBoards_Digio128_64.h>
#include <LandBoards_I2CIO8.h>
#include <LandBoards_I2CIO8X.h>
#include <LandBoards_I2CTEMP01.h>
#include <LandBoards_I2CRPT01.h>
#include <LandBoards_I2CRPT08.h>
#include <LandBoards_MCP23017.h>
#include <LandBoards_MCP23008.h>

//////////////////////////////////////////////////////////
// defines follow

#define SERIAL_DEBUG Serial

typedef enum {
  NONE,
  DIGIO16I2C_CARD = 1,
  DIGIO128_CARD,    // 2
  DIGIO128_64_CARD, // 3
  OPTOIN8I2C_CARD,  // 4
  OPTOOUT8I2C_CARD, // 5
  DIGIO32I2C_CARD,  // 6
  PROTO16I2C_CARD,  // 7
  ODASPSOC5_CARD,   // 8
  ODASRELAY16_CARD, // 9
  NEW_CARD = 127,
  NOEEPROMAFTER = 128,
  I2CIO8_CARD,
  I2CIO8X_CARD,
  OPTOFST_SML_NON_INVERTING_CARD,
  OPTOFST_SML_INVERTING_CARD,
  OPTOFSTBI_CARD,
  I2CRPT01_CARD,
  I2CRPT08_CARD,
  SWLEDX8_I2C_CARD,
  UNKNOWN_BOARD,
} boardType_t;

enum {TEST_PASSED, TEST_FAILED};

//////////////////////////////////////////////////////////
// globals follow

boardType_t boardType;

uint32_t failCount;
uint32_t passCount;
uint8_t single0loop1;

typedef enum {
  UUT_CARD_MUX_CH = 0x04,
  TEST_STN_INT_MUX_CH = 0x07,
  NO_MUX_CH = 0x00,
} muxChannel_t;

LandBoards_I2CRPT01 ODASTSTR_I2CMux;
LandBoards_Digio128V2 Dio128;    // Call the class constructor for the DigIO32_I2C card
LandBoards_Digio128_64 Dio128_64;    // Call the class constructor for the DigIO-128 card
LandBoards_DIGIO32I2C IntDio32;
LandBoards_DIGIO32I2C ExtDio32;
LandBoards_I2CIO8 i2cio8Card;
LandBoards_I2CIO8 i2cio8Card1;
LandBoards_I2CIO8 i2cio8Card2;
LandBoards_I2CIO8 i2cio8Card3;
LandBoards_I2CIO8 i2cio8Card4;
LandBoards_I2CIO8 i2cio8Card5;
LandBoards_I2CIO8 i2cio8Card6;
LandBoards_I2CIO8 i2cio8Card7;
LandBoards_I2CIO8 i2cio8Card8;
LandBoards_I2CIO8X i2cio8xCard;
LandBoards_MCP23008 singleMCP23008;
LandBoards_MCP23017 singleMCP23017;
LandBoards_I2CRPT01 UUTI2CMux4Ch;
LandBoards_I2CRPT08 UUTI2CMux8Ch;

//////////////////////////////////////////////////////////
// setup()
//////////////////////////////////////////////////////////

void setup()
{
  // Flags
  uint8_t boardTypeEEPROM;    // EEPROM status state
  uint8_t i2cDevCount;        // Count of I2C devices in range 0x20-0x27
  uint8_t isMCP23017;         // Is the device at 0x20 an MCP23017?
  uint8_t isMuxCard;

  // Set USB-Serial port to 9600 baud
  Serial.begin(9600);
  while (!Serial);    // wait for serial port to connect. Needed for native USB

  // Initialize the I2C mux on the BLACK-PILL-HUN card
  // I2C Slave address = 0x71
  ODASTSTR_I2CMux.begin(1);

  // Initialize the internal DIGIO32-I2C card
  // I2C Slave address = 0x20
  ODASTSTR_I2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
  IntDio32.begin(0);

  // Global variables
  failCount = 0;
  passCount = 0;
  single0loop1 = 0;
  boardType = NEW_CARD;   // Assume new card until proven otherwise

  ODASTSTR_I2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  // EEPROM Detection
  // If the UUT EEPROM was already set up, use the information to setup card
  //  0 : Board has an already programmed EEPROM
  //  1 : Board has an unprogrammed EEPROM
  //  2 : Board does not have an EEPROM
  boardTypeEEPROM = boardEEPROMStatus();
  i2cDevCount = count0x20_I2CDevices();
  if (checkI2CAddr(0x70) == 0x0)
  {
    isMuxCard = 1;
    Serial.println("Found external I2C mux card");
  }
  else
  {
    Serial.println("No external I2C mux card");
    isMuxCard = 0;
  }

  // For boards with EEPROMs
  // Validate number of I2C devices match
  if (boardTypeEEPROM == 0)
  {
    switch (boardType)
    {
      case DIGIO16I2C_CARD:
      case PROTO16I2C_CARD:
      case ODASRELAY16_CARD:
        if (i2cDevCount != 1)
          Serial.print("ERROR - Mismatch I2C device count, expected 1, got ");
        Serial.println(i2cDevCount, DEC);
        break;
      case DIGIO32I2C_CARD:
        if (i2cDevCount != 2)
          Serial.print("ERROR - Mismatch I2C device count, expected 2, got ");
        Serial.println(i2cDevCount, DEC);
        break;
      case DIGIO128_64_CARD:
        if (i2cDevCount != 4)
          Serial.print("ERROR - Mismatch I2C device count, expected 4, got ");
        Serial.println(i2cDevCount, DEC);
        break;
      case DIGIO128_CARD:
        if (i2cDevCount != 8)
          Serial.print("ERROR - Mismatch I2C device count, expected 8, got ");
        Serial.println(i2cDevCount, DEC);
        break;
    }
  }
  // Board has unprogrammed EEPROM
  // Count the number of MCP230xx devices
  // Used to pre-select board choice
  else if (boardTypeEEPROM == 1)
  {
    if (i2cDevCount > 0)
      isMCP23017 = checkIfMCP23017(0x20);
    else
      isMCP23017 = 0;
    selectBoardType(i2cDevCount, isMCP23017);
    eepromWrite();
  }
  // Board does not have an EEPROM
  // Count the number I2C deices
  // If there are I2C devices, detect if there are MCP23017 devices
  else if ((boardTypeEEPROM == 2) && (isMuxCard == 0))
  {
    if (i2cDevCount > 0)
      isMCP23017 = checkIfMCP23017(0x20);
    else
      isMCP23017 = 0;
    otherBoardType(i2cDevCount, isMCP23017);
  }
  else if ((boardTypeEEPROM == 2) && (isMuxCard == 1))
  {
    selectMuxBoardType();
  }
  beginUUTDevice();
  Serial.println(F("C=Card Tests, D=Direct, E=EEPROM, I=access Internal DIGIO32"));
}

//////////////////////////////////////////////////////////
//  void beginUUTDevice(void)
//  Globals
//    boardType_t boardType
//////////////////////////////////////////////////////////

void beginUUTDevice(void)
{
  ODASTSTR_I2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  switch (boardType)    // Instantiate the classes here for the boards
  {
    case PROTO16I2C_CARD:
    case ODASRELAY16_CARD:
    case SWLEDX8_I2C_CARD:
      singleMCP23017.begin(0);
      break;
    case OPTOIN8I2C_CARD:
    case OPTOOUT8I2C_CARD:
      singleMCP23008.begin();               // use default address 0
      break;
    case DIGIO128_CARD:
      Dio128.begin();
      break;
    case DIGIO128_64_CARD:
      Dio128_64.begin();
      break;
    case DIGIO32I2C_CARD:
      ExtDio32.begin(0);
      break;
    case I2CIO8_CARD:
      Serial.println(F("Init I2CIO-8 card"));
      i2cio8Card.begin(0);
      break;
    case I2CIO8X_CARD:
      Serial.println(F("Init I2CIO-8X card"));
      i2cio8xCard.begin(0);
      break;
    case I2CRPT01_CARD:       // testing external I2C-RPT-01 card
      Serial.println(F("Init I2C-RPT-01 card"));
      // Set interbal mux off
      ODASTSTR_I2CMux.setI2CChannel(NO_MUX_CH);
      // Start up the external I2C mux
      UUTI2CMux4Ch.begin(0);                 
      // Requires (4) I2CIO8 cards connected to external I2C-RPT-01 card
      UUTI2CMux4Ch.setI2CChannel(I2CRPT01_CH0);
      if (checkI2CAddr(0x20) != 0)
        Serial.println(F("I2CIO8 card #0 not detected"));
      else
      {
        Serial.println(F("I2CIO8 card #0 was detected"));
        i2cio8Card1.begin(0);
      }
      UUTI2CMux4Ch.setI2CChannel(I2CRPT01_CH1);
      if (checkI2CAddr(0x20) != 0)
         Serial.println(F("I2CIO8 card #1 not detected"));
      else
      {
        Serial.println(F("I2CIO8 card #1 was detected"));
        i2cio8Card2.begin(0);
      }
      UUTI2CMux4Ch.setI2CChannel(I2CRPT01_CH2);
      if (checkI2CAddr(0x20) != 0)
         Serial.println(F("I2CIO8 card #2 not detected"));
      else
      {
        Serial.println(F("I2CIO8 card #2 was detected"));
        i2cio8Card3.begin(0);
      }
      UUTI2CMux4Ch.setI2CChannel(I2CRPT01_CH3);
      if (checkI2CAddr(0x20) != 0)
         Serial.println(F("I2CIO8 card #3 not detected"));
      else
      {
        Serial.println(F("I2CIO8 card #3 was detected"));
        i2cio8Card4.begin(0);
      }
      break;
    case I2CRPT08_CARD:
      ODASTSTR_I2CMux.setI2CChannel(NO_MUX_CH);
      UUTI2CMux8Ch.begin(0);                   // testing external I2C-RPT-01 card
      UUTI2CMux8Ch.setI2CChannel(0, 1);
      if (checkI2CAddr(0x20) != 0)
        Serial.println(F("I2CIO8 card #0 not detected"));
      else
      {
        Serial.println(F("I2CIO8 card #0 was detected"));
        i2cio8Card1.begin(0);
      }
      UUTI2CMux8Ch.setI2CChannel(0, 0);
      UUTI2CMux8Ch.setI2CChannel(1, 1);
      if (checkI2CAddr(0x20) != 0)
        Serial.println(F("I2CIO8 card #1 not detected"));
      else
      {
        Serial.println(F("I2CIO8 card #1 was detected"));
        i2cio8Card2.begin(0);
      }
      UUTI2CMux8Ch.setI2CChannel(1, 0);
      UUTI2CMux8Ch.setI2CChannel(2, 1);
      if (checkI2CAddr(0x20) != 0)
        Serial.println(F("I2CIO8 card #2 not detected"));
      else
      {
        Serial.println(F("I2CIO8 card #2 was detected"));
        i2cio8Card3.begin(0);
      }
      UUTI2CMux8Ch.setI2CChannel(2, 0);
      UUTI2CMux8Ch.setI2CChannel(3, 1);
      if (checkI2CAddr(0x20) != 0)
        Serial.println(F("I2CIO8 card #3 not detected"));
      else
      {
        Serial.println(F("I2CIO8 card #3 was detected"));
        i2cio8Card4.begin(0);
      }
      UUTI2CMux8Ch.setI2CChannel(3, 0);
      UUTI2CMux8Ch.setI2CChannel(4, 1);
      if (checkI2CAddr(0x20) != 0)
        Serial.println(F("I2CIO8 card #4 not detected"));
      else
      {
        Serial.println(F("I2CIO8 card #4 was detected"));
        i2cio8Card5.begin(0);
      }
      UUTI2CMux8Ch.setI2CChannel(4, 0);
      UUTI2CMux8Ch.setI2CChannel(5, 1);
      if (checkI2CAddr(0x20) != 0)
        Serial.println(F("I2CIO8 card #5 not detected"));
      else
      {
        Serial.println(F("I2CIO8 card #5 was detected"));
        i2cio8Card6.begin(0);
      }
      UUTI2CMux8Ch.setI2CChannel(5, 0);
      UUTI2CMux8Ch.setI2CChannel(6, 1);
      if (checkI2CAddr(0x20) != 0)
        Serial.println(F("I2CIO8 card #6 not detected"));
      else
      {
        Serial.println(F("I2CIO8 card #6 was detected"));
        i2cio8Card7.begin(0);
      }
      UUTI2CMux8Ch.setI2CChannel(6, 0);
      UUTI2CMux8Ch.setI2CChannel(7, 1);
      if (checkI2CAddr(0x20) != 0)
        Serial.println(F("I2CIO8 card #7 not detected"));
      else
      {
        Serial.println(F("I2CIO8 card #7 was detected"));
        i2cio8Card8.begin(0);
      }
      UUTI2CMux8Ch.setI2CChannel(7, 0);
      break;
  }
}

//////////////////////////////////////////////////////////
// loop()
//////////////////////////////////////////////////////////

void loop()
{
  while (1)
  {
    topLevelMenu();
  }
}
