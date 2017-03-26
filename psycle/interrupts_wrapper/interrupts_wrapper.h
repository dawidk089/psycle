/*
 * interrupts_wrapper.h
 *
 * Created: 2017-03-26 13:02:23
 *  Author: Korpo
 */ 


#ifndef INTERRUPTS_WRAPPER_H_
#define INTERRUPTS_WRAPPER_H_

#include "avr/io.h"

#define MAX_INTERRUPTS 20

class Interrupt{
public:
	Interrupt(void);
	static void Register(uint8_t interrupt_number, Interrupt* inThisPtr);
	//Interrupt wrapper list
	static void Interrupt_5(void);
	
	virtual void myISR(void) = 0;
private:
	static Interrupt* ISRVectorTable[MAX_INTERRUPTS];
};



#endif /* INTERRUPTS_WRAPPER_H_ */