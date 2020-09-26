/*
 * i2c.h - I2C library for avr-gcc for devices with TWI
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

#ifndef I2C_H_
#define I2C_H_

#define I2C_SDA					PC4
#define I2C_SDA_PORT			PORTC
#define I2C_SDA_DDR				DDRC

#define I2C_SCL					PC5
#define I2C_SCL_PORT			PORTC
#define I2C_SCL_DDR				DDRC

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_write(uint8_t);
uint8_t i2c_read_ack(void);
uint8_t i2c_read_nack(void);
uint8_t i2c_status(void);

#endif /* I2C_H_ */
