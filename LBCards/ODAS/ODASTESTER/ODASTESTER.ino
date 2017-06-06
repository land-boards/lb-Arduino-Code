//////////////////////////////////////////////////////////
// ODASTESTER Factory Test code
// Test each card and channel
// Read/write EEPROM
//////////////////////////////////////////////////////////

#include <LandBoards_DIGIO32_I2C.h>
#include <LandBoards_Digio128V2.h>
#include <LandBoards_I2CIO8.h>
#include <LandBoards_I2CIO8X.h>
#include <LandBoards_I2CTEMP01.h>
#include <LandBoards_I2CRPT01.h>
#include <Adafruit_MCP23008.h>
#include <Adafruit_MCP23017.h>

//////////////////////////////////////////////////////////
// defines follow

#define SERIAL_DEBUG Serial

typedef enum {
  NONE,
  DIGIO16I2C_CARD = 1,
  DIGIO128_CARD,
  OPTOIN8I2C_CARD,
  OPTOOUT8I2C_CARD,
  DIGIO32I2C_CARD,
  PROTO16I2C_CARD,
  ODASPSOC5_CARD,
  NEW_CARD = 499,
  NOEEPROMAFTER = 500,
  I2CIO8_CARD,
  I2CIO8X_CARD,
  OPTOSMALL_CARD,
  OPTOFAST_CARD,
} boardType_t;

//////////////////////////////////////////////////////////
// globals follow

boardType_t boardType;

uint32_t failCount;
uint32_t passCount;
uint8_t single0loop1;

typedef enum {
  UUT_CARD_MUX_CH = 0,
  TEST_STN_INT_MUX_CH = 1,
} muxChannel_t;

LandBoards_I2CRPT01 myI2CMux;

//////////////////////////////////////////////////////////
// setup()
//////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(9600);
  myI2CMux.begin();
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  TWBR = 12;    // go to 400 KHz I2C speed mode

  failCount = 0;
  passCount = 0;
  single0loop1 = 0;
  boardType = NEW_CARD;
  if (detectBoardInEeprom() == 1)
  {
    selectBoardType();
    eepromWrite();
  }
  Serial.println(F("E=EEPROM Access, C=Card Test Menu, D=Direct Access Menu"));
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

//////////////////////////////////////////////////////////
// void setMuxChannel(muxChannel_t)
//  UUT_Card = 0,
//  TEST_STN_DIGIO32_I2C=1,
//////////////////////////////////////////////////////////

void setMuxChannel(muxChannel_t newMuxChannel)
{
  myI2CMux.setI2CChannel(newMuxChannel);

}

