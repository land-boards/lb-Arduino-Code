// MOZZI_Vibrato
// https://sensorium.github.io/Mozzi/learn/a-simple-sketch/

#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/sin2048_int8.h>

#define CONTROL_RATE 128
Oscil <2048, AUDIO_RATE> aSin(SIN2048_DATA);
Oscil <2048, CONTROL_RATE> kVib(SIN2048_DATA);

float centre_freq = 440.0;
float depth = 0.25;

void setup(){
  kVib.setFreq(6.5f);
  startMozzi(CONTROL_RATE);
}

void updateControl(){
  float vibrato = depth * kVib.next();
  aSin.setFreq(centre_freq+vibrato);
}

int updateAudio(){
  return aSin.next();
}

void loop(){
  audioHook();
}
