/******************************************************************************
 *
 * Module: Timer1
 *
 * File Name: timer1.h
 *
 * Description: This file contains the implementation of functions for
 *              configuring and using Timer1 in various modes, including
 *              normal counting, PWM, and CTC, IC modes.
 *
 * Created on: Oct 8, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef MCAL_TIMERS_TIMER1_H_
#define MCAL_TIMERS_TIMER1_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include <avr/io.h>
#include "../../LIB/std_types.h"

/*******************************************************************************
 *                                 Macros                                      *
 *******************************************************************************/

#define TIMER1_ENABLE_IC_INTERRUPT
/*#define TIMER1_ENABLE_OV_INTERRUPT*/
/*#define TIMER1_ENABLE_CTC_A_INTERRUPT*/
/*#define TIMER1_ENABLE_CTC_B_INTERRUPT*/

#define TIMER1_PRE_SCALER	8

/** @brief Set the Timer1 register value.
 *
 * @param val The value to set to the Timer1 register (TCNT1).
 */
#define TIMER1_setTimerValue(val) (TCNT1 = val)

/** @brief Set the Timer1 Input Capture Regsiter value.
 *
 * @param val The value to set to the Input Capture Regsiter register (ICR1).
 */
#define TIMER1_setInputCapture(val) (ICR1 = val)

/** @brief Set the compare value for timer1A.
 *
 * @param val The compare value to set (OCR1A).
 */
#define TIMER1_setCompareValue_A(val) (OCR1A = val)

/** @brief Set the compare value for timer1B.
 *
 * @param val The compare value to set (OCR1B).
 */
#define TIMER1_setCompareValue_B(val) (OCR1B = val)

/** @brief Configure the Input Capture Noise Canceler.
 *
 * @param val The desired value to enable or disable the Noise Canceler.
 */
#define	TIMER1_IC_NoiseCancelr_Control(val)   (TCCR1Bbits.icnc1 = val)

/** @brief Select the Input Capture edge (rising or falling).
 *
 * @param val The desired edge select value (1 for rising, 0 for falling).
 */
#define TIMER1_IC_EdgeSelect(val) 	      (TCCR1Bbits.ices1 = val)

/** @brief Enable Timer1 with the configured clock prescaler.
 */
#define TIMER1_ENABLE()	(TCCR1Bbits.cs1 = g_timer1.clockPre)

/** @brief Disable Timer1 by clearing the clock source.
 */
#define TIMER1_DISABLE()  (TCCR1Bbits.cs1 = 0)

/** @brief Clear Pre-scaler of both timer1 and timer0 as they share same pre-scaler
 */
#define TIMER1_AND_TIMER0_RESET_PRESCALER()  (SFIOR = (SFIOR | (1 << PSR10)));

/*******************************************************************************
 *                                 Enums                                       *
 *******************************************************************************/

/** @brief Enumeration for timer1 modes. */
typedef enum {
  TIMER1_MODE_NORMAL, /* Normal counting mode */

  TIMER1_MODE_PWM_PC_8BIT, /* PWM, Phase Correct, 8-bit  */
  TIMER1_MODE_PWM_PC_9BIT, /* PWM, Phase Correct, 9-bit  */
  TIMER1_MODE_PWM_PC_10BIT, /* PWM, Phase Correct, 10-bit */

  TIMER1_MODE_CTC_OCR1A, /* CTC, Compare mode TOP: OCR1A */

  TIMER1_MODE_PWM_FAST_8BIT, /* Fast PWM, 8-bit  */
  TIMER1_MODE_PWM_FAST_9BIT, /* Fast PWM, 9-bit  */
  TIMER1_MODE_PWM_FAST_10BIT, /* Fast PWM, 10-bit */

  TIMER1_MODE_PWM_PC_FC_ICR1, /* PWM, Phase and Frequency Correct TOP: ICR1  */
  TIMER1_MODE_PWM_PC_FC_OCR1A, /* PWM, Phase and Frequency Correct TOP: OCR1A */

  TIMER1_MODE_PWM_PC_ICR1, /* PWM, Phase Correct TOP: ICR1  */
  TIMER1_MODE_PWM_PC_OCR1A, /* PWM, Phase Correct TOP: OCR1A */

  TIMER1_MODE_CTC_ICR1, /* CTC, Compare mode TOP: ICR1 */

  TIMER1_MODE_PWM_FAST_ICR1 = 14, /* Fast PWM TOP: ICR1  */
  TIMER1_MODE_PWM_FAST_OCR1A, /* Fast PWM TOP: OCR1A */
} TIMER1_mode_t;

