/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and sends to led as pwm level.
 
 This example code is in the public domain.
 */

#define SW5WAY A0
#define SSR 4
#define DS2 5  // pwmable
#define DS1 6  // pwmable
#define BUZZ 10  // pwmable

// the setup routine runs once when you press reset:
void setup() {
  pinMode(SSR, OUTPUT);
  pinMode(DS1, OUTPUT);
  pinMode(DS2, OUTPUT);
  pinMode(BUZZ, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  analogWrite(DS2,255-(sensorValue>>2));
}
