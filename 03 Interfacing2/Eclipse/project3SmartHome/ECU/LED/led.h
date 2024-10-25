/******************************************************************************
 *
 * Module: LED
 *
 * File Name: led.h
 *
 * Description: This module provides the interface for controlling LED
 * components. It includes functions for initializing, turning on, turning
 * off, and toggling LEDs, with support for different logic configurations.
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef ECU_LED_LED_H_
#define ECU_LED_LED_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../std_types.h"  /* Include standard types header */

/*******************************************************************************
 *                              Types Definitions                               *
 *******************************************************************************/

/**
 * @brief Enumeration for LED logic type.
 *
 * This enum defines the logic configuration for the LED:
 * - LED_LOGIC_POSITIVE: LED is on when the pin is high.
 * - LED_LOGIC_NEGATIVE: LED is on when the pin is low.
 */
typedef enum {
    LED_LOGIC_POSITIVE,   /* LED logic for positive logic (active high) */
    LED_LOGIC_NEGATIVE    /* LED logic for negative logic (active low) */
} LED_logic_t;

/**
 * @brief Structure for LED configuration.
 *
 * This struct defines the configuration parameters for an LED:
 * - port: The port identifier where the LED is connected.
 * - pin: The pin number on the port where the LED is connected.
 * - ledLogic: The logic configuration for the LED (positive or negative).
 */
typedef struct {
    uint8 port : 2;      /* Port identifier */
    uint8 pin : 3;       /* Pin number on the port */
    uint8 ledLogic : 1;  /* Logic configuration for the LED */
} LED_t;

/*******************************************************************************
 *                              Global Variables                                *
 *******************************************************************************/

/* Global instances of LEDs */
extern LED_t g_ledRed;    /* Red LED configuration */
extern LED_t g_ledGreen;  /* Green LED configuration */
extern LED_t g_ledBlue;   /* Blue LED configuration */

/*******************************************************************************
 *                              Functions Prototypes                            *
 *******************************************************************************/

/**
 * @brief Initializes the LED for operation.
 *
 * This function sets up the GPIO pin for the LED based on the provided
 * configuration structure.
 *
 * @param led Pointer to the LED configuration structure.
 */
void LED_init(LED_t *led);

/**
 * @brief Turns on the LED.
 *
 * This function activates the LED based on its logic configuration.
 *
 * @param led Pointer to the LED configuration structure.
 */
void LED_turnOn(LED_t *led);

/**
 * @brief Turns off the LED.
 *
 * This function deactivates the LED based on its logic configuration.
 *
 * @param led Pointer to the LED configuration structure.
 */
void LED_turnOff(LED_t *led);

/**
 * @brief Toggles the LED state.
 *
 * This function changes the LED state from on to off or vice versa
 * based on its logic configuration.
 *
 * @param led Pointer to the LED configuration structure.
 */
void LED_toggle(LED_t *led);

#endif /* ECU_LED_LED_H_ */
