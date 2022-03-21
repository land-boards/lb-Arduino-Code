//////////////////////////////////////////////////////////////////////////////////////
// ODAS card internal loopback test code
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t internalLBTestCard(void) -
//  Set all pins to inputs
//  Write to OLATAB registers
//  Read-back from OLATAB registers
//  Bounce a 1 across all the output lines
//  Returns
//    TEST_PASSED
//    TEST_FAILED
//////////////////////////////////////////////////////////////////////////////////////

uint8_t internalLBTestCard(void)
{
  uint8_t portNum;
  ODASTSTR_I2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  // Check that the I2C address(es) is(are) present
  switch (boardType)
  {
    case OPTOIN8I2C_CARD:
    case OPTOOUT8I2C_CARD:
    case I2CIO8X_CARD:
    case DIGIO16I2C_CARD:
    case PROTO16I2C_CARD:
    case ODASRELAY16_CARD:
      if (checkI2CAddr(0x20) != 0)
      {
        Serial.println(F("ERROR - I2C at 0x20 UUT Card not detected"));
        return TEST_FAILED;
      }
      break;
    case DIGIO32I2C_CARD:
      for (portNum = 0x20; portNum < 0x22; portNum++)
      {
        if (checkI2CAddr(portNum) != 0)
        {
          Serial.print(F("ERROR - I2C at "));
          Serial.print(portNum,HEX);
          Serial.println(F(" UUT Card not detected"));
          return TEST_FAILED;
        }
      }
      break;
    case DIGIO128_CARD:
      for (portNum = 0x20; portNum < 0x28; portNum++)
      {
        if (checkI2CAddr(portNum) != 0)
        {
          Serial.print(F("ERROR - I2C at "));
          Serial.print(portNum,HEX);
          Serial.println(F(" UUT Card not detected"));
          return TEST_FAILED;
        }
      }
      break;
    case DIGIO128_64_CARD:
      for (portNum = 0x20; portNum < 0x24; portNum++)
      {
        if (checkI2CAddr(portNum) != 0)
        {
          Serial.print(F("ERROR - I2C at "));
          Serial.print(portNum,HEX);
          Serial.println(F(" UUT Card not detected"));
          return TEST_FAILED;
        }
      }
      break;
  }
  switch (boardType)
  {
    // Cards with single MCP23008 parts
    case OPTOIN8I2C_CARD:
    case OPTOOUT8I2C_CARD:
      return (intLBTstSingleMCP23008());
      break;
    case I2CIO8_CARD:
      Serial.println(F("Testing UUT single MCP23008 card"));
      return (intLBTstI2CIO8());
      break;
    case I2CIO8X_CARD:
      // Serial.println(F("Testing UUT I2CIO8-X card"));
      return (intLBTstI2CIO8X());
      break;
    // Cards with single MCP23017 parts
    case DIGIO16I2C_CARD:
    case PROTO16I2C_CARD:
    case ODASRELAY16_CARD:
      Serial.println(F("Testing UUT single MCP23017 card"));
      return (intLBTstSingleMCP23017());
      break;
    // Cards with two MCP23017 parts
    case DIGIO32I2C_CARD:
      Serial.println(F("Testing UUT DIGIO32 - I2C card"));
      return (internaltestDigio32Card());
      break;
    // Cards with 8 MCP23017 parts
    case DIGIO128_CARD:
      Serial.println(F("Testing UUT DIGIO-128 card"));
      return (internalLBTestDIGIO128_CARD());
      break;
    case DIGIO128_64_CARD:
      Serial.println(F("Testing UUT DIGIO - 64 card"));
      return (internalextLBTestDIGIO128_64_CARD());
      break;
    case ODASPSOC5_CARD:
      Serial.println(F("Not supported at present"));
      break;
    case NEW_CARD:
      Serial.println(F("Not supported at present"));
      break;
    default:
      Serial.println(F("Undefined board type"));
      return 1;
      break;
  }
  ODASTSTR_I2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  return 0; // fail
}