/** @brief Enumeration for timer1 compare output modes. */
typedef enum {
  TIMER1_COMPARE_NORMAL, /* Normal port operation, OC1A/OC1B disconnected. */

  TIMER1_COMPARE_PWM_NON_TOGGLE_OC1, /* Toggle OC1A/OC1B on compare match.                         */
  TIMER1_COMPARE_PWM_NON_CLEAR_OC1, /* Clear OC1A/OC1B on compare match (Set output to low level) */
  TIMER1_COMPARE_PWM_NON_SET_OC1, /* Set OC1A/OC1B on compare match (Set output to high level)  */

  /* WGM13:0 = 15: Toggle OC1A on Compare Match, OC1B disconnected (normal port operation).
   * For all other WGM13:0 settings, normal port operation, OC1A/OC1B disconnected. */
  TIMER1_COMPARE_PWM_FAST_SPECIAL = 1,
  TIMER1_COMPARE_PWM_FAST_NIN_INVERTING, /* Clear OC1A/OC1B on compare match, set OC1A/OC1B at BOTTOM, (non-inverting mode) */
  TIMER1_COMPARE_PWM_FAST_INVERTING, /* Set OC1A/OC1B on compare match, clear OC1A/OC1B at BOTTOM, (inverting mode)     */

  /* WGM13:0 = 9 or 14: Toggle OC1A on Compare Match, OC1B disconnected (normal port operation).
   * For all other WGM13:0 settings, normal port operation, OC1A/OC1B disconnected. */
  TIMER1_COMPARE_PWM_PC_SPECIAL = 1,
  /* Clear OC1A/OC1B on compare match when up-counting.
   * Set OC1A/OC1B on compare match when down-counting */
  TIMER1_COMPARE_PWM_PC_CLEAR_UP,
  /* Set OC1A/OC1B on compare match when up-counting.
   * Clear OC1A/OC1B on compare match when down-counting.*/
  TIMER1_COMPARE_PWM_PC_CLEAR_DOWN
} TIMER1_compareOutput_mode_t;

/** @brief Enumeration for timer1 clock pre-scaler options. */
typedef enum {
  TIMER1_CLOCK_0, /* No clock source (Timer/Counter stopped). */
  TIMER1_CLOCK_DIV_1, /* clk /(No pre-scaling) */
  TIMER1_CLOCK_DIV_8, /* clk /8 (From pre-scaler) */
  TIMER1_CLOCK_DIV_64, /* clk /64 (From pre-scaler) */
  TIMER1_CLOCK_DIV_256, /* clk /256 (From pre-scaler) */
  TIMER1_CLOCK_DIV_1024, /* clk /1024 (From pre-scaler) */
  TIMER1_CLOCK_EXTERNAL_FALLING, /* External clock source on T1 pin. Clock on falling edge. */
  TIMER1_CLOCK_EXTERNAL_RISING /* External clock source on T1 pin. Clock on rising edge. */
} TIMER1_clockPrescaler_t;

/** @brief Enumeration for Input Capture Noise Canceler. */
typedef enum{
  TIMER1_INPUT_CAPTURE_NOISE_CALNCELER_DISABLE,
  TIMER1_INPUT_CAPTURE_NOISE_CALNCELER_ENABLE
} TIMER1_inputCaptureNoise_t;

