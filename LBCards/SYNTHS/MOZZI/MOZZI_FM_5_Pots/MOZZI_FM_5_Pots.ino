/* 
  MOZZI_FM_5_Pots.ino
  Example change FM synthesis parameters, and a knob for fundamental frequency,
  using Mozzi sonification library.

  https://www.instructables.com/Using-Mozzi-Library-with-5-potentiometers/

  Demonstrates analog input, audio and control oscillators, phase modulation
  and smoothing a control signal at audio rate to avoid clicks.
  Also demonstrates AutoMap, which maps unpredictable inputs to a set range.
  
  This example goes with a tutorial on the Mozzi site:
  http://sensorium.github.io/Mozzi/learn/Mozzi_Introductory_Tutorial.pdf
  
  The circuit:
     Audio output on digital pin 9 (on a Uno or similar), or 
     check the README or http://sensorium.github.com/Mozzi/

     Potentiometer connected to analog pin 0.
       Center pin of the potentiometer goes to the analog pin.
       Side pins of the potentiometer go to +5V and ground
  
     Light dependent resistor (LDR) and 5.1k resistor on analog pin 1:
       LDR from analog pin to +5V
       5.1k resistor from analog pin to ground
     
     Light dependent resistor (LDR) and 5.1k resistor on analog pin 2:
       LDR from analog pin to +5V
       5.1k resistor from analog pin to ground
  
  Mozzi help/discussion/announcements:
  https://groups.google.com/forum/#!forum/mozzi-users

  Tim Barrass 2013.
  This example code is in the public domain.
*/

#include <MozziGuts.h>
#include <Oscil.h> // oscillator 
#include <tables/cos2048_int8.h> // table for Oscils to play
#include <Smooth.h>
#include <AutoMap.h> // maps unpredictable inputs to a range
 
// int freqVal;
 
// desired carrier frequency max and min, for AutoMap
const int MIN_CARRIER_FREQ = 22;
const int MAX_CARRIER_FREQ = 440;

const int MIN = 1;
const int MAX = 10;

const int MIN_2 = 1;
const int MAX_2 = 15;

// desired intensity max and min, for AutoMap, note they're inverted for reverse dynamics
const int MIN_INTENSITY = 700;
const int MAX_INTENSITY = 10;

// desired mod speed max and min, for AutoMap, note they're inverted for reverse dynamics
const int MIN_MOD_SPEED = 10000;
const int MAX_MOD_SPEED = 1;

AutoMap kMapCarrierFreq(0,1023,MIN_CARRIER_FREQ,MAX_CARRIER_FREQ);
AutoMap kMapIntensity(0,1023,MIN_INTENSITY,MAX_INTENSITY);
AutoMap kMapModSpeed(0,1023,MIN_MOD_SPEED,MAX_MOD_SPEED);
AutoMap mapThis(0,1023,MIN,MAX);
AutoMap mapThisToo(0,1023,MIN_2,MAX_2);

const int KNOB_PIN=7; // Frequency
const int RV2_PIN=4; // fm_intensity
const int RV3_PIN=6; // mod rate
const int LDR3_PIN=3; // 
const int LDR4_PIN=5;

Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aCarrier(COS2048_DATA);
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aModulator(COS2048_DATA);
Oscil<COS2048_NUM_CELLS, CONTROL_RATE> kIntensityMod(COS2048_DATA);

int mod_ratio = 5; // brightness (harmonics)
long fm_intensity; // carries control info from updateControl to updateAudio

// smoothing for intensity to remove clicks on transitions
float smoothness = 0.95f;
Smooth <long> aSmoothIntensity(smoothness);


void setup(){
  Serial.begin(115200); // set up the Serial output so we can look at the light level
  startMozzi(); // :))
}


void updateControl(){
  
//  freqVal = map(LDR3_PIN, 0, 1023, 1, 100);
  
   int freqVal = mozziAnalogRead(LDR3_PIN); // value is 0-1023
   int FRQ = mapThis(freqVal);
   
   int knob2 = mozziAnalogRead(LDR4_PIN); // value is 0-1023
   int knob2Val = mapThis(knob2);
  
  // read the knob
  int knob_value = mozziAnalogRead(KNOB_PIN); // value is 0-1023
  
  // map the knob to carrier frequency
  int carrier_freq = kMapCarrierFreq(knob_value);
  
  //calculate the modulation frequency to stay in ratio
  int mod_freq = carrier_freq * mod_ratio * FRQ;
  
  // set the FM oscillator frequencies
  aCarrier.setFreq(carrier_freq); 
  aModulator.setFreq(mod_freq);
  
  // read the light dependent resistor on the width Analog input pin
  int RV2_value= mozziAnalogRead(RV2_PIN); // value is 0-1023
  // print the value to the Serial monitor for debugging
//  Serial.print("RV2 = "); 
//  Serial.print(RV2_value);
//  Serial.print(", "); // prints a tab

  int RV2_calibrated = kMapIntensity(RV2_value);
//  Serial.print("RV2_calibrated = ");
//  Serial.print(RV2_calibrated);
//  Serial.print(", "); // prints a tab
  
 // calculate the fm_intensity
  fm_intensity = ((long)RV2_calibrated * knob2Val * (kIntensityMod.next()+128))>>8; // shift back to range after 8 bit multiply
//  Serial.print("fm_intensity = ");
//  Serial.print(fm_intensity);
//  Serial.print(", "); // prints a tab
  
  // read the light dependent resistor on the speed Analog input pin
  int RV3_value= mozziAnalogRead(RV3_PIN); // value is 0-1023
//  Serial.print("RV3 = "); 
//  Serial.print(RV3_value);
//  Serial.print(", "); // prints a tab
  
  // use a float here for low frequencies
  float mod_speed = (float)kMapModSpeed(RV3_value)/1000;
//  Serial.print(", mod_speed = ");
//  Serial.print(mod_speed);
  kIntensityMod.setFreq(mod_speed);
  
//  Serial.println(); // finally, print a carraige return for the next line of debugging info
}


int updateAudio(){
  long modulation = aSmoothIntensity.next(fm_intensity) * aModulator.next();
  return aCarrier.phMod(modulation);
}


void loop(){
  audioHook();
}
