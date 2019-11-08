/*
 * solar_OOP.cpp
 *
 * Created: 31.07.2013 16:57:26
 *  Author: hillenbrand
 */

#include "solar_OOP.h"

Solar  SOLAR;

Solar::Solar()
{
   test = 0;
   wdt_enable(WDTO_60MS);
#if (CLOCK_PRESCALER != 0)
/*CLKPR = (1 << CLKPCE);    enable clock prescaler */
/* CLKPR |= (1 << CLKPCE) & ~((1 << CLKPS3) | (1 << CLKPS2) | (1 << CLKPS1) | (1 << CLKPS0));  remove preconfigured scale which is defined by fuse */
 #if (CLOCK_PRESCALER == 1)
CLKPR = (1 << CLKPCE);
 #elif (CLOCK_PRESCALER == 2)
CLKPR = (1 << 7) | ((1 << CLKPS0));
 #elif (CLOCK_PRESCALER == 4)
CLKPR = (1 << CLKPCE) | ((1 << CLKPS1));
 #elif (CLOCK_PRESCALER == 8)
CLKPR = (1 << CLKPCE) | ((1 << CLKPS1) | (1 << CLKPS0));
 #elif (CLOCK_PRESCALER == 16)
CLKPR = (1 << CLKPCE) | ((1 << CLKPS2));
 #elif (CLOCK_PRESCALER == 32)
CLKPR = (1 << CLKPCE) | ((1 << CLKPS2) | (1 << CLKPS0));
 #elif (CLOCK_PRESCALER == 64)
CLKPR = (1 << CLKPCE) | ((1 << CLKPS2) | (1 << CLKPS1));
 #elif (CLOCK_PRESCALER == 128)
CLKPR = (1 << CLKPCE) | ((1 << CLKPS2) | (1 << CLKPS1) | (1 << CLKPS0));
 #elif (CLOCK_PRESCALER == 256)
CLKPR = (1 << CLKPCE) | ((1 << CLKPS3));
 #endif /*CLOCK PRESCALER*/
#else
 #error "CLOCK_PRESCALER different from 0 has to be defined"
#endif /*CLOCK PRESCALER*/
test = CLKPR;
}



int main(void)
{


   Port_A_In.Set_Port_configuration(Port::Port_A, Port::Port_In,  Port::Pull_up_disabled);
   Port_B_Out.Set_Port_configuration(Port::Port_B, Port::Port_Out, Port::Pull_up_enabled);
   Port_C_Out.Set_Port_configuration(Port::Port_C, Port::Port_Out, Port::Pull_up_enabled);
   SERIAL_IF.CLOCK = 0;
   sei();
   while(1)
   {
      wdt_reset();
      SERIAL_IF.CLOCK++;
      DATE_TIME.Date_time_cyclic();
      WIRE1.Wire1_cyclic();
      SERIAL_IF.Usart_cyclic();
      DCM.Dcm_cyclic();
   }
}
