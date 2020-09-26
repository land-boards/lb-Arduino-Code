#ifndef __DDS_H__
#define __DDS_H__

#include "adc.h"
#include <SPI.h>
#include "digipot.h"

//#include "spi_utils.h"

const byte dds_ss_pin = 10;    // pin 10 as dds_ss_pin
const byte spi_mosi_pin = 11;  // pin 11 as dds_mosi_pin
const byte spi_sck_pin = 13;   // pin 13 as dds_sck_pin

volatile unsigned long dds_out_data;  
unsigned long dds_freq = 0x54F8;  // 500 Hz
unsigned long dds_func = 0x2000;

unsigned int FREQZEROREG = 0x4000;

enum WAVE_TYPE {SINE, TRIANGLE, SQUARE};
WAVE_TYPE func = SINE;

enum SWEEP_DIRECTION {UP,DOWN};
SWEEP_DIRECTION sweep_direction = UP;
long sweepcounter;

enum MODE {NORMAL, SWEEP};
MODE mode = NORMAL;

//float sweepspeed = 32;


long maxclkspeed = 100000;
long minclkspeed = 1;

long clkspeed = 10000;
int freqincr = 0;

// phase presets and current setting
int PHASE0 = 0xC000;
int PHASE90 = 0xC400;
int PHASE180 = 0xC800;
int PHASE270 = 0xCC00;
int current_phase = PHASE0;


volatile long maxFreq = 1000;  // the maximum selectable frequency
volatile long selectedUpperFreq = 0; // temp value from ADCInput
volatile long selectedLowerFreq = 0; // temp value from ADCInput
volatile long currentFreq = 0;  // actual value depending on mode

void set_dds_outdata(unsigned long pData) 
{
  dds_out_data = pData;
}

void write_dds_spi()
{
  digitalWrite(spi_sck_pin,HIGH);      // make sure SCK pin is high
  digitalWrite(spi_mosi_pin,LOW);     // and the MOSI pin low
  digitalWrite(dds_ss_pin,HIGH);       // then take the SS pin HIGH as well
  
  // first set the SPI port for 5MHz clock, data sent MSB first,
  // data mode 10 -- with SCK idle high (CPOL = 1) and
  //                MOSI data read on falling edge (CPHA = 0)
  // then begin the SPI transaction
  digitalWrite(dds_ss_pin, LOW); // pull SS(FSYNC) pin low to set for loading
  SPI.beginTransaction(SPISettings(5000000, MSBFIRST, SPI_MODE2));
  
  long recVal16;          // local variable for SPI received data (not used)
  recVal16 = SPI.transfer16(dds_out_data);  // send 16 bits of data out
  SPI.endTransaction();

  
    
  digitalWrite(dds_ss_pin, HIGH);     // then bring SS/FSYNC pin high again
  digitalWrite(spi_mosi_pin,LOW);     // also drop the MOSI pin
  
} 


void setDDSFrequency(long hertz) 
{
  long freqword = (hertz*pow(2,28)) / 25000000;
  
  // Calc Lower Word
  //
  
  // shift left 2bits into a 2-byte integer to retain 14 LSB
  unsigned int loword=freqword<<2;
  // shift it right 2bits and copy command bits into their empty positions
  loword = (loword >>2) | FREQZEROREG;
  
  //printBinaryQWORD(loword);  // Use QWORD to examine full 8-byte memory slo
 

  // Calc Higher Word
  //
  
  // shift right and truncate to 2-byte integer to retain 14 MSB
  unsigned int hiword = freqword>>14;
   
  hiword = hiword | FREQZEROREG;
  //printBinaryQWORD(hiword); // Use QWORD to examine full 8-byte memory slot

  //Serial.println();

  set_dds_outdata(current_phase);
  write_dds_spi();

  // send the control command
  if(func == SINE)
  {
    set_dds_outdata(0x2000);
  }
  else if(func == TRIANGLE)
  {
    set_dds_outdata(0x2002);
  }
  else if(func == SQUARE) 
  {
    set_dds_outdata(0x2068);
  }
  write_dds_spi();

   // send the data command
  set_dds_outdata(loword);
  write_dds_spi();
  
  set_dds_outdata(hiword);
  write_dds_spi();

  
}

void dds_callback_func()
{
  
  //
  // set the freq range
  selectedUpperFreq = map(ADCInput, 1024, 0, 1, maxFreq);
  selectedLowerFreq = map(ADCInput1, 1024, 0, 1, maxFreq);

  if(mode == SWEEP){

     
    Timer1.setPeriod(map(ADCInput6, 0, 1024, 1, maxclkspeed));
    
    // prevent low freq setting from going above upper freq setting
    if (selectedLowerFreq >= selectedUpperFreq)
    {
      // but also prevent upper freq from pushing lower freq down into invalid (zero) value.
      if(selectedLowerFreq > 1)
      {
        selectedLowerFreq = selectedUpperFreq - 1;
      }
      else
      {
        selectedLowerFreq = 1;
      }
      
    }
    
      
    if(sweep_direction == UP)
    {
      if(sweepcounter<selectedUpperFreq)
      {
        sweepcounter++;
      }
      else
      {
        sweep_direction=DOWN;
      }
    }
    else if (sweep_direction == DOWN) 
    {
      if(sweepcounter>selectedLowerFreq)
      {
        sweepcounter--;
      }
      else
      {
        sweep_direction=UP;
      }
    }
    setDDSFrequency(sweepcounter);
    currentFreq = sweepcounter;
  }
  if(mode == NORMAL) {

    // clamp the lower range whilst in normal mode
    selectedLowerFreq = selectedUpperFreq-1;
    
    setDDSFrequency(selectedUpperFreq); 
    currentFreq = selectedUpperFreq;
  }
}









/*
 * void dds_init() 
{
  // now we set the initial values for the AD9833 control register
  dds_out_data = 0x2100;   // resets all registers, sets DB13 for loading
                      // frequency regs via 2 consecutive 14-bit words
                      // (LSB first, then MSB), and sinewave output
  write_dds_spi();         // sends it
  
  //outData = 0x69F1;   // LSB for 1000Hz & Freq0 register = 29F1 + 4000
  dds_out_data = dds_freq;
  write_dds_spi();
  dds_out_data = 0x4000;   // MSB for 1000Hz & Freq0 register = 0000 + 4000
  write_dds_spi();
  dds_out_data = 0xC000;   // writes 000h into Phase0 register
  write_dds_spi();
  dds_out_data = dds_func;   // now exit reset mode for normal operation
  write_dds_spi();
  
}
*/



#endif
