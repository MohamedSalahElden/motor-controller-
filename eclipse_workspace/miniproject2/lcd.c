/*
 * lcd.c
 *
 *  Created on: Dec 29, 2019
 *      Author: mohamed salah
 */

#include "lcd.h"



void LCD_init(void){
	/*set the pins connected to LCD to output port*/
	SET_BIT(CONTROL_PORT_DIR , RS);
	SET_BIT(CONTROL_PORT_DIR , RW);
	SET_BIT(CONTROL_PORT_DIR , E);
#if (LCD_MODE == 8)
	DATA_PORT_DIR = 0xFF;
	LCD_sendCommand(_8BIT_2LINES);	/*set LCD to 8bit 2lines mode*/
#elif (LCD_MODE == 4)
	LCD_sendCommand(_4BIT_DATA_MODE);
#ifdef LCD_4BIT_MODE_UPPER_PORT
	DATA_PORT_DIR |= 0xF0;
	LCD_sendCommand(_4BIT_2LINES);	/*set LCD to 8bit 2lines mode*/
#endif
#ifndef LCD_4BIT_MODE_UPPER_PORT
	DATA_PORT_DIR |= 0x0F;
	LCD_sendCommand(_4BIT_2LINES);	/*set LCD to 8bit 2lines mode*/
#endif
#endif
	LCD_sendCommand(DISPLAY_ON_CURSOR_OFF);	/*turn on the LCD and display cursor*/
}
/*
 * send 8 bit command to LCD (read LCD command section in lcd.h)
 * */
void LCD_sendCommand(uint8 a_command){
	CLEAR_BIT(CONTROL_PORT , RS);	/*RS = 0 to command*/
	CLEAR_BIT(CONTROL_PORT , RW);  	/* RW = 0 to write*/
#if (LCD_MODE == 8)
	_delay_ms(1); 					/*delay tas (50 ~ ns)*/
	SET_BIT(CONTROL_PORT , E); 		/*enable pin = 1*/
	_delay_ms(1); 					/*delay tpw - tdsw (290~_ - 100~_ ns = 190~_ns)*/
	DATA_PORT = a_command;			/*write command*/
	_delay_ms(1); 					/*delay tdsw	(100~_ns)*/
	CLEAR_BIT(CONTROL_PORT , E); 	/*enable pin = 0*/
#elif (LCD_MODE == 4)
#ifdef LCD_4BIT_MODE_UPPER_PORT
	_delay_ms(1); 					/*delay tas (50 ~ ns)*/
	SET_BIT(CONTROL_PORT , E); 		/*enable pin = 1*/
	_delay_ms(1); 					/*delay tpw - tdsw (290~_ - 100~_ ns = 190~_ns)*/
	DATA_PORT = (DATA_PORT & 0x0f)|(a_command & 0xf0);	/*write upper 4 bit of command*/
	_delay_ms(1); 					/*delay tdsw	(100~_ns)*/
	CLEAR_BIT(CONTROL_PORT , E); 	/*disable*/

	_delay_ms(1); 					/*delay tas (50 ~ ns)*/
	SET_BIT(CONTROL_PORT , E); 		/*enable pin = 1*/
	_delay_ms(1); 					/*delay tpw - tdsw (290~_ - 100~_ ns = 190~_ns)*/
	DATA_PORT = (DATA_PORT & 0x0f)|((a_command & 0x0f)<<4);	/*write lower 4 bit of command*/
	_delay_ms(1); 					/*delay tdsw	(100~_ns)*/
	CLEAR_BIT(CONTROL_PORT , E); 	/*disable*/
#endif
#ifndef LCD_4BIT_MODE_UPPER_PORT
	_delay_ms(1); 					/*delay tas (50 ~ ns)*/
	SET_BIT(CONTROL_PORT , E); 		/*enable pin = 1*/
	_delay_ms(1); 					/*delay tpw - tdsw (290~_ - 100~_ ns = 190~_ns)*/
	DATA_PORT = (DATA_PORT & 0xf0)|((a_command & 0xf0)>>4);	/*write upper 4 bit of command*/
	_delay_ms(1); 					/*delay tdsw	(100~_ns)*/
	CLEAR_BIT(CONTROL_PORT , E); 	/*enable pin = 0*/

	_delay_ms(1); 					/*delay tas (50 ~ ns)*/
	SET_BIT(CONTROL_PORT , E); 		/*enable pin = 1*/
	_delay_ms(1); 					/*delay tpw - tdsw (290~_ - 100~_ ns = 190~_ns)*/
	DATA_PORT = (DATA_PORT & 0xf0)|((a_command & 0x0f));	/*write lower 4 bit of command*/
	_delay_ms(1); 					/*delay tdsw	(100~_ns)*/
	CLEAR_BIT(CONTROL_PORT , E); 	/*enable pin = 0*/
#endif
#endif

}

