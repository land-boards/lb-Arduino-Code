//////////////////////////////////////////////////////////////////////////////////////
// void bounceLedsCard(void) -
//////////////////////////////////////////////////////////////////////////////////////

uint8_t bounceLedsCard(void)
{
  ODASTSTR_I2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  switch (boardType)
  {
    case DIGIO16I2C_CARD:
      bounceLedsSingle23017_CARD();
      return 1;
      break;
    case DIGIO128_CARD:
      bounceLedsDIGIO128_CARD();
      return 1;
      break;
    case DIGIO128_64_CARD:
      bounceLedsDIGIO128_64_CARD();
      return 1;
      break;
    case SWLEDX8_I2C_CARD:
      bounceLedsSwLedX8();
      return 1;
      break;
    case OPTOIN8I2C_CARD:
      bounceOptoIn8();
      return 0;
      break;
    case OPTOOUT8I2C_CARD:
      bounceOptoOut8();
      return 0;
      break;
    case DIGIO32I2C_CARD:
      bounceLedsDigio32();
      return 1;
      break;
    case PROTO16I2C_CARD:
      bounceLedsSingle23017_CARD();
      return 1;
      break;
    case ODASRELAY16_CARD:
      bounceLedsSingle23017_CARD();
      return 1;
      break;
    case ODASPSOC5_CARD:
      Serial.println(F("Not supported at present"));
      return 0;
      break;
    case NEW_CARD:
      Serial.println(F("Not supported at present"));
      return 0;
      break;
    case I2CIO8_CARD:
      bounceLedsI2CIO8();
      return 1;
      break;
    case I2CIO8X_CARD:
      bounceLedsI2CIO8X();
      return 1;
      break;
    case I2CRPT01_CARD:
      bounceLedsI2CRPT01();
      return 1;
      break;
    case I2CRPT08_CARD:
      bounceLedsI2CRPT08();
      return 1;
      break;
    case OPTOFST_SML_NON_INVERTING_CARD:
    case OPTOFST_SML_INVERTING_CARD:
      Serial.println(F("Bounce OPTOFAST"));
      bounceOPTOFAST_CARD(0);
      return 1;
      break;
    default:
      Serial.println(F("Not supported at present - default case"));
      break;
  }
  if (Serial.available() > 0)
  {
    Serial.read();
    return 0;
  }
}

//////////////////////////////////////////////////////////////////////////////////////
// bounceOPTOFAST_CARD
//////////////////////////////////////////////////////////////////////////////////////

void bounceOPTOFAST_CARD(uint8_t inv)
{
  uint8_t port;
  ODASTSTR_I2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
  delay(10);
  for (port = 8; port < 12; port++)   // Set all inputs to Pullup
    Dio32.pinMode(port, INPUT_PULLUP);
  delay(10);
  for (port = 0; port < 4; port++)   // Set outputs
  {
    Dio32.pinMode(port, OUTPUT);
    Dio32.digitalWrite(port, LOW);
  }
  delay(10);
  for (port = 0; port < 4; port++)   // Set all inputs to Pullup
  {
    Dio32.digitalWrite(port, HIGH);
    delay(10);
    Dio32.digitalWrite(port, LOW);
    delay(10);
  }
}

//////////////////////////////////////////////////////////////////////////////////////
// void bounceOptoIn8(void)
// Cable from UUT connector to the DIGIO32 card in the Test Station.
// The Test Station has an internal DIGIO32 card.
// The DIGIO32 internal to the Test Station is set to all outputs.
// Put out 8 bit test vector on DIGIO32 pins
//    D0 is LED1+
//    D8 is LED1-
// To turn on LED1, set D0 High and D8 Low
// Looks at the returned values on the OptoIn8-I2C
// The OptoIn8-I2C cards that is the UUT is set up to all inputs.
//////////////////////////////////////////////////////////////////////////////////////

void bounceOptoIn8(void)
{
  uint8_t port;
  ODASTSTR_I2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
  for (port = 0; port < 16; port++)     // Set DIGIO32 lines 0-15 inside the Test Station to outputs
  { // Need 16 Output lines to control the input LEDs
    Dio32.pinMode(port, OUTPUT);    // Set to outputs
    Dio32.digitalWrite(port, LOW);    // Start setting all LED+ and LED- outputs to LOW
  }
  for (port = 0; port < 8; port++)    // Writing a High to the Digio32 D0-D7 should turn on LEDs
  { // Turning on LEDs should result in a low on the OptoIn8 card
    Dio32.digitalWrite(port, HIGH);   // Turn on the LED
    delay(2);             // Optos take time, but 2 mS is way, way too long
    Dio32.digitalWrite(port, LOW);   // Turn on the LED
  }
}

