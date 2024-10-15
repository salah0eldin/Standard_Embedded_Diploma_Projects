/******************************************************************************
 *
 * Module: LED
 *
 * File Name: led.c
 *
 * Description: This module provides the implementation of functions to control
 * LED components, including initialization, turning on, turning off, and toggling
 * their states.
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "led.h"               /* Include the LED header file */
#include "../../MCAL/GPIO/gpio.h"  /* Include the GPIO header file for pin control */

/*******************************************************************************
 *                              Global Variables                                *
 *******************************************************************************/

/* Global instances of LEDs with their configurations */
LED_t g_ledRed =
  { .port = PORTC_ID, .pin = PIN0_ID, .ledLogic = LED_LOGIC_POSITIVE };  /* Red LED configuration */

LED_t g_ledGreen =
  { .port = PORTC_ID, .pin = PIN1_ID, .ledLogic = LED_LOGIC_POSITIVE };  /* Green LED configuration */

LED_t g_ledBlue =
  { .port = PORTC_ID, .pin = PIN2_ID, .ledLogic = LED_LOGIC_POSITIVE };   /* Blue LED configuration */

/*******************************************************************************
 *                              Functions Implementation                        *
 *******************************************************************************/

/**
 * @brief Initializes the LED for operation.
 *
 * This function configures the GPIO pin for the LED as an output.
 *
 * @param led Pointer to the LED configuration structure.
 */
void LED_init(LED_t *led) {
  GPIO_setupPinDirection(led->port, led->pin, PIN_OUTPUT);  /* Set the pin direction to output */
}

/**
 * @brief Turns on the LED.
 *
 * This function activates the LED based on its logic configuration.
 *
 * @param led Pointer to the LED configuration structure.
 */
void LED_turnOn(LED_t *led) {
  GPIO_writePin(led->port, led->pin, LOGIC_HIGH ^ led->ledLogic);  /* Write the appropriate logic level to turn on the LED */
}

/**
 * @brief Turns off the LED.
 *
 * This function deactivates the LED based on its logic configuration.
 *
 * @param led Pointer to the LED configuration structure.
 */
void LED_turnOff(LED_t *led) {
  GPIO_writePin(led->port, led->pin, LOGIC_LOW ^ led->ledLogic);   /* Write the appropriate logic level to turn off the LED */
}

/**
 * @brief Toggles the LED state.
 *
 * This function changes the LED state from on to off or vice versa based
 * on its logic configuration.
 *
 * @param led Pointer to the LED configuration structure.
 */
void LED_toggle(LED_t *led) {
  GPIO_togglePin(led->port, led->pin);  /* Toggle the pin state */
}
