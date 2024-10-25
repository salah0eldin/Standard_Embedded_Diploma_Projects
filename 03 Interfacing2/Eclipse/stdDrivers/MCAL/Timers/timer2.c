/******************************************************************************
 *
 * Module: Timer2
 *
 * File Name: timer2.c
 *
 * Description: This file contains the implementation of functions for
 *              configuring and using Timer2 in various modes, including
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
#include "timer2.h"          /* Include timer2 header file */
#include "../GPIO/gpio.h"    /* Include GPIO header file */
#include <avr/interrupt.h>   /* Include AVR interrupt library */

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

/** @brief Global instance of timer2_t to hold timer2 configurations. */
TIMER2_t g_timer2 = { .mode = TIMER2_MODE_PWM_FAST, .clockPre = TIMER2_CLOCK_DIV_1024,
    .compareOutputMode = TIMER2_COMPARE_PWM_FAST_NIN_INVERTING,
.clockSource = TIMER2_SOURCE_CLK_SYNC};

#ifdef TIMER2_ENABLE_OV_INTERRUPT
/** @brief Pointer to the overflow interrupt handler function. */
static void (*TIMER2_overFlowInterruptHandler) (void) = NULL_PTR;
#endif

#ifdef TIMER2_ENABLE_CTC_INTERRUPT
/** @brief Pointer to the compare interrupt handler function. */
static void (*TIMER2_compareInterruptHandler) (void) = NULL_PTR;
#endif

/*******************************************************************************
 *                              Function Definitions                           *
 *******************************************************************************/

/**
 * @brief Initializes timer2 with the specified configuration.
 *
 * This function configures timer2 based on the settings provided in the
 * timer2_t structure and enables the appropriate modes and interrupts.
 *
 * @param timer2 Pointer to the timer2_t structure containing the
 *               configuration settings for timer2.
 */
void TIMER2_init(TIMER2_t *timer2) {
  TCCR2bits.cs2 = TIMER2_CLOCK_0; /* Set clock source to stop the timer */

  /* Set Mode */
  TCCR2bits.wgm20 = timer2->mode & 0x01; /* Set WGM20 based on mode */
  TCCR2bits.wgm21 = timer2->mode >> 1; /* Set WGM21 based on mode */

  /* Set Compare Mode */
  TCCR2bits.com2 = timer2->compareOutputMode; /* Set compare output mode */

  /* Enable needed interrupts */
#ifdef TIMER2_ENABLE_OV_INTERRUPT
  SET_BIT(TIMSK, TOIE2);  /* Enable timer2 overflow interrupt */
#endif

#ifdef TIMER2_ENABLE_CTC_INTERRUPT
  SET_BIT(TIMSK, OCIE2);  /* Enable timer2 CTC interrupt */
#endif

  /* Configure the output pin if not in normal mode */
  if (timer2->compareOutputMode != TIMER2_COMPARE_NORMAL) {
    GPIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_OUTPUT);
  }

  /* Set timer operation mode  */
  switch (timer2->mode)
    {
    case TIMER2_MODE_NORMAL:
    case TIMER2_MODE_CTC:
      TCCR2bits.foc2 = 1; /* Set FOC2 for normal mode OR CTC mode */
      break;
    case TIMER2_MODE_PWM_PC:
    case TIMER2_MODE_PWM_FAST:
      TCCR2bits.foc2 = 0; /* Clear FOC2 for PWM mode OR fast PWM mode */
      break;
    }

  /* Set sync or A-sync */
  ASSRbits.as2 = timer2->clockSource;

  /* Set clock pre-scaler */
  TCCR2bits.cs2 = timer2->clockPre;
}

/**
 * @brief De-initializes timer2 and stops its operation.
 *
 * This function resets timer2 and disables its operation, clearing
 * all associated interrupts.
 */
void TIMER2_deInit(void) {
  TCCR2 = 0; /* Reset timer2 registers */
  CLEAR_BIT(TIMSK, TOIE2); /* Disable timer2 overflow interrupt */
  CLEAR_BIT(TIMSK, OCIE2); /* Disable timer2 CTC interrupt */
}

#ifdef TIMER2_ENABLE_OV_INTERRUPT
/**
 * @brief Sets the overflow interrupt handler for timer2.
 *
 * @param overFlowInterruptHandler Pointer to the function to be called on
 *                                  timer2 overflow interrupt.
 */
void TIMER2_setOFInterruptHandler(void (*overFlowInterruptHandler)(void)){
  TIMER2_overFlowInterruptHandler = overFlowInterruptHandler;
}
#endif

#ifdef TIMER2_ENABLE_CTC_INTERRUPT
/**
 * @brief Sets the compare interrupt handler for timer2.
 *
 * @param compareInterruptHandler Pointer to the function to be called on
 *                                 timer2 compare match interrupt.
 */
void TIMER2_setCTCInterruptHandler(void (*compareInterruptHandler)(void)){
  TIMER2_compareInterruptHandler = compareInterruptHandler;
}
#endif

/*******************************************************************************
 *                                 ISR Functions                               *
 *******************************************************************************/
#ifdef TIMER2_ENABLE_OV_INTERRUPT
/** @brief ISR for timer2 overflow interrupt. */
ISR(TIMER2_OVF_vect)
{
  if (NULL_PTR != TIMER2_overFlowInterruptHandler)
    TIMER2_overFlowInterruptHandler(); /* Call the overflow handler if set */
}
#endif

#ifdef TIMER2_ENABLE_CTC_INTERRUPT
/** @brief ISR for timer2 compare match interrupt. */
ISR(TIMER2_COMP_vect)
{
  if (NULL_PTR != TIMER2_compareInterruptHandler)
    TIMER2_compareInterruptHandler(); /* Call the compare handler if set */
}
#endif

