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
void loop() {
  // read the input on analog pin 0:
  int RV1 = analogRead(A7);
  int RV2 = analogRead(A4);
  int RV3 = analogRead(A6);
  int RV4 = analogRead(A3);
  int RV5 = analogRead(A5);
  int RV6 = analogRead(A2);
  int J1 = analogRead(A0);
  int J2 = analogRead(A1);
  // print out the value you read:
  Serial.print(RV1);
  Serial.print(", ");
  Serial.print(RV2);
  Serial.print(", ");
  Serial.print(RV3);
  Serial.print(", ");
  Serial.print(RV4);
  Serial.print(", ");
  Serial.print(RV5);
  Serial.print(", ");
  Serial.print(RV6);
  Serial.print(", ");
  Serial.print(J1);
  Serial.print(", ");
  Serial.println(J2);
  delay(1);        // delay in between reads for stability
}
