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
  
  sensorValue = analogRead(2);
  if (sensorValue > 512)
    digitalWrite(BUZZER, LOW);
  else
    digitalWrite(BUZZER, HIGH);
}

