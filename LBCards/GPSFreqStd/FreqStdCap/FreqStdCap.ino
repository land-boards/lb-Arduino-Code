// FreqStdCap.ino - Frequency Standard
// Generate the bytesting tables for 1, 8, and 10 MHz
// bytStr = b'\xB5\x62\x06\x31\x20\x00\x00\x01\x00\x00\x32\x00\x00\x00\x05\x0D\x00\x00\x80\x96\x98\x00\x00\x00\x00\x80\x00\x00\x00\x80\x00\x00\x00\x00\x0F\x00\x00\x00\x59\x13'

struct GPS_TP5_MSG
{
  uint8_t   header1;              // 0xB5
  uint8_t   header2;              // 0x62
  uint8_t   message_class;        // 0x06
  uint8_t   message_id;           // 0x31
  uint16_t  length;               // 0x20, 0x00 (32)
  uint8_t   timepulse_idx;        // 0x00
  uint8_t   version;              // 0x01
  uint16_t  reserved;             // 0x00, 0x00
  int16_t   antenna_cable_delay;  // 0x32, 0x00
  int16_t   rf_group_delay;       // 0x00, 0x00
  uint32_t  frequency_unlocked;   // 0x05, 0x0D, 0x00, 0x00 = 3333 dec
  uint32_t  frequency_locked;     // 0x80, 0x96, 0x98, 0x00 = 10,000,000 dec
  uint32_t  duty_cycle_unlocked;  // 0x00, 0x00, 0x00, 0x80 
  uint32_t  duty_cycle_locked;    // 0x00, 0x00, 0x00, 0x80
  uint32_t  user_delay;           // 0x00, 0x00, 0x00, 0x00
  uint32_t  flags;                // 0x0F, 0x00, 0x00, 0x00
  uint16_t  checksum;             // 0x59, 0x13
} __attribute__((packed));

const uint16_t GPS_TP5_ACTIVE           = 0x01;
const uint16_t GPS_TP5_SYNC_TO_GNSS     = 0x02;
const uint16_t GPS_TP5_LOCKED_OTHER_SET = 0x04;
const uint16_t GPS_TP5_IS_FREQUENCY     = 0x08;
const uint16_t GPS_TP5_IS_LENGTH        = 0x10;
const uint16_t GPS_TP5_ALIGN_TO_TOW     = 0x20;
const uint16_t GPS_TP5_POLARITY_RISING  = 0x40;

const uint32_t GPS_TP5_DUTY_CYCLE_50    = 0x80000000;

uint16_t calculateChecksum(uint8_t *p, size_t len)
{
  uint8_t ck_a = 0;
  uint8_t ck_b = 0;
  while (len--)
  {
    ck_a = ck_a + *p++;
    ck_b = ck_b + ck_a;
  }
  return ck_a | (ck_b << 8);
}

void setup() 
{
  char buff[50];

  Serial.begin(9600);
  while (!Serial);
  
  // put your setup code here, to run once:
  GPS_TP5_MSG msg;
  memset(&msg, 0, sizeof(msg));

  msg.header1 = 0xB5;
  msg.header2 = 0x62;
  msg.message_class = 0x06;
  msg.message_id = 0x31;
  msg.length = 32;
  msg.version = 1;
  msg.antenna_cable_delay = 50;
  msg.frequency_unlocked = 3333;
  msg.duty_cycle_unlocked = GPS_TP5_DUTY_CYCLE_50;
  msg.duty_cycle_locked = GPS_TP5_DUTY_CYCLE_50;
  msg.flags = GPS_TP5_ACTIVE | GPS_TP5_SYNC_TO_GNSS | GPS_TP5_LOCKED_OTHER_SET | GPS_TP5_IS_FREQUENCY;

  unsigned char * msgPtr = &msg.header1;

//  msg.frequency_locked = freq;
  msg.frequency_locked = 10000000UL;
  msg.checksum = calculateChecksum(((uint8_t*)&msg) + 2, 4 + msg.length);
  Serial.println("# 10 MHz output");
  Serial.print("bytStr = b'");
  for (uint16_t i = 0; i < sizeof(msg); i++)
  {
    sprintf(buff, "\\x%02X", msgPtr[i]);
    Serial.print(buff);
  }
  Serial.print("'\n\r");

  msg.frequency_locked = 8000000UL;
  msg.checksum = calculateChecksum(((uint8_t*)&msg) + 2, 4 + msg.length);
  Serial.println("# 8 MHz output");
  Serial.print("# bytStr = b'");
  for (uint16_t i = 0; i < sizeof(msg); i++)
  {
    sprintf(buff, "\\x%02X", msgPtr[i]);
    Serial.print(buff);
  }
  Serial.print("'\n\r");

  
  msg.frequency_locked = 1000000UL;
  msg.checksum = calculateChecksum(((uint8_t*)&msg) + 2, 4 + msg.length);
  Serial.println("# 1 MHz output");
  Serial.print("# bytStr = b'");
  for (uint16_t i = 0; i < sizeof(msg); i++)
  {
    sprintf(buff, "\\x%02X", msgPtr[i]);
    Serial.print(buff);
  }
  Serial.print("'\n\r");

}
void loop() {
  // put your main code here, to run repeatedly:

}
