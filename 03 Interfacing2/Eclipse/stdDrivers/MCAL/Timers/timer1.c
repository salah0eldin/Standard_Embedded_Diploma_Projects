/******************************************************************************
 *
 * Module: Timer1
 *
 * File Name: timer1.c
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

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "timer1.h"
#include "../GPIO/gpio.h"
#include <avr/interrupt.h>

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

/** @brief Global instance of TIMER0_t to hold Timer0 configurations. */
TIMER1_t g_timer1 = { .mode = TIMER1_MODE_NORMAL, .clockPre = TIMER1_CLOCK_DIV_8,
    .compareOutputModeA = TIMER1_COMPARE_NORMAL, .compareOutputModeB = TIMER1_COMPARE_NORMAL,
    .inputCaptureNoise = TIMER1_INPUT_CAPTURE_NOISE_CALNCELER_DISABLE, .inputCaptureEdge =
	TIMER1_INPUT_CAPTURE_RAISING };

static uint16 TIMER1_TOP = 0;

#ifdef TIMER1_ENABLE_IC_INTERRUPT
/** @brief Pointer to the overflow interrupt handler function. */
static void (*TIMER1_inputCaptureInterruptHandler)(void) = NULL_PTR;
#endif

#ifdef TIMER1_ENABLE_OV_INTERRUPT
/** @brief Pointer to the overflow interrupt handler function. */
static void (*TIMER1_overFlowInterruptHandler)(void) = NULL_PTR;
#endif

#ifdef TIMER1_ENABLE_CTC_A_INTERRUPT
/** @brief Pointer to the compare interrupt handler function. */
static void (*TIMER1_compareInterruptHandler_A)(void) = NULL_PTR;
#endif

#ifdef TIMER1_ENABLE_CTC_B_INTERRUPT
/** @brief Pointer to the compare interrupt handler function. */
static void (*TIMER1_compareInterruptHandler_B)(void) = NULL_PTR;
#endif

/*******************************************************************************
 *                              Static Functions                               *
 *******************************************************************************/
static inline void TIMER1_setTopValue(uint8 mode) {
  /* Set TOP value */
  switch (mode)
    {
    case TIMER1_MODE_NORMAL:
      TIMER1_TOP = 0XFFFF;
      break;
    case TIMER1_MODE_PWM_PC_8BIT:
    case TIMER1_MODE_PWM_FAST_8BIT:
      TIMER1_TOP = 0X00FF;
      break;
    case TIMER1_MODE_PWM_PC_9BIT:
    case TIMER1_MODE_PWM_FAST_9BIT:
      TIMER1_TOP = 0X01FF;
      break;
    case TIMER1_MODE_PWM_PC_10BIT:
    case TIMER1_MODE_PWM_FAST_10BIT:
      TIMER1_TOP = 0X03FF;
      break;
    case TIMER1_MODE_CTC_OCR1A:
    case TIMER1_MODE_PWM_PC_FC_OCR1A:
    case TIMER1_MODE_PWM_PC_OCR1A:
    case TIMER1_MODE_PWM_FAST_OCR1A:
      TIMER1_TOP = OCR1A;
      break;
    case TIMER1_MODE_CTC_ICR1:
    case TIMER1_MODE_PWM_PC_FC_ICR1:
    case TIMER1_MODE_PWM_PC_ICR1:
    case TIMER1_MODE_PWM_FAST_ICR1:
      TIMER1_TOP = ICR1;
      break;

    }
}

/*******************************************************************************
 *                              Function Definitions                           *
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
void TIMER1_init(TIMER1_t *timer1) {
  TCCR1Bbits.cs1 = 0; /* Set clock source to stop the timer */

  /* Set Mode */
  TCCR1Abits.wgm1_01 = timer1->mode;
  TCCR1Bbits.wgm1_23 = timer1->mode >> 2;

  /* Set Compare Modes */
  TCCR1Abits.com1a = timer1->compareOutputModeA; /* Set compare A output mode */
  TCCR1Abits.com1b = timer1->compareOutputModeB; /* Set compare B output mode */

  /* Enable needed interrupts */
#ifdef TIMER1_ENABLE_IC_INTERRUPT
  SET_BIT(TIMSK, TICIE1); /* Enable Timer1 input capture interrupt */
#endif

#ifdef TIMER1_ENABLE_OV_INTERRUPT
  SET_BIT(TIMSK, TOIE1); /* Enable Timer1 overflow interrupt */
#endif

#ifdef TIMER1_ENABLE_CTC_A_INTERRUPT
  SET_BIT(TIMSK, OCIE1A); /* Enable Timer1 CTC A interrupt */
#endif

#ifdef TIMER1_ENABLE_CTC_B_INTERRUPT
  SET_BIT(TIMSK, OCIE1B); /* Enable Timer1 CTC B interrupt */
