/******************************************************************************
 *
 * Module: Light
 *
 * File Name: light.h
 *
 * Description: Header file for the light module responsible for handling light
 *              intensity measurements and LED control based on intensity levels.
 *
 * Created on: Oct 5, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef APP_LIGHT_LIGHT_H_
#define APP_LIGHT_LIGHT_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../std_types.h"

/*******************************************************************************
 *                               Types Definition                              *
 *******************************************************************************/

/* Light intensity thresholds for the application *
 * to handle and change the LEDs states           */
typedef enum {
  LIGHT_LEVEL1 = 15,   /**< Low light intensity threshold */
  LIGHT_LEVEL2 = 50,   /**< Medium light intensity threshold */
  LIGHT_LEVEL3 = 70    /**< High light intensity threshold */
} LIGHT_Threshold_t;

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

/* Global variable to store the current light intensity level */
extern uint8 g_lightIntensity;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/**
 * @brief Initializes the light sensor module.
 *
 * This function is responsible for setting up the necessary configurations for
 * the light sensor to measure intensity.
 */
void LIGHT_init(void);

/**
 * @brief Handles the light intensity and adjusts the LEDs accordingly.
 *
 * This function reads the light sensor values and adjusts the system's response
 * (e.g., turning LEDs on/off) based on the light intensity thresholds.
 */
void LIGHT_handleIntensity(void);

#endif /* APP_LIGHT_LIGHT_H_ */
