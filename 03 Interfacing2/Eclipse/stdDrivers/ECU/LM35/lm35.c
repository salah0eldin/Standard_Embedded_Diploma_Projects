/******************************************************************************
 *
 * Module: Temperature Sensor LM35
 *
 * File Name: lm35.c
 *
 * Description: Source file for the LM35 temperature sensor driver.
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#include "lm35.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/ADC/adc.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
LM35_t g_lm35_1 =                     /* Global variable representing the first LM35 sensor instance */
  { .port = PORTA_ID, .pin = PIN1_ID };

/*******************************************************************************
 *                              Functions Definitions                           *
 *******************************************************************************/

/**
 * @brief Initializes the LM35 temperature sensor.
 *
 * This function initializes the ADC module and sets the pin direction
 * for the LM35 sensor. It also calls the temperature retrieval function
 * to get the initial temperature reading.
 *
 * @param lm35 Pointer to a structure of type `LM35_t` that holds the configuration settings for the LM35.
 */
void LM35_init(LM35_t *lm35)
{
  ADC_init(&g_adc1);                              /* Initialize the ADC module */
  GPIO_setupPinDirection(lm35->port, lm35->pin, PIN_INPUT); /* Set the LM35 pin as input */

  LM35_getTemp(&g_lm35_1);                       /* Retrieve the initial temperature value */
}

/**
 * @brief Retrieves the temperature measured by the LM35 sensor.
 *
 * This function reads the analog voltage output from the LM35 sensor and converts
 * it into a temperature value using the ADC. The calculation is based on the
 * known characteristics of the LM35 sensor.
 *
 * @param lm35 Pointer to the LM35 configuration structure.
 * @return `uint8` The temperature in degrees Celsius measured by the LM35.
 */
uint8 LM35_getTemp(LM35_t *lm35)
{
  uint8 temp_val = 0;                             /* Variable to hold the calculated temperature value */
  uint16 adc_value = 0;                           /* Variable to store the ADC value */

  adc_value = ADC_readChannelBlocking(lm35->pin); /* Read the ADC value for the specified pin */

  /* Convert the ADC value to temperature in degrees Celsius */
  temp_val = (uint8) (((uint32) adc_value * LM35_MAX_TEMPERATURE * ADC_REF_VOLT_VALUE)
      / (ADC_MAXIMUM_VALUE * LM35_MAX_VOLT_VALUE));

  return temp_val;                                 /* Return the calculated temperature */
}
