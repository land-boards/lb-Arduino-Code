// ER_GATE_SEQ_TEST_V1
//  GATE sequencer test code
//  Test all 6 GATE outputs
//  Use CLK_IN as an OUT for this test only

// Pins
#define GATE_OUT_1 5
#define GATE_OUT_2 6
#define GATE_OUT_3 7
#define GATE_OUT_4 8
#define GATE_OUT_5 9
#define GATE_OUT_6 10
#define ENC_PIN1 3
#define ENC_PIN1 2
#define PUSH_BUTTON 12
#define CLK_IN 13

void setup() {
  //pin mode setting
  pinMode(PUSH_BUTTON, INPUT_PULLUP); //BUTTON
  pinMode(CLK_IN, OUTPUT); //Normally IN, use as OUT for testing
  pinMode(GATE_OUT_1, OUTPUT); //CH1
  pinMode(GATE_OUT_2, OUTPUT); //CH2
  pinMode(GATE_OUT_3, OUTPUT); //CH3
  pinMode(GATE_OUT_4, OUTPUT); //CH4
  pinMode(GATE_OUT_5, OUTPUT); //CH5
  pinMode(GATE_OUT_6, OUTPUT); //CH6
  digitalWrite(CLK_IN, LOW);
  digitalWrite(GATE_OUT_1, LOW);
  digitalWrite(GATE_OUT_2, LOW);
  digitalWrite(GATE_OUT_3, LOW);
  digitalWrite(GATE_OUT_4, LOW);
  digitalWrite(GATE_OUT_5, LOW);
  digitalWrite(GATE_OUT_6, LOW);
}

void loop()
{
  digitalWrite(GATE_OUT_1, HIGH);
  delay(10);
  digitalWrite(GATE_OUT_1, LOW);
  digitalWrite(GATE_OUT_2, HIGH);
  delay(10);
  digitalWrite(GATE_OUT_2, LOW);
  digitalWrite(GATE_OUT_3, HIGH);
  delay(10);
  digitalWrite(GATE_OUT_3, LOW);
  digitalWrite(GATE_OUT_4, HIGH);
  delay(10);
  digitalWrite(GATE_OUT_4, LOW);
  digitalWrite(GATE_OUT_5, HIGH);
  delay(10);
  digitalWrite(GATE_OUT_5, LOW);
  digitalWrite(GATE_OUT_6, HIGH);
  delay(10);
  digitalWrite(GATE_OUT_6, LOW);
  digitalWrite(CLK_IN, HIGH);
  delay(10);
  digitalWrite(CLK_IN, LOW);
}
