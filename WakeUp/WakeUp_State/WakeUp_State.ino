///////////////////////////////////////////////////////////////////
// WakeUp_State - State machine implementation of power monitor/alarm

// Hardware device to pin mapping
const int BUZZER = 0;
const int BUTTON = 3;
const int LED = 1;

// State machine related objects and definitions
const int ELAPSED_TIME_LIMIT = 3000;	// Buzzer time in 10 mSec increments

enum
{
  POWER_ON,
  WAIT_FOR_AC_POWER,
  ALARM_ON,
  AC_POWER_ON_NORMAL_OPS,
  BUZZER_TEST,
};

unsigned char state;   // state machine is above
long elapsedTime;      // elapsed time counter - in 10 mSec increments

///////////////////////////////////////////////////////////////////
// setup() - Set the state, enable the outputs and make sure the 
//   buzzer is off

void setup() 
{
  buzzerOff();
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT);
  state = POWER_ON;
}

///////////////////////////////////////////////////////////////////
// loop - implements the state machine
// No delays longer than 1/2 second.
// Retains the state since loop runs repeatedly start to finish.

void loop() 
{
  int sensorValue;
  int loopCount;
  switch (state)
  {
  case POWER_ON:               // power is turned on
    buzzerOn();
    delay(500);
    buzzerOff();
    state = WAIT_FOR_AC_POWER;
    break;
  case WAIT_FOR_AC_POWER:        // wait for the AC Power to come on
    if (isACPowerOn() == true)
    {
      state = AC_POWER_ON_NORMAL_OPS;
      break;
    }
    break;
  case AC_POWER_ON_NORMAL_OPS:   // "normal" state with AC Power OK
    if (isACPowerOn() == false)
    {
      buzzerOn();
      elapsedTime = 0;
      state = ALARM_ON;
      break;
    }
    if (isButtonPressed() == true)
    {
      state = BUZZER_TEST;
      break;
    }
    break;
  case ALARM_ON:
    if (isButtonPressed() == true)
    {
      buzzerOff();
      state = WAIT_FOR_AC_POWER;
      break;
    }
    if (elapsedTime < ELAPSED_TIME_LIMIT)
    {
      delay(10);      // 10 mSec increments allow switch polling to be quicker
      elapsedTime++;
      break;
    }
    else
    {
      buzzerOff();
      state = WAIT_FOR_AC_POWER;
      break;
    }
    break;
  case BUZZER_TEST:
    buzzerOn();
    while (isButtonPressed() == true);
    buzzerOff();
    state = AC_POWER_ON_NORMAL_OPS;
    break;
  }
}

///////////////////////////////////////////////////////////////////
//

int isButtonPressed(void)
{
  if (digitalRead(BUTTON) == 0)
    return true;
  else
    return false;
}

///////////////////////////////////////////////////////////////////
//

int isACPowerOn(void)
{
  if (analogRead(2) < 512)
    return false;
  else
    return true;
}

///////////////////////////////////////////////////////////////////
//

void buzzerOn(void)
{
  digitalWrite(BUZZER, HIGH);
  digitalWrite(LED, HIGH);
}

///////////////////////////////////////////////////////////////////
//

void buzzerOff(void)
{
  digitalWrite(BUZZER, LOW);
  digitalWrite(LED, LOW);
}


