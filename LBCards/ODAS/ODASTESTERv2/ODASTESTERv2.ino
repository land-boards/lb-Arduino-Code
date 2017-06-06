//////////////////////////////////////////////////////////
// ODASTESTER Factory Test code
// Test each card and channel
// Read/write EEPROM
//////////////////////////////////////////////////////////

#include <LandBoards_DIGIO32_I2C.h>
#include <LandBoards_Digio128.h>
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
int looping;

typedef enum {
  UUT_CARD_MUX_CH=0,
  TEST_STN_INT_MUX_CH=1,
} muxChannel_t;

LandBoards_I2CRPT01 myI2CMux;

//////////////////////////////////////////////////////////
// setup()
//////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(9600);
  myI2CMux.begin();
  setMuxChannel(UUT_CARD_MUX_CH);
  TWBR = 12;    // go to 400 KHz I2C speed mode

  failCount = 0;
  passCount = 0;
  looping = 0;
  boardType = NEW_CARD;
  if (detectBoardInEeprom() == 1)
  {
    selectBoardType();
    eepromWrite();
  }
  Serial.println(F("R=Read EEPROM, W=Write EEPROM, T=Test DIGIOs, L=Loop Test, B=Bounce LEDs"));
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
    switch (incomingByte)
    {
      case 'R':
      case 'r':
        {
          eepromRead();
          break;
        }
      case 'W':
      case 'w':
        {
          selectBoardType();
          eepromWrite();
          break;
        }
      case 'T':
      case 't':
        {
          if (loopBackTestCard() == 0)
            passCount++;
          else
            failCount++;

          Serial.print(F("Loopback Test PASS = "));
          Serial.print(passCount);
          Serial.print(F(", FAIL = "));
          Serial.println(failCount);
          break;
        }
      case 'L':
      case 'l':
        {
          looping = 1;
          break;
        }
      case 'B':
      case 'b':
        {
          bounceLedsCard();
          break;
        }
      default:
        {
          if (looping == 1)
            looping = 0;
          else
            Serial.println(F("Unrecognized command"));
          Serial.println(F("\nR=Read EEPROM, W=Write EEPROM, T=Test DIGIOs, L=Loop Test, B=Bounce LEDs"));
          break;
        }
    }
    while (Serial.available() > 0)
      Serial.read();

    if (looping == 1)
      Serial.println("Looping, hit a key to stop");
    while ((looping == 1) && (Serial.available() == 0))
    {
      if (loopBackTestCard() == 0)
        passCount++;
      else
        failCount++;

      Serial.print("Loopback Test PASS = ");
      Serial.print(passCount);
      Serial.print(", FAIL = ");
      Serial.println(failCount);
    }
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

