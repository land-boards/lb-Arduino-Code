#include <Arduino.h>
#include <ClickEncoder.h>
#include <TimerOne.h>
#include <U8g2lib.h>
#include <PE43xx.h>

// encoder
#define ENCODER_PINA 8
#define ENCODER_PINB 9
#define ENCODER_BTN 7
#define ENCODER_STEPS_PER_NOTCH 2
ClickEncoder encoder = ClickEncoder(ENCODER_PINA, ENCODER_PINB, ENCODER_BTN, ENCODER_STEPS_PER_NOTCH);

// oled
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);
#define digits 1

// attenuator
PE43xx attenuator(A4, A5, A6, PE4302);

float newlevel = 0;

// tmp
unsigned long previousMillis = 0;
unsigned long interval = 250;
bool blink = true;

// timer interrupt for servicing the encoder
void timerIsr()
{
  encoder.service();
}

void setup()
{
  // for debugging
  Serial.begin(9600);

  // no need for these
  encoder.setButtonHeldEnabled(false);
  encoder.setDoubleClickEnabled(false);

  // display
  u8g2.begin();

  // initialize the attenuator
  attenuator.begin();

  Timer1.initialize(1000); // in us => 1000hz
  Timer1.attachInterrupt(timerIsr);
}

void handleEncoder()
{
  // get new level
  newlevel = newlevel + attenuator.getStep() * encoder.getValue();
  if (newlevel > attenuator.getMax())
  {
    newlevel = attenuator.getMax();
  }
  if (newlevel < 0)
  {
    newlevel = 0;
  }

  // if encoder is clicked set the new level in the attenuator
  if (encoder.getButton() == ClickEncoder::Clicked)
  {
    attenuator.setLevel(newlevel);
  }
}

void draw()
{
  u8g2.setFont(u8g2_font_bubble_tr);

  if (newlevel != attenuator.getLevel())
  {
    // different view if we are setting new value
    u8g2.setCursor(5, 25);
    u8g2.print(attenuator.getLevel(), digits);
    u8g2.print(" dB");

    // blink the new value
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
    {
      previousMillis = currentMillis;
      blink = !blink;
    }
    if (blink)
    {
      u8g2.setCursor(5, 52);
      u8g2.print(newlevel, digits);
      u8g2.print(" dB");
    }

    u8g2.setFont(u8g2_font_courB08_tf);
    u8g2.setCursor(10, 64);
    u8g2.print("click to activate");
  }
  else
  {
    // normal view
    u8g2.setCursor(5, 35);
    u8g2.print(attenuator.getLevel(), digits);
    u8g2.print(" dB");
  }
}

void loop()
{
  // draw
  u8g2.firstPage();
  do
  {
    draw();
  } while (u8g2.nextPage());

  // handle encoder inputs
  handleEncoder();
}