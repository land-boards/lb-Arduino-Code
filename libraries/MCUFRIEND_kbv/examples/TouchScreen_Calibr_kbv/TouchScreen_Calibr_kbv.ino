// TouchScreen_Calibr_kbv for MCUFRIEND UNO Display Shields
// adapted by David Prentice
// for Adafruit's <TouchScreen.h> Resistive Touch Screen Library
// from Henning Karlsen's original program.  Many Thanks.

// UTouch_Calibration (C)2013-2014 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program can be used to calibrate the touchscreen
// of the display modules.
//
// It is assumed that the display module is connected to an
// appropriate shield or that you know how to change the pin
// numbers in the setup.
//
// Instructions will be given on the display.

#define TOUCH_ORIENTATION  PORTRAIT
#define TITLE "TouchScreen.h Calibration"

#include <Adafruit_GFX.h>
#include <UTFTGLUE.h>            //we are using UTFT display methods
UTFTGLUE myGLCD(0x9341, A2, A1, A3, A4, A0);

#include <TouchScreen.h>         //Adafruit Library

// MCUFRIEND UNO shield shares pins with the TFT.   Due does NOT work
#define YP A1   //[A1], A3 for ILI9320, A2 for ST7789V 
#define YM 7    //[ 7], 9             , 7
#define XM A2   //[A2], A2 for ILI9320, A1 for ST7789V
#define XP 6    //[ 6], 8             , 6

TouchScreen myTouch(XP, YP, XM, YM, 300);
TSPoint tp;                      //Touchscreen_due branch uses Point

void readResistiveTouch(void)
{
    tp = myTouch.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
}

bool ISPRESSED(void)
{
    // .kbv this was too sensitive !!
    // now touch has to be stable for 50ms
    int count = 0;
    bool state, oldstate;
    while (count < 10) {
        readResistiveTouch();
        state = tp.z > 20 && tp.z < 1000;
        if (state == oldstate) count++;
        else count = 0;
        oldstate = state;
        delay(5);
    }
    return oldstate;
}

void showpoint(void)
{
    Serial.print("\r\nx="); Serial.print(tp.x);
    Serial.print(" y="); Serial.print(tp.y);
    Serial.print(" z="); Serial.print(tp.z);
}

// ************************************
// DO NOT EDIT ANYTHING BELOW THIS LINE
// ************************************

// Declare which fonts we will be using
#if defined(SmallFont)         //.kbv new GLUE defines FreeSmallFont
#undef SmallFont               //.kbv lose it
#define SmallFont NULL         //.kbv use System Font
#else
extern uint8_t SmallFont[];    //.kbv
#endif

uint32_t cx, cy;
uint32_t rx[8], ry[8];
int32_t clx, crx, cty, cby;
float px, py;
int dispx, dispy, text_y_center, swapxy;
uint32_t calx, caly, cals;
char buf[13];

void setup()
{
    Serial.begin(9600);
    Serial.println(TITLE);
    digitalWrite(A0, HIGH);
    pinMode(A0, OUTPUT);
    myGLCD.InitLCD(TOUCH_ORIENTATION);
    myGLCD.clrScr();
    myGLCD.setFont(SmallFont);
    dispx = myGLCD.getDisplayXSize();
    dispy = myGLCD.getDisplayYSize();
    text_y_center = (dispy / 2) - 6;
}

void drawCrossHair(int x, int y)
{
    myGLCD.drawRect(x - 10, y - 10, x + 10, y + 10);
    myGLCD.drawLine(x - 5, y, x + 5, y);
    myGLCD.drawLine(x, y - 5, x, y + 5);
}

void readCoordinates()
{
    int iter = 5000;
    int failcount = 0;
    int cnt = 0;
    uint32_t tx = 0;
    uint32_t ty = 0;
    boolean OK = false;

    while (OK == false)
    {
        myGLCD.setColor(255, 255, 255);
        myGLCD.print("*  PRESS  *", CENTER, text_y_center);
        while (ISPRESSED() == false) {}
        myGLCD.print("*  HOLD!  *", CENTER, text_y_center);
        cnt = 0;
        iter = 400;
        do
        {
            readResistiveTouch();
            // showpoint(tp);
            if (tp.z > 20 && tp.z < 1000)
            {
                tx += tp.x;
                ty += tp.y;
                cnt++;
            }
            else
                failcount++;
        } while ((cnt < iter) && (failcount < 10000));
        if (cnt >= iter)
        {
            OK = true;
        }
        else
        {
            tx = 0;
            ty = 0;
            cnt = 0;
        }
        if (failcount >= 10000)
            fail();
    }

    cx = tx / iter;
    cy = ty / iter;
}

