#include <Ultrasonic.h>   // Library modified to make timing public (not private) function

//#include "HVPot2Channel.h"

#define VOLDAT	2
#define FREQDAT	3
#define CLK	4
#define CS0	5

Ultrasonic ultrasonic1(8,9);
Ultrasonic ultrasonic2(10,11);

// VOLDAT
// FREQDAT
// CLK
// CS0

void setup(void)
{
  Serial.begin(9600);
  pinMode(VOLDAT, OUTPUT);
  pinMode(FREQDAT, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(CS0, OUTPUT);
  digitalWrite(VOLDAT, LOW);
  digitalWrite(FREQDAT, LOW);
  digitalWrite(CLK, LOW);
  digitalWrite(CS0, HIGH);
  setHVPots(0,0);
}

void loop()
{
  int pitch = ultrasonic2.timing();
  int vol = ultrasonic1.timing();
  int pitch2;
  int vol2;
  Serial.println(pitch);
  Serial.println(vol);
  if (pitch < 3000)
  {
    pitch2 = map(pitch,0,3000,0,100);
    vol2 = map(vol,0,3000,0,10);
    setHVPots(vol2,pitch2);
  }
}

void setHVPots(unsigned char volumeValue,unsigned char freqValue)
{
  int bit;
  // set CS0 low
  digitalWrite(CS0, LOW);
  // set CLK high edge
  digitalWrite(CLK, HIGH);
  // set CLK low edge
  digitalWrite(CLK, LOW);
  // set pot data bits and cycle clock
  for (bit = 0x40; bit != 0; bit >>= 1)
  {
    if ((volumeValue & bit) == 0)
      digitalWrite(VOLDAT, LOW);
    else 
      digitalWrite(VOLDAT, HIGH);
    if ((freqValue & bit) == 0)
      digitalWrite(FREQDAT, LOW);
    else 
      digitalWrite(FREQDAT, HIGH);
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
  }
  digitalWrite(CS0, HIGH);
  digitalWrite(CLK, HIGH);
  digitalWrite(CLK, LOW);
}


