//////////////////////////////////////////////////////////
// loopBackTest()
// http://land-boards.com/blwiki/index.php?title=DIGIO-128
//////////////////////////////////////////////////////////

uint8_t loopBackTest(void)
{
  uint8_t chip;
  uint8_t port;
  uint8_t pass0fail1 = 0;

  // All channels are inputs prior to this point
  // All inputs are pulled High via enabled pullups in the chips
  // Verify that all of the channels are pulled up
  for (chip = 0; chip < 8; chip++)
  {
    for (port = 0; port < 16; port++)
    {
      if (mcpRead(chip, port) != HIGH)  
      {
        Serial.print("Pull-up quiescent value error on chip ");
        Serial.print(chip);
        Serial.print(" and port ");
        Serial.print(port);
        Serial.println(", expected High on pin");
        pass0fail1 = 1;
      }
    }
  }
  for (chip = 0; chip < 8; chip += 2)  // cycle through a channel pair at a time
  {
    for (port = 0; port < 16; port++)
    {
      mcpPinMode(chip, port, OUTPUT);      // Even chips = OUTPUT
      mcpWrite(chip, port, LOW);           // All outs = LOW
      mcpPinMode(chip + 1, port, INPUT);   // Odd chips = INPUTS
    }
    for (port = 0; port < 16; port++)
    {
      mcpWrite(chip, port, HIGH);          // set 1 channel high at a time
      for (uint8_t readPort = 0; readPort < 16; readPort++)
      {
        if (readPort == (15 - port))      // This is the only port that should be high
        {
          if (mcpRead(chip + 1, readPort) != HIGH)
          {
            Serial.print("(1)Error on chip ");
            Serial.print(chip);
            Serial.print(" and port ");
            Serial.print(port);
            Serial.println(" Expected High");
            pass0fail1 = 1;
          }
        }
        else if (mcpRead(chip + 1, readPort) != LOW)  // Rest of the ports should be low
        {
          Serial.print("(2)Error on chip ");
          Serial.print(chip);
          Serial.print(" and port ");
          Serial.print(port);
          Serial.println(" Expected Low");
          pass0fail1 = 1;
        }
      }

      mcpWrite(chip, port, LOW);
      for (uint8_t readPort = 0; readPort < 16; readPort++)
      {
        if (readPort == (15 - port))      // This is the only port that should be LOW
        {
          if (mcpRead(chip + 1, readPort) != LOW)
          {
            Serial.print("(3)Error on chip ");
            Serial.print(chip);
            Serial.print(" and port ");
            Serial.print(port);
            Serial.println(" Expected LOW");
            pass0fail1 = 1;
          }
        }
      }
    }
    for (port = 0; port < 16; port++)    // set all ports back to inputs 
      mcpPinMode(chip, port, INPUT);

  }
  return pass0fail1;
}