//////////////////////////////////////////////////////////////////////////////////////
//  void intLBTstI2CIO8(void)
//  Write to the LED bits, read back the bits to verify access OK
//  Return value:
//    TEST_PASSED
//    TEST_FAILED
//////////////////////////////////////////////////////////////////////////////////////

uint8_t intLBTstI2CIO8(void)
{
  uint8_t rdVal;
//  Serial.println(F("Testing I2CIO-8 card"));
  i2cio8Card.writeLED(0,HIGH);
  rdVal = i2cio8Card.readGPIO();
  if ((rdVal & 0x01) != 0x01)
    return TEST_FAILED;
  i2cio8Card.writeLED(0,LOW);
  rdVal = i2cio8Card.readGPIO();
  if ((rdVal & 0x01) != 0x00)
    return TEST_FAILED;

  i2cio8Card.writeLED(1,HIGH);
  rdVal = i2cio8Card.readGPIO();
  if ((rdVal & 0x02) != 0x02)
    return TEST_FAILED;
  i2cio8Card.writeLED(1,LOW);
  rdVal = i2cio8Card.readGPIO();
  if ((rdVal & 0x02) != 0x00)
    return TEST_FAILED;
    
  i2cio8Card.writeLED(2,HIGH);
  rdVal = i2cio8Card.readGPIO();
  if ((rdVal & 0x04) != 0x04)
    return TEST_FAILED;
  i2cio8Card.writeLED(2,LOW);
  rdVal = i2cio8Card.readGPIO();
  if ((rdVal & 0x04) != 0x00)
    return TEST_FAILED;
    
  i2cio8Card.writeLED(3,HIGH);
  rdVal = i2cio8Card.readGPIO();
  if ((rdVal & 0x08) != 0x08)
    return TEST_FAILED;
  i2cio8Card.writeLED(3,LOW);
  rdVal = i2cio8Card.readGPIO();
  if ((rdVal & 0x08) != 0x00)
    return TEST_FAILED;
    
  return TEST_PASSED;
}

//////////////////////////////////////////////////////////////////////////////////////
//  void intLBTstI2CIO8X(void)
//  Write to the LED bits, read back the bits to verify access OK
//  Return value:
//    TEST_PASSED
//    TEST_FAILED
//////////////////////////////////////////////////////////////////////////////////////

