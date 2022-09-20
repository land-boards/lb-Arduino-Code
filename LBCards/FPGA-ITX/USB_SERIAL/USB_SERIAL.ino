/*
  USB_SERIAL

  USES XIAO RP2040 AS USB SERIAL INTERFACE.
  INCLUDES HARDWARE HANDSHAKE.
*/

# define RTS_PIN 6

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(RTS_PIN, INPUT);
}

// the loop routine runs over and over again forever:
void loop() 
{
  uint8_t chIn;
  while (digitalRead(RTS_PIN) == 1);    // WAIT UNTIL HW HANDSHAKE READY
  if (Serial.available() > 0)
  {
    chIn = Serial.read();
    Serial1.write(chIn);
  }
  if (Serial1.available() > 0)
  {
    chIn = Serial1.read();
    Serial.write(chIn);
  }
}
