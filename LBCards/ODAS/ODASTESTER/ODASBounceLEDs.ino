//////////////////////////////////////////////////////////////////////////////////////
// void bounceLedsCard(void) -
//////////////////////////////////////////////////////////////////////////////////////

void bounceLedsCard(void)
{
  switch (boardType)
  {
    case DIGIO16I2C:
      Serial.println(F("Not supported at present"));
      break;
    case DIGIO128:
      bounceLedsDigio128();
      break;
    case OPTOIN8I2C:
      Serial.println(F("Can't bounce LEDs on an input only card"));
      break;
    case OPTOOUT8I2C:
      Serial.println(F("Not supported at present"));
      break;
    case DIGIO32I2C:
      bounceLedsDigio32();
      break;
    case PROTO16I2C:
      bounceLedsProto16I2C();
      break;
    case ODASPSOC5:
      Serial.println(F("Not supported at present"));
      break;
    case NEWBOARD:
      Serial.println(F("Not supported at present"));
      break;
  }
    if (Serial.available() > 0)
    {
      Serial.read();
    }
}

//////////////////////////////////////////////////////////////////////////////////////
// void bounceLedsProto16I2C(void)
//////////////////////////////////////////////////////////////////////////////////////

void bounceLedsProto16I2C(void)
{
  Serial.println(F("Bouncing LEDs - any key to stop"));
  Adafruit_MCP23017 mcp;
  mcp.begin(1);      // use default address ?

  while (1)
  {
    for (uint8_t port = 0; port < 16; port++)
    {
      mcp.pinMode(port, OUTPUT);
      mcp.digitalWrite(port, HIGH);
      delay(250);
      mcp.digitalWrite(port, LOW);
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
  Digio32 Dio32;
  Dio32.begin(0);
  Serial.println(F("Bouncing LEDs - any key to stop"));
  while (1)
  {
    for (uint8_t port = 0; port < 32; port++)
    {
      Dio32.pinMode(port, OUTPUT);
      Dio32.digitalWrite(port, HIGH);
      delay(2);
      Dio32.digitalWrite(port, LOW);
      delay(2);
    }
    if (Serial.available() > 0)
    {
      Serial.read();
      return;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////
// void bounceLedsDigio128(void)
//////////////////////////////////////////////////////////////////////////////////////

void bounceLedsDigio128(void)
{
  Digio128 Dio128;
  Dio128.begin();
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


