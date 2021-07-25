// Petit FS test.   
// For minimum flash use edit pffconfig.h and only enable
// _USE_READ and either _FS_FAT16 or _FS_FAT32

#include "PF.h"
#include "PetitSerial.h"

PetitSerial PS;
// Use PetitSerial instead of Serial.
#define Serial PS

// The SD chip select pin is currently defined as 10
// in pffArduino.h.  Edit pffArduino.h to change the CS pin.

FATFS fs;     /* File system object */
//------------------------------------------------------------------------------
void errorHalt(char* msg) {
  Serial.print("Error: ");
  Serial.println(msg);
  while(1);
}
//------------------------------------------------------------------------------
void test() {
  uint8_t buf[32];
  
  // Initialize SD and file system.
  if (PF.begin(&fs)) errorHalt("pf_mount");
  
  // Open test file.
  if (PF.open("TEST.TXT")) errorHalt("pf_open");
  
  // Dump test file to Serial.
  while (1) {
    UINT nr;
    if (PF.readFile(buf, sizeof(buf), &nr)) errorHalt("pf_read");
    if (nr == 0) break;
    Serial.write(buf, nr);
  }
}
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  test();
  Serial.println("\nDone!");
}
void loop() {}