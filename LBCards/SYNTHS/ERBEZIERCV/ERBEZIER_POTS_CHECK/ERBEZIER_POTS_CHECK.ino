/*
  HAGIWO_PROTO02_POTS_CHECK
  Read the Pots and CV.
  Prints the values that were read to the monitor.
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int RV1 = analogRead(A0);
  int RV2 = analogRead(A1);
  int RV3 = analogRead(A2);
  int RV4 = analogRead(A3);
  int J4 = analogRead(A6);
  int J5 = analogRead(A7);
  // print out the value you read:
  Serial.print(RV1);
  Serial.print(", ");
  Serial.print(RV2);
  Serial.print(", ");
  Serial.print(RV3);
  Serial.print(", ");
  Serial.print(RV4);
  Serial.print(", ");
  Serial.print(J4);
  Serial.print(", ");
  Serial.println(J5);
  delay(1);        // delay in between reads for stability
}
