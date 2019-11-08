/*
 * dcm.cpp
 *
 * Created: 14.08.2013 11:41:31
 *  Author: hillenbrand
 */

#include "dcm.h"

   typedef struct
   {
      uint8_t CMD_COMMAND;
      uint8_t CMD_SUB_COMMAND;
      void (*PTR_CMD_FUNCTION_CALL)(uint8_t *queue);
      uint8_t CMD_LENGTH;
   }command_array_t;

   #define Write_by_id()                        0x2E

   #define Write_minute_id()                    0x22
   #define Write_minute_length()                0x03

   #define Write_hour_id()                      0x23
   #define Write_hour_length()                  0x03


   #define Read_by_id()                         0x22

   #define Read_time()                          0x20
   #define Read_time_length()                   0x02

   #define Read_rom_present()                   0x30
   #define Read_rom_present_length()            0x02

dcm DCM;
const command_array_t COMMAND_ARRAY[]=
{
   {
      Write_by_id(),
      Write_minute_id(),
      &SET_MINUTE,
      Write_minute_length(),
   }
   ,
   {
      Write_by_id(),
      Write_hour_id(),
      &SET_SECOND,
      Write_hour_length(),
   }
   ,
   {
      Read_by_id(),
      Read_time(),
      &READ_TIME,
      Read_time_length(),

   },
   {
      Read_by_id(),
      Read_rom_present(),
      &READ_ROM_PRESENT,
      Read_rom_present_length(),

   }
};
const uint8_t Command_array_length = sizeof (COMMAND_ARRAY) / sizeof (COMMAND_ARRAY[0]);

dcm::dcm()
{
}

uint8_t dcm::Dcm_check_for_new_in_msg(void)
{
   uint8_t ret_val = false;
   ret_val = SERIAL_IF.Message_in_IN_queue();
   //ret_val = true;
   return (ret_val);
}

void dcm::Dcm_execute_command()
{
   uint8_t counter = 0;
   uint8_t command_index = 0xFF;
   while (   (command_index == 0xFF)
          && (counter < Command_array_length)
         )
   {
      if (DCM_CMD == COMMAND_ARRAY[counter].CMD_COMMAND)
      {
         if (DCM_SUB_CMD == COMMAND_ARRAY[counter].CMD_SUB_COMMAND)
         {
            if (DCM_IN_MSG_LENGTH == COMMAND_ARRAY[counter].CMD_LENGTH)
            {
               command_index = counter;
            }
         }
      }
      counter++;
   }
   if (command_index < Command_array_length)
   {
//      SERIAL_IF.Write_char_to_OUT_queue(DCM_CMD + 0x40,false);
//      SERIAL_IF.Write_char_to_OUT_queue(DCM_SUB_CMD,false);
      COMMAND_ARRAY[command_index].PTR_CMD_FUNCTION_CALL(&DCM_IN_QUEUE[Dcm_queue_offset_data]);
   }
   else
   {
      SERIAL_IF.Write_char_to_OUT_queue(0x7F,false);
      SERIAL_IF.Write_char_to_OUT_queue(DCM_CMD,false);
      SERIAL_IF.Write_char_to_OUT_queue(DCM_SUB_CMD,false);
      SERIAL_IF.Write_char_to_OUT_queue(DCM_IN_MSG_LENGTH,false);
      SERIAL_IF.Write_char_to_OUT_queue(DCM_E_SERVICENOTSUPPORTED,true);
   }

}

void dcm::Dcm_cyclic(void)
{
   uint8_t queue_byte = 0;
   if (Dcm_check_for_new_in_msg() != false)
   {
      DCM_IN_MSG_LENGTH = 0;
      while ((queue_byte = SERIAL_IF.Read_next_byte_of_IN_queue()) != '\0')
      {
         DCM_IN_QUEUE[DCM_IN_MSG_LENGTH++] = queue_byte; /* in msg length correction is not needed*/
      }
      if (DCM_IN_MSG_LENGTH != 0)
      {
         queue_byte = 0;
         DCM_CMD = DCM_IN_QUEUE[queue_byte++];
         if (DCM_IN_MSG_LENGTH > Dcm_queue_offset_sub_cmd)
         {
            DCM_SUB_CMD = DCM_IN_QUEUE[queue_byte++];
         }
         Dcm_execute_command();
      }
   }
}