/*
 * timer_2.cpp
 *
 * Created: 03.08.2013 22:05:49
 *  Author: hillenbrand
 */ 


#include "timer_2.h"

Timer_2 TIMER_2;

ISR(TIMER2_COMPA_vect)
{
   /* 2 ms interrupt */
   TIMER_2.Set_Compare_Interrupt_A_detected();
}

Timer_2::Timer_2()
{
/*Timer2 konfigurieren*/
#ifdef TIMER_2_PRESCALER
//TIMSK2 |= (1 << TOIE2);            // Timer Overflow Interrupt enabled
TIMSK2 |= (1 << OCF2A);            // Timer Compare Interrupt enabled
TCCR2B = TCCR2B & ~((1 << CS22) | (1 << CS21) | (1 << CS20)); /* remove timer prescaler bits => Timer 2 is disabled */
 #if (TIMER_2_PRESCALER == 0)
TCCR2B = TCCR2B;   
 #elif (TIMER_2_PRESCALER == 1)
TCCR2B |= ((1 << CS20));
 #elif (TIMER_2_PRESCALER == 8)
TCCR2B |= ((1 << CS21));
 #elif (TIMER_2_PRESCALER == 32)
TCCR2B |= ((1 << CS21) | (1 << CS20));
 #elif (TIMER_2_PRESCALER == 64)
TCCR2B |= ((1 << CS22));
 #elif (TIMER_2_PRESCALER == 128)
TCCR2B |= ((1 << CS22) | (1 << CS20));
 #elif (TIMER_2_PRESCALER == 256)
TCCR2B |= ((1 << CS22) | (1 << CS21));
 #elif (TIMER_2_PRESCALER == 1024)
TCCR2B |= ((1 << CS22) | (1 << CS21) | (1 << CS20));
 #endif /* TIMER 2 PRESCALER */
#endif

OCR2A = two_ms_OCR2A; 
TCCR2A = 1 << COM2A1;
Compare_Interrupt_A_detected = 0;
}


uint8_t Timer_2::Get_Compare_Interrupt_A_detected()
{
   return (Compare_Interrupt_A_detected);
}
void Timer_2::Set_Compare_Interrupt_A_detected()
{
   Compare_Interrupt_A_detected = 1;
}
void Timer_2::Reset_Compare_Interrupt_A_detected()
{
   Compare_Interrupt_A_detected = 0;
}
