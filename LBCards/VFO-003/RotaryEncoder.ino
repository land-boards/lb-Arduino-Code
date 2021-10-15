// Rotary encoder reading
// There is a debouncing r/c and 74AC14 buffer on the totary encoder outputs and switch
// Rotary encoder scrolls between options
// Press encoder button to select

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
  pinMode(ROTARY_CLK, INPUT);
  pinMode(ROTARY_DATA, INPUT);
  pinMode(encoderSwitch, INPUT);
}

// waitForControlChange()
// Wait around for an encoder change (knob turn or button)
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
// Translate values into enum
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
    return(0);
  if (swC == 1)  // Down
  {
    while (readRotarySwitch() != 0)
      delay(100);
    return(-1);
  }
  else if (swC == 2)  // Up
  {
    while (readRotarySwitch() != 0)
      delay(100);
    return(1);
  }
}

// readRotarySwitch()
// Pack the rotary switch lines into two bits
uint8_t readRotarySwitch(void)
{
  uint8_t swA, swB, swC;
  swA = digitalRead(ROTARY_CLK);
  swB = digitalRead(ROTARY_DATA);
  swC = (swA << 1) | swB;
  return (swC);
}

// checkSwitch()
// Check the rotary encoder switch
// If rotary encoder is pressed, waits until switch is released before return
// VFO-003 has switch pulled up but buffered by 74AC14 inverter so encoderSwitch goes high when pressed
// If switch is pressed return 1
uint8_t checkSwitch(void)
{
  if (digitalRead(encoderSwitch) == 1)
  {
    while (digitalRead(encoderSwitch) == 1)
      delay(100);    // Debounce
    return (1);
  }
  return (0);
}
