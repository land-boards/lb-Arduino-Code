//////////////////////////////////////////////////////////
// void topLevelMenu(void) - The top level menu.
//////////////////////////////////////////////////////////

void topLevelMenu(void)
{
  int incomingByte = 0;   // for incoming serial data
  if (Serial.available() > 0)
  {
    // read the incoming byte:
    incomingByte = Serial.read();
    switch (incomingByte)
    {
      case 'C':
      case 'c':
        cardTestMenu();
        break;
      case 'D':
      case 'd':
        directAccessMenu();
        break;
      case 'E':
      case 'e':
        eepromAccessMenu();
        break;
      default:
        Serial.println(F("\nC=Card Test Menu, D=Direct Access Menu, E=EEPROM Access"));
        break;
    }
    flushSerial();
  }
}

//////////////////////////////////////////////////////////
// void eepromAccessMenu(void)
//////////////////////////////////////////////////////////

void eepromAccessMenu(void)
{
  int incomingByte = 0;   // for incoming serial data
  Serial.println(F("\nR=Read EEPROM, W=Write EEPROM, X=Exit Menu"));
  while (1)
  {
    if (Serial.available() > 0)
    {
      // read the incoming byte:
      incomingByte = Serial.read();
      switch (incomingByte)
      {
        case 'R':
        case 'r':
          Serial.println(F("Reading EEPROM"));
          eepromRead();
//          Serial.println(F("\neepromAccessMenu() - Finished reading EEPROM"));
          break;
        case 'W':
        case 'w':
          selectBoardType();
          eepromWrite();
//          Serial.println(F("\neepromAccessMenu() - Finished writing EEPROM"));
          break;
        case 'X':
        case 'x':
          return;
          break;
        default:
          Serial.println(F("\nR=Read EEPROM, W=Write EEPROM, X=Exit Menu"));
          break;
      }
      flushSerial();
    }
  }
}

//////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////

void flushSerial(void)
{
  while (Serial.available() > 0)
    Serial.read();
}

//////////////////////////////////////////////////////////
// void directAccessMenu(void)
//////////////////////////////////////////////////////////

void directAccessMenu(void)
{
  int incomingByte = 0;   // for incoming serial data
  uint8_t bitToCheck;
  uint8_t bitToWrite;
  uint8_t readValue;
  flushSerial();
  Serial.println("Direct Access Hardware");
  Serial.println(F("R=Read a bit, W=Write a bit, X=eXit"));
  while (1)
  {
    if (Serial.available() > 0)
    {
      // read the incoming byte:
      incomingByte = Serial.read();
      switch (incomingByte)
      {
        case 'R':   // read a bit
        case 'r':
          {
            Serial.print("Bit to read (NEX): ");
            flushSerial();
            bitToCheck = getHexSerial();
            Serial.println("");
            readValue = readBitValue(bitToCheck);
            Serial.print("Value: ");
            Serial.println(readValue, HEX);
            break;
          }
        case 'W':   // write a bit
        case 'w':
          {
            flushSerial();
            Serial.print("Bit to write (NEX): ");
            bitToCheck = getHexSerial();
            Serial.println("");
            flushSerial();
            Serial.print("Write Value (NEX): ");
            bitToWrite = getHexSerial();
            Serial.println("");
            writeBitValue(bitToCheck, bitToWrite);
            Serial.println("Completed write");
            break;
          }
        case 'X':   // write a bit
        case 'x':
          {
            return;
            break;
          }
        default:
          {
            Serial.println(F("\nR=Read a bit, W=Write a bit, X=eXit Menu"));
            break;
          }
      }
      while (Serial.available() > 0)
        Serial.read();
    }
  }
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
      hexVal = (hexVal * 10) + (theStringValue[linePtr] - '0');
    else if ((theStringValue[linePtr] >= 'a') && (theStringValue[linePtr] <= 'f'))
      hexVal = (hexVal * 10) + (theStringValue[linePtr] - 'a');
    else if ((theStringValue[linePtr] >= 'A') && (theStringValue[linePtr] <= 'F'))
      hexVal = (hexVal * 10) + (theStringValue[linePtr] - 'A');
    else
    {
      Serial.println("Conversion error");
      return (0);
    }
    linePtr++;
  }
  //  Serial.print("stringToHex() - returning: ");
  //  Serial.println(hexVal);
  return (hexVal);
}

//////////////////////////////////////////////////////////
// void cardTestMenu()
//////////////////////////////////////////////////////////

enum {NO_TEST, LOOPBACK_TEST, INTERNAL_TEST, BOUNCE_LEDS};

void cardTestMenu(void)
{
  int incomingByte = 0;   // for incoming serial data
  uint8_t testType = NO_TEST;
  Serial.println(F("\nL/S=Loop/Single Test, T=Test DIGIOs, B=Bounce LEDs, I=Internal Tests, X=eXit to upper menu"));
  while (1)
  {
    if (Serial.available() > 0)
    {
      testType = NO_TEST;
      // read the incoming byte:
      incomingByte = Serial.read();
      switch (incomingByte)
      {
        case 'T':
        case 't':
          {
            testType = LOOPBACK_TEST;
            break;
          }
        case 'I':
        case 'i':
          {
            testType = INTERNAL_TEST;
            break;
          }
        case 'B':
        case 'b':
          {
            testType = BOUNCE_LEDS;
            break;
          }
        case 'L':
        case 'l':
          {
            single0loop1 = 1;
            Serial.println("Set flag to loop tests");
            break;
          }
        case 'S':
        case 's':
          {
            single0loop1 = 0;
            Serial.println("Set flag to not loop tests");
            break;
          }
        case 'X':
        case 'x':
          {
            Serial.println(F("\nR=Read EEPROM, W=Write EEPROM, C=Card Test Menu, D=Direct Access Menu"));
            return;
            break;
          }
        default:
          {
            Serial.println(F("\nL/S=Loop/Single Test, T=Test DIGIOs, B=Bounce LEDs, I=Internal Tests, X=eXit to upper menu"));
            break;
          }
      }
      while (Serial.available() > 0)  // flush extra chars
        Serial.read();

      do
      {
        switch (testType)
        {
          case LOOPBACK_TEST:
            if (loopBackTestCard() == 0)
              passCount++;
            else
              failCount++;
            Serial.print(F("Test PASS = "));
            Serial.print(passCount);
            Serial.print(F(", FAIL = "));
            Serial.println(failCount);
            break;
          case INTERNAL_TEST:
            if (internalLoopBackTestCard() == 0)
              passCount++;
            else
              failCount++;
            Serial.print(F("Test PASS = "));
            Serial.print(passCount);
            Serial.print(F(", FAIL = "));
            Serial.println(failCount);
            break;
          case BOUNCE_LEDS:
            bounceLedsCard();
            Serial.print(F("Test PASS = "));
            Serial.print(passCount);
            Serial.print(F(", FAIL = "));
            Serial.println(failCount);
            break;
        }
      }
      while ((single0loop1) && (Serial.available() == 0));
      testType = NO_TEST;
    }
  }
}

