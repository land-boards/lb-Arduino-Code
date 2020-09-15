#include <SPI.h>
#include <Adafruit_ZeroPDMSPI.h>

#define PDM_SPI            SPI2    // PDM mic SPI peripheral
#define PDM_SERCOM_HANDLER SERCOM3_0_Handler

Adafruit_ZeroPDMSPI pdmspi(&PDM_SPI);

// INTERRUPT HANDLERS ------------------------------------------------------
volatile int16_t pdmLastReading = 0;
void PDM_SERCOM_HANDLER(void) {
  digitalWrite(13, HIGH);
  uint16_t v = 0;
  if (pdmspi.decimateFilterWord(&v)) {
    pdmLastReading = (int32_t)v - 32768;
  }
  digitalWrite(13, LOW);
}

void setup() {
  while (!Serial) delay(10);
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  delay(100);
  Serial.println("PDM Mic test");
  Serial.println("-------------------");
  
  pdmspi.begin(16000);
  Serial.print("Final PDM frequency: "); Serial.println(pdmspi.sampleRate);

  // Set up analog output ------------------------------------------
  analogWriteResolution(12);
}

void loop() {
  analogWrite(A0, 2048 + pdmLastReading / 16);
  //Serial.println(voiceLastReading);
}
