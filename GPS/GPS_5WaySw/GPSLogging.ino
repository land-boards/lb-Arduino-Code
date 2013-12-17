/////////////////////////////////////////////////////////////////////////////
// GPS logging functions include
// startLog()
// stopLog()
// clrLog()
// dumpLog()
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// startLog() - Start logging
/////////////////////////////////////////////////////////////////////////////

void startLog(void)
{
  tft.fillRect(0,10,128,70,ST7735_BLACK);
  setCursorTFT(1,0);
  tft.print(F("Starting Logging"));
  setCursorTFT(2,0);
  if (GPS.LOCUS_StartLogger())
    tft.println("Logging STARTED!");
  else
    tft.println("!No response!");
  setCursorTFT(3,0);
  tft.print(F("Any key to continue"));
  while(mySwitch.checkKeypad() == NOKEY);
}

/////////////////////////////////////////////////////////////////////////////
// stopLog() - Stop logging
/////////////////////////////////////////////////////////////////////////////

void stopLog(void)
{
  tft.fillRect(0,10,128,70,ST7735_BLACK);
  setCursorTFT(1,0);
  tft.print(F("Stopping Logging"));
  GPS.sendCommand("$PMTK185,1*23");

  // If using hardware serial (e.g. Arduino Mega), change this to Serial1, etc.
  while (mySerial.available())
    mySerial.read();

  setCursorTFT(2,0);
  tft.print(F("Stopped Logging"));
  setCursorTFT(3,0);
  tft.print(F("Any key to continue"));
  while(mySwitch.checkKeypad() == NOKEY);
}

/////////////////////////////////////////////////////////////////////////////
// clrLog() - Clearing the log
// clear log = $PMKT184,1*22
// returns  $PMKT184,1*22
/////////////////////////////////////////////////////////////////////////////

void clrLog(void)
{
  tft.fillRect(0,10,128,70,ST7735_BLACK);
  setCursorTFT(1,0);
  tft.print(F("Clearing Log"));
  GPS.sendCommand("$PMTK184,1*22");
  // If using hardware serial (e.g. Arduino Mega), change this to Serial1, etc.
  while (mySerial.available())
    mySerial.read();
  setCursorTFT(2,0);
  tft.print(F("Cleared Log"));
  setCursorTFT(3,0);
  tft.print(F("Any key to continue"));
  while(mySwitch.checkKeypad() == NOKEY);
}

/////////////////////////////////////////////////////////////////////////////
// dumpLog() - Dump the log
/////////////////////////////////////////////////////////////////////////////

void dumpLog(void)
{
  tft.fillRect(0,10,128,70,ST7735_BLACK);
  setCursorTFT(1,0);
  tft.print(F("Dump Logging"));
  setCursorTFT(2,0);

  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_OFF);

  // If using hardware serial (e.g. Arduino Mega), change this to Serial1, etc.
  while (mySerial.available())
    mySerial.read();

  Serial.println(F("--- Log Start ---"));
  useInterrupt(false);
  delay(1000);
  GPS.sendCommand("$PMTK622,1*29");
  do
  {
    if (mySerial.available()) 
    {
      char c = mySerial.read();
      if (c) UDR0 = c;  
    }
  }
  while(mySwitch.checkKeypad() == NOKEY);
  Serial.println(F("--- Log End ---"));
  setCursorTFT(3,0);
  tft.print(F("Any key to continue"));
  while(mySwitch.checkKeypad() == NOKEY);
  useInterrupt(true);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
}

