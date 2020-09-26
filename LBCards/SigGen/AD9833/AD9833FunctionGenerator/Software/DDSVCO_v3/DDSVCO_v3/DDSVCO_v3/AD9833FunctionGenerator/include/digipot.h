#ifndef __DIGIPOT_H__
#define __DIGIPOT_H__

#include <SPI.h>
//#include "spi_utils.h"
#include "BinaryUtils.h"

//DIG POT
// Define the MCP41100 OP command bits (only one POT)
// Note: command byte format xxCCxxPP, CC command, PP pot number (01 if selected) 
#define MCP_NOP 0b00000000
#define MCP_WRITEPB0 0b00010001
#define MCP_WRITEPB1 0b00010010
#define MCP_WRITEBOTH 0b00010011
#define MCP_SHTDWN 0b00100001

#define SPI_POTWRITE  0x33  // write to both pots
#define SPI_POTSDOWN  0x21

const byte digipot_ss_pin = 9;    // pin 9 as SSPin

void digipot_write_spi(int cmd, int data, uint8_t ssPin)
// SPI write the command and data to the MCP IC connected to the ssPin
{
  SPI.beginTransaction(SPISettings(5000000, MSBFIRST, SPI_MODE2));
  digitalWrite(digipot_ss_pin, LOW); // SS pin low to select chip
  SPI.transfer(cmd);        // Send command code
  SPI.transfer(data);       // Send associated value
  digitalWrite(digipot_ss_pin, HIGH);// SS pin high to de-select chip
  SPI.endTransaction();
}


#endif
