//////////////////////////////////////////////////////////////////////////////////////
// ODAS card loopback test code
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t extLBTestCard(void) -
//////////////////////////////////////////////////////////////////////////////////////

uint8_t extLBTestCard(void)
{
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  switch (boardType)
  {
    case DIGIO16I2C_CARD:
      return (testDigio16Card());
      break;
    case DIGIO128_CARD:
      return (extLBTestDIGIO128_CARD());
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
    case PROTO16I2C_CARD:
      return (testProto16());
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
    case OPTOFST_SML_NON_INVERTING_CARD:
      return (testOptoFastSmallNonInverting());
      break;
    case OPTOFST_SML_INVERTING_CARD:
      return (testOptoFastSmallInverting());
      break;
    case NEW_CARD:
      Serial.println(F("Not supported at present"));
      break;
    default:
      Serial.println(F("Undefined board type"));
      return 1;
      break;
  }
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  return TEST_FAILED; // fail
}

//////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////

uint8_t testOptoFastSmallInverting(void)
{
  uint8_t port;
  uint8_t testResults = TEST_PASSED;
  myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
  for (port = 0; port < 4; port++)   // Set all inputs to Pullup
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
//
//////////////////////////////////////////////////////////////////////////////////////

uint8_t testOptoFastSmallNonInverting(void)
{
  uint8_t port;
  uint8_t testResults = TEST_PASSED;
  myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
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
//
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
  //  Serial.println(F("Testing PROTO16-I2C card"));
  for (loopCnt = 0; loopCnt < 16; loopCnt++)
    singleMCP23017.pinMode(loopCnt, OUTPUT);
  singleMCP23017.writeGPIOAB(0x55aa);
  readBackVal = singleMCP23017.readGPIOAB();
  if (readBackVal != 0x55aa)
  {
    Serial.print(F("Readback="));
    Serial.println(readBackVal);
    failed = TEST_FAILED;
  }
  delay(10);
  singleMCP23017.writeGPIOAB(0xaa55);
  readBackVal = singleMCP23017.readGPIOAB();
  if (readBackVal != 0xaa55)
  {
    Serial.print(F("Readback="));
    Serial.println(readBackVal);
    failed = TEST_FAILED;
  }
  for (loopCnt = 0; loopCnt < 16; loopCnt++)
    singleMCP23017.pinMode(loopCnt, INPUT);
  delay(1);
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
  while (1)
  {
    i2cio8Card.writeLED(LED0, !i2cio8Card.readJumper(H4JUMPER));
    i2cio8Card.writeLED(LED1, !i2cio8Card.readJumper(H5JUMPER));
    i2cio8Card.writeLED(LED2, !i2cio8Card.readJumper(H6JUMPER));
    i2cio8Card.writeLED(LED3, !i2cio8Card.readJumper(H7JUMPER));
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
  myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
  for (port = 0; port < 32; port++)   	// Set DIGIO32 lines inside the Test Station to be inputs with pull-ups
    Dio32.pinMode(port, INPUT_PULLUP);
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  for (port = 0; port < 32; port++)		// Set all UUT channels to outputs
    Dio32.pinMode(port, OUTPUT);
  // Set bits being checked to Low
  // Verify that a Low is read back
  for (port = 0; port < 32; port++)
  {
    myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);		// Write out from UUT card
    Dio32.digitalWrite(port, LOW);
    myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);	// Read in from Test Station
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
    myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);		// Write out from UUT card
    Dio32.digitalWrite(port, HIGH);
    myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);	// Read in from Test Station
    if (Dio32.digitalRead(port) != HIGH)
    {

      Serial.print(F("Error on port "));
      Serial.print(port);
      Serial.println(F(" Expected High"));
      testResults = TEST_FAILED;
    }
  }
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);			// Leave the UUT as inputs when done
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
  myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
  for (port = 0; port < 32; port++)		// Set DIGIO32 lines inside the Test Station to be inputs with pull-ups
    Dio32.pinMode(port, INPUT_PULLUP);
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  for (port = 0; port < 16; port++)					// Set all UUT channels to outputs
    singleMCP23017.pinMode(port, OUTPUT);
  // Check bits to Low
  for (port = 0; port < 16; port++)
  {
    myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
    singleMCP23017.digitalWrite(port, LOW);			// Write out from UUT card
    myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
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
    myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
    singleMCP23017.digitalWrite(port, HIGH);		// Write out from UUT card
    myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
    if (Dio32.digitalRead(port) != HIGH)			// Read in from Test Station
    {

      Serial.print(F("Error on port "));
      Serial.print(port);
      Serial.println(F(" Expected High"));
      testResults = TEST_FAILED;
    }
  }
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
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
  myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
  for (port = 0; port < 16; port++)   	// Set DIGIO32 lines inside the Test Station to outputs
  { // Need 16 Output lines to control the output LEDs
    Dio32.pinMode(port, OUTPUT);		// Set to outputs
    Dio32.digitalWrite(port, LOW);		// Start setting all LED+ and LED- outputs to LOW
  }
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
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
  myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);	// Loop sets it back to Test Station before the end
  for (port = 0; port < 8; port++)		// Writing a High to the Digio32 D0-D7 should turn on LEDs
  { // Turning on LEDs should result in a low on the OptoIn8 card
    Dio32.digitalWrite(port, HIGH);		// Turn on the LED
    delay(2);							// Optos take time, but 2 mS is way, way too long
    myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
    readVal = singleMCP23008.digitalRead(port);
    if (readVal != LOW)
    {
      testResults = TEST_FAILED;
      Serial.print(F("OptoIn8-I2C failed - Expected HIGH on bit "));
      Serial.println(port);
    }
    myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);	// Leave LED off when done
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
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  for (port = 0; port < 8; port++)   	// Set all of the OptoOut lines High (LEDs off)
  {
    singleMCP23008.pinMode(port, OUTPUT);
    singleMCP23008.digitalWrite(port, HIGH);
  }
  myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);	// Leave LED off when done
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
      Serial.println(port);
    }
  }
  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  for (port = 0; port < 8; port++)   	// Goes to Ground pins of the OptoOut card
  {
    singleMCP23008.digitalWrite(port, LOW);	// Turn on the LEDs one at a time
    myI2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);	// Leave LED off when done
    if (Dio32.digitalRead(port) != LOW)
    {
      testResults = TEST_FAILED;
      Serial.print(F("OptoOut8-I2C failed - Expected LOW on bit "));
      Serial.println(port);
    }
    myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
    singleMCP23008.digitalWrite(port, HIGH);	// Leave LED off after the test
  }

  return TEST_PASSED;
}

//////////////////////////////////////////////////////////////////////////////////////
// uint8_t extLBTestDIGIO128_CARD(void) -
//////////////////////////////////////////////////////////////////////////////////////

uint8_t extLBTestDIGIO128_CARD(void)
{
  uint8_t testResults = TEST_PASSED;
  //  myI2CMux.setI2CChannel(UUT_CARD_MUX_CH);
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

      delay(2);
      Dio128.digitalWrite((chip << 4) + port, HIGH);
      delay(2);
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
      delay(2);
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
      delay(2);
    }
  }
  if (testResults)
    return TEST_PASSED;
  return TEST_FAILED;
}

