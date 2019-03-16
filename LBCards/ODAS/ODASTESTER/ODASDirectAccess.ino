//////////////////////////////////////////////////////////////////////////////////////
// uint8_t readBitValue(uint8_t bitToCheck)
//////////////////////////////////////////////////////////////////////////////////////

uint8_t readBitValue(uint8_t bitToCheck)
{
  switch (boardType)
  {
    case DIGIO128_CARD:
      return (Dio128.digitalRead(bitToCheck));
      break;
    case DIGIO128_64_CARD:
      return (Dio128_64.digitalRead(bitToCheck));
      break;
    case OPTOIN8I2C_CARD:
      return (singleMCP23008.digitalRead(bitToCheck));
      break;
    case DIGIO16I2C_CARD:
      return (singleMCP23017.digitalRead(bitToCheck));
      break;
    case DIGIO32I2C_CARD:
      return (Dio32.digitalRead(bitToCheck));
      break;
    case PROTO16I2C_CARD:
      return (singleMCP23017.digitalRead(bitToCheck));
      break;
    case I2CIO8_CARD:
      return (i2cio8Card.digitalRead(bitToCheck));
      break;
    case I2CIO8X_CARD:
      return (i2cio8xCard.digitalRead(bitToCheck));
      break;
    case ODASRELAY16_CARD:
      Serial.println("Card is write-only");
      return(0);
      break;
    case ODASPSOC5_CARD:
      Serial.println("Not implemented");
      return(0);
      break;
    case OPTOOUT8I2C_CARD:
      Serial.println("Card is write-only");
      return(0);
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
  //Serial.println(F("\nreadBitDIGIO128() - reached function"));
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
  //Serial.println(F("\nreadBitDIGIO128() - reached function"));
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
    case DIGIO128_CARD:
      Dio128.pinMode(bitToCheck, OUTPUT);
      Dio128.digitalWrite(bitToCheck, bitToWrite);
      break;
    case DIGIO128_64_CARD:
      Dio128_64.pinMode(bitToCheck, OUTPUT);
      Dio128_64.digitalWrite(bitToCheck, bitToWrite);
      break;
    case PROTO16I2C_CARD:
      singleMCP23017.pinMode(bitToCheck, OUTPUT);
      singleMCP23017.digitalWrite(bitToCheck, bitToWrite);
      break;
    case ODASRELAY16_CARD:
      singleMCP23017.pinMode(bitToCheck, OUTPUT);
      singleMCP23017.digitalWrite(bitToCheck, bitToWrite);
      break;
    case SWLEDX8_I2C_CARD:
      singleMCP23017.pinMode(bitToCheck, OUTPUT);
      singleMCP23017.digitalWrite(bitToCheck, bitToWrite);
      break;
    case DIGIO32I2C_CARD:
      Dio32.pinMode(bitToCheck, OUTPUT);
      Dio32.digitalWrite(bitToCheck, bitToWrite);
      break;
    case DIGIO16I2C_CARD:
      singleMCP23017.pinMode(bitToCheck, OUTPUT);
      singleMCP23017.digitalWrite(bitToCheck, bitToWrite);
      break;
    case I2CIO8_CARD:
      i2cio8Card.pinMode(bitToCheck, OUTPUT);
      i2cio8Card.digitalWrite(bitToCheck, bitToWrite);
      break;
    case I2CIO8X_CARD:
      i2cio8xCard.pinMode(bitToCheck, OUTPUT);
      i2cio8xCard.digitalWrite(bitToCheck, bitToWrite);
      break;
    case OPTOOUT8I2C_CARD:
      singleMCP23008.pinMode(bitToCheck, OUTPUT);
      singleMCP23008.digitalWrite(bitToCheck, bitToWrite);
      break;
    case OPTOIN8I2C_CARD:
      Serial.println("Card is read-only");
      break;
    case ODASPSOC5_CARD:
      Serial.println("Not implemented");
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
