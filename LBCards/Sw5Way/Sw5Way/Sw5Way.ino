///////////////////////////////////////////////////////////////////////
// Sw5Way 
///////////////////////////////////////////////////////////////////////

enum KEYPAD_VALUES
{
  NOKEY = 0,
  LEFT,
  RIGHT,
  UP,
  DOWN,
  SELECT,
};

///////////////////////////////////////////////////////////////////////
// signed char checkKeypad(void)
///////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////

void setup() 
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

///////////////////////////////////////////////////////////////////////
// the loop routine runs over and over again forever:
///////////////////////////////////////////////////////////////////////

void loop() 
{
  // read the input on analog pin 0:
  int retKeypad = checkKeypad();
  // print out the value you read:
  Serial.println(retKeypad);
  delay(1);        // delay in between reads for stability
}

