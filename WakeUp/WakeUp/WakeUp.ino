// WakeUp

// Hardware
const int BUZZER = 0;
const int BUTTON = 3;

void setup() 
{
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop() 
{
  int sensorValue;
  int loopCount;
  
  sensorValue = analogRead(2);
  if (sensorValue < 512)    // 2.5V
  {
    digitalWrite(BUZZER, HIGH);
    for (loopCount = 0; loopCount < 100; loopCount++)
    {
      delay(100);
      if (digitalRead(BUTTON) == 0)
        loopCount = 100;
    }
  }
  else
    digitalWrite(BUZZER, LOW);
}

