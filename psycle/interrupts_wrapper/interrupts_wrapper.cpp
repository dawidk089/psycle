/*
 * interrupts_wrapper.cpp
 *
 * Created: 2017-03-26 13:01:50
 *  Author: Korpo
 */ 

#include "avr/io.h"
#include "interrupts_wrapper.h"

Interrupt* Interrupt::ISRVectorTable[MAX_INTERRUPTS];

void Interrupt::Interrupt_5(void){
	ISRVectorTable[5]->myISR();
}

void Interrupt::Register(uint8_t interrupt_number, Interrupt* inThisPtr){
	ISRVectorTable[interrupt_number] = inThisPtr;
}

