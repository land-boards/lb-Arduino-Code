/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() 
{
  int sensorValue;
  // read the input on analog pin 26
  sensorValue = analogRead(26); // Freq CV
  Serial.print("pin 26 ");
  Serial.print(sensorValue);
  sensorValue = analogRead(27); // Freq pot
  Serial.print(", pin 27 ");
  Serial.print(sensorValue);
  sensorValue = analogRead(28); // Mod CV
  Serial.print(", pin 28 ");
  Serial.print(sensorValue);
  sensorValue = analogRead(29); // Mod pot
  Serial.print(", pin 29 ");
  Serial.println(sensorValue);
  delay(100);        // delay in between reads for stability
}
