#include <AD9833.h>

/**
 * AD9833 Test pattern
 */

//Function pin to enable SPI communication. Active LOW, set up by the AD9833::begin() function.
#define FNC_PIN 4 

//AD9833 library object
AD9833 ad9833;

void setup() { 
    // This MUST be the first command after declaring the AD9833 object
    ad9833.begin(FNC_PIN);
}

void loop() { 

    /*
     * Apply a signal of type:
     * SINE_WAVE, SQUARE_WAVE, or TRIANGLE_WAVE
     * with frequency in KHz.
     */
    ad9833.setFrequency(SINE_WAVE, 50); //This should output a 50KHz sine wave.
    delay(1000);
}

