// example use of LCDI2C library with the  i2C lcd display libraries
// Demonstrate custom characters with animation
// Ran Talbott

#include <Wire.h>

//  Uncoment the correct two lines below for your display

#include <LCDi2cNHD.h>                       //   http://www.newhavendisplay.com
LCDi2cNHD lcd = LCDi2cNHD(4,20,0x50>>1,0);


byte Num_rows = 2;
byte Num_cols = 16;

#define BANNER_DURATION 2000
#define VERSION_STRING "custchar V0.6"

// Assume 16 character lcd

#define MINIMUM_LCD_ROWS    1
#define MAXIMUM_LCD_ROWS    4
#define DEFAULT_LCD_ROWS    2
#define MINIMUM_LCD_COLUMNS 16
#define MAXIMUM_LCD_COLUMNS 40
#define DEFAULT_LCD_COLUMNS 16

#define CURSOR_DELAY	10
// #define WRITE_DELAY		1




// Space Invaders (tm) character with tendrils right
#define CCHAR_INV_R		1
uint8_t Crom_inv_r[8] = { 0x0e, 0x1f, 0x15, 0x1f, 0x15, 0x0a, 0x05, 0x00 } ;

// Space Invaders (tm) character with tendrils left
#define CCHAR_INV_L		2
uint8_t Crom_inv_l[8] = { 0x0e, 0x1f, 0x15, 0x1f, 0x15, 0x0a, 0x14, 0x00 } ;

// Space Invaders (tm) character with tendrils down
#define CCHAR_INV_S		3
uint8_t Crom_inv_s[8] = { 0x0e, 0x1f, 0x15, 0x1f, 0x15, 0x15, 0x15, 0x00 } ;

// Simple smiley
#define CCHAR_SMILE		4
uint8_t Crom_smiley[8] = { 0x00, 0x00, 0x0a, 0x00, 0x11, 0x0e, 0x00, 0x00 } ;

// Simple frowny
#define CCHAR_FROWN		5
uint8_t Crom_frowny[8] = { 0x00, 0x00, 0x0a, 0x00, 0x00, 0x0e, 0x11, 0x00 } ;

// Simple neutral mouth
#define CCHAR_NEUT		6
uint8_t Crom_neut[8] = { 0x00, 0x00, 0x0a, 0x00, 0x00, 0x0e, 0x00, 0x00 } ;

// Simple open mouth
#define CCHAR_GASP		7
uint8_t Crom_gasp[8] = { 0x00, 0x00, 0x0a, 0x00, 0x0e, 0x0a, 0x0e, 0x00 } ;


// Bell
#define CCHAR_BELL		7
uint8_t Crom_bell[8] = { 0x00, 0x04, 0x0e, 0x0e, 0x0e, 0x1f, 0x04, 0x00 } ;

// Checkmark
#define CCHAR_CHECK		6
uint8_t Crom_check[8] = { 0x00, 0x01, 0x03, 0x16, 0x1c, 0x08, 0x00, 0x00 } ;

// Target
#define CCHAR_TARGET	5
uint8_t Crom_target[8] = { 0x00, 0x00, 0x0e, 0x11, 0x15, 0x11, 0x0e, 0x00 } ;

// Up arrow
#define CCHAR_ARROW_U		4
uint8_t Crom_up_arrow[8] = { 0x00, 0x04, 0x0e, 0x15, 0x04, 0x04, 0x04, 0x00 } ;

// Down arrow
#define CCHAR_ARROW_D		3
uint8_t Crom_down_arrow[8] = { 0x00, 0x04, 0x04, 0x04, 0x15, 0x0e, 0x04, 0x00 } ;

// Hourglass V 1
#define CCHAR_HOURGLASS_V1	1
uint8_t Crom_hourglass_v1[8] = { 0x00, 0x00, 0x1f, 0x0a, 0x04, 0x0e, 0x1f, 0x00 } ;

// Hourglass V 2
#define CCHAR_HOURGLASS_V2	2
uint8_t Crom_hourglass_v2[8] = { 0x00, 0x00, 0x1f, 0x0e, 0x04, 0x0a, 0x1f, 0x00 } ;

