/*
 * Based on original by:
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 * This version adds debug output messages
 */

#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) 
  {
    if (results.value != 0xffffffff)
    {
//      Serial.print(results.value, HEX);
//      Serial.print("=");
      if (results.value == 0xFFA25D)
        Serial.print("CH-");
      else if (results.value == 0xFF629D)
        Serial.print("CH");
      else if (results.value == 0xFFE21D)
        Serial.print("CH+");
      else if (results.value == 0xFF22DD)
        Serial.print("LEFT");
      else if (results.value == 0xFF02FD)
        Serial.print("RIGHT");
      else if (results.value == 0xFFC23D)
        Serial.print("PAUSE");
      else if (results.value == 0xFFE01F)
        Serial.print("MINUS");
      else if (results.value == 0xFFA857)
        Serial.print("PLUS");
      else if (results.value == 0xFF906F)
        Serial.print("EQ");
      else if (results.value == 0xFF6897)
        Serial.print("0");
      else if (results.value == 0xFF9867)
        Serial.print("100+");
      else if (results.value == 0xFFB04F)
        Serial.print("200+");
      else if (results.value == 0xFF30CF)
        Serial.print("1");
      else if (results.value == 0xFF18E7)
        Serial.print("2");
      else if (results.value == 0xFF7A85)
        Serial.print("3");
      else if (results.value == 0xFF10EF)
        Serial.print("4");
      else if (results.value == 0xFF38C7)
        Serial.print("5");
      else if (results.value == 0xFF5AA5)
        Serial.print("6");
      else if (results.value == 0xFF42BD)
        Serial.print("7");
      else if (results.value == 0xFF4AB5)
        Serial.print("8");
      else if (results.value == 0xFF52AD)
        Serial.print("9");
      Serial.println("");
    }
    irrecv.resume(); // Receive the next value
  }
}