void calibrate(int x, int y, int i)
{
    myGLCD.setColor(255, 255, 255);
    drawCrossHair(x, y);
    myGLCD.setBackColor(255, 0, 0);
    readCoordinates();
    myGLCD.setColor(255, 255, 255);
    myGLCD.print("* RELEASE *", CENTER, text_y_center);
    myGLCD.setColor(80, 80, 80);
    drawCrossHair(x, y);
    rx[i] = cx;
    ry[i] = cy;
    Serial.print("\r\ncx="); Serial.print(cx);
    Serial.print(" cy="); Serial.print(cy);
    while (ISPRESSED() == true) {}
}

void waitForTouch()
{
    while (ISPRESSED() == true) {}
    while (ISPRESSED() == false) {}
    while (ISPRESSED() == true) {}
}

void toHex(uint32_t num)
{
    buf[0] = '0';
    buf[1] = 'x';
    buf[10] = 'U';
    buf[11] = 'L';
    buf[12] = 0;
    for (int zz = 9; zz > 1; zz--)
    {
        if ((num & 0xF) > 9)
            buf[zz] = (num & 0xF) + 55;
        else
            buf[zz] = (num & 0xF) + 48;
        num = num >> 4;
    }
}

void startup()
{
    myGLCD.setColor(255, 0, 0);
    myGLCD.fillRect(0, 0, dispx - 1, 13);
    myGLCD.setColor(255, 255, 255);
    myGLCD.setBackColor(255, 0, 0);
    myGLCD.drawLine(0, 14, dispx - 1, 14);
    myGLCD.print(TITLE, CENTER, 1);
    myGLCD.setBackColor(0, 0, 0);

    myGLCD.print("#define NUMSAMPLES 3 in Library", LEFT, 18);
    myGLCD.print("Use a stylus or something", LEFT, 30);
    myGLCD.print("similar to touch as close", LEFT, 42);
    myGLCD.print("to the center of the", LEFT, 54);
    myGLCD.print("highlighted crosshair as", LEFT, 66);
    myGLCD.print("possible. Keep as still as", LEFT, 78);
    myGLCD.print("possible and keep holding", LEFT, 90);
    myGLCD.print("until the highlight is", LEFT, 102);
    myGLCD.print("removed. Repeat for all", LEFT, 114);
    myGLCD.print("crosshairs in sequence.", LEFT, 126);
    myGLCD.print("Touch screen to continue", CENTER, 162);

    waitForTouch();
    myGLCD.clrScr();
}

void showNumI(char *msg, uint32_t val, int x, int y)
{
    myGLCD.print(msg, x, y);
    myGLCD.printNumI(val, x + 50, y);
}

void done()
{
    uint16_t TS_LEFT, TS_RT, TS_TOP, TS_BOT, TS_WID, TS_HT, TS_SWAP;
    int16_t tmp;
    myGLCD.clrScr();
    myGLCD.setColor(255, 0, 0);
    myGLCD.fillRect(0, 0, dispx - 1, 13);
    myGLCD.setColor(255, 255, 255);
    myGLCD.setBackColor(255, 0, 0);
    myGLCD.drawLine(0, 14, dispx - 1, 14);
    myGLCD.print(TITLE, CENTER, 1);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.print("To use the new calibration", LEFT, 30);
    myGLCD.print("settings you must map the values", LEFT, 42);
    myGLCD.print("from Point p = ts.getPoint() e.g. ", LEFT, 54);
    myGLCD.print("x = map(p.x, LEFT, RT, 0, tft.width());", LEFT, 66);
    myGLCD.print("y = map(p.y, TOP, BOT, 0, tft.height());", LEFT, 78);
    myGLCD.print("swap p.x and p.y if diff ORIENTATION", LEFT, 90);

    //.kbv show human values
    TS_LEFT = (calx >> 14) & 0x3FFF;
    TS_RT   = (calx >>  0) & 0x3FFF;
    TS_TOP  = (caly >> 14) & 0x3FFF;
    TS_BOT  = (caly >>  0) & 0x3FFF;
    TS_WID  = ((cals >> 12) & 0x0FFF) + 1;
    TS_HT   = ((cals >>  0) & 0x0FFF) + 1;
    TS_SWAP = (cals >> 31);
    if (TOUCH_ORIENTATION != 0) {
        myGLCD.print("Sketch is LANDSCAPE", 0, 126);
        myGLCD.printNumI(TS_WID, 150, 126);
        myGLCD.print("x", 174, 126);
        myGLCD.printNumI(TS_HT, 186, 126);
        showNumI("LEFT ", TS_LEFT, 0, 138);
        showNumI("RT   ", TS_RT, 100, 138);
        showNumI("TOP  ", TS_TOP, 0, 150);
        showNumI("BOT  ", TS_BOT, 100, 150);
        switch (TOUCH_ORIENTATION) {
            case 1:
                tmp = TS_LEFT, TS_LEFT = TS_TOP, TS_TOP = TS_RT, TS_RT = TS_BOT, TS_BOT = tmp;
                tmp = TS_WID, TS_WID = TS_HT, TS_HT = tmp;
                break;
        }
    }
    myGLCD.print("PORTRAIT CALIBRATION", 0, 174);
    myGLCD.printNumI(TS_WID, 150, 174);
    myGLCD.print("x", 174, 174);
    myGLCD.printNumI(TS_HT, 186, 174);
    showNumI("LEFT ", TS_LEFT, 0, 186);
    showNumI("RT   ", TS_RT, 100, 186);
    myGLCD.printNumF(((float)TS_RT - TS_LEFT) / TS_WID, 2, 200, 186);
    showNumI("TOP  ", TS_TOP, 0, 198);
    showNumI("BOT  ", TS_BOT, 100, 198);
    myGLCD.printNumF(((float)TS_BOT - TS_TOP) / TS_HT, 2, 200, 198);
    myGLCD.print("Touch Pin Wiring is ", 0, 222);
    myGLCD.print((cals >> 31) ? "SWAPXY" : "PORTRAIT", 170, 222);

}

