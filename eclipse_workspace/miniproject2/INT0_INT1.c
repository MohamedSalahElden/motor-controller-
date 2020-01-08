/*
 * INT0_INT1.c
 *
 *  Created on: Jan 7, 2020
 *      Author: SALAH
 */

#include "INT0_INT1.h"

volatile static void (*g_INT0_functionPtr) (void) = NULL;
volatile static void (*g_INT1_functionPtr) (void) = NULL;

void INT0_init(senseControl INT0_control){
	/*set INT0 PD3 as input pin*/
	CLEAR_BIT(DDRD , PD2);
#ifdef ENABLE_INT0_IPUR /*internal pull up configuration*/
	SET_BIT(PORTD , PD2);
#endif
	/*set the interrupt sense control bits*/
	MCUCR  = (MCUCR & 0xFC) | (INT0_control & 0x03);
	/*enable INT0 request*/
	SET_BIT(GICR, INT0);
}
void INT0_setCallback(void (*functionPtr)(void)){
	g_INT0_functionPtr = functionPtr;
}
void INT0_changeSenseControl(senseControl INT0_control){
	/*set the interrupt sense control bits*/
	MCUCR  = (MCUCR & 0xFC) | (INT0_control & 0x03);
}
void INT0_DeInit(){
	CLEAR_BIT(PORTD , PD2);
	/*set the interrupt sense control bits*/
	MCUCR  = (MCUCR & 0xFC) | (0x00 & 0x03);
	/*enable INT0 request*/
	CLEAR_BIT(GICR, INT0);
}

void INT1_init(senseControl INT1_control){
	/*set INT0 PD3 as input pin*/
	CLEAR_BIT(DDRD , PD3);
#ifdef ENABLE_INT1_IPUR /*internal pull up configuration*/
	SET_BIT(PORTD , PD3);
#endif
	/*set the interrupt sense control bits*/
	MCUCR  = (MCUCR & 0xF3) | (INT1_control & 0x0C);
	/*enable INT0 request*/
	SET_BIT(GICR, INT1);
}
void INT1_setCallback(void (*functionPtr)(void)){
	g_INT1_functionPtr = functionPtr;
}
void INT1_changeSenseControl(senseControl INT1_control){
	/*set the interrupt sense control bits*/
	MCUCR  = (MCUCR & 0xF3) | (INT1_control & 0x0C);
}
void INT1_DeInit(){
	CLEAR_BIT(PORTD , PD3);
	/*set the interrupt sense control bits*/
	MCUCR  = (MCUCR & 0xF3) | (0x00 & 0x0C);
	/*enable INT0 request*/
	CLEAR_BIT(GICR, INT1);
}

ISR(INT0_vect){
	if(g_INT0_functionPtr != NULL){
		(*g_INT0_functionPtr)();
	}
}

ISR(INT1_vect){
	if(g_INT1_functionPtr != NULL){
		(*g_INT1_functionPtr)();
	}
}

