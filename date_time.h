/*
 * date_time.h
 *
 * Created: 04.08.2013 16:33:49
 *  Author: hillenbrand
 */ 


#ifndef DATE_TIME_H_
#define DATE_TIME_H_

#include <avr/io.h>
#include "timer_2.h"
#include "IOport.h"
#include "solar_OOP.h"
#include "Usart.h"


class Date_time
{
public:
	Date_time();
	~Date_time(){}
   void Date_time_cyclic();
   void Get_time_date (uint8_t* year, uint8_t* month, uint8_t* day, uint8_t* hour, uint8_t* minute, uint8_t* second);
   void Set_minute(uint8_t minute);
   void Set_second(uint8_t second);
   
protected:
	
private:
   uint16_t COMPARE_INTERRUPTS_2_MS;
   uint8_t  SECOND;
   uint8_t  MINUTE;
   uint8_t  HOUR;
   uint8_t  DAY;
   uint8_t  MONTH;
   uint8_t  YEAR;
   void Increment_date_time();
};
extern void SET_MINUTE(uint8_t* ptr_to_minute);
extern void SET_SECOND(uint8_t* ptr_to_second);
extern void READ_TIME (uint8_t* ptrto_queue);

extern    Date_time DATE_TIME;
#endif /* DATE_TIME_H_ */