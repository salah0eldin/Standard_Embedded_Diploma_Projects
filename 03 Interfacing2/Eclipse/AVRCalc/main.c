/******************************************************************************
 *
 * File Name: main.c
 *
 * Description: main file
 *
 * Created on: Sep 26, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#include "APP/calc.h"
#include "ECU/Keypad/keypad.h"
#include "ECU/LCD/lcd.h"

int main(void) {
	KEYPAD_key_t inputKey = KEYPAD_NO_KEY;
	CALC_state_t state = CALC_FIRST_NUM_INPUT;

	CALC_t calculator;

	CALC_init(&calculator);

	for (;;) {

		inputKey = KEYPAD_getPressedKeyBlocking();

		if (inputKey == KEYPAD_ENTER_ASCII) {
			CALC_reset(&calculator);
		}

		if (state == 0) {
			if (inputKey >= '0' && inputKey <= '9') {
				LCD_displayCharacter(inputKey);
				calculator.num1 *= 10;
				calculator.num1 += inputKey - '0';
			} else if (inputKey == '+' || inputKey == '-' || inputKey == '*'
					|| inputKey == '/') {
				LCD_displayCharacter(' ');
				LCD_displayCharacter(inputKey);
				LCD_displayCharacter(' ');
				calculator.operator = inputKey;
				state = 1;
			}
		} else if (state == 1 || state == 3) {
			if (inputKey >= '0' && inputKey <= '9') {
				LCD_displayCharacter(inputKey);
				calculator.num2 *= 10;
				calculator.num2 += inputKey - '0';
			} else if (inputKey == '=') {
				LCD_displayCharacter(' ');
				LCD_displayCharacter(inputKey);
				LCD_displayCharacter(' ');
				calculator.result = 0;
				switch (calculator.operator) {
				case '+':
					calculator.result = calculator.num1 + calculator.num2;
					break;
				case '-':
					calculator.result = calculator.num1 - calculator.num2;
					break;
				case '*':
					calculator.result = calculator.num1 * calculator.num2;
					break;
				case '/':

					calculator.result =
							calculator.num2 == 0 ?
									0 : calculator.num1 / calculator.num2;
					break;
				}
				LCD_displayNumber(calculator.result);
				if (state == 1)
					state = 2;
				else
					state = 4;
			}
		} else if (state == 2 || state == 4) {
			LCD_clearScreen();
			if (inputKey >= '0' && inputKey <= '9') {
				LCD_displayCharacter(inputKey);
				calculator.num1 = inputKey - '0';
				calculator.num2 = 0;
				state = 0;
			} else if (inputKey == '+' || inputKey == '-' || inputKey == '*'
					|| inputKey == '/') {
				LCD_displayString("Ans ");
				LCD_displayCharacter(inputKey);
				LCD_displayCharacter(' ');
				calculator.operator = inputKey;
				calculator.num1 = calculator.result;
				calculator.num2 = 0;
				state = 3;
			} else if (state == 4 && inputKey == '=') {
				switch (calculator.operator) {
				case '+':
					calculator.result = calculator.result + calculator.num2;
					break;
				case '-':
					calculator.result = calculator.result - calculator.num2;
					break;
				case '*':
					calculator.result = calculator.result * calculator.num2;
					break;
				case '/':

					calculator.result = calculator.result / calculator.num2;
					break;
				}
				LCD_displayString("Ans ");
				LCD_displayCharacter(calculator.operator);
				LCD_displayCharacter(' ');
				LCD_displayNumber(calculator.num2);
				LCD_displayString(" = ");
				LCD_displayNumber(calculator.result);
			}
		}
	}

}

