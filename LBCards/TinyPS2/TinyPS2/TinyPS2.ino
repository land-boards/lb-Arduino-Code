// TinyPS06 - Read PS/2 Keyboard, write Serial data out
//    https://github.com/land-boards/lb-Arduino-Code/tree/master/LBCards/TinyPS2/TinyPS2
// Ported from Scott Baker's build
//  https://www.smbaker.com/ps2-ttlserial-adapter-for-rc2014-and-midi
// Modified to build under Arduino environment
// Original pieces that make up the code
//    https://github.com/thegaragelab/tinytemplate
//    http://www.nerdkits.com/videos/interrupts_and_ps2_keyboard/
//

/** Baud rate to use
 *
 * The implementation is optimised for higher baudrates - please don't use
 * anything below 57600 on an 8MHz clock. It does work at up to 250000 baud
 * but you may experience a small amount of dropped packets at that speed.
 */
#define BAUD_RATE 115200

volatile uint8_t kbd_data;
volatile uint8_t char_waiting;
uint8_t started;
uint8_t bit_count;
uint8_t shift;
uint8_t caps_lock;
uint8_t extended;
uint8_t release;

uint8_t key_code = 0;
char key_char;

char str_buf[21];
uint8_t buf_pos = 0;

void setup()
{
  init_keyboard();
  
  uartInit();
  
  //enable interrupts
  sei();
  
  str_buf[0] = str_buf[1] = 0x00;

}

void loop()
{
  if(char_waiting)
  {
    key_code = read_char();
    key_char = render_scan_code(key_code);
    uartSend(key_char);
  }
}
