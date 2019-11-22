// 1970's TV game recreation by Grant Searle 2013
// Emulation of the PAL version of the AY-3-8500 that was used in many TV games from that era
//
// current web page is http://searle.hostei.com/grant/AVRPong/index.html
// If this page is not found (moved etc) then search for "Grant Searle" using a search engine such as Google
// to find my electronics page. On there will be a link to this page
//
// Top half of this file is my code to recreate the 4 paddle games that were on the game consoles.
// Second half is a cut-down and modified version of the TV Out library (http://code.google.com/p/arduino-tvout/)

// Bitmap for the edges - faster than setting individual pixels
PROGMEM const unsigned char edge[] = {
  0b10101010, 0b10101010, 0b10101010, 0b10101010
};

// Font bitmap for the 7 segment on-screen scoring display
PROGMEM const unsigned char sevenSegPAL[] = {
  0b11111100, 0b11111100, 0b11111100, 0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b11001100,
  0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b11111100, 0b11111100, 0b11111100, /* 0 */
  
  0b00001100, 0b00001100, 0b00001100, 0b00001100, 0b00001100, 0b00001100, 0b00001100, 0b00001100,
  0b00001100, 0b00001100, 0b00001100, 0b00001100, 0b00001100, 0b00001100, 0b00001100, /* 1 */

  0b11111100, 0b11111100, 0b11111100, 0b00001100, 0b00001100, 0b00001100, 0b11111100, 0b11111100,
  0b11111100, 0b11000000, 0b11000000, 0b11000000, 0b11111100, 0b11111100, 0b11111100, /* 2 */

  0b11111100, 0b11111100, 0b11111100, 0b00001100, 0b00001100, 0b00001100, 0b11111100, 0b11111100,
  0b11111100, 0b00001100, 0b00001100, 0b00001100, 0b11111100, 0b11111100, 0b11111100, /* 3 */

  0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b11111100, 0b11111100,
  0b11111100, 0b00001100, 0b00001100, 0b00001100, 0b00001100, 0b00001100, 0b00001100, /* 4 */

  0b11111100, 0b11111100, 0b11111100, 0b11000000, 0b11000000, 0b11000000, 0b11111100, 0b11111100,
  0b11111100, 0b00001100, 0b00001100, 0b00001100, 0b11111100, 0b11111100, 0b11111100, /* 5 */

  0b11111100, 0b11111100, 0b11111100, 0b11000000, 0b11000000, 0b11000000, 0b11111100, 0b11111100,
  0b11111100, 0b11001100, 0b11001100, 0b11001100, 0b11111100, 0b11111100, 0b11111100, /* 6 */

  0b11111100, 0b11111100, 0b11111100, 0b00001100, 0b00001100, 0b00001100, 0b00001100, 0b00001100,
  0b00001100, 0b00001100, 0b00001100, 0b00001100, 0b00001100, 0b00001100, 0b00001100, /* 7 */

  0b11111100, 0b11111100, 0b11111100, 0b11001100, 0b11001100, 0b11001100, 0b11111100, 0b11111100,
  0b11111100, 0b11001100, 0b11001100, 0b11001100, 0b11111100, 0b11111100, 0b11111100, /* 8 */

  0b11111100, 0b11111100, 0b11111100, 0b11001100, 0b11001100, 0b11001100, 0b11111100, 0b11111100,
  0b11111100, 0b00001100, 0b00001100, 0b00001100, 0b11111100, 0b11111100, 0b11111100, /* 9 */
};
PROGMEM const unsigned char sevenSegNTSC[] = {
  0b11111100, 0b11111100, 0b11001100, 0b11001100, 0b11001100, 0b11001100,
  0b11001100, 0b11001100, 0b11111100, 0b11111100, /* 0 */
  
  0b00001100, 0b00001100, 0b00001100, 0b00001100, 0b00001100, 0b00001100,
  0b00001100, 0b00001100, 0b00001100, 0b00001100, /* 1 */

  0b11111100, 0b11111100, 0b00001100, 0b00001100, 0b11111100, 0b11111100,
  0b11000000, 0b11000000, 0b11111100, 0b11111100, /* 2 */

  0b11111100, 0b11111100, 0b00001100, 0b00001100, 0b11111100, 0b11111100,
  0b00001100, 0b00001100, 0b11111100, 0b11111100, /* 3 */

  0b11001100, 0b11001100, 0b11001100, 0b11001100, 0b11111100, 0b11111100,
  0b00001100, 0b00001100, 0b00001100, 0b00001100, /* 4 */

  0b11111100, 0b11111100, 0b11000000, 0b11000000, 0b11111100, 0b11111100,
  0b00001100, 0b00001100, 0b11111100, 0b11111100, /* 5 */

  0b11111100, 0b11111100, 0b11000000, 0b11000000, 0b11111100, 0b11111100,
  0b11001100, 0b11001100, 0b11111100, 0b11111100, /* 6 */

  0b11111100, 0b11111100, 0b00001100, 0b00001100, 0b00001100, 0b00001100,
  0b00001100, 0b00001100, 0b00001100, 0b00001100, /* 7 */

  0b11111100, 0b11111100, 0b11001100, 0b11001100, 0b11111100, 0b11111100,
  0b11001100, 0b11001100, 0b11111100, 0b11111100, /* 8 */

  0b11111100, 0b11111100, 0b11001100, 0b11001100, 0b11111100, 0b11111100,
  0b00001100, 0b00001100, 0b11111100, 0b11111100, /* 9 */
};


int leftPaddle;
int rightPaddle;
const char LEFT_POTENTIOMETER=4;
const char RIGHT_POTENTIOMETER=5;
const char GAME_SEL=17;
//Use the following instead of a single game select button if preferred
//const int TENNIS_SEL=17;
//const int SOCCER_SEL=16;
//const int SQUASH_SEL=15;
//const int SOLO_SEL=14;
const char RESET_SW=5;
const char PADDLE_SIZE_SW=6;
const char SPEED_SW=7;
const char ANGLES_SW=8;
const char VERSION_SEL=12;
const char PAL_NTSC=4;
char ballVisible=1;
char attractMode=1;
char squashActivePlayer=1;
char ballSpeed=1;
char bigAngles=1;
char scoreLeft=0;
char scoreRight=0;
char ballX=0;
char ballY=0;
int virtualBallY=0;
char ballXInc=0;
char ballYInc=0;
char paddleHeight=14;
char chipVersion=1;

