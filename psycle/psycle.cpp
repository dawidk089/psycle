/*
 File:      main.cpp
 Version:   0.1 - first version
 Date:      February 12, 2015
 License:	GPL v2

 ILI9163 LCD Test code
 1.44" Serial 128X128 SPI Color TFT LCD Module Display

 ****************************************************************************
 Copyright (C) 2015 Radu Motisan  <radu.motisan@gmail.com>

 http://www.pocketmagic.net

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ****************************************************************************
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <string.h>
#include <stdlib.h>
// local headers
#include "config.h" // defines F_CPU
#include "ili9163/ili9163lcd.h"
#include "ili9163/colors.h"
#include "spi/spi.h"

#include "views/velocity_simple.h"

// FUSES =
// {
// 	.low = 0xDC,		// external 8MHz Quartz crystal
// 	.high = 0x9F,
// 	.extended = 0xEF,
// };

#define GREEN_LED_PIN 0
#define GREEN_LED_DDR DDRB
#define GREEN_LED_PORT PORTB

#define RED_LED_PIN 7
#define RED_LED_DDR DDRD
#define RED_LED_PORT PORTD

#define VELOCITY_DIG_N 3
#define INN2MM(x) 254*x

void dec2str(uint8_t x, char* str_msc){
	*str_msc-- = '\0';
	uint8_t prev_x;
	for(uint8_t i=0; i<VELOCITY_DIG_N; ++i){
		prev_x = x; x/=10;
		char dig = '0'+prev_x-x*10;
		*str_msc-- = (dig=='0'?' ':dig);
	}
}


// sda = mosi
// a0 = dc - data/command
DigitalPin	pinSCK(&PORTB, PORTB5), pinSDA(&PORTB, PORTB3), pinA0(&PORTB, PORTB1), pinRESET(&PORTC, PORTC3), pinCS(&PORTB, PORTB2);
ILI9163 	lcd(&pinA0, &pinRESET, &pinCS);

/************************************************************************************************************************************************/
/* Main entry point                                                    																			*/
/************************************************************************************************************************************************/
int main(void) {
		
	spi_init();
	
	lcd.init(ILI9163::ROT270);
	lcd.drawClear(BLACK);
	
/*****VELOCITY*****/
	VELOCITY_LIN velocity_lin;
	velocity_lin.init(INN2MM(26));
	
	char velocity_str[VELOCITY_DIG_N];
	
	while(true){
		uint8_t velocity = velocity_lin.get_velocity();
		dec2str(velocity, velocity_str);
		lcd.drawString(0, 80, sizeof(velocity_str)/sizeof(velocity_str[0]), YELLOW, BLACK, velocity_str);
		_delay_ms(500);
	}
	
}
