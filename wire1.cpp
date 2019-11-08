/*
 * wire1.cpp
 *
 *  Created on: 21.12.2015
 *      Author: rolandh
 */

#include "wire1.h"

Wire1 WIRE1;
Wire1::Wire1()
{
   COUNTER_15mus                 = 0;
   COUNTER_75mus                 = 0;
   COUNTER_480mus                = 0;
   WIRE1_PORT_IS_HIGH            = false;
   WIRE1_CHECK_FOR_ROM_PRESENCE  = false;
   WIRE1_ROM_PORT_WAS_HIGH       = false;
   WIRE1_ROM_PORT_WAS_LOW        = false;
   WIRE1_ROM_PRESENCE            = false;
   WIRE1_ROM_SEARCH_DONE         = false;
   REQUEST_CONVERT               = false;
   CONVERSION_TIME_IS_OVER       = false;
}

void Wire1:: Reset_counters()
{
   COUNTER_15mus                 = 0;
   COUNTER_75mus                 = 0;
   COUNTER_480mus                = 0;
   WIRE1_CHECK_FOR_ROM_PRESENCE  = false;
   WIRE1_ROM_PORT_WAS_HIGH       = false;
   WIRE1_ROM_PORT_WAS_LOW        = false;
   WIRE1_ROM_PRESENCE            = false;
   WIRE1_ROM_SEARCH_DONE         = false;
//   WIRE1_DEBUG1                  = 0;
   WIRE1_DEBUG2                  = 0;
   WIRE1_DEBUG3                  = 0;
}
uint8_t Wire1_reset()
{
   uint8_t ret_val = true;
   return (ret_val);
}

uint8_t Wire1::Rom_present()
{
   uint8_t ret_val = true;
   WIRE1_ROM_PRESENCE = ONE_WIRE_CRC.reset();
   return (ret_val);
}

uint8_t Wire1::Read_rom()
{
   WIRE1_ROM_SEARCH_DONE = ONE_WIRE_CRC.search(&ROM_ADDRESS[0]);
   if (OneWireCRC::crc8(&ROM_ADDRESS[0], ADDRESS_CRC_BYTE) == ROM_ADDRESS[ADDRESS_CRC_BYTE])   /* check address CRC is valid */
   {
      WIRE1_ROM_SEARCH_DONE |= 0x10;
   }
   return (1);
}

void Wire1::Request_temperature_conversion(uint8_t* address)
{
   ONE_WIRE_CRC.reset();                // reset device
   ONE_WIRE_CRC.matchROM(address);      // select which device to talk to
   ONE_WIRE_CRC.writeByte(CONVERT_T);
   REQUEST_CONVERT = true;
   CONVERSION_TIME_IS_OVER = 0;
}

uint8_t Wire1::Read_temperature(uint8_t* address, int32_t* temperature)
{
   int16_t scratch_val;
   int32_t temp;
   ONE_WIRE_CRC.reset();                // reset device
   ONE_WIRE_CRC.matchROM(address);      // select which device to talk to
   ONE_WIRE_CRC.writeByte(READ_SCRATCHPAD);    // read Scratchpad
   WIRE1_DEBUG2 ++;
   CONVERSION_TIME_IS_OVER = 2;
   for (int i = 0; i < THERMOM_SCRATCHPAD_SIZE; i++)
   {
       // we need all bytes which includes CRC check byte
      SCRATCHPAD_DATA[i] = ONE_WIRE_CRC.readByte();
   }
   scratch_val = (SCRATCHPAD_DATA[1]<<8) + (SCRATCHPAD_DATA[0]);
   temp = ((int32_t)scratch_val) * ((int32_t)625);
   temp /= ((int32_t)100);
   *temperature = temp;
}

void Wire1::Wire1_cyclic()
{
   if (TIMER_0.Get_Compare_Interrupt_A_detected() != 0)
   {
      TIMER_0.Reset_Compare_Interrupt_A_detected();
      COUNTER_15mus++;
      if ((COUNTER_15mus%5) == 0)
      {
         if (COUNTER_75mus == 0)
         {
            COUNTER_75mus++;
         }
      }
      if ((COUNTER_15mus % 32) == 0)
      {
         if (COUNTER_480mus < 3)
         {
            COUNTER_480mus++;
         }
         COUNTER_15mus = 0;
      }
   }
   switch (Processing())
   {
   case ROM_PRESENT:
   {
      Rom_present();
      break;
   }
   case READ_ROM:
   {
      Read_rom();
      break;
   }
   case READ_TEMPERATURE:
   {
      if (REQUEST_CONVERT == 0)
      {
         Request_temperature_conversion((uint8_t*)(&DEVICE_ROM_ADDRESS[0][0]));
         Request_temperature_conversion((uint8_t*)(&DEVICE_ROM_ADDRESS[1][0]));
      }
      else
      {
         if (CONVERSION_TIME_IS_OVER == 1)
         {
            Read_temperature((uint8_t*)(&DEVICE_ROM_ADDRESS[0][0]), &TEMPERATURE[0]);
            Read_temperature((uint8_t*)(&DEVICE_ROM_ADDRESS[1][0]), &TEMPERATURE[1]);
         }
      }
      break;
   }
   default:
   {
      break;
   }
   }
}

