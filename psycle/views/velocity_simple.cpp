/*
 * velocity_simple.cpp
 *
 * Created: 2017-03-25 18:48:07
 *  Author: Korpo
 */ 
#include "velocity_simple.h"
#include "avr/interrupt.h"
#include "avr/io.h"

#define PI_APPROX_MP(x) ((uint32_t)(x)*355/113)
#define PI_APPROX_DIV(x) ((uint32_t)(x)*113/355)

uint16_t tUnitColl[TIME_COLL_WIDTH];
uint8_t tUnitPos;
bool isStop;

VelocityLin::VelocityLin(void){
	tUnitCollPtr = tUnitColl;
	isStop = true;
}

void VelocityLin::init(uint16_t diameter_mm){
	this->circumf_mm = PI_APPROX_MP(diameter_mm);
	
	TCCR1B |= this->clkPrescaler;// | (1<<ICNC1); //TODO edge? 
	//ACSR |= (1<<ACIC);
	TIMSK |= (1<<TICIE1) | (1<<TOIE1); //TODO overflow interrupt
	sei();	
}

void VelocityLin::addRotTime(uint16_t t_unit){
	tUnitColl[tUnitPos++]=t_unit;
	if(tUnitPos>TIME_COLL_WIDTH)tUnitPos=0;
}

uint8_t VelocityLin::getVelocity(){
	uint32_t sum = 0;
	for(uint8_t i=0;i<TIME_COLL_WIDTH; ++i) sum+=tUnitColl[i];
	return (uint32_t)F_CPU/T1_PRESC*circumf_mm/(sum>>TIME_COLL_BWIDTH) / 3600;
}

#define RED_LED_PIN PD5
#define RED_LED_DDR DDRD
#define RED_LED_PORT PORTD

#define GREEN_LED_PIN PD6
#define GREEN_LED_DDR DDRD
#define GREEN_LED_PORT PORTD

ISR(TIMER1_CAPT_vect){
	VelocityLin::addRotTime(ICR1);
	TCNT1=0;
	isStop = false;
	RED_LED_PORT ^= (1<<RED_LED_PIN);
	TIFR |= (1<<ICF1);
}

ISR(TIMER1_OVF_vect){
	isStop = true;
	GREEN_LED_PORT ^= (1<<GREEN_LED_PIN);
	TIFR |= (1<<TOV1);
	TIFR |= (1<<ICF1);
}

