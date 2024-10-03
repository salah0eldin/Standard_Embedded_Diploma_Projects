 /******************************************************************************
 *
 * Module: timer0
 *
 * File Name: timer0.h
 *
 * Description: 
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef MCAL_TIMERS_TIMER0_H_
#define MCAL_TIMERS_TIMER0_H_

#include "../std_types.h"

/*#define TIMER0_ENABLE_OV_INTERRUPT*/
/*#define TIMER0_ENABLE_CTC_INTERRUPT*/

#define TIMER0_setTimerValue(val) (TCNT0 = val)

#define TIMER0_setCompareValue(val) (OCR0 = val)

#define TIMER0_setDutyCycle(val) (OCR0 = val * 255 / 100)

#define TIMER0_deInit() (TCCR0bits.cs0 = TIMER0_CLOCK_0)

typedef enum{
  TIMER0_MODE_NORMAL,	/* Normal counting mode        */
  TIMER0_MODE_PWM_PC,	/* PWM with phase correct mode */
  TIMER0_MODE_CTC,	/* Compare mode mode           */
  TIMER0_MODE_FAST_PWM	/* Fast PWM mode               */
} TIMER0_mode_t;

typedef enum{
  TIMER0_COMPARE_NORMAL,		/* Normal port operation, OC0 disconnected. */

  TIMER0_COMPARE_NON_PWM_TOGGLE_OC0,    /*  Toggle OC0 on compare match */
  TIMER0_COMPARE_NON_PWM_CLEAR_OC0,	/*  Clear OC0 on compare match  */
  TIMER0_COMPARE_NON_PWM_SET_OC0,	/*  Set OC0 on compare match    */

  TIMER0_COMPARE_FAST_PWM_NIN_INVERTING = 2, /* Clear OC0 on compare match, set OC0 at BOTTOM */
  TIMER0_COMPARE_FAST_PWM_INVERTING,         /* Set OC0 on compare match, clear OC0 at BOTTOM */

  /* Clear OC0 on compare match when up-counting.
   *  Set OC0 on compare match when down-counting. */
  TIMER0_COMPARE_PC_PWM_CLEAR_UP = 2,
  /* Set OC0 on compare match when up-counting.
   *  Clear OC0 on compare match when down-counting. */
  TIMER0_COMPARE_PC_PWM_CLEAR_DOWN
} TIMER0_compareOuput_mode_t;

typedef enum{
  TIMER0_CLOCK_0,		/* No clock source (Timer/Counter stopped). */
  TIMER0_CLOCK_DIV_1,		/* clk /(No pre-scaling)                    */
  TIMER0_CLOCK_DIV_8,		/* clk /8 (From pre-scaler)                 */
  TIMER0_CLOCK_DIV_64,		/* clk /64 (From pre-scaler)                */
  TIMER0_CLOCK_DIV_256,		/* clk /256 (From pre-scaler)               */
  TIMER0_CLOCK_DIV_1024,	/* clk /1024 (From pre-scaler)              */
  TIMER0_CLOCK_EXTERNAL_FALLING,/* External clock source on T0 pin. Clock on falling edge. */
  TIMER0_CLOCK_EXTERNAL_RISING	/*  External clock source on T0 pin. Clock on rising edge. */
} TIMER0_clockPrescaller_t;

typedef struct{
  uint8 mode : 2;
  uint8 compareOutputMode : 2;
  uint8 clockPre : 3;
  union {
    uint8 timerValue;
    uint8 compareValue;
    uint8 dutyCycle;
  } uni;
#ifdef TIMER0_ENABLE_OV_INTERRUPT
  void (*overFlowInterruptHandler)(void);
#endif

#ifdef TIMER0_ENABLE_CTC_INTERRUPT
  void (*compareInterruptHandler)(void);
#endif

} TIMER0_t;

extern TIMER0_t g_timer0;

void TIMER0_init(TIMER0_t * timer0);

#endif /* MCAL_TIMERS_TIMER0_H_ */
