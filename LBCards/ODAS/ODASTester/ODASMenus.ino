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
      case '?':
        Serial.println(F("\nC=Card Test Sub-Menu (Bounce LEDs, External loopback, Internal Tests)"));
        Serial.println(F("D=Direct Access Menu (Read or Write memory)"));
        Serial.println(F("E=EEPROM Access (Read/Write EEPROM)"));
        break;
      default:
        Serial.println(F("\nC=Card Test Menu, D=Direct Access Menu, E=EEPROM Access"));
        break;
    }
    flushSerial();
  }
}

//////////////////////////////////////////////////////////
// void cardTestMenu()
//////////////////////////////////////////////////////////

enum {NO_TEST, LOOPBACK_TEST, INTERNAL_TEST, BOUNCE_LEDS};

void cardTestMenu(void)
{
  int incomingByte = 0;   // for incoming serial data
  uint8_t testType = NO_TEST;
  Serial.println(F("L/S=Loop/Single, T=Test, B=Bounce LEDs, I=Int'l Tests, X=eXit sub-menu"));
  while (1)
  {
    testType = NO_TEST;
    if (Serial.available() > 0)
    {
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
            Serial.println(F("\nC=Card Test Menu, D=Direct Access Menu, E=EEPROM Access"));
            return;
            break;
          }
        case '?':
          Serial.println(F("\nL/S=Loop Tests or Run Single Test (control)"));
          Serial.println(F("T=Test card with external loopback cable/hardware"));
          Serial.println(F("B=Bounce a single bit across the LEDs"));
          Serial.println(F("I=Internal Card Tests test (no loopback)"));
          Serial.println(F("X=eXit sub-menu (back to top menu)"));
          break;
        default:
          {
            Serial.println(F("\nL/S=Loop/Single, T=Test, B=Bounce LEDs, I=Int'l Tests, X=eXit sub-menu"));
            break;
          }
      }
      do
      {
        switch (testType)
        {
          case LOOPBACK_TEST:
            {
              if (loopBackTestCard() == 0)
                passCount++;
              else
                failCount++;
              Serial.print(F("Test PASS = "));
              Serial.print(passCount);
              Serial.print(F(", FAIL = "));
              Serial.println(failCount);
              break;
            }
          case INTERNAL_TEST:
            {
              if (internalLoopBackTestCard() == 0)
                passCount++;
              else
                failCount++;
              Serial.print(F("Test PASS = "));
              Serial.print(passCount);
              Serial.print(F(", FAIL = "));
              Serial.println(failCount);
              break;
            }
          case BOUNCE_LEDS:
            {
              bounceLedsCard();
              Serial.println("Finished bouncing LEDs");
              break;
            }
        }
      }
      while ((single0loop1 == 1) && (Serial.available() == 0) && (testType != NO_TEST));
      flushSerial();
      testType = NO_TEST;
    }
  }
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
  Serial.println(F("H=Write High, L=Write Low, R=Read a bit, X=eXit"));
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
            Serial.print("Bit to read (HEX): 0x");
            flushSerial();
            bitToCheck = getHexSerial();
            Serial.println("");
            readValue = readBitValue(bitToCheck);
            Serial.print("Read value: ");
            Serial.println(readValue, HEX);
            break;
          }
        case 'H':   // Set a bit
        case 'h':
          {
            flushSerial();
            Serial.print("Bit to set High (HEX): 0x");
            bitToCheck = getHexSerial();
            Serial.println("");
            flushSerial();
            writeBitValue(bitToCheck, 1);
            //            Serial.println("Completed write");
            break;
          }
        case 'L':   // Clear a bit
        case 'l':
          {
            flushSerial();
            Serial.print("Bit to clear Low  (HEX): 0x");
            bitToCheck = getHexSerial();
            Serial.println("");
            flushSerial();
            writeBitValue(bitToCheck, 0);
            //            Serial.println("Completed write");
            break;
          }
        case 'X':   // write a bit
        case 'x':
          {
            Serial.println("\nC=Card Test Menu, D=Direct Access Menu, E=EEPROM Access");
            return;
            break;
          }
        case '?':
          {
            Serial.println(F("\nH=Set a DIGIO pin High"));
            Serial.println(F("L=Clear a DIGIO pin to Low"));
            Serial.println(F("R=Read a DIGIO bit"));
            Serial.println(F("X=eXit up a level to higher menu"));
            break;
          }
        default:
          {
            Serial.println(F("\nH=Write High, R=Read a bit, L=Write Low, X=eXit"));
            break;
          }
      }
      while (Serial.available() > 0)
        Serial.read();
    }
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
          Serial.println(F("\neepromAccessMenu() - Finished reading EEPROM"));
          break;
        case 'W':
        case 'w':
          selectBoardType();
          eepromWrite();
          //          Serial.println(F("\neepromAccessMenu() - Finished writing EEPROM"));
          break;
        case 'X':
        case 'x':
          Serial.println("\nC=Card Test Menu, D=Direct Access Menu, E=EEPROM Access");
          return;
          break;
        case '?':
          Serial.println(F("\nR=Read EEPROM"));
          Serial.println(F("W=select Board type and Write EEPROM"));
          Serial.println(F("X=Exit to higher level Menu"));
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
  //  Serial.println(hexVal);
  return (hexVal);
}


