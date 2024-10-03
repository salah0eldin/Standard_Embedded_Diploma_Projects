/******************************************************************************
 *
 * Module: Flame Sensor
 *
 * File Name: flame.c
 *
 * Description: 
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#include "flame.h"
#include "../../MCAL/GPIO/gpio.h"

FLAME_t g_flameSensor1 =
  { .port = PORTD_ID, .pin = PIN2_ID, .flameLogic = LOGIC_HIGH };

void FLAME_init(FLAME_t *flameSensor)
{
  GPIO_setupPinDirection(flameSensor->port, flameSensor->pin, PIN_INPUT);
}

uint8 FLAME_isFlame(FLAME_t *flameSensor)
{
  return flameSensor->flameLogic == GPIO_readPin(flameSensor->port, flameSensor->pin);
}
