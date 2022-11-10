// ************************************************************************
// AUDUINO - MIDI Upgrade v1.1
// For Arduino NANO
//
// MIDI programming by Notes and Volts http://www.notesandvolts.com
//
// Tutorial - http://www.notesandvolts.com/2015/05/auduino-synth-midi.html
// 
// ** Requires Arduino MIDI Library v4.2 or later **
//
// Based on the Auduino Synthesizer v5 by Peter Knight http://tinker.it
// ************************************************************************
// Version 1.0 - Initial release
// Version 1.1 - Fixed bug that caused note to hang with some DAWs
// ************************************************************************

#include <avr/io.h>
#include <avr/interrupt.h>
#include <MIDI.h> // Requires Arduino MIDI Library v4.2 or later
                  // https://github.com/FortySevenEffects/arduino_midi_library

// *** MIDI Parameters ***********************************************************
#define BENDRANGE 12 // Change to set Number of Semitones for Pitch Bend (1 to 24)
// *******************************************************************************
// If the DIP Switch option is installed - set dipSwitchInstalled to "true"
const bool dipSwitchInstalled = false;
// DIP Switch Setting = Channel (1=ON, 0=OFF)
// 0000 = 1   0001 = 2   0010 = 3   0011 = 4
// 0100 = 5   0101 = 6   0110 = 7   0111 = 8
// 1000 = 9   1001 = 10  1010 = 11  1011 = 12
// 1100 = 13  1101 = 14  1110 = 15  1111 = 16
//
// If DIP Switch is NOT installed - change dipSwitchInstalled to "false"
// If dipSwitchInstalled is set to false, the MIDI channel will be set
// to the value of MIDICHANNEL
#define MIDICHANNEL 1 // Can be a value from 1 to 16
// *******************************************************************************

MIDI_CREATE_DEFAULT_INSTANCE();

uint16_t syncPhaseAcc;
uint16_t syncPhaseInc;
uint16_t grainPhaseAcc;
uint16_t grainPhaseInc;
uint16_t grainAmp;
uint8_t grainDecay;
uint16_t grain2PhaseAcc;
uint16_t grain2PhaseInc;
uint16_t grain2Amp;
uint8_t grain2Decay;

// DIP Switch Pins
#define DIP_SW1 9
#define DIP_SW2 10
#define DIP_SW3 11
#define DIP_SW4 12

// Map Analogue channels
#define SYNC_CONTROL         (4)
#define GRAIN_FREQ_CONTROL   (0)
#define GRAIN_DECAY_CONTROL  (2)
#define GRAIN2_FREQ_CONTROL  (3)
#define GRAIN2_DECAY_CONTROL (1)

#define BUFFER 8 //Size of keyboard buffer

#if defined(__AVR_ATmega8__)
//
// On old ATmega8 boards.
//    Output is on pin 11
//
#define LED_PIN       13
#define LED_PORT      PORTB
#define LED_BIT       5
#define PWM_PIN       11
#define PWM_VALUE     OCR2
#define PWM_INTERRUPT TIMER2_OVF_vect
#elif defined(__AVR_ATmega1280__)
//
// On the Arduino Mega
//    Output is on pin 3
//
#define LED_PIN       13
#define LED_PORT      PORTB
#define LED_BIT       7
#define PWM_PIN       3
#define PWM_VALUE     OCR3C
#define PWM_INTERRUPT TIMER3_OVF_vect
#else
//
// For modern ATmega168 and ATmega328 boards
//    Output is on pin 3
//
#define PWM_PIN       3
#define PWM_VALUE     OCR2B
#define LED_PIN       13
#define LED_PORT      PORTB
#define LED_BIT       5
#define PWM_INTERRUPT TIMER2_OVF_vect
#endif

// Smooth logarithmic mapping
//
uint16_t antilogTable[] = {
  64830, 64132, 63441, 62757, 62081, 61413, 60751, 60097, 59449, 58809, 58176, 57549, 56929, 56316, 55709, 55109,
  54515, 53928, 53347, 52773, 52204, 51642, 51085, 50535, 49991, 49452, 48920, 48393, 47871, 47356, 46846, 46341,
  45842, 45348, 44859, 44376, 43898, 43425, 42958, 42495, 42037, 41584, 41136, 40693, 40255, 39821, 39392, 38968,
  38548, 38133, 37722, 37316, 36914, 36516, 36123, 35734, 35349, 34968, 34591, 34219, 33850, 33486, 33125, 32768
};
uint16_t mapPhaseInc(uint16_t input) {
  return (antilogTable[input & 0x3f]) >> (input >> 6);
}

