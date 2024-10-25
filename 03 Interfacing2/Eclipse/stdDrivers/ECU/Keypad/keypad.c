/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.c
 *
 * Description: This module provides functionality for interfacing with a
 *              4x4 or 4x3 keypad. It includes initialization, key press
 *              detection, and adjustment of key values based on the keypad layout.
 *
 * Created on: Sep 27, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#include "keypad.h"
#include "../../MCAL/GPIO/gpio.h"
#include <util/delay.h>

/*******************************************************************************
 *                      Functions Prototypes (Private)                          *
 *******************************************************************************/

#ifdef SPECIAL_KEYPAD
const uint8 *g_keys = NULL_PTR;
#else
#ifndef STANDARD_KEYPAD

#if (KEYPAD_NUM_COLS == 3)
/*
 * Function responsible for adjusting the pressed key number for a
 * 4x3 keypad layout to match the correct functional values.
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number);
#elif (KEYPAD_NUM_COLS == 4)
/*
 * Function responsible for adjusting the pressed key number for a
 * 4x4 keypad layout to match the correct functional values.
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);
#endif

#endif /* STANDARD_KEYPAD */

#endif /* SPECIAL_KEYPAD */

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

/*
 * Description: Initializes the keypad by setting the row pins as output
 *              and column pins as input. This prepares the keypad for
 *              key press detection.
 */
void KEYPAD_init(void) {
  uint8 col = 0, row = 0;

  // Set row pins as input
  for (; row < KEYPAD_NUM_ROWS; row++) {
    GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,
    KEYPAD_FIRST_ROW_PIN_ID + row,
			   PIN_INPUT);
  }

  // Set column pins as input
  for (; col < KEYPAD_NUM_COLS; col++) {
    GPIO_setupPinDirection(KEYPAD_COL_PORT_ID,
    KEYPAD_FIRST_COL_PIN_ID + col,
			   PIN_INPUT);
  }
}

#ifdef SPECIAL_KEYPAD
void KEYPAD_setKeys(const uint8 *keysO) {
  g_keys = keysO;
}
#endif

/*
 * Description: Scans the keypad for any pressed keys. It returns the
 *              corresponding key value or KEYPAD_NO_KEY if no key is pressed.
 */
uint8 KEYPAD_getPressedKey(void) {
  uint8 col = 0, row = 0;
  uint8 key = KEYPAD_NO_KEY; // Initialize key variable

  // Loop through each row to check for key presses
  for (; row < KEYPAD_NUM_ROWS; row++) {
    /*
     * Set the current row as OUTPUT and clear its pin to indicate it is active.
     */
    GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,
    KEYPAD_FIRST_ROW_PIN_ID + row,
			   PIN_OUTPUT);

    // Activate the current row by setting it to LOW
    GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + row,
    KEYPAD_BUTTON_PRESSED);

    // Loop through each column to check if any key is pressed
    for (col = 0; col < KEYPAD_NUM_COLS; col++) {
      /* Check if the switch is pressed in this column */
      if (GPIO_readPin(KEYPAD_COL_PORT_ID,
      KEYPAD_FIRST_COL_PIN_ID + col) == KEYPAD_BUTTON_PRESSED) {
	_delay_ms(20); // Delay for debouncing
	// Wait until the key is released
	while (GPIO_readPin(KEYPAD_COL_PORT_ID,
	KEYPAD_FIRST_COL_PIN_ID + col) == KEYPAD_BUTTON_PRESSED)
	  ;
#ifdef SPECIAL_KEYPAD
	key = g_keys[(row * KEYPAD_NUM_COLS) + col];
#else
#if (KEYPAD_NUM_COLS == 3)
	#ifdef STANDARD_KEYPAD
							key = ((row * KEYPAD_NUM_COLS) + col + 1);
	#else
							key = KEYPAD_4x3_adjustKeyNumber((row * KEYPAD_NUM_COLS) + col + 1);
	#endif
#elif (KEYPAD_NUM_COLS == 4)
#ifdef STANDARD_KEYPAD
							key = ((row * KEYPAD_NUM_COLS) + col + 1);
#else
				key = KEYPAD_4x4_adjustKeyNumber(
						(row * KEYPAD_NUM_COLS) + col + 1);
#endif
#endif
#endif /* SPECIAL_KEYPAD */
	break;
      }
    }
    // Reset the row pin direction to INPUT after scanning
    GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,
    KEYPAD_FIRST_ROW_PIN_ID + row,
			   PIN_INPUT);
    _delay_ms(5); /* Small delay to fix CPU load issue in Proteus */
  }

  return key; // Return the detected key value
}

#if !defined(STANDARD_KEYPAD) && !defined(SPECIAL_KEYPAD)

#if (KEYPAD_NUM_COLS == 3)
/*
 * Description: Adjusts the pressed button value for a 4x3 keypad layout
 *              to the corresponding functional value. This handles special
 *              cases for buttons '*', '0', and '#'
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number) {
	uint8 keypad_button = 0; // Initialize variable for adjusted button
	switch(button_number) {
		case 10: keypad_button = '*'; // Adjusted value for '*' button
				 break;
		case 11: keypad_button = 0; // Adjusted value for '0' button
				 break;
		case 12: keypad_button = '#'; // Adjusted value for '#' button
				 break;
		default: keypad_button = button_number; // Default to button number
				break;
	}
	return keypad_button; // Return the adjusted button value
}

#elif (KEYPAD_NUM_COLS == 4)

/*
 * Description: Adjusts the pressed button value for a 4x4 keypad layout
 *              to the corresponding functional value. This handles all
 *              button cases including '1', '2', '3', etc.
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number) {
	uint8 keypad_button = 0; // Initialize variable for adjusted button
	switch (button_number) {
	case 1:
		keypad_button = '7';
		break;
	case 2:
		keypad_button = '8';
		break;
	case 3:
		keypad_button = '9';
		break;
	case 4:
		keypad_button = '/';
		break; // Adjusted value for '%' button
	case 5:
		keypad_button = '4';
		break;
	case 6:
		keypad_button = '5';
		break;
	case 7:
		keypad_button = '6';
		break;
	case 8:
		keypad_button = '*';
		break; // Adjusted value for '*' button
	case 9:
		keypad_button = '1';
		break;
	case 10:
		keypad_button = '2';
		break;
	case 11:
		keypad_button = '3';
		break;
	case 12:
		keypad_button = '-';
		break; // Adjusted value for '-' button
	case 13:
		keypad_button = KEYPAD_ENTER_ASCII;
		break; // Adjusted value for Enter
	case 14:
		keypad_button = '0';
		break;
	case 15:
		keypad_button = '=';
		break; // Adjusted value for '=' button
	case 16:
		keypad_button = '+';
		break; // Adjusted value for '+' button
	default:
		keypad_button = button_number;
		break; // Default to button number
	}
	return keypad_button; // Return the adjusted button value
}

#endif

#endif

/*
 * Description: Blocks execution until a key is pressed on the keypad.
 *              This function continuously checks for key presses and
 *              returns the detected key value when one is pressed.
 */
uint8 KEYPAD_getPressedKeyBlocking(void) {
  uint8 input = KEYPAD_NO_KEY; // Initialize input variable
  while (input == KEYPAD_NO_KEY) { // Loop until a key is detected
    input = KEYPAD_getPressedKey(); // Get the pressed key
  }
  return input; // Return the detected key value
}
