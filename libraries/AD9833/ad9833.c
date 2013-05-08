/*
* File: code for controlling the ad9833 DDS
* Author: Tuomas Nylund (tuomas.nylund@gmail.com)
* Website: http://tuomasnylund.fi
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ad9833.h"
#include "spi.h"

ad9833_settings_t ad_settings;

static inline void ad9833_send(uint16_t packet){
  spi_send_byte((uint8_t)(packet>>8));
  spi_send_byte((uint8_t)packet);
}

void ad9833_init(void){
  //init FSYNC pin (aka Chip select)
  ad_settings.command_reg |= (1<<AD_B28);
  AD_FSYNC_DDR |= (1<<AD_FSYNC_BIT);
  AD_FSYNC_HI();

  //init timer modulation
  TCCR1B |= (1<<WGM12); //timer in CTC mode
  TCCR1B |= (1<<CS11)|(1<<CS10);//clockdiv 64
  TIMSK1 |= (1<<OCIE1A);
  OCR1A = 0xFFF0;

  //some datasheet-proscribed delay here
  _delay_us(10);

  //start as half-asleep
  AD_FSYNC_LO();
  _delay_us(5);
  ad9833_send((1<<AD_SLEEP12)|(1<<AD_RESET));
  ad_settings.command_reg |= (1<<AD_SLEEP12);
  _delay_us(5);
  AD_FSYNC_HI();

  //set some nice default values
  ad9833_set_frequency(0, 0);
  ad9833_set_frequency(1, 0);
  ad9833_set_phase(0, 0);
  ad9833_set_phase(1, 0);
  ad9833_set_freq_out(0);
  ad9833_set_phase_out(0);

}

void ad9833_set_mode(uint8_t mode){
  ad_settings.mode = mode;
  switch (mode){
  case AD_OFF:
    ad_settings.command_reg |= (1<<AD_SLEEP12);
    ad_settings.command_reg |= (1<<AD_SLEEP1);
    break;
  case AD_TRIANGLE:
    ad_settings.command_reg &= ~(1<<AD_OPBITEN);
    ad_settings.command_reg |= (1<<AD_MODE);
    ad_settings.command_reg &= ~(1<<AD_SLEEP12);
    ad_settings.command_reg &= ~(1<<AD_SLEEP1);
    break;
  case AD_SQUARE:
    ad_settings.command_reg |= (1<<AD_OPBITEN);
    ad_settings.command_reg &= ~(1<<AD_MODE);
    ad_settings.command_reg |= (1<<AD_DIV2);
    ad_settings.command_reg &= ~(1<<AD_SLEEP12);
    ad_settings.command_reg &= ~(1<<AD_SLEEP1);
    break;
  case AD_SINE:
    ad_settings.command_reg &= ~(1<<AD_OPBITEN);
    ad_settings.command_reg &= ~(1<<AD_MODE);
    ad_settings.command_reg &= ~(1<<AD_SLEEP12);
    ad_settings.command_reg &= ~(1<<AD_SLEEP1);
    break;
  }

  AD_FSYNC_LO();
  _delay_us(5);
  ad9833_send(ad_settings.command_reg);
  _delay_us(5);
  AD_FSYNC_HI();
}

void ad9833_set_phase(uint8_t reg, double phase){
  uint16_t reg_reg; //probably should be renamed...
  if (reg==1)
  reg_reg = AD_PHASE1;
  else
  reg_reg = AD_PHASE0;

  ad_settings.phase[reg] = phase;

  AD_FSYNC_LO();
  _delay_us(5);
  ad9833_send(reg_reg | AD_PHASE_CALC(ad_settings.phase[reg]));
  _delay_us(5);
  AD_FSYNC_HI();
}

double ad9833_get_phase(uint8_t reg){
  return ad_settings.phase[reg];
}

void ad9833_set_freq_out(uint8_t freq_out){
  ad_settings.freq_out = freq_out;
  switch (freq_out){
  case 0:
    ad_settings.command_reg &= ~(1<<AD_FSELECT);
    break;
  case 1:
    ad_settings.command_reg |= (1<<AD_FSELECT);
    break;
  case 2:
    //TODO
    break;
  }

  AD_FSYNC_LO();
  _delay_us(5);
  ad9833_send(ad_settings.command_reg);
  _delay_us(5);
  AD_FSYNC_HI();
}

uint8_t ad9833_get_freq_out(void){
  return ad_settings.freq_out;
}

void ad9833_set_phase_out(uint8_t phase_out){
  ad_settings.phase_out = phase_out;
  switch (phase_out){
  case 0:
    ad_settings.command_reg &= ~(1<<AD_PSELECT);
    break;
  case 1:
    ad_settings.command_reg |= (1<<AD_PSELECT);
    break;
  case 2:
    //TODO
    break;
  }

  AD_FSYNC_LO();
  _delay_us(5);
  ad9833_send(ad_settings.command_reg);
  _delay_us(5);
  AD_FSYNC_HI();
}

uint8_t ad9833_get_phase_out(void){
  return ad_settings.phase_out;
}

void ad9833_set_frequency(uint8_t reg, double freq){
  uint32_t freq_reg;
  uint16_t reg_reg; //probably should be renamed...
  freq_reg = AD_FREQ_CALC(freq);
  ad_settings.freq[reg] = freq;

  if (reg==1)
  reg_reg = AD_FREQ1;
  else
  reg_reg = AD_FREQ0;

  AD_FSYNC_LO();
  _delay_us(5);
  ad9833_send((1<<AD_B28) | ad_settings.command_reg);
  ad9833_send(reg_reg | (0x3FFF&(uint16_t)(freq_reg>>2 )));
  ad9833_send(reg_reg | (0x3FFF&(uint16_t)(freq_reg>>16)));
  _delay_us(5);
  AD_FSYNC_HI();
}

double ad9833_get_frequency(uint8_t reg){
  return ad_settings.freq[reg];
}

void ad9833_set_mod_freq(uint16_t freq){
  ad_settings.mod_freq = freq;
  OCR1A = AD_MOD_FREQ_CALC(freq);
}


void ad9833_set_mod_bytes(uint8_t num, uint8_t *bytes, uint8_t repeat){
  //TODO implements this thing
}

ISR(TIMER1_COMPA_vect){
  uint16_t check = ad_settings.command_reg;
  //TODO implement modulation of real signals
  if (ad_settings.freq_out == 2)
  ad_settings.command_reg ^= ((uint16_t)1<<AD_FSELECT);
  if (ad_settings.phase_out == 2)
  ad_settings.command_reg ^= ((uint16_t)1<<AD_PSELECT);

  if (check != ad_settings.command_reg){
    AD_FSYNC_LO();
    _delay_us(5);
    ad9833_send(ad_settings.command_reg);
    _delay_us(5);
    AD_FSYNC_HI();
  }
}
