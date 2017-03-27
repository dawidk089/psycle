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

#define GREEN_LED_PIN PD6
#define GREEN_LED_DDR DDRD
#define GREEN_LED_PORT PORTD

#define RED_LED_PIN PD5
#define RED_LED_DDR DDRD
#define RED_LED_PORT PORTD

#define VELOCITY_DIG_N 3
#define INN2MM(x) 254*x

void dec2str(uint32_t x, uint8_t digitN, char* str_msc){
	bool isDigit = false;
	str_msc+=digitN;
	*str_msc-- = '\0';
	uint8_t prev_x;
	for(uint8_t i=0; i<digitN; ++i){
		prev_x = x; x/=10;
		*str_msc-- = '0'+prev_x-x*10;
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
	GREEN_LED_DDR |= (1<<GREEN_LED_PIN);
	RED_LED_DDR |= (1<<RED_LED_PIN);
		
	spi_init();
	
	lcd.init(ILI9163::ROT270);
	lcd.drawClear(BLACK);
	
	RED_LED_PORT |= (1<<RED_LED_PIN);	
	
/*****VELOCITY*****/
	VelocityLin velocityLin;
	velocityLin.init(INN2MM(26));
	
	char velocityStr[16];
	
	GREEN_LED_PORT |= (1<<GREEN_LED_PIN);
	
	while(true){
		uint8_t velocity = velocityLin.getVelocity();
		dec2str((isStop?0:velocity), VELOCITY_DIG_N, velocityStr);
		lcd.drawString(0, 50, 1, YELLOW, BLACK, "v[km/h]: ");
		lcd.drawString(80, 50, 1, YELLOW, BLACK, velocityStr);
		dec2str(ICR1, 5, velocityStr);
		lcd.drawString(0, 60, 1, YELLOW, BLACK, "ticks ICR1: ");
		lcd.drawString(80, 60, 1, YELLOW, BLACK, velocityStr);
		dec2str(TCNT1, 5, velocityStr);
		lcd.drawString(0, 70, 1, YELLOW, BLACK, "ticks TCNT1: ");
		lcd.drawString(80, 70, 1, YELLOW, BLACK, velocityStr);
	}
	
}
