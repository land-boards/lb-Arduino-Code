// RotaryEncoder
// Robust Rotary encoder reading
// Rotary encoder scrolls between options
// Press encoder button to select
//
// Polled rotary switch implementation based on
// Copyright John Main - https://www.best-microcontroller-projects.com/rotary-encoder.html
//  Look undder "Code For Improved Table Decode" near bottom of page
// Clean no-bounce rotary switch code

static int encoder0Pos = 0;
static uint8_t prevNextCode = 0;
static uint16_t store = 0;

// setupEncoder()
void setupEncoder()
{
  pinMode(ROTARY_CLK, INPUT);
  pinMode(ROTARY_DATA, INPUT);
  pinMode(encoderSwitch, INPUT);
}

// A vald CW or  CCW move returns 1, invalid returns 0.
int8_t read_rotary()
{
  static int8_t rot_enc_table[] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0};

  prevNextCode <<= 2;
  if (digitalRead(ROTARY_DATA)) prevNextCode |= 0x02;
  if (digitalRead(ROTARY_CLK))  prevNextCode |= 0x01;
  prevNextCode &= 0x0f;

  // If valid then store as 16 bit data.
  if  (rot_enc_table[prevNextCode])
  {
    store <<= 4;
    store |= prevNextCode;

    if ((store & 0xff) == 0x2b)
      return -1;
    if ((store & 0xff) == 0x17)
      return 1;
  }
  return 0;
}

int getEncoderDelta(void)
{
  if (encoder0Pos > 0)
  {
    encoder0Pos = 0;
    return (1);
  }
  else if (encoder0Pos < 0)
  {
    encoder0Pos = 0;
    return (-1);
  }
  else
  {
    return (0);
  }
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
  
  uint8_t checkSwitch(void)
  {
    if (digitalRead(encoderSwitch) == 0)
    {
      while (digitalRead(encoderSwitch) == 0)
        delay(100);    // Debounce
      return (1);
    }
    return (0);
  }
  
