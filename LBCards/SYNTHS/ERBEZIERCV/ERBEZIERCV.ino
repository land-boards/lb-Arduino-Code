// Bezier curve random CV generator
// https://note.com/solder_state/n/n39aacefd73a3
//
// Card Build
// http://land-boards.com/blwiki/index.php?title=HAGIWO_Bezier_Random_CV_Generator
//

#include  <avr/io.h>//for fast PWM

// Pots and jacks analog pins
// Freq pot and Freq CV get added together
//    If using CV to control freq set pot to fully CCW
// Curve pot and Curve CV get added together
//    If using CV to control curve set pot to fully CCW
#define RV1 0   // Freq Pot
#define RV2 1   // Curve Pot
#define RV3 2   // Deviation Pot
#define RV4 3   // Level Pot
#define J4 6    // Freq CV
#define J5 7    // Curve CV
#define J6 10   // Output

// Global variables
uint16_t  i = 0;
uint16_t  start_val = 0;            // Bezier Curve Starting Point
uint16_t  end_val = 255;            // Bezier Curve end Point
uint16_t  dev, level, curve, freq;
uint16_t  freq_rnd = 501;
uint16_t  freq_dev = 40;
uint32_t  timer = 0;                //
uint32_t  timer1 = 0;               // Analog read interval
float     x[256];                   // Bezier Curve Calculation Tables
float     old_wait = 0;
float     wait = 0;                 // Bezier curve x-axis (time)
float     bz_val = 0;               // Bezier curve y-axis (voltage)

// Tables
uint16_t   chance[32] = {5, 12, 21, 33, 48, 67, 90, 118, 151, 189, 232, 279, 331, 386, 443, 501, 559, 616, 671, 723, 770, 813, 851, 884, 912, 935, 954, 969, 981, 990, 997, 1000};//normal distribution table
uint16_t   freq_err[32] = {8, 9, 10, 11, 12, 13, 14, 15, 16, 18, 20, 22, 24, 26, 28, 30, 33, 36, 40, 46, 52, 58, 64, 70, 76, 82, 90, 98, 110, 122, 136, 148};//Frequency Variation

void setup()
{
  // Preparation of Bezier Curve Calculation Tables
  for (uint16_t j = 0; j < 256; j++)
  {
    x[j] = j * 0.003921; // j/255
  }
  pinMode(J6, OUTPUT) ;//CV output
  timer = micros();
  timer1 = millis();
  // Pin 10 pwm setting
  // Timer 1
  // https://circuitdigest.com/microcontroller-projects/arduino-timer-tutorial
  TCCR1B &= B11111000;
  TCCR1B |= B00000001;    // No pre-scaler
  delay(50);
}

// Loop forever
void loop()
{
  // Poll the controls @ 200 Hz sample rate
  if (timer1 + 50 < millis())
  {
    freq = min(511, (analogRead(RV1) / 2 + analogRead(J4) / 2)) * freq_dev;
    curve = min(255, (analogRead(RV2) / 4 + analogRead(J5) / 4));
    level = analogRead(RV4) / 4;
    timer1 = millis();
  }

  if (timer + (wait - old_wait)  <= micros())
  {
    old_wait = wait;
    i++;

    //Recalculation of target voltage values
    if (i >= 255)
    {
      i = 0;
      start_val = end_val;
      end_val = random(0, 255);
      change_freq_error();
    }

    //Bezier Curve Calculations
    wait = 3 * pow((1 - x[i]), 2) * x[i] * curve + 3 * (1 - x[i]) * pow(x[i], 2) * (255 - curve) + pow(x[i], 3) * 255;
    wait = 1 + wait * freq * 2;
    bz_val = pow((1 - x[i]), 3) * start_val + 3 * pow((1 - x[i]), 2) * x[i] * start_val + 3 * (1 - x[i]) * pow(x[i], 2) * end_val + pow(x[i], 3) * end_val;

    timer = micros();
    PWM_OUT();//PWM output
  }
}

// Frequency variation is obtained from the standard deviation table
void change_freq_error()
{
  dev = map(analogRead(RV3), 0, 1023, 0, 500);
  freq_rnd = random(500 - dev, 500 + dev);
  for (int k = 0; k < 32; k++)
  {
    if (freq_rnd >= chance[k] && freq_rnd < chance[k + 1]) {
      freq_dev = freq_err[k];
    }
  }
}

// PWM output
void PWM_OUT()
{
  analogWrite(J6, bz_val * level / 255);
}