// Stepped chromatic mapping
//
uint16_t midiTable[] = {
  0, 18, 19, 20, 22, 23, 24, 26, 27, 29, 31, 32, 34, 36, 38, 41, 43, 46, 48, 51, 54, 58, 61, 65, 69, 73,
  77, 82, 86, 92, 97, 103, 109, 115, 122, 129, 137, 145, 154, 163, 173, 183, 194, 206, 218, 231,
  244, 259, 274, 291, 308, 326, 346, 366, 388, 411, 435, 461, 489, 518, 549, 581, 616, 652, 691,
  732, 776, 822, 871, 923, 978, 1036, 1097, 1163, 1232, 1305, 1383, 1465, 1552, 1644, 1742,
  1845, 1955, 2071, 2195, 2325, 2463, 2610, 2765, 2930, 3104, 3288, 3484, 3691, 3910, 4143,
  4389, 4650, 4927, 5220, 5530, 5859, 6207, 6577, 6968, 7382, 7821, 8286, 8779, 9301, 9854,
  10440, 11060, 11718, 12415, 13153, 13935, 14764, 15642, 16572, 17557, 18601, 19708, 20879,
  22121, 23436, 24830, 26306
};
uint16_t mapMidi(uint16_t input) {
  return (midiTable[input]);
}

// Stepped Pentatonic mapping
//
uint16_t pentatonicTable[54] = {
  0, 19, 22, 26, 29, 32, 38, 43, 51, 58, 65, 77, 86, 103, 115, 129, 154, 173, 206, 231, 259, 308, 346,
  411, 461, 518, 616, 691, 822, 923, 1036, 1232, 1383, 1644, 1845, 2071, 2463, 2765, 3288,
  3691, 4143, 4927, 5530, 6577, 7382, 8286, 9854, 11060, 13153, 14764, 16572, 19708, 22121, 26306
};

uint16_t mapPentatonic(uint16_t input) {
  uint8_t value = (1023 - input) / (1024 / 53);
  return (pentatonicTable[value]);
}

//Global Varibles used by MIDI Upgrade
byte note = 0;
byte buff[BUFFER];
byte buffersize = 0;
float bendfactor = ((BENDRANGE * 100.0) / 8190.0);
float cents = 0;
bool pot = false;
bool noteOn = false;
int oldpot = 0;
int transpose = 0;

void audioOn() {
#if defined(__AVR_ATmega8__)
  // ATmega8 has different registers
  TCCR2 = _BV(WGM20) | _BV(COM21) | _BV(CS20);
  TIMSK = _BV(TOIE2);
#elif defined(__AVR_ATmega1280__)
  TCCR3A = _BV(COM3C1) | _BV(WGM30);
  TCCR3B = _BV(CS30);
  TIMSK3 = _BV(TOIE3);
#else
  // Set up PWM to 31.25kHz, phase accurate
  TCCR2A = _BV(COM2B1) | _BV(WGM20);
  TCCR2B = _BV(CS20);
  TIMSK2 = _BV(TOIE2);
#endif
}

void setup() {
  if (dipSwitchInstalled) {
    pinMode(DIP_SW1, INPUT_PULLUP);
    pinMode(DIP_SW2, INPUT_PULLUP);
    pinMode(DIP_SW3, INPUT_PULLUP);
    pinMode(DIP_SW4, INPUT_PULLUP);
  }
  pinMode(PWM_PIN, OUTPUT);
  audioOn();
  pinMode(LED_PIN, OUTPUT);
  oldpot = analogRead(SYNC_CONTROL);
  if (dipSwitchInstalled) {
    MIDI.begin(DipSwitch());
  }
  else {
    MIDI.begin(MIDICHANNEL);
  }
  MIDI.setHandleNoteOn(NoteOnMidi);
  MIDI.setHandleNoteOff(NoteOffMidi);
  MIDI.setHandlePitchBend(Pitchbend);
}

