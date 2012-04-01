/*
 CdSSerial based on AnalogReadSerial example sketch.
 Reads a CdS SENSOR on pin 0, prints the result to the serial monitor.
 Running a python program to read the serial port on the host computer.
*/

int ledNum;

void setup() {
  Serial.begin(9600);
  ledNum = 13;
}

void loop() 
{
  int sensorValue;
  sensorValue = analogRead(A0);
  Serial.print("A0=");
  Serial.print(sensorValue);

  sensorValue = analogRead(A1);
  Serial.print(",A1=");
  Serial.print(sensorValue);

  sensorValue = analogRead(A2);
  Serial.print(",A2=");
  Serial.print(sensorValue);

  sensorValue = analogRead(A3);
  Serial.print(",A3=");
  Serial.print(sensorValue);

  sensorValue = analogRead(A4);
  Serial.print(",A4=");
  Serial.print(sensorValue);

  sensorValue = analogRead(A5);
  Serial.print(",A5=");
  Serial.println(sensorValue);
  pinMode(ledNum,OUTPUT);
  digitalWrite(ledNum,LOW);
  delay(200);
  digitalWrite(ledNum,HIGH);
  ledNum--;
  if (ledNum <= 1)
    ledNum = 13;
}

