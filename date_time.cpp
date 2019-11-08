/*
 * date_time.cpp
 *
 * Created: 04.08.2013 16:33:16
 *  Author: hillenbrand
 */

#include "date_time.h"

Date_time DATE_TIME;

Date_time::Date_time()
{
   COMPARE_INTERRUPTS_2_MS = 0;
}
void Date_time::Date_time_cyclic()
{
   if (TIMER_2.Get_Compare_Interrupt_A_detected() != 0)
   {
      TIMER_2.Reset_Compare_Interrupt_A_detected();
      COMPARE_INTERRUPTS_2_MS++;
      if (COMPARE_INTERRUPTS_2_MS == 491)
      {
         COMPARE_INTERRUPTS_2_MS = 0;
         Increment_date_time();
         if (WIRE1.REQUEST_CONVERT == true)
         {
            WIRE1.CONVERSION_TIME_IS_OVER = true;
         }
      }
   }
}

void Date_time::Increment_date_time()
{
   SECOND++;
   Port_B_Out.Toggle_Port_Pin(PIN7);
   Port_B_Out.Toggle_Port_Pin(PIN0);
   if (SECOND == 60)
   {

      SECOND = 0;
      MINUTE++;
      Port_B_Out.Toggle_Port_Pin(PIN1);

      if (SECOND == 60)
      {
         MINUTE = 0;
         HOUR++;
         if (HOUR == 24)
         {
            HOUR = 0;
            DAY++;
            if (DAY == 30)
            {
               DAY = 0;
               MONTH++;
            }
         }
      }
   }
   if (SECOND%5 == 0)
   {
      uint32_t temp;
      uint8_t temp_8;
/*      temp = (WIRE1.SCRATCHPAD_DATA[1]<<8) + (WIRE1.SCRATCHPAD_DATA[0]);
      temp *= (625);
      temp /= 100;
*/
      temp = WIRE1.TEMPERATURE[(SECOND%10)==0];
      SERIAL_IF.Write_char_to_OUT_queue((HOUR/10)+'0',false);
      SERIAL_IF.Write_char_to_OUT_queue((HOUR%10)+'0',false);
      SERIAL_IF.Write_char_to_OUT_queue(':',false);
      SERIAL_IF.Write_char_to_OUT_queue((MINUTE/10)+'0',false);
      SERIAL_IF.Write_char_to_OUT_queue((MINUTE%10)+'0',false);
      SERIAL_IF.Write_char_to_OUT_queue(':',false);
      SERIAL_IF.Write_char_to_OUT_queue((SECOND/10)+'0',false);
      SERIAL_IF.Write_char_to_OUT_queue((SECOND%10)+'0',false);
      SERIAL_IF.Write_char_to_OUT_queue('_',false);
      SERIAL_IF.Write_char_to_OUT_queue((temp/10000)+'0',false);
      temp %=10000;
      SERIAL_IF.Write_char_to_OUT_queue((temp/1000)+'0',false);
      temp %=1000;
      SERIAL_IF.Write_char_to_OUT_queue((temp/100)+'0',false);
      temp %=100;
      SERIAL_IF.Write_char_to_OUT_queue(',',false);
      SERIAL_IF.Write_char_to_OUT_queue((temp/10)+'0',false);
      temp %=10;
      SERIAL_IF.Write_char_to_OUT_queue((temp)+'0',false);
      SERIAL_IF.Write_char_to_OUT_queue('_',false);
      temp_8 = WIRE1.ROM_ADDRESS[0];
      SERIAL_IF.Write_char_to_OUT_queue(temp,false);
      temp_8 = WIRE1.ROM_ADDRESS[1];
      SERIAL_IF.Write_char_to_OUT_queue(temp,false);
      temp_8 = WIRE1.ROM_ADDRESS[2];
      SERIAL_IF.Write_char_to_OUT_queue(temp,false);
      temp_8 = WIRE1.ROM_ADDRESS[3];
      SERIAL_IF.Write_char_to_OUT_queue(temp,false);
      temp_8 = WIRE1.ROM_ADDRESS[4];
      SERIAL_IF.Write_char_to_OUT_queue(temp,false);
      temp_8 = WIRE1.ROM_ADDRESS[5];
      SERIAL_IF.Write_char_to_OUT_queue(temp,false);
      temp_8 = WIRE1.ROM_ADDRESS[6];
      SERIAL_IF.Write_char_to_OUT_queue(temp,false);
      temp_8 = WIRE1.ROM_ADDRESS[7];
      SERIAL_IF.Write_char_to_OUT_queue(temp,false);
      SERIAL_IF.Write_char_to_OUT_queue('_',false);
      SERIAL_IF.Write_char_to_OUT_queue(((SERIAL_IF.CLOCK/100000000000)%10)+'0',false);
      SERIAL_IF.Write_char_to_OUT_queue(((SERIAL_IF.CLOCK/10000000000)%10)+'0',false);
      SERIAL_IF.Write_char_to_OUT_queue(((SERIAL_IF.CLOCK/1000000000)%10)+'0',false);
      SERIAL_IF.Write_char_to_OUT_queue(((SERIAL_IF.CLOCK/100000000)%10)+'0',false);
      SERIAL_IF.Write_char_to_OUT_queue(((SERIAL_IF.CLOCK/1000000)%10)+'0',false);
      SERIAL_IF.Write_char_to_OUT_queue(((SERIAL_IF.CLOCK/100000)%10)+'0',false);
      SERIAL_IF.Write_char_to_OUT_queue(((SERIAL_IF.CLOCK/10000)%10)+'0',false);
      SERIAL_IF.Write_char_to_OUT_queue(((SERIAL_IF.CLOCK/1000)%10)+'0',false);
      SERIAL_IF.Write_char_to_OUT_queue(((SERIAL_IF.CLOCK/100)%10)+'0',false);
      SERIAL_IF.Write_char_to_OUT_queue(((SERIAL_IF.CLOCK/10)%10)+'0',false);
      SERIAL_IF.Write_char_to_OUT_queue(((SERIAL_IF.CLOCK/1)%10)+'0',true);
      SERIAL_IF.CLOCK = 0;
      WIRE1.REQUEST_CONVERT = false;
      WIRE1.WIRE1_DEBUG1 = 0;
   }
}

