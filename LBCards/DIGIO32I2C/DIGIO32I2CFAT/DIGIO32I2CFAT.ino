//////////////////////////////////////////////////////////
// DIGIO32I2CFAT : DIGIO32-I2C Factory Test code
// Test each channel
// Read/write EEPROM
// Tested in Arduino Uno/Arduino NANO cards
// Use Serial Port for menu/test results
//////////////////////////////////////////////////////////

#if defined(ARDUINO_ARCH_AVR)
  // AVR-specific code
#else
  #error This library only supports boards with an AVR processor.
#endif

#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 mcp0;   // Uses the Adafruit MCP23017 library - globals
Adafruit_MCP23017 mcp1;

uint32_t failCount;       // Globals used in the below code
uint32_t passCount;
int looping;

//////////////////////////////////////////////////////////
// setup()
//////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(9600);     // 9600 baud serial connection
  mcp0.begin(0);          // Instantate two MCP23017 chips
  mcp1.begin(1);
  
#if defined(ARDUINO_ARCH_AVR)
  //  TWBR = 12;    // go to 400 KHz I2C speed mode
#endif

  for (uint8_t chip = 0; chip < 2; chip++)  // Set all of the ports to inputs with pullups on
  {
    for (uint8_t port = 0; port < 16; port++)
    {
      mcpPullUp(chip, port, HIGH);
      mcpPinMode(chip, port, INPUT);
    }
  }
  failCount = 0;  // Initialize the test variables
  passCount = 0;
  looping = 0;
  Serial.print("Running loopback test...");
  if (loopBackTest() != 0)
    Serial.println("Failed loopback test");
  else
    Serial.println("Passed loopback test");
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
  Serial.println("R=Read EEPROM, W=Write EEPROM, T=Test DIGIOs, L=Loop Mode, B=Blink LEDs");  // Test menu
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
    else if ((incomingByte == 'T') || (incomingByte == 't'))
    {
      if (loopBackTest() == 0)
        passCount++;
      else
        failCount++;
      Serial.print("Loopback Test PASS = ");
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
      while (Serial.available() == 0)
      {
        for (uint8_t port = 0; port < 16; port++)
        {
          mcpPinMode(0, port, OUTPUT);
          mcpWrite(0, port, HIGH);
          delay(2);
          mcpWrite(0, port, LOW);
          delay(2);
        }
        for (uint8_t port = 0; port < 16; port++)
        {
          mcpPinMode(1, port, OUTPUT);
          mcpWrite(1, port, HIGH);
          delay(2);
          mcpWrite(1, port, LOW);
          delay(2);
        }
      }
    }
    else
    {
      if (looping == 1)
        looping = 0;
      else
        Serial.println("Unrecognized command");
      Serial.println("\nR=Read EEPROM, W=Write EEPROM, T=Test DIGIOs, L=Loop Test");
    }
  }

  while (Serial.available() > 0)    // Flush extra read data (CR-LF extras)
    Serial.read();

  while ((looping == 1) && (Serial.available() == 0))
  {
    if (loopBackTest() == 0)
      passCount++;
    else
      failCount++;

    Serial.print("Loopback Test PASS = ");
    Serial.print(passCount);
    Serial.print(", FAIL = ");
    Serial.println(failCount);
  }
}

/* mcpPinMode(chipNum, chNum, val)
  Set the pin to be an input or output.
  chipNum is from 0-7
  chNum is from 0-15
  val is INPUT or OUTPUT
*/
void mcpPinMode(uint8_t chipNum, uint8_t chNum, uint8_t val)
{
  switch (chipNum)
  {
    case 0:
      mcp0.pinMode(chNum, val);
      break;
    case 1:
      mcp1.pinMode(chNum, val);
      break;
  }
}

/* mcpPullUp(chipNum, chNum, val)
  Set the pull up for a channel.
  chipNum is from 0-7
  chNum is from 0-15
  val is HIGH to turn on pull up and LOW to turn off pullup
*/
void mcpPullUp(uint8_t chipNum, uint8_t chNum, uint8_t val)
{
  switch (chipNum)
  {
    case 0:
      mcp0.pullUp(chNum, val);
      break;
    case 1:
      mcp1.pullUp(chNum, val);
      break;
  }
}

/*
  uint8_t loopBackTest()
  Set up the first chip as outputs and the second chip as inputs
  First and second chips are wired bit-to-bit
  High and low values are bounced across the 16-bits and checked
*/

uint8_t loopBackTest(void)
{
  uint8_t port;
  uint8_t pass0fail1 = 0;

  for (port = 0; port < 16; port++)
  {
    mcpPinMode(0, port, OUTPUT);
    mcpPinMode(1, port, INPUT);
    mcpPullUp(1, port, HIGH);

    delay(2);
    mcpWrite(0, port, HIGH);
    delay(2);
    if (mcpRead(1, port) != HIGH)
    {
      Serial.print("Error on chip 0");
      Serial.print(" and port ");
      Serial.print(port);
      Serial.println(" Expected High");
      pass0fail1 = 1;
    }
    mcpWrite(0, port, LOW);
    delay(2);
    if (mcpRead(1, port) != LOW)
    {
      Serial.print("Error on chip 0");
      Serial.print(" and port ");
      Serial.print(port);
      Serial.println(" Expected LOW");
      pass0fail1 = 1;
    }
    mcpPinMode(0, port, INPUT);
    delay(2);
  }

  return pass0fail1;
}

/* mcpRead(chipNum, chNum)
  Reads a channel.
  chipNum is from 0-7
  chNum is from 0-15
  Returns the value of the pin
*/
uint8_t mcpRead(uint8_t chipNum, uint8_t chNum)
{
  switch (chipNum)
  {
    case 0:
      return (mcp0.digitalRead(chNum));
      break;
    case 1:
      return (mcp1.digitalRead(chNum));
      break;
  }
}

//////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////

/* mcpWrite(chipNum, chNum, val)
  Write a value to a pin.
  chipNum is from 0-7
  chNum is from 0-15
  val is LOW or HIGH
*/
void mcpWrite(uint8_t chipNum, uint8_t chNum, uint8_t val)
{
  switch (chipNum)
  {
    case 0:
      mcp0.digitalWrite(chNum, val);
      break;
    case 1:
      mcp1.digitalWrite(chNum, val);
      break;
  }
}

