/*
 * IOport.cpp
 *
 * Created: 31.07.2013 17:03:38
 *  Author: hillenbrand
 */
#include "IOport.h"

   Port Port_A_In;
   Port Port_B_Out;
   Port Port_C_Out;
   Port Port_D_Out;


Port::Port()
{
}
void Port::COPY_PORTs_TO_PORT_PTRs (uint8_t* port_ptr, uint8_t* ddr_ptr, uint8_t* pin_ptr, uint8_t port_num)
{
   switch (port_num)
   {
      case Port_A:
      *port_ptr = PORTA;
      *ddr_ptr  = DDRA;
      *pin_ptr  = PINA;
      break;
      case Port_B:
      *port_ptr = PORTB;
      *ddr_ptr  = DDRB;
      *pin_ptr  = PINB;
      break;
      case Port_C:
      *port_ptr = PORTC;
      *ddr_ptr  = DDRC;
      *pin_ptr  = PINC;
      break;
      case Port_D:
      *port_ptr = PORTD;
      *ddr_ptr  = DDRD;
      *pin_ptr  = PIND;
      break;
      default:
      *port_ptr = PORTA;
      *ddr_ptr  = DDRA;
      *pin_ptr  = PINA;
      break;

   }

}
void Port::COPY_DDR_PTR_TO_DDR (uint8_t ddr_ptr, uint8_t port_num)
{
   switch (port_num)
   {
      case Port_A:
      {
         DDRA  = ddr_ptr;
         break;
      }
      case Port_B:
      {
         DDRB  = ddr_ptr;
         break;
      }
      case Port_C:
      {
         DDRC  = ddr_ptr;
         break;
      }
      case Port_D:
      {
         DDRD  = ddr_ptr;
         break;
      }
      default:
      {
         break;
      }
   }
}
void Port::COPY_PORT_PTR_TO_PORT (uint8_t port_ptr, uint8_t port_num)
{
   switch (port_num)
   {
      case Port_A:
      {
         PORTA = port_ptr;
         break;
      }
      case Port_B:
      {
         PORTB = port_ptr;
         break;
      }
      case Port_C:
      {
         PORTC = port_ptr;
         break;
      }
      case Port_D:
      {
         PORTD = port_ptr;
         break;
      }
      default:
      {
         break;
      }
   }
}
void Port::COPY_PIN_PTR_TO_PIN (uint8_t pin_ptr, uint8_t port_num)
{
   switch (port_num)
   {
      case Port_A:
      {
         PINA  = pin_ptr;
         break;
      }
      case Port_B:
      {
         PINB  = pin_ptr;
         break;
      }
      case Port_C:
      {
         PINC  = pin_ptr;
         break;
      }
      case Port_D:
      {
         PIND  = pin_ptr;
         break;
      }
      default:
      {
         break;
      }
   }
}
void Port::Set_Port_configuration(Port_number_e port_num, Port_config_e direction, Port_pull_up_config_e pull_up)
{
   uint8_t  PORT_ptr;
   uint8_t  DDR_ptr;
   uint8_t  PIN_ptr;
   COPY_PORTs_TO_PORT_PTRs (&PORT_ptr, &DDR_ptr, &PIN_ptr, port_num);
   if (direction == Port_Out)
   {
      DDR_ptr  = (1 << DD0) | (1 << DD1) | (1 << DD2) | (1 << DD3) | (1 << DD4) | (1 << DD5) | (1 << DD6) | (1 << DD7);
      if (pull_up == Pull_up_enabled)
      {
         PORT_ptr = (1 << PIN0)  | (1 << PIN1)  | (1 << PIN2)  | (1 << PIN3)  | (1 << PIN4)  | (1 << PIN5)  | (1 << PIN6)  | (1 << PIN7);
      }
   }
   if (direction == Port_In)
   {
      DDR_ptr = 0;
   }
   COPY_PORT_PTR_TO_PORT (PORT_ptr, port_num);
   COPY_DDR_PTR_TO_DDR (DDR_ptr, port_num);
   Port_num = port_num;
}

void Port::Set_Port_Pin(/*Port_number_e port_num,*/ uint8_t Pin, Pin_out_value_e value)
{
   uint8_t  PORT_ptr;
   uint8_t  DDR_ptr;
   uint8_t  PIN_ptr;
   uint8_t  port_num;
   port_num = this->Port_num;
   COPY_PORTs_TO_PORT_PTRs (&PORT_ptr, &DDR_ptr, &PIN_ptr, port_num);
   if (port_num < port_num_max)
   {
      if (value == On)
      {  /* ~1111 = 0000 | 0100 = 0100 => ~0100 = 1011 */
         /* ~0101 = 1010 | 0100 = 1110 => ~1110 = 0001 */
         PORT_ptr = (~((~PORT_ptr) | (1<<Pin)));
      }
      else
      {
         if (value == Off)
         {
            PORT_ptr |= (1<<Pin);
         }
      }
   }
   COPY_PORT_PTR_TO_PORT (PORT_ptr, port_num);
}
uint8_t Port::Get_Port_Pin(uint8_t Pin)
{
   uint8_t  PORT_ptr;
   uint8_t  DDR_ptr;
   uint8_t  PIN_ptr;
   uint8_t  port_num;
   port_num = this->Port_num;
   COPY_PORTs_TO_PORT_PTRs (&PORT_ptr, &DDR_ptr, &PIN_ptr, port_num);
   return (((~PIN_ptr) & (1 << Pin)) != 0);
}

void Port::Toggle_Port_Pin (uint8_t Pin)
{
   uint8_t  PIN_ptr;
   uint8_t  port_num;
   port_num = this->Port_num;
   if (port_num < port_num_max)
   {
      PIN_ptr = (1<<Pin);
      COPY_PIN_PTR_TO_PIN(PIN_ptr, port_num);
   }

}
