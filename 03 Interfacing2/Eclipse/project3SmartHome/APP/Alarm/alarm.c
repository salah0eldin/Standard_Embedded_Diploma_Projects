/******************************************************************************
 *
 * Module: Alarm
 *
 * File Name: alarm.c
 *
 * Description: Source file for the Alarm system which handles flame detection.
 *
 * Created on: Oct 5, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "alarm.h"
#include "../../ECU/FlameSensor/flame.h"
#include "../../ECU/Buzzer/buzzer.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

uint8 g_flameFlag = FALSE; /* Flag to track flame detection state */

/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/

/**
 * @brief Initializes the alarm system.
 *
 * This function initializes the buzzer and flame sensor, preparing them for operation.
 */
void ALARM_init(void) {
  BUZZER_init(&g_buzzer1); /* Initialize the buzzer */
  FLAME_init(&g_flameSensor1); /* Initialize the flame sensor */
}

/**
 * @brief Handles the flame detection logic and controls the alarm.
 *
 * This function checks the flame sensor's state and activates/deactivates the alarm
 * (buzzer) accordingly.
 */
void ALARM_handleFlame(void) {
  if (FLAME_isFlame(&g_flameSensor1)) {
    if (g_flameFlag == FALSE) {
      BUZZER_turnOn(&g_buzzer1); /* Turn on the buzzer if flame detected */
      g_flameFlag = TRUE; /* Update flame flag */
    }
  }
  else {
    if (g_flameFlag == TRUE) {
      BUZZER_turnOff(&g_buzzer1); /* Turn off the buzzer if no flame is detected */
      g_flameFlag = FALSE; /* Reset flame flag */
    }
  }
}
