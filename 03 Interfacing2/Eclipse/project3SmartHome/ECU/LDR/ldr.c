/******************************************************************************
 *
 * Module: LDR (Light Dependent Resistor)
 *
 * File Name: ldr.c
 *
 * Description: Implementation of the LDR driver functions. This module
 * provides the functionalities to initialize the LDR, check for light
 * detection, and retrieve the light intensity level.
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "ldr.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/ADC/adc.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
LDR_t g_ldr1 = {
    .port = PORTA_ID,              /* Port identifier where the LDR is connected */
    .pin = PIN0_ID,                /* Pin number on the port */
    .ldrLogic = LDR_LOGIC_BIGGER_IS_LIGHT, /* Logic configuration for light detection */
    .threshold = 500,              /* Threshold value for light detection */
    .max = 1023,                   /* Maximum ADC value corresponding to full light */
    .min = 2                        /* Minimum ADC value corresponding to no light */
};

/*******************************************************************************
 *                              Functions Implementation                        *
 *******************************************************************************/

/**
 * @brief Initializes the LDR and prepares it for operation.
 *
 * This function initializes the ADC and sets the GPIO pin direction for the LDR.
 *
 * @param ldr Pointer to a structure of type `LDR_t` that holds the configuration settings for the LDR.
 */
void LDR_init(LDR_t *ldr) {
    ADC_init(&g_adc1);                          /* Initialize the ADC module */
    GPIO_setupPinDirection(ldr->port, ldr->pin, PIN_INPUT); /* Set pin direction as input */
}

/**
 * @brief Checks if the LDR detects light based on the configured threshold.
 *
 * This function reads the current value from the LDR through the ADC and
 * compares it against the threshold to determine if light is present.
 *
 * @param ldr Pointer to the LDR configuration structure.
 * @return uint8 Returns LDR_LIGHT_ON if light is detected, otherwise returns LDR_LIGHT_OFF.
 */
uint8 LDR_isLight(LDR_t *ldr) {
    return (uint8) (
        (ADC_readChannelBlocking(ldr->pin) > ldr->threshold) ? (LDR_LIGHT_ON) : (LDR_LIGHT_OFF))
        ^ ldr->ldrLogic;  /* XOR with ldrLogic to adjust the return value based on logic configuration */
}

/**
 * @brief Gets the current light intensity reading from the LDR.
 *
 * This function calculates the light intensity as a percentage of the
 * defined range based on the ADC value read from the LDR.
 *
 * @param ldr Pointer to the LDR configuration structure.
 * @return uint8 The intensity value of the light detected by the LDR, scaled to a percentage.
 */
uint8 LDR_getIntensity(LDR_t *ldr) {
    return (uint8) (
        (uint32)(ADC_readChannelBlocking(ldr->pin) - ldr->min) * 100 / (ldr->max - ldr->min)
    );  /* Scale ADC value to percentage based on min and max */
}
