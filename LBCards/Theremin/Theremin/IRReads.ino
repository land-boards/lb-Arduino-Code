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
    vol128 = mapLimit(tempVol,IRConfigs.volLoEE,IRConfigs.volHiEE,0,127);
    freq128 = mapLimit(tempFreq,IRConfigs.freqLoEE,IRConfigs.freqHiEE,0,127);
    setHVPots();
  }
}

// map() - Does not constrain values to within the range
// mapLimit() - Does constrain values to within the range

long mapLimit(long value, long fromLow, long fromHigh, long toLow, long toHigh)
{
  if (value < fromLow)
    return(toLow);
  if (value > fromHigh)
    return(toHigh);
  else
    return (map(value,fromLow,fromHigh,toLow,toHigh));
}