//////////////////////////////////////////////////////////////////////////////////////
// void bounceOptoOut8(void)
// There are three lines per Channel that need to be connected:
// Ground (Gx), Power (Vx), Open Collector Output (Sx)
// If the LED is not being driven, the Open Collector output will be pulled up
// Wire Grounds to Digio32 channels 0-7
// Wire Powers to Digio32 channels 8-15
// Wire Signals to Digio32 channels 16-23
//////////////////////////////////////////////////////////////////////////////////////

void bounceOptoOut8(void)
{
  uint8_t port;
  uint8_t testResults = TEST_PASSED;
  ODASTSTR_I2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  for (port = 0; port < 8; port++)     // Set all of the OptoOut lines High (LEDs off)
  {
    singleMCP23008.pinMode(port, OUTPUT);
    singleMCP23008.digitalWrite(port, HIGH);
  }
  ODASTSTR_I2CMux.setI2CChannel(TEST_STN_INT_MUX_CH); // Leave LED off when done
  for (port = 0; port < 8; port++)    // Goes to Ground pins of the OptoOut card
  {
    Dio32.pinMode(port, OUTPUT);
    Dio32.digitalWrite(port, LOW);
  }
  for (port = 8; port < 16; port++)     // Goes to Power pins of the OptoOut card connector
  {
    Dio32.pinMode(port, OUTPUT);
    Dio32.digitalWrite(port, HIGH);
  }
  for (port = 16; port < 24; port++)     // Set internal DIGIO32 lines on the Test Station to inputs
  {
    Dio32.pinMode(port, INPUT);
  }
  delay(10);
  ODASTSTR_I2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  for (port = 0; port < 8; port++)     // Goes to Ground pins of the OptoOut card
  {
    singleMCP23008.digitalWrite(port, LOW); // Turn on the LEDs one at a time
    delay(10);
    singleMCP23008.digitalWrite(port, HIGH); // Turn off the LEDs one at a time
  }
}

//////////////////////////////////////////////////////////////////////////////////////
// void bounceLedsSingle23017_CARD(void)
//////////////////////////////////////////////////////////////////////////////////////

void bounceLedsSingle23017_CARD(void)
{
  Serial.println(F("Bouncing LEDs Single MCP23017 - any key to stop"));
  ODASTSTR_I2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  while (1)
  {
    for (uint8_t port = 0; port < 16; port++)
    {
      singleMCP23017.pinMode(port, OUTPUT);
    }
    for (uint8_t port = 0; port < 16; port++)
    {
      singleMCP23017.digitalWrite(port, HIGH);
      delay(250);
      singleMCP23017.digitalWrite(port, LOW);
    }
    if (Serial.available() > 0)
    {
      Serial.read();
      for (uint8_t port = 0; port < 16; port++)
        singleMCP23017.pinMode(port, INPUT);
      return;
    }
  }

}

//////////////////////////////////////////////////////////////////////////////////////
// void bounceLedsDigio32(void)
//////////////////////////////////////////////////////////////////////////////////////

