/*
  SDFileOps - SD Card File Operations

  fileDump(char * filePathName) - SD card file dump
*/

// Select the Serial port to send output to
// #define Serial Serial1  // UART pins
// #define Serial Serial      // USB Serial

// ///////////////////////////////////////////////////////////////////////////////////////////////
// SDInit()- Initialize the SD interface
// SD.begin(chipSelectPin)
//  https://www.arduino.cc/reference/en/libraries/sd/begin/
// Returns
//    0 = init was OK
//    1 = init failed
// ///////////////////////////////////////////////////////////////////////////////////////////////

uint8_t SDInit()
{
  if (!USBSerInit)
    initUSBSerial();
  // Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect))    // Returns 1 on success, 0 on failure.
    return (1);
  SDInitialized = true;
  return (0);
}

// ///////////////////////////////////////////////////////////////////////////////////////////////
// SDInfo() - Read SD Card info
// ///////////////////////////////////////////////////////////////////////////////////////////////

void SDInfo()
{
  char numStr[17];    // Used for number to string
  if (!USBSerInit)
    initUSBSerial();
  if (!SDInitialized)
  {
    if (SDInit() == 1)
    {
      u8x8.clear();
      u8x8.draw2x2String(0, 2, "SD Card");
      u8x8.draw2x2String(0, 4, "Init Fail");
      u8x8.draw2x2String(0, 6, "Key/cont");
      pressButtonToContinue();
      return;
    }
  }

  if (!card.init(SPI_HALF_SPEED, chipSelect))
  {
    u8x8.clear();
    u8x8.draw2x2String(0, 2, "SD Card");
    u8x8.draw2x2String(0, 4, "Init Fail");
    u8x8.draw2x2String(0, 6, "Key/cont");
    pressButtonToContinue();
    return;
  }

  u8x8.clear();
  u8x8.drawString(0, 0, "SD Init=OK");

  // print the type of card
  u8x8.drawString(0, 1, "Type=");
  switch (card.type())
  {
    case SD_CARD_TYPE_SD1:
      u8x8.drawString(6, 1, "SD1");
//      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      u8x8.drawString(6, 1, "SD2");
//      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      u8x8.drawString(6, 1, "SDHC");
//      Serial.println("SDHC");
      break;
    default:
      u8x8.drawString(6, 1, "Unknown");
//      Serial.println("Unknown");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card))
  {
    u8x8.drawString(0, 2, "No FAT16/FAT32");
    pressButtonToContinue();
    return;
  }
  if (volume.fatType() == 32)
    u8x8.drawString(0, 2, "FAT32 File Sys");
  else if (volume.fatType() == 16)
    u8x8.drawString(0, 2, "FAT16 File Sys");
  else
    u8x8.drawString(0, 2, "Unknown F/S");
  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
  //
  u8x8.drawString(0, 3, "Clus=");
  itoa(volume.clusterCount(), numStr, 10);
  u8x8.drawString(5, 3, numStr);
  //
  u8x8.drawString(0, 4, "Clus/Blk=");
  itoa(volume.blocksPerCluster(), numStr, 10);
  u8x8.drawString(9, 4, numStr);
  //  Serial.print("Volume size (Mb):  ");
  //
  u8x8.drawString(0, 5, "MB=");
  itoa(volumesize / 1024, numStr, 10);
  u8x8.drawString(3, 5, numStr);
  volumesize /= 1024;
//  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
//  root.openRoot(volume);
  // list all files in the card with date and size
//  root.ls(LS_R | LS_DATE | LS_SIZE);
  root.close();
  pressButtonToContinue();
}

// ///////////////////////////////////////////////////////////////////////////////////////////////
// SDDir()
// ///////////////////////////////////////////////////////////////////////////////////////////////

void SDDir()
{
  File SDroot;
  dirLevel = 0;
  strcpy(&SavePath[0],"");
  if (!USBSerInit)
    initUSBSerial();
  if (!card.init(SPI_HALF_SPEED, chipSelect))
  {
    u8x8.clear();
    u8x8.draw2x2String(0, 2, "SD Card");
    u8x8.draw2x2String(0, 4, "Init Fail");
    u8x8.draw2x2String(0, 6, "Key/cont");
    pressButtonToContinue();
    return;
  }
  if (!volume.init(card))
  {
    u8x8.drawString(0, 2, "No FAT16/FAT32");
    pressButtonToContinue();
    return;
  }
  root.openRoot(volume);
  SDroot = SD.open("/");
  //root.close();
  printDirectory(SDroot, 0);
}

// ///////////////////////////////////////////////////////////////////////////////////////////////
// printDirectory(File dir, int numTabs)
// This function uses recursion to dexcend into folders
// ///////////////////////////////////////////////////////////////////////////////////////////////

void printDirectory(File dir, int numTabs)
{
  uint8_t lineOnOLED = 0;
//  Serial.println("Reached printDirectory()");
//  Serial.print(" dirLevel = ");
//  Serial.println(dirLevel);
  u8x8.clear();
  u8x8.drawString(0, 0, "/               ");
  if (numTabs > 0)
    u8x8.drawString(1, 0, SavePath);
  lineOnOLED++;
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry)     // no more files
      break;
//    for (uint8_t i = 0; i < numTabs; i++)
//      Serial.print('\t');
    if (entry.isDirectory())
    {
      strcpy(&SavePath[0],entry.name());
//      Serial.println("/");
//      Serial.print("Folder = ");
//      Serial.println(SavePath);
      dirLevel++;
      printDirectory(entry, numTabs + 1);   // print subdirectories
//      Serial.print(" dirLevel = ");
//      Serial.println(dirLevel);
    }
    else 
    {
//      Serial.print(entry.name());    
      // files have sizes, directories do not
//      Serial.print("\t");
//      Serial.println(entry.size(), DEC);
      u8x8.drawString(0, lineOnOLED, entry.name());
      lineOnOLED++;
//      delay(250);
    }
    entry.close();
//    delay(250);
  }
  pressButtonToContinue();
  dirLevel--;
  if (dirLevel == 0)
    {
    strcpy(&SavePath[0],"/               ");
    u8x8.drawString(0, 0, SavePath);
    }

//  Serial.print(" dirLevel = ");
//  Serial.println(dirLevel);
}

// ///////////////////////////////////////////////////////////////////////////////////////////////
// fileDump(filePathName)
// ///////////////////////////////////////////////////////////////////////////////////////////////

void fileDump(char * filePathName)
{
  if (!USBSerInit)
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
