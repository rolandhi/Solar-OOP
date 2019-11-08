/*
 * Usart_1.cpp
 *
 * Created: 10.08.2013 14:02:52
 *  Author: Hillenbrand
 */
#include "Usart.h"

Usart SERIAL_IF;

ISR(USART0_RX_vect)
{
   uint8_t buffer;
   buffer = UDR0;
   SERIAL_IF.Write_char_to_IN_queue(buffer);
}

ISR(USART0_UDRE_vect)
{
}

ISR(USART0_TX_vect)
{
}

Usart::Usart()
{
   Set_Baud_Rate(38400);
   UCSR0B |= RXCIE0;
   WRITE_TO_IN_QUEUE_POINTER   = 0;
   READ_FROM_IN_QUEUE_POINTER  = 0;
   WRITE_TO_OUT_QUEUE_POINTER  = 0;
   READ_FROM_OUT_QUEUE_POINTER = 0;
   READ_STRING_COMPLETED       = false;
   OUT_QUEUE_IS_READY_FOR_SEND = false;
}
void Usart::Set_Baud_Rate(uint32_t baud_rate)
{
   uint16_t ubrr = ((F_CPU_CLOCK/16/baud_rate)-1);
   uint16_t ubrr2x =	((F_CPU_CLOCK/8/baud_rate)-1);
   uint32_t rbaund = (F_CPU_CLOCK/16/(ubrr+1));
   uint32_t rbaund2x = (F_CPU_CLOCK/8/(ubrr2x+1));
   uint32_t err1;
   uint32_t err2;
   uint16_t ubrrToUse;

   if(baud_rate > rbaund)
   err1 = (baud_rate - rbaund)*1000/baud_rate;
   else
   err1 = (rbaund - baud_rate)*1000/rbaund;

   if(baud_rate > rbaund2x)
   err2 = (baud_rate - rbaund2x)*1000/baud_rate;
   else
   err2 = (rbaund2x - baud_rate)*1000/rbaund2x;

   if(err1 > err2)
   {
   /* Enable receiver and transmitter*/
      UCSR0B = (1<<RXEN0)|(1<<TXEN0);
      ubrrToUse = ubrr2x;
   }
   else
   {
      UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
      ubrrToUse = ubrr;
   }
   /* Set baud rate*/
   UBRR0H = (unsigned char)(ubrrToUse>>8);
   UBRR0L = (unsigned char)ubrrToUse;
   /* Set frame format: 8data, 2stop bit*/
   UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void Usart::Write_char_to_IN_queue(uint8_t character)
{
   if (READ_STRING_COMPLETED == false)
   {
      if (   (character != '\r')
          && (character != '\n')
          && (WRITE_TO_IN_QUEUE_POINTER < (In_queue_length-1))
         )
      {
         MSG_IN_QUEUE[WRITE_TO_IN_QUEUE_POINTER++]=character;
      }
      else
      {
         MSG_IN_QUEUE[WRITE_TO_IN_QUEUE_POINTER] = '\0';
         WRITE_TO_IN_QUEUE_POINTER  = 0;
         READ_STRING_COMPLETED      = true;
      }
   }
}
uint8_t Usart::Read_next_byte_of_IN_queue(void)
{
   uint8_t ret_val = '\0';
   if (READ_FROM_IN_QUEUE_POINTER < (In_queue_length - 1))
   {
      ret_val = MSG_IN_QUEUE[READ_FROM_IN_QUEUE_POINTER++];
      if (ret_val == '\0')
      {
         READ_STRING_COMPLETED = false; /* release IN QUEUE*/
         READ_FROM_IN_QUEUE_POINTER = 0;
      }
   }
   else
   {
      READ_STRING_COMPLETED = false; /* release IN QUEUE*/
      READ_FROM_IN_QUEUE_POINTER = 0;
   }
   return (ret_val);
}
void Usart::Write_char_to_OUT_queue(uint8_t character, uint8_t is_last_character)
{
   if (   (WRITE_TO_OUT_QUEUE_POINTER < (Out_queue_length - 2 ))
      )
   {
      MSG_OUT_QUEUE[WRITE_TO_OUT_QUEUE_POINTER++] = character;
   }
   if (is_last_character != false)
   {
      MSG_OUT_QUEUE[WRITE_TO_OUT_QUEUE_POINTER]=0x0D;
      WRITE_TO_OUT_QUEUE_POINTER = 0;
      OUT_QUEUE_IS_READY_FOR_SEND = true;
   }
}
uint8_t Usart::Read_next_byte_of_OUT_queue(void)
{
   uint8_t character = '0';
   if (READ_FROM_OUT_QUEUE_POINTER < Out_queue_length - 1)
   {
      character = MSG_OUT_QUEUE[READ_FROM_OUT_QUEUE_POINTER++];
      if (character == 0x0D)
      {
         READ_FROM_OUT_QUEUE_POINTER = 0;
         OUT_QUEUE_IS_READY_FOR_SEND = false;
      }
   }
   else
   {
      READ_FROM_OUT_QUEUE_POINTER = 0;
      OUT_QUEUE_IS_READY_FOR_SEND = false;
   }
   return (character);
}
void Usart::Send_char_on_usart(void)
{
   uint8_t to_send_char;
   while (!(UCSR0A & (1<<UDRE0)))  /* wait for sending slot*/
   {
   }
   /* Globally Disable interrupts */
   cli();
   to_send_char = Read_next_byte_of_OUT_queue();     /* transmit the character on USART */
   UDR0 = to_send_char;
   /* Globally Enable interrupts */
   sei();

}

void Usart::Usart_cyclic(void)
{

   if (OUT_QUEUE_IS_READY_FOR_SEND == true)
   {
      Send_char_on_usart();
   }
}

uint8_t Usart::Message_in_IN_queue(void)
{
   return (READ_STRING_COMPLETED);
}

void Usart::Read_n_byte_of_IN_queue_by_position(uint8_t* ptr_to_queue, uint8_t queue_position, uint8_t number_of_bytes)
{

}
