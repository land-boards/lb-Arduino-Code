/*
	SerialOps - Serial Operations

  baud_XXX() - Set the baud rate and init the serial port
  XXXno_hanksh() - Set the handshake type
  initSerial1(baudRate) - Initialize the port at baudRate
  fileSend() - Send the file
  fileReceive() - Receive the file
  initUSBSerial() - Initialize the USB serial
*/

// Baud rate

void baud_300()
{
  baudRate = 300;
  initSerial1(300);
  u8x8.clear();
  u8x8.draw2x2String(0, 2, "300 b/s");
  delay(500);
}

void baud_1200()
{
  baudRate = 1200;
  initSerial1(1200);
  u8x8.clear();
  u8x8.draw2x2String(0, 2, "1.2k b/s");
  delay(500);
}

void baud_9600()
{
  baudRate = 9600;
  initSerial1(9600);
  u8x8.clear();
  u8x8.draw2x2String(0, 2, "9.6k b/s");
  delay(500);
}

void baud_115k()
{
  baudRate = 115200;
  initSerial1(115200);
  u8x8.clear();
  u8x8.draw2x2String(0, 2, "115.2k b");
  delay(500);
}

// Handshake type

void no_hanksh()
{
  handshakeType = NO_HANDSHAKE;
  u8x8.clear();
  u8x8.draw2x2String(0, 2, "No h/s");
  delay(500);
}

void hw_hansh()
{
  handshakeType = HW_HANDSHAKE;
  u8x8.clear();
  u8x8.draw2x2String(0, 2, "H/W h/s");
  delay(500);
}

void x_hansh()
{
  handshakeType = XON_XOFF_HANDSHAKE;
  u8x8.clear();
  u8x8.draw2x2String(0, 2, "Xon h/s");
  delay(500);
}

void initSerial1(uint32_t baudRate)
{
  if (comInit == 1)
    Serial1.end();
  // Open serial communications and wait for port to open:
  Serial1.begin(baudRate);
  // Wait for Serial Monitor to connect.
  // Needed for native USB port boards only
  while (!Serial1);
  comInit = 1;
}

// fileSend()
void fileSend()
{
  if (comInit == 0)
  {
  u8x8.clear();
  u8x8.draw2x2String(0, 2, "Need to");
  u8x8.draw2x2String(0, 4, "set baud");
  u8x8.draw2x2String(0, 6, "rate");
  delay(2000);
  return;
  }
  u8x8.clear();
  u8x8.draw2x2String(0, 2, "File");
  u8x8.draw2x2String(1, 4, "Send");
  delay(2000);
}

// fileReceive()
void fileReceive()
{
  if (comInit == 0)
  {
  u8x8.clear();
  u8x8.draw2x2String(0, 2, "Need to");
  u8x8.draw2x2String(0, 4, "set baud");
  u8x8.draw2x2String(0, 6, "rate");
  delay(2000);
  return;
  }
  u8x8.clear();
  u8x8.draw2x2String(0, 2, "File");
  u8x8.draw2x2String(1, 4, "Receive");
  delay(2000);
}

// debugUSB
void initUSBSerial()
{
  if (USBSerInit == 1)
    return;
  u8x8.clear();
  u8x8.draw2x2String(0, 2, "USB");
  u8x8.draw2x2String(0, 4, "Serial");
  u8x8.draw2x2String(0, 6, "init");
  delay(2000);
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // Wait for Serial Monitor to connect.
  // Needed for native USB port boards only
  if (!Serial)
  {
    u8x8.clear();
    u8x8.draw2x2String(0, 2, "Waiting");
    u8x8.draw2x2String(1, 4, "for Ser");
    u8x8.draw2x2String(1, 6, "Monitor");
  }
  while (!Serial);
  USBSerInit = 1;
  Serial.println("Initialized USB Serial");
}
