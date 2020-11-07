// Routines which deal with Configuration EEPROM

//unsigned long VFO_0_Freq = 100000000ULL;
//
//uint32_t stepSize = STEP_1_MHZ;
//
//uint8_t VFO_O_OnOff = VFO_ON;
//

#define FREQ0_OFFSET          0
#define STEPSIZE_OFFSET       4
#define VFO0ONOFF_OFFSET      8
#define WAVEFORM_TYPE_OFFSET  12
#define MAGICNUMBER_OFFSET    16

// Load the configuration from the EEPROM
void loadEEPROM(void)
{
  VFO_0_Freq = EEPROM.get(FREQ0_OFFSET,VFO_0_Freq);
  stepSize = EEPROM.get(STEPSIZE_OFFSET,stepSize);
  VFO_O_OnOff = EEPROM.get(VFO0ONOFF_OFFSET,VFO_O_OnOff);
  waveformType = EEPROM.get(WAVEFORM_TYPE_OFFSET,waveformType);
}

// Store the configuration to the EEPROM
void storeEEPROM(void)
{
  uint8_t magicNumber = 0x5a;
  EEPROM.put(FREQ0_OFFSET,VFO_0_Freq);
  EEPROM.put(STEPSIZE_OFFSET,stepSize);
  EEPROM.put(VFO0ONOFF_OFFSET,VFO_O_OnOff);
  EEPROM.put(WAVEFORM_TYPE_OFFSET,waveformType);
  EEPROM.put(MAGICNUMBER_OFFSET,magicNumber);
}

// Set default EEPROM values
void setEEPROMDefaults(void)
{
  VFO_0_Freq = 1000000ULL;
  stepSize = STEP_1_MHZ;
  VFO_O_OnOff = VFO_ON;
  waveformType = SINE_WAVE_TYPE;
}

// If the magic number is present, then load the default values from thr EEPROM
// If the magic number is not present, then store the default values to the EEPROM
void checkEEPROM(void)
{
  uint8_t magicNumber = 0x5a;
  #ifdef HAS_INTERNAL_EEPROM
    if (EEPROM.get(MAGICNUMBER_OFFSET,magicNumber) == 0x5a)
      loadEEPROM();
    else
    {
      setEEPROMDefaults();
      storeEEPROM();
    }
  #endif
}
