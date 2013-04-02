//////////////////////////////////////////////////////////////////////////////
// mapLimit - "Improves" on the built-in map function by clipping at the ends.
//////////////////////////////////////////////////////////////////////////////

long mapLimit(long value, long fromLow, long fromHigh, long toLow, long toHigh);

int getSetVolFreq(void)
{
  int tempVol;
  int tempFreq;
  tempVol = analogRead(ANALOGIN1);
  tempFreq = analogRead(ANALOGIN2);  
  if ((tempFreq != lastFreq) || (tempVol != lastVol))
  {
    lastFreq = tempFreq;
    lastVol = tempVol;
    vol1024 = mapLimit(tempVol,IRConfigs.volLoEE,IRConfigs.volHiEE,0,1023);
    freq1024 = mapLimit(tempFreq,IRConfigs.freqLoEE,IRConfigs.freqHiEE,1023,0);
    setHVPots();
  }
}

//////////////////////////////////////////////////////////////////////////////
// map() - Does not constrain values to within the range
// mapLimit() - Does constrain values to within the range
//////////////////////////////////////////////////////////////////////////////

long mapLimit(long value, long fromLow, long fromHigh, long toLow, long toHigh)
{
  if (value < fromLow)
    return(toLow);
  if (value > fromHigh)
    return(toHigh);
  else
    return (map(value,fromLow,fromHigh,toLow,toHigh));
}

