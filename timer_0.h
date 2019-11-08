/*
 * timer_0.h
 *
 * Created: 03.08.2013 22:05:30
 *  Author: hillenbrand
 */


#ifndef TIMER_0_H_
#define TIMER_0_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "solar_OOP.h"

/* prescaler of 0 disables timer*/
#define TIMER_0_PRESCALER CLOCK_PRESCALER * 64

#define fifteen_mus 2

class Timer_0
{
public:
	Timer_0();
	~Timer_0(){}
   uint8_t Get_Compare_Interrupt_A_detected();
   void Set_Compare_Interrupt_A_detected();
   void Reset_Compare_Interrupt_A_detected();
protected:

private:
   uint8_t Compare_Interrupt_A_detected;
};
extern Timer_0 TIMER_0;
#endif /* TIMER_0_H_ */