char fieldWidth=79;
char bat1X=2;
char bat2X=18;
char leftDig1X=21;
char leftDig2X=29;
char centreX=40;
char rightDig1X=43;
char rightDig2X=51;
char bat3X=58;
char bat4X=60;
char bat5X=76;
char edgeWidth=1;
char ballWidth=1;
char fieldHeight=115;
char soccerEdgeHeight=25;
char gameNumber=1; //1=Tennis, 2=Football, 3=Squash, 4=Solo
char downCount=0;
char palOrNtscMode=1; //1=PAL, 0=NTSC

uint8_t * screen;
// 5 lines of double-resolution to hold the ball
uint8_t * doubleResScreen;

void setup()  
{
  pinMode(LEFT_POTENTIOMETER, INPUT);
  pinMode(RIGHT_POTENTIOMETER, INPUT);

  pinMode(GAME_SEL, INPUT_PULLUP);
//Use the following instead of a single game select button if preferred
//  pinMode(TENNIS_SEL, INPUT_PULLUP);
//  pinMode(SOCCER_SEL, INPUT_PULLUP);
//  pinMode(SQUASH_SEL, INPUT_PULLUP);
//  pinMode(SOLO_SEL, INPUT_PULLUP);

  pinMode(RESET_SW, INPUT_PULLUP);
  pinMode(SPEED_SW, INPUT_PULLUP);
  pinMode(ANGLES_SW, INPUT_PULLUP);
  pinMode(PADDLE_SIZE_SW, INPUT_PULLUP);
  pinMode(VERSION_SEL, INPUT_PULLUP);
  pinMode(PAL_NTSC, INPUT_PULLUP);

  doubleResScreen = (unsigned char*)malloc(10 * 5 * sizeof(unsigned char));
  
  setPAL_NTSC();
  

  reset();
}

void setPAL_NTSC()
{
  if (digitalRead(PAL_NTSC)==1) // 1=PAL, 0=NTSC
  {
    fieldHeight=115;
    soccerEdgeHeight=25;
    palOrNtscMode=1;

    beginVideo(80,116);
    //Position to the same location as for the AY3-3-8500
    forceOutStart(47);
    forceLineStart(50);
  }
  else
  {
    fieldHeight=96;
    soccerEdgeHeight=21;
    palOrNtscMode=0;

    beginVideo(80,97);
    //Position to the same location as for the AY3-3-8500-1
    forceOutStart(49);
    forceLineStart(45);
  }
}

void setGame()
{
  // Ensure the selection button is pressed for several frames before accepting
  // to debounce it.
  if (digitalRead(GAME_SEL)==1)
  {
     downCount=0;
  }
  else if (downCount<10)
  {
      downCount=downCount+1;
  }
  if (downCount==4)
  {
    // Select next game
    gameNumber=gameNumber+1;
    if (gameNumber>4)
    {
      gameNumber=1;
    }
  }
//Use the following instead of a single game select button if preferred
/*
  if (digitalRead(TENNIS_SEL)==0)
  {
    gameNumber=1;
  }
  if (digitalRead(SOCCER_SEL)==0)
  {
    gameNumber=2;
  }
  if (digitalRead(SQUASH_SEL)==0)
  {
    gameNumber=3;
  }
  if (digitalRead(SOLO_SEL)==0)
  {
    gameNumber=4;
  }
*/
}

void reset()
{
  scoreLeft=0;
  scoreRight=0;

  // Position ball off field so that it appears at the correct entry point
  // a short while after reset
  ballX=0;
  virtualBallY=-18;

  // Reset ball speed/angle
  ballXInc=ballSpeed;
  ballYInc=ballSpeed;
  ballVisible=1;
  
  attractMode=0;
  squashActivePlayer=1;
}

void drawBoundary()
{
  // Top and bottom dotted boundary
  int i1;
  for (i1=0;i1<fieldWidth-8;i1=i1+8)
  {
     bitmap(i1,0,edge,0,8,1); 
     bitmap(i1,fieldHeight-1,edge,0,8,1); 
  }
  for (int i2=i1-8;i2<fieldWidth;i2=i2+2)
  {
    setPixel(i2,0,1);
    setPixel(i2,fieldHeight-1,1);
  }

  //Set bytes directly as it is much quicker than "setPixel"  

  // Goals for Soccer
  if (gameNumber==2)
  {
    if (chipVersion==2)
    {
      for (int i=0;i<(soccerEdgeHeight*10);i=i+10)
      {
          screen[i] |= 0b11000000;
          screen[i+9] |=0b11000000;
      }
      for (int i=((fieldHeight-soccerEdgeHeight)*10);i<(fieldHeight*10);i=i+10)
      {
          screen[i] |= 0b11000000;
          screen[i+9] |=0b11000000;
      }
    }
    else
    {
      for (int i=0;i<(soccerEdgeHeight*10);i=i+10)
      {
          screen[i] |= 0b10000000;
          screen[i+9] |=0b00000010;
      }
      for (int i=((fieldHeight-soccerEdgeHeight)*10);i<(fieldHeight*10);i=i+10)
      {
          screen[i] |= 0b10000000;
          screen[i+9] |=0b00000010;
      }
    }
  }
  
  //Left wall for Squash or Solo
  if (gameNumber==3 || gameNumber==4)
  {
    if (chipVersion==2)
    {
      for (int i=0;i<(fieldHeight*10);i=i+10)
      {
          screen[i] |= 0b11000000;
      }
    }
    else
    {
      for (int i=0;i<(fieldHeight*10);i=i+10)
      {
          screen[i] |= 0b10000000;
      }
    }
  }
  
  //Centre line for Tennis or Soccer
  if (gameNumber==1 || gameNumber==2)
  {
    if (palOrNtscMode==1) // PAL - Dotted centre
    {
      if (chipVersion==2)
      {
        int byteNum=24;
        for (int i=4;i<fieldHeight-2;i=i+4)
        {
          screen[byteNum]=0b00001000;
          screen[byteNum+10]=0b00001000;
          byteNum=byteNum+40;
        }
      }
      else
      {
        int byteNum=25;
        for (int i=4;i<fieldHeight-2;i=i+4)
        {
          screen[byteNum]=0b10000000;
          screen[byteNum+10]=0b10000000;
          byteNum=byteNum+40;
        }
      }
    }
    else // NTSC - solid centre
    {
      if (chipVersion==2)
      {
        int byteNum=14;
        for (int i=2;i<fieldHeight;i++)
        {
          screen[byteNum]=0b00001000;
          byteNum=byteNum+10;
        }
      }
      else
      {
        int byteNum=15;
        for (int i=2;i<fieldHeight;i++)
        {
          screen[byteNum]=0b10000000;
          byteNum=byteNum+10;
        }
      }
    }
  }
}

