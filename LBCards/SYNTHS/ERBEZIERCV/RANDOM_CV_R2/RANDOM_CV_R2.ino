// RANDOM_CV_R2 - Random CV generator
//
// Card Build
//    http://land-boards.com/blwiki/index.php?title=HAGIWO_Bezier_Random_CV_Generator
//

#include  <avr/io.h>    // Direct access to registers for clocking fast PWM
#include  <math.h>

// Pots
//  RV1 = Notes rate (50 mS to 4 secs)
//  RV2 = Gate percentage (0-100)
//  RV3 = Minimum output voltage
//  RV4 = Maximum output voltage
//  Freq High/Low pots
// Jacks
//  J3 = Gate digital output
//  J6 = Analog output

#define RV1 0   // Clock Rate
#define RV2 1   // Clock Duty Cycle
#define RV3 2   // Min CV output voltage
#define RV4 3   // Max CV output voltage
#define J3  A5  // GATE Digital output
//#define J4 6    // 
//#define J5 7    // 
#define J6 10   // Output

void setup()
{
  pinMode(J3, OUTPUT);
  digitalWrite(J3, LOW);
  pinMode(J6, OUTPUT);  // CV PWM output
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
//  uint16_t pot;
  uint16_t gateFreq;
  uint16_t gateFreq1;
  uint16_t gateOnTime;
  uint16_t gateOffTime;
  uint32_t outVal;
  uint16_t bottomVal;
  uint16_t topVal;
  double   logPot;

  // Output voltage range
  bottomVal = analogRead(RV3)>>2;
  topVal = analogRead(RV4)>>2;
  if (bottomVal > topVal)
    topVal = bottomVal;
    
  outVal = map(random(512),0,511,bottomVal,topVal);
  PWM_OUT(outVal);

  // Handle GATE pulse
  delayMicroseconds(10);    // Time for VCO to settle
  digitalWrite(J3, HIGH);   // Drive GATE on
  // Turn the linear pot used for speed into a log pot
  logPot = int(1023.0 * log10(analogRead(RV1)) / log10(1023));
  gateFreq = map(logPot,0,1023,4000,50);  // 20mS to 4 secs
  gateOnTime = map(analogRead(RV2),0,1023,0,gateFreq);
  gateOffTime = gateFreq - gateOnTime;
  delay(gateOnTime);
  digitalWrite(J3, LOW);    // Turn GATE off
  delay(gateOffTime);
}

// PWM output
void PWM_OUT(uint32_t val)
{
  analogWrite(J6,val);
}
