// TinyPS06 - Read PS/2 Keyboard, write Serial data out

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
//    _delay_ms(5);   /* delay so the led blink is obvious */
  }
}
