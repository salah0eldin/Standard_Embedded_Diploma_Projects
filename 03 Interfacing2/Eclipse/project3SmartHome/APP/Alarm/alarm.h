/******************************************************************************
 *
 * Module: Alarm
 *
 * File Name: alarm.h
 *
 * Description: Header file for the Alarm system which handles flame detection.
 *
 * Created on: Oct 5, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef APP_ALARM_ALARM_H_
#define APP_ALARM_ALARM_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../std_types.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
extern uint8 g_flameFlag;    /* Global flag indicating flame detection */

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * @brief Initializes the alarm system.
 *
 * This function sets up the necessary configurations for the alarm system.
 */
void ALARM_init(void);

/**
 * @brief Handles the flame detection and alarm triggering.
 *
 * This function is responsible for processing the flame detection logic
 * and activating the alarm if a flame is detected.
 */
void ALARM_handleFlame(void);

#endif /* APP_ALARM_ALARM_H_ */