void drawScores()
{
  // Only draw first digit if score is >9
  if (scoreLeft>9)
  {
    drawDigit(leftDig1X,3,1);
    drawDigit(leftDig2X,3,scoreLeft-10);
  }
  else
  {
    drawDigit(leftDig2X,3,scoreLeft);
  }

  if (gameNumber!=4) // not solo
  {
    // Only draw first digit if score is >9
    if (scoreRight>9)
    {
      drawDigit(rightDig1X,3,1);
      drawDigit(rightDig2X,3,scoreRight-10);
    }
    else
    {
      drawDigit(rightDig2X,3,scoreRight);
    }
  }
}

void drawDigit(int x, int y, int v)
{
  if (palOrNtscMode==1)
  {
     bitmap(x,y,sevenSegPAL,v*15,8,15);
  }
  else
  {
     bitmap(x,y,sevenSegNTSC,v*10,8,10);
  }
}
// Draw the ball on a virtual screen area 80 pixels across by 5 pixels high.
// This area is then displayed (double vertical resolution) instead of the normal background
// for those 5 lines.
static void inline setBallPixel(uint8_t x, uint8_t y) 
{  
    if (x<0 || x>79 || y<0 || y>4)
    {
        return;
    } 
    doubleResScreen[(x/8) + (y*10)] |= 0x80 >> (x&7);
}

void drawBall()
{
  // Copy the screen to the high res screen
  for (int x=0;x<10;x++)
  {
    // Put the appropriate 3 lines that are being overlayed into
    // the double-res buffer
    if ((virtualBallY % 2)==0)
    {
      doubleResScreen[x]=screen[x+(10*(ballY))];
      doubleResScreen[x+10]=screen[x+(10*(ballY))];
      doubleResScreen[x+20]=screen[x+(10*(ballY+1))];
      doubleResScreen[x+30]=screen[x+(10*(ballY+1))];
      doubleResScreen[x+40]=screen[x+(10*(ballY+2))];

    }
    else
    {
      doubleResScreen[x]=screen[x+(10*(ballY))];
      doubleResScreen[x+10]=screen[x+(10*(ballY+1))];
      doubleResScreen[x+20]=screen[x+(10*(ballY+1))];
      doubleResScreen[x+30]=screen[x+(10*(ballY+2))];
      doubleResScreen[x+40]=screen[x+(10*(ballY+2))];
    }
  }
  // Mask off the sides to produce a dotted boundary
  // (same as done in the display render routine)

  if (chipVersion==2)
  {
    if ((virtualBallY % 2)==0)
    {
      for (int i=10;i<=30;i=i+20)
      {
        if (gameNumber>1) doubleResScreen[i] &= 0b00111111;
        if (gameNumber==2) doubleResScreen[i+9] =0;
      }
    }
    else
    {
      for (int i=0;i<=40;i=i+20)
      {
        if (gameNumber>1) doubleResScreen[i] &= 0b00111111;
        if (gameNumber==2) doubleResScreen[i+9] =0;
      }
    }
  }
  else
  {
    if ((virtualBallY % 2)==0)
    {
      for (int i=10;i<=30;i=i+20)
      {
        if (gameNumber>1) doubleResScreen[i] &= 0b01111111;
        if (gameNumber==2) doubleResScreen[i+9] &=0b11111101;
      }
    }
    else
    {
      for (int i=0;i<=40;i=i+20)
      {
        if (gameNumber>1) doubleResScreen[i] &= 0b01111111;
        if (gameNumber==2) doubleResScreen[i+9] &=0b11111101;
      }
    }
  }

// Draw the ball on the double-resolution screen
// This will then replace a strip across the screen at the ball
// position, ensuring a smooth ball travel
  setBallPixel(ballX,0);
  setBallPixel(ballX,1);
  setBallPixel(ballX,2);

  // Newer version of the AY-3-8500 had a wider and taller ball
  if (chipVersion==2)
  {
    setBallPixel(ballX,3);
    setBallPixel(ballX,4);
    setBallPixel(ballX+1,0);
    setBallPixel(ballX+1,1);
    setBallPixel(ballX+1,2);
    setBallPixel(ballX+1,3);
    setBallPixel(ballX+1,4);
  }
}

