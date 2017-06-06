/////////////////////////////////////////////////////////////////////////////
// TestCardConfig
// Use a Digio32-I2C card as the mate for a UUT
// Test station card is on a different mux channel
// If the UUT is an output card, then the Digio32-I2C
//  card is set up as an input card.
// If the UUT is an input card, then the Digio32-I2C
//  card is set up as an output card.
// If the UUT is a I/O card, then the Digio32-I2C
//  card is set up as a listener (input card).
// For mixed input/output cards, the Digio32-I2C card
//  is set up as a mixed listener/output card.
/////////////////////////////////////////////////////////////////////////////

Digio32 mateDigio32;

/////////////////////////////////////////////////////////////////////////////
// void initMateCard(void)
/////////////////////////////////////////////////////////////////////////////

void initMateCard(boardType_t UUTCard)
{
  setMuxChannel(TEST_STN_INT_MUX_CH);
  switch (UUTCard)
  {
    case DIGIO16I2C_CARD:
      for (uint8_t pin = 0; pin < 16; pin++)
        mateDigio32.pinMode(pin,INPUT_PULLUP);
      break;
    case DIGIO128_CARD: // Digio32-I2C does not have enough lines
      Serial.println(F("Not using Digio32-I2C due to not enough lines"));
      break;
    case OPTOIN8I2C_CARD:
      for (uint8_t pin = 0; pin < 8; pin++)
        mateDigio32.pinMode(pin,INPUT_PULLUP);
      break;
    case OPTOOUT8I2C_CARD:
      for (uint8_t pin = 0; pin < 8; pin++)
        mateDigio32.pinMode(pin,OUTPUT);
      break;
    case DIGIO32I2C_CARD:
      for (uint8_t pin = 0; pin < 32; pin++)
        mateDigio32.pinMode(pin,INPUT_PULLUP);
      break;
    case PROTO16I2C_CARD:
      Serial.print(F("Proto16-I2C card does not support connectorized IO"));
      break;
    case ODASPSOC5_CARD:
      for (uint8_t pin = 0; pin < 32; pin++)
        mateDigio32.pinMode(pin,INPUT_PULLUP);
      break;
    case I2CIO8_CARD:
      for (uint8_t pin = 0; pin < 8; pin++)
        mateDigio32.pinMode(pin,INPUT_PULLUP);
      break;
    case I2CIO8X_CARD:
      for (uint8_t pin = 0; pin < 8; pin++)
        mateDigio32.pinMode(pin,INPUT_PULLUP);
      break;
    case OPTOSMALL_CARD:
      for (uint8_t pin = 0; pin < 4; pin++)
        mateDigio32.pinMode(pin,INPUT_PULLUP);
      for (uint8_t pin = 4; pin < 8; pin++)
        mateDigio32.pinMode(pin,OUTPUT);
      break;
    case OPTOFAST_CARD:
      for (uint8_t pin = 0; pin < 4; pin++)
        mateDigio32.pinMode(pin,INPUT_PULLUP);
      for (uint8_t pin = 4; pin < 8; pin++)
        mateDigio32.pinMode(pin,OUTPUT);
      break;
    default:
      Serial.println(F("initMateCard: Card Mate is not configured"));
      break;
  }
  setMuxChannel(UUT_CARD_MUX_CH);
}

/////////////////////////////////////////////////////////////////////////////
// uint8_t readMateCard8(void)
// Read a byte value from the lower 8 bits of the Digio32-I2C mate card.
/////////////////////////////////////////////////////////////////////////////

uint8_t readMateCard8(void)
{
  uint8_t retVal;
  setMuxChannel(TEST_STN_INT_MUX_CH);
  uint16_t readVal = mateDigio32.readGPIOAB(0);
  retVal = (uint8_t) readVal;
  setMuxChannel(UUT_CARD_MUX_CH);
  return retVal;
}

/////////////////////////////////////////////////////////////////////////////
// uint16_t readMateCard16(void)
// Read a 16-bit value from the lower 16 bits of the Digio32-I2C mate card.
/////////////////////////////////////////////////////////////////////////////

uint16_t readMateCard16(void)
{
  uint16_t retVal;
  setMuxChannel(TEST_STN_INT_MUX_CH);
  retVal = mateDigio32.readGPIOAB(0);
  setMuxChannel(UUT_CARD_MUX_CH);
  return retVal;
}

/////////////////////////////////////////////////////////////////////////////
// uint32_t readMateCard32(void)
// Read a long value from the 32 bits of the Digio32-I2C mate card.
/////////////////////////////////////////////////////////////////////////////

uint32_t readMateCard32(void)
{
  uint16_t retValLow;
  uint16_t retValHigh;
  setMuxChannel(TEST_STN_INT_MUX_CH);
  retValLow = mateDigio32.readGPIOAB(0);
  retValHigh = mateDigio32.readGPIOAB(1);
  setMuxChannel(UUT_CARD_MUX_CH);
  return (((uint32_t) retValLow) + (((uint32_t) retValHigh)<<16));
}

/////////////////////////////////////////////////////////////////////////////
// uint32_t readMateCardBit(uint8_t bitNumber)
// Read a bit from the Digio32-I2C mate card.
/////////////////////////////////////////////////////////////////////////////

uint32_t readMateCardBit(uint8_t bitNumber)
{
  setMuxChannel(TEST_STN_INT_MUX_CH);
  mateDigio32.digitalRead(bitNumber);
  setMuxChannel(UUT_CARD_MUX_CH);
  return 0;
}

/////////////////////////////////////////////////////////////////////////////
// void writeMateCardBit(uint8_t bitNumber, unit8_t value)
// Read a bit to the Digio32-I2C mate card.
/////////////////////////////////////////////////////////////////////////////

void writeMateCardBit(uint8_t bitNumber, uint8_t value)
{
  setMuxChannel(TEST_STN_INT_MUX_CH);
  mateDigio32.digitalWrite(bitNumber, value);
  setMuxChannel(UUT_CARD_MUX_CH);
  return;
}

/////////////////////////////////////////////////////////////////////////////
// void writeMateCard8(unit8_t value)
// Write a byte to the Digio32-I2C mate card.
/////////////////////////////////////////////////////////////////////////////

void writeMateCard8(uint8_t value)
{
  uint16_t tmpVal;
  setMuxChannel(TEST_STN_INT_MUX_CH);
  tmpVal = mateDigio32.readGPIOAB(0);
  tmpVal &= 0xff00;
  tmpVal |= value;
  mateDigio32.writeOLATAB(0,tmpVal);
  setMuxChannel(UUT_CARD_MUX_CH);
  return;
}

/////////////////////////////////////////////////////////////////////////////
// void writeMateCard16(uint16_t value)
//  Write a 16-bit value to the Digio32-I2C mate card.
/////////////////////////////////////////////////////////////////////////////

void writeMateCard16(uint8_t value)
{
  setMuxChannel(TEST_STN_INT_MUX_CH);
  mateDigio32.writeOLATAB(0,value);
  setMuxChannel(UUT_CARD_MUX_CH);
  return;
}

/////////////////////////////////////////////////////////////////////////////
// void writeMateCard32(uint32_t value)
//  Write a 32-bit value to the Digio32-I2C mate card.
/////////////////////////////////////////////////////////////////////////////

void writeMateCard32(uint32_t value)
{
  setMuxChannel(TEST_STN_INT_MUX_CH);
  mateDigio32.write32(value);
  setMuxChannel(UUT_CARD_MUX_CH);
  return;
}