/*
 * send character (ascii of character) to be displayed on the LCD
 * */
void LCD_characterDisplay(uint8 a_character){
	SET_BIT(CONTROL_PORT , RS);		/*RS = 1 to data*/
	CLEAR_BIT(CONTROL_PORT , RW);  	/* RW = 0 to write*/
#if (LCD_MODE == 8)
	_delay_ms(1); 					/*delay tas (50 ~ ns)*/
	SET_BIT(CONTROL_PORT , E); 		/*enable pin = 1*/
	_delay_ms(1); 					/*delay tpw - tdsw (290~_ - 100~_ ns = 190~_ns)*/
	DATA_PORT = a_character;			/*write command*/
	_delay_ms(1); 					/*delay tdsw	(100~_ns)*/
	CLEAR_BIT(CONTROL_PORT , E); 	/*enable pin = 0*/
#elif (LCD_MODE == 4)
#ifdef LCD_4BIT_MODE_UPPER_PORT

	_delay_ms(1); 					/*delay tas (50 ~ ns)*/
	SET_BIT(CONTROL_PORT , E); 		/*enable pin = 1*/
	_delay_ms(1); 					/*delay tpw - tdsw (290~_ - 100~_ ns = 190~_ns)*/
	DATA_PORT = (DATA_PORT & 0x0f)|(a_character & 0xf0);	/*write upper 4 bit of command*/
	_delay_ms(1); 					/*delay tdsw	(100~_ns)*/
	CLEAR_BIT(CONTROL_PORT , E); 	/*enable pin = 0*/

	_delay_ms(1); 					/*delay tas (50 ~ ns)*/
	SET_BIT(CONTROL_PORT , E); 		/*enable pin = 1*/
	_delay_ms(1); 					/*delay tpw - tdsw (290~_ - 100~_ ns = 190~_ns)*/
	DATA_PORT = (DATA_PORT & 0x0f)|((a_character & 0x0f)<<4);	/*write lower 4 bit of command*/
	_delay_ms(1); 					/*delay tdsw	(100~_ns)*/
	CLEAR_BIT(CONTROL_PORT , E); 	/*enable pin = 0*/
#endif
#ifndef LCD_4BIT_MODE_UPPER_PORT
	_delay_ms(1); 					/*delay tas (50 ~ ns)*/
	SET_BIT(CONTROL_PORT , E); 		/*enable pin = 1*/
	_delay_ms(1); 					/*delay tpw - tdsw (290~_ - 100~_ ns = 190~_ns)*/
	DATA_PORT = (DATA_PORT & 0xf0)|((a_character & 0xf0)>>4);	/*write upper 4 bit of command*/
	_delay_ms(1); 					/*delay tdsw	(100~_ns)*/
	CLEAR_BIT(CONTROL_PORT , E); 	/*enable pin = 0*/

	_delay_ms(1); 					/*delay tas (50 ~ ns)*/
	SET_BIT(CONTROL_PORT , E); 		/*enable pin = 1*/
	_delay_ms(1); 					/*delay tpw - tdsw (290~_ - 100~_ ns = 190~_ns)*/
	DATA_PORT = (DATA_PORT & 0xf0)|((a_character & 0x0f));	/*write lower 4 bit of command*/
	_delay_ms(1); 					/*delay tdsw	(100~_ns)*/
	CLEAR_BIT(CONTROL_PORT , E); 	/*enable pin = 0*/
#endif
#endif
}

void LCD_displayString(const uint8 *a_string){
	while(*a_string != '\0'){
		LCD_characterDisplay(*a_string);
		a_string ++;
	}
}


void LCD_clearScreen(void){
	LCD_sendCommand(CLEAR_DISPLAY_SCREEN);
}



void LCD_displayNumber(uint16 a_num){
	if(a_num == 0){
		LCD_characterDisplay('0');
	}
	uint8 num_string[16] = {'\0'};
	uint8 shift = 1;
	while(a_num > 0){
		int i=shift;
		for( ; i>=0 ; i--){
			num_string[i] = num_string[i-1];
		}
		num_string[0] = (a_num % 10) + 48;
		a_num /= 10;
		shift++;
	}
	LCD_displayString(num_string);
}


void LCD_goTo(uint8 a_row , uint8 a_col){
	uint8 address;
	switch(a_row){
	case 0:
		address = 128 + a_col;
		break;
	case 1:
		address = 128 + a_col + 0x40;
		break;
#if (LCD_ROW_NUM == 4)
	case 2:
		address = 128 + a_col + 0x10;
		break;
	case 3:
		address = 128 + a_col + 0x50;
		break;
#endif
	default :
		break;
	}
	LCD_sendCommand(address);
}
