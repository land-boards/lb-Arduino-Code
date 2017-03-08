#MCUFRIEND_kbv 
Library for Uno 2.4, 2.8, 3.5, 3.6, 3.95 inch mcufriend  Shields

1. The Arduino Library Manager should find and install MCUFRIEND_kbv library

2. Install the Adafruit_GFX library if not already in your User libraries.

3. Insert your Mcufriend style display shield into UNO.   Only 28-pin shields are supported.

4. Build any of the Examples from the File->Examples->Mcufriend_kbv menu.  e.g.

graphictest_kbv.ino: shows all the methods.

LCD_ID_readreg.ino:  diagnostic check to identify unsupported controllers.

MCUFRIEND_kbv inherits all the methods from 
the Adafruit_GFX class: https://learn.adafruit.com/adafruit-gfx-graphics-library/overview 
and Print class: https://www.arduino.cc/en/Serial/Print

The only "new" methods are hardware related: 
vertScroll(), readGRAM(), readPixel(), setAddrWindow(), pushColors(), readID(), begin()

readReg(), pushCommand() access the controller registers

The File layout changed with v2.9.3.   If replacing a pre-v2.9.3 library:
Please leave IDE.  Delete the existing MCUFRIEND_kbv folder.  Start the IDE.  Install from Library Manager.

HOW TO INSTALL AND USE: is now in "mcufriend_how_to.txt"

CHANGE HISTORY:         is now in "mcufriend_history.txt"
