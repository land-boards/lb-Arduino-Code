// 20190417 M.lemming 
// Leider fehlt mal wieder das wichtigste - die verdrahtung
// AD9833 wird über SPI angebunden
// getestet mit Arduino ATMEGA168 und Arduino GUI 1.8.6
// Pinout
// VCC    5V
// GND    Masse
// DAT    Pin 11 
// CLK    PIN 13
// FSYNC  => Chip Select
// AGND   Output Masse
// OUT    Output Sinus, Triangle ca 800mV PP, zwischen 0V und 800mV, Square und half square ca. 0V 4,8V 

// Quelle ApplySignal.ino 2018 WLWilliams
// This sketch demonstrates the basic use of the AD9833 DDS module library.
// Using the ApplySignal to generate and/or change the signal.
// Library code found at: https://github.com/Billwilliams1952/AD9833-Library-Arduino
 
#include <AD9833.h>     // Include the library

#define FNC_PIN 10       // Can be any digital IO pin

//--------------- Create an AD9833 object ---------------- 
// Note, SCK and MOSI must be connected to CLK and DAT pins on the AD9833 for SPI
// genau aber wie ? siehe oben !

AD9833 gen(FNC_PIN);       // Defaults to 25MHz internal reference frequency

void setup() 
{
    // This MUST be the first command after declaring the AD9833 object
    gen.Begin();              

    // Apply a 1000 Hz sine wave using REG0 (register set 0). There are two register sets,
    // REG0 and REG1. 
    // Each one can be programmed for:
    //   Signal type - SINE_WAVE, TRIANGLE_WAVE, SQUARE_WAVE, and HALF_SQUARE_WAVE
    //   Frequency - 0 to 12.5 MHz
    //   Phase - 0 to 360 degress (this is only useful if it is 'relative' to some other signal
    //           such as the phase difference between REG0 and REG1).
    // In ApplySignal, if Phase is not given, it defaults to 0.
    // gen.ApplySignal(SINE_WAVE,REG0,1000);
    // gen.ApplySignal(SINE_WAVE,REG0,1000,0);
    // gen.ApplySignal(HALF_SQUARE_WAVE,REG0,1000);
    // gen.ApplySignal(SQUARE_WAVE,REG0,1000);
    // gen.ApplySignal(SINE_WAVE,REG0,1000);
   
    gen.EnableOutput(true);   // Turn ON the output - it defaults to OFF
    // There should be a 1000 Hz sine wave on the output of the AD9833
}

void loop() 
{

  //  Waveforms
    
    gen.ApplySignal(SQUARE_WAVE,REG0,1000);    delay(2500);

    gen.ApplySignal(HALF_SQUARE_WAVE,REG0,1000);  delay(2500); // Half-Square ergibt die Halbe Frequenz !!!

    gen.ApplySignal(SINE_WAVE,REG0,1000,0); delay(2500);

    gen.ApplySignal(TRIANGLE_WAVE,REG0,1000);delay(2500);
   

  //  Switch between register sets

    gen.ApplySignal(SINE_WAVE,REG0,1000);
    gen.ApplySignal(SINE_WAVE,REG1,2000);
    gen.SetPhase(REG1,180);           // Offset second freq by 180 deg
    gen.Reset();

    for (unsigned char lc = 0; lc < 6; lc++)    
    {
    gen.SetOutputSource(REG0);    
    delay(500);
    gen.SetOutputSource(REG1);    
    delay(500);

    }


    // Turn on off

    for (unsigned char lc = 0; lc < 6; lc++)    
    {
    gen.EnableOutput(false);delay(500);  // Turn OFF the output
    gen.EnableOutput(true);delay(500);  // Turn ON the output
    }


    
}
