// u8g2_prepare()
// Setup the screen font, etc
// List of fonts
// https://github.com/olikraus/u8g2/wiki/fntlist8#u8g2-fonts-capital-a-height-38
void u8g2_prepare(void)
{
//  u8g2.setFont(u8g2_font_ncenB14_tr); // 14 Pixel tall font
  u8g2.setFont(u8g2_font_t0_11b_tf); // 8 Pixel tall font
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void displayFreqInKHzOnOLED(float freq)
{
  char inBuffer[10];
  char outBuffer[15];
  uint8_t buffOff;
  u8g2.clearBuffer();
  u8g2_prepare();
  if (freq >= 10000000)
  {
    // Adda a comma below the MHz digits
    // 0123456789012
    // 10000000
    // 10,000.000 KHz
    dtostrf(freq, 8, 0, inBuffer);
    outBuffer[0] = inBuffer[0];
    outBuffer[1] = inBuffer[1];
    outBuffer[2] = '.';
    outBuffer[3] = inBuffer[2];
    outBuffer[4] = inBuffer[3];
    outBuffer[5] = inBuffer[4];
    outBuffer[6] = ',';
    outBuffer[7] = inBuffer[5];
    outBuffer[8] = inBuffer[6];
    outBuffer[9] = inBuffer[7];
    outBuffer[10] = ' ';
    outBuffer[11] = 'M';
    outBuffer[12] = 'H';
    outBuffer[13] = 'z';
    outBuffer[14] = 0;
  }
  else if (freq >= 1000000)
  {
    // Adda a comma below the MHz digits
    // 0123456789012
    // 1000000
    // 1,000.00 KHz
    dtostrf(freq, 7, 0, inBuffer);
    outBuffer[0] = inBuffer[0];
    outBuffer[1] = '.';
    outBuffer[2] = inBuffer[1];
    outBuffer[3] = inBuffer[2];
    outBuffer[4] = inBuffer[3];
    outBuffer[5] = ',';
    outBuffer[6] = inBuffer[4];
    outBuffer[7] = inBuffer[5];
    outBuffer[8] = inBuffer[6];
    outBuffer[9] = ' ';
    outBuffer[10] = 'M';
    outBuffer[11] = 'H';
    outBuffer[12] = 'z';
    outBuffer[13] = 0;
  }
  else if (freq >= 100000)
  {
    // 0123456789012
    // 100000
    // 100.000 KHz
    dtostrf(freq, 6, 0, inBuffer);
    outBuffer[0] = inBuffer[0];
    outBuffer[1] = inBuffer[1];
    outBuffer[2] = inBuffer[2];
    outBuffer[3] = '.';
    outBuffer[4] = inBuffer[3];
    outBuffer[5] = inBuffer[4];
    outBuffer[6] = inBuffer[5];
    outBuffer[7] = ' ';
    outBuffer[8] = 'K';
    outBuffer[9] = 'H';
    outBuffer[10] = 'z';
    outBuffer[11] = 0;
  }
  else if (freq >= 10000)
  {
    // 0123456789012
    // 10000
    // 10.000 KHz
    dtostrf(freq, 5, 0, inBuffer);
    outBuffer[0] = inBuffer[0];
    outBuffer[1] = inBuffer[1];
    outBuffer[2] = '.';
    outBuffer[3] = inBuffer[2];
    outBuffer[4] = inBuffer[3];
    outBuffer[5] = inBuffer[4];
    outBuffer[6] = ' ';
    outBuffer[7] = 'K';
    outBuffer[8] = 'H';
    outBuffer[9] = 'z';
    outBuffer[10] = 0;
  }
  else if (freq >= 1000)
  {
    // 0123456789012
    // 1000
    // 1.000 KHz
    dtostrf(freq, 4, 0, inBuffer);
    outBuffer[0] = inBuffer[0];
    outBuffer[1] = ',';
    outBuffer[2] = inBuffer[1];
    outBuffer[3] = inBuffer[2];
    outBuffer[4] = inBuffer[3];
    outBuffer[5] = ' ';
    outBuffer[6] = 'K';
    outBuffer[7] = 'H';
    outBuffer[8] = 'z';
    outBuffer[9] = 0;
  }
  else if (freq >= 100)
  {
    // 0123456789012
    // 100
    // 100 Hz
    dtostrf(freq, 3, 0, inBuffer);
    outBuffer[0] = inBuffer[0];
    outBuffer[1] = inBuffer[1];
    outBuffer[2] = inBuffer[2];
    outBuffer[3] = ' ';
    outBuffer[4] = 'H';
    outBuffer[5] = 'z';
    outBuffer[6] = 0;
  }
  else if (freq >= 10)
  {
    // 0123456789012
    // 10
    // 10 Hz
    dtostrf(freq, 2, 0, inBuffer);
    outBuffer[0] = inBuffer[0];
    outBuffer[1] = inBuffer[1];
    outBuffer[2] = ' ';
    outBuffer[3] = 'H';
    outBuffer[4] = 'z';
    outBuffer[5] = 0;
  }
  else
  {
    // 0123456789012
    // 1
    // 1 Hz
    dtostrf(freq, 1, 0, inBuffer);
    outBuffer[0] = inBuffer[0];
    outBuffer[1] = ' ';
    outBuffer[2] = 'H';
    outBuffer[3] = 'z';
    outBuffer[3] = 0;
  }
  u8g2.drawStr( 0, 0, outBuffer);
  u8g2.sendBuffer();
}

void printStringToOLED(char * charStr)
{
  u8g2.clearBuffer();
  u8g2_prepare();
  u8g2.drawStr( 0, 0, charStr);
  u8g2.sendBuffer();
}