// Hourglass H
#define CCHAR_HOURGLASS_H	3
uint8_t Crom_hourglass_h[8] = { 0x00, 0x00, 0x11, 0x1b, 0x17, 0x1b, 0x11, 0x00 } ;


void setup()
{ 

  	lcd.init();                          // Init the display, clears the display
	do_banner();
        lcd.clear();

}


void loop()
{
	do_banner();
	Fancy_Clear();
	do_hourglass();
	Fancy_Clear();
	do_invader();
	Fancy_Clear();
}


	/*
	 * Display a simple text message
	 */
void do_banner()
{
	lcd.print(VERSION_STRING);
	delay(BANNER_DURATION);
}


/*
 * Show a rotating "hourglass" progress indicator
 */
#define WORK_ROW	0
#define WORK_COL	6
#define WORK_LOOPS	5
#define WORK_MSG	"Working"
#define WORK_CLR	"       "
#define HG_ROW		0
#define HG_COL		3
#define HG_DELAY	1000
#define DONE_MSG	"Done"
#define DONE_DELAY	3000

#define CUST_CHAR_LOAD_DELAY 50


void do_hourglass()
{
	byte i;

	lcd.load_custom_character(CCHAR_HOURGLASS_V1, Crom_hourglass_v1);
	delay(CUST_CHAR_LOAD_DELAY);
	lcd.load_custom_character(CCHAR_HOURGLASS_V2, Crom_hourglass_v2);
	delay(CUST_CHAR_LOAD_DELAY);
	lcd.load_custom_character(CCHAR_HOURGLASS_H, Crom_hourglass_h);
	delay(CUST_CHAR_LOAD_DELAY);
	lcd.load_custom_character(CCHAR_CHECK, Crom_check);
	delay(CUST_CHAR_LOAD_DELAY);

	lcd.setCursor(1, 6);
#ifdef CURSOR_DELAY
	delay(CURSOR_DELAY);
#endif
	lcd.write(CCHAR_HOURGLASS_V1);
	delay(10);
	lcd.write(CCHAR_HOURGLASS_H);
	delay(10);
	lcd.write(CCHAR_HOURGLASS_V2);
	delay(10);
	lcd.write(CCHAR_CHECK);
	delay(10);

	for (i = 0; i < WORK_LOOPS; i++)
		{
		lcd.setCursor(WORK_ROW, WORK_COL);
#ifdef CURSOR_DELAY
		delay(CURSOR_DELAY);
#endif
		lcd.print(WORK_MSG);
#ifdef WRITE_DELAY
		delay(WRITE_DELAY);
#endif

		lcd.setCursor(HG_ROW, HG_COL);
#ifdef CURSOR_DELAY
		delay(CURSOR_DELAY);
#endif
		lcd.write(CCHAR_HOURGLASS_V1);
		delay(HG_DELAY);

		lcd.setCursor(HG_ROW, HG_COL);
//		lcd.left();
#ifdef CURSOR_DELAY
		delay(CURSOR_DELAY);
#endif
		lcd.write(CCHAR_HOURGLASS_H);
		delay(HG_DELAY);

		lcd.setCursor(HG_ROW, HG_COL);
//		lcd.left();
#ifdef CURSOR_DELAY
		delay(CURSOR_DELAY);
#endif
		lcd.write(CCHAR_HOURGLASS_V2);
		delay(HG_DELAY);

		lcd.setCursor(HG_ROW, HG_COL);
//		lcd.left();
#ifdef CURSOR_DELAY
		delay(CURSOR_DELAY);
#endif
		lcd.write(CCHAR_HOURGLASS_H);
			// Add a little interest by making the "Working" blink
		lcd.setCursor(WORK_ROW, WORK_COL);
#ifdef CURSOR_DELAY
		delay(CURSOR_DELAY);
#endif
		lcd.print(WORK_CLR);
		delay(HG_DELAY);
		}
		//
	lcd.setCursor(HG_ROW, HG_COL);
#ifdef CURSOR_DELAY
		delay(CURSOR_DELAY);
#endif
	lcd.write(CCHAR_CHECK);
	lcd.setCursor(WORK_ROW, WORK_COL);
#ifdef CURSOR_DELAY
		delay(CURSOR_DELAY);
#endif
	lcd.print(DONE_MSG);
	delay(DONE_DELAY);

}

