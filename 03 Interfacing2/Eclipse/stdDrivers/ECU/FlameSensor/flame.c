/******************************************************************************
 *
 * Module: Flame Sensor
 *
 * File Name: flame.c
 *
 * Description: Source file for the Flame Sensor driver.
 *
 * This module implements the functions for initializing and reading the
 * state of a flame sensor, allowing for detection of flames in embedded
 * systems.
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#include "flame.h"
#include "../../MCAL/GPIO/gpio.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
FLAME_t g_flameSensor1 = { .port = PORTD_ID, .pin = PIN2_ID, .flameLogic = LOGIC_HIGH }; /* Global instance of the flame sensor configuration */

/*******************************************************************************
 *                              Function Definitions                           *
 *******************************************************************************/

/**
 * @brief Initializes the flame sensor according to the provided configuration.
 *
 * This function sets up the GPIO pin direction for the flame sensor,
 * preparing it for use in detecting flames.
 *
 * @param flameSensor Pointer to a structure of type `FLAME_t` that holds the configuration settings for the flame sensor.
 */
void FLAME_init(FLAME_t *flameSensor) {
  GPIO_setupPinDirection(flameSensor->port, flameSensor->pin, PIN_INPUT); /* Set the pin as input to read the flame sensor */
}

/**
 * @brief Checks if a flame is detected by the sensor.
 *
 * This function reads the state of the flame sensor and returns
 * a value indicating whether a flame is detected based on the configuration.
 *
 * @param flameSensor Pointer to the flame sensor configuration structure.
 * @return uint8 Returns 1 if a flame is detected, otherwise returns 0.
 */
uint8 FLAME_isFlame(FLAME_t *flameSensor) {
  return flameSensor->flameLogic == GPIO_readPin(flameSensor->port, flameSensor->pin); /* Compare the sensor's pin reading with the configured logic */
}
