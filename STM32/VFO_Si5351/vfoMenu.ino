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

// Menu options
// Menu is entered by pressing encoder button
void vfoMenu(void)
{
  setVFOStepSize();
  delay(1000);
}

// If pressed, waits until switch is released before return
// If switch is pressed return 1
int checkSwitch(void)
{
  if (digitalRead(encoderSwitch) == 0)
  {
    while (digitalRead(encoderSwitch) == 0)
      delay(50);    // Debounce
    //Serial.print("Button Pressed\n");
    return (1);
  }
  return (0);
}

//int getEncoderDelta(void)
//{
//  if (encoder0Pos == 0)
//  {
//    return (0);
//  }
//  else if (encoder0Pos < 0)
//  {
//    encoder0Pos = 0;
//    return (-1);
//  }
//  else if (encoder0Pos > 0)
//  {
//    encoder0Pos = 0;
//    return(1);
//  }
//}
