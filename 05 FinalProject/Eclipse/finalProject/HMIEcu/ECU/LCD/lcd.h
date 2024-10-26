/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: This header file contains the necessary definitions,
 *              macros, and function prototypes for interfacing with an
 *              LCD module. It supports both 4-bit and 8-bit data modes.
 *
 * Created on: Sep 27, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "../../LIB/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* LCD Data bits mode configuration. Its value should be 4 or 8. */
#define LCD_DATA_BITS_MODE 8

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))
#error "Number of Data bits should be equal to 4 or 8"
#endif

/* LCD Hardware Ports and Pins IDs */
#define LCD_RS_PORT_ID                 PORTC_ID
#define LCD_RS_PIN_ID                  PIN0_ID

#define LCD_E_PORT_ID                  PORTC_ID
#define LCD_E_PIN_ID                   PIN1_ID

#define LCD_DATA_PORT_ID               PORTA_ID

#if (LCD_DATA_BITS_MODE == 4)
#define LCD_DB4_PIN_ID                 PIN3_ID
#define LCD_DB5_PIN_ID                 PIN4_ID
#define LCD_DB6_PIN_ID                 PIN5_ID
#define LCD_DB7_PIN_ID                 PIN6_ID
#endif

/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01          // Clear display command
#define LCD_GO_TO_HOME                       0x02          // Return home command
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38          // 8-bit mode, 2 lines
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28          // 4-bit mode, 2 lines
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33          // 4-bit mode initialization step 1
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32          // 4-bit mode initialization step 2
#define LCD_CURSOR_OFF                       0x0C          // Cursor off command
#define LCD_CURSOR_ON                        0x0E          // Cursor on command
#define LCD_CURSOR_BLINK                     0x0D          // Cursor blink command
#define LCD_SET_CURSOR_LOCATION              0x80          // Set cursor position command

#define LCD_FIRST_ROW	0
#define LCD_SECOND_ROW	1
#define LCD_FIRST_COL	0

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description: Initializes the LCD by configuring the GPIO pins
 *              for the LCD and setting the data mode (4-bit or 8-bit).
 */
void LCD_init (void);

/*
 * Description: Sends the specified command to the LCD.
 *
 * @param command: The command to be sent.
 */
void LCD_sendCommand (uint8 command);

/*
 * Description: Displays a single character on the LCD.
 *
 * @param data: The character to be displayed.
 */
void LCD_displayCharacter (uint8 data);

/*
 * Description: Displays a string on the LCD.
 *
 * @param Str: Pointer to the string to be displayed.
 */
void LCD_displayString (const char *Str);

/*
 * Description: Moves the cursor to a specified row and column on the LCD.
 *
 * @param row: The row index (0 or 1).
 * @param col: The column index (0 to 15).
 */
void LCD_moveCursor (uint8 row, uint8 col);

/*
 * Description: Displays a string at a specified row and column on the LCD.
 *
 * @param row: The row index (0 or 1).
 * @param col: The column index (0 to 15).
 * @param Str: Pointer to the string to be displayed.
 */
void LCD_displayStringRowColumn (uint8 row, uint8 col, const char *Str);

/*
 * Description: Sends the clear screen command to the LCD, clearing all displayed content.
 */
void LCD_clearScreen (void);

/*
 * Description: Sends the cursor blink command to the LCD.
 */
void LCD_cursorBlink (void);

/*
 * Description: Displays a decimal value on the LCD.
 *
 * @param data: The integer value to be displayed.
 */
void LCD_displayNumber (sint32 data);

#endif /* LCD_H_ */
