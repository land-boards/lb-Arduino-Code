////////////////////////////////////////////////////////////////////////////////
// Logic Tester
// Puts out bits
// Reads back bits
// Checks the bits that it read back
// Table oriented
////////////////////////////////////////////////////////////////////////////////

#include "LandBoards_Digio128.h"
#include "DIGIO128TESTER-DEFS.h"   // DIGIO-128 Discrete pins are listed here

// Mapping to DIGIO-128 lines

#define LO 0
#define HI 1
#define IGNORE 2

#define NUMBER_TEST_STEPS 2
#define INPUT_LINES 1
#define OUTPUT_LINES 1

// The read line values expected for each test step
uint8_t readDiscretesTable[NUMBER_TEST_STEPS][INPUT_LINES] = {
{LO},
{HI},
};

uint8_t discretesDriveTable[NUMBER_TEST_STEPS][OUTPUT_LINES] = {
{LO},
{HI},
};

// The pin names of the output lines
uint8_t discreteDriveLines[OUTPUT_LINES] = {
ONE_OUT_BIT,
};

// The pin names of the input lines
uint8_t discreteReadLines[INPUT_LINES] = {
ONE_IN_BIT
};

////////////////////////////////////////////////////////////////////////////////
// checkVector() Check the outputs from the UUT
// Returns 1 if failed
// Returns 0 if passed
////////////////////////////////////////////////////////////////////////////////

uint8_t checkVector(uint8_t currentStep)
{
  if (Dio128.digitalRead(discreteReadLines[0]) != readDiscretesTable[currentStep])
  {
    Serial.print("Error in firstBit Value. Expected to get: ");
    Serial.print(Dio128.digitalRead(readDiscretesTable[currentStep]));
    Serial.print(". Instead, got: ");
    Serial.println(Dio128.digitalRead(ONE_IN_BIT));
    return (1);
  }
  return (0);
}

////////////////////////////////////////////////////////////////////////////////
// Write all of the outputs (from Tester to UUT) lines
// drive the discrete lines
////////////////////////////////////////////////////////////////////////////////

void putVector(uint8_t currentStep)
{
  Dio128.digitalWrite(discreteDriveLines[0], discretesDriveTable[currentStep][0]);
}

////////////////////////////////////////////////////////////////////////////////
// Go through the states one at a time
////////////////////////////////////////////////////////////////////////////////

uint8_t runStates(uint8_t continueFlag)
{
  uint8_t failedFlag = 0;
  if (checkCableLoopBacks() != 0)
    return(1);
  checkPower();
  initLogicTest();
  for (stepNum = 0; stepNum < NUMBER_TEST_STEPS; stepNum++)
  {
    Serial.print(F("At Step:"));
    Serial.print(stepNum);
    Serial.print(F(" "));
    putVector(stepNum);
    if (checkVector(stepNum) != 0)
    {
      Serial.println(F("- ***FAILED***"));
      delay(10);
      if (continueFlag == 0)
        return (1);
      failedFlag = 1;
    }
    else
      Serial.println(F("- Passed"));
    delay(10);
  }
  if (failedFlag == 0)
    Serial.println(F("Passed all tests"));
  else
    Serial.println(F("Failed test(s) - See log"));    
}

////////////////////////////////////////////////////////////////////////////////
// Initialize the states of the Logic Test
////////////////////////////////////////////////////////////////////////////////

void initLogicTest(void)
{
  // Preset the output values for the first test
  for (uint8_t bitCounter = 0; bitCounter < OUTPUT_LINES; bitCounter++)
  {
    Dio128.digitalWrite(discreteDriveLines[bitCounter],discretesDriveTable[0][bitCounter]);
    Dio128.pinMode(discreteDriveLines[bitCounter],OUTPUT);
  }

  // Make sure the inputs are inputs
  for (uint8_t bitCounter = 0; bitCounter < OUTPUT_LINES; bitCounter++)
  {
    Dio128.pinMode(discreteReadLines[0], HIGH);
    Dio128.pinMode(discreteReadLines[0], INPUT);
  }
}

