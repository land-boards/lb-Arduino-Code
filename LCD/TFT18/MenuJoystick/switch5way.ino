///////////////////////////////////////////////////////////////////////
// checkIfKeyIsPressed()
///////////////////////////////////////////////////////////////////////
//enum IR_VALUES
//{
//  NOKEY = 0,
//  CHMINUS,
//  CH,
//  CHPLUS,
//  LEFT,
//  RIGHT,
//  PAUSE,
//  MINUS,
//  PLUS,
//  EQ,
//  ZEROKEY,
//  V100PLUS,
//  V200PLUS,
//  ONEKEY,
//  TWOKEY,
//  THREEKEY,
//  FOURKEY,
//  FIVEKEY,
//  SIXKEY,
//  SEVENKEY,
//  EIGHTKEY,
//  NINEKEY,
//};

signed char checkKeypad(void)
{
  int sensorValue = analogRead(A0);
  if (sensorValue >= 893)      // NONE
    return(NOKEY);
  else if (sensorValue < 79)   //RIGHT
    return(RIGHT);
  else if (sensorValue < 251)  // UP
    return(UP);
  else if (sensorValue < 435)  // DOWN
    return(DOWN);
  else if (sensorValue < 643)  // LEFT
    return(LEFT);
  else if (sensorValue < 893)  // SELECT
    return(SELECT);
}

