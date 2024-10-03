/******************************************************************************
 *
 * Module: LDR
 *
 * File Name: ldr.c
 *
 * Description: 
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#include "ldr.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/ADC/adc.h"


LDR_t g_ldr1 = {
    .port = PORTA_ID,
    .pin = PIN0_ID,
    .ldrLogic = LDR_LOGIC_BIGGER_IS_LIGHT,
    .threshold = 500
};

void LDR_init (LDR_t *ldr)
{
  ADC_init(&g_adc1);
  GPIO_setupPinDirection (ldr->port, ldr->pin, PIN_INPUT);
}

uint8 LDR_isLight (LDR_t *ldr)
{
  return (uint8) ((ADC_readChannelBlocking (ldr->pin) > ldr->threshold) ? (LDR_LIGHT_ON) : (LDR_LIGHT_OFF))
      ^ ldr->ldrLogic;
}

uint16 LDR_readValue (LDR_t *ldr)
{
  return ADC_readChannelBlocking (ldr->pin);
}
