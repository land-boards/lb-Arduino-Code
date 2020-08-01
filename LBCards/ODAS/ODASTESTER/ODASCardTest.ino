//////////////////////////////////////////////////////////////////////////////////////
// ODAS card loopback test code
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t extLBTestCard(void) -
//////////////////////////////////////////////////////////////////////////////////////

uint8_t extLBTestCard(void)
{
  BluePillI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  switch (boardType)
  {
    case DIGIO16I2C_CARD:
      return (testDigio16Card());
      break;
    case DIGIO128_CARD:
      return (extLBTestDIGIO128_CARD());
      break;
    case DIGIO128_64_CARD:
      return (extLBTestDIGIO128_64_CARD());
      break;
    case PROTO16I2C_CARD:
      return (testProto16());
      break;
    case OPTOIN8I2C_CARD:
      return (extLBTestOptoIn8());
      break;
    case OPTOOUT8I2C_CARD:
      return (extLBTestOptoOut8());
      break;
    case DIGIO32I2C_CARD:
      return (testDigio32Card());
      break;
    case ODASRELAY16_CARD:
      return (testProto16());
      break;
    case ODASPSOC5_CARD:
      Serial.println(F("Not supported at present"));
      break;
    case I2CIO8_CARD:
      return (testI2CIO8());
      break;
    case I2CIO8X_CARD:
      return (testI2CIO8X());
      break;
    case SWLEDX8_I2C_CARD:
      return (testSwLedX8());
      break;
    case I2CRPT01_CARD:
      return (testLedsI2CRPT01());
      break;
    case I2CRPT08_CARD:
      return (testLedsI2CRPT08());
      break;
    case OPTOFST_SML_NON_INVERTING_CARD:
      return (testOptoFastSmallNonInverting());
      break;
    case OPTOFST_SML_INVERTING_CARD:
      return (testOptoFastSmallInverting());
      break;
    case OPTOFSTBI_CARD:
      return (testOptoFastBi());
      break;
    case NEW_CARD:
      Serial.println(F("Not supported at present"));
      break;
    default:
      Serial.println(F("Undefined board type"));
      return 1;
      break;
  }
  BluePillI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  return TEST_FAILED; // fail
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t testOptoFastSmallInverting(void)
//////////////////////////////////////////////////////////////////////////////////////

uint8_t testOptoFastSmallInverting(void)
{
  uint8_t port;
  uint8_t testResults = TEST_PASSED;
  BluePillI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
  for (port = 0; port < 4; port++)   // Set all inputs to Pullup
  {
    Dio32.pinMode(port, OUTPUT);
    Dio32.digitalWrite(port, LOW);
  }
  for (port = 8; port < 12; port++)   // Set all inputs to Pullup
    Dio32.pinMode(port, INPUT_PULLUP);
  for (port = 0; port < 4; port++)   // Set all inputs to Pullup
  {
    Dio32.digitalWrite(port, HIGH);
    delay(2);
    if (Dio32.digitalRead(port + 8) != LOW)
    {
      Serial.print(F("Error on port "));
      Serial.print(port);
      Serial.println(F(" Expected Low"));
      testResults = TEST_FAILED;
    }
    Dio32.digitalWrite(port, LOW);
    delay(2);
    if (Dio32.digitalRead(port + 8) != HIGH)
    {
      Serial.print(F("Error on port "));
      Serial.print(port);
      Serial.println(F(" Expected High"));
      testResults = TEST_FAILED;
    }
  }
  return testResults;
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t testOptoFastSmallNonInverting(void)
//////////////////////////////////////////////////////////////////////////////////////

uint8_t testOptoFastSmallNonInverting(void)
{
  uint8_t port;
  uint8_t testResults = TEST_PASSED;
  BluePillI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
  for (port = 0; port < 4; port++)   // Set all inputs to Pullup
    Dio32.pinMode(port, OUTPUT);
  for (port = 8; port < 12; port++)   // Set all inputs to Pullup
    Dio32.pinMode(port, INPUT_PULLUP);
  for (port = 0; port < 4; port++)   // Set all inputs to Pullup
  {
    Dio32.digitalWrite(port, LOW);
    if (Dio32.digitalRead(port + 8) != LOW)
    {
      Serial.print(F("Error on port "));
      Serial.print(port);
      Serial.println(F(" Expected Low"));
      testResults = TEST_FAILED;
    }
    Dio32.digitalWrite(port, HIGH);
    if (Dio32.digitalRead(port + 8) != HIGH)
    {
      Serial.print(F("Error on port "));
      Serial.print(port);
      Serial.println(F(" Expected High"));
      testResults = TEST_FAILED;
    }
  }
  return testResults;
}


//////////////////////////////////////////////////////////////////////////////////////
// uint8_t testOptoFastBi(void)
//////////////////////////////////////////////////////////////////////////////////////

uint8_t testOptoFastBi
(void)
{
  uint8_t port;
  uint8_t testResults = TEST_PASSED;
  BluePillI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
  for (port = 0; port < 4; port++)   // Set ports 0-3 to outputs
    Dio32.pinMode(port, OUTPUT);
  for (port = 8; port < 12; port++)   // Set all inputs to Pullup
    Dio32.pinMode(port, INPUT_PULLUP);
  for (port = 0; port < 4; port++)   // Set all inputs to Pullup
  {
    Dio32.digitalWrite(port, LOW);
    if (Dio32.digitalRead(port + 8) != HIGH)
    {
      Serial.print(F("Error on port "));
      Serial.print(port);
      Serial.println(F(" Expected High"));
      testResults = TEST_FAILED;
    }
    Dio32.digitalWrite(port, HIGH);
    if (Dio32.digitalRead(port + 8) != LOW)
    {
      Serial.print(F("Error on port "));
      Serial.print(port);
      Serial.println(F(" Expected Low"));
      testResults = TEST_FAILED;
    }
  }
  return testResults;
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t testSwLedX8(void)
//////////////////////////////////////////////////////////////////////////////////////

uint8_t testSwLedX8(void)
{
  uint8_t loopCnt;
  Serial.println(F("Testing SWLEDX8-I2C card"));
  Serial.println(F("Slide switches verify lights"));
  Serial.println(F("Hit any key to exit"));
  for (loopCnt = 0; loopCnt < 8; loopCnt++)
    singleMCP23017.pinMode(loopCnt, INPUT);
  for (loopCnt = 8; loopCnt < 16; loopCnt++)
  {
    singleMCP23017.digitalWrite(loopCnt, LOW);
    singleMCP23017.pinMode(loopCnt, OUTPUT);
  }
  while (Serial.available() == 0)
  {
    for (loopCnt = 0; loopCnt < 8; loopCnt++)
    {
      singleMCP23017.digitalWrite(loopCnt + 8, singleMCP23017.digitalRead(loopCnt));
    }
  }
  return TEST_PASSED;
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t testProto16(void) - Test the PROTO16-I2C card
// This test is an internal loopback test since the pins are dependent on the wiring.
//////////////////////////////////////////////////////////////////////////////////////

uint8_t testProto16(void)
{
  uint8_t failed = TEST_PASSED;
  uint8_t loopCnt;
  uint16_t readBackVal;
  uint16_t testVal;
  for (loopCnt = 0; loopCnt < 16; loopCnt++)
    singleMCP23017.pinMode(loopCnt, OUTPUT);
  testVal = 1;
  while (testVal != 0)
  {
    singleMCP23017.writeOLATAB(testVal);
    readBackVal = singleMCP23017.readOLATAB();
    if (testVal != readBackVal)
    {
      Serial.print(F("testProto16(1): Readback="));
      Serial.println(readBackVal, HEX);
      Serial.println(F("testProto16(1): Expected="));
      Serial.println(testVal, HEX);
      failed = TEST_FAILED;
    }
    testVal <<= 1;
  }
  while (testVal != 0)
  {
    singleMCP23017.writeOLATAB(~testVal);
    readBackVal = ~singleMCP23017.readOLATAB();
    if (testVal != readBackVal)
    {
      Serial.print(F("testProto16(1): Readback="));
      Serial.println(~readBackVal, HEX);
      Serial.println(F("testProto16(1): Expected="));
      Serial.println(~testVal, HEX);
      failed = TEST_FAILED;
    }
    testVal <<= 1;
  }
  for (loopCnt = 0; loopCnt < 16; loopCnt++)
    singleMCP23017.pinMode(loopCnt, INPUT);
  return (failed);
}

  //////////////////////////////////////////////////////////////////////////////////////
  // uint8_t testI2CIO8(void) - Test the I2CIO8 card
  //////////////////////////////////////////////////////////////////////////////////////

  uint8_t testI2CIO8(void)
  {
    Serial.println(F("I2CIO8 card tests"));
    Serial.println(F("Move jumper across H5-H8, observe LEDs D0-D3"));
    Serial.println(F("Verify Int LED blinks"));
    Serial.println(F("Hit a key to stop test"));
    delay(1);
    while (Serial.available() > 0)
      Serial.read();
    while (1)
    {
      i2cio8Card.writeLED(LED0, i2cio8Card.readJumper(H4JUMPER));
      i2cio8Card.writeLED(LED1, i2cio8Card.readJumper(H5JUMPER));
      i2cio8Card.writeLED(LED2, i2cio8Card.readJumper(H6JUMPER));
      i2cio8Card.writeLED(LED3, i2cio8Card.readJumper(H7JUMPER));
      delay(250);
      if (Serial.available() > 0)
      {
        Serial.read();
        return TEST_PASSED;
      }
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////
  // uint8_t testI2CIO8X(void)
  //////////////////////////////////////////////////////////////////////////////////////

  uint8_t testI2CIO8X(void)
  {
    uint8_t jumpers;
    //  Serial.println(F("I2CIO8X card"));
    //  Serial.println(F("Install test jumper"));
    //  Serial.println(F("Hit a key to stop test"));
    for (jumpers = 0; jumpers < 4; jumpers++)
      i2cio8xCard.pinMode(jumpers, INPUT);
    for (jumpers = 4; jumpers < 8; jumpers++)
      i2cio8xCard.pinMode(jumpers, OUTPUT);
    for (jumpers = 0; jumpers < 4; jumpers++)
    {
      i2cio8xCard.digitalWrite(jumpers + H4JUMPER, LOW);
      if (i2cio8xCard.digitalRead(jumpers) != LOW)
      {
        Serial.println(F("Failed LOW"));
        return TEST_FAILED;
      }
      i2cio8xCard.digitalWrite(jumpers + H4JUMPER, HIGH);
      if (i2cio8xCard.digitalRead(jumpers) != HIGH)
      {
        Serial.println(F("Failed HIGH"));
        return TEST_FAILED;
      }
    }
    return TEST_PASSED;
  }

  //////////////////////////////////////////////////////////////////////////////////////
  // uint8_t testDigio32Card() - Test the DIGIO32 card.
  // Cable from UUT connector to the DIGIO32 card in the Test Station.
  // The Test Station and the UUT both are DIGIO32 cards.
  // The DIGIO32 internal to the Test Station is set to all inputs with pull-ups.
  // The DIGIO32 that is the UUT is set up to all outputs.
  //////////////////////////////////////////////////////////////////////////////////////

  uint8_t testDigio32Card(void)
  {
    uint8_t port;
    uint8_t testResults = TEST_PASSED;	// Assume pass until proven otherwise
    BluePillI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
    for (port = 0; port < 32; port++)   	// Set DIGIO32 lines inside the Test Station to be inputs with pull-ups
      Dio32.pinMode(port, INPUT_PULLUP);
    BluePillI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
    for (port = 0; port < 32; port++)		// Set all UUT channels to outputs
      Dio32.pinMode(port, OUTPUT);
    // Set bits being checked to Low
    // Verify that a Low is read back
    for (port = 0; port < 32; port++)
    {
      BluePillI2CMux.setI2CChannel(UUT_CARD_MUX_CH);		// Write out from UUT card
      Dio32.digitalWrite(port, LOW);
      BluePillI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);	// Read in from Test Station
      if (Dio32.digitalRead(port) != LOW)
      {
        Serial.print(F("Error on port "));
        Serial.print(port);
        Serial.println(F(" Expected Low"));
        testResults = TEST_FAILED;
      }
    }
    // Set bits being checked to High
    // Verify that a High is read back
    for (port = 0; port < 32; port++)
    {
      BluePillI2CMux.setI2CChannel(UUT_CARD_MUX_CH);		// Write out from UUT card
      Dio32.digitalWrite(port, HIGH);
      BluePillI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);	// Read in from Test Station
      if (Dio32.digitalRead(port) != HIGH)
      {

        Serial.print(F("Error on port "));
        Serial.print(port);
        Serial.println(F(" Expected High"));
        testResults = TEST_FAILED;
      }
    }
    BluePillI2CMux.setI2CChannel(UUT_CARD_MUX_CH);			// Leave the UUT as inputs when done
    for (port = 0; port < 32; port++)
      Dio32.pinMode(port, INPUT);
    return testResults;
  }

  //////////////////////////////////////////////////////////////////////////////////////
  // uint8_t testDigio16Card() - Test the DIGIO16 card.
  // Cable from UUT connector to the DIGIO32 card in the Test Station.
  // The Test Station has an internal DIGIO32 card.
  // The DIGIO32 internal to the Test Station is set to all inputs with pull-ups.
  // The DIGIO16 that is the UUT is set up to all outputs.
  //////////////////////////////////////////////////////////////////////////////////////

  uint8_t testDigio16Card(void)
  {
    uint8_t port;
    uint8_t testResults = TEST_PASSED;	// Assume pass until proven otherwise
    BluePillI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
    for (port = 0; port < 32; port++)		// Set DIGIO32 lines inside the Test Station to be inputs with pull-ups
      Dio32.pinMode(port, INPUT_PULLUP);
    BluePillI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
    for (port = 0; port < 16; port++)					// Set all UUT channels to outputs
      singleMCP23017.pinMode(port, OUTPUT);
    // Check bits to Low
    for (port = 0; port < 16; port++)
    {
      BluePillI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
      singleMCP23017.digitalWrite(port, LOW);			// Write out from UUT card
      BluePillI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
      if (Dio32.digitalRead(port) != LOW)				// Read in from Test Station
      {
        Serial.print(F("Error on port "));
        Serial.print(port);
        Serial.println(F(" Expected Low"));
        testResults = TEST_FAILED;
      }
    }
    // Check bits to High
    for (port = 0; port < 16; port++)
    {
      BluePillI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
      singleMCP23017.digitalWrite(port, HIGH);		// Write out from UUT card
      BluePillI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
      if (Dio32.digitalRead(port) != HIGH)			// Read in from Test Station
      {

        Serial.print(F("Error on port "));
        Serial.print(port);
        Serial.println(F(" Expected High"));
        testResults = TEST_FAILED;
      }
    }
    BluePillI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
    for (port = 0; port < 16; port++)					// Leave the UUT as inputs when done
      singleMCP23017.pinMode(port, INPUT);
    return testResults;
  }

  //////////////////////////////////////////////////////////////////////////////////////
  // uint8_t extLBTestOptoIn8(void) - Test the OptoIn8-I2C card.
  // Cable from UUT connector to the DIGIO32 card in the Test Station.
  // The Test Station has an internal DIGIO32 card.
  // The DIGIO32 internal to the Test Station is set to all outputs.
  // Put out 8 bit test vector on DIGIO32 pins
  //		D0 is LED1+
  //  	D8 is LED1-
  // To turn on LED1, set D0 High and D8 Low
  // Looks at the returned values on the OptoIn8-I2C
  // The OptoIn8-I2C cards that is the UUT is set up to all inputs.
  //////////////////////////////////////////////////////////////////////////////////////

  uint8_t extLBTestOptoIn8(void)
  {
    uint8_t readVal;
    uint8_t port;
    uint8_t testResults = TEST_PASSED;
    //  Serial.println(F("Testing OptoIn8-I2C card"));
    BluePillI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
    for (port = 0; port < 16; port++)   	// Set DIGIO32 lines inside the Test Station to outputs
    { // Need 16 Output lines to control the output LEDs
      Dio32.pinMode(port, OUTPUT);		// Set to outputs
      Dio32.digitalWrite(port, LOW);		// Start setting all LED+ and LED- outputs to LOW
    }
    BluePillI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
    for (port = 0; port < 8; port++)   	// Set all UUT inputs to Pull-ups (should already be set)
      singleMCP23008.pinMode(port, INPUT_PULLUP);
    for (port = 0; port < 8; port++)		// Since the LEDs are not being driven, all of the OptoIn
    { // optocoupler outputs should be off (pulled up High)
      readVal = singleMCP23008.digitalRead(port);
      if (readVal != HIGH)
      {
        testResults = TEST_FAILED;
        Serial.print(F("OptoIn8-I2C failed - Expected LOW on bit "));
        Serial.println(port);
      }
    }
    BluePillI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);	// Loop sets it back to Test Station before the end
    for (port = 0; port < 8; port++)		// Writing a High to the Digio32 D0-D7 should turn on LEDs
    { // Turning on LEDs should result in a low on the OptoIn8 card
      Dio32.digitalWrite(port, HIGH);		// Turn on the LED
      delay(2);							// Optos take time, but 2 mS is way, way too long
      BluePillI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
      readVal = singleMCP23008.digitalRead(port);
      if (readVal != LOW)
      {
        testResults = TEST_FAILED;
        Serial.print(F("OptoIn8-I2C failed - Expected HIGH on bit "));
        Serial.println(port);
      }
      BluePillI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);	// Leave LED off when done
      Dio32.digitalWrite(port, LOW);
    }
    for (port = 0; port < 32; port++)   	// Set internal DIGIO32 lines on the Test Station to inputs
      Dio32.pinMode(port, INPUT);
    return (testResults);
  }

  //////////////////////////////////////////////////////////////////////////////////////
  // uint8_t extLBTestOptoOut8(void) - Test the OptoOut8-I2C card
  // Puts out 8 bits on OptoOut8-I2C card
  // Reads the 8 bits on DIGIO32 card
  // There are three lines per Channel that need to be connected:
  // Ground (Gx), Power (Vx), Open Collector Output (Sx)
  // If the LED is not being driven, the Open Collector output will be pulled up
  // Wire Grounds to Digio32 channels 0-7
  // Wire Powers to Digio32 channels 8-15
  // Wire Signals to Digio32 channels 16-23
  // Resistors can be checked by setting the Power line high and checking the OC outputs
  //////////////////////////////////////////////////////////////////////////////////////

  uint8_t extLBTestOptoOut8(void)
  {
    uint8_t readVal;
    uint8_t port;
    uint8_t testResults = TEST_PASSED;
    BluePillI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
    for (port = 0; port < 8; port++)   	// Set all of the OptoOut lines High (LEDs off)
    {
      singleMCP23008.pinMode(port, OUTPUT);
      singleMCP23008.digitalWrite(port, HIGH);
    }
    BluePillI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);	// Leave LED off when done
    for (port = 0; port < 8; port++)   	// Goes to Ground pins of the OptoOut card
    {
      Dio32.pinMode(port, OUTPUT);
      Dio32.digitalWrite(port, LOW);
    }
    for (port = 8; port < 16; port++)   	// Goes to Power pins of the OptoOut card
    {
      Dio32.pinMode(port, OUTPUT);
      Dio32.digitalWrite(port, HIGH);
    }
    for (port = 16; port < 24; port++)   	// Set internal DIGIO32 lines on the Test Station to inputs
    {
      Dio32.pinMode(port, INPUT);
    }
    for (port = 16; port < 24; port++)   	// Check that all of the outputs are High from the OptoOut
    {
      if (Dio32.digitalRead(port) != HIGH)
      {
        testResults = TEST_FAILED;
        Serial.print(F("OptoOut8-I2C failed - Expected HIGH on bit "));
        Serial.println(port - 16);
      }
    }
    BluePillI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
    for (port = 0; port < 8; port++)   	// Goes to Ground pins of the OptoOut card
    {
      singleMCP23008.digitalWrite(port, LOW);	// Turn on the LEDs one at a time
      BluePillI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);	// Leave LED off when done
      if (Dio32.digitalRead(port) != LOW)
      {
        testResults = TEST_FAILED;
        Serial.print(F("OptoOut8-I2C failed - Expected LOW on bit "));
        Serial.println(port);
      }
      BluePillI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
      singleMCP23008.digitalWrite(port, HIGH);	// Leave LED off after the test
    }

    return TEST_PASSED;
  }

  //////////////////////////////////////////////////////////////////////////////////////
  // uint8_t extLBTestDIGIO128_CARD(void) -
  // Cable connects
  //  chip 0 bit 0 to chip 1 bit 15, etc
  //////////////////////////////////////////////////////////////////////////////////////

  uint8_t extLBTestDIGIO128_CARD(void)
  {
    uint8_t testResults = TEST_PASSED;
    //  BluePillI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
    for (uint8_t port = 0; port < 128; port++)
    {
      Dio128.pinMode(port, INPUT_PULLUP);
    }
    for (uint8_t chip = 0; chip < 8; chip += 2)
    {
      for (uint8_t port = 0; port < 16; port++)
      {

        Dio128.pinMode((chip << 4) + port, OUTPUT);
        Dio128.pinMode(((chip + 1) << 4) + 15 - port, INPUT_PULLUP);
        //      delay(2);
        Dio128.digitalWrite((chip << 4) + port, HIGH);
        //      delay(2);
        if (Dio128.digitalRead(((chip + 1) << 4) + 15 - port) != HIGH)
        {
          Serial.print(F("extLBTestDIGIO128_CARD() 1: Error on chip "));
          Serial.print(chip);
          Serial.print(F(" and port "));
          Serial.print(port);
          Serial.println(F(" Expected High"));
          testResults = TEST_FAILED;
        }
        Dio128.digitalWrite((chip << 4) + port, LOW);
        //      delay(2);
        if (Dio128.digitalRead(((chip + 1) << 4) + 15 - port) != LOW)
        {
          Serial.print(F("extLBTestDIGIO128_CARD() 2: Error on chip "));
          Serial.print(chip);
          Serial.print(F(" and port "));
          Serial.print(port);
          Serial.println(F(" Expected LOW"));
          testResults = TEST_FAILED;
        }
        Dio128.pinMode((chip << 4) + port, INPUT);
        //      delay(2);
      }
    }
    return testResults;
  }

  //////////////////////////////////////////////////////////////////////////////////////
  // uint8_t extLBTestDIGIO128_64_CARD(void) -
  // Cable connects
  //  chip 0 bit 0 to chip 1 bit 15, etc
  //////////////////////////////////////////////////////////////////////////////////////

  uint8_t extLBTestDIGIO128_64_CARD(void)
  {
    uint8_t testResults = TEST_PASSED;
    //  BluePillI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
    for (uint8_t port = 0; port < 64; port++)
    {
      Dio128_64.pinMode(port, INPUT_PULLUP);
    }
    for (uint8_t chip = 0; chip < 4; chip += 2)
    {
      for (uint8_t port = 0; port < 16; port++)
      {

        Dio128_64.pinMode((chip << 4) + port, OUTPUT);
        Dio128_64.pinMode(((chip + 1) << 4) + 15 - port, INPUT_PULLUP);
        //      delay(2);
        Dio128_64.digitalWrite((chip << 4) + port, HIGH);
        //      delay(2);
        if (Dio128_64.digitalRead(((chip + 1) << 4) + 15 - port) != HIGH)
        {
          Serial.print(F("extLBTestDIGIO128_64_CARD() 1: Error on chip "));
          Serial.print(chip);
          Serial.print(F(" and port "));
          Serial.print(port);
          Serial.println(F(" Expected High"));
          testResults = TEST_FAILED;
        }
        Dio128_64.digitalWrite((chip << 4) + port, LOW);
        //      delay(2);
        if (Dio128_64.digitalRead(((chip + 1) << 4) + 15 - port) != LOW)
        {
          Serial.print(F("extLBTestDIGIO128_64_CARD() 2: Error on chip "));
          Serial.print(chip);
          Serial.print(F(" and port "));
          Serial.print(port);
          Serial.println(F(" Expected LOW"));
          testResults = TEST_FAILED;
        }
        Dio128_64.pinMode((chip << 4) + port, INPUT);
        //      delay(2);
      }
    }
    return testResults;
  }

  //////////////////////////////////////////////////////////////////////////////////////
  // void testLedsI2CRPT01(void)
  //////////////////////////////////////////////////////////////////////////////////////

  uint8_t testLedsI2CRPT01(void)
  {
    uint8_t port;
    uint8_t intStatus;
    Serial.println(F("Testing I2C-RPT-01 using 4x I2CIO8 and jumpers - any key to stop"));
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
      intStatus = UUTI2CMux.getIntStatus();
      if ((intStatus & 0x1) == 0x1)
      {
        UUTI2CMux.setI2CChannel(0);
        Serial.print("Card #0 - Jumpers = ");
        Serial.println(i2cio8Card1.readAllJumpers());
      }
      if ((intStatus & 0x2) == 0x2)
      {
        UUTI2CMux.setI2CChannel(1);
        Serial.print("Card #1 - Jumpers = ");
        Serial.println(i2cio8Card2.readAllJumpers());
      }
      if ((intStatus & 0x4) == 0x4)
      {
        UUTI2CMux.setI2CChannel(2);
        Serial.print("Card #2 - Jumpers = ");
        Serial.println(i2cio8Card3.readAllJumpers());
      }
      if ((intStatus & 0x8) == 0x8)
      {
        UUTI2CMux.setI2CChannel(3);
        Serial.print("Card #3 - Jumpers = ");
        Serial.println(i2cio8Card4.readAllJumpers());
      }
      if (Serial.available() > 0)
      {
        Serial.read();
        return (TEST_PASSED);
      }
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////
  // void testLedsI2CRPT01(void)
  //////////////////////////////////////////////////////////////////////////////////////

  uint8_t testLedsI2CRPT08(void)
  {
    uint8_t port;
    uint8_t intStatus;
    Serial.println(F("Testing I2C-RPT-08 using 8x I2CIO8 and jumpers - any key to stop"));
    while (1)
    {
      // writes
      UUTI2CMux8.setI2CChannel(0,1);
      for (port = 0; port < 4; port++)
      {
        i2cio8Card1.writeLED(port, HIGH);
        delay(250);
        i2cio8Card1.writeLED(port, LOW);
      }
      UUTI2CMux8.setI2CChannel(0,0);
      UUTI2CMux8.setI2CChannel(1,1);
      for (port = 0; port < 4; port++)
      {
        i2cio8Card2.writeLED(port, HIGH);
        delay(250);
        i2cio8Card2.writeLED(port, LOW);
      }
      UUTI2CMux8.setI2CChannel(1,0);
      UUTI2CMux8.setI2CChannel(2,1);
      for (port = 0; port < 4; port++)
      {
        i2cio8Card3.writeLED(port, HIGH);
        delay(250);
        i2cio8Card3.writeLED(port, LOW);
      }
      UUTI2CMux8.setI2CChannel(2,0);
      UUTI2CMux8.setI2CChannel(3,1);
      for (port = 0; port < 4; port++)
      {
        i2cio8Card4.writeLED(port, HIGH);
        delay(250);
        i2cio8Card4.writeLED(port, LOW);
      }
      UUTI2CMux8.setI2CChannel(3,0);
      UUTI2CMux8.setI2CChannel(4,1);
      for (port = 0; port < 4; port++)
      {
        i2cio8Card4.writeLED(port, HIGH);
        delay(250);
        i2cio8Card5.writeLED(port, LOW);
      }
      UUTI2CMux8.setI2CChannel(4,0);
      UUTI2CMux8.setI2CChannel(5,1);
      for (port = 0; port < 4; port++)
      {
        i2cio8Card4.writeLED(port, HIGH);
        delay(250);
        i2cio8Card6.writeLED(port, LOW);
      }
      UUTI2CMux8.setI2CChannel(5,0);
      UUTI2CMux8.setI2CChannel(6,1);
      for (port = 0; port < 4; port++)
      {
        i2cio8Card4.writeLED(port, HIGH);
        delay(250);
        i2cio8Card7.writeLED(port, LOW);
      }
      UUTI2CMux8.setI2CChannel(6,0);
      UUTI2CMux8.setI2CChannel(7,1);
      for (port = 0; port < 4; port++)
      {
        i2cio8Card8.writeLED(port, HIGH);
        delay(250);
        i2cio8Card4.writeLED(port, LOW);
      }
      UUTI2CMux8.setI2CChannel(7,0);
      if (Serial.available() > 0)
      {
        Serial.read();
        return (TEST_PASSED);
      }
    }
  }
  
