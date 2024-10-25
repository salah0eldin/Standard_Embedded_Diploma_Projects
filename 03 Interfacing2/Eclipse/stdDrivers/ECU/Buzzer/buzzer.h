/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the Buzzer driver.
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef ECU_BUZZER_BUZZER_H_
#define ECU_BUZZER_BUZZER_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../std_types.h"

/*******************************************************************************
 *                              Types Declaration                              *
 *******************************************************************************/

/* Define buzzer logic states*/
typedef enum {
  BUZZER_LOGIC_POSITIVE, /* Buzzer activated with a positive logic */
  BUZZER_LOGIC_NEGATIVE /* Buzzer activated with a negative logic */
} BUZZER_logic_t;

/* Buzzer Configuration Structure */
typedef struct {
  uint8 port :2; /* Port number where the buzzer is connected (2 bits) */
  uint8 pin :3; /* Pin number where the buzzer is connected (3 bits) */
  uint8 buzzerLogic :1; /* Logic type for the buzzer (1 bit) */
} BUZZER_t;

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
extern BUZZER_t g_buzzer1; /* Global instance of the Buzzer configuration */

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * @brief Initializes the Buzzer according to the configuration settings in the BUZZER_t structure.
 *
 * This function sets up the buzzer hardware based on the provided configuration,
 * allowing it to be ready for operation.
 *
 * @param buzzer Pointer to a structure of type `BUZZER_t` that holds the configuration settings for the Buzzer.
 */
void BUZZER_init(BUZZER_t *buzzer);

/**
 * @brief Turns on the buzzer.
 *
 * This function activates the buzzer according to its configuration settings.
 *
 * @param buzzer Pointer to the buzzer configuration structure.
 */
void BUZZER_turnOn(BUZZER_t *buzzer);

/**
 * @brief Turns off the buzzer.
 *
 * This function deactivates the buzzer.
 *
 * @param buzzer Pointer to the buzzer configuration structure.
 */
void BUZZER_turnOff(BUZZER_t *buzzer);

/**
 * @brief Toggles the state of the buzzer.
 *
 * This function switches the buzzer between on and off states.
 *
 * @param buzzer Pointer to the buzzer configuration structure.
 */
void BUZZER_toggle(BUZZER_t *buzzer);

#endif /* ECU_BUZZER_BUZZER_H_ */
