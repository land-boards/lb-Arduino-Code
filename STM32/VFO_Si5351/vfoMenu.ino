#define STEP_100_HZ 10000ULL
#define STEP_1_KHZ  100000ULL
#define STEP_10_KHZ 1000000ULL
#define STEP_100_KHZ 10000000ULL

void setVFOStepSize(void)
{
  if (stepSize == STEP_100_HZ)
  {
    stepSize = STEP_1_KHZ;
    printStringToOLED("Step 1 KHz");
  }
  else if (stepSize == STEP_1_KHZ)
  {
    stepSize = STEP_10_KHZ;
    printStringToOLED("Step 10 KHz");
  }
  else if (stepSize == STEP_10_KHZ)
  {
    stepSize = STEP_100_KHZ;
    printStringToOLED("Step 100 KHz");
  }
  else if (stepSize == STEP_100_KHZ)
  {
    stepSize = STEP_100_HZ;
    printStringToOLED("Step 100 Hz");
  }
}

enum MenuStateValues
{
  SET_STEP_SIZE,
  SET_FREQ,
  SELECT_VFO,
  VFO_ON_OFF
};

enum ControlsState
{
  NOTHING,
  ENC_SW_PRESSED,
  ENC_UP,
  ENC_DOWN
};

MenuStateValues menuState = SET_STEP_SIZE;

void displayTopMenuOption()
{
  if (menuState == SET_STEP_SIZE)
  {
    printStringToOLED("Set Step Size");
  }
  else if (menuState == SET_FREQ)
  {
    printStringToOLED("Set fREQ");
  }
  else if (menuState == SELECT_VFO)
  {
    printStringToOLED("Select VFO");
  }
}

// Menu options
// Menu is entered by pressing encoder button
void vfoMenu(void)
{
  uint8_t controlVal;
  displayTopMenuOption();
  while(1)
  {
    do
    {
      controlVal = checkControls();
    }
    while (controlVal == NOTHING);
    //Serial.print("Encoder action\n");
    if (controlVal == ENC_SW_PRESSED)
    {
      //Serial.print("Button pressed\n");
      printStringToOLED("Button presst");
    }
    else if (controlVal == ENC_UP)
    {
      //Serial.print("Up\n");
      printStringToOLED("Enc up");
    }
    else if (controlVal == ENC_DOWN)
    {
      //Serial.print("Down\n");
      printStringToOLED("Emc down");
    }
//    setVFOStepSize();
  }
}

uint8_t checkControls()
{
  int encoderDelta = 0;
  if (checkSwitch() == 1)
    return ENC_SW_PRESSED;
  pollEncoder();
  encoderDelta = getEncoderDelta();
  if (encoderDelta == 0)
    return(NOTHING);
  else if (encoderDelta == 1)
    return(ENC_UP);
  else if (encoderDelta == -1)
    return(ENC_DOWN);
  return(NOTHING);
}
