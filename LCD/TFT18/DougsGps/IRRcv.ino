int checkIR(void)
{
  int retVal = NOKEY;
  if (irrecv.decode(&results)) 
  {
    if (results.value != 0xffffffff)
    {
      if (results.value == 0xFFA25D)
        retVal = CHMINUS;
      else if (results.value == 0xFF629D)
        retVal = CH;
      else if (results.value == 0xFFE21D)
        retVal = CHPLUS;
      else if (results.value == 0xFF22DD)
        retVal = LEFT;
      else if (results.value == 0xFF02FD)
        retVal = RIGHT;
      else if (results.value == 0xFFC23D)
        retVal = PAUSE;
      else if (results.value == 0xFFE01F)
        retVal = MINUS;
      else if (results.value == 0xFFA857)
        retVal = PLUS;
      else if (results.value == 0xFF906F)
        retVal = EQ;
      else if (results.value == 0xFF6897)
        retVal = ZEROKEY;
      else if (results.value == 0xFF9867)
        retVal = V100PLUS;
      else if (results.value == 0xFFB04F)
        retVal = V200PLUS;
      else if (results.value == 0xFF30CF)
        retVal = ONEKEY;
      else if (results.value == 0xFF18E7)
        retVal = TWOKEY;
      else if (results.value == 0xFF7A85)
        retVal = THREEKEY;
      else if (results.value == 0xFF10EF)
        retVal = FOURKEY;
      else if (results.value == 0xFF38C7)
        retVal = FIVEKEY;
      else if (results.value == 0xFF5AA5)
        retVal = SIXKEY;
      else if (results.value == 0xFF42BD)
        retVal = SEVENKEY;
      else if (results.value == 0xFF4AB5)
        retVal = EIGHTKEY;
      else if (results.value == 0xFF52AD)
        retVal = NINEKEY;
      else
        retVal = NOKEY;
    }
    irrecv.resume(); // Receive the next value
  }
  return(retVal);
}

