/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.c
 *
 * Description: This source file implements the functions necessary for
 *              initializing, deinitializing, and handling interrupts for
 *              Timer0, Timer1, and Timer2 in various modes.
 *
 * Created on: Nov 1, 2024
 *
 * Author: Shahd Gamal
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*******************************************************************************
 *                            Global Variables                                 *
 *******************************************************************************/

/* Global callback pointers for Timer interrupts */
static void (*g_Timer0callBack)(void) = NULL_PTR;
static void (*g_Timer1callBack)(void) = NULL_PTR;
static void (*g_Timer2callBack)(void) = NULL_PTR;

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

/**
 * @brief Initializes a Timer with the specified configuration.
 *
 * This function configures the selected Timer based on the provided
 * configuration settings, such as mode and clock prescaler.
 *
 * @param Config_Ptr Pointer to TIMER_t structure with configuration settings.
 */
void TIMER_init(const TIMER_t *Config_Ptr) {

  switch (Config_Ptr->timer_ID)
    {
    case TIMER0_ID:
      /* Set Timer0 mode and initial values */
      TCCR0 = (Config_Ptr->mode == TIMER_MODE_NORMAL) ? (1 << FOC0) : ((1 << FOC0) | (1 << WGM01));
      TCNT0 = Config_Ptr->initial_value;
      OCR0 = Config_Ptr->compare_value;

      /* Enable Timer0 interrupt based on mode */
      TIMSK |= (Config_Ptr->mode == TIMER_MODE_NORMAL) ? (1 << TOIE0) : (1 << OCIE0);

      /* Set Timer0 clock prescaler */
      TCCR0 |= Config_Ptr->timer_clock;
      break;

    case TIMER1_ID:
      /* Set Timer1 mode and initial values */
      TCCR1A = (1 << FOC1A);
      TCNT1 = Config_Ptr->initial_value;
      OCR1A = Config_Ptr->compare_value;

      /* Enable Timer1 interrupt based on mode */
      TIMSK |= (Config_Ptr->mode == TIMER_MODE_NORMAL) ? (1 << TOIE1) : (1 << OCIE1A);

      /* Set Timer1 mode and clock prescaler */
      TCCR1B = (Config_Ptr->mode == TIMER_MODE_COMPARE) ? (1 << WGM12) | (Config_Ptr->timer_clock) : (Config_Ptr->timer_clock);
      break;

    case TIMER2_ID:
      /* Set Timer2 mode and initial values */
      TCCR2 = (Config_Ptr->mode == TIMER_MODE_NORMAL) ? (1 << FOC2) : ((1 << FOC2) | (1 << WGM21));
      TCNT2 = Config_Ptr->initial_value;
      OCR2 = Config_Ptr->compare_value;

      /* Enable Timer2 interrupt based on mode */
      TIMSK |= (Config_Ptr->mode == TIMER_MODE_NORMAL) ? (1 << TOIE2) : (1 << OCIE2);

      /* Set Timer2 clock prescaler */
      TCCR2 |= Config_Ptr->timer_clock;
      break;
    }
}

/**
 * @brief Deinitializes and stops the specified Timer.
 *
 * This function stops the selected Timer by clearing its control
 * registers and disabling its interrupts.
 *
 * @param timer_type Identifier for the Timer to deinitialize.
 */
void TIMER_deInit(TIMER_ID timer_type) {
  switch (timer_type)
    {
    case TIMER0_ID:
      TCCR0 = TCNT0 = OCR0 = 0;        /* Reset Timer0 registers */
      TIMSK &= 0xFC;                   /* Disable Timer0 interrupts */
      break;
    case TIMER1_ID:
      TCCR1A = TCCR1B = TCNT1 = OCR1A = 0;  /* Reset Timer1 registers */
      TIMSK &= 0xC3;                        /* Disable Timer1 interrupts */
      break;
    case TIMER2_ID:
      TCCR2 = TCNT2 = OCR2 = 0;        /* Reset Timer2 registers */
      TIMSK &= 0x3F;                   /* Disable Timer2 interrupts */
      break;
    }
}

/**
 * @brief Sets a callback function for the Timer interrupt.
 *
 * This function assigns a user-defined function to be called during the
 * specified Timer’s interrupt.
 *
 * @param a_ptr Pointer to the callback function.
 * @param a_timer_ID Identifier for the Timer to assign the callback.
 */
void TIMER_setCallBack(void (*a_ptr)(void), TIMER_ID a_timer_ID) {
  switch (a_timer_ID)
    {
    case TIMER0_ID:
      g_Timer0callBack = a_ptr;
      break;
    case TIMER1_ID:
      g_Timer1callBack = a_ptr;
      break;
    case TIMER2_ID:
      g_Timer2callBack = a_ptr;
      break;
    }
}

/*******************************************************************************
 *                          Interrupt Service Routines                         *
 *******************************************************************************/

/**
 * @brief Timer0 Overflow ISR.
 *
 * This interrupt service routine is called when Timer0 overflows.
 */
ISR(TIMER0_OVF_vect) {
  if (g_Timer0callBack != NULL_PTR) {
    (*g_Timer0callBack)();
  }
}

/**
 * @brief Timer0 Compare Match ISR.
 *
 * This interrupt service routine is called on a Timer0 compare match.
 */
ISR(TIMER0_COMP_vect) {
  if (g_Timer0callBack != NULL_PTR) {
    (*g_Timer0callBack)();
  }
}

/**
 * @brief Timer1 Overflow ISR.
 *
 * This interrupt service routine is called when Timer1 overflows.
 */
ISR(TIMER1_OVF_vect) {
  if (g_Timer1callBack != NULL_PTR) {
    (*g_Timer1callBack)();
  }
}

/**
 * @brief Timer1 Compare Match ISR.
 *
 * This interrupt service routine is called on a Timer1 compare match.
 */
ISR(TIMER1_COMPA_vect) {
  if (g_Timer1callBack != NULL_PTR) {
    (*g_Timer1callBack)();
  }
}

/**
 * @brief Timer2 Overflow ISR.
 *
 * This interrupt service routine is called when Timer2 overflows.
 */
ISR(TIMER2_OVF_vect) {
  if (g_Timer2callBack != NULL_PTR) {
    (*g_Timer2callBack)();
  }
}

/**
 * @brief Timer2 Compare Match ISR.
 *
 * This interrupt service routine is called on a Timer2 compare match.
 */
ISR(TIMER2_COMP_vect) {
  if (g_Timer2callBack != NULL_PTR) {
    (*g_Timer2callBack)();
  }
}
