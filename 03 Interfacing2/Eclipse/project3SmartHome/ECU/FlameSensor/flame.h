/******************************************************************************
 *
 * Module: Flame Sensor
 *
 * File Name: flame.h
 *
 * Description: Header file for the Flame Sensor driver.
 *
 * This module provides the necessary functions and definitions for interfacing
 * with a flame sensor, allowing for flame detection functionality in embedded
 * systems.
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef ECU_FLAMESENSOR_FLAME_H_
#define ECU_FLAMESENSOR_FLAME_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../std_types.h"

/*******************************************************************************
 *                                Type Definitions                              *
 *******************************************************************************/

/* Flame Sensor Configuration Structure */
typedef struct
{
  uint8 port :2;        /* Port number where the flame sensor is connected */
  uint8 pin :3;         /* Pin number on the port for the flame sensor */
  uint8 flameLogic :1;  /* Logic level for flame detection (active high/low) */
  uint8 :0;             /* Padding to ensure correct struct alignment */
} FLAME_t;

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
extern FLAME_t g_flameSensor1; /* Global instance of the flame sensor configuration */

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * @brief Initializes the flame sensor according to the provided configuration.
 *
 * This function sets up the GPIO pin direction for the flame sensor,
 * preparing it for use in detecting flames.
 *
 * @param flameSensor Pointer to a structure of type `FLAME_t` that holds the configuration settings for the flame sensor.
 */
void FLAME_init(FLAME_t *flameSensor);

/**
 * @brief Checks if a flame is detected by the sensor.
 *
 * This function reads the state of the flame sensor and returns
 * a value indicating whether a flame is detected based on the configuration.
 *
 * @param flameSensor Pointer to the flame sensor configuration structure.
 * @return uint8 Returns 1 if a flame is detected, otherwise returns 0.
 */
uint8 FLAME_isFlame(FLAME_t *flameSensor);

#endif /* ECU_FLAMESENSOR_FLAME_H_ */
