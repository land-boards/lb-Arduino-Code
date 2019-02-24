//////////////////////////////////////////////////////////
// D128Access Direct access the DIGIO-128 card
// Directly access bits on the card from the Serial Port
//////////////////////////////////////////////////////////

#include <LandBoards_Digio128V2.h>
#include <LandBoards_I2CRPT01.h>

//////////////////////////////////////////////////////////
// defines follow

#define SERIAL_DEBUG Serial

LandBoards_I2CRPT01 myI2CMux;

#define UUT_CARD_MUX_CH 0

Digio128 Dio128;

//////////////////////////////////////////////////////////
// setup()
//////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(9600);
  myI2CMux.begin();
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  TWBR = 12;    // go to 400 KHz I2C speed mode
  Serial.println(F("H=Set a bit High, L=Set a bit Low, R=Read bit (no dir change), P=Poll input bit"));
  Dio128.begin();
}

//////////////////////////////////////////////////////////
// loop()
//////////////////////////////////////////////////////////

void loop()
{
  int incomingByte = 0;   // for incoming serial data
  uint8_t bitToCheck;
  uint8_t readValue;
  if (Serial.available() > 0)
  {
    // read the incoming byte:
    incomingByte = Serial.read();
    switch (incomingByte)
    {
      case 'H':
      case 'h':
        flushSerial();
        Serial.print("Bit to set to High (NEX): ");
        bitToCheck = getHexSerial();
        Serial.println("");
        flushSerial();
        writeBitDIGIO128(bitToCheck, 1);
        Serial.println("Completed write");
        break;
      case 'L':
      case 'l':
        flushSerial();
        Serial.print("Bit to clear to LOW (NEX): ");
        bitToCheck = getHexSerial();
        Serial.println("");
        flushSerial();
        writeBitDIGIO128(bitToCheck, 0);
        Serial.println("Completed write");
        break;
      case 'R':
      case 'r':
        Serial.print("Bit to read (NEX): ");
        flushSerial();
        bitToCheck = getHexSerial();
        Serial.println("");
        Dio128.pinMode(bitToCheck,INPUT);
        readValue = readBitDIGIO128(bitToCheck);
        Serial.print("Value: ");
        Serial.println(readValue, HEX);
        break;
      case 'P':
      case 'p':
        Serial.print("Bit to poll (NEX): ");
        flushSerial();
        bitToCheck = getHexSerial();
        Serial.println("");
        readValue = readBitDIGIO128(bitToCheck);
        Serial.print("Value: ");
        Serial.println(readValue, HEX);
        break;
      default:
        Serial.println(F("H=Set a bit High, L=Set a bit Low, R=Read bit (no dir change), P=Poll input bit"));
        break;
    }
    flushSerial();
  }
}

//////////////////////////////////////////////////////////
// void flushSerial(void)
//////////////////////////////////////////////////////////

void flushSerial(void)
{
  while (Serial.available() > 0)
    Serial.read();
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t readBitDIGIO128(uint8_t bitToCheck)
//////////////////////////////////////////////////////////////////////////////////////

uint8_t readBitDIGIO128(uint8_t bitToRead)
{
  uint32_t rdVal;
//  Serial.println(F("\nreadBitDIGIO128() - reached function"));
  rdVal = Dio128.digitalRead(bitToRead);
  Serial.print(F("Read Value: "));
  Serial.println(rdVal);
  return(rdVal);
}

//////////////////////////////////////////////////////////////////////////////////////
// void writeBitDIGIO128(uint8_t bitToCheck, uint8_t bitWeiteValue)
//////////////////////////////////////////////////////////////////////////////////////

void writeBitDIGIO128(uint8_t bitToWrite, uint8_t writeValue)
{
//  Serial.println(F("\writeBitDIGIO128() - reached function"));
  Dio128.pinMode(bitToWrite,OUTPUT);
  Dio128.digitalWrite(bitToWrite,writeValue);
}

//////////////////////////////////////////////////////////
// uint32_t getHexSerial(void)
//////////////////////////////////////////////////////////

uint32_t getHexSerial(void)
{
  char inString[81];
  uint8_t hexVal;
  flushSerial();
  //  Serial.println("getHexSerial() - reached function");
  readInSerialString(inString);
  //  Serial.print("readInSerialString(): Returned: ");
  //  Serial.println(inString);
  hexVal = stringToHex(inString);
  //  Serial.print("stringToHex() - Returned: ");
  //  Serial.println(bitToCheck);
  return (hexVal);
}

//////////////////////////////////////////////////////////
// uint32_t readInSerialString(char * myString)
//////////////////////////////////////////////////////////

uint32_t readInSerialString(char * myString)
{
  uint8_t lineCounter = 0;
  flushSerial();
  //  Serial.println("readInSerialString() - reached function");
  while (1)
  {
    while (Serial.available() == 0);
    myString[lineCounter] = Serial.read();
    Serial.print(myString[lineCounter]);
    if ((myString[lineCounter] == '\n') || (myString[lineCounter] == '\r'))
    {
      myString[lineCounter] = 0;
      //      Serial.print("The String: ");
      //      Serial.println(myString);
      //      Serial.print("String Length: ");
      //      Serial.println(lineCounter);
      return lineCounter;
    }
    lineCounter++;
  }
}

//////////////////////////////////////////////////////////
// uint32_t stringToHex(String theStringValue)
//////////////////////////////////////////////////////////

uint32_t stringToHex(char * theStringValue)
{
  uint8_t hexVal = 0;
  uint8_t linePtr = 0;
  //  Serial.println("stringToHex() - reached function");
  while (theStringValue[linePtr] != 0)
  {
    if ((theStringValue[linePtr] >= '0') && (theStringValue[linePtr] <= '9'))
      hexVal = (hexVal * 16) + (theStringValue[linePtr] - '0');
    else if ((theStringValue[linePtr] >= 'a') && (theStringValue[linePtr] <= 'f'))
      hexVal = (hexVal * 16) + (theStringValue[linePtr] - 'a' + 10);
    else if ((theStringValue[linePtr] >= 'A') && (theStringValue[linePtr] <= 'F'))
      hexVal = (hexVal * 16) + (theStringValue[linePtr] - 'A' + 10);
    else
    {
      Serial.println("Conversion error");
      return (0);
    }
    linePtr++;
  }
//  Serial.print("stringToHex() - returning: ");
//  Serial.println(hexVal,HEX);
  return (hexVal);
}


