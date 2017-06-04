//////////////////////////////////////////////////////////////////////////////////////
// ODAS card internal loopback test code
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t internalLoopBackTestCard(void) -
//////////////////////////////////////////////////////////////////////////////////////

uint8_t internalLoopBackTestCard(void)
{
  setMuxChannel(UUT_CARD_MUX_CH);
  switch (boardType)
  {
    case DIGIO16I2C_CARD:
      Serial.println(F("Not supported at present"));
      break;
    case DIGIO128_CARD:
      return (internalLoopBackTestDIGIO128_CARD());
      break;
    case DIGIO32I2C_CARD:
      return (internalLoopBackTestDigio32());
      break;
    case PROTO16I2C_CARD:
      return (internalLoopBackTestProto16());
      break;
    case OPTOIN8I2C_CARD:
      return (internalLoopBackTestOptoIn8());
      break;
    case OPTOOUT8I2C_CARD:
      return (internalLoopBackTestOptoOut8());
      break;
    case I2CIO8_CARD:
      return (internalLoopBackTestI2CIO8());
      break;
    case I2CIO8X_CARD:
      return (internalLoopBackTestI2CIO8X());
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
  setMuxChannel(UUT_CARD_MUX_CH);
  return 1; // fail
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t internalLoopBackTestDigio32()
//////////////////////////////////////////////////////////////////////////////////////

uint8_t internalLoopBackTestDigio32(void)
{
  uint8_t port;
  uint8_t pass0fail1 = 0;
  uint32_t wrBit;
  uint32_t rback32;
  uint8_t bit;
  Digio32 Dio32;
  Dio32.begin(0);
//  Serial.println(F("internalLoopBackTestDigio32() - reached function"));
  for (wrBit = 1; wrBit != 0; wrBit <<=1)
  {
    Dio32.write32(wrBit);
    rback32 = Dio32.readGPIOAB(1);
    rback32 <<= 16;
    rback32 |= Dio32.readGPIOAB(0);
    if (rback32 != wrBit)
    {
      Serial.print("Got back: ");
      Serial.println(rback32,HEX);
      return 1;
    }
  }
//  Serial.print("Upper Half");
//  Serial.println(rback32,HEX);
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t internalLoopBackTestProto16(void) - Test the PROTO16-I2C card
//////////////////////////////////////////////////////////////////////////////////////

uint8_t internalLoopBackTestProto16(void)
{
  uint8_t failed = 0;
  uint8_t loopCnt;
  uint16_t readBackVal;
//  Serial.println(F("Testing PROTO16-I2C card"));
  Adafruit_MCP23017 mcp;
  mcp.begin(0);      // use default address
  for (loopCnt = 0; loopCnt < 16; loopCnt++)
    mcp.pinMode(loopCnt,OUTPUT);
  mcp.writeGPIOAB(0x55aa);
  readBackVal = mcp.readGPIOAB();
  if (readBackVal != 0x55aa)
  {
    Serial.print(F("Readback="));
    Serial.println(readBackVal);
    failed = 1;
  }
  delay(10);
  mcp.writeGPIOAB(0xaa55);
  readBackVal = mcp.readGPIOAB();
  if (readBackVal != 0xaa55)
  {
    Serial.print(F("Readback="));
    Serial.println(readBackVal);
    failed = 1;
  }
  for (loopCnt = 0; loopCnt < 16; loopCnt++)
    mcp.pinMode(loopCnt,INPUT);
  delay(10);
  return(failed);
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t internalLoopBackTestI2CIO8(void) - Test the I2CIO8 card
//////////////////////////////////////////////////////////////////////////////////////

uint8_t internalLoopBackTestI2CIO8(void)
{
  LandBoards_I2CIO8 i2cio8Card;
  i2cio8Card.begin(0);
  Serial.println(F("I2CIO8 card tests"));
  Serial.println(F("Move jumper across H5-H8, observe LEDs D0-D3"));
  Serial.println(F("Verify Int LED blinks"));
  Serial.println(F("Hit a key to stop test"));
  while (1)
  {
    i2cio8Card.writeLED(LED0, !i2cio8Card.readJumper(H4JUMPER));
    i2cio8Card.writeLED(LED1, !i2cio8Card.readJumper(H5JUMPER));
    i2cio8Card.writeLED(LED2, !i2cio8Card.readJumper(H6JUMPER));
    i2cio8Card.writeLED(LED3, !i2cio8Card.readJumper(H7JUMPER));
    delay(250);
    if (Serial.available() > 0)
    {
      Serial.read();
      return 0;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t internalLoopBackTestI2CIO8X(void)
//////////////////////////////////////////////////////////////////////////////////////

uint8_t internalLoopBackTestI2CIO8X(void)
{
  uint8_t jumpers;
  LandBoards_I2CIO8X i2cio8Card;
  i2cio8Card.begin(0);
//  Serial.println(F("I2CIO8X card"));
//  Serial.println(F("Install test jumper"));
//  Serial.println(F("Hit a key to stop test"));
  for (jumpers = 0; jumpers < 4; jumpers++)
    i2cio8Card.pinMode(jumpers, INPUT);
  for (jumpers = 4; jumpers < 8; jumpers++)
    i2cio8Card.pinMode(jumpers, OUTPUT);
  for (jumpers = 0; jumpers < 4; jumpers++)
  {
    i2cio8Card.digitalWrite(jumpers + H4JUMPER, LOW);
    if (i2cio8Card.digitalRead(jumpers) != LOW)
    {
      Serial.println(F("Failed LOW"));
      return 1;
    }
    i2cio8Card.digitalWrite(jumpers + H4JUMPER, HIGH);
    if (i2cio8Card.digitalRead(jumpers) != HIGH)
    {
      Serial.println(F("Failed HIGH"));
      return 1;
    }
  }
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////
// OptoIn8-I2C card test code
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t internalLoopBackTestOptoIn8(void) - Test the OptoIn8-I2C card
// Puts out 8 bit test vector on Arduino pins
//  Arduino Output lines aew D2-D5, D7, D8, D14(A0), D15(A1)
// Looks at the returned values on the OptoIn8-I2C
//////////////////////////////////////////////////////////////////////////////////////

uint8_t internalLoopBackTestOptoIn8(void)
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
// uint8_t internalLoopBackTestOptoOut8(void) - Test the OptoOut8-I2C card
// Puts out 8 bits on OptoOut8-I2C card
// Reads the 8 bits on Arduino pins
// Arduino Input lines are D2-D5, D7, D8, D14(A0), D15(A1)
// Looks at the returned values on the OptoIn8-I2C
//////////////////////////////////////////////////////////////////////////////////////

uint8_t internalLoopBackTestOptoOut8(void)
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
// uint8_t internalLoopBackTestDIGIO128_CARD(void) -
//////////////////////////////////////////////////////////////////////////////////////

uint8_t internalLoopBackTestDIGIO128_CARD(void)
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


