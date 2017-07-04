//////////////////////////////////////////////////////////////////////////////////////
// ODAS card loopback test code
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t loopBackTestCard(void) -
//////////////////////////////////////////////////////////////////////////////////////

uint8_t loopBackTestCard(void)
{
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  switch (boardType)
  {
    case DIGIO16I2C_CARD:
      return (testDigio16Card());
      break;
    case DIGIO128_CARD:
      return (loopBackTestDIGIO128_CARD());
      break;
    case OPTOIN8I2C_CARD:
      return (loopBackTestOptoIn8());
      break;
    case OPTOOUT8I2C_CARD:
      return (loopBackTestOptoOut8());
      break;
    case DIGIO32I2C_CARD:
      return (testDigio32Card());
      break;
    case PROTO16I2C_CARD:
      return (testProto16());
      break;
    case ODASRELAY16_CARD:
      return (testProto16());
      break;
    case ODASPSOC5_CARD:
      Serial.println(F("Not supported at present"));
      break;
    case I2CIO8_CARD:
      return (testI2CIO8());
      break;
    case I2CIO8X_CARD:
      return (testI2CIO8X());
      break;
    case SWLEDX8_I2C_CARD:
      return(testSwLedX8());
      break;
    case OPTOFST_SML_NON_INVERTING_CARD:
      return(testOptoFastSmallNonInverting());
      break;
    case OPTOFST_SML_INVERTING_CARD:
      return(testOptoFastSmallInverting());
      break;
    case NEW_CARD:
      Serial.println(F("Not supported at present"));
      break;
    default:
      Serial.println(F("Undefined board type"));
      return 1;
      break;
  }
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  return 1; // fail
}

//////////////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////////////

uint8_t testOptoFastSmallInverting(void)
{
  uint8_t port;
  uint8_t pass0fail1 = 0;
  myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
  for (port = 0; port < 4; port++)   // Set all inputs to Pullup 
    Dio32.pinMode(port, OUTPUT);
  for (port = 8; port < 12; port++)   // Set all inputs to Pullup 
    Dio32.pinMode(port, INPUT_PULLUP);
  for (port = 0; port < 4; port++)   // Set all inputs to Pullup 
  {
    Dio32.digitalWrite(port,LOW);
    if (Dio32.digitalRead(port+8) != HIGH)
    {
      Serial.print(F("Error on port "));
      Serial.print(port);
      Serial.println(F(" Expected High"));
      pass0fail1 = 1;
    }
    Dio32.digitalWrite(port,HIGH);
    if (Dio32.digitalRead(port+8) != LOW)
    {
      Serial.print(F("Error on port "));
      Serial.print(port);
      Serial.println(F(" Expected Low"));
      pass0fail1 = 1;
    }
  }
  return pass0fail1;
}

//////////////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////////////

uint8_t testOptoFastSmallNonInverting(void)
{
  uint8_t port;
  uint8_t pass0fail1 = 0;
  myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
  for (port = 0; port < 4; port++)   // Set all inputs to Pullup 
    Dio32.pinMode(port, OUTPUT);
  for (port = 8; port < 12; port++)   // Set all inputs to Pullup 
    Dio32.pinMode(port, INPUT_PULLUP);
  for (port = 0; port < 4; port++)   // Set all inputs to Pullup 
  {
    Dio32.digitalWrite(port,LOW);
    if (Dio32.digitalRead(port+8) != LOW)
    {
      Serial.print(F("Error on port "));
      Serial.print(port);
      Serial.println(F(" Expected Low"));
      pass0fail1 = 1;
    }
    Dio32.digitalWrite(port,HIGH);
    if (Dio32.digitalRead(port+8) != HIGH)
    {
      Serial.print(F("Error on port "));
      Serial.print(port);
      Serial.println(F(" Expected High"));
      pass0fail1 = 1;
    }
  }
  return pass0fail1;
}

//////////////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////////////

