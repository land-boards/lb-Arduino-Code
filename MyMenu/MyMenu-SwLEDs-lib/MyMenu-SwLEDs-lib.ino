#include <Wire.h>
#include "MyMenu.h"

MyMenu myMenuCard;

void setup()
{
  myMenuCard.begin();
}

void loop()
{
  int a;
  a = myMenuCard.pollKeypad();
  if (a == SELECT)
    myMenuCard.setLED(0, HIGH);
  else
    myMenuCard.setLED(0, LOW);
  delay(10);
}

