#include <Wire.h>
#include "MyMenu.h"

MyMenu myMenuCard;

void setup()
{
  myMenuCard.setLED(0, HIGH);
  delay(100);
  myMenuCard.setLED(0, LOW);
}

void loop()
{
  int a;
  a = myMenuCard.pollKeypad();
  if (a == SELECT)
    myMenuCard.setLED(0, HIGH);
  delay(100);
  myMenuCard.setLED(0, LOW);
}

