////////////////////////////////////////////////////////////////////////////////
// setHVPots() - Set the high voltage pots to the desired frequency and volume
// Uses globals: 
//  vol1024 - 10-bit volume control value
//  freq1024 - 10-bit frequency control value
// SYNC0 and CLK are both high on entering and on leaving this function
////////////////////////////////////////////////////////////////////////////////

void setHVPots(void)
{
  unsigned int vol;
  unsigned int freq;
  unsigned int bit = 0x8000;
  unsigned int cmdReg;
  
  cmdReg = 0x1 << 10;    // 0x1 is a write value command
  freq = cmdReg | freq1024;
  vol = cmdReg | vol1024;
  
  digitalWrite(CLK, LOW);
  digitalWrite(SYNC0, LOW);
  // set pot data bits and cycle clock
  while (bit)
  {
    digitalWrite(CLK, HIGH);
    if (vol & bit)
      digitalWrite(VOLDAT, HIGH);
    else 
      digitalWrite(VOLDAT, LOW);
    if (freq & bit)
      digitalWrite(FREQDAT, HIGH);
    else 
      digitalWrite(FREQDAT, LOW);
    digitalWrite(CLK, LOW);
    bit >>= 1;
  }
//  if (analogRead(ANALOGIN3) > IRConfigs.levelCal)
//    while (analogRead(ANALOGIN3) > IRConfigs.levelCal);
//  else
//    while (analogRead(ANALOGIN3) < IRConfigs.levelCal);
  digitalWrite(SYNC0, HIGH);
  digitalWrite(CLK, HIGH);
  digitalWrite(CLK, LOW);
  digitalWrite(CLK, HIGH);
}

////////////////////////////////////////////////////////////////////////////////
// enableRDAC() - Enable the Resistor D/A Converter
////////////////////////////////////////////////////////////////////////////////

void enableRDAC(void)
{
  unsigned int vol  = 0x1806;
  unsigned int freq = 0x1806;
  unsigned int bit = 0x8000;

  digitalWrite(CLK, LOW);
  digitalWrite(SYNC0, LOW);
  // set pot data bits and cycle clock
  do
  {
    digitalWrite(CLK, HIGH);
    if (vol & bit)
      digitalWrite(VOLDAT, HIGH);
    else 
      digitalWrite(VOLDAT, LOW);
    if (freq & bit)
      digitalWrite(FREQDAT, HIGH);
    else
      digitalWrite(FREQDAT, LOW);
    digitalWrite(CLK, LOW);
    bit >>= 1;
  }
  while (bit);
  digitalWrite(SYNC0, HIGH);
  digitalWrite(CLK, HIGH);
  digitalWrite(CLK, LOW);
  digitalWrite(CLK, HIGH);
//  delay(2);
}

