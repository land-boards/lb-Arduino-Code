// TouchScreen_Calibr_kbv for MCUFRIEND UNO Display Shields
// adapted by David Prentice
// for Adafruit's <TouchScreen.h> Resistive Touch Screen Library
// from Henning Karlsen's original program.  Many Thanks.

// UTouch_Calibration (C)2013-2014 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program can be used to calibrate the touchscreen
// of the display modules.
// This program requires the UTFT library and a touch
// screen module that is compatible with UTFT.
//
// It is assumed that the display module is connected to an
// appropriate shield or that you know how to change the pin
// numbers in the setup.
//
// Instructions will be given on the display.

#define TOUCH_ORIENTATION  PORTRAIT
#define USE_UTOUCH         0

#if !(USE_UTOUCH)
#define TITLE "TouchScreen.h Calibration"
#include <Adafruit_GFX.h>
#include <UTFTGLUE.h>            //we are using UTFT display methods
UTFTGLUE myGLCD(0x9341, A2, A1, A3, A4, A0);

#include <TouchScreen.h>

// MCUFRIEND UNO shield shares pins with the TFT.   Due does NOT work
#define YP A1   //A3 for ILI9320
#define YM 7    //9
#define XM A2
#define XP 6    //8  

TouchScreen myTouch(XP, YP, XM, YM, 300);
TSPoint tp;                      //Touchscreen_due branch uses Point

void readResistiveTouch(void)
{
    tp = myTouch.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);
    digitalWrite(XM, HIGH);
}

bool ISPRESSED(void)
{
    readResistiveTouch();
    return tp.z > 20 && tp.z < 1000;
}

void showpoint(void)
{
    Serial.print("\r\nx="); Serial.print(tp.x);
    Serial.print(" y="); Serial.print(tp.y);
    Serial.print(" z="); Serial.print(tp.z);
}
#else
#define TITLE "UTouch.h Calibration"
#include <SPI.h>
#include <UTFT.h>
#include <UTouch.h>
UTFT    myGLCD(ILI9486, 38, 39, 40, 41);
UTouch  myTouch( 6, 5, 4, 3, 2);

#define ISPRESSED() myTouch.dataAvailable()
extern void fail();

#endif

// ************************************
// DO NOT EDIT ANYTHING BELOW THIS LINE
// ************************************

// Declare which fonts we will be using
extern uint8_t SmallFont[];

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
    Serial.println("UTouch_Calibr_kbv");
    digitalWrite(A0, HIGH);
    pinMode(A0, OUTPUT);
    myGLCD.InitLCD(TOUCH_ORIENTATION);
    myGLCD.clrScr();
    myGLCD.setFont(SmallFont);
#if (USE_UTOUCH)
    myTouch.InitTouch(TOUCH_ORIENTATION);
#endif
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
#if (USE_UTOUCH)
        while ((ISPRESSED() == true) && (cnt < iter) && (failcount < 10000))
        {
            myTouch.calibrateRead();
            if (!((myTouch.TP_X == 65535) || (myTouch.TP_Y == 65535)))
            {
                tx += myTouch.TP_X;
                ty += myTouch.TP_Y;
                cnt++;
            }
            else
                failcount++;
        }
#else
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
#endif
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
    myGLCD.clrScr();
    myGLCD.setColor(255, 0, 0);
    myGLCD.fillRect(0, 0, dispx - 1, 13);
    myGLCD.setColor(255, 255, 255);
    myGLCD.setBackColor(255, 0, 0);
    myGLCD.drawLine(0, 14, dispx - 1, 14);
    myGLCD.print(TITLE, CENTER, 1);
    myGLCD.setBackColor(0, 0, 0);
#if (USE_UTOUCH)
    myGLCD.print("To use the new calibration", LEFT, 30);
    myGLCD.print("settings you must edit the", LEFT, 42);
    myGLCD.setColor(160, 160, 255);
    myGLCD.print("UTouchCD.h", LEFT, 54);
    myGLCD.setColor(255, 255, 255);
    myGLCD.print("file and change", 88, 54);
    myGLCD.print("the following values. The", LEFT, 66);
    myGLCD.print("values are located right", LEFT, 78);
    myGLCD.print("below the opening comment.", LEFT, 90);
    myGLCD.print("CAL_X", LEFT, 110);
    myGLCD.print("CAL_Y", LEFT, 122);
    myGLCD.print("CAL_S", LEFT, 134);
    toHex(calx);
    myGLCD.print(buf, 75, 110);
    toHex(caly);
    myGLCD.print(buf, 75, 122);
    toHex(cals);
    myGLCD.print(buf, 75, 134);
#else
    myGLCD.print("To use the new calibration", LEFT, 30);
    myGLCD.print("settings you must map the values", LEFT, 42);
    myGLCD.print("from Point p = ts.getPoint() e.g. ", LEFT, 54);
    myGLCD.print("x = map(p.x, LEFT, RT, 0, tft.width());", LEFT, 66);
    myGLCD.print("y = map(p.y, TOP, BOT, 0, tft.height());", LEFT, 78);
    myGLCD.print("swap p.x and p.y if diff ORIENTATION", LEFT, 90);
#endif
    //.kbv show human values
    showNumI("LEFT ", (calx >> 14) & 0x3FFF, 0, 186);
    showNumI("RT   ", (calx) & 0x3FFF, 100, 186);
    myGLCD.printNumF(px, 2, 200, 186);
    showNumI("TOP  ", (caly >> 14) & 0x3FFF, 0, 198);
    showNumI("BOT  ", (caly) & 0x3FFF, 100, 198);
    myGLCD.printNumF(py, 2, 200, 198);
    showNumI("WID ", (cals >> 12) & 0xFFF, 0, 210);
    showNumI("HT  ", (cals) & 0xFFF, 100, 210);
    myGLCD.print("Touch Controller is ", 0, 222);
    myGLCD.print((cals >> 31) ? "LANDSCAPE" : "PORTRAIT", 170, 222);

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
    myGLCD.print("hardware issue and can", 88, 54);
    myGLCD.print("not be corrected in", LEFT, 66);
    myGLCD.print("software.", LEFT, 78);

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
