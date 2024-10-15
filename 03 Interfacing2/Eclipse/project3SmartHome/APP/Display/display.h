/******************************************************************************
 *
 * Module: Display
 *
 * File Name: display.h
 *
 * Description: Header file for the display module responsible for showing alarm
 *              and normal operation states.
 *
 * Created on: Oct 5, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef APP_DISPLAY_DISPLAY_H_
#define APP_DISPLAY_DISPLAY_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../std_types.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

extern uint8 g_changeLcdView;  /* Flag to track if the LCD view should change */

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * @brief Initializes the display module.
 *
 * This function initializes any hardware or modules required for display operations.
 */
void DISPLAY_init(void);

/**
 * @brief Displays the alarm state on the LCD.
 *
 * This function shows the alarm state when a flame or hazard is detected.
 */
void DISPLAY_showAlarm(void);

/**
 * @brief Displays the normal state on the LCD.
 *
 * This function shows the normal state when no hazard is detected.
 */
void DISPLAY_showNormal(void);

#endif /* APP_DISPLAY_DISPLAY_H_ */
