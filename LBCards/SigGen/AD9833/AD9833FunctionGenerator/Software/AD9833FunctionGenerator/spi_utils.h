#ifndef __SPI_UTILS_H__
#define __SPI_UTILS_H__

const byte spi_mosi_pin = 11;  // pin 11 as dds_mosi_pin
const byte spi_sck_pin = 13;   // pin 13 as dds_sck_pin
//// SPI PIN Definitions

int _DIG_SS = 1;
int _DDS_SS = 2;
int _MOSI = 3;
int _SCK = 5;


void setup_spi()
{
  unsigned char sreg;   // save status register and disable interrupts
  sreg = SREG;          //
  cli();                //

    DDRB |= _BV(_DIG_SS);               // set SS pin to output before enabling SPI (req. for master)
    
    //SPCR |=  _BV(SPE) | _BV(MSTR);  // enable spi as master
    
    DDRB |= _BV(_SCK) | _BV(_MOSI); // set pins to output

  sei();                // enable interrupts and restore status register 
  SREG = sreg;          //
}

#endif
