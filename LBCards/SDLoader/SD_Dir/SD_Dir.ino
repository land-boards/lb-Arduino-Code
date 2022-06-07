/*
  SD_Dir
  This example shows how print out the files in a
  directory on a SD card.Pin numbers reflect the default
  SPI pins for Uno and Nano models
  
  The circuit:
   SD card attached to SPI bus as follows:
 ** SCLK - CLK - pin 13
 ** MISO - SDI - pin 12
 ** MOSI - SDO - pin 11
 ** SS - CS - depends on your SD card shield or module.
        Pin 10 used here for consistency with other Arduino examples
    (for MKRZero SD: SDCARD_SS_PIN)
 
 created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe
  modified 2 Feb 2014
  by Scott Fitzgerald
  modified 24 July 2020
  by Tom Igoe
  This example code is in the public domain.
*/

#include <SD.h>

// Select the Serial port to send output to
// #define THESERIAL Serial1  // UART pins
#define THESERIAL Serial      // USB Serial

const int chipSelect = 3;

File root;

void setup() {
 // Open serial communications and wait for port to open:
  THESERIAL.begin(9600);
  // wait for Serial Monitor to connect. Needed for native USB port boards only:
  while (!THESERIAL);
  THESERIAL.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    THESERIAL.println("initialization failed. Things to check:");
    THESERIAL.println("1. is a card inserted?");
    THESERIAL.println("2. is your wiring correct?");
    THESERIAL.println("3. did you change the chipSelect pin to match your shield or module?");
    THESERIAL.println("Note: press reset or reopen this serial monitor after fixing your issue!");
    while (true);
  }
  THESERIAL.println("initialization done.");
  root = SD.open("/");
  printDirectory(root, 0);
  THESERIAL.println("done!");
}
void loop() {
  // nothing happens after setup finishes.
}
void printDirectory(File dir, int numTabs) {
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      THESERIAL.print('\t');
    }
    THESERIAL.print(entry.name());
    if (entry.isDirectory()) {
      THESERIAL.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      THESERIAL.print("\t\t");
      THESERIAL.println(entry.size(), DEC);
    }
    entry.close();
  }
}
