/******************************************************************************
 *
 * Module: button
 *
 * File Name: button.c
 *
 * Description: Source file for the button module. It contains the
 *              implementation of the functions for initializing a button
 *              and getting its current state.
 *
 * Created on: Oct 12, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "button.h"
#include "../../MCAL/GPIO/gpio.h" /* GPIO module for setting pin directions and reading pin states */

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

/* Global button configuration initialized with default values (port A, pin 0, internal pull-up) */
BUTTON_t g_button1 = { .port = PORTD_ID, .pin = PIN2_ID, .connection = BUTTON_PULL_UP_EXTERNAL };

/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/

/**
 * @brief Initializes the button by setting the direction of the pin and applying
 *        the appropriate connection type (pull-up or pull-down).
 *
 * @param button Pointer to a BUTTON_t structure containing the button configuration.
 */
void BUTTON_init(BUTTON_t *button) {
  /* Set the button pin as input */
  GPIO_setupPinDirection(button->port, button->pin, PIN_INPUT);
  /* Write the default value based on the button's connection type (0 or 1) */
  GPIO_writePin(button->port, button->pin, button->connection & 1);
}

/**
 * @brief Retrieves the current state of the button (pressed or not pressed) based on the
 *        connection type (pull-up or pull-down).
 *
 * @param button Pointer to a BUTTON_t structure containing the button configuration.
 * @return BUTTON_state_t The current state of the button (BUTTON_PRESSED or BUTTON_NOT_PRESSED).
 */
BUTTON_state_t BUTTON_getState(BUTTON_t *button) {
  /* Check the connection type and read the pin state accordingly */
  switch (button->connection)
    {
    case BUTTON_PULL_DOWN:
      /* Button is pressed if the pin reads logic high in pull-down mode */
      return
	  (GPIO_readPin(button->port, button->pin) == LOGIC_HIGH) ?
	      BUTTON_PRESSED : BUTTON_NOT_PRESSED;
    case BUTTON_PULL_UP_EXTERNAL:
    case BUTTON_PULL_UP_INTERNAL:
      /* Button is pressed if the pin reads logic low in pull-up mode */
      return
	  (GPIO_readPin(button->port, button->pin) == LOGIC_LOW) ?
	      BUTTON_PRESSED : BUTTON_NOT_PRESSED;
    default:
      /* Default case to handle invalid connection types */
      return BUTTON_NOT_PRESSED;
    }
}
