//////////////////////////////////////////////////////////////////////////////////////
// ODAS card loopback test code
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t loopBackTestCard(void) -
//////////////////////////////////////////////////////////////////////////////////////

uint8_t loopBackTestCard(void)
{
  switch (boardType)
  {
    case DIGIO16I2C:
      Serial.println(F("Not supported at present"));
      break;
    case DIGIO128:
      return (loopBackTestDigio128());
      break;
    case OPTOIN8I2C:
      return (loopBackTestOptoIn8());
      break;
    case OPTOOUT8I2C:
      return (loopBackTestOptoOut8());
      break;
    case DIGIO32I2C:
      return (loopBackTestDigio32());
      break;
    case PROTO16I2C:
      Serial.println(F("Not supported at present"));
      break;
    case ODASPSOC5:
      Serial.println(F("Not supported at present"));
      break;
    case I2CIO8:
      return (testI2CIO8());
      break;
    case I2CIO8X:
      return (testI2CIO8X());
      break;
    case NEWBOARD:
      Serial.println(F("Not supported at present"));
      break;
    default:
      Serial.println(F("Undefined board type"));
      return 1;
      break;
  }
  return 1; // fail
}

uint8_t testI2CIO8(void)
{
  Serial.println(F("I2CIO8 card"));
  I2CIO8 i2cio8Card;
  i2cio8Card.begin();
  while(1)
  {
    uint8 theJumpers;
    writeLED(0,i2cio8Card.readJumper(0));
    writeLED(1,i2cio8Card.readJumper(1));
    writeLED(2,i2cio8Card.readJumper(2));
    writeLED(3,i2cio8Card.readJumper(3));
  }
}

