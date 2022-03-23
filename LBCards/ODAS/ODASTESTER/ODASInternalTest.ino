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
    case SWLEDX8_I2C_CARD:
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
    case I2CIO8_CARD:
    case I2CIO8X_CARD:
      Serial.println(F("Testing UUT single MCP23008 card"));
      return (testInternalMCP23008(0x20));
      break;
    // Cards with single MCP23017 parts but no EPROM
    case DIGIO16I2C_CARD:
    case PROTO16I2C_CARD:
    case ODASRELAY16_CARD:
    case SWLEDX8_I2C_CARD:
      Serial.println(F("Testing UUT single MCP23017 card"));
      return (testInternalMCP23017(0x20));
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
// uint8_t internaltestDigio32Card()
//////////////////////////////////////////////////////////////////////////////////////

uint8_t internaltestDigio32Card(void)
{
  uint8_t testResults;
  testResults = testInternalMCP23017(0x20);
  if (testResults == TEST_FAILED)
    return TEST_FAILED;
  testResults = testInternalMCP23017(0x21);
  if (testResults == TEST_FAILED)
    return TEST_FAILED;
  return TEST_PASSED;
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t internalLBTestDIGIO128_CARD(void) -
//////////////////////////////////////////////////////////////////////////////////////

uint8_t internalLBTestDIGIO128_CARD(void)
{
  uint8_t testResults;
  testResults = testInternalMCP23017(0x20);
  if (testResults == TEST_FAILED)
    return TEST_FAILED;
  testResults = testInternalMCP23017(0x21);
  if (testResults == TEST_FAILED)
    return TEST_FAILED;
  testResults = testInternalMCP23017(0x22);
  if (testResults == TEST_FAILED)
    return TEST_FAILED;
  testResults = testInternalMCP23017(0x23);
  if (testResults == TEST_FAILED)
    return TEST_FAILED;
  testResults = testInternalMCP23017(0x24);
  if (testResults == TEST_FAILED)
    return TEST_FAILED;
  testResults = testInternalMCP23017(0x25);
  if (testResults == TEST_FAILED)
    return TEST_FAILED;
  testResults = testInternalMCP23017(0x26);
  if (testResults == TEST_FAILED)
    return TEST_FAILED;
  testResults = testInternalMCP23017(0x27);
  if (testResults == TEST_FAILED)
    return TEST_FAILED;
  return TEST_PASSED;
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t internalextLBTestDIGIO128_64_CARD(void) -
//////////////////////////////////////////////////////////////////////////////////////

uint8_t internalextLBTestDIGIO128_64_CARD(void)
{
  uint8_t testResults;
  testResults = testInternalMCP23017(0x20);
  if (testResults == TEST_FAILED)
    return TEST_FAILED;
  testResults = testInternalMCP23017(0x21);
  if (testResults == TEST_FAILED)
    return TEST_FAILED;
  testResults = testInternalMCP23017(0x22);
  if (testResults == TEST_FAILED)
    return TEST_FAILED;
  testResults = testInternalMCP23017(0x23);
  if (testResults == TEST_FAILED)
    return TEST_FAILED;
  return TEST_PASSED;
}

//////////////////////////////////////////////////////////////////////////////////////
//  uint8_t testInternalMCP23008(uint8_t addr) - Test internal access
//////////////////////////////////////////////////////////////////////////////////////

uint8_t testInternalMCP23008(uint8_t addr)
{
  uint8_t savePUPReg;
  uint8_t testVal;
  uint8_t retVal = TEST_PASSED;
  savePUPReg = read8_MCP_I2C(addr,0x06);      // Save MCP23008 GPPU = 0x06
  for (testVal = 1; testVal != 0; testVal <<= 1)
  {
    write8_MCP_I2C(addr,0x06,testVal);
    if (read8_MCP_I2C(addr,0x06) != testVal)
      retVal = TEST_FAILED;
  }
  write8_MCP_I2C(addr,0x06,savePUPReg);     // Restore GPPU
  return retVal;
}

//////////////////////////////////////////////////////////////////////////////////////
//  uint8_t testInternalMCP23017(uint8_t addr) - Test internal access
//////////////////////////////////////////////////////////////////////////////////////

uint8_t testInternalMCP23017(uint8_t addr)
{
  uint8_t savePUPReg;
  uint8_t testVal;
  uint8_t retVal = TEST_PASSED;
  savePUPReg = read8_MCP_I2C(addr,0x0c);      // Save MCP23017 GPPU = 0x0c
  for (testVal = 1; testVal != 0; testVal <<= 1)
  {
    write8_MCP_I2C(addr,0x0c,testVal);
    if (read8_MCP_I2C(addr,0x0c) != testVal)
      retVal = TEST_FAILED;
  }
  write8_MCP_I2C(addr,0x0c,savePUPReg);     // Restore GPPU
  return retVal;
}

////////////////////////////////////////////////////////////////////////////
//  uint8_t read8_MCP_I2C(uint8_t i2caddr, uint8_t regAddr)
//  Read a byte from MCP230xx part
//  Passed variables
//    i2caddr - The I2C address (from 0x20 - 0x27 on MCP230xx parts)
//    regAddr - The register offset in the part
//  Returns:
//    byte value that was read
//  MCP230xx parts have an indirect register access method
//  https://www.arduino.cc/en/Reference/WireRequestFrom
////////////////////////////////////////////////////////////////////////////

uint8_t read8_MCP_I2C(uint8_t i2caddr, uint8_t regAddr) 
{
  Wire.beginTransmission(i2caddr);
  Wire.write((uint8_t)regAddr); 
  Wire.endTransmission();
  Wire.requestFrom(i2caddr, 1);   // get 1 byte
  return (uint8_t)Wire.read();
}

////////////////////////////////////////////////////////////////////////////
//  void write8_MCP_I2C(uint8_t i2caddr, uint8_t regAddr, uint8_t value)
//  Write to MCP230xx part
//  Passed variables
//    i2caddr - The I2C address (from 0x20 - 0x27 on MCP230xx parts)
//    regAddr - The register offset in the part
//    value - 8-bit value to write
//  MCP230xx parts have an indirect register access method
////////////////////////////////////////////////////////////////////////////

void write8_MCP_I2C(uint8_t i2caddr, uint8_t regAddr, uint8_t value) 
{
  Wire.beginTransmission(i2caddr);
  Wire.write((uint8_t)regAddr);
  Wire.write((uint8_t)value);
  Wire.endTransmission();
}