uint8_t intLBTstI2CIO8X(void)
{
  uint8_t rdVal;
  uint8_t testBit;
  //Serial.println(F("Testing I2CIO-8X card internal"));
  ODASTSTR_I2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  delay(2);
  for (testBit = 0; testBit < 8; testBit++)
    i2cio8xCard.pinMode(testBit,OUTPUT);
  for (testBit = 0; testBit < 8; testBit++)
  {
    i2cio8xCard.digitalWrite(testBit,HIGH);
    delay(2);
    rdVal = i2cio8xCard.digitalRead(testBit);
    if (rdVal != HIGH)
    {
      Serial.print(F("intLBTstI2CIO8X() Test failed, Wrote 1, Read "));
      Serial.println(rdVal);
      return TEST_FAILED;
    }
    i2cio8xCard.digitalWrite(testBit,LOW);
    delay(2);
    rdVal = i2cio8xCard.digitalRead(testBit);
    if (rdVal != LOW)
    {
      Serial.print(F("intLBTstI2CIO8X() Test failed, Wrote 0, Read "));
      Serial.println(rdVal);
      return TEST_FAILED;
    }
  for (testBit = 0; testBit < 8; testBit++)
    i2cio8xCard.pinMode(testBit,INPUT_PULLUP);
  }
  return TEST_PASSED;
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t intLBTstSingleMCP23008(void) - Test card with MCP23008
// 
// 
//////////////////////////////////////////////////////////////////////////////////////

uint8_t intLBTstSingleMCP23008(void)
{
  int testResults = 1;
  uint8_t readVal;
  uint8_t loopVal;
  //  Serial.println(F("Internal tests OptoIn8 - I2C card"));
  for (loopVal = 0; loopVal < 8; loopVal++)
    singleMCP23008.pinMode(loopVal, INPUT);
  for (loopVal = 1; loopVal != 0; loopVal <<= 1)
  {
    singleMCP23008.writeOLAT(loopVal);
    readVal = singleMCP23008.readOLAT();
    if (readVal != loopVal)
    {
      Serial.print(F("Readback = "));
      Serial.println(readVal, HEX);
      testResults = TEST_FAILED;
    }
  }
  for (loopVal = 1; loopVal != 0; loopVal <<= 1)
  {
    singleMCP23008.writeOLAT(~loopVal);
    readVal = ~singleMCP23008.readOLAT();
    if (readVal != loopVal)
    {
      Serial.print(F("Readback = "));
      Serial.println(~readVal, HEX);
      testResults = TEST_FAILED;
    }
  }
  return testResults;
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t intLBTstSingleMCP23017(void) - Test the PROTO16-I2C card interrnals
//////////////////////////////////////////////////////////////////////////////////////

uint8_t intLBTstSingleMCP23017(void)
{
  uint8_t testResult = TEST_PASSED;
  uint16_t loopVal;
  uint16_t readBackVal;
  //  Serial.println(F("Testing UUT single MCP23017 card"));
  ODASTSTR_I2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  for (loopVal = 0; loopVal < 16; loopVal++)
    singleMCP23017.pinMode(loopVal, OUTPUT);
  for (loopVal = 1; loopVal != 0; loopVal <<= 1)
  {
    singleMCP23017.writeOLATAB(loopVal);
    //delay(10);
    readBackVal = singleMCP23017.readOLATAB();
    //delay(10);
    if (readBackVal != loopVal)
    {
      Serial.print(F("intLBTstSingleMCP23017: loopVal  = "));
      Serial.println(loopVal, HEX);
      Serial.print(F("intLBTstSingleMCP23017: Readback = "));
      Serial.println(readBackVal, HEX);
      testResult = TEST_FAILED;
    }
  }
  //delay(10);
  for (loopVal = 1; loopVal != 0; loopVal <<= 1)
  {
    singleMCP23017.writeOLATAB(~loopVal);
    //delay(10);
    readBackVal = ~singleMCP23017.readOLATAB();
    //delay(10);
    if (readBackVal != loopVal)
    {
      Serial.print(F("intLBTstSingleMCP23017: loopVal  = "));
      Serial.println(~loopVal, HEX);
      Serial.print(F("intLBTstSingleMCP23017: Readback = "));
      Serial.println(~readBackVal, HEX);
      testResult = TEST_FAILED;
    }
  }
  for (loopVal = 0; loopVal < 16; loopVal++)
    singleMCP23017.pinMode(loopVal, INPUT_PULLUP);
  delay(10);
  return (testResult);
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t internaltestDigio32Card()
//////////////////////////////////////////////////////////////////////////////////////

uint8_t internaltestDigio32Card(void)
{
  uint16_t wrBit;
  uint16_t rback16;
  uint8_t testResults = 0;
  for (wrBit = 0; wrBit < 32; wrBit++)
    Dio32.pinMode(wrBit, INPUT);
  for (wrBit = 1; wrBit != 0; wrBit <<= 1)
  {
    Dio32.writeOLATAB(0, wrBit);
    rback16 = Dio32.readOLATAB(0);
    if (rback16 != wrBit)
    {
      testResults = 1;
      Serial.print(F("internaltestDigio32Card(): Chip 0 Wrote bit: 0x"));
      Serial.println(wrBit, HEX);
      Serial.print(F("internaltestDigio32Card(): Chip 0 Got back: 0x"));
      Serial.println(rback16, HEX);
    }
  }
  for (wrBit = 0xfffe; wrBit != 0; wrBit <<= 1)
  {
    Dio32.writeOLATAB(0, wrBit);
    rback16 = Dio32.readOLATAB(0);
    if (rback16 != wrBit)
    {
      testResults = 1;
      Serial.print(F("internaltestDigio32Card(): Chip 0 (High) Wrote bit: 0x"));
      Serial.println(wrBit, HEX);
      Serial.print(F("internaltestDigio32Card(): Chip 0 (High) Got back: 0x"));
      Serial.println(rback16, HEX);
    }
  }
  for (wrBit = 1; wrBit != 0; wrBit <<= 1)
  {
    Dio32.writeOLATAB(1, wrBit);
    rback16 = Dio32.readOLATAB(1);
    if (rback16 != wrBit)
    {
      testResults = 1;
      Serial.print(F("internaltestDigio32Card(): Chip 1 Wrote bit: 0x"));
      Serial.println(wrBit, HEX);
      Serial.print(F("internaltestDigio32Card(): Chip 1 Got back: 0x"));
      Serial.println(rback16, HEX);
    }
  }
  for (wrBit = 0xfffe; wrBit != 0; wrBit <<= 1)
  {
    Dio32.writeOLATAB(1, wrBit);
    rback16 = Dio32.readOLATAB(1);
    if (rback16 != wrBit)
    {
      testResults = 1;
      Serial.print(F("internaltestDigio32Card(): Chip 1 Wrote bit: 0x"));
      Serial.println(wrBit, HEX);
      Serial.print(F("internaltestDigio32Card(): Chip 1 Got back: 0x"));
      Serial.println(rback16, HEX);
    }
  }
  return testResults;
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t internalLBTestDIGIO128_CARD(void) -
//////////////////////////////////////////////////////////////////////////////////////

uint8_t internalLBTestDIGIO128_CARD(void)
{
  uint8_t testResults = 1;
  for (uint8_t port = 0; port < 128; port++)
    Dio128.pinMode(port, INPUT_PULLUP);
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
        testResults = 0;
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
        testResults = 0;
      }
      Dio128.pinMode((chip * 16) + port, INPUT);
      delay(2);
    }
  }
  if (testResults)
    return 0;
  else
    return 1;
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t internalextLBTestDIGIO128_64_CARD(void) -
//////////////////////////////////////////////////////////////////////////////////////

uint8_t internalextLBTestDIGIO128_64_CARD(void)
{
  uint8_t testResults = 1;
  for (uint8_t port = 0; port < 64; port++)
    Dio128_64.pinMode(port, INPUT_PULLUP);
  for (uint8_t chip = 0; chip < 4; chip += 2)
  {
    for (uint8_t port = 0; port < 16; port++)
    {

      Dio128_64.pinMode((chip * 16) + port, OUTPUT);
      Dio128_64.pinMode(((chip + 1) * 16) + 15 - port, INPUT);

      delay(2);
      Dio128_64.digitalWrite((chip * 16) + port, HIGH);
      delay(2);
      if (Dio128_64.digitalRead(((chip + 1) * 16) + 15 - port) != HIGH)
      {
        Serial.print(F("Error on chip "));
        Serial.print(chip);
        Serial.print(F(" and port "));
        Serial.print(port);
        Serial.println(F(" Expected High"));
        testResults = 0;
      }
      Dio128_64.digitalWrite((chip * 16) + port, LOW);
      delay(2);
      if (Dio128_64.digitalRead(((chip + 1) * 16) + 15 - port) != LOW)
      {
        Serial.print(F("Error on chip "));
        Serial.print(chip);
        Serial.print(F(" and port "));
        Serial.print(port);
        Serial.println(F(" Expected LOW"));
        testResults = 0;
      }
      Dio128_64.pinMode((chip * 16) + port, INPUT);
      delay(2);
    }
  }
  if (testResults)
    return 0;
  else
    return 1;
}