void drawPaddle(int paddleNum, int val)
{
  int paddleX=0;
  if (paddleNum==1) // Left player left paddle
  {
    paddleX=bat1X;
  }
  if (paddleNum==5) // Right player right paddle
  {
    paddleX=bat5X;
  }
  if (paddleNum==4) // Left player mid/squash paddle
  {
    paddleX=bat4X;
  }
  if (paddleNum==2) // Right player mid paddle
  {
    paddleX=bat2X;
  }
  if (paddleNum==3) // Right player squash paddle
  {
    paddleX=bat3X;
  }
  int y1=val;
  int y2=val+paddleHeight;
  if (y1<1)
  {
    y1=1;
  }
  if (y2>fieldHeight-2)
  {
    y2=fieldHeight-2;
  }

  drawLine(paddleX,y1,paddleX,y2,1);

  // Intercept ball
  if (ballVisible==1 && attractMode==0)
  {
    if ((ballXInc<0 && (ballX==paddleX || ballX == (paddleX+1)))
     || (ballXInc>0 && (ballX==(paddleX-ballWidth) || ballX == (paddleX-ballWidth+1))))
    {
       if (ballY>=val-1 && ballY<=val+paddleHeight)
      {
        beep(1000,32);
         if (gameNumber==3) //Squash
         {
            if (ballXInc<0 || (squashActivePlayer==1 && paddleNum!=4) || (squashActivePlayer==2 && paddleNum!=3))
            {
               // Either the bat is not active or it is passing through the left bat
               // so don't intercept on this game
               return;
            }
            if (ballXInc>0 && (squashActivePlayer==1 && paddleNum==4))
             {
                ballXInc=-ballXInc;
                squashActivePlayer=2;
             } 
            if (ballXInc>0 && (squashActivePlayer==2 && paddleNum==3))
             {
                ballXInc=-ballXInc;
                squashActivePlayer=1;
             } 
         }
         else if (gameNumber==4) //Solo
         {
            if (ballXInc>0)
             {
                ballXInc=-ballXInc;
                squashActivePlayer=2;
             } 
         }
         else
         {
           if (ballXInc<0 && (paddleNum==1 || paddleNum==4))
             {
                ballXInc=-ballXInc;
             } 
            if (ballXInc>0 && (paddleNum==2 || paddleNum==3 || paddleNum==5))
             {
                ballXInc=-ballXInc;
             }
         }
         if (bigAngles==1 && ballY<val+paddleHeight/4)
         {
           if (ballSpeed==1)
           {
              ballYInc=-3;
           }
           else
           {
               ballYInc=-5;
           }
         }
         else if (ballY<val+paddleHeight/2)
         {
             ballYInc=-ballSpeed;
         }
         else if (bigAngles==0 || ballY<val+paddleHeight*3/4)
         {
             ballYInc=ballSpeed;
         }
         else
         {
           if (ballSpeed==1)
           {
              ballYInc=3;
           }
           else
           {
               ballYInc=5;
           }
         }
      }
    }
  }
}

void configureSelectedChipVersion()
{
  // The two versions of the AY-3-8500 have different widths, so set the positions
  // depending on the version selected.
  if (digitalRead(VERSION_SEL)==1)
  {
    chipVersion=2;
    fieldWidth=74;
    bat1X=3;
    bat2X=19;
    bat3X=52;
    bat4X=54;
    bat5X=70;
    leftDig1X=19;
    leftDig2X=27;
    centreX=36;
    rightDig1X=37;
    rightDig2X=45;
    edgeWidth=2;
    ballWidth=2;
  }
  else
  {
    chipVersion=1;
    fieldWidth=79;
    bat1X=2;
    bat2X=18;
    bat3X=58;
    bat4X=60;
    bat5X=76;
    leftDig1X=21;
    leftDig2X=29;
    centreX=40;
    rightDig1X=43;
    rightDig2X=51;
    edgeWidth=1;
    ballWidth=1;
  }  
}

void setGameOptionsFromSwitches()
{
  if (digitalRead(SPEED_SW)==1)
  {
    // Switch to higher speed if not already set
    if (ballSpeed==1)
    {
      ballXInc=ballXInc*2;
      if (ballYInc==-1 || ballYInc==1)
      {
          ballYInc=ballYInc*2; // from 1 line to 2 lines per step
      }
      else if (ballYInc<-1)
      {
          ballYInc=-5; // from 3 lines to 5 lines per step
      }
      else if (ballYInc>1)
      {
          ballYInc=5; // from 3 lines to 5 lines per step
      }
        
      ballSpeed=2;
    }   
  }
  else
  {
    // Switch to lower speed if not already set
    if (ballSpeed==2)
    {
      ballXInc=ballXInc/2;
      if (ballYInc==-2 || ballYInc==2)
      {
          ballYInc=ballYInc/2; // from 2 lines down to 1 line per step
      }
      else if (ballYInc<-1)
      {
          ballYInc=-3; // from 5 lines down to 3 lines per step
      }
      else if (ballYInc>1)
      {
          ballYInc=3; // from 5 lines down to 3 lines per step
      }
        
      ballSpeed=1;
    }   
  }
  
  if (digitalRead(ANGLES_SW)==1)
  {
    bigAngles=1;   
  }
  else
  {
    bigAngles=0;   
  }
  if (digitalRead(PADDLE_SIZE_SW)==1)
  {
    paddleHeight=14;
  }
  else
  {
    paddleHeight=7;
  }
}

void drawPaddles()
{
  leftPaddle=analogRead(LEFT_POTENTIOMETER);
  rightPaddle=analogRead(RIGHT_POTENTIOMETER);
  leftPaddle=map(leftPaddle,0,1023,2-paddleHeight,fieldHeight-2);
  rightPaddle=map(rightPaddle,0,1023,2-paddleHeight,fieldHeight-2);

  if (gameNumber==1 || gameNumber==2) // Tennis or Football
  {
    drawPaddle(1,leftPaddle);
    drawPaddle(5,rightPaddle);
  }
  if (gameNumber==2) // Football
  {
    drawPaddle(4,leftPaddle);
    drawPaddle(2,rightPaddle);
  }
  if (gameNumber==3) // Squash
  {
    drawPaddle(4,leftPaddle);
    drawPaddle(3,rightPaddle);
  }
  if (gameNumber==4) // Solo
  {
    drawPaddle(3,rightPaddle);
  }
}