void loop() { // *** MAIN LOOP ***

  MIDI.read();

  if (abs(analogRead(SYNC_CONTROL) - oldpot) > 5) pot = true;// Check if SYNC Pot has been touched

  // If Sync pot has been touched - Play pentatonic major scale with Root Note set by note on keyboard
  if (pot == true && noteOn == true) {
    syncPhaseInc = (mapPentatonic(analogRead(SYNC_CONTROL)) * pow(2, ((cents + transpose) / 1200)) );
    oldpot = analogRead(SYNC_CONTROL);
  }
  // If Sync pot has not been touched - Play the note sent by keyboard
  else {
    syncPhaseInc = mapMidi(note) * pow(2, (cents / 1200));
  }

  grainPhaseInc  = mapPhaseInc(analogRead(GRAIN_FREQ_CONTROL)) / 2;
  grainDecay     = analogRead(GRAIN_DECAY_CONTROL) / 8;
  grain2PhaseInc = mapPhaseInc(analogRead(GRAIN2_FREQ_CONTROL)) / 2;
  grain2Decay    = analogRead(GRAIN2_DECAY_CONTROL) / 4;
}

SIGNAL(PWM_INTERRUPT)
{
  uint8_t value;
  uint16_t output;

  syncPhaseAcc += syncPhaseInc;
  if (syncPhaseAcc < syncPhaseInc) {
    // Time to start the next grain
    grainPhaseAcc = 0;
    grainAmp = 0x7fff;
    grain2PhaseAcc = 0;
    grain2Amp = 0x7fff;
    LED_PORT ^= 1 << LED_BIT; // Faster than using digitalWrite
  }

  // Increment the phase of the grain oscillators
  grainPhaseAcc += grainPhaseInc;
  grain2PhaseAcc += grain2PhaseInc;

  // Convert phase into a triangle wave
  value = (grainPhaseAcc >> 7) & 0xff;
  if (grainPhaseAcc & 0x8000) value = ~value;
  // Multiply by current grain amplitude to get sample
  output = value * (grainAmp >> 8);

  // Repeat for second grain
  value = (grain2PhaseAcc >> 7) & 0xff;
  if (grain2PhaseAcc & 0x8000) value = ~value;
  output += value * (grain2Amp >> 8);

  // Make the grain amplitudes decay by a factor every sample (exponential decay)
  grainAmp -= (grainAmp >> 8) * grainDecay;
  grain2Amp -= (grain2Amp >> 8) * grain2Decay;

  // Scale output to the available range, clipping if necessary
  output >>= 9;
  if (output > 255) output = 255;

  // Output to PWM (this is faster than using analogWrite)
  PWM_VALUE = output;
}

// NoteOnMidi function is called when a Note On event is detected
// Put note in key buffer and set note variable
void NoteOnMidi(byte channel, byte pitch, byte velocity) {
  if (buffersize < BUFFER) {
    note = pitch;
    buff[buffersize] = pitch;
    buffersize++;
  }
  noteOn = true;
  // Set root note of Pentatonic scale
  int offset = pitch % 12;
  if (offset < 7) transpose = (5 + offset) * 100;
  else if (offset >= 7) transpose = (offset - 7) * 100;
}

// NoteOffMidi function is called when a Note Off event is detected
// If there are other notes in the key buffer (more than one key held)
// re-trigger old note. If key buffer is empty - set note to zero (off).
void NoteOffMidi(byte channel, byte pitch, byte velocity) {
  if (buffersize > 1) {
    for (int ctr = 0; ctr < buffersize; ctr++) {
      if (buff[ctr] == pitch) {

        ShiftLeft(ctr + 1);
        break;
      }
    }
    note = buff[buffersize - 1];
    int offset = note % 12;
    if (offset < 7) transpose = (5 + offset) * 100;
    else if (offset >= 7) transpose = (offset - 7) * 100;
  }
  else {
    note = 0;
    noteOn = false;
    buff[buffersize - 1] = 0;
    buffersize = 0;
  }
  pot = false;
}

// ShiftLeft closes gap in key buffer when note is removed.
void ShiftLeft(int index) {
  int ctr = (index - 1);
  for (ctr; ctr < buffersize - 1; ctr++) {
    buff[ctr] = buff[ctr + 1];
  }
  buff[ctr + 1] = 0;
  buffersize--;
}

// Pitchbend function is called when Pitchbend data is received.
// This function coverts the Pitchbend number into cents (100 cents = 1 semitone)
// In the main loop, the frequency of the note plus the pitchbend is calculated
// using this formula: Final Frequency = note * 2^(cents/1200)
void Pitchbend (byte channel, int bend) {
  cents = bend * bendfactor;
}

byte DipSwitch() {
  byte value = 0;
  if (digitalRead(DIP_SW4) == LOW)
    value += 1;
  if (digitalRead(DIP_SW3) == LOW)
    value += 2;
  if (digitalRead(DIP_SW2) == LOW)
    value += 4;
  if (digitalRead(DIP_SW1) == LOW)
    value += 8;
  return (value + 1);
}
