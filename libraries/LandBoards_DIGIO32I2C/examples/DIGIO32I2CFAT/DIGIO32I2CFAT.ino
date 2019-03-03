//////////////////////////////////////////////////////////
// DIGIO32I2CFAT : DIGIO32-I2C Factory Test code
// Test each channel
// Read/write EEPROM
// Tested in Arduino Uno/Arduino NANO cards
// Use Serial Port for menu/test results
//////////////////////////////////////////////////////////

#include "LandBoards_DIGIO32_I2C.h"

uint32_t failCount;       // Globals used in the below code
uint32_t passCount;
int looping;

Digio32 Dio32;

//////////////////////////////////////////////////////////
// setup()
//////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(9600);     	// 9600 baud serial connection
  Dio32.begin(0);         	// Instantiate Digio32 card

  for (uint8_t port = 0; port < 32; port++)
  {
    Dio32.pinMode(port, INPUT_PULLUP);
  }
  failCount = 0;  // Initialize the test variables
  passCount = 0;
  looping = 0;
  
  Serial.print("Running internal loopback test...");
  if (internalLoopBackTest() != 0)
    Serial.println("Failed internal loopback test");
  else
    Serial.println("Passed internal loopback test");
    
  Serial.print("Running external loopback test...");
  if (externalLoopBackTest() != 0)
    Serial.println("Failed external loopback test");
  else
    Serial.println("Passed external loopback test");
  if (eepromCheck() != 0)   // Check to see if the EEPROM was already programmed
  {
    Serial.println("Failed eeprom check test");
    Serial.println("Writing EEPROM");
    eepromWrite();          // Program EEPROM for the first time
    if (eepromCheck() != 0) // Check EEPROM was successfully programmed
    {
      Serial.println("Failed eeprom check test");
    }
  }
  else
    Serial.println("Passed eeprom check test");
  Serial.println("R=Read EEPROM, W=Write EEPROM, T=Test DIGIOs, L=Loop Mode, I=Internal Loopback, B=Blink LEDs");  // Test menu
}

//////////////////////////////////////////////////////////
// loop()
//////////////////////////////////////////////////////////

void loop()
{
  int incomingByte = 0;   // for incoming serial data
  if (Serial.available() > 0) // If there is serial data present
  {
    incomingByte = Serial.read();     // read the incoming byte:
    if ((incomingByte == 'R') || (incomingByte == 'r'))
    {
      eepromRead();
    }
    else if ((incomingByte == 'W') || (incomingByte == 'w'))
    {
      eepromWrite();
    }
    else if ((incomingByte == 'I') || (incomingByte == 'i'))
    {
      if (internalLoopBackTest() == 0)
        passCount++;
      else
        failCount++;
      Serial.print("Internal Loopback Test PASS = ");
      Serial.print(passCount);
      Serial.print(", FAIL = ");
      Serial.println(failCount);
    }
    else if ((incomingByte == 'T') || (incomingByte == 't'))
    {
      if (externalLoopBackTest() == 0)
        passCount++;
      else
        failCount++;
      Serial.print("External Loopback Test PASS = ");
      Serial.print(passCount);
      Serial.print(", FAIL = ");
      Serial.println(failCount);
    }
    else if ((incomingByte == 'L') || (incomingByte == 'l'))
    {
      looping = 1;
    }
    else if ((incomingByte == 'B') || (incomingByte == 'b'))
    {
      do
      {
        for (uint8_t port = 0; port < 32; port++)
        {
          Dio32.pinMode(port, OUTPUT);
          Dio32.digitalWrite(port, HIGH);
          delay(250);
          Dio32.digitalWrite(port, LOW);
          Dio32.pinMode(port, INPUT);
        }
      }
      while (Serial.available() == 0);
    }
    else
    {
      if (looping == 1)
        looping = 0;
      else
        Serial.println("Unrecognized command");
      Serial.println("\nR=Read EEPROM, W=Write EEPROM, T=Test DIGIOs, I=Internal Loopback, L=Loop Mode, B=Blink LEDs");
    }
  }

  while (Serial.available() > 0)    // Flush extra read data (CR-LF extras)
    Serial.read();

  while ((looping == 1) && (Serial.available() == 0))
  {
    if (externalLoopBackTest() == 0)
      passCount++;
    else
      failCount++;

    Serial.print("Loopback Test PASS = ");
    Serial.print(passCount);
    Serial.print(", FAIL = ");
    Serial.println(failCount);
  }
}

/*
  uint8_t externalLoopBackTest()
  Set up the first chip as outputs and the second chip as inputs
  First and second chips are wired bit-to-bit
  High and low values are bounced across the 16-bits and checked
*/

uint8_t externalLoopBackTest(void)
{
  uint8_t port;
  uint8_t pass0fail1 = 0;

  for (port = 0; port < 16; port++)
  {
    Dio32.pinMode(port, OUTPUT);
    Dio32.pinMode(port + 16, INPUT_PULLUP);

    delay(2);
    Dio32.digitalWrite(port, HIGH);
    delay(2);
    if (Dio32.digitalRead(port + 16) != HIGH)
    {
      Serial.print("Error on chip 0");
      Serial.print(" and port ");
      Serial.print(port);
      Serial.println(" Expected High");
      pass0fail1 = 1;
    }
    Dio32.digitalWrite(port, LOW);
    delay(2);
    if (Dio32.digitalRead(port + 16) != LOW)
    {
      Serial.print("Error on chip 0");
      Serial.print(" and port ");
      Serial.print(port);
      Serial.println(" Expected LOW");
      pass0fail1 = 1;
    }
    Dio32.pinMode(port, INPUT);
    delay(2);
  }
  for (port = 0; port < 32; port++)
    Dio32.pinMode(port, INPUT);

  return pass0fail1;
}

/*
  uint8_t loopBackTest()
  Set up the first chip as outputs and the second chip as inputs
  First and second chips are wired bit-to-bit
  High and low values are bounced across the 16-bits and checked
*/

uint8_t internalLoopBackTest(void)
{
  uint8_t port;
  uint8_t chip;
  uint8_t pass0fail1 = 0;
  uint16_t rdVal;
  uint16_t bit;
  for (port = 0; port < 32; port++)
    Dio32.pinMode(port,OUTPUT);
  for (chip = 0; chip < CHIP_COUNT; chip++)
  {
    for (bit = 1; bit != 0; bit <<= 1)
    {
      Dio32.writeOLATAB(chip,bit);
      rdVal = Dio32.readGPIOAB(chip);
      if (rdVal != bit)
      {
        Serial.print("internalLoopBackTest(): Test failed - Could not set chip: ");
        Serial.println(chip);
        Serial.print("Expected: 0x");
        Serial.print(bit);
        Serial.print(", Got: 0x");
        Serial.println(rdVal);
        pass0fail1 = 1;
      }
    }
  }
  for (port = 0; port < 32; port++)
    Dio32.pinMode(port,INPUT);
  return pass0fail1;
}
