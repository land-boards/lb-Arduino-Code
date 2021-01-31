//////////////////////////////////////////////////////////
// ODASTESTER Factory Test code
// Test each card and channel
// Read/write EEPROM if there is one
//////////////////////////////////////////////////////////
// Tester Hardware
//  Blue Pill Hub card
//    http://land-boards.com/blwiki/index.php?title=Blue_Pill_Hub
//  DIGIO32-I2C 32 bit I2C card
//    http://land-boards.com/blwiki/index.php?title=DIGIO32-I2C
//  LED-32 card
//    http://land-boards.com/blwiki/index.php?title=LED-32
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

// enumerated card types
typedef enum {
  NONE,
  DIGIO16I2C_CARD = 1,
  DIGIO128_CARD,
  DIGIO128_64_CARD,
  OPTOIN8I2C_CARD,
  OPTOOUT8I2C_CARD,
  DIGIO32I2C_CARD,
  PROTO16I2C_CARD,
  ODASPSOC5_CARD,
  ODASRELAY16_CARD,
  NEW_CARD = 499,
  NOEEPROMAFTER = 500,
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

boardType_t boardType;    // Board type value

uint32_t failCount;       // Fail count for looping
uint32_t passCount;       // Pass count for looping
uint8_t single0loop1;     // Single vs loop flag

typedef enum {
  UUT_CARD_MUX_CH = 0,      // UUT is on PORT 0 of the Hub card
  TEST_STN_INT_MUX_CH = 3,  // DIGIO32 is on PORT 3 of the Hub card
} muxChannel_t;

// Classes for the UUT card types
LandBoards_I2CRPT01 BlackPillI2CMux;
LandBoards_Digio128V2 Dio128;    // Call the class constructor for the DigIO32_I2C card
LandBoards_Digio128_64 Dio128_64;    // Call the class constructor for the DigIO-128 card
LandBoards_DIGIO32I2C Dio32;
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
LandBoards_I2CRPT01 UUTI2CMux;
LandBoards_I2CRPT08 UUTI2CMux8;

//////////////////////////////////////////////////////////
// setup()
//////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(9600);
  // Mux in Hub card is set to address 0x01 offset
  BlackPillI2CMux.begin(1);
  // Configure the DIGIO32 in the test station
  BlackPillI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
  Dio32.begin(0);
  // Leave the hub mux channel pointing to Port 0
  BlackPillI2CMux.setI2CChannel(UUT_CARD_MUX_CH);

  failCount = 0;
  passCount = 0;
  single0loop1 = 0;
  boardType = NEW_CARD;   // Undetected card type
  if (detectBoardInEeprom() == 1)
  {
    // loop until legal board type is selected
    while ((boardType == NONE) || (boardType == NEW_CARD))
    {
        selectBoardType();
    }
    // If the card has an EEPROM, write it
    if ((boardType != I2CIO8_CARD)                && (boardType != I2CIO8X_CARD)    && (boardType != OPTOFST_SML_NON_INVERTING_CARD) && 
        (boardType != OPTOFST_SML_INVERTING_CARD) && (boardType != OPTOFSTBI_CARD)  && (boardType != I2CRPT01_CARD) && 
        (boardType != I2CRPT08_CARD)              && (boardType != SWLEDX8_I2C_CARD))
      eepromWrite();
  }
  // Call the initializer method for the UUT card
  switch (boardType)    // Instantiate the classes here for the boards
  {
    case DIGIO128_CARD:
      Dio128.begin();
      break;
    case DIGIO128_64_CARD:
      Dio128_64.begin();
      break;
    case PROTO16I2C_CARD:
      singleMCP23017.begin(0);      // use default address
      break;
    case ODASRELAY16_CARD:
      singleMCP23017.begin(0);      // use default address
      break;
    case SWLEDX8_I2C_CARD:
      singleMCP23017.begin(0);
      break;
    case DIGIO32I2C_CARD:
      Dio32.begin(0);
      break;
    case I2CIO8_CARD:
      i2cio8Card.begin();
      break;
    case I2CIO8X_CARD:
      i2cio8xCard.begin();
      break;
    case OPTOIN8I2C_CARD:
      singleMCP23008.begin();               // use default address 0
      break;
    case OPTOOUT8I2C_CARD:
      singleMCP23008.begin();               // use default address 0
      break;
    case I2CRPT01_CARD:
      UUTI2CMux.begin(0);                   // testing external I2C-RPT-01 card
      UUTI2CMux.setI2CChannel(0); 
      i2cio8Card1.begin(0);                  // Requires I2CIO8 cards connected to external I2C-RPT-01 card
      UUTI2CMux.setI2CChannel(1); 
      i2cio8Card2.begin(0);
      UUTI2CMux.setI2CChannel(2); 
      i2cio8Card3.begin(0);
      UUTI2CMux.setI2CChannel(3); 
      i2cio8Card4.begin(0);
      break;
    case I2CRPT08_CARD:
      UUTI2CMux8.begin(0);                   // testing external I2C-RPT-01 card
      UUTI2CMux8.setI2CChannel(0,1); 
      i2cio8Card1.begin(0);                  // Requires I2CIO8 cards connected to external I2C-RPT-01 card
      UUTI2CMux8.setI2CChannel(0,0);
      UUTI2CMux8.setI2CChannel(1,1); 
      i2cio8Card2.begin(0);
      UUTI2CMux8.setI2CChannel(1,0);
      UUTI2CMux8.setI2CChannel(2,1); 
      i2cio8Card3.begin(0);
      UUTI2CMux8.setI2CChannel(2,0);
      UUTI2CMux8.setI2CChannel(3,1); 
      i2cio8Card4.begin(0);
      UUTI2CMux8.setI2CChannel(3,0);
      UUTI2CMux8.setI2CChannel(4,1); 
      i2cio8Card5.begin(0);
      UUTI2CMux8.setI2CChannel(4,0);
      UUTI2CMux8.setI2CChannel(5,1); 
      i2cio8Card6.begin(0);
      UUTI2CMux8.setI2CChannel(5,0);
      UUTI2CMux8.setI2CChannel(6,1); 
      i2cio8Card7.begin(0);
      UUTI2CMux8.setI2CChannel(6,0);
      UUTI2CMux8.setI2CChannel(7,1); 
      i2cio8Card8.begin(0);
      UUTI2CMux8.setI2CChannel(7,0);
      break;
  }
  Serial.println(F("C=Card Tests, D=Direct, E=EEPROM, I=access Internal DIGIO32"));
}

//////////////////////////////////////////////////////////
// loop() - Loop on the menu
//////////////////////////////////////////////////////////

void loop()
{
  while (1)
  {
    topLevelMenu();
  }
}
