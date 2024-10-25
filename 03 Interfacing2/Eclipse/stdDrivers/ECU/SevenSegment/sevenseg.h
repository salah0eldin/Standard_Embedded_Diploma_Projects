/******************************************************************************
 * Module: Seven-Segment Display
 *
 * File Name: sevenseg.h
 *
 * Description: Header file for the Seven-Segment Display driver.
 *              It provides function prototypes for initializing and displaying
 *              numbers on the seven-segment display.
 *
 * Created on: Sep 27, 2024
 *
 * Author: Salah-Eldin
 *******************************************************************************/

#ifndef ECU_SEVENSEGMENT_SEVENSEG_H_
#define ECU_SEVENSEGMENT_SEVENSEG_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../std_types.h"

/*******************************************************************************
 *                         Functions Prototypes                                *
 *******************************************************************************/

/**
 * @brief Initialize the seven-segment display.
 *
 * This function initializes the GPIO pins used for the seven-segment display
 * based on the configuration specified in the configuration header file.
 * It sets the direction of the pins as output.
 *
 * @note This function must be called before any other seven-segment function.
 */
void SEVENSEG_init(void);

/**
 * @brief Display a number on the seven-segment display.
 *
 * This function takes a number (0-9) and displays it on the seven-segment
 * display by lighting up the corresponding segments. If an invalid number
 * is passed (outside the 0-9 range), it may handle it gracefully or show
 * an error pattern (e.g., blank).
 *
 * @param[in] num: The number to display (valid range: 0-9).
 */
void SEVENSEG_display(uint8 num);

#endif /* ECU_SEVENSEGMENT_SEVENSEG_H_ */