void loop()  
{
  // Synchronise, so that this runs once per frame
  delay_frame(1);

  configureSelectedChipVersion();

  clearScreen();  

  setGame();

  drawBoundary();

  drawScores();

  setGameOptionsFromSwitches();
  
  drawPaddles();

  // If reset button is pressed then don't proceed any further
  if (digitalRead(RESET_SW)==0)
  {
    reset();
    return;
  }
  
  // Update the ball position
  ballX=ballX+ballXInc;
  virtualBallY=virtualBallY+ballYInc;
  ballY=virtualBallY/2;
  if (virtualBallY<0)
  {
    ballY=(virtualBallY-1)/2;
  }
  
  // Check if a boundary has been hit
  if (gameNumber==2 && ballVisible==1) // Football - left/right partial wall
  {
    if (ballY<soccerEdgeHeight+2 || ballY>fieldHeight-soccerEdgeHeight-1)
    {
      if (ballXInc<0 && ballX<=edgeWidth && ballX>=0)
      {
        ballXInc=-ballXInc;
        beep(500,32);
      }
      if (ballXInc>0 && ballX >= fieldWidth-ballWidth-edgeWidth && ballX < fieldWidth)
      {
        ballXInc=-ballXInc;
        beep(500,32);
      }
    }
  }

  if (gameNumber>=3 && ballVisible==1) // Squash or Solo - left full wall
  {
      if (ballXInc<0 && ballX<=edgeWidth)
      {
        ballXInc=-ballXInc;
        beep(500,32);
      }
  }

  // Check if the ball has exited the left or right side of the field, and update the score as required
  if (ballXInc>0 && ballX >= fieldWidth)
  {
    ballXInc=-ballXInc;
    if (ballVisible==0)
    {
      ballVisible=1;
    }
    else
    {
      beep(2000,32);
      if (attractMode==0)
      {
        if (gameNumber==3)
        {
         if (squashActivePlayer==1)
        {
          scoreRight=scoreRight+1;
        }
        else
        {
          scoreLeft=scoreLeft+1;
        }
       }
       else
       {
        scoreLeft=scoreLeft+1;
       }
        if (scoreLeft>=15 || scoreRight>=15)
        {
          attractMode=1;
        }
      }
      ballX=fieldWidth*0.7;
      ballVisible=0;
    }
  }

  if (ballXInc<0 && ballX <= -ballWidth)
  {
    ballXInc=-ballXInc;
    if (ballVisible==0)
    {
      ballVisible=1;
    }
    else
    {
      beep(2000,32);

      if (attractMode==0)
      {
        scoreRight=scoreRight+1;
        if (scoreRight>=15)
        {
          attractMode=1;
        }
      }
      ballX=fieldWidth*0.3;
      ballVisible=0;
    }
  }
  
  // Bounce the ball off the top or bottom edge if needed
  if ((ballYInc<0 && ballY<2) || (ballYInc>0 && ballY > fieldHeight-4))
  {
    ballYInc=-ballYInc;
    beep(500,32);
  }
  
  // Draw the ball if visible
  if (ballVisible==1)
  {
     drawBall();
  }
}
// END OF GAME CODE

//###################################################################################################

// MODIFIED AND REDUCED TV OUT LIBRARY CODE. MODIFICATIONS BY GRANT SEARLE
// Go to http://code.google.com/p/arduino-tvout/ to see the documentation and original code

