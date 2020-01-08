/*
 * adc.c
 *
 *  Created on: Dec 31, 2019
 *      Author: SALAH
 */


#include "adc.h"

static workingMode current_mode = polling;
static volatile void (*g_functionPtr)(void) = NULL;
volatile uint16 g_digital_value = 0;
void ADC_init(adcConfig *a_adc_config){
	if(a_adc_config->adc_refrence == AREF){
		ADMUX &= (~(1<<REFS1)) & (~(1<<REFS0));
	}
	else if (a_adc_config->adc_refrence == AVCC){
		ADMUX &= (~(1<<REFS1));
		ADMUX |= (1<<REFS0);

	}

	else if(a_adc_config->adc_refrence == internal){
		ADMUX |= (1<<REFS1) | (1<<REFS0);
	}

	else{
		ADMUX &= (~(1<<REFS1)) & (~(1<<REFS0));
	}


	CLEAR_BIT(ADMUX , ADLAR); /*disable left shift*/
	/*
	 * 7 ADEN ADC enable 1
	 * 6 ADSC ADC start conversion 0
	 * 5 ADATE ADC auto trigger 0
	 * 4 ADIF ADC interrupt flag 1 (CLEAR) (ADIF is cleared by writing a logical one to the flag)
	 * 3 ADIE ADC interrupt enable (0 polling) (1 interrupt)
	 * 2 ADPS2:0 prescaler 011 prescaler = 8(sampling frequency)
	 * */
	ADCSRA = (1<<ADEN) | (1<<ADIF) | (1<<ADPS1) | (1<<ADPS0);
	if(a_adc_config->adc_mode == interrupt){
		current_mode = interrupt;
		SET_BIT(ADCSRA , ADIE);
	}
}

uint16 ADC_readChannel(uint8 channel_num){
	ADMUX = (ADMUX & 0xE0) | (channel_num & 0x07);	 /*select channel*/
	SET_BIT(ADCSRA,ADSC);	/*start conversion*/
	if(current_mode == polling){
		while(BIT_IS_CLEAR(ADCSRA,ADIF)); 	/*busy loop for polling mode*/
		SET_BIT(ADCSRA,ADIF); 	/*clear ADC flag*/
		return ADC;
	}
}

void ADC_setCallback(void (*a_functionPtr)(void)){
	g_functionPtr = a_functionPtr;
}


/* interrupt service routine for ADC*/
ISR(ADC_vect){
	if(g_functionPtr != NULL){
		(* g_functionPtr)();
	}
	g_digital_value = ADC;
}



