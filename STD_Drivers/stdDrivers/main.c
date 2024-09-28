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

#include "ECU/LCD/lcd.h"
#include "MCAL/GPIO/gpio.h"
#include "ECU/Keypad/keypad.h"
#include "ECU/SevenSegment/sevenseg.h"
#include "util/delay.h"

int main(void) {
	uint8 input = KEYPAD_NO_KEY;
	uint8 state = 0;
	sint16 num1 = 0, num2 = 0;
	uint8 operator = '+';
	sint32 result = 0;
	KEYPAD_init();
	LCD_init();
	LCD_sendCommand(LCD_CURSOR_BLINK);
	SEVENSEG_display(0);

	for (;;) {

		input = KEYPAD_getPressedKeyBlocking();

		if(input == KEYPAD_ENTER_ASCII){
			num1 = num2 = result = 0;
			LCD_clearScreen();
		}

		if (state == 0) {
			if (input >= '0' && input <= '9') {
				LCD_displayCharacter(input);
				num1 *= 10;
				num1 += input - '0';
			} else if (input == '+' || input == '-' || input == '*'
					|| input == '/') {
				LCD_displayCharacter(' ');
				LCD_displayCharacter(input);
				LCD_displayCharacter(' ');
				operator = input;
				state = 1;
			}
		} else if (state == 1 || state == 3) {
			if (input >= '0' && input <= '9') {
				LCD_displayCharacter(input);
				num2 *= 10;
				num2 += input - '0';
			} else if (input == '=') {
				LCD_displayCharacter(' ');
				LCD_displayCharacter(input);
				LCD_displayCharacter(' ');
				result = 0;
				switch (operator) {
				case '+':
					result = num1 + num2;
					break;
				case '-':
					result = num1 - num2;
					break;
				case '*':
					result = num1 * num2;
					break;
				case '/':

					result = num2 == 0 ? 0 : num1 / num2;
					break;
				}
				LCD_displayNumber(result);
				if (state == 1)
					state = 2;
				else
					state = 4;
			}
		} else if (state == 2 || state == 4) {
			LCD_clearScreen();
			if (input >= '0' && input <= '9') {
				LCD_displayCharacter(input);
				num1 = input - '0';
				num2 = 0;
				state = 0;
			} else if (input == '+' || input == '-' || input == '*'
					|| input == '/') {
				LCD_displayString("Ans ");
				LCD_displayCharacter(input);
				LCD_displayCharacter(' ');
				operator = input;
				num1 = result;
				num2 = 0;
				state = 3;
			} else if (state == 4 && input == '=') {
				switch (operator) {
				case '+':
					result = result + num2;
					break;
				case '-':
					result = result - num2;
					break;
				case '*':
					result = result * num2;
					break;
				case '/':

					result = result / num2;
					break;
				}
				LCD_displayString("Ans ");
				LCD_displayCharacter(operator);
				LCD_displayCharacter(' ');
				LCD_displayNumber(num2);
				LCD_displayString(" = ");
				LCD_displayNumber(result);
			}
		}
	}

}

