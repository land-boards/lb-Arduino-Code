////////////////////////////////////////////////////////////////////////////
//  ODASCardDetect - Functions related to ODAS card type detection
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// uint8_t checkI2CAddr(uint8_t addr) - Check that an I2C device is present
// Pass: addr - I2C address
// Returns:
//      0 : success
//      1 : data too long to fit in transmit buffer
//      2 : received NACK on transmit of address
//      3 : received NACK on transmit of data
//      4 : other error
////////////////////////////////////////////////////////////////////////////

uint8_t checkI2CAddr(uint8_t addr)
{
  Wire.beginTransmission(addr);
  return (Wire.endTransmission());
}

////////////////////////////////////////////////////////////////////////////
//  uint8_t checkIfMCP23017(uint8_t addr)
//  Check to see if the I2C part is a MCP23017
//    The GPU Pullup A register (internal register address 0x0c) is present
//    in a MCP23017 but not in a MCP23008.
//  Pass: addr - I2C address
//  Returns
//    0 : Not an MCP23017
//    1 : Likely an MCP23017
////////////////////////////////////////////////////////////////////////////

uint8_t checkIfMCP23017(uint8_t addr)
{
  // Write 0x55 to MCP23017_GPPUA (0x0c)
  Wire.beginTransmission(addr);
  Wire.write(0x0c);
  Wire.write(0x55);
  Wire.endTransmission(1);
  // Read back
  Wire.beginTransmission(addr);
  Wire.write(0x0c);
  Wire.endTransmission();
  Wire.requestFrom(addr,  1);
  if (Wire.read() == 0x55)
  {
    Serial.println(F("Detected MCP23017"));
    return 1;
  }
  else
  {
    Serial.println(F("Detected MCP23008"));
    return 0;
  }
}

//////////////////////////////////////////////////////////
// uint8_t count0x20_I2CDevices(void)
// Returns
//    Number of I2C devices in 0x20-0x27 range
//////////////////////////////////////////////////////////

uint8_t count0x20_I2CDevices(void)
{
  uint8_t i2cDevCount = 0;
  uint8_t devAddr;
  for (devAddr = 0x20; devAddr < 0x28; devAddr++)
  {
    if (checkI2CAddr(devAddr) == 0)
    {
      i2cDevCount++;
    }
  }
  Serial.print(F("Count of I2C devices in range 0x20-0x27 on UUT = "));
  Serial.println(i2cDevCount, DEC);
  return (i2cDevCount);
}

//////////////////////////////////////////////////////////
// void selectBoardType(uint8_t i2cDevCount, uint8_t isMCP23017)
//  
//////////////////////////////////////////////////////////

void selectBoardType(uint8_t i2cDevCount, uint8_t isMCP23017)
{
  Serial.println(F("Select the board type (EEPROM)"));
  if ((i2cDevCount == 1) && (isMCP23017 == 1))
    Serial.println(F("1 - DIGIO16-I2C board"));
  if ((i2cDevCount == 8) && (isMCP23017 == 1))
    Serial.println(F("2 - DIGIO-128 board"));
  if ((i2cDevCount == 1) && (isMCP23017 == 0))
  {
    Serial.println(F("3 - OptoIn8-I2C board"));
    Serial.println(F("4 - OptoOut8-I2C board"));
  }
  if ((i2cDevCount == 2) && (isMCP23017 == 1))
  {
    Serial.println(F("5 - DIGIO32-I2C board"));
    Serial.println(F("6 - PROTO16-I2C board"));
  }
  if (i2cDevCount == 0)
    Serial.println(F("7 - ODAS-PSOC5 board"));
  if ((i2cDevCount == 1) && (isMCP23017 == 1))
    Serial.println(F("8 - ODAS-RELAY16 board"));
  if ((i2cDevCount == 4) && (isMCP23017 == 1))
    Serial.println(F("A - DIGIO-128/64 board"));
  Serial.println(F("9 - TBD board"));
  Serial.println(F("X - Boards without EEPROMs"));
  Serial.print(F("Select board > "));
  int incomingByte = 0;   // for incoming serial data

  while (Serial.available() > 0)
    Serial.read();
  while (Serial.available() == 0);
  if (Serial.available() > 0)
  {
    // read the incoming byte:
    incomingByte = Serial.read();
    Serial.write(incomingByte);
    Serial.println();
    switch (incomingByte)
    {
      case '1':
        {
          boardType = DIGIO16I2C_CARD;
          break;
        }
      case '2':
        {
          boardType = DIGIO128_CARD;
          break;
        }
      case '3':
        {
          boardType = OPTOIN8I2C_CARD;
          break;
        }
      case '4':
        {
          boardType = OPTOOUT8I2C_CARD;
          break;
        }
      case '5':
        {
          boardType = DIGIO32I2C_CARD;
          break;
        }
      case '6':
        {
          boardType = PROTO16I2C_CARD;
          break;
        }
      case '7':
        {
          boardType = ODASPSOC5_CARD;
          break;
        }
      case '8':
        {
          boardType = ODASRELAY16_CARD;
          break;
        }
      case '9':
        {
          boardType = NEW_CARD;
          break;
        }
      case 'A':
      case 'a':
        {
          boardType = DIGIO128_64_CARD;
          break;
        }
      case 'X':
      case 'x':
        {
          otherBoardType(-1,-1);
          break;
        }
      default:
        {
          Serial.println(F("Failed to select board type"));
          boardType = NONE;
        }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////
//  void otherBoardType(uint8_t i2cDevCount, uint8_t isMCP23017)
//////////////////////////////////////////////////////////////////////////////////////


void otherBoardType(uint8_t i2cDevCount, uint8_t isMCP23017)
{
  Serial.println(F("Select the board type (Other)"));
  if ((i2cDevCount == 1) && (isMCP23017 == 0))
  {
    Serial.println(F("1 - I2CIO8 board"));
    Serial.println(F("2 - I2CIO8X board"));
  }
  if (i2cDevCount == 0)
  {
    Serial.println(F("3 - SWLEDX8-I2C board"));
    Serial.println(F("4 - OPTOFast/Small Non-Inverting board"));
    Serial.println(F("5 - OPTOFast/Small Inverting board"));
    Serial.println(F("6 - I2C-RPT-01 board"));
    Serial.println(F("7 - I2C-RPT-08 board"));
    Serial.println(F("8 - OptoFastBi board"));
  }
  Serial.print(F("Select board > "));
  int incomingByte = 0;   // for incoming serial data

  while (Serial.available() > 0)
    Serial.read();
  while (Serial.available() == 0);
  if (Serial.available() > 0)
  {
    // read the incoming byte:
    incomingByte = Serial.read();
    Serial.write(incomingByte);
    Serial.println();
    switch (incomingByte)
    {
      case '1':
        {
          boardType = I2CIO8_CARD;
          break;
        }
      case '2':
        {
          boardType = I2CIO8X_CARD;
          break;
        }
      case '3':
        {
          boardType = SWLEDX8_I2C_CARD;
          break;
        }
      case '4':
        {
          boardType = OPTOFST_SML_NON_INVERTING_CARD;
          break;
        }
      case '5':
        {
          boardType = OPTOFST_SML_INVERTING_CARD;
          break;
        }
      case '6':
        {
          boardType = I2CRPT01_CARD;
          break;
        }
      case '7':
        {
          boardType = I2CRPT08_CARD;
          break;
        }
      case '8':
        {
          boardType = OPTOFSTBI_CARD;
          break;
        }
      default:
        {
          Serial.println(F("Failed to select board type"));
        }
    }
  }
}
