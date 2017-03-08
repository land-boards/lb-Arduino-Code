#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>

/*
 * an empty Leonardo sketch uses 3.5kB + 4kB bootloader 
 * 
 * this C++ program avoids Serial and f-p.
 * so it just fits in the Flash.
 * 
 * This is a complete dummy sketch.   
 * its only purpose is to tell the IDE which libraries to use
 * 
 * The actual program is in the graphictest_v25.cpp
 * 
 * This enables me to build an identical AS7 project
 *
 * Edit the HOW_SLIM macro to build for other chips
 *
 */

