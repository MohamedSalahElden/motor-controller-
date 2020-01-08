/*
 * main.c
 *
 *  Created on: Jan 7, 2020
 *      Author: SALAH
 */

#include "lcd.h"
#include "adc.h"
#include "l293D.h"
#include "INT0_INT1.h"

adcConfig g_adc_config = {interrupt , AREF};
motor_config motor1_config = {M0 , CW , 0};

/*INT0 push button interrupt handler callback function*/
void INT0_interruptHandler(void){
	static motorDir state  = CW;
	if(state == CCW){
		state = CW;
	}
	else if(state == CW){
		state = CCW;
	}
	changeDirection(M0 , state);
}


void main(void){
	/*variable to update LCD only when ADC value changes*/
	uint16 last_value = 0;
	LCD_init();	/* initialize LCD */
	/*
	 * initialize ADC with interrupt mode
	 * and AREF as a refrence voltage connected to 5 volt
	 * */
	ADC_init(&g_adc_config);

	LCD_clearScreen();
	LCD_displayString("ADC value = ");
	/*
	 * start motor with clock wise rotation and speed = 0
	 * */
	startMotor(&motor1_config);
	/*
	 * initialize INT0 and set the call back function
	 * */
	INT0_init(rising);
	INT0_setCallback(INT0_interruptHandler);

	/*enable CPU global interrupt*/
	SREG |= (1<<7);

	while(1){
		/*
		 * start conversion of analog voltage
		 * attached to channel 0
		 * */
		ADC_readChannel(0);
		/*
		 * update the LCD only when the ADC value changes
		 * to prevent blinking of LCD while displaying
		 * the update takes place only on the 4 digits
		 * the ADC value is being displayed in hence 4 spaces
		 * in  LCD_displayString("    "); starting from position 12
		 * change the speed of motor will take place only at change
		 * of ADC value ... to minimize the master loop iteration time
		 * */
		if(g_digital_value != last_value){
			LCD_goTo(0,12);
			LCD_displayString("    ");
			changeSpeed(M0 , g_digital_value/4);
			last_value = g_digital_value;
		}
		/*
		 * display the ADC value in it's specified position
		 * line 0 col 12
		 * */
		LCD_goTo(0,12);
		LCD_displayNumber(g_digital_value);
	}
}
