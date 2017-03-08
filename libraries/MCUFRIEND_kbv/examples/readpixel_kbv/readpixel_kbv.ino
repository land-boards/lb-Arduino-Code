#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#include <Adafruit_GFX.h> // Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

//#include <Adafruit_TFTLCD.h> // Hardware-specific library
//Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
//Adafruit_TFTLCD tft;

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void setup(void);
void loop(void);

uint16_t g_identifier;

void setup(void) {
    tft.reset();
    g_identifier = tft.readID();

    Serial.begin(9600);
    Serial.print("readID = 0x");
    Serial.println(g_identifier, HEX);
    if (g_identifier == 0xFFFF) g_identifier = 0x9341;
    if (g_identifier == 0) {
        Serial.println("Unknown ID");
        while (1);
    }

    tft.begin(g_identifier);
    tft.setRotation(0);
}

uint16_t colors[] = { 
    BLACK, BLUE 
};

void colordump(uint16_t x, uint16_t y)
{
    uint16_t pixel, pixels[32];
    char i, j, buf[20], dirty;
    uint8_t wid = (tft.width() - 9 * 6)/ (5 * 6), ht = (tft.height() / 8) - 1;
    tft.setTextColor(WHITE);
    tft.setTextSize(1);
    for (j = 0; j < ht; j++) {
        sprintf(buf, "%3d,%3d:", x, y + j);
        tft.print(buf);
        dirty = 1;
        for (i = 0; i < wid; i++) {
#if 1 && defined(MCUFRIEND_KBV_H_)        
            if (dirty) tft.readGRAM(x, y + j, pixels, wid, 1);
            dirty = 0;
            pixel = pixels[i];
#else
            pixel = tft.readPixel(x + i, y + j);
#endif
            tft.print(" ");
            if (pixel == WHITE) tft.setTextColor(GREEN);
            sprintf(buf, "%04X", pixel);
            tft.print(buf);
            tft.setTextColor(WHITE);
        }
        tft.println();
    }
}

uint16_t bgr(uint16_t color)
{
    return ((color & 0xF800) >> 11) | (color & 0x7E0) | (color & 0x1F) << 11;
}

void duffcolor(uint16_t color)
{
    uint16_t pixel, x, y;
    char done, buf[20];
    uint16_t BGR = bgr(color);
    for (done = 0, y = 0; y < 320 && !done; y++) {
        for (x= 0; x < 240; x++) {
            //            pixel = readxy(x, y);
            pixel = tft.readPixel(x, y);
            if (pixel != BGR) {
                done = 1;
                sprintf(buf, "0x%04X @ %d, %d", pixel, x, y);
                tft.println(buf);
                break;
            }
        }
    }
}

uint8_t aspect;
char *aspectname[] = {
    "PORTRAIT", "LANDSCAPE", "PORTRAIT_REV", "LANDSCAPE_REV" 
};

void loop(void) 
{
    uint16_t iter, color;
    char buf[80];
    aspect = (aspect + 1) & 3;
    tft.setRotation(aspect);
    for (iter = 0; iter < sizeof(colors) / sizeof(uint16_t); iter++) {
        color = colors[iter];
        tft.fillScreen(color);
        tft.setTextColor(WHITE);
        tft.setTextSize(1);
        tft.setCursor(0, 0);
        sprintf(buf, "ID=0x%04X Background=%04X %s",
           tft.readID(), color, aspectname[aspect]);
        tft.println(buf);
        colordump(6 * 6, 0);
        //    duffcolor(color);
        delay(5000);
    }
}







