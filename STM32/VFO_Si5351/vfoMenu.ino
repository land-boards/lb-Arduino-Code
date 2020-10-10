extern

void vfoMenu(void)
{
  if (stepSize == 10000ULL)
  {
    stepSize = 100000ULL;
    Serial.print("Srep by 1 KHz\n");
  }
  else
  {
    stepSize = 10000ULL;
    Serial.print("Srep by 100 Hz\n");
  }
}

// If switch is pressed call menu
void checkSwitch(void)
{
  if (digitalRead(encoderSwitch) == 0)
  {
    while (digitalRead(encoderSwitch) == 0)
      delay(50);    // Debounce
    //Serial.print("Button Pressed\n");
    vfoMenu();
  }
}
