#ifndef LCDI2Ct_h

#define LCDI2C_h

#define CMDDELAY 50        // Delay to wait after sending commands;
#define POSDELAY 100		 // Long delay required by Position command
#define CHARDELAY 0

#define LCDI2C_MIN_BRIGHTNESS		0
#define LCDI2C_MAX_BRIGHTNESS		250
#define LCDI2C_VALUE_OUT_OF_RANGE	1
#define LCDI2C_MIN_CONTRAST			0
#define LCDI2C_MAX_CONTRAST			100

#include <inttypes.h>
#include "Print.h"

class LCDI2C : public Print {
public: 
	LCDI2C(int,int,int,int);		//LCDI2C(int num_lines,int num_col,int i2c_address,int display);
  
	void command(int value);
	void writeStartUpScreen(char message[32]);
	void init();
	virtual size_t write(uint8_t);
	void clear();
	void home();
	void on(int value);
	void off();
	void cursor_on();
	void cursor_off();
	void blink_on();
	void blink_off();
	void left();
	void right();
	int keypad();
  	// Overload the Print class function for strings because
	// the base class implementation causes problems by doing
	// an I2C I/O for every character
	void printstr(const char[]);
	void setCursor(int line_num, int x);

// Values for graphtype in calls to init_bargraph
#define LCDI2C_THIN_VERTICAL_BAR_GRAPH    1 // **
#define LCDI2C_THICK_VERTICAL_BAR_GRAPH    2 // **
#define LCDI2C_HORIZONTAL_BAR_GRAPH  3
#define LCDI2C_HORIZONTAL_LINE_GRAPH 4

	unsigned char init_bargraph(unsigned char graphtype);
	void draw_horizontal_graph(unsigned char row, unsigned char column, unsigned char len,  unsigned char pixel_col_end);
	void draw_vertical_graph(unsigned char row, unsigned char column, unsigned char len,  unsigned char pixel_col_end);

#define LCDI2C_NUM_CUSTOM_CHARS 8
#define LCDI2C_CUSTOM_CHAR_SIZE 8
	void load_custom_character(unsigned char char_num, unsigned char *rows);
	unsigned char set_backlight_brightness(unsigned char new_val);
	unsigned char set_contrast(unsigned char new_val);

	private:
	

};

#endif

