/*
 * l293D.h
 *
 *  Created on: Jan 7, 2020
 *      Author: SALAH
 */

#ifndef L293D_H_
#define L293D_H_

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"
#include "pwm.h"

#define CONTROL_PORT_DIR DDRB
#define CONTROL_PORT_DATA PORTB

#define IN1 PB0
#define IN2 PB1
#define EN1	OC0
#define IN3 PB3
#define IN4 PB4
#define EN2 OC1A

typedef enum{
	M0 , M1
}motorNum;

typedef enum{
	CW , CCW
}motorDir;

typedef struct{
	motorNum motor_number;
	motorDir motor_direction;
	uint8 motor_speed ;
}motor_config;


void startMotor(motor_config *a_motor_config);
void stopMotor(motorNum num);
void changeSpeed(motorNum num , uint8 speed);
void changeDirection(motorNum num , motorDir direction);




#endif /* L293D_H_ */
