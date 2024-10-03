/******************************************************************************
 *
 * Module: timer0
 *
 * File Name: timer0.c
 *
 * Description: 
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#include "timer0.h"
#include "../GPIO/gpio.h"
#include <avr/interrupt.h>

TIMER0_t g_timer0 =
  { .mode = TIMER0_MODE_FAST_PWM, .clockPre = TIMER0_CLOCK_DIV_1024, .compareOutputMode =
      TIMER0_COMPARE_FAST_PWM_NIN_INVERTING, .uni.dutyCycle = 0 };

#ifdef TIMER0_ENABLE_OV_INTERRUPT
static void (*TIMER0_overFlowInterruptHandler) (void) = NULL_PTR;
#endif

#ifdef TIMER0_ENABLE_CTC_INTERRUPT
static void (*TIMER0_compareInterruptHandler) (void) = NULL_PTR;
#endif

void TIMER0_init (TIMER0_t *timer0)
{
  TCCR0bits.cs0 = TIMER0_CLOCK_0;

  TCCR0bits.wgm00 = timer0->mode & 0x01;

  TCCR0bits.wgm01 = timer0->mode >> 1;

  TCCR0bits.com0 = timer0->compareOutputMode;

#ifdef TIMER0_ENABLE_OV_INTERRUPT
  SET_BIT(TIMSK, TOIE0);
  TIMER0_overFlowInterruptHandler = timer0->overFlowInterruptHandler;
#endif

#ifdef TIMER0_ENABLE_CTC_INTERRUPT
  SET_BIT(TIMSK, OCIE0);
  TIMER0_compareInterruptHandler = timer0->compareInterruptHandler;
#endif

  if (timer0->compareOutputMode != TIMER0_COMPARE_NORMAL)
    {
      GPIO_setupPinDirection (PORTB_ID, PIN3_ID, PIN_OUTPUT);
    }

  switch (timer0->mode)
    {
    case TIMER0_MODE_NORMAL:
      TCCR0bits.foc0 = 1;
      TIMER0_setTimerValue(timer0->uni.timerValue);
      break;
    case TIMER0_MODE_PWM_PC:
      TCCR0bits.foc0 = 0;
      break;
    case TIMER0_MODE_CTC:
      TCCR0bits.foc0 = 1;
      TIMER0_setCompareValue(timer0->uni.compareValue);
      break;
    case TIMER0_MODE_FAST_PWM:
      TCCR0bits.foc0 = 0;
      TIMER0_setDutyCycle(timer0->uni.dutyCycle);
      break;
    }

  TCCR0bits.cs0 = timer0->clockPre;
}

#ifdef TIMER0_ENABLE_OV_INTERRUPT
ISR(TIMER0_OVF_vect)
{
  if (NULL_PTR != TIMER0_overFlowInterruptHandler)
    TIMER0_overFlowInterruptHandler ();
}
#endif

#ifdef TIMER0_ENABLE_CTC_INTERRUPT
ISR(TIMER0_COMP_vect)
{
  if (NULL_PTR != TIMER0_compareInterruptHandler)
    TIMER0_compareInterruptHandler ();
}
#endif
