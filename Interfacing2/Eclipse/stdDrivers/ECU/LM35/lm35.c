/******************************************************************************
 *
 * Module: Temperature Sensor LM35
 *
 * File Name: lm35.c
 *
 * Description: 
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#include "lm35.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/ADC/adc.h"

LM35_t g_lm35_1 =
  { .port = PORTA_ID, .pin = PIN1_ID };

void LM35_init (LM35_t *lm35)
{
  ADC_init (&g_adc1);
  GPIO_setupPinDirection (lm35->port, lm35->pin, PIN_INPUT);

  LM35_getTemp(&g_lm35_1);
}

uint8 LM35_getTemp (LM35_t *lm35)
{
  uint8 temp_val = 0;
  uint16 adc_value = 0;
  adc_value = ADC_readChannelBlocking (lm35->pin);
  temp_val = (uint8) (((uint32) adc_value * LM35_MAX_TEMPERATURE * ADC_REF_VOLT_VALUE)
      / (ADC_MAXIMUM_VALUE * LM35_MAX_VOLT_VALUE));
  return temp_val;
}
