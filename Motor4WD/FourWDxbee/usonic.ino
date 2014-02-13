//////////////////////////////////////////////////////////////////////////
// checkUsonic(int stopDistance) - Reduces interaction to a single function
// Passed stopDistance - set to the distance for the stop value
// Return values
//  US_STOP - flags the measured distance is less than the threshold
//  US_RUN - flags the measured distance is more than the threshold
//////////////////////////////////////////////////////////////////////////

byte checkUsonic(int stopDistance)
{
  int rangeVal = ultrasonic.Ranging(INC);
#ifdef SERIAL_DEBUG_USONIC
  Serial.print("Distance = ");
  Serial.print(rangeVal);
#endif
  putNewRange(rangeVal);
  if (getRangeVal() < stopDistance)
  {
#ifdef SERIAL_DEBUG_USONIC
  Serial.println(" Ultrasonic Stop");
#endif
    return(US_STOP);
  }  
  else
  {
#ifdef SERIAL_DEBUG_USONIC
  Serial.println(" Ultrasonic Run");
#endif
    return(US_RUN);
  }
}

//////////////////////////////////////////////////////////////////////////
// putNewRange() - Stuff the latest value into the end of the list and
// shuffle all of the items back
//////////////////////////////////////////////////////////////////////////

void putNewRange(short newRangeVal)
{
 ranges[0] = ranges[1];
 ranges[1] = ranges[2];
 ranges[2] = ranges[3];
 ranges[3] = ranges[4];
 ranges[4] = newRangeVal;
 return;
}

//////////////////////////////////////////////////////////////////////////
// // initRanges() - Need to fill up the ranges the first time around
//////////////////////////////////////////////////////////////////////////

void initRanges(void)
{
  putNewRange(ultrasonic.Ranging(INC));
  putNewRange(ultrasonic.Ranging(INC));
  putNewRange(ultrasonic.Ranging(INC));
  putNewRange(ultrasonic.Ranging(INC));
  putNewRange(ultrasonic.Ranging(INC));  
}

//////////////////////////////////////////////////////////////////////////
// getRangeVal() - Returns the median value of the last five samples.
// That way high and low values get discarded.
//////////////////////////////////////////////////////////////////////////

short getRangeVal(void)
{
  short shuffleSpot;
  int loopCt;
  for (loopCt = 0; loopCt < 5; loopCt++)  // copy into the list
    sortedRanges[loopCt] = ranges[loopCt]; 
  for (loopCt = 0; loopCt < 4; loopCt++)
  {
    if (sortedRanges[loopCt] > sortedRanges[loopCt+1])
    {
      shuffleSpot = sortedRanges[loopCt];
      sortedRanges[loopCt] = sortedRanges[loopCt+1];
      sortedRanges[loopCt+1] = shuffleSpot;
    }
  }
  return(sortedRanges[2]);
}

