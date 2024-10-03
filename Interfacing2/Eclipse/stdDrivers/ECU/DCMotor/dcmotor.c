/******************************************************************************
 *
 * Module: H-Brdige DC Motors
 *
 * File Name: dcmotor.c
 *
 * Description: 
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#include "dcmotor.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/Timers/timer0.h"

DCMOTOR_t g_dcmotor = {
  .dirPort = PORTB_ID,
  .dirPin1 = PIN0_ID,
  .dirPin2 = PIN1_ID,
  .enableEn = 1,
  .enPort = PORTB_ID,
  .enPin = PIN3_ID
};

void DCMOTOR_init (DCMOTOR_t *dcmotor)
{
  GPIO_setupPinDirection (dcmotor->dirPort, dcmotor->dirPin1, PIN_OUTPUT);
  GPIO_setupPinDirection (dcmotor->dirPort, dcmotor->dirPin2, PIN_OUTPUT);

  if (dcmotor->enableEn)
    GPIO_setupPinDirection (dcmotor->enPort, dcmotor->enPin, PIN_OUTPUT);

  TIMER0_init (&g_timer0);
}

void DCMOTOR_setDir (DCMOTOR_t *dcmotor, uint8 dir)
{
  GPIO_writePin (dcmotor->dirPort, dcmotor->dirPin1, dir);
  GPIO_writePin (dcmotor->dirPort, dcmotor->dirPin1, !dir);
}

void DCMOTOR_stop (DCMOTOR_t *dcmotor)
{
  GPIO_writePin (dcmotor->dirPort, dcmotor->dirPin1, LOGIC_LOW);
  GPIO_writePin (dcmotor->dirPort, dcmotor->dirPin1, LOGIC_LOW);
}

void DCMOTOR_setSpeed (uint8 speed)
{
  TIMER0_setDutyCycle(speed % 100);
}
