/////////////////////////////////////////////////////////////////////////////////////////
// NewPot-X1 - Arduino Code to interface an incremental rotary switch
//   to an ATTiny85.
// LED is controlled via PWM to dim/brighten based on turning the knob.
// Using NewPot card:
//   http://land-boards.com/blwiki/index.php?title=NewPot
// Uses SPI-PotX2 Digital Pot
//  http://land-boards.com/blwiki/index.php?title=SPI-POTX2
//
// This code is based in part on:
// Rotary Encoder Demo
//
//   David Johnson-Davies - www.technoblogy.com - 3rd October 2015
//   ATtiny85 @ 1 MHz (internal oscillator; BOD disabled)
//
//   CC BY 4.0
//   Licensed under a Creative Commons Attribution 4.0 International license:
//   http://creativecommons.org/licenses/by/4.0/
//
// Encoder Switch resets the ATTiny85.
// Also the port assignments are different.
// Some of the port assignment stuff was hardcoded and the hardcoding was removed.
// Made Laststate a global.
// Set potValue in the setup code.
// Using external pullups rather than the pullups in the ATTiny85.
// Each click of encoder includes four state changes
// Eliminates LED and replaces with Digital Pot
/////////////////////////////////////////////////////////////////////////////////////////
// ATTiny support - board manager
// https://github.com/SpenceKonde/ATTinyCore
//  Add path to support files (File|Preferences|Additional Boards Manager URLs):
//  Can use a comma to add to list or click the add box
//  Add the following
//    http://drazzy.com/package_drazzy.com_index.json
/////////////////////////////////////////////////////////////////////////////////////////

// ATtiny85 inputs/outputs
const int EncoderA = 0;		// Encoder pins
const int EncoderB = 1;
//static const int8_t MOSI = 2;			// SPI-POT pins
//static const int8_t SCK = 3;
const int CS = 4;

// Globals
int Laststate;
uint16_t rotaryCount;

/////////////////////////////////////////////////////////////////////////////////////////
// Pin change interrupt service routine
// This code was originally written increments on both edges
/////////////////////////////////////////////////////////////////////////////////////////

ISR (PCINT0_vect)
{
  int Gray = (PINB & ((1 << EncoderA) | (1 << EncoderB))); // Read PB1 and PB2
  int State = (Gray >> 1) ^ Gray;            // Convert from Gray code to binary
  if (State != Laststate) {
    int Value = ((Laststate - State) & 3) - 2; // Gives -1 or +1
    ChangeValue(Value);
    Laststate = State;
  }
  GIFR = 1 << PCIF;                          // Clear pin change interrupt flag.
}

/////////////////////////////////////////////////////////////////////////////////////////
// ChangeValue()
// Called when encoder is rotated; Change is -1 (anticlockwise) or 1 (clockwise)
/////////////////////////////////////////////////////////////////////////////////////////

void ChangeValue (int Change)
{
  uint16_t oldRotaryCount = rotaryCount;
  rotaryCount = max(min(rotaryCount + Change, 512), 0);
  if ((oldRotaryCount >> 2) != (rotaryCount >> 2))
    writePotValue(rotaryCount >> 2);
}

/////////////////////////////////////////////////////////////////////////////////////////
// writePotBit(int bitToWrite)
/////////////////////////////////////////////////////////////////////////////////////////

void writePotBit(uint16_t bitToWrite)
{
  digitalWrite(SCK, LOW);
  if (bitToWrite)
    digitalWrite(MOSI, HIGH);
  else
    digitalWrite(MOSI, LOW);
  digitalWrite(SCK, HIGH);
}

/////////////////////////////////////////////////////////////////////////////////////////
// writePotValue(int)
/////////////////////////////////////////////////////////////////////////////////////////

void writePotValue(uint16_t potValue)
{
  uint16_t bitToWrite = 0x8000;
  uint16_t commandWord = 0x0000;
  commandWord |= (potValue & 0x00ff);
  digitalWrite(CS, LOW);
  for (int i = 0; i < 16; i++)
  {
    writePotBit(commandWord & bitToWrite);
    bitToWrite >>= 1;
  }
  digitalWrite(CS, HIGH);
}

/////////////////////////////////////////////////////////////////////////////////////////
// setup() - Configure the pins of the ATTiny (direction control)
/////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  pinMode(EncoderA, INPUT);
  pinMode(EncoderB, INPUT);
  pinMode(MOSI, OUTPUT);
  digitalWrite(MOSI, LOW);
  pinMode(SCK, OUTPUT);
  digitalWrite(SCK, HIGH);
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);

  PCMSK |= 1 << PCINT0 | 1 << PCINT1; // Pin change interrupt mask
  GIMSK = 1 << PCIE;               // Enable pin change interrupts
  GIFR = 1 << PCIF;                // Clear pin change interrupt flag.
  rotaryCount = 256;
  writePotValue(rotaryCount >> 2);	// half scale
}

/////////////////////////////////////////////////////////////////////////////////////////
// loop)() - Everything done under interrupt!
/////////////////////////////////////////////////////////////////////////////////////////

void loop()
{
}
