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
// getRangeVal() - Returns the digitally filtered range value
// This algorithm could use some improvement
//////////////////////////////////////////////////////////////////////////

short getRangeVal(void)
{
  if (ranges[4] == ranges[3])
    return(ranges[4]);
  else if (ranges[4] == ranges[3] + 1)
    return(ranges[3]);
  else if (ranges[4] == ranges[3] -1 )
    return(ranges[3]);
  else if (ranges[4] == ranges[2])
    return(ranges[4]);
  else if (ranges[3] == ranges[2])
    return(ranges[3]);
  else if (ranges[2] == ranges[1])
    return(ranges[2]);
  return(ranges[4]); 
}

