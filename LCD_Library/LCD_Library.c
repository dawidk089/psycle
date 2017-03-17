#include <avr/io.h>
#include <util/delay.h>

// defines

#define GREEN_LED_PIN PB0
#define GREEN_LED_DDR DDRB
#define GREEN_LED_PORT PORTB

#define RED_LED_PIN PD7
#define RED_LED_DDR DDRD
#define RED_LED_PORT PORTD

#define CS_LD_PIN PC3
#define CS_LD_DDR DDRC
#define CS_LD_PORT PORTC

#define CS_SD_PIN PC4
#define CS_SD_DDR DDRC
#define CS_SD_PORT PORTC

#define DC_LD_PIN PC5
#define DC_LD_DDR DDRC
#define DC_LD_PORT PORTC


int i = 0, j = 0, storedSin = 0;

int main(void) {
	
	RED_LED_DDR |= (1 << RED_LED_PIN);
	GREEN_LED_DDR |= (1 << GREEN_LED_PIN);
	RED_LED_PORT |= (1 << RED_LED_PIN);
	
	while (1)
	{
		_delay_ms(1000);
		GREEN_LED_PORT ^= (1 << GREEN_LED_PIN);
	}
	
}
