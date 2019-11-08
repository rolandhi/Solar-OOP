/*
 * Usart.h
 *
 * Created: 10.08.2013 14:03:07
 *  Author: Hillenbrand
 */


#ifndef USART_H_
#define USART_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "solar_OOP.h"

#define In_queue_length    10
#define Out_queue_length   25

class Usart
{
public:
	Usart();
	~Usart(){};
   void Write_char_to_IN_queue(uint8_t character);
   void Read_n_byte_of_IN_queue_by_position(uint8_t* ptr_to_queue, uint8_t queue_position, uint8_t number_of_bytes);
   uint8_t Read_next_byte_of_IN_queue(void);
   void Write_char_to_OUT_queue(uint8_t character, uint8_t is_last_character);
   uint8_t Message_in_IN_queue(void);
   void Usart_cyclic(void);
   uint32_t CLOCK;

protected:

private:
   uint8_t MSG_IN_QUEUE[In_queue_length];
   uint8_t WRITE_TO_IN_QUEUE_POINTER;
   uint8_t READ_FROM_IN_QUEUE_POINTER;
   uint8_t MSG_OUT_QUEUE[Out_queue_length];
   uint8_t WRITE_TO_OUT_QUEUE_POINTER;
   uint8_t READ_FROM_OUT_QUEUE_POINTER;
   uint8_t READ_STRING_COMPLETED;
   uint8_t OUT_QUEUE_IS_READY_FOR_SEND;
   void Set_Baud_Rate(uint32_t baud_rate);
   void Send_char_on_usart(void);
   uint8_t Read_next_byte_of_OUT_queue(void);
};

extern Usart SERIAL_IF;


#endif /* USART_H_ */
