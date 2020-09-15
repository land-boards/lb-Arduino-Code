#include "Adafruit_ZeroPDM.h"

#define SAMPLERATE_HZ 22000
#define DECIMATION    64

// Create PDM receiver object, with Clock and Data pins used (not all pins available)
Adafruit_ZeroPDM pdm = Adafruit_ZeroPDM(1, 4);  // Metro M0 or Arduino zero
//Adafruit_ZeroPDM pdm = Adafruit_ZeroPDM(34, 35);  // CPlay express

#define SERIALPORT Serial

// a windowed sinc filter for 44 khz, 64 samples
uint16_t sincfilter[DECIMATION] = {0, 2, 9, 21, 39, 63, 94, 132, 179, 236, 302, 379, 467, 565, 674, 792, 920, 1055, 1196, 1341, 1487, 1633, 1776, 1913, 2042, 2159, 2263, 2352, 2422, 2474, 2506, 2516, 2506, 2474, 2422, 2352, 2263, 2159, 2042, 1913, 1776, 1633, 1487, 1341, 1196, 1055, 920, 792, 674, 565, 467, 379, 302, 236, 179, 132, 94, 63, 39, 21, 9, 2, 0, 0};

// a manual loop-unroller!
#define ADAPDM_REPEAT_LOOP_16(X) X X X X X X X X X X X X X X X X


void setup() {
  pinMode(13, OUTPUT);
  
  // Configure serial port.
  while (!SERIALPORT);
  SERIALPORT.begin(115200);
  SERIALPORT.println("SAMD PDM Demo");

  // Initialize the PDM/I2S receiver
  if (!pdm.begin()) {
    SERIALPORT.println("Failed to initialize I2S/PDM!");
    while (1);
  }
  SERIALPORT.println("PDM initialized");

  // Configure PDM receiver, sample rate
  if (!pdm.configure(SAMPLERATE_HZ * DECIMATION / 16, true)) {
    SERIALPORT.println("Failed to configure PDM");
    while (1);
  }
  SERIALPORT.println("PDM configured");

  // use analog output A0 @ full rez
  analogWriteResolution(10);
  pinMode(A0, OUTPUT);
}


void loop() {
  uint16_t runningsum = 0;
  uint16_t *sinc_ptr = sincfilter;

  for (uint8_t samplenum=0; samplenum < (DECIMATION/16) ; samplenum++) {
     uint16_t sample = pdm.read() & 0xFFFF;    // we read 16 bits at a time, by default the low half

     ADAPDM_REPEAT_LOOP_16(      // manually unroll loop: for (int8_t b=0; b<16; b++) 
       {
         // start at the LSB which is the 'first' bit to come down the line, chronologically 
         // (Note we had to set I2S_SERCTRL_BITREV to get this to work, but saves us time!)
         if (sample & 0x1) {
           runningsum += *sinc_ptr;     // do the convolution
         }
         sinc_ptr++;
         sample >>= 1;
      }
    )
  }

  // since we wait for the samples from I2S peripheral, we dont need to delay, we will 'naturally'
  // wait the right amount of time between analog writes
  //Serial.println(runningsum);

  // "echo" the analog value we've calculated out to A0
  runningsum /= 64 ; // convert 16 bit -> 10 bit
  analogWrite(A0, runningsum);

  // note that we cannot print the the serial port fast enough to keep up!
}

