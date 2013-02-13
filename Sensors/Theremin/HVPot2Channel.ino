////////////////////////////////////////////////////////////////////////////////
// setHVPots() - Set the high voltage pots to the desired frequency and volume
// Uses globals: 
//  vol128 - 7-bit volume control
//  freq128
////////////////////////////////////////////////////////////////////////////////

void setHVPots(void)
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
    if ((vol128 & bit) == 0)
      digitalWrite(VOLDAT, LOW);
    else 
      digitalWrite(VOLDAT, HIGH);
    if ((freq128 & bit) == 0)
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