/*
 * Move a Space Invaders-style alien across the screen toward a 
 * face that changes expression as it gets closer.
 */

#define FACE_ROW	1
#define FACE_COL	15
#define INV_ROW		0
#define INV_DELAY	400
#define INV_DONE_DELAY	2000

const unsigned char Faces[4] = { CCHAR_SMILE, CCHAR_NEUT, CCHAR_FROWN, CCHAR_GASP } ;

void do_invader()
{
	byte i, j;

	lcd.load_custom_character(CCHAR_INV_R, Crom_inv_r);
	delay(CUST_CHAR_LOAD_DELAY);
	lcd.load_custom_character(CCHAR_INV_L, Crom_inv_l);
	delay(CUST_CHAR_LOAD_DELAY);
	lcd.load_custom_character(CCHAR_INV_S, Crom_inv_s);
	delay(CUST_CHAR_LOAD_DELAY);
	lcd.load_custom_character(CCHAR_SMILE, Crom_smiley);
	delay(CUST_CHAR_LOAD_DELAY);
	lcd.load_custom_character(CCHAR_FROWN, Crom_frowny);
	delay(CUST_CHAR_LOAD_DELAY);
	lcd.load_custom_character(CCHAR_NEUT, Crom_neut);
	delay(CUST_CHAR_LOAD_DELAY);
	lcd.load_custom_character(CCHAR_GASP, Crom_gasp);
	delay(CUST_CHAR_LOAD_DELAY);

	lcd.setCursor(FACE_ROW, FACE_COL);
	lcd.write(CCHAR_SMILE);
	
	for (i = 0; i <= FACE_COL; i++)
		{
		lcd.setCursor(INV_ROW, i);
#ifdef CURSOR_DELAY
		delay(CURSOR_DELAY);
#endif
		lcd.write(CCHAR_INV_R);
		delay(INV_DELAY);

		lcd.setCursor(INV_ROW, i);
//		lcd.left();
#ifdef CURSOR_DELAY
		delay(CURSOR_DELAY);
#endif
		lcd.write(CCHAR_INV_S);
		delay(INV_DELAY);

		lcd.setCursor(INV_ROW, i);
//		lcd.left();
#ifdef CURSOR_DELAY
		delay(CURSOR_DELAY);
#endif
		lcd.write(CCHAR_INV_L);
		delay(INV_DELAY);

			// Pick the face based on how close the alien is
		lcd.setCursor(FACE_ROW, FACE_COL);
#ifdef CURSOR_DELAY
		delay(CURSOR_DELAY);
#endif
//		j = map(i, 0, FACE_COL, 0, 3);
		j = i / 4;
		lcd.write(Faces[j]);

			// Blank the alien before moving to the next column
		lcd.setCursor(INV_ROW, i);
#ifdef CURSOR_DELAY
		delay(CURSOR_DELAY);
#endif
		lcd.write(' ');
		}

		// Make the alien "eat" the face
	lcd.setCursor(FACE_ROW, FACE_COL);
#ifdef CURSOR_DELAY
		delay(CURSOR_DELAY);
#endif
	lcd.write(CCHAR_INV_S);

}

// Clear the screen by zig-zagging back and forth across it

void Fancy_Clear(){
	int i, j;
	for (i = 0; i < DEFAULT_LCD_ROWS; i++)
		{
		if (i & 1)
			for (j = 0; j < DEFAULT_LCD_COLUMNS; j++)
				{
				lcd.setCursor(i, j);
				lcd.write(' ');
				delay(10);
				}
		  else
			for (j = (DEFAULT_LCD_COLUMNS - 1); j >= 0; j--)
				{
				lcd.setCursor(i, j);
//				lcd.write(' ');
				lcd.print((uint8_t)' ');
				delay(10);
				}
		}
	lcd.setCursor(0, 0);
}



