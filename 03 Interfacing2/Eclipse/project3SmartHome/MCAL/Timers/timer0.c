/******************************************************************************
 *
 * Module: timer0
 *
 * File Name: timer0.c
 *
 * Description: This file contains the implementation of functions for
 *              configuring and using Timer0 in various modes, including
 *              normal counting, PWM, and CTC modes.
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "timer0.h"          /* Include Timer0 header file */
#include "../GPIO/gpio.h"    /* Include GPIO header file */
#include <avr/interrupt.h>   /* Include AVR interrupt library */

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

/** @brief Global instance of TIMER0_t to hold Timer0 configurations. */
TIMER0_t g_timer0 = { .mode = TIMER0_MODE_FAST_PWM, .clockPre = TIMER0_CLOCK_DIV_1024,
    .compareOutputMode = TIMER0_COMPARE_FAST_PWM_NIN_INVERTING, .uni.dutyCycle = 0 };

#ifdef TIMER0_ENABLE_OV_INTERRUPT
/** @brief Pointer to the overflow interrupt handler function. */
static void (*TIMER0_overFlowInterruptHandler) (void) = NULL_PTR;
#endif

#ifdef TIMER0_ENABLE_CTC_INTERRUPT
/** @brief Pointer to the compare interrupt handler function. */
static void (*TIMER0_compareInterruptHandler) (void) = NULL_PTR;
#endif

/*******************************************************************************
 *                              Function Definitions                           *
 *******************************************************************************/

/**
 * @brief Initializes Timer0 with the specified configuration.
 *
 * This function configures Timer0 based on the settings provided in the
 * TIMER0_t structure and enables the appropriate modes and interrupts.
 *
 * @param timer0 Pointer to the TIMER0_t structure containing the
 *               configuration settings for Timer0.
 */
void TIMER0_init(TIMER0_t *timer0) {
  TCCR0bits.cs0 = TIMER0_CLOCK_0; /* Set clock source to stop the timer */

  TCCR0bits.wgm00 = timer0->mode & 0x01; /* Set WGM00 based on mode */
  TCCR0bits.wgm01 = timer0->mode >> 1; /* Set WGM01 based on mode */
  TCCR0bits.com0 = timer0->compareOutputMode; /* Set compare output mode */

#ifdef TIMER0_ENABLE_OV_INTERRUPT
  SET_BIT(TIMSK, TOIE0);  /* Enable Timer0 overflow interrupt */
  TIMER0_overFlowInterruptHandler = timer0->overFlowInterruptHandler; /* Set overflow handler */
#endif

#ifdef TIMER0_ENABLE_CTC_INTERRUPT
  SET_BIT(TIMSK, OCIE0);  /* Enable Timer0 CTC interrupt */
  TIMER0_compareInterruptHandler = timer0->compareInterruptHandler; /* Set compare handler */
#endif

  /* Configure the output pin for PWM if not in normal mode */
  if (timer0->compareOutputMode != TIMER0_COMPARE_NORMAL) {
    GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
  }

  /* Set timer operation mode and initialize values */
  switch (timer0->mode)
    {
    case TIMER0_MODE_NORMAL:
      TCCR0bits.foc0 = 1; /* Set FOC0 for normal mode */
      TIMER0_setTimerValue(timer0->uni.timerValue); /* Set initial timer value */
      break;
    case TIMER0_MODE_PWM_PC:
      TCCR0bits.foc0 = 0; /* Clear FOC0 for PWM mode */
      break;
    case TIMER0_MODE_CTC:
      TCCR0bits.foc0 = 1; /* Set FOC0 for CTC mode */
      TIMER0_setCompareValue(timer0->uni.compareValue); /* Set compare value */
      break;
    case TIMER0_MODE_FAST_PWM:
      TCCR0bits.foc0 = 0; /* Clear FOC0 for fast PWM mode */
      TIMER0_setDutyCycle(timer0->uni.dutyCycle); /* Set duty cycle */
      break;
    }

  TCCR0bits.cs0 = timer0->clockPre; /* Set clock prescaler */
}

/**
 * @brief Deinitializes Timer0 and stops its operation.
 *
 * This function resets Timer0 and disables its operation, clearing
 * all associated interrupts.
 */
void TIMER0_deInit(void) {
  TCCR0 = 0; /* Reset Timer0 registers */
  CLEAR_BIT(TIMSK, TOIE0); /* Disable Timer0 overflow interrupt */
  CLEAR_BIT(TIMSK, OCIE0); /* Disable Timer0 CTC interrupt */
}

#ifdef TIMER0_ENABLE_OV_INTERRUPT
/**
 * @brief Sets the overflow interrupt handler for Timer0.
 *
 * @param overFlowInterruptHandler Pointer to the function to be called on
 *                                  Timer0 overflow interrupt.
 */
void TIMER0_setOFInterruptHandler(void (*overFlowInterruptHandler)(void)){
  TIMER0_overFlowInterruptHandler = overFlowInterruptHandler;
}
#endif

#ifdef TIMER0_ENABLE_CTC_INTERRUPT
/**
 * @brief Sets the compare interrupt handler for Timer0.
 *
 * @param compareInterruptHandler Pointer to the function to be called on
 *                                 Timer0 compare match interrupt.
 */
void TIMER0_setCTCInterruptHandler(void (*compareInterruptHandler)(void)){
  TIMER0_compareInterruptHandler = compareInterruptHandler;
}
#endif

#ifdef TIMER0_ENABLE_OV_INTERRUPT
/** @brief ISR for Timer0 overflow interrupt. */
ISR(TIMER0_OVF_vect)
{
  if (NULL_PTR != TIMER0_overFlowInterruptHandler)
    TIMER0_overFlowInterruptHandler(); /* Call the overflow handler if set */
}
#endif

#ifdef TIMER0_ENABLE_CTC_INTERRUPT
/** @brief ISR for Timer0 compare match interrupt. */
ISR(TIMER0_COMP_vect)
{
  if (NULL_PTR != TIMER0_compareInterruptHandler)
    TIMER0_compareInterruptHandler(); /* Call the compare handler if set */
}
#endif
