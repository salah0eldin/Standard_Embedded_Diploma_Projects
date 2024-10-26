/******************************************************************************
 *
 * Module: LDR (Light Dependent Resistor)
 *
 * File Name: ldr.h
 *
 * Description: Header file for the LDR driver. This module defines the
 * configuration and function prototypes for interfacing with an LDR,
 * enabling light intensity detection.
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef ECU_LDR_LDR_H_
#define ECU_LDR_LDR_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../LIB/std_types.h"

/*******************************************************************************
 *                            Type Definitions                                 *
 *******************************************************************************/

/* Logic type for LDR */
typedef enum
{
  LDR_LOGIC_BIGGER_IS_LIGHT,  /* Higher value indicates more light */
  LDR_LOGIC_BIGGER_IS_DARK    /* Higher value indicates darkness */
} LDR_logic_t;

/* State of the LDR based on light detection */
typedef enum
{
  LDR_LIGHT_OFF,  /* Indicates the LDR detected no light */
  LDR_LIGHT_ON    /* Indicates the LDR detected light */
} LDR_state_t;

/* Structure for LDR configuration */
typedef struct
{
  uint8 port :2;      /* Port identifier where the LDR is connected */
  uint8 pin :3;       /* Pin number on the port */
  uint8 ldrLogic :1;  /* Logic configuration for light detection */
  uint16 max;         /* Maximum threshold value for light detection */
  uint16 min;         /* Minimum threshold value for light detection */
  uint16 threshold;   /* Threshold value for light intensity comparison */
} LDR_t;

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
extern LDR_t g_ldr1;  /* Global instance of the LDR configuration */

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * @brief Initializes the LDR according to the configuration settings.
 *
 * This function sets up the GPIO pin direction for the LDR, preparing it
 * for use in light detection.
 *
 * @param ldr Pointer to a structure of type `LDR_t` that holds the configuration settings for the LDR.
 */
void LDR_init(LDR_t *ldr);

/**
 * @brief Checks if the LDR detects light.
 *
 * This function reads the state of the LDR and returns a value indicating
 * whether light is detected based on the configuration.
 *
 * @param ldr Pointer to the LDR configuration structure.
 * @return uint8 Returns 1 if light is detected, otherwise returns 0.
 */
uint8 LDR_isLight(LDR_t *ldr);

/**
 * @brief Gets the current light intensity reading from the LDR.
 *
 * This function retrieves the light intensity value from the LDR,
 * which can be used to assess the light level.
 *
 * @param ldr Pointer to the LDR configuration structure.
 * @return uint8 The intensity value of the light detected by the LDR.
 */
uint8 LDR_getIntensity(LDR_t *ldr);

#endif /* ECU_LDR_LDR_H_ */
