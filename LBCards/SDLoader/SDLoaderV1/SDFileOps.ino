/*
  SDFileOps - SD Card File Operations

  fileDump(char * filePathName) - SD card file dump
*/

// Select the Serial port to send output to
// #define THESERIAL Serial1  // UART pins
// #define THESERIAL Serial      // USB Serial

// ///////////////////////////////////////////////////////////////////////////////////////////////
// SDInit()- Initialize the SD interface
// Returns
//    0 = init was OK
//    1 = init failed
// ///////////////////////////////////////////////////////////////////////////////////////////////

uint8_t SDInit()
{
  if (USBSerInit == 0)
    initUSBSerial();
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect))
    return (1);
  SDInitialized = 1;
  return (0);
}

// ///////////////////////////////////////////////////////////////////////////////////////////////
// SDInfo() - Read SD Card info
// ///////////////////////////////////////////////////////////////////////////////////////////////

void SDInfo()
{
  char numStr[17];    // Used for number to strinng
  if (USBSerInit == 0)
    initUSBSerial();
  if (SDInitialized == 0)
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
  u8x8.drawString(0, 0, "SD Init = OK");
  
  // print the type of card
  u8x8.drawString(0, 1, "Type:");
  switch (card.type()) 
  {
    case SD_CARD_TYPE_SD1:
      u8x8.drawString(6, 1, "SD1");
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      u8x8.drawString(6, 1, "SD2");
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      u8x8.drawString(6, 1, "SDHC");
      Serial.println("SDHC");
      break;
    default:
      u8x8.drawString(6, 1, "Unknown");
      Serial.println("Unknown");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card))
  {
    u8x8.drawString(0, 2, "No FAT16/FAT32");
    pressButtonToContinue();
    return;
  }
  if (volume.fatType() == 32)
    u8x8.drawString(0, 3, "FAT32 File Sys");
  else if (volume.fatType() == 16)
    u8x8.drawString(0, 3, "FAT16 File Sys");
  else
    u8x8.drawString(0, 3, "Unknown F/S");
  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
  // 
  u8x8.drawString(0, 4, "MB:");
  itoa(volumesize / 1024, numStr, 10);
  u8x8.drawString(3, 4, numStr);
  // 
  u8x8.drawString(0, 5, "Clus:");
  itoa(volume.clusterCount(), numStr, 10);
  u8x8.drawString(5, 5, numStr);
  //  Serial.print("Volume size (Mb):  ");
  volumesize /= 1024;
  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);
  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
  root.close();
  pressButtonToContinue();
}

// ///////////////////////////////////////////////////////////////////////////////////////////////
// fileDump(filePathName)
// ///////////////////////////////////////////////////////////////////////////////////////////////

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


// ///////////////////////////////////////////////////////////////////////////////////////////////
// dir()
// ///////////////////////////////////////////////////////////////////////////////////////////////

void dir()
{

}
