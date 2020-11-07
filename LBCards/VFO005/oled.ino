void u8g2_prepare(void)
{
  u8g2.setFont(u8g2_font_ncenB14_tr); // 14 Pixel tall font
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void displayFreqInKHzOnOLED(float freq)
{
  char buffer[14];
  u8g2.clearBuffer();
  u8g2_prepare();
  dtostrf(freq / 1000.0, 9, 3, buffer);
  // Adda a comma below the MHz digits
  if (freq >= 1000000)
  {
    buffer[7] = buffer[6];
    buffer[6] = buffer[5];
    buffer[5] = buffer[4];
    buffer[4] = buffer[3];
    buffer[3] = buffer[2];
    buffer[2] = ',';
  }
  buffer[8] = ' ';
  buffer[9] = 'K';
  buffer[10] = 'H';
  buffer[11] = 'z';
  buffer[12] = 0;
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
