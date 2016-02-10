/* Rotary Encoder Demo

   David Johnson-Davies - www.technoblogy.com - 3rd October 2015
   ATtiny85 @ 1 MHz (internal oscillator; BOD disabled)
   
   CC BY 4.0
   Licensed under a Creative Commons Attribution 4.0 International license: 
   http://creativecommons.org/licenses/by/4.0/
*/

// ATtiny85 inputs/outputs
const int LED = 4;
const int LED2 = 2;
const int EncoderA = 1;
const int EncoderB = 0;
const int EncoderSwitch = 3;

// Global - lamp brightness
volatile int Brightness = 128;
int Laststate;
int swTurned;

// Pin change interrupt service routine
ISR (PCINT0_vect) {
  digitalWrite(LED2,swTurned);
  swTurned ^= 1;
  int Gray = (PINB & ((1<<EncoderA)|(1<<EncoderB)));               // Read PB1 and PB2
  int State = (Gray>>1) ^ Gray;              // Convert from Gray code to binary
  if (State != Laststate) {
    int Value = ((Laststate-State) & 3) - 2; // Gives -1 or +1
    ChangeValue(Value);
    Laststate=State;
  } 
  GIFR = 1<<PCIF;                            // Clear pin change interrupt flag.
}

// Called when encoder is rotated; Change is -1 (anticlockwise) or 1 (clockwise)
void ChangeValue (int Change) {
  Brightness = max(min(Brightness+Change, 255), 0);
  analogWrite(LED, Brightness);
}

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(EncoderA, INPUT_PULLUP);
  pinMode(EncoderB, INPUT_PULLUP);
  pinMode(EncoderSwitch, INPUT_PULLUP);
  // Configure pin change interrupts on PB0, PB1, and PB3
  PCMSK |= 1<<PCINT0 | 1<<PCINT1;
  GIMSK = 1<<PCIE;                // Enable pin change interrupts
  GIFR = 1<<PCIF;                 // Clear pin change interrupt flag.
  analogWrite(LED, Brightness);
  swTurned = 1;
  digitalWrite(LED2,swTurned);
}

// Everything done under interrupt!
void loop() {
}
