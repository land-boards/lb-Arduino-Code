// NOT FOR PUBLIC USE

//#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h> // Hardware-specific library
#if !defined(AVR)
#include <avr/dtostrf.h>
#endif

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <FreeSevenSegNumFontPlusPlus.h>
#include <Fonts/FreeMonoBold24pt7b.h>

const GFXfont *Fonts[] = {
    NULL,
    NULL,
    &FreeSans9pt7b,         //FONT2
    NULL,
    &FreeSans12pt7b,        //FONT4
    NULL,
    &FreeSans18pt7b,        //FONT6
    &FreeSevenSegNumFontPlusPlus, //FONT7
    &FreeSevenSegNumFontPlusPlus, //FONT8
    //    &FreeMonoBold24pt7b,    //FONT8
};

//These enumerate the text plotting alignment (reference datum point)
#define TL_DATUM 0 // Top left (default)
#define TC_DATUM 1 // Top centre
#define TR_DATUM 2 // Top right
#define ML_DATUM 3 // Middle left
#define CL_DATUM 3 // Centre left, same as above
#define MC_DATUM 4 // Middle centre
#define CC_DATUM 4 // Centre centre, same as above
#define MR_DATUM 5 // Middle right
#define CR_DATUM 5 // Centre right, same as above
#define BL_DATUM 6 // Bottom left
#define BC_DATUM 7 // Bottom centre
#define BR_DATUM 8 // Bottom right
#define L_BASELINE  9 // Left character baseline (Line the 'A' character would sit on)
#define C_BASELINE 10 // Centre character baseline
#define R_BASELINE 11 // Right character baseline

class TFT_PRINTGLUE : public MCUFRIEND_kbv
{
    public:
        TFT_PRINTGLUE() {}
        void begin(void) {
            init();
        }
        void init(void)
        {
            MCUFRIEND_kbv::reset();
            _ID = MCUFRIEND_kbv::readID();
            if (_ID == 0xD3D3) _ID = 0x9486;
            MCUFRIEND_kbv::begin(_ID);
            MCUFRIEND_kbv::setRotation(1);
            _first = true;
            _datum = TL_DATUM;
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

        void pushColors(uint16_t *data, uint16_t len, int first)
        {
            MCUFRIEND_kbv::pushColors((uint16_t*)data, len, first);
        }

        void pushColor(uint16_t color)
        {
            uint16_t c = color;
            MCUFRIEND_kbv::pushColors(&c, 1, _first);
            _first = false;
        }

        void setCursor(int16_t x, int16_t y, uint8_t idx = 255)
        {
            if (idx == 255) idx = _font; //use current font
            setTextFont(idx);
            MCUFRIEND_kbv::setCursor(x, y + _ydatum);
        }

        void setFreeFont(const GFXfont *pfont)
        {
            _font = 1;
            _ascent = 7;
            _descent = 1;
            MCUFRIEND_kbv::setFont(_pfont = pfont);
            if (pfont != NULL) {
                int16_t x = 0, y = 0, x1, y1 = 0, x2, y2 = 0;
                MCUFRIEND_kbv::setTextSize(1);
                charBounds('0', &x, &y, &x1, &y1, &x2, &y2);
                _ascent = y2 - y1;    //yAdvance
                GFXfont f;
                memcpy_P(&f, _pfont, sizeof(f));
                if (f.last >= '{' && '{' >= f.first) {
                    charBounds('{', &x, &y, &x1, &y1, &x2, &y2);
                    _descent = y2 - y1 + 1 - _ascent;   //
                }
            }
            setTextDatum(_datum);
        }

        int16_t drawNumber(long long_num, int16_t poX, int16_t poY, uint8_t idx)
        {
            char buf[12];
            ltoa(long_num, buf, 10);
            return drawString(buf, poX, poY, idx);
        }

        int16_t drawChar(char c, int16_t poX, int16_t poY, uint8_t idx)
        {
            char buf[2];
            buf[0] = c;
            buf[1] = 0;
            return drawString(buf, poX, poY, idx);
        }

        int16_t drawString(const char *string, int16_t poX, int16_t poY, uint8_t idx)
        {
            int16_t x1, y1;
            uint16_t w, h;
            setTextFont(idx);
            getTextBounds(string, 0, 50, &x1, &y1, &w, &h);   //assume no newlines
            w += x1;
            x1 = poX;
            uint16_t xpad = (_padding > w) ? _padding : w;
            switch (_datum) {
                case TC_DATUM: 
                case MC_DATUM: 
                case BC_DATUM: 
                case C_BASELINE:
                    poX -= w / 2;
                    x1 -= xpad / 2;
                    break;
                case TR_DATUM: 
                case MR_DATUM: 
                case BR_DATUM: 
                case R_BASELINE:
                    poX -= w;
                    x1 -= xpad;
                    break;
            }
            if (textcolor != textbgcolor) fillRect(x1, poY + _ydatum - _ascent, xpad, _ascent + _descent, textbgcolor);
            MCUFRIEND_kbv::setCursor(poX, poY + _ydatum);
            print(string);
            return w;
        }
        int16_t   drawCentreString(const char *string, int16_t poX, int16_t poY, uint8_t idx)
        {
            uint8_t datum = _datum;
            setTextDatum(TC_DATUM);
            uint16_t len = drawString(string, poX, poY, idx);
            setTextDatum(datum);
            return len;
        }
        int16_t   drawRightString(const char *string, int16_t poX, int16_t poY, uint8_t idx)
        {
            uint8_t datum = _datum;
            setTextDatum(TR_DATUM);
            uint16_t len = drawString(string, poX, poY, idx);
            setTextDatum(datum);
            return len;
        }
        int16_t drawFloat(float fp_num, uint8_t dec, int16_t poX, int16_t poY, int16_t idx)
        {
            char buf[12];
            dtostrf(fp_num, 0, dec, buf);
            return drawString(buf, poX, poY, idx);
        }

        void   setTextDatum(uint8_t datum) {
            _padding = 0;
            switch (_datum = datum) {
                case TL_DATUM:
                case TR_DATUM:
                case TC_DATUM:
                    _ydatum = _ascent;
                    break;
                case ML_DATUM:
                case MR_DATUM:
                case MC_DATUM:
                    _ydatum = _ascent / 2;
                    break;
                case BL_DATUM:
                case BR_DATUM:
                case BC_DATUM:
                    _ydatum = -_descent;
                    break;
                case L_BASELINE:
                case R_BASELINE:
                case C_BASELINE:
                    _ydatum = 0;
                    break;
            }
        }
        void   setTextPadding(uint16_t x_width) {
            _padding = x_width;
        }
        uint8_t fontHeight(uint8_t idx) {
            GFXfont f;
            memcpy_P(&f, _pfont, sizeof(f));
            return f.yAdvance;
        }
        void setTextFont(uint8_t idx)
        {
            if (_font == idx) return;
            _font = idx;
            setFreeFont(Fonts[_font]);
        }

    private:
        uint16_t _ID, _padding;
        uint8_t _font, _first, _datum, _ascent, _descent;
        int8_t _ydatum;
        const GFXfont *_pfont;
};
