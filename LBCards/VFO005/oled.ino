void u8g2_prepare(void)
{
  u8g2.setFont(u8g2_font_ncenB14_tr); // 14 Pixel tall font
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void displayFreqOnOLED(float freq)
{
  char buffer[17];
  uint8_t buffOff;
  u8g2.clearBuffer();
  u8g2_prepare();
  if (freq >= 10000000)
  {
    // Adda a comma below the MHz digits
    // 0123456789012
    // 10000000
    // 10,000.00 KHz
    dtostrf(freq, 8, 0, buffer);
    buffer[7] = buffer[5];
    buffer[6] = '.';
    buffer[5] = buffer[4];
    buffer[4] = buffer[3];
    buffer[3] = buffer[2];
    buffer[2] = ',';
    buffer[8] = ' ';
    buffer[9] = 'K';
    buffer[10] = 'H';
    buffer[11] = 'z';
    buffer[12] = 0;
  }
  else if (freq >= 1000000)
  {
    // Adda a comma below the MHz digits
    // 0123456789012
    // 1000000
    // 1,000.00 KHz
    dtostrf(freq, 7, 0, buffer);
    buffer[7] = buffer[5];
    buffer[6] = buffer[4];
    buffer[5] = '.';
    buffer[4] = buffer[3];
    buffer[3] = buffer[2];
    buffer[2] = buffer[1];
    buffer[1] = ',';
    buffer[8] = ' ';
    buffer[9] = 'K';
    buffer[10] = 'H';
    buffer[11] = 'z';
    buffer[12] = 0;
  }
  else if (freq >= 100000)
  {
    // 0123456789012
    // 100000
    // 100.000 KHz
    dtostrf(freq, 6, 0, buffer);
    buffer[6] = buffer[5];
    buffer[5] = buffer[4];
    buffer[4] = buffer[3];
    buffer[3] = '.';
    buffer[7] = ' ';
    buffer[8] = 'K';
    buffer[9] = 'H';
    buffer[10] = 'z';
    buffer[11] = 0;
  }
  else if (freq >= 10000)
  {
    // 0123456789012
    // 10000
    // 10.000 KHz
    dtostrf(freq, 5, 0, buffer);
    buffer[5] = buffer[4];
    buffer[4] = buffer[3];
    buffer[3] = buffer[2];
    buffer[2] = '.';
    buffer[6] = ' ';
    buffer[7] = 'K';
    buffer[8] = 'H';
    buffer[9] = 'z';
    buffer[10] = 0;
  }
  else if (freq >= 1000)
  {
    // 0123456789012
    // 1000
    // 1.000 KHz
    dtostrf(freq, 4, 0, buffer);
    buffer[4] = buffer[3];
    buffer[3] = buffer[2];
    buffer[2] = buffer[1];
    buffer[1] = '.';
    buffer[5] = ' ';
    buffer[6] = 'K';
    buffer[7] = 'H';
    buffer[8] = 'z';
    buffer[9] = 0;
  }
  else if (freq >= 100)
  {
    // 0123456789012
    // 100
    // 100 Hz
    dtostrf(freq, 3, 0, buffer);
    buffer[3] = ' ';
    buffer[4] = 'H';
    buffer[5] = 'z';
    buffer[6] = 0;
  }
  else if (freq >= 10)
  {
    // 0123456789012
    // 10
    // 10 Hz
    dtostrf(freq, 2, 0, buffer);
    buffer[2] = ' ';
    buffer[3] = 'H';
    buffer[4] = 'z';
    buffer[5] = 0;
  }
  else
  {
    // 0123456789012
    // 1
    // 1 Hz
    dtostrf(freq, 1, 0, buffer);
    buffer[1] = ' ';
    buffer[2] = 'H';
    buffer[3] = 'z';
    buffer[4] = 0;
  }
  u8g2.drawStr( 0, 0, buffer);
  u8g2.sendBuffer();
}

void printStringToOLED(char * charStr)
{
  u8g2.clearBuffer();
  u8g2_prepare();
  u8g2.drawStr( 0, 0, charStr);
  u8g2.sendBuffer();
}
