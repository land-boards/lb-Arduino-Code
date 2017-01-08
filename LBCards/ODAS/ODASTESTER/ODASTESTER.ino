//////////////////////////////////////////////////////////
// ODASTESTER Factory Test code
// Test each channel
// Read/write EEPROM
//////////////////////////////////////////////////////////

//#include <Wire.h>
#include <LandBoards_DIGIO32_I2C.h>
#include <LandBoards_Digio128.h>
#include <Adafruit_MCP23008.h>
//#include "Adafruit_MCP23017.h"

//////////////////////////////////////////////////////////
// defines follow

#define SERIAL_DEBUG Serial

typedef enum {
  NONE,
  DIGIO16I2C = 1,
  DIGIO128,
  OPTOIN8I2C,
  OPTOOUT8I2C,
  DIGIO32I2C,
  PROTO16I2C,
  ODASPSOC5,
  NEWBOARD = 9999,
}
boardType_t;

boardType_t boardType;

uint32_t failCount;
uint32_t passCount;
int looping;

//////////////////////////////////////////////////////////
// setup()
//////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(9600);
  //  TWBR = 12;    // go to 400 KHz I2C speed mode

  failCount = 0;
  passCount = 0;
  looping = 0;
  boardType = NEWBOARD;
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

