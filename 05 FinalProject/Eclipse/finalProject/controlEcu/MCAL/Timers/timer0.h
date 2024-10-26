/******************************************************************************
 *
 * Module: Timer0
 *
 * File Name: timer0.h
 *
 * Description: This header file contains the definitions and declarations
 *              necessary for configuring and using Timer0 in various modes.
 *              It supports normal counting, PWM, and CTC modes.
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef MCAL_TIMERS_TIMER0_H_
#define MCAL_TIMERS_TIMER0_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include <avr/io.h>
#include "../../LIB/std_types.h"

/*******************************************************************************
 *                                 Macros                                      *
 *******************************************************************************/

/*#define TIMER0_ENABLE_OV_INTERRUPT*/
/*#define TIMER0_ENABLE_CTC_INTERRUPT*/

/** @brief Set the Timer0 register value.
 *
 * @param val The value to set to the Timer0 register (TCNT0).
 */
#define TIMER0_setTimerValue(val) (TCNT0 = val)

/** @brief Set the compare value for Timer0.
 *
 * @param val The compare value to set (OCR0).
 */
#define TIMER0_setCompareValue(val) (OCR0 = val)

/** @brief Set the duty cycle for PWM.
 *
 * @param val The desired duty cycle percentage (0-100).
 */
#define TIMER0_setDutyCycle(val) (OCR0 = (uint8)((uint16)val * 255 / 100))

/** @brief Clear Pre-scaler of both timer1 and timer0 as they share same pre-scaler
 */
#define TIMER0_AND_TIMER1_RESET_PRESCALER()  (SFIOR = (SFIOR | (1 << PSR10)));

/*******************************************************************************
 *                                 Enums                                       *
 *******************************************************************************/

/** @brief Enumeration for Timer0 modes. */
typedef enum {
  TIMER0_MODE_NORMAL,        /* Normal counting mode */
  TIMER0_MODE_PWM_PC,        /* PWM with phase correct mode */
  TIMER0_MODE_CTC,           /* Compare mode */
  TIMER0_MODE_PWM_FAST       /* Fast PWM mode */
} TIMER0_mode_t;

/** @brief Enumeration for Timer0 compare output modes. */
typedef enum {
  TIMER0_COMPARE_NORMAL,                    /* Normal port operation, OC0 disconnected. */
  TIMER0_COMPARE_PWM_NON_TOGGLE_OC0,        /* Toggle OC0 on compare match */
  TIMER0_COMPARE_PWM_NON_CLEAR_OC0,         /* Clear OC0 on compare match */
  TIMER0_COMPARE_PWM_NON_SET_OC0,           /* Set OC0 on compare match */

  TIMER0_COMPARE_PWM_FAST_NIN_INVERTING = 2,  /* Clear OC0 on compare match, set OC0 at BOTTOM */
  TIMER0_COMPARE_PWM_FAST_INVERTING,          /* Set OC0 on compare match, clear OC0 at BOTTOM */

  /* Clear OC0 on compare match when up-counting.
   * Set OC0 on compare match when down-counting. */
  TIMER0_COMPARE_PWM_PC_CLEAR_UP = 2,
  /* Set OC0 on compare match when up-counting.
   * Clear OC0 on compare match when down-counting. */
  TIMER0_COMPARE_PWM_PC_CLEAR_DOWN
} TIMER0_compareOutput_mode_t;

/** @brief Enumeration for Timer0 clock prescaler options. */
typedef enum {
  TIMER0_CLOCK_0,                  /* No clock source (Timer/Counter stopped). */
  TIMER0_CLOCK_DIV_1,              /* clk /(No pre-scaling) */
  TIMER0_CLOCK_DIV_8,              /* clk /8 (From pre-scaler) */
  TIMER0_CLOCK_DIV_64,             /* clk /64 (From pre-scaler) */
  TIMER0_CLOCK_DIV_256,            /* clk /256 (From pre-scaler) */
  TIMER0_CLOCK_DIV_1024,           /* clk /1024 (From pre-scaler) */
  TIMER0_CLOCK_EXTERNAL_FALLING,   /* External clock source on T0 pin. Clock on falling edge. */
  TIMER0_CLOCK_EXTERNAL_RISING     /* External clock source on T0 pin. Clock on rising edge. */
} TIMER0_clockPrescaler_t;

/*******************************************************************************
 *                             Struct Definitions                              *
 *******************************************************************************/

/** @brief Structure to hold Timer0 configuration. */
typedef struct {
  uint8 mode : 2;                  /* Timer mode selection */
  uint8 compareOutputMode : 2;     /* Compare output mode selection */
  uint8 clockPre : 3;              /* Clock pre-scaler selection */
} TIMER0_t;

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
/* Global instance of TIMER0_t to hold Timer0 configurations */
extern TIMER0_t g_timer0;

/*******************************************************************************
 *                              Function Prototypes                             *
 *******************************************************************************/

/**
 * @brief Initializes Timer0 with the specified configuration.
 *
 * This function configures Timer0 based on the settings provided in the
 * TIMER0_t structure.
 *
 * @param timer0 Pointer to the TIMER0_t structure containing the
 *               configuration settings for Timer0.
 */
void TIMER0_init(TIMER0_t *timer0);

/**
 * @brief Deinitializes Timer0 and stops its operation.
 *
 * This function resets Timer0 and disables its operation.
 */
void TIMER0_deInit(void);

/* Function prototypes for interrupt handlers, only available if enabled */
/* The below functions allow setting user-defined interrupt handlers for Timer0 */
#ifdef TIMER0_ENABLE_OV_INTERRUPT
/**
 * @brief Sets the overflow interrupt handler for Timer0.
 *
 * @param overFlowInterruptHandler Pointer to the function to be called on
 *                                  Timer0 overflow interrupt.
 */
void TIMER0_setOFInterruptHandler(void (*overFlowInterruptHandler)(void));
#endif

#ifdef TIMER0_ENABLE_CTC_INTERRUPT
/**
 * @brief Sets the compare interrupt handler for Timer0.
 *
 * @param compareInterruptHandler Pointer to the function to be called on
 *                                 Timer0 compare match interrupt.
 */
void TIMER0_setCTCInterruptHandler(void (*compareInterruptHandler)(void));
#endif

#endif /* MCAL_TIMERS_TIMER0_H_ */
