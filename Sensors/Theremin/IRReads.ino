int getSetVolFreq(void)
{
  int tempVol;
  int tempFreq;
  tempVol = analogRead(ANALOGIN1);
  tempFreq = analogRead(ANALOGIN2);  
  if ((tempFreq != freqValue) || (tempVol != volumeValue))
  {
    freqValue = tempFreq;
    tempVol = volumeValue;
    setHVPots();
  }
}

