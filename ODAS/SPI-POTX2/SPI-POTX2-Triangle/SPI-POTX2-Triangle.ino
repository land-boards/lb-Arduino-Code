/*
Exploring Arduino - Code Listing 9-1: SPI Control of Multiple Digital Potentiometers
http://www.exploringarduino.com/content/ch9

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Include SPI library
#include <SPI.h>

//11 = MOSI, 12 = MISO, 13 = CLK
const int SS1=10; //Slave Select Chip 1

const byte REG0=B00000000; //Register 0 Write command
const byte REG1=B00010000; //Register 1 Write command

void setup()
{
  //Set pin directions for SS
  pinMode(SS1, OUTPUT);
 
  //Initialize SPI
  SPI.begin();
}

void setLed(int SS, int reg, int level)
{
  digitalWrite(SS, LOW); //Set the given SS pin low
  SPI.transfer(reg);   //Choose the register to write to
  SPI.transfer(level);  //Set the LED level (0-128)
  digitalWrite(SS, HIGH); //Set the given SS pin high again
}

void loop()
{
  for (int i=0; i<=128; i++)
  {
    setLed(SS1, REG0, i);
    setLed(SS1, REG1, i);
//    delay(1);
  }
//  delay(300);
  for (int i=128; i>=0; i--)
  {
    setLed(SS1, REG0, i);
    setLed(SS1, REG1, i);
//    delay(1);
  } 
//  delay(300);
}


