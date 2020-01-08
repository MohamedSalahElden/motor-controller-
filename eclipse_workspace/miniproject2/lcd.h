/*
 * lcd.h
 *
 *  Created on: Dec 29, 2019
 *      Author: mohamed salah
 */

#ifndef LCD_H_
#define LCD_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"


/*----------------------------------------------------------------------------------------------
 * LCD static configuration
 * ---------------------------------------------------------------------------------------------*/
/*
 * change to match number of your LCD rows 1 , 2 , 4
 * */
#define LCD_ROW_NUM 2
/*
 * change to match the connecting mode
 * 4 represents 4 wires connected to R4~7 in LCD
 * 8 represents 8 wires connected to R0~7 in LCD
 * */
#define LCD_MODE 8
/*
 *	comment the #define LCD_4BIT_MODE_UPPER_PORT
 *	if you connects the 4 wires the least significant 4 bits in your micro controller port
 * */
#if (LCD_MODE == 4)
#define LCD_4BIT_MODE_UPPER_PORT
#endif
/* change the pins bellow to match the connection in your microcontroller
 * note : all control pins must be connected on the same port
 *			all data pins must be connected adjacently on the same port
 *			for 4 bit mode (0~3 or 4~7)
 *			for 8 bit mode (0~7)
 * */
#define DATA_PORT PORTC
#define CONTROL_PORT PORTD
#define DATA_PORT_DIR DDRC
#define CONTROL_PORT_DIR DDRD
#define RS 4
#define RW 5
#define E  6
#define V0 3

/*------------------------------------------------------------------------------------------------
 * LCD commands definitions
 * -----------------------------------------------------------------------------------------------*/

#define CLEAR_DISPLAY_SCREEN 		0x01
#define _4BIT_DATA_MODE				0x02
#define SHIFT_CURSOR_TO_LEFT 		0x04
#define SHIFT_CURSOR_TO_RIGHT 		0x06
#define SHIFT_DISPLAY_LEFT 			0x18
#define SHIFT_DISPLAY_RIGHT 		0x1C
#define DISPLAY_OFF_CURSOR_OFF 		0x08
#define DISPLAY_OFF_CURSOR_ON 		0x0A
#define DISPLAY_ON_CURSOR_ON 		0x0E
#define DISPLAY_ON_CURSOR_OFF		0x0C
#define DISPLAY_OFF_CURSOR_BLINKING 0x0F
#define SHIFT_CURSOR_LEFT 			0x10
#define SHIFT_CURSOR_RIGHT 			0x14
#define SHIT_DISPLAY_LEFT 			0x18
#define MOVE_CURSOR_1ST_LINE 		0x80
#define MOVE_CURSOR_2ND_LINE 		0xC0
#define _8BIT_2LINES 				0x38
#define _4BIT_2LINES				0x28


/*------------------------------------------------------------------------------------------------------------
 * function prototypes
 * -----------------------------------------------------------------------------------------------------------*/
/*
 * function name 	: LCD_init
 * description 		: this function initializes the LCD , set it to desired mode (1/2/4 lines 4/8 mode )
 * */
void LCD_init(void);
/*
 * function name 	: LCD_sendCommand
 * description 		: this function send one command of the predefined command (see LDC command definition)
 * args				: a_command : 8bit variable represents the command
 * */
void LCD_sendCommand(uint8 a_command);
/*
 * function name 	: LCD_characterDisplay
 * description 		: this function send 8bits (data) to LCD . character is sent as an ASCII code
 * args				: a_character : 8bit variable represents the data
 * */
void LCD_characterDisplay(uint8 a_character);
/*
 * function name 	: LCD_displayString
 * description 		: this function send characters of string one by one to be displayed on the screen
 * args				: a_character : 8bit variable represents the data
 * */
void LCD_displayString(const uint8 *a_string);
/*
 * function name 	: LCD_goToRowColumn
 * description 		: this function takes a specific location on the LCD and send the command that
 * 					moves the cursor to this position
 * args				: uint8 a_row specifies the LCD row (0~1 for 2 line LCD)
 * 															(0~4 for 4 lins LCD)
 * 					  uint8 a_col specifies the LCD columns (0~15)
 * */
void LCD_goTo(uint8 a_row , uint8 a_col);
/*
 * function name 	: LCD_clearScreen
 * description 		: this function clears the LCD
 * */
void LCD_clearScreen(void);

/*
 * function name 	: LCD_displayNumber
 * description 		: this function takes an integer convert it to it's
 * 					ASCII representation string of 15 digit then display it on LCD
 * */
void LCD_displayNumber(uint16 a_num);

#endif /* LCD_H_ */
