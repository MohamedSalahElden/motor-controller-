/*
 * pwm.c
 *
 *  Created on: Jan 5, 2020
 *      Author: mohamed salah
 */

#include "pwm.h"
/*
 * responsible for start a PWM signal with the specified frequency and duty cycle
 * */
void PWM_start(s_pwmConfig * a_pwm_config){
	if(a_pwm_config->pwm_port == OC0){
		SET_BIT(DDRB , PB3); /*configure OC0 as output pin*/
		TCNT0 = 0; /*clear timer 0 counter register*/
		OCR0  = a_pwm_config->duty; /*set the duty cycle*/
		/*
		 * configure TCCR0 register
		 * 7- FOC0 	0	(active only in non PWM modes)
		 * 6- WGM00 1	(WGM01~0 = 11 for fast PWM mode )
		 * 5- COM01		(COM01~0 = a_pwm_config -> pwm_mode)
		 * 4- COM00
		 * 3- WGM01	1
		 * 2- CS02  	(CS02~0 = a_pwm_config -> pwm_prescaler)
		 * 1- CS01
		 * 0- CS00
		 * */
		TCCR0 = (1<<WGM00) | (1<<WGM01); /*configure timer1 to PWM mode*/
		TCCR0 = (TCCR0 & 0xCF) | ((a_pwm_config->pwm_mode & 0x03)<<4);
		TCCR0 = (TCCR0 & 0xF8) | (a_pwm_config->pwm_prescaler & 0x07);
	}
	else if(a_pwm_config->pwm_port == OC1A){
		SET_BIT(DDRD , PD5); /*configure OC1A as output pin*/
		ICR1  = a_pwm_config->freq;
		OCR1A = a_pwm_config->duty;
		/*set the compare mode for OC1A inverting / non */
		TCCR1A = (TCCR1A & 0x3F) | ((a_pwm_config->pwm_mode & 0x03)<<6);
		CLEAR_BIT(TCCR1A,FOC1A);
		SET_BIT(TCCR1A , WGM11);
		CLEAR_BIT(TCCR1A , WGM10);
		SET_BIT(TCCR1B , WGM12);
		SET_BIT(TCCR1B , WGM13);
		TCCR1B = (TCCR1B & 0xF8) | (a_pwm_config->pwm_prescaler & 0x07);
	}
	else if(a_pwm_config->pwm_port == OC1B){
		SET_BIT(DDRD , PD4); /*configure OC1B as output pin*/
		ICR1  = a_pwm_config->freq;
		OCR1B = a_pwm_config->duty;
		/*set the compare mode for OC1A inverting / non */
		TCCR1A = (TCCR1A & 0xCF) | ((a_pwm_config->pwm_mode & 0x03)<<4);
		CLEAR_BIT(TCCR1A,FOC1B);
		SET_BIT(TCCR1A , WGM11);
		CLEAR_BIT(TCCR1A , WGM10);
		SET_BIT(TCCR1B , WGM12);
		SET_BIT(TCCR1B , WGM13);
		TCCR1B = (TCCR1B & 0xF8) | (a_pwm_config->pwm_prescaler & 0x07);
	}
	else if(a_pwm_config->pwm_port == OC2){
		SET_BIT(DDRD , PD7); 	/*configure OC2 as output pin*/
		TCNT2 = 0; 				/*clear timer 0 counter register*/
		OCR2  = a_pwm_config->duty; 		/*set the duty cycle*/
		TCCR2 = (1<<WGM20) | (1<<WGM21); 	/*configure timer1 to PWM mode*/
		TCCR2 = (TCCR2 & 0xCF) | ((a_pwm_config->pwm_mode & 0x03)<<4);
		TCCR2 = (TCCR2 & 0xF8) | (a_pwm_config->pwm_prescaler & 0x07);
	}
}
/*
 * stop the timer1 PWM
 * */
void PWM_stop(e_pwmChannel ch){
	switch(ch){
	case OC0:
		TCCR0 = (TCCR0 & 0xF8) | (0x00);
		break;
	case OC1A:
	case OC1B:
		TCCR1B = (TCCR1B & 0xF8) | (0x00);
		break;
	case OC2:
		TCCR2 = (TCCR2 & 0xF8) | (0x00);
		break;
	default:
		break;
	}
}

void PWM_change_DutyCycle(e_pwmChannel ch , uint16 duty){
	switch(ch){
	case OC0:
		OCR0  = duty; /*set the duty cycle*/
		break;
	case OC1A:
		OCR1A = duty;
		break;
	case OC1B:
		OCR1B = duty;
		break;
	case OC2:
		OCR2 = duty;
		break;
	default:
		break;
	}
}


