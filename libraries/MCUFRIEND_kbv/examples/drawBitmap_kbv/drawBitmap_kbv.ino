#include "MCUFRIEND_kbv.h"
MCUFRIEND_kbv tft;

#define LOWFLASH (defined(__AVR_ATmega328P__) && defined(MCUFRIEND_KBV_H_))

#include "bitmap_mono.h"
#include "bitmap_RGB.h"

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY    0x8410
#define ORANGE  0xE880

void setup()
{
    Serial.begin(9600);
    uint16_t ID = tft.readID();

    Serial.print(F("ID = 0x"));
    Serial.println(ID, HEX);

    Serial.println(F("GFX drawBitmap() plots one mono pixel at a time"));
    Serial.println(F("it defaults to transparent plotting"));
    Serial.println(F("unless you specify foreground and background colours"));
    Serial.println(F("it can plot a monochrome bitmap from Flash or SRAM"));

    Serial.println(F(""));
    Serial.println(F("GFX drawGrayscaleBitmap() is not relevant for OLED, TFT"));
    Serial.println(F("GFX drawRGBBitmap() plots one colour pixel at a time"));
    Serial.println(F("from Flash or SRAM and with a monochrome transparent bitmask"));
    Serial.println(F(""));
    Serial.println(F("Using the hardware pushColors() methods is faster"));
    Serial.println(F("pushColors() expects uint16 array in SRAM"));
    Serial.println(F("for any runtime generated images"));
    Serial.println(F("but it expects uint8_t array of serialised bytes in Flash"));
    Serial.println(F(""));

    Serial.println(F("Colour TFTs are natively big-endian"));
    Serial.println(F("Many microcontrollers and Tools are little-endian"));
    Serial.println(F("you can use the optional argument to select big-end"));
    tft.begin(ID);
    //    invertmap(betty_1_bmp + 62, 8960);
    //    while (1);
}

// GFX drawBitmap() expects each row to be on 8-bit boundary.  i.e. pad = 7
// Mono BMP rows are on 32-bit boundary. i.e. pad = 31,  rows are in RVS order.
// FreeFont bitmaps have no padding.  i.e. pad = 0.   e.g. 5x4 bitmap is in 3 bytes
void showbgd(int x, int y, const uint8_t *bmp, int w, int h, uint16_t color, uint16_t bg, uint8_t pad = 7)
{
    int yy, xx;
    uint8_t first = 1, RVS = pad & 0x80;
    uint16_t pixel;
    pad &= 31;
    uint16_t wid = (w + pad) & ~pad;                    //bits per row
    tft.setAddrWindow(x, y, x + w - 1, y + h - 1); //
    for (yy = 0; yy < h; yy++) {
        uint32_t ofs = (RVS ? (h - yy - 1) : yy) * wid; //bit offset
        const uint8_t *p = bmp + (ofs >> 3);            //flash address
        uint8_t mask = 0x80 >> (ofs & 7);               //bit mask
        uint8_t c = pgm_read_byte(p++);
        for (xx = 0; xx < w; xx++) {
            if (mask == 0) {
                c = pgm_read_byte(p++);
                mask = 0x80;
            }
            pixel = (c & mask) ? color : bg;
            tft.pushColors(&pixel, 1, first);
            first = 0;
            mask >>= 1;
        }
    }
    tft.setAddrWindow(0, 0, tft.width() - 1, tft.height() - 1);
}

void msg_time(int x, int y, String msg, uint32_t t)
{
    t = millis() - t;
    tft.setCursor(x, y);
    tft.print(msg);
    tft.print(t);
    tft.print(F("ms"));
}

void loop(void)
{
    int x = 5, y, w = 128, h = 64;
    uint32_t t;
    const int SZ = w * h / 8;
    uint8_t sram[SZ];
    memcpy_P(sram, tractor_128x64, SZ);

    tft.fillScreen(BLACK);
    y = 0; t = millis();
    tft.drawBitmap(x, y, tractor_128x64, 128, 64, BLUE);
    msg_time(0, y + 66, F("drawBitmap() transparent flash "), t);
    y = 80; t = millis();
    tft.drawBitmap(x, y, tractor_128x64, 128, 64, RED, YELLOW);
    msg_time(0, y + 66, F("drawBitmap() background flash "), t);
    y = 160; t = millis();
    tft.fillRect(x, y, w, h, GREY);
    tft.drawBitmap(x, y, sram, 128, 64, GREEN);
    msg_time(0, y + 66, F("drawBitmap() fill bgd SRAM "), t);
    y = 240; t = millis();
    showbgd(x, y, tractor_128x64, 128, 64, MAGENTA, YELLOW);
    msg_time(0, y + 66, F("pushColors() background flash "), t);
    delay(5000);

    tft.fillScreen(BLACK);
    y = 0; t = millis();
    tft.drawRGBBitmap(x, y, marilyn_64x64, 64, 64);
    msg_time(0, y + 66, "drawRGBBitmap() flash ", t);
    y = 80; t = millis();
    tft.setAddrWindow(x, y, x + 64 - 1, y + 64 - 1);
    tft.pushColors((const uint8_t*)marilyn_64x64, 64 * 64, 1, false);
    tft.setAddrWindow(0, 0, tft.width() - 1, tft.height() - 1);
    msg_time(0, y + 66, F("pushColors() flash "), t);
    y = 160; t = millis();
    w = 64;
    tft.fillRect(x, y, w, h, GREY);
    tft.drawRGBBitmap(x, y, marilyn_64x64, magnify_64x64, 64, 64);
    msg_time(0, y + 66, F("drawRGBBitmap() with mask "), t);
    y = 240; t = millis();
    w = 64;
    tft.fillRect(x, y, w, h, GREY);
    tft.drawRGBBitmap(x, y, marilyn_64x64, magnify_inv_64x64, 64, 64);
    msg_time(0, y + 66, F("drawRGBBitmap() with mask "), t);
    delay(5000);

#if !LOWFLASH
    tft.fillScreen(BLACK);
    y = 0; t = millis();
    tft.drawRGBBitmap(x, y, tractor10_96x64, 96, 64);
    msg_time(0, y + 66, "drawRGBBitmap() flash ", t);
    y = 80; t = millis();
    tft.setAddrWindow(x, y, x + 96 - 1, y + 64 - 1);
    tft.pushColors((const uint8_t*)tractor10_96x64, 96 * 64, 1, false);
    tft.setAddrWindow(0, 0, tft.width() - 1, tft.height() - 1);
    msg_time(0, y + 66, F("pushColors() flash "), t);
    y = 160; t = millis();
    w = 96;
    tft.fillRect(x, y, w, h, GREY);
    tft.drawRGBBitmap(x, y, tractor10_96x64, camera_96x64, 96, 64);
    msg_time(0, y + 66, F("drawRGBBitmap() with mask "), t);
    y = 240; t = millis();
    w = 96;
    tft.fillRect(x, y, w, h, GREY);
    tft.drawRGBBitmap(x, y, tractor10_96x64, camera_inv_96x64, 96, 64);
    msg_time(0, y + 66, F("drawRGBBitmap() with mask "), t);
    delay(5000);
#endif
}


