/*
  Test of audio input and processing with control input,
  using Mozzi sonification library.

  Configuration: requires these lines in the Mozzi/mozzi_config.h file:
  #define USE_AUDIO_INPUT true
  #define AUDIO_INPUT_PIN 0

  Circuit:
    Audio input on pin analog 0
    Output on DAC/A14 on Teensy 3.0, 3.1, or digital pin 9 on a Uno or similar, or
    check the README or http://sensorium.github.io/Mozzi/

     Potentiometer connected to analog pin A1.
     Center pin of the potentiometer goes to the analog pin.
     Side pins of the potentiometer go to +5V and ground

  Mozzi documentation/API
  https://sensorium.github.io/Mozzi/doc/html/index.html

  Mozzi help/discussion/announcements:
  https://groups.google.com/forum/#!forum/mozzi-users

*/

#include <MozziGuts.h>
#include <LowPassFilter.h>

#define KNOB_PIN 1

LowPassFilter lpf;


void setup(){
  lpf.setResonance(220);
  startMozzi();
}


void updateControl(){
  int knob = mozziAnalogRead(KNOB_PIN);
  byte cutoff_freq = knob>>2; // range 0-255
  lpf.setCutoffFreq(cutoff_freq);
}


AudioOutput_t updateAudio(){
  // subtracting 512 moves the unsigned audio data into 0-centred,
  // signed range required by all Mozzi units
  int asig = getAudioInput()-512;
  asig = lpf.next(asig>>1);
  return MonoOutput::fromAlmostNBit(9, asig);
}


void loop(){
  audioHook();
}
