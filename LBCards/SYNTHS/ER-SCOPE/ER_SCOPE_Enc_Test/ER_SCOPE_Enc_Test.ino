// ER_SCOPE_Enc_Test
// Tests the Rotary encoder, pushbutton, Trigger input
// Watch output on Serial Monitor
// Knob CW should increase number
// Rotary Switch Low = pressed
// Example output
//  Rotary SW LOW
//  Rotary SW HIGH
//  Trig HIGH
//  Trig LOW
//  Rotary = 13
//  Rotary = 14

/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(4, 2);
//   avoid using pins with LEDs attached

#define INPUT_SW 5
#define EXT_TRIG 7


void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
  pinMode(INPUT_SW, INPUT_PULLUP);
  pinMode(EXT_TRIG, INPUT_PULLUP);        // External triger detect
}

uint16_t oldPosition  = -999;
uint8_t oldTrig = 0;
uint8_t oldPB = 1;

void loop() {
  uint16_t newPosition = myEnc.read()/4;
  if (newPosition != oldPosition)
  {
    oldPosition = newPosition;
    Serial.print("Rotary = ");
    Serial.println(newPosition);
  }
  uint8_t newTrig = digitalRead(EXT_TRIG);
  if (newTrig != oldTrig)
  {
    if (newTrig == 1)
      Serial.println("Trig HIGH");
    else
      Serial.println("Trig LOW");     
    oldTrig = newTrig;
  }
  uint8_t newPB = digitalRead(INPUT_SW);
  if (newPB != oldPB)
  {
    if (newPB == 1)
      Serial.println("Rotary SW HIGH");
    else
      Serial.println("Rotary SW LOW");     
    oldPB = newPB;
  }
}