void  Wire1::Get_rom_present(uint8_t* present, uint8_t* present1, uint8_t* present2, uint8_t* present3, uint8_t* present4, uint8_t* present5, uint8_t* present6, uint8_t* present7)
{
   *present  = ROM_ADDRESS[7];
   *present1 = ROM_ADDRESS[6];
   *present2 = ROM_ADDRESS[5];
   *present3 = ROM_ADDRESS[4];
   *present4 = ROM_ADDRESS[3];
   *present5 = ROM_ADDRESS[2];
   *present6 = ROM_ADDRESS[1];
   *present7 = ROM_ADDRESS[0];

   /*
   *present  = SCRATCHPAD_DATA[7];
   *present1 = WIRE1_DEBUG2;
   *present2 = SCRATCHPAD_DATA[8];
   *present3 = SCRATCHPAD_DATA[4];
   *present4 = SCRATCHPAD_DATA[3];
   *present5 = SCRATCHPAD_DATA[2];
   *present6 = SCRATCHPAD_DATA[1];
   *present7 = SCRATCHPAD_DATA[0];
   *present  = WIRE1_ROM_PRESENCE;
   *present1 = WIRE1_ROM_SEARCH_DONE;
   *present2 = WIRE1_DEBUG2;
   *present3 = WIRE1_DEBUG3;
   *present6 = WIRE1_ROM_SEARCH_DONE;
   *present1 = WIRE1_PORT_IS_HIGH           ;
   *present2 = WIRE1_CHECK_FOR_ROM_PRESENCE ;
   *present3 = WIRE1_OUT_PIN_STATUS       ;
   *present4 = WIRE1_ROM_PORT_WAS_HIGH      ;
   *present5 = WIRE1_ROM_PORT_WAS_LOW       ;
   *present6 = Port_A_In.Get_Port_Pin(PIN7) == Port::On;
*/
/*
   *present4 = WIRE1_DEBUG2      ;
   *present5 = COUNTER_480mus       ;
*/
}

void READ_ROM_PRESENT(uint8_t* ptr_to_second)
{
   uint8_t l_rom_present;
   uint8_t l_rom_present1;
   uint8_t l_rom_present2;
   uint8_t l_rom_present3;
   uint8_t l_rom_present4;
   uint8_t l_rom_present5;
   uint8_t l_rom_present6;
   uint8_t l_rom_present7;
   WIRE1.Get_rom_present(&l_rom_present, &l_rom_present1, &l_rom_present2, &l_rom_present3, &l_rom_present4, &l_rom_present5, &l_rom_present6, &l_rom_present7);
   SERIAL_IF.Write_char_to_OUT_queue(l_rom_present  /*+ '0'*/,false);
   SERIAL_IF.Write_char_to_OUT_queue(l_rom_present1 /*+ '0'*/,false);
   SERIAL_IF.Write_char_to_OUT_queue(l_rom_present2 /*+ '0'*/,false);
   SERIAL_IF.Write_char_to_OUT_queue(l_rom_present3 /*+ '0'*/,false);
   SERIAL_IF.Write_char_to_OUT_queue(l_rom_present4 /*+ '0'*/,false);
   SERIAL_IF.Write_char_to_OUT_queue(l_rom_present5 /*+ '0'*/,false);
   SERIAL_IF.Write_char_to_OUT_queue(l_rom_present6 /*+ '0'*/,false);
   SERIAL_IF.Write_char_to_OUT_queue(l_rom_present7 /*+ '0'*/,true);
}

uint8_t Wire1::Processing()
{
   uint8_t ret_val = 0;
   if (WIRE1_ROM_PRESENCE == false)
   {
      ret_val = ROM_PRESENT;
   }
  else if (WIRE1_ROM_SEARCH_DONE == false)
  {
     ret_val = READ_ROM;
  }
  else if ((WIRE1_DEBUG1 < 8) || ((CONVERSION_TIME_IS_OVER != 0) && (CONVERSION_TIME_IS_OVER != 2)))
  {
     ret_val = READ_TEMPERATURE;
     WIRE1_DEBUG1 ++;
  }
   return ret_val;
}
