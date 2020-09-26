/*
 * i2c.c - I2C library for avr-gcc for devices with TWI
 *
 * Copyright (C) 2014 Jason Milldrum <milldrum@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <util/twi.h>
#include <avr/power.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>

#include "i2c.h"

void i2c_init(void)
{
	power_twi_enable();

	//set SCL to ~100 kHz for 8 MHz CPU clock
	TWSR = 0; /* Prescale /1 */
	TWBR = 0x25;

	//enable I2C
	TWCR = _BV(TWEN);
}

void i2c_start(void)
{
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
	while (!(TWCR & _BV(TWINT)));
}

void i2c_stop(void)
{
	TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
}

void i2c_write(uint8_t data)
{
	TWDR = data;
	TWCR = _BV(TWINT) | _BV(TWEN);
	while (!(TWCR & _BV(TWINT)));
}

uint8_t i2c_read_ack(void)
{
	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
	while (!(TWCR & _BV(TWINT)));
	return TWDR;
}

uint8_t i2c_read_nack(void)
{
	TWCR = _BV(TWINT) | _BV(TWEN);
	while (!(TWCR & _BV(TWINT)));
	return TWDR;
}

uint8_t i2c_status(void)
{
	return TW_STATUS;
}
