// Basic_MOZZI
// https://sensorium.github.io/Mozzi/learn/a-simple-sketch/
// Make a 440 Hz output

#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/sin2048_int8.h>

#define CONTROL_RATE 128
Oscil <2048, AUDIO_RATE> aSin(SIN2048_DATA);

void setup(){
  aSin.setFreq(440);
  startMozzi(CONTROL_RATE);
}

void updateControl(){
}

int updateAudio(){
  return aSin.next();
}

void loop(){
  audioHook();
}
