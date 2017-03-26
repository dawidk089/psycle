/*
 * velocity_simple.cpp
 *
 * Created: 2017-03-25 18:48:07
 *  Author: Korpo
 */ 
#include "velocity_simple.h"
#include "../interrupts_wrapper/interrupts_wrapper.h"
#include <avr/interrupt.h>
#include "avr/io.h"

#define PI_APPROX_MP(x) ((uint32_t)(x)*355/113)
#define PI_APPROX_DIV(x) ((uint32_t)(x)*113/355)

ICP1Interrupt::ICP1Interrupt(){
	 Interrupt::Register(TIMER1_CAPT_vect_num, this);
}

ICP1Interrupt objICP1Interrupt;

void ICP1Interrupt::setOwnerPtr(VELOCITY_LIN* ownerPtr){
	InterruptOwnerPtr = ownerPtr;
}

void ICP1Interrupt::myISR(void){
	this->InterruptOwnerPtr->add_rot_time(ICR1);
	TIFR |= (1<<ICF1);
};

void VELOCITY_LIN::init(uint16_t diameter_mm){
	this->circumf_mm = PI_APPROX_MP(diameter_mm);
	
	TCCR1B |= this->clk_prescaler | (1<<ICNC1); //TODO edge? 
	ACSR |= (1<<ACIC);
	TIMSK |= (1<<TICIE1) | (1<<TOIE1); //TODO overflow interrupt
	TIFR |= (1<<ICF1) | (1<<TOV1); //clear
}

void VELOCITY_LIN::add_rot_time(uint16_t t_unit){
	this->t_unit_coll[t_unit_pos++]=t_unit;
}

uint8_t VELOCITY_LIN::get_velocity(){
	uint32_t sum = 0;
	for(uint8_t i=0;i<TIME_COLL_WIDTH; ++i) sum+=t_unit_coll[i];
	return sum>>TIME_COLL_BWIDTH;
}

VELOCITY_LIN::VELOCITY_LIN(void){
	//InterruptPtr = new ICP1Interrupt(this);
	//InterruptPtr = &objICP1Interrupt;
	//InterruptPtr->setOwnerPtr(this);
}



/*
ISR(TIMER1_CAPT_vect){
	*add_rot_time_fun(ICR1);
	TIFR |= (1<<ICF1);
}
*/
