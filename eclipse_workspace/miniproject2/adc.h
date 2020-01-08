/*
 * adc.h
 *
 *  Created on: Dec 31, 2019
 *      Author: SALAH
 */

#ifndef ADC_H_
#define ADC_H_

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

/*--------- ADC working modes ---------------- */
#ifndef NULL
#define NULL ((void *)0)
#endif

typedef enum{
	polling , interrupt
}workingMode;

/*--------- source select definition ---------------- */
typedef enum{
	AREF , AVCC , internal
}refrence;

typedef struct {
	workingMode adc_mode;
	refrence adc_refrence;
}adcConfig;

/*
 * ADC_MODE represents the ADC modes either
 * 	- POLLING (busy loop keeps running till the ADC complete converting)
 * 	- INTERRUPT (when ADC complete converting it calls ISR that updates the e_adc_reading)
 * */

extern volatile uint16 g_digital_value;


void ADC_init(adcConfig *a_adc_config);
/*
 * function name  	: ADC_readChannel
 * Description 		: this function responsible to return the value of ADC reading in case of polling mode
 * 												  return 1 if ADC reading is ready to use (that the ADC reading stored in e_adc_reading) (INTERRUPT mode)
 * 												  		 0 in data is not ready yet (INTERRUPT mode)
 * 												usage in INTERRUPT mode
 * 						if(ADC_readChannel(1)){
 * 							temp = e_adc_reading;
 * 							do something
 * 						}
 * 	args 			: channel_num is an integer 0~7 represents the channel number you want it's digital reading
 * */

uint16 ADC_readChannel(uint8 channel_num);
void ADC_setCallback(void (*a_functionPtr)(void));
#endif /* ADC_H_ */
