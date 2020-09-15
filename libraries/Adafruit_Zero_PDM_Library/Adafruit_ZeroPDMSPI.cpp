/*!
 * @file Adafruit_ZeroPDMSPI.cpp
 */
#include "Adafruit_ZeroPDMSPI.h"

/// @cond DISABLE
#if defined(__SAMD51__)
/// @endcond DISABLE

static uint16_t const sincfilter[64] = {
    0,    2,    9,    21,   39,   63,   94,   132,  179,  236,  302,
    379,  467,  565,  674,  792,  920,  1055, 1196, 1341, 1487, 1633,
    1776, 1913, 2042, 2159, 2263, 2352, 2422, 2474, 2506, 2516, 2506,
    2474, 2422, 2352, 2263, 2159, 2042, 1913, 1776, 1633, 1487, 1341,
    1196, 1055, 920,  792,  674,  565,  467,  379,  302,  236,  179,
    132,  94,   63,   39,   21,   9,    2,    0,    0};

#define DC_PERIOD 4096 //!< Recalculate DC offset this many samplings
// DC_PERIOD does NOT need to be a power of 2, but might save a few cycles.
// PDM rate is 46875, so 4096 = 11.44 times/sec

static Sercom *const sercomList[] = {
    SERCOM0, SERCOM1, SERCOM2, SERCOM3,
#if defined(SERCOM4)
    SERCOM4,
#endif
#if defined(SERCOM5)
    SERCOM5,
#endif
#if defined(SERCOM6)
    SERCOM6,
#endif
#if defined(SERCOM7)
    SERCOM7,
#endif
};

static IRQn_Type const sercomIRQList[] {
  SERCOM0_0_IRQn, SERCOM1_0_IRQn, SERCOM2_0_IRQn, SERCOM3_0_IRQn,
#if defined(SERCOM4)
      SERCOM4_0_IRQn,
#endif
#if defined(SERCOM5)
      SERCOM5_0_IRQn,
#endif
#if defined(SERCOM6)
      SERCOM6_0_IRQn,
#endif
#if defined(SERCOM7)
      SERCOM7_0_IRQn,
#endif
};

Adafruit_ZeroPDMSPI::Adafruit_ZeroPDMSPI(SPIClass *theSPI) { _spi = theSPI; }

bool Adafruit_ZeroPDMSPI::begin(uint32_t freq) {
  freq *= 64;
  SPISettings settings(freq, LSBFIRST, SPI_MODE0);

  _spi->begin();
  _spi->beginTransaction(settings); // this SPI transaction is left open
  _sercom = sercomList[_spi->getSercomIndex()];
  _irq = sercomIRQList[_spi->getSercomIndex()];
  _dataReg = _spi->getDataRegister();

  // Enabling 32-bit SPI must be done AFTER SPI.begin() which
  // resets registers. But SPI.CTRLC (where 32-bit mode is set) is
  // enable-protected, so peripheral must be disabled temporarily...
  _sercom->SPI.CTRLA.bit.ENABLE = 0; // Disable SPI
  while (_sercom->SPI.SYNCBUSY.bit.ENABLE)
    ;                                 // Wait for disable
  _sercom->SPI.CTRLC.bit.DATA32B = 1; // Enable 32-bit mode
  _sercom->SPI.CTRLA.bit.ENABLE = 1;  // Re-enable SPI
  while (_sercom->SPI.SYNCBUSY.bit.ENABLE)
    ; // Wait for enable
  // 4-byte word length is implicit in 32-bit mode,
  // no need to set up LENGTH register.

  _sercom->SPI.INTENSET.bit.DRE = 1; // Data-register-empty interrupt
  NVIC_DisableIRQ(_irq);
  NVIC_ClearPendingIRQ(_irq);
  NVIC_SetPriority(_irq, 0); // Top priority
  NVIC_EnableIRQ(_irq);

  _sercom->SPI.DATA.bit.DATA = 0; // Kick off SPI free-run

  // sampleRate is float in case factors change to make it not divide evenly.
  // It DOES NOT CHANGE over time, only playbackRate does.
  sampleRate = (48000000.0 / 2.0) / ((_sercom->SPI.BAUD.reg + 1) * 64.0);

  return true; // Success
}

