/******************************************************************************
 *
 * Module: Time Counter
 *
 * File Name: timecounter.c
 *
 * Description: Source file for the Time Counter module. This module uses Timer0
 *              to create a time delay for a specified interval (in milliseconds)
 *              and calls a user-defined interrupt handler upon completion.
 *
 * Created on: Oct 25, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "timecounter.h"
#include "../../MCAL/Timers/timer0.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Holds the computed value for Timer0 Compare Register */
static uint32 compareValue = 0;

/* Holds the number of times Timer0 Compare Match occurs before the final interrupt */
static uint8 compareCount = 0;

/* Pointer to the user-defined interrupt handler to be called when the timer completes */
static void (*TIMECOUNTER_intHandler)(void) = NULL_PTR;

/*******************************************************************************
 *                      Private Function Definitions                           *
 *******************************************************************************/

/**
 * @brief Handles the Timer0 Compare Match interrupt. It decrements the compareCount
 * and triggers the user-defined interrupt handler if the timer interval has expired.
 */
void TIMECOUNTER_compareCountForOneTimeIntHandle(void) {
    if (compareCount == 0) {
        TIMER0_deInit(); /* Stop Timer0 */
        if (NULL_PTR != TIMECOUNTER_intHandler) {
            (*TIMECOUNTER_intHandler)(); /* Call user-defined handler */
        }
    } else if (compareCount == 1) {
        /* Set the remaining compare value for the final count */
        TIMER0_setCompareValue(compareValue % TIMER0_MAX_TIMER_VALUE);
    } else {
        /* Set the maximum compare value for the remaining counts */
        TIMER0_setCompareValue(TIMER0_MAX_TIMER_VALUE);
    }
    compareCount--; /* Decrement compare count */
}

/*******************************************************************************
 *                      Public Function Definitions                            *
 *******************************************************************************/

/**
 * @brief Configures Timer0 in CTC mode to run for a specified time interval and
 *        triggers an interrupt when the interval expires.
 *
 * This function calculates the number of compare matches needed for the given time
 * interval (msTime) and sets Timer0 accordingly. Once the time interval elapses,
 * the specified interrupt handler is called.
 *
 * @param msTime The time interval in milliseconds for which Timer0 should run.
 * @param interruptHandler Pointer to the function to be called upon timer completion.
 */
void TIMERCOUNTER_forOneTime(uint16 msTime, void (*interruptHandler)(void)) {
    /* Set the interrupt handler for Timer0 Compare Match */
    TIMER0_setCTCInterruptHandler(TIMECOUNTER_compareCountForOneTimeIntHandle);

    /* Store the user-defined interrupt handler */
    TIMECOUNTER_intHandler = interruptHandler;

    /* Calculate the total compare value based on the required time and the CPU frequency */
    compareValue = (uint64)(msTime * F_CPU) / ((uint64)1000 * TIMER0_PRE_SCALER_VAL);

    /* Calculate the number of compare counts needed */
    compareCount = compareValue / TIMER0_MAX_TIMER_VALUE + 1;

    /* Set the compare value for the first count */
    if (compareCount == 1) {
        TIMER0_setCompareValue((uint8)compareValue);
    } else {
        TIMER0_setCompareValue(TIMER0_MAX_TIMER_VALUE);
    }

    /* Initialize Timer0 with the predefined settings */
    TIMER0_init(&g_timer0);

    /* Decrement compare count for the first compare match */
    compareCount--;
}
