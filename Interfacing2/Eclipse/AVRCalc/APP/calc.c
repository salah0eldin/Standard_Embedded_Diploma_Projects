/******************************************************************************
 *
 * Module: Calculator
 *
 * File Name: calc.c
 *
 * Description: 
 *
 * Created on: Sep 28, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#include "calc.h"

#include "../ECU/LCD/lcd.h"
#include "../MCAL/GPIO/gpio.h"
#include "../ECU/Keypad/keypad.h"
#include <util/delay.h>

const uint8 keys[] = {
		'7', '8', '9', '/',
		'4', '5', '6', '*',
		'1', '2', '3', '-',
		KEYPAD_ENTER_ASCII, '0', '=', '+'
};

void CALC_init(CALC_t * calculator){
	KEYPAD_init();
	KEYPAD_setKeys(keys);
	LCD_init();
	LCD_cursorBlink();
	CALC_reset(calculator);
	LCD_moveCursor(0,4);
	LCD_displayString("Calculator");
	LCD_moveCursor(1,0);
}

void CALC_reset(CALC_t *calculator) {
	calculator->num1 = calculator->num2 = calculator->result = 0;
	LCD_clearScreen();
}