bool Adafruit_ZeroPDMSPI::decimateFilterWord(uint16_t *value, bool removeDC) {
  static bool evenWord = true; // Alternates 0/1 with each interrupt call
  static uint32_t sumTemp = 0; // Temp. value used across 2 interrupt calls
  // Shenanigans: SPI data read/write are shadowed...even though it appears
  // the same register here, it's legit to write new MOSI value before
  // reading the received MISO value from the same location. This helps
  // avoid a gap between words...provides a steady stream of bits.
  *_dataReg = 0;               // Write clears DRE flag, starts next xfer
  uint32_t sample = *_dataReg; // Read last-received word

  uint32_t sum = 0; // local var = register = faster than sumTemp
  if (evenWord) {   // Even-numbered 32-bit word...
    // At default speed and optimization settings (120 MHz -Os), the PDM-
    // servicing interrupt consumes about 12.5% of CPU time. Though this
    // code looks bulky, it's actually reasonably efficient (sincfilter[] is
    // const, so these compile down to constants, there is no array lookup,
    // any any zero-value element refs will be removed by the compiler).
    // Tested MANY methods and this was hard to beat. One managed just under
    // 10% load, but required 4KB of tables...not worth it for small boost.
    // Can get an easy boost with overclock and optimizer tweaks.
    if (sample & 0x00000001)
      sum += sincfilter[0];
    if (sample & 0x00000002)
      sum += sincfilter[1];
    if (sample & 0x00000004)
      sum += sincfilter[2];
    if (sample & 0x00000008)
      sum += sincfilter[3];
    if (sample & 0x00000010)
      sum += sincfilter[4];
    if (sample & 0x00000020)
      sum += sincfilter[5];
    if (sample & 0x00000040)
      sum += sincfilter[6];
    if (sample & 0x00000080)
      sum += sincfilter[7];
    if (sample & 0x00000100)
      sum += sincfilter[8];
    if (sample & 0x00000200)
      sum += sincfilter[9];
    if (sample & 0x00000400)
      sum += sincfilter[10];
    if (sample & 0x00000800)
      sum += sincfilter[11];
    if (sample & 0x00001000)
      sum += sincfilter[12];
    if (sample & 0x00002000)
      sum += sincfilter[13];
    if (sample & 0x00004000)
      sum += sincfilter[14];
    if (sample & 0x00008000)
      sum += sincfilter[15];
    if (sample & 0x00010000)
      sum += sincfilter[16];
    if (sample & 0x00020000)
      sum += sincfilter[17];
    if (sample & 0x00040000)
      sum += sincfilter[18];
    if (sample & 0x00080000)
      sum += sincfilter[19];
    if (sample & 0x00100000)
      sum += sincfilter[20];
    if (sample & 0x00200000)
      sum += sincfilter[21];
    if (sample & 0x00400000)
      sum += sincfilter[22];
    if (sample & 0x00800000)
      sum += sincfilter[23];
    if (sample & 0x01000000)
      sum += sincfilter[24];
    if (sample & 0x02000000)
      sum += sincfilter[25];
    if (sample & 0x04000000)
      sum += sincfilter[26];
    if (sample & 0x08000000)
      sum += sincfilter[27];
    if (sample & 0x10000000)
      sum += sincfilter[28];
    if (sample & 0x20000000)
      sum += sincfilter[29];
    if (sample & 0x40000000)
      sum += sincfilter[30];
    if (sample & 0x80000000)
      sum += sincfilter[31];
    sumTemp = sum; // Copy register to static var for next call
  } else {
    if (sample & 0x00000001)
      sum += sincfilter[32];
    if (sample & 0x00000002)
      sum += sincfilter[33];
    if (sample & 0x00000004)
      sum += sincfilter[34];
    if (sample & 0x00000008)
      sum += sincfilter[35];
    if (sample & 0x00000010)
      sum += sincfilter[36];
    if (sample & 0x00000020)
      sum += sincfilter[37];
    if (sample & 0x00000040)
      sum += sincfilter[38];
    if (sample & 0x00000080)
      sum += sincfilter[39];
    if (sample & 0x00000100)
      sum += sincfilter[40];
    if (sample & 0x00000200)
      sum += sincfilter[41];
    if (sample & 0x00000400)
      sum += sincfilter[42];
    if (sample & 0x00000800)
      sum += sincfilter[43];
    if (sample & 0x00001000)
      sum += sincfilter[44];
    if (sample & 0x00002000)
      sum += sincfilter[45];
    if (sample & 0x00004000)
      sum += sincfilter[46];
    if (sample & 0x00008000)
      sum += sincfilter[47];
    if (sample & 0x00010000)
      sum += sincfilter[48];
    if (sample & 0x00020000)
      sum += sincfilter[49];
    if (sample & 0x00040000)
      sum += sincfilter[50];
    if (sample & 0x00080000)
      sum += sincfilter[51];
    if (sample & 0x00100000)
      sum += sincfilter[52];
    if (sample & 0x00200000)
      sum += sincfilter[53];
    if (sample & 0x00400000)
      sum += sincfilter[54];
    if (sample & 0x00800000)
      sum += sincfilter[55];
    if (sample & 0x01000000)
      sum += sincfilter[56];
    if (sample & 0x02000000)
      sum += sincfilter[57];
    if (sample & 0x04000000)
      sum += sincfilter[58];
    if (sample & 0x08000000)
      sum += sincfilter[59];
    if (sample & 0x10000000)
      sum += sincfilter[60];
    if (sample & 0x20000000)
      sum += sincfilter[61];
    if (sample & 0x40000000)
      sum += sincfilter[62];
    if (sample & 0x80000000)
      sum += sincfilter[63];
    sum += sumTemp; // Add static var from last call

    if (removeDC) {
      // 'sum' is new raw audio value -- process it --------------------------
      uint16_t dcOffset;

      dcSum += sum; // Accumulate long-term average for DC offset correction
      if (++dcCounter < DC_PERIOD) {
        // Interpolate between dcOffsetPrior and dcOffsetNext
        dcOffset = dcOffsetPrior +
                   (dcOffsetNext - dcOffsetPrior) * dcCounter / DC_PERIOD;
      } else {
        // End of period reached, move 'next' to 'previous,' calc new 'next'
        // from avg
        dcOffsetPrior = dcOffset = dcOffsetNext;
        dcOffsetNext = dcSum / DC_PERIOD;
        dcCounter = dcSum = 0;
      }

      // Adjust raw reading by DC offset to center (ish) it, scale by mic gain
      int32_t adjusted = ((int32_t)sum - dcOffset) * micGain / 256;

      // Go back to uint16_t space and clip to 16-bit range
      adjusted += 32768;
      if (adjusted > 65535)
        adjusted = 65535;
      else if (adjusted < 0)
        adjusted = 0;

      *value = adjusted;
    } else {
      *value = sum;
    }
  }
  evenWord = !evenWord;

  return evenWord;
}

// Adjust input gain, higher = amplify, 1.0 = normal, no adjustment
void Adafruit_ZeroPDMSPI::setMicGain(float g) {
  if (g > (65535.0 / 256.0))
    g = (65535.0 / 256.0); // sic
  else if (g < 0.0)
    g = 0.0;
  micGain = (uint16_t)(g * 256.0 + 0.5);
}

/// @cond DISABLE
#endif // defined(__SAMD51__)
/// @endcond DISABLE
