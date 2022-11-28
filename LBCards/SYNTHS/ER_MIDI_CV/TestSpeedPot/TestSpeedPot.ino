/*
  TestSpeedPot

  Reads the ER-MIDI-CV4-02 speed pot on Analog 1, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).

  This us based on the AnalogReadSerial example code from the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial

  Card:
  http://land-boards.com/blwiki/index.php?title=ER-MIDI-CV4-02
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int speedPot = analogRead(A1);
  // print out the value you read:
  Serial.print("Speed Pot ");
  Serial.println(speedPot);
  delay(1);        // delay in between reads for stability
}
