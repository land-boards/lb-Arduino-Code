/*
  TestPotDigIOs

  Reads the ER-MIDI-CV4-02 speed pot on Analog 1, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Toggles the Digital Outputs.

  This us based on the AnalogReadSerial example code from the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial

  Card:
  http://land-boards.com/blwiki/index.php?title=ER-MIDI-CV4-02
*/

#define CLK_PIN 4
#define TRIG_PIN 6
#define GATE_PIN 5

#define LDAC2_PIN 8
#define LDAC1_PIN 9
#define SCK_PIN 13
#define MOSI_PIN 11
#define SS_PIN 10

uint8_t loopCount = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(GATE_PIN, OUTPUT);
  digitalWrite(CLK_PIN, LOW);
  digitalWrite(TRIG_PIN, LOW);
  digitalWrite(GATE_PIN, LOW);
  loopCount = 0;
  // SPI
  pinMode(LDAC2_PIN, OUTPUT);
  pinMode(LDAC1_PIN, OUTPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(SS_PIN, OUTPUT);
  digitalWrite(LDAC2_PIN, HIGH);
  digitalWrite(LDAC1_PIN, HIGH);
  digitalWrite(SCK_PIN, HIGH);
  digitalWrite(MOSI_PIN, HIGH);
  digitalWrite(SS_PIN, HIGH);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int speedPot = analogRead(A1);
  // print out the value you read:
  Serial.print("Speed Pot ");
  Serial.println(speedPot);
  delay(1);        // delay in between reads for stability
  loopCount += 1;
  if ((loopCount & 1) == 0)
    digitalWrite(CLK_PIN, LOW);
  else
    digitalWrite(CLK_PIN, HIGH);
  if ((loopCount & 2) == 0)
    digitalWrite(TRIG_PIN, LOW);
  else
    digitalWrite(TRIG_PIN, HIGH);
  if ((loopCount & 4) == 0)
    digitalWrite(GATE_PIN, LOW);
  else
    digitalWrite(GATE_PIN, HIGH);
}
