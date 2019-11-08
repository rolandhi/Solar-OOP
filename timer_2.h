/*
 * timer_2.h
 *
 * Created: 03.08.2013 22:05:30
 *  Author: hillenbrand
 */ 


#ifndef TIMER_2_H_
#define TIMER_2_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "solar_OOP.h"

/* prescaler of 0 disables timer*/
#define TIMER_2_PRESCALER CLOCK_PRESCALER * 64

#define two_ms_OCR2A 124

class Timer_2
{
public:
	Timer_2();
	~Timer_2(){}
   uint8_t Get_Compare_Interrupt_A_detected();
   void Set_Compare_Interrupt_A_detected();
   void Reset_Compare_Interrupt_A_detected();
protected:
	
private:
   uint8_t Compare_Interrupt_A_detected;
};
extern Timer_2 TIMER_2;
#endif /* TIMER_2_H_ */
