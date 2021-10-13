// Routines which deal with Configuration EEPROM

#define MAGIC_NUM 0x5a  // Change to different number re-write default table

// Offsets into the EEPROM
#define FREQ0_OFFSET 0          // VFO 0 frequency
#define FREQ1_OFFSET 4
#define FREQ2_OFFSET 8
#define STEPSIZE_OFFSET 12      // Frequency step size
#define CALVAL_OFFSET 16
#define VFO0ONOFF_OFFSET 20     // VFO 0 On/Off control
#define VFO1ONOFF_OFFSET 24
#define VFO2ONOFF_OFFSET 28
#define VFONUMBER_OFFSET 32     // Current VFO being set
#define MAGICNUMBER_OFFSET 33   // Reload defaults flag

// Load the configuration from the EEPROM
void loadEEPROM(void)
{
  VFO_0_Freq = EEPROM.get(FREQ0_OFFSET,VFO_0_Freq);
  VFO_1_Freq = EEPROM.get(FREQ1_OFFSET,VFO_1_Freq);
  VFO_2_Freq = EEPROM.get(FREQ2_OFFSET,VFO_2_Freq);
  stepSize = EEPROM.get(STEPSIZE_OFFSET,stepSize);
  calFactor = EEPROM.get(CALVAL_OFFSET,calFactor);
  VFO_O_OnOff = EEPROM.get(VFO0ONOFF_OFFSET,VFO_O_OnOff);
  VFO_1_OnOff = EEPROM.get(VFO1ONOFF_OFFSET,VFO_1_OnOff);
  VFO_2_OnOff = EEPROM.get(VFO2ONOFF_OFFSET,VFO_2_OnOff);
  currentVFONumber = EEPROM.get(VFONUMBER_OFFSET,currentVFONumber);
}

// Store the configuration to the EEPROM
void storeEEPROM(void)
{
  uint8_t magicNumber = MAGIC_NUM;
  EEPROM.put(FREQ0_OFFSET,VFO_0_Freq);
  EEPROM.put(FREQ1_OFFSET,VFO_1_Freq);
  EEPROM.put(FREQ2_OFFSET,VFO_2_Freq);
  EEPROM.put(STEPSIZE_OFFSET,stepSize);
  EEPROM.put(CALVAL_OFFSET,calFactor);
  EEPROM.put(VFO0ONOFF_OFFSET,VFO_O_OnOff);
  EEPROM.put(VFO1ONOFF_OFFSET,VFO_1_OnOff);
  EEPROM.put(VFO2ONOFF_OFFSET,VFO_2_OnOff);
  EEPROM.put(VFONUMBER_OFFSET,currentVFONumber);
  EEPROM.put(MAGICNUMBER_OFFSET,magicNumber);
}

// Set default EEPROM values
// Loaded only the first time the program is run on a "virgin" Arduino Pro Mini
void setEEPROMDefaults(void)
{
  VFO_0_Freq = 1400000000ULL;
  VFO_1_Freq = 1200000000ULL;
  VFO_2_Freq = 1000000000ULL;
  stepSize = STEP_1_MHZ;
  calFactor = 0;
  VFO_O_OnOff = VFO_ON;
  VFO_1_OnOff = VFO_ON;
  VFO_2_OnOff = VFO_ON;
  currentVFONumber = 0;
}

// If the magic number is present, then load the default values from thr EEPROM
// If the magic number is not present, then store the default values to the EEPROM
void checkEEPROM(void)
{
  magicNumber = MAGIC_NUM;
  #ifdef HAS_INTERNAL_EEPROM
    if (EEPROM.get(MAGICNUMBER_OFFSET,magicNumber) == MAGIC_NUM)
      loadEEPROM();
    else
    {
      setEEPROMDefaults();
      storeEEPROM();
    }
  #endif
}