void bounceLedsDigio32(void)
{
  Serial.println(F("Bouncing LEDs DIGIO32 - any key to stop"));
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
  Serial.println(F("Bouncing LEDs LEDS-SWITCHES Card- any key to stop"));
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
// void bounceLedsDIGIO128_64_CARD(void)
//////////////////////////////////////////////////////////////////////////////////////

void bounceLedsDIGIO128_64_CARD(void)
{
  Serial.println(F("Bouncing LEDs DIGIO-128/64 - any key to stop"));
  while (1)
  {
    for (uint8_t port = 0; port < 64; port++)
    {
      Dio128_64.pinMode(port, OUTPUT);
      delay(20);
      Dio128_64.digitalWrite(port, HIGH);
      delay(20);
      Dio128_64.digitalWrite(port, LOW);
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
  uint8_t port;
  Serial.println(F("Bouncing LEDs I2CIO-8 - any key to stop"));
  ODASTSTR_I2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  while (1)
  {
    for (port = 0; port < 4; port++)
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
  uint8_t jumpers;
  Serial.println(F("Bouncing LEDs I2CIO8X - any key to stop"));
  ODASTSTR_I2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  for (jumpers = 0; jumpers < 8; jumpers++)
  {
    i2cio8xCard.pinMode(jumpers, OUTPUT);
  }
  while (1)
  {
    for (uint8_t port = 0; port < 8; port++)
    {
      i2cio8xCard.digitalWrite(port, HIGH);
      delay(250);
      i2cio8xCard.digitalWrite(port, LOW);
      if (Serial.available() > 0)
      {
        Serial.read();
        return;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////
// void bounceLedsI2CRPT01(void)
//////////////////////////////////////////////////////////////////////////////////////

void bounceLedsI2CRPT01(void)
{
  uint8_t port;
  Serial.println(F("Bouncing LEDs I2C-RPT-01 and I2CIO8 - any key to stop"));
  while (1)
  {
    UUTI2CMux.setI2CChannel(0);
    for (port = 0; port < 4; port++)
    {
      i2cio8Card1.writeLED(port, HIGH);
      delay(250);
      i2cio8Card1.writeLED(port, LOW);
    }
    UUTI2CMux.setI2CChannel(1);
    for (port = 0; port < 4; port++)
    {
      i2cio8Card2.writeLED(port, HIGH);
      delay(250);
      i2cio8Card2.writeLED(port, LOW);
    }
    UUTI2CMux.setI2CChannel(2);
    for (port = 0; port < 4; port++)
    {
      i2cio8Card3.writeLED(port, HIGH);
      delay(250);
      i2cio8Card3.writeLED(port, LOW);
    }
    UUTI2CMux.setI2CChannel(3);
    for (port = 0; port < 4; port++)
    {
      i2cio8Card4.writeLED(port, HIGH);
      delay(250);
      i2cio8Card4.writeLED(port, LOW);
    }
    if (Serial.available() > 0)
    {
      Serial.read();
      return;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////
// void bounceLedsI2CRPT08(void)
//////////////////////////////////////////////////////////////////////////////////////

void bounceLedsI2CRPT08(void)
{
  uint8_t port;
  Serial.println(F("Bouncing LEDs I2C-RPT-01 and I2CIO8 - any key to stop"));
  while (1)
  {
    UUTI2CMux8.setI2CChannel(0, 1);
    for (port = 0; port < 4; port++)
    {
      i2cio8Card1.writeLED(port, HIGH);
      delay(250);
      i2cio8Card1.writeLED(port, LOW);
    }
    UUTI2CMux8.setI2CChannel(1, 1);
    for (port = 0; port < 4; port++)
    {
      i2cio8Card2.writeLED(port, HIGH);
      delay(250);
      i2cio8Card2.writeLED(port, LOW);
    }
    UUTI2CMux8.setI2CChannel(2, 1);
    for (port = 0; port < 4; port++)
    {
      i2cio8Card3.writeLED(port, HIGH);
      delay(250);
      i2cio8Card3.writeLED(port, LOW);
    }
    UUTI2CMux8.setI2CChannel(3, 1);
    for (port = 0; port < 4; port++)
    {
      i2cio8Card4.writeLED(port, HIGH);
      delay(250);
      i2cio8Card4.writeLED(port, LOW);
    }
    UUTI2CMux8.setI2CChannel(4, 1);
    for (port = 0; port < 4; port++)
    {
      i2cio8Card4.writeLED(port, HIGH);
      delay(250);
      i2cio8Card5.writeLED(port, LOW);
    }
    UUTI2CMux8.setI2CChannel(5, 1);
    for (port = 0; port < 4; port++)
    {
      i2cio8Card4.writeLED(port, HIGH);
      delay(250);
      i2cio8Card6.writeLED(port, LOW);
    }
    UUTI2CMux8.setI2CChannel(6, 1);
    for (port = 0; port < 4; port++)
    {
      i2cio8Card4.writeLED(port, HIGH);
      delay(250);
      i2cio8Card7.writeLED(port, LOW);
    }
    UUTI2CMux8.setI2CChannel(7, 1);
    for (port = 0; port < 4; port++)
    {
      i2cio8Card4.writeLED(port, HIGH);
      delay(250);
      i2cio8Card8.writeLED(port, LOW);
    }
    if (Serial.available() > 0)
    {
      Serial.read();
      return;
    }
  }
}