/*
 Copyright (c) 2010 Myles Metzer

 Permission is hereby granted, free of charge, to any person
 obtaining a copy of this software and associated documentation
 files (the "Software"), to deal in the Software without
 restriction, including without limitation the rights to use,
 copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following
 conditions:

 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdint.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <stdlib.h>

//video
#define PORT_VID	PORTB
#define	DDR_VID		DDRB
#define	VID_PIN		2
//sync
#define PORT_SYNC	PORTB
#define DDR_SYNC	DDRB
#define SYNC_PIN	1
//sound
#define PORT_SND	PORTB
#define DDR_SND		DDRB
#define	SND_PIN		3

//automatic BST/BLD/ANDI macro definition
#if VID_PIN == 0
#define BLD_HWS		"bld	r16,0\n\t"
#define BST_HWS		"bst	r16,0\n\t"
#define ANDI_HWS	"andi	r16,0xFE\n"
#elif VID_PIN == 1
#define BLD_HWS		"bld	r16,1\n\t"
#define BST_HWS		"bst	r16,1\n\t"
#define ANDI_HWS	"andi	r16,0xFD\n"
#elif VID_PIN == 2
#define BLD_HWS		"bld	r16,2\n\t"
#define BST_HWS		"bst	r16,2\n\t"
#define ANDI_HWS	"andi	r16,0xFB\n"
#elif VID_PIN == 3
#define BLD_HWS		"bld	r16,3\n\t"
#define BST_HWS		"bst	r16,3\n\t"
#define ANDI_HWS	"andi	r16,0xF7\n"
#elif VID_PIN == 4
#define BLD_HWS		"bld	r16,4\n\t"
#define BST_HWS		"bst	r16,4\n\t"
#define ANDI_HWS	"andi	r16,0xEF\n"
#elif VID_PIN == 5
#define BLD_HWS		"bld	r16,5\n\t"
#define BST_HWS		"bst	r16,5\n\t"
#define ANDI_HWS	"andi	r16,0xDF\n"
#elif VID_PIN == 6
#define BLD_HWS		"bld	r16,6\n\t"
#define BST_HWS		"bst	r16,6\n\t"
#define ANDI_HWS	"andi	r16,0xBF\n"
#elif VID_PIN == 7
#define BLD_HWS		"bld	r16,7\n\t"
#define BST_HWS		"bst	r16,7\n\t"
#define ANDI_HWS	"andi	r16,0x7F\n"
#endif

#define _CYCLES_PER_US			(F_CPU / 1000000)

#define _TIME_HORZ_SYNC			4.7
#define _TIME_VERT_SYNC			58.85
#define _TIME_ACTIVE			46
#define _CYCLES_VERT_SYNC		((_TIME_VERT_SYNC * _CYCLES_PER_US) - 1)
#define _CYCLES_HORZ_SYNC		((_TIME_HORZ_SYNC * _CYCLES_PER_US) - 1)

#define _NTSC_TIME_SCANLINE		63.55
#define _NTSC_TIME_OUTPUT_START		12
#define _NTSC_LINE_FRAME		262
#define _NTSC_LINE_START_VSYNC		0
#define _NTSC_LINE_STOP_VSYNC		3
#define _NTSC_LINE_DISPLAY		216
#define _NTSC_LINE_MID			((_NTSC_LINE_FRAME - _NTSC_LINE_DISPLAY)/2 + _NTSC_LINE_DISPLAY/2)
#define _NTSC_CYCLES_SCANLINE		((_NTSC_TIME_SCANLINE * _CYCLES_PER_US) - 1)
#define _NTSC_CYCLES_OUTPUT_START	((_NTSC_TIME_OUTPUT_START * _CYCLES_PER_US) - 1)

#define _PAL_TIME_SCANLINE		64
#define _PAL_TIME_OUTPUT_START		12.5
#define _PAL_LINE_FRAME			312
#define _PAL_LINE_START_VSYNC		0
#define _PAL_LINE_STOP_VSYNC		3
#define _PAL_LINE_DISPLAY		260
#define _PAL_LINE_MID			((_PAL_LINE_FRAME - _PAL_LINE_DISPLAY)/2 + _PAL_LINE_DISPLAY/2)
#define _PAL_CYCLES_SCANLINE		((_PAL_TIME_SCANLINE * _CYCLES_PER_US) - 1)
#define _PAL_CYCLES_OUTPUT_START	((_PAL_TIME_OUTPUT_START * _CYCLES_PER_US) - 1)

#define WHITE				1
#define BLACK				0

volatile int scanLine;
volatile unsigned long frames;
unsigned char startRenderLine;
int linesPerFrame;
volatile uint8_t vertRes;
volatile uint8_t horizRes;
uint8_t outputDelay;
char linesPerVertPixel;
char remainingLinesPerVertPixel;
char vsyncEnd;
//uint8_t * screen;
volatile long remainingToneVsyncs;
int renderStartOffset;
void (*lineHandler)() = &empty;

char beginVideo(uint8_t x, uint8_t y) {
	// check if x is divisable by 8
	if ( !(x & 0xF8))
		return 1;
	x = x/8;
		
	screen = (unsigned char*)malloc(x * y * sizeof(unsigned char));
	if (screen == NULL)
		return 4;
		
	renderSetup(x,y,screen);
	clearScreen();
	return 0;
}

void endVideo() {
	TIMSK1 = 0;
	free(screen);
}

void clearScreen() {
	for (int i = 0; i < (horizRes)*vertRes; i++)
		screen[i] = 0;
}

void delay_frame(unsigned int x) {
	int stopLine = (int)(startRenderLine + (vertRes*linesPerVertPixel))+1;
	while (x) {
		while (scanLine != stopLine);
		while (scanLine == stopLine);
		x--;
	}
}

void forceOutStart(uint8_t time) {
	delay_frame(1);
	outputDelay = ((time * _CYCLES_PER_US) - 1);
}

void forceLineStart(uint8_t line) {
	delay_frame(1);
	startRenderLine = line;
}

static void inline sp(uint8_t x, uint8_t y, char c) {
  if (c==1)
    screen[(x/8) + (y*horizRes)] |= 0x80 >> (x&7);
  else if (c==0)
    screen[(x/8) + (y*horizRes)] &= ~0x80 >> (x&7);
  else
    screen[(x/8) + (y*horizRes)] ^= 0x80 >> (x&7);
}

void setPixel(uint8_t x, uint8_t y, char c) {
	if (x<0 || y<0 || x >= horizRes*8 || y >= vertRes)
		return;
	sp(x,y,c);
}

void drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, char c) {
	if (x0<0 || y0<0 || x1<0 || x1<0 || x0 > horizRes*8 || y0 > vertRes || x1 > horizRes*8 || y1 > vertRes)
		return;
	if (x0 == x1)
		drawColumn(x0,y0,y1,c);
	else if (y0 == y1)
		drawRow(y0,x0,x1,c);
	else {
		int e;
		signed int dx,dy,j, temp;
		signed char s1,s2, xchange;
		signed int x,y;

		x = x0;
		y = y0;
	
		//take absolute value
		if (x1 < x0) {
			dx = x0 - x1;
			s1 = -1;
		}
		else if (x1 == x0) {
			dx = 0;
			s1 = 0;
		}
		else {
			dx = x1 - x0;
			s1 = 1;
		}

		if (y1 < y0) {
			dy = y0 - y1;
			s2 = -1;
		}
		else if (y1 == y0) {
			dy = 0;
			s2 = 0;
		}
		else {
			dy = y1 - y0;
			s2 = 1;
		}

		xchange = 0;   

		if (dy>dx) {
			temp = dx;
			dx = dy;
			dy = temp;
			xchange = 1;
		} 

		e = ((int)dy<<1) - dx;  
	 
		for (j=0; j<=dx; j++) {
			sp(x,y,c);
		 
			if (e>=0) {
				if (xchange==1) x = x + s1;
				else y = y + s2;
				e = e - ((int)dx<<1);
			}
			if (xchange==1)
				y = y + s2;
			else
				x = x + s1;
			e = e + ((int)dy<<1);
		}
	}
}

void drawRow(uint8_t line, uint16_t x0, uint16_t x1, uint8_t c) {
	uint8_t lbit, rbit;
	
	if (x0 == x1)
		setPixel(x0,line,c);
	else {
		if (x0 > x1) {
			lbit = x0;
			x0 = x1;
			x1 = lbit;
		}
		lbit = 0xff >> (x0&7);
		x0 = x0/8 + horizRes*line;
		rbit = ~(0xff >> (x1&7));
		x1 = x1/8 + horizRes*line;
		if (x0 == x1) {
			lbit = lbit & rbit;
			rbit = 0;
		}
		if (c == WHITE) {
			screen[x0++] |= lbit;
			while (x0 < x1)
				screen[x0++] = 0xff;
			screen[x0] |= rbit;
		}
		else if (c == BLACK) {
			screen[x0++] &= ~lbit;
			while (x0 < x1)
				screen[x0++] = 0;
			screen[x0] &= ~rbit;
		}
	}
}

void drawColumn(uint8_t row, uint16_t y0, uint16_t y1, uint8_t c) {
	unsigned char bit;
	int byte;
	
	if (y0 == y1)
		setPixel(row,y0,c);
	else {
		if (y1 < y0) {
			bit = y0;
			y0 = y1;
			y1 = bit;
		}
		bit = 0x80 >> (row&7);
		byte = row/8 + y0*horizRes;
		if (c == WHITE) {
			while ( y0 <= y1) {
				screen[byte] |= bit;
				byte += horizRes;
				y0++;
			}
		}
		else if (c == BLACK) {
			while ( y0 <= y1) {
				screen[byte] &= ~bit;
				byte += horizRes;
				y0++;
			}
		}
	}
}

void bitmap(uint8_t x, uint8_t y, const unsigned char * bmp,
				   uint16_t i, uint8_t width, uint8_t lines) {
	uint8_t temp, lshift, rshift, save, xtra;
	uint16_t si = 0;
	
	rshift = x&7;
	lshift = 8-rshift;
	if (width == 0) {
		width = pgm_read_byte((uint32_t)(bmp) + i);
		i++;
	}
	if (lines == 0) {
		lines = pgm_read_byte((uint32_t)(bmp) + i);
		i++;
	}
		
	if (width&7) {
		xtra = width&7;
		width = width/8;
		width++;
	}
	else {
		xtra = 8;
		width = width/8;
	}
	
	for (uint8_t l = 0; l < lines; l++) {
		si = (y + l)*horizRes + x/8;
		if (width == 1)
			temp = 0xff >> rshift + xtra;
		else
			temp = 0;
		save = screen[si];
		screen[si] &= ((0xff << lshift) | temp);
		temp = pgm_read_byte((uint32_t)(bmp) + i++);
		screen[si++] |= temp >> rshift;
		for ( uint16_t b = i + width-1; i < b; i++) {
			save = screen[si];
			screen[si] = temp << lshift;
			temp = pgm_read_byte((uint32_t)(bmp) + i);
			screen[si++] |= temp >> rshift;
		}
		if (rshift + xtra < 8)
			screen[si-1] |= (save & (0xff >> rshift + xtra));
		if (rshift + xtra - 8 > 0)
			screen[si] &= (0xff >> rshift + xtra - 8);
		screen[si] |= temp << lshift;
	}
}

void beep(unsigned int frequency, unsigned long duration_ms) {
	if (frequency == 0)
		return;

#define TIMER 2
	//this is init code
	TCCR2A = 0;
	TCCR2B = 0;
	TCCR2A |= _BV(WGM21);
	TCCR2B |= _BV(CS20);
	//end init code

	//most of this is taken from Tone.cpp from Arduino
	uint8_t prescalerbits = 0b1;
	uint32_t ocr = 0;
  

    DDR_SND |= _BV(SND_PIN); //set pb3 (digital pin 11) to output

    //we are using an 8 bit timer, scan through prescalars to find the best fit
	ocr = F_CPU / frequency / 2 - 1;
  prescalerbits = 0b1;  // ck/1: same for both timers
  if (ocr > 255) {
    ocr = F_CPU / frequency / 2 / 8 - 1;
    prescalerbits = 0b010;  // ck/8: same for both timers

    if (ocr > 255) {
      ocr = F_CPU / frequency / 2 / 32 - 1;
      prescalerbits = 0b011;
    }

    if (ocr > 255) {
      ocr = F_CPU / frequency / 2 / 64 - 1;
      prescalerbits = TIMER == 0 ? 0b011 : 0b100;
      if (ocr > 255) {
        ocr = F_CPU / frequency / 2 / 128 - 1;
        prescalerbits = 0b101;
      }

      if (ocr > 255) {
        ocr = F_CPU / frequency / 2 / 256 - 1;
        prescalerbits = TIMER == 0 ? 0b100 : 0b110;
        if (ocr > 255) {
          // can't do any better than /1024
          ocr = F_CPU / frequency / 2 / 1024 - 1;
          prescalerbits = TIMER == 0 ? 0b101 : 0b111;
        }
      }
    }
  }
  TCCR2B = prescalerbits;

	if (duration_ms > 0)
		remainingToneVsyncs = duration_ms*0/1000; //60 here represents the framerate
	else
		remainingToneVsyncs = -1;
 
  // Set the OCR for the given timer,
  OCR2A = ocr;
  //set it to toggle the pin by itself
  TCCR2A &= ~(_BV(COM2A1)); //set COM2A1 to 0
  TCCR2A |= _BV(COM2A0);
}

void renderSetup(uint8_t x, uint8_t y, uint8_t *scrnptr) {
	screen = scrnptr;
	horizRes = x;
	vertRes = y;
	frames = 0;
	
  if (palOrNtscMode==1)
  {
    linesPerVertPixel = _PAL_LINE_DISPLAY/vertRes;
    startRenderLine = _PAL_LINE_MID - ((vertRes * linesPerVertPixel)/2);
    outputDelay = _PAL_CYCLES_OUTPUT_START;
    vsyncEnd = _PAL_LINE_STOP_VSYNC;
    linesPerFrame = _PAL_LINE_FRAME;
    ICR1 = _PAL_CYCLES_SCANLINE;
  }
  else
  {
  linesPerVertPixel = _NTSC_LINE_DISPLAY/vertRes;
    startRenderLine = _NTSC_LINE_MID - ((vertRes * linesPerVertPixel)/2);
    outputDelay = _NTSC_CYCLES_OUTPUT_START;
    vsyncEnd = _NTSC_LINE_STOP_VSYNC;
    linesPerFrame = _NTSC_LINE_FRAME;
    ICR1 = _NTSC_CYCLES_SCANLINE;
  }
	remainingLinesPerVertPixel = linesPerVertPixel;
	
	DDR_VID |= _BV(VID_PIN);
	DDR_SYNC |= _BV(SYNC_PIN);
	PORT_VID &= ~_BV(VID_PIN);
	PORT_SYNC |= _BV(SYNC_PIN);
	DDR_SND |= _BV(SND_PIN);	// for tone generation.
	
	// inverted fast pwm mode on timer 1
	TCCR1A = _BV(COM1A1) | _BV(COM1A0) | _BV(WGM11);
	TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);
	
	OCR1A = _CYCLES_HORZ_SYNC;
	scanLine = linesPerFrame+1;
	lineHandler = &vsyncLine;
	TIMSK1 = _BV(TOIE1);
	sei();
}

// render a line
ISR(TIMER1_OVF_vect) {
	lineHandler();
        scanLine++;
}

void empty() {}

void blankLine() {
	if (scanLine == (startRenderLine-1)) {
		renderStartOffset = 0;
		remainingLinesPerVertPixel = linesPerVertPixel;
		lineHandler = &activeLine;
	}
	else if (scanLine == linesPerFrame) {
		lineHandler = &vsyncLine;
	}
}

static void inline waitUntil(uint8_t time) {
  __asm__ __volatile__ (
      "subi %[time], 10\n"
      "sub  %[time], %[tcnt1l]\n\t"
    "100:\n\t"
      "subi %[time], 3\n\t"
      "brcc 100b\n\t"
      "subi %[time], 0-3\n\t"
      "breq 101f\n\t"
      "dec  %[time]\n\t"
      "breq 102f\n\t"
      "rjmp 102f\n"
    "101:\n\t"
      "nop\n" 
    "102:\n"
    :
    : [time] "a" (time),
    [tcnt1l] "a" (TCNT1L)
  );
}

void activeLine() {

  // The renderer will normally draw the main screen as part of the scan.
  // However, if the scanline is to draw the double-res ball area screen instead
  // then point to the appropriate screen buffer and set the offset to show
  // the correct line.
  int tempOffset = renderStartOffset;
  uint8_t * tempScreen;
  tempScreen=screen;
  int lineY=scanLine-startRenderLine;
  if (ballVisible==1 && (lineY>=virtualBallY) && (lineY<(virtualBallY+5)))
  {
    tempOffset=(lineY - virtualBallY)*10;
    tempScreen=doubleResScreen;
  }
        
	waitUntil(outputDelay);

	__asm__ __volatile__ (
		"ADD	r26,r28\n\t"
		"ADC	r27,r29\n\t"
    //save PORTB
    "in		r16,%[port]\n\t"
		ANDI_HWS
		"rjmp	enterRend\n"
	"loopRend:\n\t"
		"bst	__tmp_reg__,0\n\t"			//8
		BLD_HWS
		"out	%[port],r16\n"
	"enterRend:\n\t"
		"LD	__tmp_reg__,X+\n\t"			//1
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"bst	__tmp_reg__,7\n\t"
		BLD_HWS
		"out	%[port],r16\n"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"bst	__tmp_reg__,6\n\t"
		BLD_HWS
		"out	%[port],r16\n"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"bst	__tmp_reg__,5\n\t"
		BLD_HWS
		"out	%[port],r16\n"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"bst	__tmp_reg__,4\n\t"
		BLD_HWS
		"out	%[port],r16\n"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"bst	__tmp_reg__,3\n\t"
		BLD_HWS
		"out	%[port],r16\n"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"bst	__tmp_reg__,2\n\t"
		BLD_HWS
		"out	%[port],r16\n"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"bst	__tmp_reg__,1\n\t"
		BLD_HWS
    "out	%[port],r16\n"
		"dec	%[horizRes]\n\t"
		"breq	exitRend\n\t"					//go to loopsix
		"jmp	loopRend\n\t"						//5
	"exitRend:\n\t"
    "nop\n\t"
    "nop\n\t"
    "nop\n\t"
    "bst	__tmp_reg__,0\n\t"			//8
		BLD_HWS
		"out	%[port],r16\n"
    "in		r16,%[port]\n\t"
		ANDI_HWS
		BST_HWS
    "nop\n\t"
    "nop\n\t"
    "nop\n\t"
		BLD_HWS
		"out	%[port],r16\n"
		:
		: [port] "i" (_SFR_IO_ADDR(PORT_VID)),
		"x" (tempScreen),
		"y" (tempOffset),
		[horizRes] "d" (horizRes)
		: "r16" 
	);

  remainingLinesPerVertPixel--;
	if (remainingLinesPerVertPixel==0) {
		remainingLinesPerVertPixel = linesPerVertPixel;
		renderStartOffset += horizRes;
	}
  else
  {
    // If the second scanline of the same row is being displayed
    // (main screen has 2 scan lines per vertical pixel)
    // then DESTRUCTIVELY clear the left and right pixels so that the
    // second of each pair of scanlines will have a gap.
    // This produces the dotted edge as seen on the original game.
      if (chipVersion==2)
      {
        if (gameNumber>1)
        {
          //Wipe left two pixels
          screen[renderStartOffset] &= 0b00111111;
        }
        if (gameNumber==2)
        {
          //Wipe right two pixels
          screen[renderStartOffset+9] =0;
        }
      }
      else
      {
        if (gameNumber>1)
        {
          //Wipe left one pixel
          screen[renderStartOffset] &= 0b01111111;
        }
        if (gameNumber==2)
        {
          //Wipe right one pixel
          screen[renderStartOffset+9] &= 0b11111101;
        }
      }
  }
		
	if ((scanLine + 1) == (int)(startRenderLine + (vertRes*linesPerVertPixel)))
		lineHandler = &blankLine;
		
}

void vsyncLine() {
	if (scanLine >= linesPerFrame) {
		OCR1A = _CYCLES_VERT_SYNC;
		scanLine = 0;
		frames++;

		if (remainingToneVsyncs != 0)
		{
			if (remainingToneVsyncs > 0)
			{
				remainingToneVsyncs--;
			}

		} else
		{
			TCCR2B = 0; //stop the tone
 			PORTB &= ~(_BV(SND_PIN));
		}

	}
	else if (scanLine == vsyncEnd) {
		OCR1A = _CYCLES_HORZ_SYNC;
		lineHandler = &blankLine;
	}
}

// END OF MODIFIED TV OUT LIBRARY CODE

