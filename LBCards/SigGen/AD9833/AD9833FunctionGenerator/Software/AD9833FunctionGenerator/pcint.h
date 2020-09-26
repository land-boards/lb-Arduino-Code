#ifndef __PCINT_H__
#define __PCINT_H__

#include "config.h"
#include "EnableInterrupt.h"
#include "dds.h"
#include "digipot.h"

float gainCompensation = 1;

#define DEBOUNCE_DELAY 300 // in ms
uint32_t pd2_last_interrupt_time = 0;
uint32_t pd3_last_interrupt_time = 0;
uint32_t pd6_last_interrupt_time = 0;
uint32_t pd5_last_interrupt_time = 0;

const int FreqRelayOutput = 6;

// 1 = 1Hz -> 1Khz
// 0 = 10KHz -> 100KHz
int LFOMode = 1;    

#define PCINT_DEBUG



// mode button interrupt
void doPD2Int() 
{
  uint32_t interrupt_time = millis();
  
  if (interrupt_time - pd2_last_interrupt_time > DEBOUNCE_DELAY) 
  {
    if (mode == NORMAL)
    {
      //Serial.println("SWEEP");
      mode = SWEEP;
      // start the sweep at the lower selected frequency
      sweepcounter = selectedLowerFreq;
    }
    else if( mode == SWEEP)
    {
      //Serial.println("NORMAL");
      mode = NORMAL;
    }
  }
  pd2_last_interrupt_time = interrupt_time;
}

void doPD3Int() 
{
   uint32_t interrupt_time = millis();
  
  if (interrupt_time - pd3_last_interrupt_time > DEBOUNCE_DELAY) 
  {
    if(func == SINE)
    {
      func = TRIANGLE;
      gainCompensation = 1;
      digipot_write_spi(MCP_WRITEPB0, TriUnityLvl, digipot_ss_pin);
      digipot_write_spi(MCP_WRITEPB1, TriOffsetLvl, digipot_ss_pin);
      //Serial.println("TRI");
    }
    else if(func == TRIANGLE)
    {
      func = SQUARE;
      gainCompensation = 1;
      digipot_write_spi(MCP_WRITEPB0, SquareUnityLvl, digipot_ss_pin);
      digipot_write_spi(MCP_WRITEPB1, SquareOffsetLvl, digipot_ss_pin);
      //Serial.println("SQR");
    }
    else if(func == SQUARE) 
    {
      func = SINE;
      
      gainCompensation = 1;
      digipot_write_spi(MCP_WRITEPB0, SineUnityLvl, digipot_ss_pin);
      digipot_write_spi(MCP_WRITEPB1, SineOffsetLvl, digipot_ss_pin);
      //Serial.println("SINE");
    }
    //Serial.println("PD3");
  }
  pd3_last_interrupt_time = interrupt_time;
  
}


void doPD5Int() 
{
  uint32_t interrupt_time = millis();
  
  if (interrupt_time - pd5_last_interrupt_time > DEBOUNCE_DELAY) 
  {
    //Serial.println("PD4");
    
    if(maxFreq == 1000)
    {
      maxFreq = 10000;
    }
    else if (maxFreq == 10000)
    {
      maxFreq = 100000;
    }
    else if (maxFreq == 100000)
    {
      maxFreq = 1000;
    }
    /*else if (maxFreq == 1000000)
    {
      maxFreq = 1000;
    }*/
    /*if(LFOMode)
    {
      LFOMode = 0;  
      maxFreq=2000000;
      //Serial.println("Changing to VHF");
      //digitalWrite(PD6, LOW);
    }
    else 
    {
      LFOMode = 1;
      maxFreq=10000;
      //Serial.println("Changing to VLF");
      //digitalWrite(PD6, HIGH);
    }*/
  }
  pd5_last_interrupt_time = interrupt_time;
  
}

void doPD6Int()
{
  uint32_t interrupt_time = millis();
  
  if (interrupt_time - pd6_last_interrupt_time > DEBOUNCE_DELAY) 
  {
  /*  if (current_phase == PHASE0)
    {
      current_phase = PHASE90;
      printBinaryDWORD(current_phase); Serial.println(" - PHASE90");
    }
    else if (current_phase == PHASE90)
    {
      current_phase = PHASE180;
      printBinaryDWORD(current_phase); Serial.println(" - PHASE180");
    }
    else if (current_phase == PHASE180)
    {
      current_phase = PHASE270;
      printBinaryDWORD(current_phase); Serial.println(" - PHASE270");
    }
    else if (current_phase == PHASE270)
    {
      current_phase = PHASE0;
      printBinaryDWORD(current_phase); Serial.println(" - PHASE0");
    }
    */
    /*printBinaryDWORD(0xC000);
    Serial.println();
    printBinaryDWORD(0xC400);
    Serial.println();
    printBinaryDWORD(0xC800);
    Serial.println();
    printBinaryDWORD(0xCC00);
    Serial.println();
    printBinaryDWORD(0xCFFF);
    Serial.println();**/    
  }

  pd6_last_interrupt_time = interrupt_time;
}

void setup_pcint()
{
  
  enableInterrupt(PD2, doPD2Int, CHANGE); 
  enableInterrupt(PD3, doPD3Int, CHANGE); 
  enableInterrupt(PD5, doPD5Int, CHANGE); 
  enableInterrupt(PD6, doPD6Int, CHANGE);
  
  //pinMode(PD6, OUTPUT);
  //digitalWrite(PD6, HIGH);

  
}

#endif