void fail()
{
    myGLCD.clrScr();
    myGLCD.setColor(255, 0, 0);
    myGLCD.fillRect(0, 0, dispx - 1, 13);
    myGLCD.setColor(255, 255, 255);
    myGLCD.setBackColor(255, 0, 0);
    myGLCD.drawLine(0, 14, dispx - 1, 14);
    myGLCD.print("Touch Calibration FAILED", CENTER, 1);
    myGLCD.setBackColor(0, 0, 0);

    myGLCD.print("Unable to read the position", LEFT, 30);
    myGLCD.print("of the press. This is a", LEFT, 42);
    myGLCD.print("hardware issue and can", LEFT, 54);
    myGLCD.print("not be corrected in", LEFT, 66);
    myGLCD.print("software.", LEFT, 78);
    myGLCD.print("check XP, XM pins with a multimeter", LEFT, 102);
    myGLCD.print("check YP, YM pins with a multimeter", LEFT, 114);
    myGLCD.print("should be about 300 ohms", LEFT, 126);

    while (true) {};
}

void loop()
{
    startup();

    myGLCD.setColor(80, 80, 80);
    drawCrossHair(dispx - 11, 10);
    drawCrossHair(dispx / 2, 10);
    drawCrossHair(10, 10);
    drawCrossHair(dispx - 11, dispy / 2);
    drawCrossHair(10, dispy / 2);
    drawCrossHair(dispx - 11, dispy - 11);
    drawCrossHair(dispx / 2, dispy - 11);
    drawCrossHair(10, dispy - 11);
    myGLCD.setColor(255, 255, 255);
    myGLCD.setBackColor(255, 0, 0);
    myGLCD.print("***********", CENTER, text_y_center - 12);
    myGLCD.print("***********", CENTER, text_y_center + 12);

    calibrate(10, 10, 0);
    calibrate(10, dispy / 2, 1);
    calibrate(10, dispy - 11, 2);
    calibrate(dispx / 2, 10, 3);
    calibrate(dispx / 2, dispy - 11, 4);
    calibrate(dispx - 11, 10, 5);
    calibrate(dispx - 11, dispy / 2, 6);
    calibrate(dispx - 11, dispy - 11, 7);

    cals = (long(dispx - 1) << 12) + (dispy - 1);
    if (TOUCH_ORIENTATION == PORTRAIT) swapxy = rx[2] - rx[0];
    else swapxy = ry[2] - ry[0];
    swapxy = (swapxy < -500 || swapxy > 500);
    if ((TOUCH_ORIENTATION == PORTRAIT) ^ (swapxy != 0)) {
        clx = (rx[0] + rx[1] + rx[2]) / 3;
        crx = (rx[5] + rx[6] + rx[7]) / 3;
        cty = (ry[0] + ry[3] + ry[5]) / 3;
        cby = (ry[2] + ry[4] + ry[7]) / 3;
    } else {
        clx = (ry[0] + ry[1] + ry[2]) / 3;
        crx = (ry[5] + ry[6] + ry[7]) / 3;
        cty = (rx[0] + rx[3] + rx[5]) / 3;
        cby = (rx[2] + rx[4] + rx[7]) / 3;
    }
    px = float(crx - clx) / (dispx - 20);
    py = float(cby - cty) / (dispy - 20);
    //  px = 0;
    clx -= px * 10;
    crx += px * 10;
    cty -= py * 10;
    cby += py * 10;

    calx = (long(clx) << 14) + long(crx);
    caly = (long(cty) << 14) + long(cby);
    if (swapxy)
        cals |= (1L << 31);

    done();
    while (true) {}
}

