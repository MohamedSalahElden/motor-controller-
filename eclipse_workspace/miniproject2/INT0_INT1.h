/*
 * external_int_0.h
 *
 *  Created on: Jan 7, 2020
 *      Author: SALAH
 */

#ifndef INT0_INT1_H_
#define INT0_INT1_H_


#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

/*--------- ADC working modes ---------------- */
#ifndef NULL
#define NULL ((void *)0)
#endif

typedef enum{
	low_level , any , falling , rising
}senseControl;

void INT0_init(senseControl INT0_control);
void INT0_setCallback(void (*functionPtr)(void));
void INT0_changeSenseControl(senseControl INT0_control);
void INT0_DeInit();

void INT1_init(senseControl INT1_control);
void INT1_setCallback(void (*functionPtr)(void));
void INT1_changeSenseControl(senseControl INT1_control);
void INT1_DeInit();


#endif /* INT0_INT1_H_ */
