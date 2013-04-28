////////////////////////////////////////////////////////////////////////////////////
// Newhaven Displays Library for the Arduino
// From the Arduino LCD API 1.0 page http://arduino.cc/playground/Code/LCDAPI
// Base library is LCDi2cNHD
// 2012-04-11 DGG Modified library to run under Arduino 1.0
////////////////////////////////////////////////////////////////////////////////////

#ifndef LCDi2cNHD_h
#define LCDi2cNHD_h
#define _LCDEXPANDED				// If defined turn on advanced functions

#include <inttypes.h>
#include "Print.h"

class LCDi2cNHD : public Print 
{
public: 
	LCDi2cNHD(uint8_t num_lines, uint8_t num_col, int i2c_address, uint8_t display);
	void command(uint8_t value);
	void init();
	void setDelay(int,int);
//	virtual void write(uint8_t);	// DGG - Deleted this line and replaced with the next line
	virtual size_t write(uint8_t);	// write has a different return typw in Arduino 1.0
	void clear();
	void home();
	void on();
	void off();
	void cursor_on();
	void cursor_off();
	void blink_on();
	void blink_off();
	void setCursor(uint8_t Line, uint8_t Col );
	
	// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
	// []
	// []	Extended Functions
	// []
	// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
	
#ifdef _LCDEXPANDED		
	uint8_t status();
	void load_custom_character(uint8_t char_num, uint8_t *rows);
	 void setBacklight(uint8_t new_val);
	 void setContrast(uint8_t new_val);
#endif
private:
};

#endif

