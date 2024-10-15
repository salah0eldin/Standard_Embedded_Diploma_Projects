/******************************************************************************
 *
 * Module: button
 *
 * File Name: button.h
 *
 * Description: Header file for the button module which provides an interface
 *              for initializing a button and getting its state. This module
 *              supports different button connection types and keeps track of
 *              the button's current state.
 *
 * Created on: Oct 12, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef ECU_BUTTON_BUTTON_H_
#define ECU_BUTTON_BUTTON_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../std_types.h" /* Standard data types definition */

/*******************************************************************************
 *                               Macro Declarations                            *
 *******************************************************************************/
/* None */

/*******************************************************************************
 *                           Data Type Declarations                            *
 *******************************************************************************/

/**
 * Enum for representing the state of the button.
 * BUTTON_NOT_PRESSED: The button is not pressed.
 * BUTTON_PRESSED: The button is pressed.
 */
typedef enum{
  BUTTON_NOT_PRESSED,
  BUTTON_PRESSED
} BUTTON_state_t;

/**
 * Enum for the connection type of the button.
 * BUTTON_PULL_DOWN: Button with pull-down resistor.
 * BUTTON_PULL_UP_INTERNAL: Button with internal pull-up resistor.
 * BUTTON_PULL_UP_EXTERNAL: Button with external pull-up resistor.
 */
typedef enum {
  BUTTON_PULL_DOWN,
  BUTTON_PULL_UP_INTERNAL,
  BUTTON_PULL_UP_EXTERNAL
} BUTTON_connection_t;

/**
 * Structure to define the button configuration.
 * - port: The port number where the button is connected (2 bits).
 * - pin: The pin number where the button is connected (3 bits).
 * - connection: The button's connection type, based on BUTTON_connection_t (2 bits).
 */
typedef struct {
  uint8 port :2;
  uint8 pin :3;
  uint8 connection :2;
} BUTTON_t;

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

/**
 * Extern declaration for a global button variable.
 * Used as a placeholder for a button configuration.
 */
extern BUTTON_t g_button1;

/*******************************************************************************
 *                        Function Prototypes                                  *
 *******************************************************************************/

/**
 * @brief Initializes the button with the specified configuration.
 *
 * @param button Pointer to a BUTTON_t structure containing the button configuration.
 */
void BUTTON_init(BUTTON_t *button);

/**
 * @brief Retrieves the current state of the button.
 *
 * @param button Pointer to a BUTTON_t structure containing the button configuration.
 * @return BUTTON_state_t The current state of the button (pressed or not pressed).
 */
BUTTON_state_t BUTTON_getState(BUTTON_t *button);

#endif /* ECU_BUTTON_BUTTON_H_ */
