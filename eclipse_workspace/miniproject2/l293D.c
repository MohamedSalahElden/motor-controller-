/*
 * l293D.c
 *
 *  Created on: Jan 7, 2020
 *      Author: SALAH
 */


#include "l293D.h"

void startMotor(motor_config *a_motor_config){
	switch(a_motor_config->motor_number){
	case M0:
		/*set motor pins to output pins = 1*/
		SET_BIT(CONTROL_PORT_DIR , IN1);
		SET_BIT(CONTROL_PORT_DIR , IN2);
		/*set direction */
		if(a_motor_config->motor_direction == CW){
			SET_BIT(CONTROL_PORT_DATA,IN1);
			CLEAR_BIT(CONTROL_PORT_DATA,IN2);
		}
		else{
			CLEAR_BIT(CONTROL_PORT_DATA,IN1);
			SET_BIT(CONTROL_PORT_DATA,IN2);
		}
		/*set speed with PWM with 50Khz frequency*/
		s_pwmConfig motor1PWM = {EN1 , CLK_8 , 255 , a_motor_config->motor_speed , non_inverting};
		PWM_start(&motor1PWM);
		break;
	case M1:
		/*set motor pins to output pins = 1*/
		SET_BIT(CONTROL_PORT_DIR , IN3);
		SET_BIT(CONTROL_PORT_DIR , IN4);
		/*set direction */
		if(a_motor_config->motor_direction == CW){
			SET_BIT(CONTROL_PORT_DATA,IN3);
			CLEAR_BIT(CONTROL_PORT_DATA,IN4);
		}
		else{
			CLEAR_BIT(CONTROL_PORT_DATA,IN3);
			SET_BIT(CONTROL_PORT_DATA,IN4);
		}
		/*set speed with PWM with 50Khz frequency*/
		s_pwmConfig motor2PWM = {EN2 , CLK_8 , 255 , a_motor_config->motor_speed , non_inverting};
		PWM_start(&motor2PWM);
		break;
	}
}

void stopMotor(motorNum num){
	switch(num){
	case M0:
		PWM_stop(EN1);
		break;
	case M1:
		PWM_stop(EN2);
		break;
	}
}

void changeSpeed(motorNum num , uint8 speed){
	switch(num){
	case M0:
		PWM_change_DutyCycle(EN1 , speed);
		break;
	case M1:
		PWM_change_DutyCycle(EN2 , speed);
		break;
	}
}

void changeDirection(motorNum num , motorDir direction){
	switch(num){
	case M0:
		if(direction == CW){
			SET_BIT(CONTROL_PORT_DATA,IN1);
			CLEAR_BIT(CONTROL_PORT_DATA,IN2);
		}
		else if(direction == CCW){
			CLEAR_BIT(CONTROL_PORT_DATA,IN1);
			SET_BIT(CONTROL_PORT_DATA,IN2);
		}
		break;
	case M1:
		if(direction == CW){
			SET_BIT(CONTROL_PORT_DATA,IN3);
			CLEAR_BIT(CONTROL_PORT_DATA,IN4);
		}
		else if(direction == CCW){
			CLEAR_BIT(CONTROL_PORT_DATA,IN3);
			SET_BIT(CONTROL_PORT_DATA,IN4);
		}
		break;
	}
}
