/*
 GenesisJoystick
 Reads Sega Genesis Joystick and return the valies as serial port.
 */

void setup() {
  Serial.begin(9600);
                        // Pwr pin 5 on the joystick connector
                        // Gnd pin 8 on the joystick connector
  pinMode(2, INPUT);    // pin 9 on the joystick connector
  pinMode(4, INPUT);    // pin 6 on the joystick connector
  pinMode(5, INPUT);    // pin 4 on the joystick connector
  pinMode(6, INPUT);    // pin 3 on the joystick connector
  pinMode(7, INPUT);    // pin 2 on the joystick connector
  pinMode(8, INPUT);    // pin 1 on the joystick connector
  pinMode(3, OUTPUT);   // pin 7 on the joystick connector
}

void loop() {
  int sensorValue;
  digitalWrite(3,1);
  sensorValue = digitalRead(2);
  Serial.print("C=");
  Serial.print(!sensorValue);
  sensorValue = digitalRead(4);
  Serial.print(" B=");
  Serial.print(!sensorValue);
  sensorValue = digitalRead(5);
  Serial.print(" Rt=");
  Serial.print(!sensorValue);
  sensorValue = digitalRead(6);
  Serial.print(" Lt=");
  Serial.print(!sensorValue);
  sensorValue = digitalRead(7);
  Serial.print(" Dn=");
  Serial.print(!sensorValue);
  sensorValue = digitalRead(8);
  Serial.print(" Up=");
  Serial.print(!sensorValue);

  digitalWrite(3,0);
  sensorValue = digitalRead(4);
  Serial.print(" A=");
  Serial.print(!sensorValue);
  sensorValue = digitalRead(2);
  Serial.print(" St=");
  Serial.println(!sensorValue);

}



