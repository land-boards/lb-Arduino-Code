
//////////////////////////////////////////////////////////////////////////////////////
// void bounceLedsCard(void) -
//////////////////////////////////////////////////////////////////////////////////////

uint8_t bounceLedsCard(void)
{
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  switch (boardType)
  {
    case DIGIO16I2C_CARD:
      bounceLedsSingles23017_CARD();
      return 1;
      break;
    case DIGIO128_CARD:
      bounceLedsDIGIO128_CARD();
      return 1;
      break;
    case SWLEDX8_I2C_CARD:
      bounceLedsSwLedX8();
      return 1;
      break;
    case OPTOIN8I2C_CARD:
      Serial.println(F("Can't bounce LEDs on an input only card"));
      return 0;
      break;
    case OPTOOUT8I2C_CARD:
      bounceOptoOut8();
      Serial.println(F("Not supported at present"));
      return 0;
      break;
    case DIGIO32I2C_CARD:
      bounceLedsDigio32();
      return 1;
      break;
    case PROTO16I2C_CARD:
      bounceLedsSingles23017_CARD();
      return 1;
      break;
    case ODASRELAY16_CARD:
      bounceLedsSingles23017_CARD();
      return 1;
      break;
    case ODASPSOC5_CARD:
      Serial.println(F("Not supported at present"));
      return 0;
      return;
      break;
    case NEW_CARD:
      Serial.println(F("Not supported at present"));
      return 0;
      return;
      break;
    case I2CIO8_CARD:
      bounceLedsI2CIO8();
      return 1;
      break;
    case I2CIO8X_CARD:
      bounceLedsI2CIO8X();
      return 1;
      break;
    default:
      Serial.println(F("Not supported at present - default case"));
      break;
  }
  if (Serial.available() > 0)
  {
    Serial.read();
    return;
  }
}

//////////////////////////////////////////////////////////////////////////////////////
// void bounceOptoOut8(void)
//////////////////////////////////////////////////////////////////////////////////////

void bounceOptoOut8(void)
{
  
}

//////////////////////////////////////////////////////////////////////////////////////
// void bounceLedsSingles23017_CARD(void)
//////////////////////////////////////////////////////////////////////////////////////

void bounceLedsSingles23017_CARD(void)
{
  Serial.println(F("Bouncing LEDs - any key to stop"));
  while (1)
  {
    for (uint8_t port = 0; port < 16; port++)
    {
      singleMCP23017.pinMode(port, OUTPUT);
      singleMCP23017.digitalWrite(port, HIGH);
      delay(250);
      singleMCP23017.digitalWrite(port, LOW);
    }
    if (Serial.available() > 0)
    {
      Serial.read();
      return;
    }
  }

}

//////////////////////////////////////////////////////////////////////////////////////
// void bounceLedsDigio32(void)
//////////////////////////////////////////////////////////////////////////////////////

void bounceLedsDigio32(void)
{
  Serial.println(F("Bouncing LEDs - any key to stop"));
  while (1)
  {
    for (uint8_t port = 0; port < 32; port++)
    {
      Dio32.pinMode(port, OUTPUT);
      Dio32.digitalWrite(port, HIGH);
      delay(250);
      Dio32.digitalWrite(port, LOW);
    }
    if (Serial.available() > 0)
    {
      Serial.read();
      return;
    }
  }
}



//////////////////////////////////////////////////////////////////////////////////////
// void bounceLedsSwLedX8(void)
//////////////////////////////////////////////////////////////////////////////////////

void bounceLedsSwLedX8(void)
{
  Serial.println(F("Bouncing LEDs - any key to stop"));
  while (1)
  {
    for (uint8_t port = 8; port < 16; port++)
    {
      singleMCP23017.pinMode(port, OUTPUT);
      singleMCP23017.digitalWrite(port, HIGH);
      delay(250);
      singleMCP23017.digitalWrite(port, LOW);
    }
    for (uint8_t port = 14; port > 8; port--)
    {
      singleMCP23017.pinMode(port, OUTPUT);
      singleMCP23017.digitalWrite(port, HIGH);
      delay(250);
      singleMCP23017.digitalWrite(port, LOW);
    }
    if (Serial.available() > 0)
    {
      Serial.read();
      return;
    }
  }
}


//////////////////////////////////////////////////////////////////////////////////////
// void bounceLedsDIGIO128_CARD(void)
//////////////////////////////////////////////////////////////////////////////////////

void bounceLedsDIGIO128_CARD(void)
{
  Serial.println(F("Bouncing LEDs DIGIO-128 - any key to stop"));
  while (1)
  {
    for (uint8_t port = 0; port < 127; port++)
    {
      Dio128.pinMode(port, OUTPUT);
      delay(20);
      Dio128.digitalWrite(port, HIGH);
      delay(20);
      Dio128.digitalWrite(port, LOW);
      delay(20);
    }
    if (Serial.available() > 0)
    {
      Serial.read();
      return;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////
// void bounceLedsI2CIO8(void)
//////////////////////////////////////////////////////////////////////////////////////

void bounceLedsI2CIO8(void)
{
  Serial.println(F("Bouncing LEDs I2CIO8 - any key to stop"));
  while (1)
  {
    for (uint8_t port = 0; port < 4; port++)
    {
      i2cio8Card.writeLED(port, HIGH);
      delay(250);
      i2cio8Card.writeLED(port, LOW);
    }
    for (uint8_t port = 2; port > 0; port--)
    {
      i2cio8Card.writeLED(port, HIGH);
      delay(250);
      i2cio8Card.writeLED(port, LOW);
    }
    if (Serial.available() > 0)
    {
      Serial.read();
      return;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////
// void bounceLedsI2CIO8(void)
//////////////////////////////////////////////////////////////////////////////////////

void bounceLedsI2CIO8X(void)
{
  Serial.println(F("Bouncing LEDs I2CIO8X - any key to stop"));
  while (1)
  {
    for (uint8_t port = 0; port < 4; port++)
    {
      i2cio8xCard.digitalWrite(port, HIGH);
      delay(250);
      i2cio8xCard.digitalWrite(port, LOW);
    }
    for (uint8_t port = 2; port > 0; port--)
    {
      i2cio8xCard.digitalWrite(port, HIGH);
      delay(250);
      i2cio8xCard.digitalWrite(port, LOW);
    }
    if (Serial.available() > 0)
    {
      Serial.read();
      return;
    }
  }
}


