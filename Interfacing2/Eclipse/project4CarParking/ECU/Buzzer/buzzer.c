/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the Buzzer driver implementation.
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "buzzer.h"
#include "../../MCAL/GPIO/gpio.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

// Global instance of the Buzzer configuration
BUZZER_t g_buzzer1 = { .port = PORTC_ID, .pin = PIN5_ID, .buzzerLogic = BUZZER_LOGIC_POSITIVE };

/*******************************************************************************
 *                              Function Definitions                           *
 *******************************************************************************/

/**
 * @brief Initializes the Buzzer according to the provided configuration.
 *
 * This function sets up the GPIO pin direction for the buzzer, allowing it to
 * operate as an output pin.
 *
 * @param buzzer Pointer to a structure of type `BUZZER_t` that holds the configuration settings for the Buzzer.
 */
void BUZZER_init(BUZZER_t *buzzer) {
  // Set the pin direction for the buzzer to output
  GPIO_setupPinDirection(buzzer->port, buzzer->pin, PIN_OUTPUT);
}

/**
 * @brief Turns on the buzzer.
 *
 * This function activates the buzzer by writing the appropriate logic level
 * to the configured pin based on the buzzer's logic configuration.
 *
 * @param buzzer Pointer to the buzzer configuration structure.
 */
void BUZZER_turnOn(BUZZER_t *buzzer) {
  // Write high logic to the buzzer pin based on its logic configuration
  GPIO_writePin(buzzer->port, buzzer->pin, LOGIC_HIGH ^ buzzer->buzzerLogic);
}

/**
 * @brief Turns off the buzzer.
 *
 * This function deactivates the buzzer by writing a low logic level
 * to the configured pin based on the buzzer's logic configuration.
 *
 * @param buzzer Pointer to the buzzer configuration structure.
 */
void BUZZER_turnOff(BUZZER_t *buzzer) {
  // Write low logic to the buzzer pin based on its logic configuration
  GPIO_writePin(buzzer->port, buzzer->pin, LOGIC_LOW ^ buzzer->buzzerLogic);
}

/**
 * @brief Toggles the state of the buzzer.
 *
 * This function switches the buzzer between on and off states by toggling
 * the logic level on the configured pin.
 *
 * @param buzzer Pointer to the buzzer configuration structure.
 */
void BUZZER_toggle(BUZZER_t *buzzer) {
  // Toggle the current state of the buzzer pin
  GPIO_togglePin(buzzer->port, buzzer->pin);
}