void Date_time::Get_time_date (uint8_t* year, uint8_t* month, uint8_t* day, uint8_t* hour, uint8_t* minute, uint8_t* second)
{
   *second = SECOND;
   *minute = MINUTE;
   *hour   = HOUR;
   *day    = DAY;
   *month  = MONTH;
   *year   = YEAR;
}

void Date_time::Set_minute(uint8_t minute)
{
   MINUTE = minute;
}
void Date_time::Set_second(uint8_t second)
{
   SECOND = second;
}

void SET_MINUTE(uint8_t* ptr_to_minute)
{
   DATE_TIME.Set_minute(ptr_to_minute[0]);
   SERIAL_IF.Write_char_to_OUT_queue((ptr_to_minute[0]/10)+'0',false);
   SERIAL_IF.Write_char_to_OUT_queue((ptr_to_minute[0]%10)+'0',true);
}
void SET_SECOND(uint8_t* ptr_to_second)
{
   DATE_TIME.Set_second(ptr_to_second[0]);
   SERIAL_IF.Write_char_to_OUT_queue((ptr_to_second[0]/10)+'0',false);
   SERIAL_IF.Write_char_to_OUT_queue((ptr_to_second[0]%10)+'0',true);
}
void READ_TIME(uint8_t* ptr_to_second)
{
   uint8_t second;
   uint8_t minute;
   uint8_t hour;
   uint8_t day;
   uint8_t month;
   uint8_t year;

   DATE_TIME.Get_time_date(&year, &month, &day, &hour, &minute, &second);
   SERIAL_IF.Write_char_to_OUT_queue((hour/10)+'0',false);
   SERIAL_IF.Write_char_to_OUT_queue((hour%10)+'0',false);
   SERIAL_IF.Write_char_to_OUT_queue(':',false);
   SERIAL_IF.Write_char_to_OUT_queue((minute/10)+'0',false);
   SERIAL_IF.Write_char_to_OUT_queue((minute%10)+'0',false);
   SERIAL_IF.Write_char_to_OUT_queue(':',false);
   SERIAL_IF.Write_char_to_OUT_queue((second/10)+'0',false);
   SERIAL_IF.Write_char_to_OUT_queue((second%10)+'0',true);
}
