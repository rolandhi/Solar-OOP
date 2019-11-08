/*
 * wire1.h
 *
 *  Created on: 21.12.2015
 *      Author: rolandh
 */

#ifndef WIRE1_H_
#define WIRE1_H_

#include <avr/io.h>
#include <util/delay.h>
#include "timer_0.h"
#include "IOport.h"
#define PinName uint8_t
#include "OneWireCRC.h"



#define MATCH_ROM           0x55
#define SKIP_ROM            0xCC
#define SEARCH_ROM          0xF0
#define READ_ROM            0x33
#define ROM_PRESENT         0xAA
#define READ_TEMPERATURE    0x22

#define CONVERT_T           0x44     // DS1820 commands
#define READ_SCRATCHPAD     0xBE
#define WRITE_SCRATCHPAD    0x4E
#define EE_WRITE            0x48
#define EE_RECALL           0xB8

#define  SEARCH_FIRST       0xFF     // start new search
#define  PRESENCE_ERR       0xFF
#define  DATA_ERR           0xFE
#define  LAST_DEVICE        0x00     // last device found
//       0x01 ... 0x40: continue searching

#define THERMOM_SCRATCHPAD_SIZE 9

#define ONEWIRE_ADDR_BYTES 8
#define ONE_WIRE_DEVICE_NUMOF 2

const int ONEWIRE_OK = 0;
const int ONEWIRE_FAIL_STUCK_LOW = 1;
const int ONEWIRE_SEARCH_ALL_DONE = 2;
const int ONEWIRE_SEARCH_INIT_FAIL = 3;
const int ONEWIRE_SEARCH_NOT_FOUND = 4;
const int ONEWIRE_SEARCH_COMP_BIT_ERR = 5;

#ifndef W1_PIN
#define W1_PIN PE0
#define W1_IN  PIND
#define W1_OUT PORTD
#define W1_DDR DDRD
#endif


class Wire1
{
public:
	Wire1();	~Wire1(){}   void Wire1_cyclic();
   void Get_rom_present(uint8_t* present, uint8_t* present1, uint8_t* present2, uint8_t* present3, uint8_t* present4, uint8_t* present5, uint8_t* present6, uint8_t* present7);
   uint8_t WIRE1_DEBUG1;
   uint8_t WIRE1_DEBUG2;
   uint8_t WIRE1_DEBUG3;
   uint8_t WIRE1_ROM_PRESENCE;
   uint8_t REQUEST_CONVERT;
   uint8_t CONVERSION_TIME_IS_OVER;
   uint8_t SCRATCHPAD_DATA[THERMOM_SCRATCHPAD_SIZE];
   uint8_t ROM_ADDRESS[ONEWIRE_ADDR_BYTES];
   int32_t TEMPERATURE[ONE_WIRE_DEVICE_NUMOF];

   const uint8_t DEVICE_ROM_ADDRESS[ONE_WIRE_DEVICE_NUMOF][ONEWIRE_ADDR_BYTES] =
   {
      {0x28,0x61,0xA3,0x29,0x05,0x00,0x00,0x41},
      {0x28,0xCE,0x5B,0x29,0x05,0x00,0x00,0xA1},
   };protected:private:
   uint8_t Processing();
   uint8_t Get_search_rom_done();
   uint8_t Wire1_reset();
   uint8_t Read_rom();
   uint8_t Rom_present();
   uint8_t Read_temperature(uint8_t* address, int32_t* temperature);
   void    Request_temperature_conversion(uint8_t* address);
   void    Reset_counters();    void writeBit(int bit);
#if 0
   int readBit();
   int init();
   int readByte();
   void writeByte(char data);
   unsigned char CRC(unsigned char* addr, unsigned char len);
   char* GetErrorStr(int errCode);

   // Clear the search state so that if will start from the beginning again.
   void reset_search();
   // Look for the next device.
   // Returns
   // ONEWIRE_OK if a new address has been returned.
   // ONEWIRE_SEARCH_ALL_DONE = all devices found
   // ONEWIRE_SEARCH_INIT_FAIL = failed to init
   // ONEWIRE_SEARCH_NOT_FOUND = no devices found
   // It might be a good idea to check the CRC to make sure you didn't
   // get garbage.  The order is deterministic. You will always get
   // the same devices in the same order.
   uint8_t search(uint8_t *newAddr);
#endif
   uint8_t COUNTER_15mus;
   uint8_t COUNTER_75mus;
   uint8_t COUNTER_480mus;
   uint8_t WIRE1_PORT_IS_HIGH;
   uint8_t WIRE1_CHECK_FOR_ROM_PRESENCE;
//   uint8_t CHECK_FOR_ROM_PRESENCE;
   uint8_t WIRE1_ROM_PORT_WAS_HIGH;
   uint8_t WIRE1_ROM_PORT_WAS_LOW;
   uint8_t WIRE1_OUT_PIN_STATUS;
   uint8_t WIRE1_ROM_SEARCH_DONE;
//   uint8_t WIRE1_ROM_SEARCH_DONE;

};
extern Wire1 WIRE1;extern void READ_ROM_PRESENT(uint8_t* ptr_to_second);#endif /* WIRE1_H_ */