#endif

  /* Configure the output pins if not in normal mode */
  if (timer1->compareOutputModeA != TIMER1_COMPARE_NORMAL) {
    GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
  }
  if (timer1->compareOutputModeB != TIMER1_COMPARE_NORMAL) {
    GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_OUTPUT);
  }

  /* Set timer operation mode */
  switch (timer1->mode)
    {
    case TIMER1_MODE_NORMAL:
    case TIMER1_MODE_CTC_ICR1:
    case TIMER1_MODE_CTC_OCR1A:
      TCCR1Abits.foc1a = 1; /* Set FOC1A for normal mode OR CTC mode */
      TCCR1Abits.foc1b = 1; /* Set FOC1B for normal mode OR CTC mode */
      break;
    default:
      TCCR1Abits.foc1a = 0; /* Clear FOC1A for any PWM mode */
      TCCR1Abits.foc1b = 0; /* Clear FOC1B for any PWM mode */
      break;
    }

  /* Set input capture settings */
  TIMER1_IC_NoiseCancelr_Control(timer1->inputCaptureNoise); /* Noise Canceler enable/disable */
  TIMER1_IC_EdgeSelect(timer1->inputCaptureEdge); /* Clock Edge select to trigger interrupt*/

  /* Set clock pre-scaler */
  TCCR1Bbits.cs1 = timer1->clockPre;
}

/**
 * @brief De-initializes timer1 and stops its operation.
 *
 * This function resets timer1 and disables its operation.
 */
void TIMER1_deInit(void) {
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK &= 0b11000011;
}

/** @brief Set the duty cycle for PWM TIMER1A.
 *
 * @param dutyCycle The desired duty cycle percentage (0-100).
 */
void TIMER1_setDutyCycle_A(uint8 dutyCycle) {
  TIMER1_setTopValue(g_timer1.mode);
  OCR1A = (uint16) ((uint32) dutyCycle * TIMER1_TOP / 100);
}

/** @brief Set the duty cycle for PWM TIMER1B.
 *
 * @param dutyCycle The desired duty cycle percentage (0-100).
 */
void TIMER1_setDutyCycle_B(uint8 dutyCycle) {
  TIMER1_setTopValue(g_timer1.mode);
  OCR1B = (uint16) ((uint32) dutyCycle * TIMER1_TOP / 100);
}

/* Function prototypes for interrupt handlers, only available if enabled */
/* The below functions allow setting user-defined interrupt handlers for timer1 */
#ifdef TIMER1_ENABLE_IC_INTERRUPT
/**
 * @brief Sets the Input Capture interrupt handler for timer1.
 *
 * @param overFlowInterruptHandler Pointer to the function to be called on
 *                                  timer1 Input Capture interrupt.
 */
void TIMER1_set_IC_InterruptHandler(void (*inputCaptureInterruptHandler)(void)) {
  TIMER1_inputCaptureInterruptHandler = inputCaptureInterruptHandler;
}
#endif

#ifdef TIMER1_ENABLE_OV_INTERRUPT
/**
 * @brief Sets the overflow interrupt handler for timer1.
 *
 * @param overFlowInterruptHandler Pointer to the function to be called on
 *                                  timer1 overflow interrupt.
 */
void TIMER1_set_OF_InterruptHandler(void (*overFlowInterruptHandler)(void)) {
  TIMER1_overFlowInterruptHandler = overFlowInterruptHandler;
}
#endif

#ifdef TIMER1_ENABLE_CTC_A_INTERRUPT
/**
 * @brief Sets the compare interrupt handler for timer1A.
 *
 * @param compareInterruptHandler Pointer to the function to be called on
 *                                 timer1A compare match interrupt.
 */
void TIMER1_set_CTC_A_InterruptHandler(void (*compareInterruptHandlerA)(void)) {
  TIMER1_compareInterruptHandler_A = compareInterruptHandlerA;
}
#endif

#ifdef TIMER1_ENABLE_CTC_B_INTERRUPT
/**
 * @brief Sets the compare interrupt handler for timer1B.
 *
 * @param compareInterruptHandler Pointer to the function to be called on
 *                                 timer1B compare match interrupt.
 */
void TIMER1_set_CTC_B_InterruptHandler(void (*compareInterruptHandlerB)(void)) {
  TIMER1_compareInterruptHandler_B = compareInterruptHandlerB;
}
#endif

/*******************************************************************************
 *                                 ISR Functions                               *
 *******************************************************************************/

#ifdef TIMER1_ENABLE_IC_INTERRUPT
/** @brief ISR for Timer1 Input Capture interrupt. */
ISR(TIMER1_CAPT_vect) {
  if (NULL_PTR != TIMER1_inputCaptureInterruptHandler)
    TIMER1_inputCaptureInterruptHandler(); /* Call the input capture handler if set */
}
#endif

#ifdef TIMER1_ENABLE_OV_INTERRUPT
/** @brief ISR for Timer1 overflow interrupt. */
ISR(TIMER1_OVF_vect) {
  if (NULL_PTR != TIMER1_overFlowInterruptHandler)
    TIMER1_overFlowInterruptHandler(); /* Call the overflow handler if set */
}
#endif

#ifdef TIMER1_ENABLE_CTC_A_INTERRUPT
/** @brief ISR for Timer1 compare A match interrupt. */
ISR(TIMER1_COMPA_vect) {
  if (NULL_PTR != TIMER1_compareInterruptHandler_A)
    TIMER1_compareInterruptHandler_A(); /* Call the compare A handler if set */
}
#endif

#ifdef TIMER1_ENABLE_CTC_B_INTERRUPT
/** @brief ISR for Timer1 compare B match interrupt. */
ISR(TIMER1_COMPB_vect) {
  if (NULL_PTR != TIMER1_compareInterruptHandler_B)
    TIMER1_compareInterruptHandler_B(); /* Call the compare B handler if set */
}
#endif
