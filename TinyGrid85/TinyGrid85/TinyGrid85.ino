// Sample Sketch for TinyGrid85
// Bounces LED from one pin to another

// LED pins on 0-4
int LED0 = 0;
int LED1 = 1;
int LED2 = 2;
int LED3 = 3;
int LED4 = 4;

int ledNum; // the current LED that is lighted

void setup() 
{
  ledNum = 0;  // start with D0 LED
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop() 
{
  // a very simple switch statement
  switch (ledNum)
  {
    case 0x0:
    digitalWrite(LED0, HIGH);
    delay(250);
    digitalWrite(LED0, LOW);
    ledNum = 1;
    case 0x1:
    digitalWrite(LED1, HIGH);
    delay(250);
    digitalWrite(LED1, LOW);
    ledNum = 2;
    case 0x2:
    digitalWrite(LED2, HIGH);
    delay(250);
    digitalWrite(LED2, LOW);
    ledNum = 3;
    case 0x3:
    digitalWrite(LED3, HIGH);
    delay(250);
    digitalWrite(LED3, LOW);
    ledNum = 4;
    case 0x4:
    digitalWrite(LED4, HIGH);
    delay(250);
    digitalWrite(LED4, LOW);
    ledNum = 0;
  }
  delay(250);
}

