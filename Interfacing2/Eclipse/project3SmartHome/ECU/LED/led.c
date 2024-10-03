/******************************************************************************
 *
 * Module: LED
 *
 * File Name: led.c
 *
 * Description: 
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#include "led.h"
#include "../../MCAL/GPIO/gpio.h"

LED_t g_ledRed =
  { .port = PORTB_ID, .pin = PIN5_ID, .ledLogic = LED_LOGIC_POSITIVE };
LED_t g_ledGreen =
  { .port = PORTB_ID, .pin = PIN6_ID, .ledLogic = LED_LOGIC_POSITIVE };
LED_t g_ledBlue =
  { .port = PORTB_ID, .pin = PIN7_ID, .ledLogic = LED_LOGIC_POSITIVE };

void LED_init(LED_t *led)
{
  GPIO_setupPinDirection(led->port, led->pin, PIN_OUTPUT);
}

void LED_turnOn(LED_t *led)
{
  GPIO_writePin(led->port, led->pin, LOGIC_HIGH ^ led->ledLogic);
}

void LED_turnOff(LED_t *led)
{
  GPIO_writePin(led->port, led->pin, LOGIC_LOW ^ led->ledLogic);
}

void LED_toggle(LED_t *led)
{
  GPIO_togglePin(led->port, led->pin);
}
