// NOT FOR PUBLIC USE

#define HX8357_BLACK   0x0000
#define HX8357_BLUE    0x001F
#define HX8357_RED     0xF800
#define HX8357_GREEN   0x07E0
#define HX8357_CYAN    0x07FF
#define HX8357_MAGENTA 0xF81F
#define HX8357_YELLOW  0xFFE0
#define HX8357_WHITE   0xFFFF

//#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h> // Hardware-specific library

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSerifItalic12pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>

const GFXfont *Fonts[] = {
    NULL,
    NULL,
    &FreeSans9pt7b,
    NULL,
    &FreeSans12pt7b,
    NULL,
    &FreeSans18pt7b,
    &FreeSerifItalic12pt7b,
    &FreeMonoBold24pt7b,
};
#define TFT_BLACK       0x0000
#define TFT_NAVY        0x000F
#define TFT_DARKGREEN   0x03E0
#define TFT_DARKCYAN    0x03EF
#define TFT_MAROON      0x7800
#define TFT_PURPLE      0x780F
#define TFT_OLIVE       0x7BE0
#define TFT_LIGHTGREY   0xC618
#define TFT_DARKGREY    0x7BEF
#define TFT_BLUE        0x001F
#define TFT_GREEN       0x07E0
#define TFT_CYAN        0x07FF
#define TFT_RED         0xF800
#define TFT_MAGENTA     0xF81F
#define TFT_YELLOW      0xFFE0
#define TFT_WHITE       0xFFFF
#define TFT_ORANGE      0xFD20
#define TFT_GREENYELLOW 0xAFE5
#define TFT_PINK        0xF81F

#define MC_DATUM        4

class TFT_HX8357GLUE : public MCUFRIEND_kbv
{
    public:
        TFT_HX8357GLUE() {}
        void begin(void) {
		    init();
		}
		void init(void)
        {
            MCUFRIEND_kbv::reset();
			_ID = MCUFRIEND_kbv::readID();
            if (_ID == 0x00D3 || _ID == 0xD3D3)
			   _ID = 0x9486;
            MCUFRIEND_kbv::begin(_ID);
            MCUFRIEND_kbv::setRotation(1);
            _first = true;
        }
        void setWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
        {
            MCUFRIEND_kbv::setAddrWindow(x0, y0, x1, y1);
            _first = true;
        }

        void pushColors(uint8_t *data, uint16_t len)
        {
            MCUFRIEND_kbv::pushColors((uint8_t*)data, len, _first);
            _first = false;
        }

        void pushColors(uint16_t *data, uint8_t len)
        {
            MCUFRIEND_kbv::pushColors((uint16_t*)data, len, _first);
            _first = false;
        }

        void pushColor(uint16_t color)
        {
            uint16_t c = color;
			MCUFRIEND_kbv::pushColors(&c, 1, _first);
            _first = false;
        }

        void setCursor(int16_t x, int16_t y)
        {
            setCursor(x, y, _font);
        }
        
        void setCursor(int16_t x, int16_t y, uint8_t idx)
        {
            
            const GFXfont *f = Fonts[idx];
            MCUFRIEND_kbv::setFont(f);
//            MCUFRIEND_kbv::setCursor(x, y + f->glyph->height);

            MCUFRIEND_kbv::setCursor(x, y);
        }
        
        void setTextFont(uint8_t font)
        {
            _font = font;
            MCUFRIEND_kbv::setFont(Fonts[_font]);
        }

        int16_t drawNumber(long long_num, int16_t poX, int16_t poY, int16_t idx)
        {
            char buf[12];
            ltoa(long_num, buf, 10);
            return drawString(buf, poX, poY, idx);
        }

        int16_t drawChar(char c, int16_t poX, int16_t poY, int16_t idx)
        {
            char buf[2];
            buf[0] = c;
            buf[1] = 0;
            return drawString(buf, poX, poY, idx);
        }

        int16_t drawString(char *string, int16_t poX, int16_t poY, int16_t idx)
        {
            int16_t x1, y1;
            uint16_t w, h;
            setFont(Fonts[_font = idx]);
            getTextBounds(string, poX, poY, &x1, &y1, &w, &h);
            fillRect(x1, y1 + h, w, h, 0x0000);
            MCUFRIEND_kbv::setCursor(poX, poY + h);
            print(string);
            return w;
        }
        int16_t   drawCentreString(char *string, int16_t poX, int16_t poY, int16_t idx)
		{
            int16_t x1, y1;
            uint16_t w, h;
            setFont(Fonts[_font = idx]);
            getTextBounds(string, poX, poY, &x1, &y1, &w, &h);
            poX -= w/2;
			x1 -= w/2;
			fillRect(x1, y1 + h, w, h, 0x0000);
            MCUFRIEND_kbv::setCursor(poX, poY + h);
            print(string);
            return w;
//		    return drawString(string, dX, poY, idx);
		}
        void   setTextDatum(uint8_t datum) { ; }
        void   setTextPadding(uint16_t x_width) { ; }

    private:
        uint16_t _ID;
        uint8_t _font, _first;
};

