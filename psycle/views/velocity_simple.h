/*
 * velocity_simple.h
 *
 * Created: 2017-03-25 18:48:23
 *  Author: Korpo
 */


#ifndef VELOCITY_SIMPLE_H_
#define VELOCITY_SIMPLE_H_

#include "avr/io.h"
#define T1_PRESC 1024
#define MAX_ICR1 65535
#define TIME_COLL_BWIDTH 2
#define TIME_COLL_WIDTH (1<<TIME_COLL_BWIDTH) //average optimization

extern uint16_t tUnitColl[TIME_COLL_WIDTH];
extern uint8_t tUnitPos;
extern bool isStop;

class VelocityLin {
	const uint8_t clkPrescaler = (1<<CS12) | (1<<CS10);
	uint16_t circumf_mm;
	//uint16_t t_unit_coll[TIME_COLL_WIDTH];
	uint16_t* tUnitCollPtr;
	
public:	
	VelocityLin(void);
	void init(uint16_t diameter_mm);
	static void addRotTime(uint16_t t_unit);
	uint8_t getVelocity();
};

#endif /* VELOCITY_SIMPLE_H_ */