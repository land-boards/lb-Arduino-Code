//////////////////////////////////////////////////////////
//  Menu system
//////////////////////////////////////////////////////////


enum {INTERNAL_DIGIO, EXTERNAL_DIGIO};

enum {NO_TEST, LOOPBACK_TEST, INTERNAL_TEST, BOUNCE_LEDS};

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
      // Card test menu
      case 'C':
      case 'c':
        cardTestMenu();
        break;
      // Direct access meny
      case 'D':
      case 'd':
        directAccessMenu();
        break;
      // EEPROM menu
      case 'E':
      case 'e':
        eepromAccessMenu();
        break;
      // Direct access menus
      case 'I':
      case 'i':
        directAccessInternalDIGIO32Menu();
        break;
      case '?':
        Serial.println(F("\nC=Card Tests (Bounce LEDs, External loopback, Internal Tests)"));
        Serial.println(F("D=Direct Access (Read or Write Digital I/O pins)"));
        Serial.println(F("E=EEPROM Access (Read/Write EEPROM)"));
        Serial.println(F("I=Set/clear or read test internal DIGIO32 bits"));
        break;
      default:
        Serial.println(F("\nC=Card Tests, D=Direct, E=EEPROM, I=access Internal DIGIO32"));
        break;
    }
    flushSerial();
  }
}

//////////////////////////////////////////////////////////
// void cardTestMenu()
//////////////////////////////////////////////////////////

