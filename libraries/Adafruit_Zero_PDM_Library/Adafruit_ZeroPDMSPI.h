/*!
 * @file Adafruit_ZeroPDMSPI.h
 */
#ifndef ADAFRUIT_ZEROPDMSPI_H
#define ADAFRUIT_ZEROPDMSPI_H

/// @cond DISABLE
#if defined(__SAMD51__)
/// @endcond DISABLE

#include <Arduino.h>
#include <SPI.h>

/*!
 * ZeroPDM SPI driver
 */
class Adafruit_ZeroPDMSPI {
public:
  /*!
   * @brief Create a new instance of an PDM audio transmitter over SPI
   * @param theSPI SPI to use
   */
  Adafruit_ZeroPDMSPI(SPIClass *theSPI);

  /*!
   * @brief Initialize the SPI audio receiver.
   * @param freq Frequency (in Hertz)
   * @return Returns if connection was successful
   */
  bool begin(uint32_t freq);

  /*!
   * @brief Alternates 0 to 1 to let you know that data is ready to be read
   * @param value Variable to set the reading to
   * @param removeDC Whether or not to remove the DC offset
   * @return Returns if the word is even or not
   */
  bool decimateFilterWord(uint16_t *value, bool removeDC = true);

  /*!
   * @brief Sets the mic gain
   * @param g Mic gain
   */
  void setMicGain(float g = 1.0);

  /*!
   * @brief Sample rate
   */
  float sampleRate;

private:
  SPIClass *_spi = NULL;
  Sercom *_sercom = NULL;
  IRQn_Type _irq;
  volatile uint32_t *_dataReg;

  uint16_t dcCounter = 0;         // Rolls over every DC_PERIOD samples
  uint32_t dcSum = 0;             // Accumulates DC_PERIOD samples
  uint16_t dcOffsetPrior = 32768; // DC offset interpolates linearly
  uint16_t dcOffsetNext = 32768;  // between these two values

  uint16_t micGain = 256; // 1:1
};

/// @cond DISABLE
#endif // defined(__SAMD51__)
/// @endcond DISABLE

#endif
