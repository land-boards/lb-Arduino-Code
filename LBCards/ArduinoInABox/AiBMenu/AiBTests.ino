/*
 * AiBTests
 * 
 * 
 */

// Blink all buts including A0-A3
void blinkAll(void)
{
  uint8_t outPort;
  // Make all other pins HIGH
  for (outPort = 5; outPort <= TOP_PORT;  outPort++)
    pinMode(outPort, OUTPUT);
  for (outPort = 5; outPort <= TOP_PORT;  outPort++)
  {
    digitalWrite(outPort, HIGH);
    delay(DELAY_TIME);
    digitalWrite(outPort, LOW);
  }
  for (outPort = 5; outPort <= TOP_PORT;  outPort++)
    pinMode(outPort, INPUT);
}
