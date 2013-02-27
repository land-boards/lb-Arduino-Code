////////////////////////////////////////////////////////////////////////////////
// setHVPots() - Set the high voltage pots to the desired frequency and volume
// Uses globals: 
//  vol1024 - 10-bit volume control value
//  freq1024 - 10-bit frequency control value
// SYNC0 and CLK are both high on entering and on leaving this function
////////////////////////////////////////////////////////////////////////////////

void setHVPots(void)
{
  long bit;
  long vol;
  long freq;
  long cmdReg;
  
  cmdReg = 0x1 << 10;    // 0x1 is a write value command
  freq = cmdReg | freq1024;
  vol = cmdReg | vol1024;
  
  digitalWrite(CLK, LOW);
  digitalWrite(SYNC0, LOW);
  digitalWrite(CLK, HIGH);
  // set pot data bits and cycle clock
  for (bit = 0x8000; bit != 0; bit >>= 1)
  {
    if ((vol & bit) == 0)
      digitalWrite(VOLDAT, LOW);
    else 
      digitalWrite(VOLDAT, HIGH);
    if ((freq & bit) == 0)
      digitalWrite(FREQDAT, LOW);
    else 
      digitalWrite(FREQDAT, HIGH);
    digitalWrite(CLK, LOW);
    digitalWrite(CLK, HIGH);
  }
  digitalWrite(SYNC0, HIGH);
  digitalWrite(CLK, LOW);
  digitalWrite(CLK, HIGH);
}
