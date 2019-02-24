//////////////////////////////////////////////////////////////////////////////////////
// uint8_t readBitValue(uint8_t bitToCheck)
//////////////////////////////////////////////////////////////////////////////////////

uint8_t readBitValue(uint8_t bitToCheck)
{
  switch (boardType)
  {
    case DIGIO16I2C_CARD:
      break;
    case DIGIO128_CARD:
      return (readBitDIGIO128(bitToCheck));
      break;
    case DIGIO128_64_CARD:
      return (readBitDIGIO128_64(bitToCheck));
      break;
    case OPTOIN8I2C_CARD:
      return (readSingleMCP23008(bitToCheck));
      break;
    case OPTOOUT8I2C_CARD:
      break;
    case DIGIO32I2C_CARD:
      return (readBitDIGIO32(bitToCheck));
      break;
    case PROTO16I2C_CARD:
      break;
    case ODASRELAY16_CARD:
      break;
    case ODASPSOC5_CARD:
      break;
    case I2CIO8_CARD:
      break;
    case I2CIO8X_CARD:
      break;
    case NEW_CARD:
      Serial.println(F("Not supported at present"));
      break;
    default:
      Serial.println(F("Undefined board type"));
      return 1;
      break;
  }
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t readBitDIGIO128(uint8_t bitToCheck)
//////////////////////////////////////////////////////////////////////////////////////

uint8_t readBitDIGIO128(uint8_t bitToCheck)
{
  uint8_t rdVal;
  Serial.println(F("\nreadBitDIGIO128() - reached function"));
  Dio128.pinMode(bitToCheck, INPUT_PULLUP);
  rdVal = Dio128.digitalRead(bitToCheck);
  return (rdVal);
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t readBitDIGIO128_64(uint8_t bitToCheck)
//////////////////////////////////////////////////////////////////////////////////////

uint8_t readBitDIGIO128_64(uint8_t bitToCheck)
{
  uint8_t rdVal;
  Serial.println(F("\nreadBitDIGIO128() - reached function"));
  Dio128_64.pinMode(bitToCheck, INPUT_PULLUP);
  rdVal = Dio128_64.digitalRead(bitToCheck);
  return (rdVal);
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t readBitDIGIO32(uint8_t bitToCheck)
//////////////////////////////////////////////////////////////////////////////////////

uint8_t readBitDIGIO32(uint8_t bitToCheck)
{
  uint8_t rdVal;
  //  Serial.println(F("\nreadBitDIGIO32() - reached function"));
  rdVal = Dio32.digitalRead(bitToCheck);
  return (rdVal);
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t readSingleMCP23008(uint8_t bitToCheck)
//////////////////////////////////////////////////////////////////////////////////////

uint8_t readSingleMCP23008(uint8_t bitToCheck)
{
  uint8_t rdVal;
  //  Serial.println(F("\nreadBitDIGIO32() - reached function"));
  rdVal = singleMCP23008.digitalRead(bitToCheck);
  return (rdVal);
}

//////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////

void writeBitValue(uint8_t bitToCheck, uint8_t bitToWrite)
{
  switch (boardType)
  {
    case DIGIO16I2C_CARD:
      break;
    case DIGIO128_CARD:
      writeBitDIGIO128(bitToCheck, bitToWrite);
      break;
    case DIGIO128_64_CARD:
      writeBitDIGIO128_64(bitToCheck, bitToWrite);
      break;
    case OPTOIN8I2C_CARD:
      break;
    case OPTOOUT8I2C_CARD:
      break;
    case DIGIO32I2C_CARD:
      writeBitDIGIO32(bitToCheck, bitToWrite);
      break;
    case PROTO16I2C_CARD:
      break;
    case ODASPSOC5_CARD:
      break;
    case I2CIO8_CARD:
      break;
    case I2CIO8X_CARD:
      break;
    case NEW_CARD:
      Serial.println(F("Not supported at present"));
      break;
    default:
      Serial.println(F("Undefined board type"));
      return;
      break;
  }
}

//////////////////////////////////////////////////////////////////////////////////////
// void writeBitDIGIO32(uint8_t bitToCheck, uint8_t bitWeiteValue)
//////////////////////////////////////////////////////////////////////////////////////

void writeBitDIGIO32(uint8_t bitNumber, uint8_t bitValue)
{
  //  Serial.println(F("\writeBitDIGIO32() - reached function"));
  Dio32.pinMode(bitNumber, OUTPUT);
  Dio32.digitalWrite(bitNumber, bitValue);
}

//////////////////////////////////////////////////////////////////////////////////////
// void writeBitDIGIO128(uint8_t bitNumber, uint8_t bitValue)
//////////////////////////////////////////////////////////////////////////////////////

void writeBitDIGIO128(uint8_t bitNumber, uint8_t bitValue)
{
  //  Serial.println(F("\writeBitDIGIO128() - reached function"));
  Dio128.pinMode(bitNumber, OUTPUT);
  Dio128.digitalWrite(bitNumber, bitValue);
}

//////////////////////////////////////////////////////////////////////////////////////
// void writeBitDIGIO128_64(uint8_t bitNumber, uint8_t bitValue)
//////////////////////////////////////////////////////////////////////////////////////

void writeBitDIGIO128_64(uint8_t bitNumber, uint8_t bitValue)
{
  //  Serial.println(F("\writeBitDIGIO128() - reached function"));
  Dio128_64.pinMode(bitNumber, OUTPUT);
  Dio128_64.digitalWrite(bitNumber, bitValue);
}
