/*
 * dcm.h
 *
 * Created: 14.08.2013 11:41:49
 *  Author: hillenbrand
 */


#ifndef DCM_H_
#define DCM_H_

#include <avr/io.h>
#include "Usart.h"
#include "date_time.h"
#include "wire1.h"


#define Dcm_queue_offset_cmd     0
#define Dcm_queue_offset_sub_cmd 1
#define Dcm_queue_offset_data    2

class dcm
{
public:
	dcm();
	~dcm(){};
   void Dcm_cyclic(void);
protected:

private:

   uint8_t Dcm_check_for_new_in_msg(void);
   void Dcm_execute_command();
   uint8_t DCM_CMD;
   uint8_t DCM_SUB_CMD;
   uint8_t DCM_IN_QUEUE[10];
   uint8_t DCM_OUT_QUEUE[15];
   uint8_t DCM_IN_MSG_LENGTH;


};
extern dcm DCM;


#define DCM_E_POSITIVERESPONSE                        0x00
#define DCM_E_GENERALREJECT                           0x10
#define DCM_E_SERVICENOTSUPPORTED                     0x11
#define DCM_E_SUBFUNCTIONNOTSUPPORTED                 0x12
#define DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT   0x13
#define DCM_E_RESPONSETOOLONG                         0x14
#define DCM_E_BUSYREPEATREQUEST                       0x21
#define DCM_E_CONDITIONSNOTCORRECT                    0x22
#define DCM_E_REQUESTSEQUENCEERROR                    0x24
#define DCM_E_REQUESTOUTOFRANGE                       0x31
#define DCM_E_SECURITYACCESSDENIED                    0x33
#define DCM_E_INVALIDKEY                              0x35
#define DCM_E_EXCEEDNUMBEROFATTEMPTS                  0x36
#define DCM_E_REQUIREDTIMEDELAYNOTEXPIRED             0x37
#define DCM_E_GENERALPROGRAMMINGFAILURE               0x72
#define DCM_E_RESPONSEPENDING                         0x78
#define DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION  0x7E
#define DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION      0x7F
#define DCM_E_RPMTOOHIGH                              0x81
#define DCM_E_RPMTOOL                                 0x82
#define DCM_E_ENGINEISNOTRUNNING                      0x84
#define DCM_E_ENGINERUNTIMETOOLOW                     0x85
#define DCM_E_TEMPERATURETOOHIGH                      0x86
#define DCM_E_TEMPERATURETOOLOW                       0x87
#define DCM_E_VEHICLESPEEDTOOHIGH                     0x88
#define DCM_E_VEHICLESPEEDTOOLOW                      0x89
#define DCM_E_THROTTLE_PEDALTOOHIGH                   0x8A
#define DCM_E_THROTTLE_PEDALTOOLOW                    0x8B
#define DCM_E_TRANSMISSIONRANGENOTINNEUTRAL           0x8C
#define DCM_E_TRANSMISSIONRANGENOTINGEAR              0x8D
#define DCM_E_BRAKESWITCH_NOTCLOSED                   0x8F
#define DCM_E_SHIFTERLEVERNOTINPARK                   0x90
#define DCM_E_TORQUECONVERTERCLUTCHLOCKED             0x91
#define DCM_E_VOLTAGETOOHIGH                          0x92
#define DCM_E_VOLTAGETOOLOW                           0x93
#endif /* DCM_H_ */