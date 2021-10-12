// Rotary encoder reading

#define CLK 3
#define DATA 2

enum ControlsState
{
  NOTHING,
  ENC_SW_PRESSED,
  ENC_UP,
  ENC_DOWN
};

// setupEncoder()
void setupEncoder()
{
  pinMode(CLK, INPUT);
  pinMode(DATA, INPUT);
  pinMode(encoderSwitch, INPUT);
}

// waitForControlChange()
// Wait around for an encoder change
uint8_t waitForControlChange(void)
{
  uint8_t controlVal;
  while (1)
  {
    do
    {
      controlVal = checkControls();
    }
    while (controlVal == NOTHING);
    return (controlVal);
  }
}

// checkControls()
uint8_t checkControls()
{
  int8_t encoderDelta = 0;
  if (checkSwitch() == 1)
    return ENC_SW_PRESSED;
  encoderDelta += read_rotary();
  if (encoderDelta == 0)
    return (NOTHING);
  else if (encoderDelta >= 1)
    return (ENC_UP);
  else if (encoderDelta <= -1)
    return (ENC_DOWN);
  return (NOTHING);
}

// read_rotary()
// Read the rotary switch
int8_t read_rotary()
{
  uint8_t swC;
  swC = readRotarySwitch();
  if (swC == 0)
  {
    return(0);
  }
  if (swC == 2)  // Up
  {
    while (readRotarySwitch() != 0);
    delay(50);
    return(1);
  }
  else if (swC == 1)  // Down
  {
    while (readRotarySwitch() != 0);
    delay(50);
    return(-1);
  }
}

// readRotarySwitch()
uint8_t readRotarySwitch(void)
{
  uint8_t swA, swB, swC;
  swA = digitalRead(CLK);
  swB = digitalRead(DATA);
  swC = (swA << 1) | swB;
  return (swC);
}

// Check the rotary encoder switch
// If rotary encoder is pressed, waits until switch is released before return
// If switch is pressed return 1
uint8_t checkSwitch(void)
{
  if (digitalRead(encoderSwitch) == 1)
  {
    while (digitalRead(encoderSwitch) == 1)
      delay(50);    // Debounce
    return (1);
  }
  return (0);
}
