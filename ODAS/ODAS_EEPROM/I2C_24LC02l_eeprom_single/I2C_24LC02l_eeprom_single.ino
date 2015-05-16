//
//    FILE: I2C_small_eeprom_test.ino
//  AUTHOR: 
// VERSION: 0.1.00
// PURPOSE: show/test I2C_EEPROM library with small EEPROMS
//
#include <Wire.h>
#include <I2C_eeprom.h>

// it's only 2Kbit!!!
#define EE24LC024MAXBYTES 2048/8

// the address of your EEPROM
#define DEVICEADDRESS (0x50)

#define TEST_ADDR 16

#define SERIAL_DEBUG Serial

I2C_eeprom eeprom(DEVICEADDRESS, EE24LC024MAXBYTES);

void setup()
{
  SERIAL_DEBUG.begin(57600); 
  while (!SERIAL_DEBUG); // wait for SERIAL_DEBUG port to connect. Needed for Leonardo only

  SERIAL_DEBUG.println("IT IS BEGINNING"); 
  
  eeprom.begin();
  TWBR = 12;    // go to 400 KHz I2C speed mode
  
  
    SERIAL_DEBUG.println("----------------------------------------------");     
    SERIAL_DEBUG.print("SINGLE BYTE: writing and retreiving EEPROM on I2C at address ");
    SERIAL_DEBUG.println(DEVICEADDRESS);
    SERIAL_DEBUG.println("----------------------------------------------");  

    byte curval = eeprom.readByte(TEST_ADDR);

    SERIAL_DEBUG.print("last value: ");
    SERIAL_DEBUG.println(curval);

    curval += 1;
    eeprom.writeByte(TEST_ADDR, curval);

    SERIAL_DEBUG.print("updating to: ");
    SERIAL_DEBUG.println(curval);
    delay(10);

    curval = eeprom.readByte(TEST_ADDR);
    SERIAL_DEBUG.print("new value: ");
    SERIAL_DEBUG.println(curval);    

}

void loop()
{
  // Nothing to do during loop
}
