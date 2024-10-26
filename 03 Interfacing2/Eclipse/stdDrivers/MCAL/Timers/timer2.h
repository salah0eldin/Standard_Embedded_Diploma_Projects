/******************************************************************************
 *
 * Module: Timer2
 *
 * File Name: timer2.h
 *
 * Description: This header file contains the definitions and declarations
 *              necessary for configuring and using Timer2 in various modes.
 *              It supports normal counting, PWM, and CTC modes.
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef MCAL_TIMERS_TIMER2_H_
#define MCAL_TIMERS_TIMER2_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include <avr/io.h>
#include "../../LIB/std_types.h"

/*******************************************************************************
 *                                 Macros                                      *
 *******************************************************************************/

/*#define TIMER2_ENABLE_OV_INTERRUPT*/
/*#define TIMER2_ENABLE_CTC_INTERRUPT*/

/** @brief Set the timer2 register value.
 *
 * @param val The value to set to the timer2 register (TCNT2).
 */
#define TIMER2_setTimerValue(val) (TCNT2 = val)

/** @brief Set the compare value for timer2.
 *
 * @param val The compare value to set (OCR2).
 */
#define TIMER2_setCompareValue(val) (OCR2 = val)

/** @brief Set the duty cycle for PWM.
 *
 * @param val The desired duty cycle percentage (0-100).
 */
#define TIMER2_setDutyCycle(val) (OCR2 = (uint8)((uint16)val * 255 / 100))

/** @brief Clear Pre-scaler of both timer2
 */
#define TIMER2_RESET_PRESCALER()  (SFIOR = (SFIOR | (1 << PSR2)))

/** @brief Checks for Timer2 Asynchronous mode
 */
#define TIMER2_ASYNC_CHECK_TIMER2_UPDATE_BUSY()		(ASSR & (1 << TCN2UB))
#define TIMER2_ASYNC_CHECK_COMPARE2_UPDATE_BUSY()	(ASSR & (1 << OCR2UB))
#define TIMER2_ASYNC_CHECK_CONTROL2_UPDATE_BUSY()	(ASSR & (1 << TCR2UB))

/*******************************************************************************
 *                                 Enums                                       *
 *******************************************************************************/

/** @brief Enumeration for timer2 modes. */
typedef enum {
  TIMER2_MODE_NORMAL,        /* Normal counting mode */
  TIMER2_MODE_PWM_PC,        /* PWM with phase correct mode */
  TIMER2_MODE_CTC,           /* Compare mode */
  TIMER2_MODE_PWM_FAST       /* Fast PWM mode */
} TIMER2_mode_t;

/** @brief Enumeration for timer2 compare output modes. */
typedef enum {
  TIMER2_COMPARE_NORMAL,                     /* Normal port operation, OC2 disconnected. */

  TIMER2_COMPARE_PWM_NON_TOGGLE_OC2,         /* Toggle OC2 on compare match */
  TIMER2_COMPARE_PWM_NON_CLEAR_OC2,          /* Clear OC2 on compare match */
  TIMER2_COMPARE_PWM_NON_SET_OC2,            /* Set OC2 on compare match */

  TIMER2_COMPARE_PWM_FAST_NIN_INVERTING = 2,  /* Clear OC2 on compare match, set OC2 at BOTTOM */
  TIMER2_COMPARE_PWM_FAST_INVERTING,          /* Set OC2 on compare match, clear OC2 at BOTTOM */

  /* Clear OC2 on compare match when up-counting.
   * Set OC2 on compare match when down-counting. */
  TIMER2_COMPARE_PWM_PC_CLEAR_UP = 2,
  /* Set OC2 on compare match when up-counting.
   * Clear OC2 on compare match when down-counting. */
  TIMER2_COMPARE_PWM_PC_CLEAR_DOWN
} TIMER2_compareOutput_mode_t;

/** @brief Enumeration for timer2 clock pre-scaler options. */
typedef enum {
  TIMER2_CLOCK_0,                  /* No clock source (Timer/Counter stopped). */
  TIMER2_CLOCK_DIV_1,              /* clk /(No pre-scaling)       */
  TIMER2_CLOCK_DIV_8,              /* clk /8 (From pre-scaler)    */
  TIMER2_CLOCK_DIV_32,             /* clk /32 (From pre-scaler)   */
  TIMER2_CLOCK_DIV_64,             /* clk /64 (From pre-scaler)   */
  TIMER2_CLOCK_DIV_128,            /* clk /128 (From pre-scaler)  */
  TIMER2_CLOCK_DIV_256,            /* clk /256 (From pre-scaler)  */
  TIMER2_CLOCK_DIV_1024,           /* clk /1024 (From pre-scaler) */
} TIMER2_clockPrescaler_t;

typedef enum{
  TIMER2_SOURCE_CLK_SYNC,	/* Timer/Counter 2 is clocked from the I/O clock, clkI/O */
  TIMER2_SOURCE_EXTERNAL_ASYNC	/* Timer/Counter2 is clocked from a Crystal Oscillator
				   connected to the Timer Oscillator 1 (TOSC1) pin.      */
} TIMER2_clockSource_t;

/*******************************************************************************
 *                             Struct Definitions                               *
 *******************************************************************************/

/** @brief Structure to hold timer2 configuration. */
typedef struct {
  uint8 mode : 2;                  /* Timer mode selection           */
  uint8 compareOutputMode : 2;     /* Compare output mode selection  */
  uint8 clockPre : 3;              /* Clock pre-scaler selection     */
  uint8 clockSource : 1;	   /* Choose clk or TOSC1 (external) */
} TIMER2_t;

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
/* Global instance of timer2_t to hold timer2 configurations */
extern TIMER2_t g_timer2;

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * @brief Initializes timer2 with the specified configuration.
 *
 * This function configures timer2 based on the settings provided in the
 * timer2_t structure.
 *
 * @param timer2 Pointer to the timer2_t structure containing the
 *               configuration settings for timer2.
 */
void TIMER2_init(TIMER2_t *timer2);

/**
 * @brief Deinitializes timer2 and stops its operation.
 *
 * This function resets timer2 and disables its operation.
 */
void TIMER2_deInit(void);

/* Function prototypes for interrupt handlers, only available if enabled */
/* The below functions allow setting user-defined interrupt handlers for timer2 */
#ifdef TIMER2_ENABLE_OV_INTERRUPT
/**
 * @brief Sets the overflow interrupt handler for timer2.
 *
 * @param overFlowInterruptHandler Pointer to the function to be called on
 *                                  timer2 overflow interrupt.
 */
void TIMER2_setOFInterruptHandler(void (*overFlowInterruptHandler)(void));
#endif

#ifdef TIMER2_ENABLE_CTC_INTERRUPT
/**
 * @brief Sets the compare interrupt handler for timer2.
 *
 * @param compareInterruptHandler Pointer to the function to be called on
 *                                 timer2 compare match interrupt.
 */
void TIMER2_setCTCInterruptHandler(void (*compareInterruptHandler)(void));
#endif

#endif /* MCAL_TIMERS_TIMER2_H_ */
