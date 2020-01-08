/*
 * pwm.h
 *
 *  Created on: Jan 5, 2020
 *      Author: ahmed
 */

#ifndef PWM_H_
#define PWM_H_

#ifdef TIMER1_H_
#warning "PWM module uses timer1 to operate it will produce a runtime error operating these modules together "
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

/*--------------------------include utility files------------------------------*/
#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"
/*---------------------------prescaler data type-------------------------------*/

#ifndef PRESCALER
#define PRESCALER
typedef enum {
	CLK_OFF = 0,
	CLK_1 ,
	CLK_8 ,
	CLK_64 ,
	CLK_256 ,
	CLK_1024 ,
	EX_T1_FALLING ,
	EX_T1_RISING
}prescaler;
#endif

typedef enum{
	non_inverting=2 , inverting
}e_pwmMode;

typedef enum{
	OC0 , OC1A , OC1B , OC2
}e_pwmChannel;

typedef struct{
	e_pwmChannel pwm_port;
	prescaler pwm_prescaler;
	uint16 freq;
	uint16 duty;
	e_pwmMode pwm_mode;
}s_pwmConfig;


/*
 * responsible for start a PWM signal with the specified frequency and duty cycle
 * */
void PWM_start(s_pwmConfig * a_pwm_config);
/*
 * stop the timer1 PWM
 * */
void PWM_stop(e_pwmChannel ch);
/*
 * function responsible for changing the duty cycle of specific
 * channel
 * */
void PWM_change_DutyCycle(e_pwmChannel ch , uint16 duty);

#endif /* PWM_H_ */
