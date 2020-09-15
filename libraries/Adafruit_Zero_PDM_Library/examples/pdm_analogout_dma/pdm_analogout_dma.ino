#include <Adafruit_ZeroPDM.h>
#include <Adafruit_ZeroDMA.h>
#include "utility/dma.h"

// Create PDM receiver object, with Clock and Data pins used (not all pins available)
Adafruit_ZeroPDM pdm = Adafruit_ZeroPDM(1, 4);      // Metro M0 or Arduino zero
//Adafruit_ZeroPDM pdm = Adafruit_ZeroPDM(34, 35);  // CPlay express

// a windowed sinc filter for 44 khz, 64 samples
#define SAMPLERATE_HZ 16000
#define DECIMATION    64
uint16_t sincfilter[DECIMATION] = {0, 2, 9, 21, 39, 63, 94, 132, 179, 236, 302, 379, 467, 565, 674, 792, 920, 1055, 1196, 1341, 1487, 1633, 1776, 1913, 2042, 2159, 2263, 2352, 2422, 2474, 2506, 2516, 2506, 2474, 2422, 2352, 2263, 2159, 2042, 1913, 1776, 1633, 1487, 1341, 1196, 1055, 920, 792, 674, 565, 467, 379, 302, 236, 179, 132, 94, 63, 39, 21, 9, 2, 0, 0};

// We'll use DMA to transfer one chunk of data from PDM/I2S for us
Adafruit_ZeroDMA myDMA;
// DMA status codes returned by some functions
ZeroDMAstatus    stat;
// The memory we'll be reading from I2S
#define  DMA_DATA_LENGTH                (DECIMATION / 16)      // 16 bits per 'I2S sample'
uint32_t dest_memory[DMA_DATA_LENGTH];

// Callback for end-of-DMA-transfer
volatile bool transfer_is_done; // Done yet?
void dma_callback(Adafruit_ZeroDMA *dma) {
  transfer_is_done = true;
}

void setup() {
  pinMode(13, OUTPUT);
  
  // Configure serial port.
  while (!Serial);
  Serial.begin(115200);
  Serial.println("SAMD PDM DMA Demo");

  // Initialize the PDM/I2S receiver
  if (!pdm.begin()) {
    Serial.println("Failed to initialize I2S/PDM!");
    while (1);
  }
  Serial.println("PDM initialized");

  // Configure PDM receiver, sample rate
  if (!pdm.configure(SAMPLERATE_HZ * DECIMATION / 16, true)) {
    Serial.println("Failed to configure PDM");
    while (1);
  }
  Serial.println("PDM configured");

  // use analog output A0 @ full rez
  analogWriteResolution(10);
  pinMode(A0, OUTPUT);

  Serial.println("Configuring DMA trigger");
  void *i2s_data_reg;

  if (pdm.getSerializer() == I2S_SERIALIZER_0) {
    myDMA.setTrigger(0x29);               // I2S RX 0 Trigger (see DS Table 19-8. Peripheral Trigger Source)
    i2s_data_reg = (void *)&I2S->DATA[0]; // Serializer 0
  } else {
    myDMA.setTrigger(0x2A);               // I2S RX 1 Trigger (see DS Table 19-8. Peripheral Trigger Source)
    i2s_data_reg = (void *)&I2S->DATA[1]; // Serializer 1
  }
  myDMA.setAction(DMA_TRIGGER_ACTON_BEAT);

  Serial.print("Allocating DMA channel...");
  stat = myDMA.allocate();
  myDMA.printStatus(stat);

  Serial.println("Setting up transfer");
  myDMA.addDescriptor(
    i2s_data_reg,                     // move data from here
    dest_memory,                      // move data to here
    DMA_DATA_LENGTH,                  // this many...
    DMA_BEAT_SIZE_WORD,               // bytes/hword/words
    false,                            // increment source addr?
    true);                            // increment dest addr?

  Serial.println("Adding callback");
  // register_callback() can optionally take a second argument
  // (callback type), default is DMA_CALLBACK_TRANSFER_DONE
  myDMA.setCallback(dma_callback);

  // kick it off
  transfer_is_done = false;
  stat = myDMA.startJob();
}


#define ADAPDM_REPEAT_LOOP_16(X) X X X X X X X X X X X X X X X X

void loop() {
  uint16_t runningsum = 0;
  uint16_t *sinc_ptr = sincfilter;

  while(!transfer_is_done); // Chill until DMA transfer completes

  // save the samples
  uint32_t samples[DMA_DATA_LENGTH]; 
  memcpy(samples, dest_memory, 4 * DMA_DATA_LENGTH);  // 32 bits (4 bytes) per sample

  // start next DMA xfer!
  transfer_is_done = false;
  stat = myDMA.startJob();

  PORT->Group[0].OUTSET.reg = 1 << 17;
  for (uint8_t samplenum=0; samplenum < (DECIMATION/16) ; samplenum++) {
     uint16_t sample = samples[samplenum] & 0xFFFF;
     
     ADAPDM_REPEAT_LOOP_16(      // manually unroll loop: for (int8_t b=0; b<16; b++) 
       {
         // start at the LSB which is the 'first' bit to come down the line, chronologically 
         // (Note we had to set I2S_SERCTRL_BITREV to get this to work, but saves us time!)
         if (sample & 0x1) {
           runningsum += *sinc_ptr;
         }
         sinc_ptr++;
         sample >>= 1;
      }
    )
  }
  PORT->Group[0].OUTCLR.reg = 1 << 17;

  // since we wait for the samples from I2S peripheral, we dont need to delay, we will 'naturally'
  // wait the right amount of time between analog writes
  //Serial.println(runningsum);

  // "echo" the analog value we've calculated out to A0
  runningsum /= 64 ; // convert 16 bit -> 10 bit
  analogWrite(A0, runningsum);
  
  // note that we cannot print the the serial port fast enough to keep up!
}