uint8_t testI2CIO8X(void)
{
  Serial.println(F("I2CIO8X card"));
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t loopBackTestDigio32()
//////////////////////////////////////////////////////////////////////////////////////

uint8_t loopBackTestDigio32(void)
{
  uint8_t port;
  uint8_t pass0fail1 = 0;
  Digio32 Dio32;
  Dio32.begin(0);

  for (port = 0; port < 16; port++)
  {
    Dio32.pinMode(port, OUTPUT);
    Dio32.pinMode(port, INPUT_PULLUP);

    delay(2);
    Dio32.digitalWrite(port, HIGH);
    delay(2);
    if (Dio32.digitalRead(port + 16) != HIGH)
    {
      Serial.print(F("Error on chip 0"));
      Serial.print(F(" and port "));
      Serial.print(port + 16);
      Serial.println(F(" Expected High"));
      pass0fail1 = 1;
    }
    Dio32.digitalWrite(port, LOW);
    delay(2);
    if (Dio32.digitalRead(port + 16) != LOW)
    {
      Serial.print(F("Error on chip 0"));
      Serial.print(F(" and port "));
      Serial.print(port);
      Serial.println(F(" Expected LOW"));
      pass0fail1 = 1;
    }
    Dio32.pinMode(port, INPUT_PULLUP);
    delay(2);
  }

  return pass0fail1;
}

//////////////////////////////////////////////////////////////////////////////////////
// OptoIn8-I2C card test code
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
// initOI8pins - Init the OptoIn8-I2C card to all Inputs
//////////////////////////////////////////////////////////////////////////////////////

void initOI8pins(void)
{
  Adafruit_MCP23008 mcpOI8;
  mcpOI8.begin();               // use default address 0

  int loopCnt;
  for (loopCnt = 0; loopCnt < 8; loopCnt++)
  {
    mcpOI8.pinMode(loopCnt, INPUT);
    mcpOI8.pullUp(loopCnt, HIGH);  // turn on a 100K pullup internally
  }
}

//////////////////////////////////////////////////////////////////////////////////////
// Read a bit from the OptoIn8-I2C card
//////////////////////////////////////////////////////////////////////////////////////

unsigned char readOptoIn8(void)
{
  Adafruit_MCP23008 mcpOI8;
  mcpOI8.begin();               // use default address 0
  int loopVal;
  unsigned int rval = 0;
  for (loopVal = 0; loopVal < 8; loopVal++)
  {
    rval |= mcpOI8.digitalRead(loopVal) & 0x1;
    rval <<= 1;
  }
  return rval >> 1;
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t loopBackTestOptoIn8(void) - Test the OptoIn8-I2C card
// Puts out 8 bit test vector on Arduino pins
//  Arduino Output lines aew D2-D5, D7, D8, D14(A0), D15(A1)
// Looks at the returned values on the OptoIn8-I2C
//////////////////////////////////////////////////////////////////////////////////////

uint8_t loopBackTestOptoIn8(void)
{
  unsigned char readVal;
  int testPass = 1;
  int testBit = 0x1;
  //  Serial.println(F("Testing OptoIn8-I2C card"));

  initOI8pins();
  for (int loopVal = 2; loopVal < 6; loopVal++)
  {
    digitalWrite(loopVal, LOW);
    pinMode(loopVal, OUTPUT);
    digitalWrite(loopVal, LOW);
    readVal = readOptoIn8();
    if ((readVal & testBit) != testBit)
    {
      testPass = 0;
      Serial.print(F("OptoIn8-I2C failed LOW on bit "));
      Serial.println(testBit);
    }
    digitalWrite(loopVal, HIGH);
    delay(10);
    readVal = readOptoIn8();
    if ((readVal & testBit) == testBit)
    {
      testPass = 0;
      Serial.print(F("OptoIn8-I2C failed HIGH on bit "));
      Serial.println(testBit);
      Serial.print(F("Read back on  "));
      Serial.println(testBit);
    }
    testBit <<= 1;
  }
  for (int loopVal = 7; loopVal < 9; loopVal++)
  {
    digitalWrite(loopVal, LOW);
    pinMode(loopVal, OUTPUT);
    digitalWrite(loopVal, LOW);
    readVal = readOptoIn8();
    if ((readVal & testBit) != testBit)
    {
      testPass = 0;
      Serial.print(F("OptoIn8-I2C failed LOW on bit "));
      Serial.println(testBit);
    }
    digitalWrite(loopVal, HIGH);
    delay(10);
    readVal = readOptoIn8();
    if ((readVal & testBit) == testBit)
    {
      testPass = 0;
      Serial.print(F("OptoIn8-I2C failed HIGH on bit "));
      Serial.println(testBit);
      Serial.print(F("Read back on  "));
      Serial.println(testBit);
    }
    testBit <<= 1;
  }
  for (int loopVal = 14; loopVal < 16; loopVal++) // Uses A0, A1
  {
    digitalWrite(loopVal, LOW);
    pinMode(loopVal, OUTPUT);
    digitalWrite(loopVal, LOW);
    readVal = readOptoIn8();
    if ((readVal & testBit) != testBit)
    {
      testPass = 0;
      Serial.print(F("OptoIn8-I2C failed LOW on bit "));
      Serial.println(testBit);
    }
    digitalWrite(loopVal, HIGH);
    delay(10);
    readVal = readOptoIn8();
    if ((readVal & testBit) == testBit)
    {
      testPass = 0;
      Serial.print(F("OptoIn8-I2C failed HIGH on bit "));
      Serial.println(testBit);
      Serial.print(F("Read back on  "));
      Serial.println(testBit);
    }
    testBit <<= 1;
  }
  if (testPass)
    return 0;
  else
    return 1;
}

//////////////////////////////////////////////////////////////////////////////////////
// OptoOut8-I2C card
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
// void initOO8pins(void)
//////////////////////////////////////////////////////////////////////////////////////

void initOO8pins(void)
{
  Adafruit_MCP23008 mcpOO8;
  mcpOO8.begin();               // use default address 0
  int loopCnt;
  for (loopCnt = 0; loopCnt < 8; loopCnt++)
  {
    mcpOO8.digitalWrite(loopCnt, HIGH);
    mcpOO8.pinMode(loopCnt, OUTPUT);
  }
  for (loopCnt = 2; loopCnt < 16; loopCnt++)
    pinMode(loopCnt, INPUT);
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t loopBackTestOptoOut8(void) - Test the OptoOut8-I2C card
// Puts out 8 bits on OptoOut8-I2C card
// Reads the 8 bits on Arduino pins
// Arduino Input lines are D2-D5, D7, D8, D14(A0), D15(A1)
// Looks at the returned values on the OptoIn8-I2C
//////////////////////////////////////////////////////////////////////////////////////

uint8_t loopBackTestOptoOut8(void)
{
  //  Serial.println(F("Testing OptoOut8-I2C card"));

  Adafruit_MCP23008 mcpOO8;
  mcpOO8.begin();               // use default address 0
  initOO8pins();
  uint8_t readVal;
  int testPass = 1;;
  uint8_t testChannel = 0;
  int testBit = 0x1;
  delay(2);
  for (uint8_t loopVal = 2; loopVal < 6; loopVal++)
  {
    mcpOO8.digitalWrite(testChannel, HIGH);
    delayMicroseconds(15);
    readVal = digitalRead(loopVal);
    if (readVal != HIGH)
    {
      testPass = 0;
      Serial.print(F("OptoOut8-I2C failed HIGH on bit "));
      Serial.println(testChannel);
    }
    mcpOO8.digitalWrite(testChannel, LOW);
    delayMicroseconds(15);
    readVal = digitalRead(loopVal);
    if (readVal != LOW)
    {
      testPass = 0;
      Serial.print(F("OptoOut8-I2C failed LOW on bit "));
      Serial.println(testChannel);
    }
    testBit <<= 1;
    testChannel++;
  }
  for (uint8_t loopVal = 7; loopVal < 9; loopVal++)
  {
    mcpOO8.digitalWrite(testChannel, HIGH);
    delayMicroseconds(15);
    readVal = digitalRead(loopVal);
    if (readVal != HIGH)
    {
      testPass = 0;
      Serial.print(F("OptoOut8-I2C failed HIGH on bit "));
      Serial.println(testChannel);
    }
    mcpOO8.digitalWrite(testChannel, LOW);
    delayMicroseconds(15);
    readVal = digitalRead(loopVal);
    if (readVal != LOW)
    {
      testPass = 0;
      Serial.print(F("OptoOut8-I2C failed LOW on bit "));
      Serial.println(testChannel);
    }
    testBit <<= 1;
    testChannel++;
  }
  for (uint8_t loopVal = 14; loopVal < 16; loopVal++)
  {
    mcpOO8.digitalWrite(testChannel, HIGH);
    delayMicroseconds(15);
    readVal = digitalRead(loopVal);
    if (readVal != HIGH)
    {
      testPass = 0;
      Serial.print(F("OptoOut8-I2C failed HIGH on bit "));
      Serial.println(testChannel);
    }
    mcpOO8.digitalWrite(testChannel, LOW);
    delayMicroseconds(15);
    readVal = digitalRead(loopVal);
    if (readVal != LOW)
    {
      testPass = 0;
      Serial.print(F("OptoOut8-I2C failed LOW on bit "));
      Serial.println(testChannel);
    }
    testBit <<= 1;
    testChannel++;
  }
  if (testPass)
    return 0;
  else
    return 1;
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t loopBackTestDigio128(void) -
//////////////////////////////////////////////////////////////////////////////////////

uint8_t loopBackTestDigio128(void)
{
  Digio128 Dio128;    // Call the class constructor for the DigIO-128 card
  Dio128.begin();      // connects to the 8 MCP23017 parts

  for (uint8_t port = 0; port < 128; port++)
  {
    Dio128.pinMode(port, INPUT_PULLUP);
  }
  uint8_t testPass = 1;
  for (uint8_t chip = 0; chip < 8; chip += 2)
  {
    for (uint8_t port = 0; port < 16; port++)
    {

      Dio128.pinMode((chip * 16) + port, OUTPUT);
      Dio128.pinMode(((chip + 1) * 16) + 15 - port, INPUT);

      delay(2);
      Dio128.digitalWrite((chip * 16) + port, HIGH);
      delay(2);
      if (Dio128.digitalRead(((chip + 1) * 16) + 15 - port) != HIGH)
      {
        Serial.print(F("Error on chip "));
        Serial.print(chip);
        Serial.print(F(" and port "));
        Serial.print(port);
        Serial.println(F(" Expected High"));
        testPass = 0;
      }
      Dio128.digitalWrite((chip * 16) + port, LOW);
      delay(2);
      if (Dio128.digitalRead(((chip + 1) * 16) + 15 - port) != LOW)
      {
        Serial.print(F("Error on chip "));
        Serial.print(chip);
        Serial.print(F(" and port "));
        Serial.print(port);
        Serial.println(F(" Expected LOW"));
        testPass = 0;
      }
      Dio128.pinMode((chip * 16) + port, INPUT);
      delay(2);
    }
  }
  if (testPass)
    return 0;
  else
    return 1;
}