/** @brief Enumeration for Input Capture edge select. */
typedef enum{
  TIMER1_INPUT_CAPTURE_FALLING,   /* Capture on falling edge */
  TIMER1_INPUT_CAPTURE_RAISING    /* Capture on rising edge */
} TIMER1_inputCaptureEdge_t;

/*******************************************************************************
 *                             Struct Definitions                               *
 *******************************************************************************/

/** @brief Structure to hold timer1 configuration. */
typedef struct {
  uint8 mode :4;               /* Timer mode selection */
  uint8 compareOutputModeA :2; /* Compare A output mode selection */
  uint8 compareOutputModeB :2; /* Compare B output mode selection */
  uint8 clockPre : 3;          /* Clock prescaler selection */

  uint8 inputCaptureNoise : 1; /* Set to activate Noise Canceler                 */
  uint8 inputCaptureEdge  : 1; /* Set to select Rising Edge and Clear to falling */
} TIMER1_t;

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
/* Global instance of timer1_t to hold timer1 configurations */
extern TIMER1_t g_timer1;

/*******************************************************************************
 *                              Function Prototypes                             *
 *******************************************************************************/

/**
 * @brief Initializes timer1 with the specified configuration.
 *
 * This function configures timer1 based on the settings provided in the
 * timer1_t structure.
 *
 * @param timer1 Pointer to the timer1_t structure containing the
 *               configuration settings for timer1.
 */
void TIMER1_init(TIMER1_t *timer1);

/**
 * @brief De-initializes timer1 and stops its operation.
 *
 * This function resets timer1 and disables its operation.
 */
void TIMER1_deInit(void);

/** @brief Set the duty cycle for PWM TIMER1A.
 *
 * @param dutyCycle The desired duty cycle percentage (0-100).
 */
void TIMER1_setDutyCycle_A(uint8 dutyCycle);

/** @brief Set the duty cycle for PWM TIMER1B.
 *
 * @param dutyCycle The desired duty cycle percentage (0-100).
 */
void TIMER1_setDutyCycle_B(uint8 dutyCycle);

/* Function prototypes for interrupt handlers, only available if enabled */
/* The below functions allow setting user-defined interrupt handlers for timer1 */
#ifdef TIMER1_ENABLE_IC_INTERRUPT
/**
 * @brief Sets the Input Capture interrupt handler for timer1.
 *
 * @param overFlowInterruptHandler Pointer to the function to be called on
 *                                  timer1 Input Capture interrupt.
 */
void TIMER1_set_IC_InterruptHandler(void (*inputCaptureInterruptHandler)(void));
#endif

#ifdef TIMER1_ENABLE_OV_INTERRUPT
/**
 * @brief Sets the overflow interrupt handler for timer1.
 *
 * @param overFlowInterruptHandler Pointer to the function to be called on
 *                                  timer1 overflow interrupt.
 */
void TIMER1_set_OF_InterruptHandler(void (*overFlowInterruptHandler)(void));
#endif

#ifdef TIMER1_ENABLE_CTC_A_INTERRUPT
/**
 * @brief Sets the compare interrupt handler for timer1A.
 *
 * @param compareInterruptHandler Pointer to the function to be called on
 *                                 timer1A compare match interrupt.
 */
void TIMER1_set_CTC_A_InterruptHandler(void (*compareInterruptHandlerA)(void));
#endif

#ifdef TIMER1_ENABLE_CTC_B_INTERRUPT
/**
 * @brief Sets the compare interrupt handler for timer1B.
 *
 * @param compareInterruptHandler Pointer to the function to be called on
 *                                 timer1B compare match interrupt.
 */
void TIMER1_set_CTC_B_InterruptHandler(void (*compareInterruptHandlerB)(void));
#endif

#endif /* MCAL_TIMERS_TIMER1_H_ */
