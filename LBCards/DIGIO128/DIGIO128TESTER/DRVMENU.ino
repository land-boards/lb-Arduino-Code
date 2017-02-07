////////////////////////////////////////////////////////////////////////////////
// testMenu - The card standalone test station menu code
////////////////////////////////////////////////////////////////////////////////

#include "DIGIO128TESTER-DEFS.h"
#include "LandBoards_Digio128.h"

void testMenu(void)
{
  int incomingByte = 0;
  while (Serial.available() > 0)
    Serial.read();
  Serial.println(F("\n****Test Options****\nT=run Tests\nC=run tests Continue\nF=blink Fail LED\nV=UUT In/Out Vector\nX=Reset Tester\nR=Read a bit\nW=Write a bit\nG=toGgle Bit\nH=Help\n Select > "));
  while (Serial.available() == 0);
  incomingByte = Serial.read();
//  Serial.write(incomingByte); // echo
  switch (incomingByte)
  {
    case 'T':       // Run Tests in Stop on Failure Mode
    case 't':
      runStates(0); 
      break;
    case 'C':       // Run Tests in Continue Mode
    case 'c':
      runStates(1); 
      break;
    case 'R':       // Read a bit
    case 'r':
      readABit();
      break;
    case 'W':     // Write a bit
    case 'w':
      writeABit();
      break;
    case 'G':       // Toggle an output bit on one of the DIGIO lines
    case 'g':
      toggleABit();
      break;
    case 'F':       // Blink the fail LED forever
    case 'f':
      blinkFailLedForever();
      break;
    case 'V':       // Dump the UUT vector (inputs and outputs)
    case 'v':
      dumpUUTVector();
      break;
    case 'X':
    case 'x':
      setAllToInputs();
      break;
    case 'H':
    case 'h':
    case '?':
      helpMenu();
      break;
    default:
      Serial.println(F("Not a legal menu choice"));
      break;
  }
  while (Serial.available() > 0)
    Serial.read();
}

////////////////////////////////////////////////////////////////////////////////
// helpMenu() - Print the menu options
////////////////////////////////////////////////////////////////////////////////

void helpMenu(void)
{
   Serial.println(F("Program options"));
   Serial.println(F("T - Run all of the tests and halt on the first error"));
   Serial.println(F("C - Run all of the tests and continue if errors"));
   Serial.println(F("V - Dump the current test vector"));
   Serial.println(F("F - Blink the LED attached to DIGIO channel 128"));
   Serial.println(F("R - Read a bit from the one of the DIGIO channels"));
   Serial.println(F("  Prompts for the bit number to read (0-127)"));
   Serial.println(F("W - Write a bit to one of the DIGIO channels"));
   Serial.println(F("  Prompts for the bit number to channel (0-127)"));
   Serial.println(F("  Prompts for the value to write (0 or 1)"));
   Serial.println(F("G - Toggle a bit to one of the DIGIO channels"));
   Serial.println(F("  Prompts for the bit number to channel (0-127)"));
   Serial.println(F("X - Resets the Tester - all lines are set to input lines"));
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void setAllToInputs(void)
{
  initDigio128();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void dumpUUTVector(void)
{
  Serial.print(F("\nTest Vector, Step = "));
  Serial.println(stepNum);
  Serial.println(F("I||O"));
  Serial.print(Dio128.digitalRead(ONE_OUT_BIT));
  Serial.print("  ");
  Serial.println(Dio128.digitalRead(ONE_IN_BIT));
 }

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

uint32_t getSerialInteger(void)
{
  int inChar;
  uint32_t accumLong = 0;
  // Read serial input:
  while (Serial.available() > 0)
    Serial.read();
  while (1)
  {
    if (Serial.available() > 0)
    {
      int readChar = Serial.read();
      Serial.write(readChar);
      if ((readChar == 0x0a) || (readChar == 0x0d))
      {
        //        Serial.print(F("accumLong="));
        return (accumLong);
      }
      if ((readChar >= '0') && (readChar <= '9'))
        accumLong = (accumLong * 10) + readChar - '0';
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

void readABit(void)
{
  uint32_t addressToRead;
  Serial.setTimeout(10000);
  Serial.print(F("DIGIO-128 Bit to read:"));
  addressToRead = getSerialInteger();
//  Serial.print(addressToRead);
  Serial.print(F(", read value="));
  Serial.println(Dio128.digitalRead(addressToRead));
}

//
void writeABit(void)
{
  uint8_t addressToWrite;
  uint8_t valueToWrite;
  Serial.setTimeout(10000);
  Serial.print(F("DIGIO-128 Bit to write:"));
  addressToWrite = getSerialInteger();
//  Serial.println(addressToWrite);
  Serial.print(F("Value:"));
  valueToWrite = getSerialInteger();
  valueToWrite &= 0x1;
//  Serial.println(valueToWrite);
//  Dio128.pinMode(addressToWrite, OUTPUT);
  Dio128.digitalWrite(addressToWrite, valueToWrite);
}

////////////////////////////////////////////////////////////////////////////////
// Toggle a bit every half second
////////////////////////////////////////////////////////////////////////////////

void toggleABit(void)
{
  uint8_t addressToWrite;
  uint8_t valueToWrite = 0;
  Serial.setTimeout(10000);
  Serial.print(F("DIGIO-128 Bit to toggle:"));
  addressToWrite = getSerialInteger();
//  Serial.println(addressToWrite);
  Dio128.pinMode(addressToWrite, OUTPUT);
  
  do
  {
    Dio128.digitalWrite(addressToWrite, valueToWrite);
    valueToWrite ^= 1;
    delay(250);
  }
  while (Serial.available() == 0);
  while (Serial.available() > 0)
    Serial.read();
    
}

