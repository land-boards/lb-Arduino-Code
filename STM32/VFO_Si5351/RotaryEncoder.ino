// Robust Rotary encoder reading
// Clean no-bounce rotary switch code
// polled rotary switch implementation based on
// Copyright John Main - https://www.best-microcontroller-projects.com/rotary-encoder.html
// Does not need caps on encoder pins

#define CLK PB1
#define DATA PB0

static int encoder0Pos = 0;
static uint8_t prevNextCode = 0;
static uint16_t store = 0;

void setupEncoder() {
  pinMode(CLK, INPUT);
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DATA, INPUT);
  pinMode(DATA, INPUT_PULLUP);
}

void pollEncoder()
{
  static int8_t val;
  if ( val = read_rotary() )
    encoder0Pos += val;
}

// A vald CW or  CCW move returns 1, invalid returns 0.
int8_t read_rotary()
{
  static int8_t rot_enc_table[] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0};

  prevNextCode <<= 2;
  if (digitalRead(DATA)) prevNextCode |= 0x02;
  if (digitalRead(CLK)) prevNextCode |= 0x01;
  prevNextCode &= 0x0f;

  // If valid then store as 16 bit data.
  if  (rot_enc_table[prevNextCode] ) {
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
    return(1);
  }
  else if (encoder0Pos < 0)
  {
    encoder0Pos = 0;
    return(-1);
  }
  else
  {
    return(0);
  }
}
