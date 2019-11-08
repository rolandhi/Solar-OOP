/*
 * solar_OOP.h
 *
 * Created: 31.07.2013 17:01:18
 *  Author: hillenbrand
 */


#ifndef SOLAR_OOP_H_
#define SOLAR_OOP_H_

#define F_RC 8000*1000UL
#define CLOCK_PRESCALER 1
#define F_CPU_CLOCK (F_RC / CLOCK_PRESCALER)

#include <avr/io.h>
#include <avr/wdt.h>
#include "date_time.h"
#include "IOport.h"
#include "timer_2.h"
#include "Usart.h"
#include "dcm.h"
#include "wire1.h"

//#define True  1
//#define False 0

class Solar
{
public:
   uint8_t test;

   Solar();
	~Solar() {}
protected:

private:
};



#endif /* SOLAR_OOP_H_ */
