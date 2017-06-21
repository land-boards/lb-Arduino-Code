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
      return(readBitDIGIO128(bitToCheck));
      break;
    case OPTOIN8I2C_CARD:
      break;
    case OPTOOUT8I2C_CARD:
      break;
    case DIGIO32I2C_CARD:
      return(readBitDIGIO32(bitToCheck));
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
      return 1;
      break;
  }
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t readBitDIGIO128(uint8_t bitToCheck)
//////////////////////////////////////////////////////////////////////////////////////

uint8_t readBitDIGIO128(uint8_t bitToCheck)
{
//  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  uint32_t rdVal;
  Serial.println(F("\nreadBitDIGIO128() - reached function"));
  Dio128.pinMode(bitToCheck,INPUT_PULLUP);
  rdVal = Dio128.digitalRead(bitToCheck);
  return(rdVal);
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t readBitDIGIO32(uint8_t bitToCheck)
//////////////////////////////////////////////////////////////////////////////////////

uint8_t readBitDIGIO32(uint8_t bitToCheck)
{
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  uint32_t rdVal;
//  Serial.println(F("\nreadBitDIGIO32() - reached function"));
  rdVal = Dio32.digitalRead(bitToCheck);
  return(rdVal);
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
      writeBitDIGIO128(bitToCheck,bitToWrite);
      break;
    case OPTOIN8I2C_CARD:
      break;
    case OPTOOUT8I2C_CARD:
      break;
    case DIGIO32I2C_CARD:
      writeBitDIGIO32(bitToCheck,bitToWrite);
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
      return 1;
      break;
  }
}

//////////////////////////////////////////////////////////////////////////////////////
// void writeBitDIGIO32(uint8_t bitToCheck, uint8_t bitWeiteValue)
//////////////////////////////////////////////////////////////////////////////////////

void writeBitDIGIO32(uint8_t bitToCheck, uint8_t bitToWrite)
{
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
//  Serial.println(F("\writeBitDIGIO32() - reached function"));
  Dio32.pinMode(bitToCheck,OUTPUT);
  Dio32.digitalWrite(bitToCheck,bitToWrite);
}

//////////////////////////////////////////////////////////////////////////////////////
// void writeBitDIGIO128(uint8_t bitToWrite, uint8_t bitValue)
//////////////////////////////////////////////////////////////////////////////////////

void writeBitDIGIO128(uint8_t bitToWrite, uint8_t bitValue)
{
//  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
//  Serial.println(F("\writeBitDIGIO128() - reached function"));
  Dio128.pinMode(bitToWrite,OUTPUT);
  Dio128.digitalWrite(bitToWrite,bitValue);
}

