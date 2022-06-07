/*
  SDFileOps - SD Card File Operations

  void SDInit() - Initialize the SD interface
  fileDump(char * filePathName) - SD card file dump
*/

#include <SD.h>

// Select the Serial port to send output to
// #define THESERIAL Serial1  // UART pins
// #define THESERIAL Serial      // USB Serial

const int chipSelect = 3;   // SD card Chip Select

// 
void SDFileOps()
{
  if (SDInit() == 1)
  {
    u8x8.clear();
    u8x8.draw2x2String(0, 3, "SD Card");
    u8x8.draw2x2String(0, 6, "Init Fail");
  }
}

// 
uint8_t SDInit()
{
  if (USBSerInit == 0)
    initUSBSerial();
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) 
  {
    Serial.println("initialization failed. Things to check:");
    Serial.println("1. is a card inserted?");
    Serial.println("2. is your wiring correct?");
    Serial.println("3. did you change the chipSelect pin to match your shield or module?");
    Serial.println("Note: press reset or reopen this serial monitor after fixing your issue!");
    return (1);
  }
  Serial.println("initialization done.");
  return (0);
}

void fileDump(char * filePathName)
{
  if (USBSerInit == 0)
    initUSBSerial();
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open(filePathName);

  // if the file is available, write to it:
  if (dataFile)
  {
    while (dataFile.available())
    {
      Serial.write(dataFile.read());
    }
    dataFile.close();
  }

  // if the file isn't open, pop up an error:
  else
  {
    Serial.print("error opening ");
    Serial.println(filePathName);
  }
}
