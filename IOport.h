/*
 * IOport.h
 *
 * Created: 31.07.2013 17:04:05
 *  Author: hillenbrand
 */ 


#ifndef IOPORT_H_
#define IOPORT_H_

#include <avr/io.h>

class Port
{
   public:
   Port();
   ~Port(){}
   enum Port_config_e
   {
      Port_In  = 0,
      Port_Out = 1
   };
   enum Port_pull_up_config_e
   {
      Pull_up_disabled = 0,
      Pull_up_enabled   = 1
         
   };
   enum Pin_out_value_e
   { /**/
      On   = 0,
      Off  = 1
   };
   enum Port_number_e
   { /**/
      Port_A = 0,
      Port_B = 1,
      Port_C = 2,
      Port_D = 3,
      port_num_max
   };

   void Set_Port_configuration(Port_number_e port_num, Port_config_e direction, Port_pull_up_config_e pull_up);
   void Set_Port_Pin (uint8_t Pin, Pin_out_value_e value);
   uint8_t Get_Port_Pin (uint8_t Pin);
   void Toggle_Port_Pin (uint8_t Pin);

  protected:
      
   private:
   uint8_t Port_num;
   void COPY_PORTs_TO_PORT_PTRs (uint8_t* port_ptr, uint8_t* ddr_ptr, uint8_t* pin_ptr, uint8_t port_num);
   void COPY_PORT_PTR_TO_PORT (uint8_t port_ptr, uint8_t port_num);
   void COPY_DDR_PTR_TO_DDR (uint8_t ddr_ptr, uint8_t port_num);
   void COPY_PIN_PTR_TO_PIN (uint8_t pin_ptr, uint8_t port_num);
      
};
extern Port Port_A_In;
extern Port Port_B_Out;
extern Port Port_C_Out;
extern Port Port_D_Out;

#endif /* IOPORT_H_ */