uint8_t testSwLedX8(void)
{
  uint8_t loopCnt;
  Serial.println(F("Testing SWLEDX8-I2C card"));
  Serial.println(F("Slide switches verify lights"));
  Serial.println(F("Hit any key to exit"));
  for (loopCnt = 0; loopCnt < 8; loopCnt++)
    singleMCP23017.pinMode(loopCnt,INPUT);
  for (loopCnt = 8; loopCnt < 16; loopCnt++)
  {
    singleMCP23017.digitalWrite(loopCnt,LOW);
    singleMCP23017.pinMode(loopCnt,OUTPUT);
  }
  while(Serial.available() == 0)
  {
    for (loopCnt=0;loopCnt<8;loopCnt++)
    {
      singleMCP23017.digitalWrite(loopCnt+8,singleMCP23017.digitalRead(loopCnt));
    }
  }
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t testProto16(void) - Test the PROTO16-I2C card
// This test is an internal loopback test since the pins are dependent on the wiring.
//////////////////////////////////////////////////////////////////////////////////////

uint8_t testProto16(void)
{
  uint8_t failed = 0;
  uint8_t loopCnt;
  uint16_t readBackVal;
//  Serial.println(F("Testing PROTO16-I2C card"));
  for (loopCnt = 0; loopCnt < 16; loopCnt++)
    singleMCP23017.pinMode(loopCnt,OUTPUT);
  singleMCP23017.writeGPIOAB(0x55aa);
  readBackVal = singleMCP23017.readGPIOAB();
  if (readBackVal != 0x55aa)
  {
    Serial.print(F("Readback="));
    Serial.println(readBackVal);
    failed = 1;
  }
  delay(10);
  singleMCP23017.writeGPIOAB(0xaa55);
  readBackVal = singleMCP23017.readGPIOAB();
  if (readBackVal != 0xaa55)
  {
    Serial.print(F("Readback="));
    Serial.println(readBackVal);
    failed = 1;
  }
  for (loopCnt = 0; loopCnt < 16; loopCnt++)
    singleMCP23017.pinMode(loopCnt,INPUT);
  delay(1);
  return(failed);
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t testI2CIO8(void) - Test the I2CIO8 card
//////////////////////////////////////////////////////////////////////////////////////

uint8_t testI2CIO8(void)
{
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
// uint8_t testI2CIO8X(void)
//////////////////////////////////////////////////////////////////////////////////////

uint8_t testI2CIO8X(void)
{
  uint8_t jumpers;
//  Serial.println(F("I2CIO8X card"));
//  Serial.println(F("Install test jumper"));
//  Serial.println(F("Hit a key to stop test"));
  for (jumpers = 0; jumpers < 4; jumpers++)
    i2cio8xCard.pinMode(jumpers, INPUT);
  for (jumpers = 4; jumpers < 8; jumpers++)
    i2cio8xCard.pinMode(jumpers, OUTPUT);
  for (jumpers = 0; jumpers < 4; jumpers++)
  {
    i2cio8xCard.digitalWrite(jumpers + H4JUMPER, LOW);
    if (i2cio8xCard.digitalRead(jumpers) != LOW)
    {
      Serial.println(F("Failed LOW"));
      return 1;
    }
    i2cio8xCard.digitalWrite(jumpers + H4JUMPER, HIGH);
    if (i2cio8xCard.digitalRead(jumpers) != HIGH)
    {
      Serial.println(F("Failed HIGH"));
      return 1;
    }
  }
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t testDigio32Card() - Test the DIGIO32 card.
// Cable from UUT connector to the DIGIO32 card in the Test Station.
//////////////////////////////////////////////////////////////////////////////////////

uint8_t testDigio32Card(void)
{
  uint8_t port;
  uint8_t pass0fail1 = 0;
  myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
  for (port = 0; port < 32; port++)   // Set all inputs to Pullup 
    Dio32.pinMode(port, INPUT_PULLUP);
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  for (port = 0; port < 32; port++)
    Dio32.pinMode(port, OUTPUT);
  // Check bits to Low
  for (port = 0; port < 32; port++)
  {
    Dio32.digitalWrite(port, LOW);
    myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
    if (Dio32.digitalRead(port) != LOW)
    {
      Serial.print(F("Error on port "));
      Serial.print(port);
      Serial.println(F(" Expected Low"));
      pass0fail1 = 1;
    }
    myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  }
  // Check bits to High
  for (port = 0; port < 32; port++)
  {
    Dio32.digitalWrite(port, HIGH);
    myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
    if (Dio32.digitalRead(port) != HIGH)
    {
      
      Serial.print(F("Error on port "));
      Serial.print(port);
      Serial.println(F(" Expected High"));
      pass0fail1 = 1;
    }
    myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  }
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  for (port = 0; port < 32; port++)
    Dio32.pinMode(port, INPUT);
  return pass0fail1;
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t testDigio16Card() - Test the DIGIO16 card.
// Cable from UUT connector to the DIGIO16 card in the Test Station.
//////////////////////////////////////////////////////////////////////////////////////

uint8_t testDigio16Card(void)
{
  uint8_t port;
  uint8_t pass0fail1 = 0;
  myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
  for (port = 0; port < 32; port++)   // Set all inputs to Pullup 
    Dio32.pinMode(port, INPUT_PULLUP);
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  for (port = 0; port < 16; port++)
    singleMCP23017.pinMode(port, OUTPUT);
  // Check bits to Low
  for (port = 0; port < 16; port++)
  {
    singleMCP23017.digitalWrite(port, LOW);
    myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
    if (Dio32.digitalRead(port) != LOW)
    {
      Serial.print(F("Error on port "));
      Serial.print(port);
      Serial.println(F(" Expected Low"));
      pass0fail1 = 1;
    }
    myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  }
  // Check bits to High
  for (port = 0; port < 16; port++)
  {
    singleMCP23017.digitalWrite(port, HIGH);
    myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
    if (Dio32.digitalRead(port) != HIGH)
    {
      
      Serial.print(F("Error on port "));
      Serial.print(port);
      Serial.println(F(" Expected High"));
      pass0fail1 = 1;
    }
    myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  }
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  for (port = 0; port < 16; port++)
    singleMCP23017.pinMode(port, INPUT);
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
  int loopCnt;
  for (loopCnt = 0; loopCnt < 8; loopCnt++)
  {
    singleMCP23008.pinMode(loopCnt, INPUT);
    singleMCP23008.pullUp(loopCnt, HIGH);  // turn on a 100K pullup internally
  }
}

//////////////////////////////////////////////////////////////////////////////////////
// Read a bit from the OptoIn8-I2C card
//////////////////////////////////////////////////////////////////////////////////////

unsigned char readOptoIn8(void)
{
  int loopVal;
  unsigned int rval = 0;
  for (loopVal = 0; loopVal < 8; loopVal++)
  {
    rval |= singleMCP23008.digitalRead(loopVal) & 0x1;
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
  int port;
  int testPass = 1;
  int testBit = 0x1;
  //  Serial.println(F("Testing OptoIn8-I2C card"));

  myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
  for (port = 0; port < 32; port++)   // Set all Test Station DIGIO32 inputs to Pullup 
  {
    Dio32.pinMode(port, OUTPUT);
    Dio32.digitalWrite(port,LOW);
  }
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  for (port = 0; port < 8; port++)   // Set all inputs to Pullup 
    singleMCP23008.pinMode(port, INPUT);
  for (int port = 0; port < 8; port++)
  {
    myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
    Dio32.digitalWrite(port, LOW);
    myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
    readVal = singleMCP23008.digitalRead(port);
    if (readVal != HIGH)
    {
      testPass = 0;
      Serial.print(F("OptoIn8-I2C failed LOW on bit "));
      Serial.println(testBit);
    }
    myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
    Dio32.digitalWrite(port, HIGH);
    delay(10);
    myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
    readVal = singleMCP23008.digitalRead(port);
    if (readVal != LOW)
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
  int loopCnt;
  for (loopCnt = 0; loopCnt < 8; loopCnt++)
  {
    singleMCP23008.digitalWrite(loopCnt, HIGH);
    singleMCP23008.pinMode(loopCnt, OUTPUT);
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
  initOO8pins();
  uint8_t readVal;
  int testPass = 1;;
  uint8_t testChannel = 0;
  int testBit = 0x1;
  delay(2);
  for (uint8_t loopVal = 2; loopVal < 6; loopVal++)
  {
    singleMCP23008.digitalWrite(testChannel, HIGH);
    delayMicroseconds(15);
    readVal = digitalRead(loopVal);
    if (readVal != HIGH)
    {
      testPass = 0;
      Serial.print(F("OptoOut8-I2C failed HIGH on bit "));
      Serial.println(testChannel);
    }
    singleMCP23008.digitalWrite(testChannel, LOW);
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
    singleMCP23008.digitalWrite(testChannel, HIGH);
    delayMicroseconds(15);
    readVal = digitalRead(loopVal);
    if (readVal != HIGH)
    {
      testPass = 0;
      Serial.print(F("OptoOut8-I2C failed HIGH on bit "));
      Serial.println(testChannel);
    }
    singleMCP23008.digitalWrite(testChannel, LOW);
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
    singleMCP23008.digitalWrite(testChannel, HIGH);
    delayMicroseconds(15);
    readVal = digitalRead(loopVal);
    if (readVal != HIGH)
    {
      testPass = 0;
      Serial.print(F("OptoOut8-I2C failed HIGH on bit "));
      Serial.println(testChannel);
    }
    singleMCP23008.digitalWrite(testChannel, LOW);
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
// uint8_t loopBackTestDIGIO128_CARD(void) -
//////////////////////////////////////////////////////////////////////////////////////

uint8_t loopBackTestDIGIO128_CARD(void)
{
  uint8_t testPass = 1;
//  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  for (uint8_t port = 0; port < 128; port++)
  {
    Dio128.pinMode(port, INPUT_PULLUP);
  }
  for (uint8_t chip = 0; chip < 8; chip += 2)
  {
    for (uint8_t port = 0; port < 16; port++)
    {

      Dio128.pinMode((chip << 4) + port, OUTPUT);
      Dio128.pinMode(((chip + 1) << 4) + 15 - port, INPUT_PULLUP);

      delay(2);
      Dio128.digitalWrite((chip << 4) + port, HIGH);
      delay(2);
      if (Dio128.digitalRead(((chip + 1) << 4) + 15 - port) != HIGH)
      {
        Serial.print(F("loopBackTestDIGIO128_CARD() 1: Error on chip "));
        Serial.print(chip);
        Serial.print(F(" and port "));
        Serial.print(port);
        Serial.println(F(" Expected High"));
        testPass = 0;
      }
      Dio128.digitalWrite((chip << 4) + port, LOW);
      delay(2);
      if (Dio128.digitalRead(((chip + 1) << 4) + 15 - port) != LOW)
      {
        Serial.print(F("loopBackTestDIGIO128_CARD() 2: Error on chip "));
        Serial.print(chip);
        Serial.print(F(" and port "));
        Serial.print(port);
        Serial.println(F(" Expected LOW"));
        testPass = 0;
      }
      Dio128.pinMode((chip << 4) + port, INPUT);
      delay(2);
    }
  }
  if (testPass)
    return 0;
  else
    return 1;
}

