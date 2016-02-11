/////////////////////////////////////////////////////////////////////////////////////////
// RotarySwitchBasic - Arduino Code to interface an incremental rotary switch to an ATTiny85.
// LED is controlled via PWM to dim/brighten based on turning the knob.
// Using TinyGrid85 card:
//   http://land-boards.com/blwiki/index.php?title=TinyGrid85
// Wired Rotary Switch to Digital Pins 0 and 1
// Added 10K pullups on the Rotary Switch pins
// Wired LED to Digital Pin 4
// Code is based in part on: 
// Rotary Encoder Demo
//
//   David Johnson-Davies - www.technoblogy.com - 3rd October 2015
//   ATtiny85 @ 1 MHz (internal oscillator; BOD disabled)
//   
//   CC BY 4.0
//   Licensed under a Creative Commons Attribution 4.0 International license: 
//   http://creativecommons.org/licenses/by/4.0/
//
// Differences are that the Encoder Switch is not used.
// Also the port assignments are different.
// Some of the port assignment stuff was hardcoded and the hardcoding was removed.
// Made Laststate a global.
// Set brightness in the setup code.
// Using external pullups rather than the pullups in the ATTiny85.
// Each click of encoder includes four state changes
/////////////////////////////////////////////////////////////////////////////////////////

// ATtiny85 inputs/outputs
const int EncoderA = 1;
const int EncoderB = 0;
const int LED = 4;

// Globals
volatile int Brightness = 512;
int Laststate;

/////////////////////////////////////////////////////////////////////////////////////////
// Pin change interrupt service routine
// Seems like this code as it was originally written increments on both edges
/////////////////////////////////////////////////////////////////////////////////////////

ISR (PCINT0_vect) 
{
  int Gray = (PINB & ((1<<EncoderA)|(1<<EncoderB)));               // Read PB1 and PB2
  int State = (Gray>>1) ^ Gray;              // Convert from Gray code to binary
  if (State != Laststate) {
    int Value = ((Laststate-State) & 3) - 2; // Gives -1 or +1
    ChangeValue(Value);
    Laststate=State;
  } 
  GIFR = 1<<PCIF;                            // Clear pin change interrupt flag.
}

/////////////////////////////////////////////////////////////////////////////////////////
// Called when encoder is rotated; Change is -1 (anticlockwise) or 1 (clockwise)
/////////////////////////////////////////////////////////////////////////////////////////

void ChangeValue (int Change) 
{
  Brightness = max(min(Brightness+Change, 1023), 0);
  analogWrite(LED, Brightness>>2);
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(EncoderA, INPUT);
  pinMode(EncoderB, INPUT);
  PCMSK |= 1<<PCINT0 | 1<<PCINT1;  // Pin change interrupt mask
  GIMSK = 1<<PCIE;                 // Enable pin change interrupts
  GIFR = 1<<PCIF;                  // Clear pin change interrupt flag.
  analogWrite(LED, Brightness>>2);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Everything done under interrupt!
/////////////////////////////////////////////////////////////////////////////////////////

void loop() 
{
}