void cardTestMenu(void)
{
  int incomingByte = 0;   // for incoming serial data
  uint8_t testType = NO_TEST;
  passCount = 0;
  failCount = 0;
  Serial.println(F("L=Loop/S=Single, T=Test, B=Bounce LEDs, I=UUT Int'l Tests, X=eXit sub-menu"));
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
            Serial.print(F("Testing UUT = "));
            printBoardType();
            testType = LOOPBACK_TEST;
            break;
          }
        case 'I':
        case 'i':
          {
            Serial.println(F("UUT Internal card tests"));
            testType = INTERNAL_TEST;
            break;
          }
        case 'B':
        case 'b':
          {
            Serial.println(F("Bounce a bit across outputs"));
            testType = BOUNCE_LEDS;
            break;
          }
        case 'L':
        case 'l':
          {
            single0loop1 = 1;
            Serial.println(F("Set flag to loop tests"));
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
            Serial.println(F("\nC=Card Tests, D=Direct, E=EEPROM, I=access Internal DIGIO32"));
            return;
            break;
          }
        case '?':
          Serial.println(F("\nCard Tests"));
          Serial.println(F("L = Loop Tests (control)"));
          Serial.println(F("S = Run Single Test (control)"));
          Serial.println(F("T = Test card with external loopback cable/hardware"));
          Serial.println(F("B = Bounce a single bit across the LEDs"));
          Serial.println(F("I = Internal Card Accesses (no loopback)"));
          Serial.println(F("X = eXit sub-menu (back to top menu)"));
          break;
        default:
          {
            Serial.println(F("\nL=Loop/S=Single, T=Test, B=Bounce LEDs, I=UUT Int'l Test, X=eXit sub-menu"));
            break;
          }
      }
      do
      {
        switch (testType)
        {
          case LOOPBACK_TEST:
            {
              if (extLBTestCard() == TEST_PASSED)
                passCount++;
              else
              {
                failCount++;
                single0loop1 = 0; // break out of looping
              }
              Serial.print(F("Test PASS = "));
              Serial.print(passCount);
              Serial.print(F(", FAIL = "));
              Serial.println(failCount);
              break;
            }
          case INTERNAL_TEST:
            {
              if (internalLBTestCard() == TEST_PASSED)
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
              if (bounceLedsCard() == 0)
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
//  void printBoardType(void)
//////////////////////////////////////////////////////////

void printBoardType(void)
{
  switch (boardType)
  {
    case NONE:
      Serial.println("");
      break;
    case DIGIO16I2C_CARD:
      Serial.println("DIGIO16-I2C");
      break;
    case DIGIO128_CARD:
      Serial.println("DIGIO-128");
      break;
    case DIGIO128_64_CARD:
      Serial.println("DIGIO-128/64");
      break;
    case OPTOIN8I2C_CARD:
      Serial.println("OptoIn8-I2C");
      break;
    case OPTOOUT8I2C_CARD:
      Serial.println("OptoOut8-I2C");
      break;
    case DIGIO32I2C_CARD:
      Serial.println("DIGIO32-I2C");
      break;
    case PROTO16I2C_CARD:
      Serial.println("PROTO16-I2C");
      break;
    case ODASPSOC5_CARD:
      Serial.println("ODAS-PSOC5");
      break;
    case ODASRELAY16_CARD:
      Serial.println("ODASRELAY16");
      break;
    case NEW_CARD:
      Serial.println("New card");
      break;
    case NOEEPROMAFTER:
      Serial.println("No EEPROM");
      break;
    case I2CIO8_CARD:
      Serial.println("I2CIO-8");
      break;
    case I2CIO8X_CARD:
      Serial.println("I2CIO-8X");
      break;
    case OPTOFST_SML_NON_INVERTING_CARD:
      Serial.println("Opto Non-inv");
      break;
    case OPTOFST_SML_INVERTING_CARD:
      Serial.println("Opto Inc");
      break;
    case OPTOFSTBI_CARD:
      Serial.println("OPTO-FAST-BI");
      break;
    case I2CRPT01_CARD:
      Serial.println("I2C-RPT");
      break;
    case I2CRPT08_CARD:
      Serial.println("I2CRPT-08");
      break;
    case SWLEDX8_I2C_CARD:
      Serial.println("SWLEDX8_I2C");
      break;
    case UNKNOWN_BOARD:
      Serial.println("Unknown board");
      break;
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
  Serial.println("Direct Access UUT Hardware");
  ODASTSTR_I2CMux.setI2CChannel(UUT_CARD_MUX_CH);
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
        case 'X':   // Exit
        case 'x':
          {
            ODASTSTR_I2CMux.setI2CChannel(UUT_CARD_MUX_CH);
            Serial.println("\nC=Card Tests, D=Direct, E=EEPROM, I=access Internal DIGIO32");
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
// void directAccessMenu(void)
//////////////////////////////////////////////////////////

void directAccessInternalDIGIO32Menu(void)
{
  int incomingByte = 0;   // for incoming serial data
  uint8_t bitToCheck;
  uint8_t bitToWrite;
  uint8_t readValue;
  flushSerial();
  Serial.println(F("Direct Access Test Station DIGIO32 Hardware"));
  ODASTSTR_I2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
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
            readValue = readBitDIGIO32(bitToCheck);
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
            IntDio32.digitalWrite(bitToCheck, 1);
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
            IntDio32.digitalWrite(bitToCheck, 0);
            //            Serial.println("Completed write");
            break;
          }
        case 'X':   // Exit
        case 'x':
          {
            ODASTSTR_I2CMux.setI2CChannel(UUT_CARD_MUX_CH);
            Serial.println("\nC=Card Tests, D=Direct, E=EEPROM, I=access Internal DIGIO32");
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
          Serial.println(F("\n\reepromAccessMenu() - Finished reading EEPROM"));
          break;
        case 'W':
        case 'w':
          selectBoardType(-1,-1);
          if (boardType != NONE)
          {
            eepromWrite();
            Serial.println(F("\n\reepromAccessMenu() - Finished writing EEPROM"));
          }
          else
          {
            Serial.println(F("\n\reepromAccessMenu() - Did not select format writing EEPROM"));
          }
          break;
        case 'X':
        case 'x':
          Serial.println("\n\rC=Card Tests, D=Direct, E=EEPROM, I=access Internal DIGIO32");
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
