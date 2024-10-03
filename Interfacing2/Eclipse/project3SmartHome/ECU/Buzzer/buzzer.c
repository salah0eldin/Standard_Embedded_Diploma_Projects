/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: 
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#include "buzzer.h"
#include "../../MCAL/GPIO/gpio.h"

BUZZER_t g_buzzer1 =
  { .port = PORTD_ID, .pin = PIN3_ID, .buzzerLogic = BUZZER_LOGIC_POSITIVE };

void BUZZER_init(BUZZER_t *buzzer)
{
  GPIO_setupPinDirection(buzzer->port, buzzer->pin, PIN_OUTPUT);
}

void BUZZER_turnOn(BUZZER_t *buzzer)
{
  GPIO_writePin(buzzer->port, buzzer->pin, LOGIC_HIGH ^ buzzer->buzzerLogic);
}

void BUZZER_turnOff(BUZZER_t *buzzer)
{
  GPIO_writePin(buzzer->port, buzzer->pin, LOGIC_LOW ^ buzzer->buzzerLogic);
}

void BUZZER_toggle(BUZZER_t *buzzer)
{
  GPIO_togglePin(buzzer->port, buzzer->pin);
}
