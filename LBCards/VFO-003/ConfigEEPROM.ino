// Routines which deal with Configuration EEPROM

//unsigned long VFO_0_Freq = 1400000000ULL;
//unsigned long VFO_1_Freq = 1200000000ULL;
//unsigned long VFO_2_Freq = 1000000000ULL;
//
//uint32_t stepSize = STEP_1_MHZ;
//int32_t calFactor = 0;
//
//uint8_t VFO_O_OnOff = VFO_ON;
//uint8_t VFO_1_OnOff = VFO_ON;
//uint8_t VFO_2_OnOff = VFO_ON;
//
//si5351_drive VFO_0_Drive = SI5351_DRIVE_4MA;
//si5351_drive VFO_1_Drive = SI5351_DRIVE_4MA;
//si5351_drive VFO_2_Drive = SI5351_DRIVE_4MA;
//
//uint8_t currentVFONumber = 0;

#define FREQ0_OFFSET 0
#define FREQ1_OFFSET 4
#define FREQ2_OFFSET 8
#define STEPSIZE_OFFSET 12
#define CALVAL_OFFSET 16
#define VFO0DRIVE_OFFSET 20
#define VFO1DRIVE_OFFSET 24
#define VFO2DRIVE_OFFSET 28
#define VFO0ONOFF_OFFSET 32
#define VFO1ONOFF_OFFSET 33
#define VFO2ONOFF_OFFSET 34
#define VFONUMBER_OFFSET 35
#define MAGICNUMBER_OFFSET 36

// Load the configuration from the EEPROM
void loadEEPROM(void)
{
  VFO_0_Freq = EEPROM.get(FREQ0_OFFSET,VFO_0_Freq);
  VFO_1_Freq = EEPROM.get(FREQ1_OFFSET,VFO_1_Freq);
  VFO_2_Freq = EEPROM.get(FREQ2_OFFSET,VFO_2_Freq);
  stepSize = EEPROM.get(STEPSIZE_OFFSET,stepSize);
  calFactor = EEPROM.get(CALVAL_OFFSET,calFactor);
  VFO_0_Drive = EEPROM.get(VFO0DRIVE_OFFSET,VFO_0_Drive);
  VFO_1_Drive = EEPROM.get(VFO1DRIVE_OFFSET,VFO_1_Drive);
  VFO_2_Drive = EEPROM.get(VFO2DRIVE_OFFSET,VFO_2_Drive);
  VFO_O_OnOff = EEPROM.get(VFO0ONOFF_OFFSET,VFO_O_OnOff);
  VFO_1_OnOff = EEPROM.get(VFO1ONOFF_OFFSET,VFO_1_OnOff);
  VFO_2_OnOff = EEPROM.get(VFO2ONOFF_OFFSET,VFO_2_OnOff);
  currentVFONumber = EEPROM.get(VFONUMBER_OFFSET,currentVFONumber);
}

// Store the configuration to the EEPROM
void storeEEPROM(void)
{
  uint8_t magicNumber = 0x5a;
  EEPROM.put(FREQ0_OFFSET,VFO_0_Freq);
  EEPROM.put(FREQ1_OFFSET,VFO_1_Freq);
  EEPROM.put(FREQ2_OFFSET,VFO_2_Freq);
  EEPROM.put(STEPSIZE_OFFSET,stepSize);
  EEPROM.put(CALVAL_OFFSET,calFactor);
  EEPROM.put(VFO0DRIVE_OFFSET,VFO_0_Drive);
  EEPROM.put(VFO1DRIVE_OFFSET,VFO_1_Drive);
  EEPROM.put(VFO2DRIVE_OFFSET,VFO_2_Drive);
  EEPROM.put(VFO0ONOFF_OFFSET,VFO_O_OnOff);
  EEPROM.put(VFO1ONOFF_OFFSET,VFO_1_OnOff);
  EEPROM.put(VFO2ONOFF_OFFSET,VFO_2_OnOff);
  EEPROM.put(VFONUMBER_OFFSET,currentVFONumber);
  EEPROM.put(MAGICNUMBER_OFFSET,magicNumber);
}

// Set default EEPROM values
void setEEPROMDefaults(void)
{
  VFO_0_Freq = 1400000000ULL;
  VFO_1_Freq = 1200000000ULL;
  VFO_2_Freq = 1000000000ULL;
  stepSize = STEP_1_MHZ;
  calFactor = 0;
  VFO_0_Drive = SI5351_DRIVE_4MA;
  VFO_1_Drive = SI5351_DRIVE_4MA;
  VFO_2_Drive = SI5351_DRIVE_4MA;
  VFO_O_OnOff = VFO_ON;
  VFO_1_OnOff = VFO_ON;
  VFO_2_OnOff = VFO_ON;
  currentVFONumber = 0;
}

// If the magic number is present, then load the default values from thr EEPROM
// If the magic number is not present, then store the default values to the EEPROM
void checkEEPROM(void)
{
  magicNumber = 0xa5;
  #ifdef HAS_INTERNAL_EEPROM
    if (EEPROM.get(MAGICNUMBER_OFFSET,magicNumber) == 0xa5)
      loadEEPROM();
    else
    {
      setEEPROMDefaults();
      storeEEPROM();
    }
  #endif
}
