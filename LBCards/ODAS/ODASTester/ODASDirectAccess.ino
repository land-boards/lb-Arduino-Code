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
// uint8_t readBitDIGIO32(uint8_t bitToCheck)
//////////////////////////////////////////////////////////////////////////////////////

uint8_t readBitDIGIO32(uint8_t bitToCheck)
{
  uint32_t rdVal;
  Digio32 Dio32;
  Dio32.begin(0);
  Serial.println(F("\nreadBitDIGIO32() - reached function"));
  rdVal = Dio32.digitalRead(bitToCheck);
  Serial.print(F("Read Value: "));
  Serial.println(rdVal);
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
  Digio32 Dio32;
  Dio32.begin(0);
//  Serial.println(F("\writeBitDIGIO32() - reached function"));
  Dio32.pinMode(bitToCheck,OUTPUT);
  Dio32.digitalWrite(bitToCheck,bitToWrite);
}

