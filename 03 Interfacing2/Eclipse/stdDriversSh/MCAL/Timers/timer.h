/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.h
 *
 * Description: This header file provides definitions and declarations
 *              for configuring and using Timers in various modes including
 *              normal counting, compare, and PWM.
 *
 * Created on: Nov 1, 2024
 *
 * Author: Shahd Gamal
 *
 *******************************************************************************/

#ifndef MCAL_TIMERS_TIMER_H_
#define MCAL_TIMERS_TIMER_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "std_types.h"

/*******************************************************************************
 *                                 Enums                                       *
 *******************************************************************************/

/** @brief Enumeration for Timer clock prescaler options. */
typedef enum {
  TIMER_NO_CLOCK,                   /* No clock source (timer stopped) */
  TIMER_PRESCALER_1,                /* Clock without prescaling */
  TIMER_PRESCALER_8,                /* Clock divided by 8 */
  TIMER_PRESCALER_64,               /* Clock divided by 64 */
  TIMER_PRESCALER_256,              /* Clock divided by 256 */
  TIMER_PRESCALER_1024,             /* Clock divided by 1024 */
  TIMER_EXTERNAL_FALLING_EDGE,      /* External clock on falling edge */
  TIMER_EXTERNAL_RISING_EDGE        /* External clock on rising edge */
} TIMER_Clock;

/** @brief Enumeration for Timer operating modes. */
typedef enum {
  TIMER_MODE_NORMAL,        /* Normal counting mode */
  TIMER_MODE_COMPARE,       /* Compare match mode */
  TIMER_MODE_FAST_PWM       /* Fast PWM mode */
} TIMER_Mode;

/** @brief Enumeration for Timer identifiers. */
typedef enum {
  TIMER0_ID,                /* Identifier for Timer0 */
  TIMER1_ID,                /* Identifier for Timer1 */
  TIMER2_ID                 /* Identifier for Timer2 */
} TIMER_ID;

/*******************************************************************************
 *                             Struct Definitions                              *
 *******************************************************************************/

/** @brief Structure to hold configuration settings for a Timer instance. */
typedef struct {
  TIMER_ID timer_ID;          /* Timer identifier */
  uint16 initial_value;       /* Initial counter value */
  uint16 compare_value;       /* Compare match value */
  TIMER_Clock timer_clock;    /* Clock prescaler selection */
  TIMER_Mode mode;            /* Timer operating mode */
} TIMER_t;

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * @brief Initializes a Timer with the specified configuration.
 *
 * This function configures a Timer according to the settings provided
 * in the TIMER_t structure.
 *
 * @param Config_Ptr Pointer to TIMER_t structure with configuration settings.
 */
void TIMER_init(const TIMER_t *Config_Ptr);

/**
 * @brief Stops and deinitializes a specified Timer.
 *
 * @param timer_type Identifier for the Timer to deinitialize.
 */
void TIMER_deInit(TIMER_ID timer_type);

/**
 * @brief Sets a callback function for the Timer interrupt.
 *
 * Allows the user to assign a callback function that will be executed
 * on a Timer interrupt.
 *
 * @param a_ptr Pointer to the callback function.
 * @param a_timer_ID Identifier for the Timer for which the callback is set.
 */
void TIMER_setCallBack(void (*a_ptr)(void), TIMER_ID a_timer_ID);

#endif /* MCAL_TIMERS_TIMER_H_ */
