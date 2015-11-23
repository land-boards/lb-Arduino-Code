#include <AltSoftSerial.h>

// AltSoftSerial always uses these pins:
//
// Board          Transmit  Receive   PWM Unusable
// -----          --------  -------   ------------
// Arduino Uno        9         8         10

AltSoftSerial altSerial;

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor to open
  Serial.println("Alt-9600");
  altSerial.begin(9600);
}

void loop() {
  char c;

  if (Serial.available()) {
    c = Serial.read();
    altSerial.print(c);
  }
  if (altSerial.available()) {
    c = altSerial.read();
    Serial.print(c);
  }
}

