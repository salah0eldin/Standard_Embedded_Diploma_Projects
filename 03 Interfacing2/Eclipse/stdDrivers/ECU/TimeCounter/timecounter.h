/******************************************************************************
 *
 * Module: Time Counter
 *
 * File Name: timecounter.h
 *
 * Description: Header file for the Time Counter module. This module allows
 *              configuring Timer0 to run for a specified time interval (in
 *              milliseconds) using CTC mode and calling a user-defined
 *              interrupt handler upon completion.
 *
 * Created on: Oct 25, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef ECU_TIMECOUNTER_TIMECOUNTER_H_
#define ECU_TIMECOUNTER_TIMECOUNTER_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../LIB/std_types.h"  /* Standard data types definitions */

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * @brief Configure Timer0 to generate a time delay for a specified time in milliseconds.
 *
 * This function sets Timer0 in CTC mode to run for the specified time interval (msTime).
 * Once the time elapses, the function executes the user-defined interrupt handler.
 *
 * @param msTime The time interval in milliseconds after which the interrupt handler is called.
 * @param interruptHandler Pointer to the function that will be called when the timer expires.
 */
void TIMERCOUNTER_forOneTime(uint16 msTime, void(*interruptHandler)(void));

#endif /* ECU_TIMECOUNTER_TIMECOUNTER_H_ */
