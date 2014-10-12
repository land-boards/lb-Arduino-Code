// Sample Sketch for TinyGrid85
// Bounces LED from one pin to another

// LED pins on 0-4
int LED0 = 0;
int LED1 = 1;
int LED2 = 2;
int LED3 = 3;
int LED4 = 4;
const int buttonPin = 3;
int ledNum; // the current LED that is lighted
int sensorValue;

void setup() 
{
  pinMode(LED0, OUTPUT);
  pinMode(buttonPin, INPUT);  
}

void loop() 
{
  // a very simple switch statement

  int switchA = 3;
  sensorValue = analogRead(2);
  if (sensorValue > 512)
    digitalWrite(LED0, LOW);
   else
    digitalWrite(LED0, HIGH);
}

