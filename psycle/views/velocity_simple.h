/*
 * velocity_simple.h
 *
 * Created: 2017-03-25 18:48:23
 *  Author: Korpo
 */


#ifndef VELOCITY_SIMPLE_H_
#define VELOCITY_SIMPLE_H_

#include "avr/io.h"
#include "../interrupts_wrapper/interrupts_wrapper.h"
#define TIME_COLL_BWIDTH 2
#define TIME_COLL_WIDTH (1<<TIME_COLL_BWIDTH) //average optimization

class VELOCITY_LIN;

class ICP1Interrupt : public Interrupt{
public:
	ICP1Interrupt(void);
	void setOwnerPtr(VELOCITY_LIN* ownerPtr);
	virtual void myISR(void);
private: 
	VELOCITY_LIN* InterruptOwnerPtr;	
};

class VELOCITY_LIN {
	friend class ICP1Interrupt;
	ICP1Interrupt* InterruptPtr;
	
	const uint8_t clk_prescaler = (1<<CS12) | (1<<CS10);
	uint16_t circumf_mm;
	uint16_t t_unit_coll[TIME_COLL_WIDTH];
	uint8_t t_unit_pos = 0;
	
public:	
	VELOCITY_LIN(void);
	void init(uint16_t diameter_mm);
	void add_rot_time(uint16_t t_unit);
	uint8_t get_velocity();
};

#endif /* VELOCITY_SIMPLE_H_ */