/*
 * generate testcard similar to BMP
 */

#include <Adafruit_GFX.h>
#if defined(_GFXFONT_H_)           //are we using the new library?
#include <Fonts/FreeSans9pt7b.h>
#define ADJ_BASELINE 11            //new fonts setCursor to bottom of letter
#else
#define ADJ_BASELINE 0             //legacy setCursor to top of letter
#endif
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define RGB(r, g, b) (((r&0xF8)<<8)|((g&0xFC)<<3)|(b>>3))

#define GREY      RGB(127, 127, 127)
#define DARKGREY  RGB(64, 64, 64)
#define TURQUOISE RGB(0, 128, 128)
#define PINK      RGB(255, 128, 192)
#define OLIVE     RGB(128, 128, 0)
#define PURPLE    RGB(128, 0, 128)
#define AZURE     RGB(0, 128, 255)
#define ORANGE    RGB(255,128,64)
 
#include <stdio.h>

uint16_t ID;
uint8_t hh, mm, ss; //containers for current time

uint8_t conv2d(const char* p)
{
    uint8_t v = 0;
    if ('0' <= *p && *p <= '9') v = *p - '0';
    return 10 * v + *++p - '0';
}

void setup(void)
{
    Serial.begin(9600);
    tft.reset();
    ID = tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    //    if (ID == 0xD3D3) ID = 0x9481; // write-only shield
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
    tft.begin(ID);
    tft.setRotation(1);
    tft.fillScreen(BLACK);
#if defined(_GFXFONT_H_)
    tft.setFont(&FreeSans9pt7b);
#endif
    hh = conv2d(__TIME__);
    mm = conv2d(__TIME__ + 3);
    ss = conv2d(__TIME__ + 6);

}

void loop(void)
{
    int16_t x, y, dx, dy, radius = 108, idx;
    uint16_t w, h, len, mask;
    uint16_t colors[8] = { BLACK, WHITE, YELLOW, CYAN, GREEN, MAGENTA, RED, BLUE };
    uint16_t height, width;
    width = tft.width();
    height = tft.height();
    tft.fillRect(0, 0, 7, 3, WHITE);
    tft.fillRect(313, 0, 7, 3, WHITE);
    tft.fillRect(0, 237, 7, 3, WHITE);
    tft.fillRect(313, 237, 7, 3, WHITE);
    for (y = 0, w = 18, h = 3; y < 240; y += 13 * w + h) {
        for (x = 25; x < 320 - 18; x += 2 * w) {
            tft.fillRect(x, y, w, h, WHITE);
        }
    }
    for (x = 0, w = 7, h = 18; x < 320; x += 17 * h + w) {
        for (y = 21; y < 240 - 18; y += 2 * h) {
            tft.fillRect(x, y, w, h, WHITE);
        }
    }
    tft.fillRect(7, 3, 17 * 18, 13 * 18, GREY);
    for (x = 7, y = 0, w = 1, h = 240; x < 320; x += 18) {
        tft.fillRect(x, y, w, h, WHITE);
    }
    for (x = 0, y = 3, w = 320, h = 1; y < 240; y += 18) {
        tft.fillRect(x, y, w, h, WHITE);
    }
    tft.fillRect(26, 22, 17, 99, TURQUOISE);
    tft.fillRect(26, 120, 17, 99, PINK);
    tft.fillRect(44, 22, 17, 35, AZURE);
    tft.fillRect(44, 184, 17, 35, ORANGE);
    tft.fillRect(260, 22, 17, 35, AZURE);
    tft.fillRect(260, 184, 17, 35, ORANGE);
    tft.fillRect(278, 22, 17, 99, OLIVE);
    tft.fillRect(278, 120, 17, 99, PURPLE);

    for (dx = radius; dx > -radius; dx--) {
        w = sqrt(radius * radius - dx * dx);
        y = 120 - dx;
        dy = (y - 3) / 18;
        mask = 7;
        colors[0] = (dy == 3) ? DARKGREY : BLACK;
        switch (dy) {
            case 0:
            case 1: idx = 1; len = 0; break;
            case 2: idx = 0; len = 0; break;
            case 3: idx = 0; len = 13; mask = 1; break;
            case 4:
            case 5: idx = 2; len = 38; break;
            case 6:
            case 7:
            case 8: idx = 0; len = 0; break;
            case 9: for (idx = 2; idx < 8; idx++) {
                    //dy = 0xFF >> (7 - idx);
                    dy = (idx - 2) * 51;
                    colors[idx] = tft.color565(dy, dy, dy);
                }
                idx = 2; len = 38; break;
            case 10: idx = 1; len = 0; break;
            case 11:
            case 12: colors[2] = YELLOW; idx = 2; len = 0; break;
        }
        if (len == 0)
            tft.fillRect(160 - w, y, w * 2, 1, colors[idx]);

        else {
            if (mask == 1) idx = 1 + (w) / len;
            dy = w % len;
            for (x = 160 - w; x < 160 + w; idx++) {
                tft.fillRect(x, y, dy, 1, colors[idx & mask]);
                x += dy;
                if (x + len > 160 + w) dy = w % len;
                else dy = len;
            }
        }

    }
    for (x = 72, y = 129, dx = 5, dy = 0; dx > 0; x += 2 * dx) {
        tft.fillRect(x, y, dx, 36, WHITE);
        dy += dx * 2;
        if (dy >= 36) {
            dy = 0;
            dx--;
        }
    }
    tft.fillRect(160 - 8, 5 * 18 + 3, 17, 3 * 18, BLACK);
    for (x = 3 * 18 + 7, y = 6 * 18 + 3, w = 1, h = 18; x < 160 + 108; x += 18) {
        tft.fillRect(x, y, w, h, WHITE);
    }
    tft.fillRect(160 - 108, 120, 108 * 2, 1, WHITE);
    tft.fillRect(160, 5 * 18 + 3, 1, 3 * 18, WHITE);
    tft.fillRect(108, 2 * 18 + 3, 6 * 18, 18, WHITE);
    //    tft.fillRect(108, 10 * 18 + 3, 6 * 18, 18, BLACK);
    tft.fillRect(160 - 8, 11 * 18 + 3, 17, radius - 18*9/2, RED);
    tft.setCursor(160 - 36, 24 + ADJ_BASELINE);
    tft.setTextColor(BLACK);
    tft.setTextSize(1);
    tft.print("320x240");
    tft.setCursor(109, 43 + ADJ_BASELINE);
    tft.setTextColor(BLACK);
    tft.setTextSize(1);
    tft.print("ID=0x");
    tft.print(tft.readID(), HEX);
    tft.setTextColor(WHITE, BLACK);
    //    tft.setFont(NULL);
    //    tft.setTextSize(2);
    while (1) {
        if (++ss > 59) {
            ss = 0;
            mm++;
            if (mm > 59) {
                mm = 0;
                hh++;
                if (hh > 23) hh = 0;
            }
        }
        char buf[20];
        sprintf(buf, "%02d:%02d:%02d", hh, mm, ss);
        tft.fillRect(108, 10 * 18 + 3, 6 * 18, 18, BLACK);
        tft.setCursor(128, 187 + ADJ_BASELINE);
        tft.print(buf);
        delay(1000);
    }
}
