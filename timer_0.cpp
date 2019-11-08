/*
 * timer_0.cpp
 *
 * Created: 03.08.2013 22:05:49
 *  Author: hillenbrand
 */


#include "timer_0.h"

Timer_0 TIMER_0;

ISR(TIMER0_COMPA_vect)
{
   /* 15 mus interrupt */
   TIMER_0.Set_Compare_Interrupt_A_detected();
}

Timer_0::Timer_0()
{
/*Timer0 konfigurieren*/
#ifdef TIMER_0_PRESCALER
//TIMSK0 |= (1 << TOIE2);            // Timer Overflow Interrupt enabled
TIMSK0 |= (1 << OCIE0A);            // Timer Compare Interrupt enabled
TIFR0  |= (1 << OCF0A);
TCCR0B = TCCR0B & ~((1 << CS02) | (1 << CS01) | (1 << CS00)); /* remove timer prescaler bits => Timer 0 is disabled */
 #if (TIMER_0_PRESCALER == 0)
TCCR0B = TCCR0B;
 #elif (TIMER_0_PRESCALER == 1)
TCCR0B |= ((1 << CS00));
 #elif (TIMER_0_PRESCALER == 8)
TCCR0B |= ((1 << CS01));
 #elif (TIMER_0_PRESCALER == 64)
TCCR0B |= ((1 << CS01) | (1 << CS00));
 #elif (TIMER_0_PRESCALER == 256)
TCCR0B |= ((1 << CS02));
 #endif /* TIMER 2 PRESCALER */
#endif

OCR0A = 2;//fifteen_mus;
TCCR0A = 0;//1 << COM0A1;
Compare_Interrupt_A_detected = 0;
}


uint8_t Timer_0::Get_Compare_Interrupt_A_detected()
{
   return (Compare_Interrupt_A_detected);
}
void Timer_0::Set_Compare_Interrupt_A_detected()
{
   Compare_Interrupt_A_detected = 1;
}
void Timer_0::Reset_Compare_Interrupt_A_detected()
{
   Compare_Interrupt_A_detected = 0;
}
