/******************************************************************************
 *
 * Module: Temperature Sensor LM35
 *
 * File Name: lm35.h
 *
 * Description: Header file for the LM35 temperature sensor driver.
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef ECU_LM35_LM35_H_
#define ECU_LM35_LM35_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../LIB/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LM35_MAX_VOLT_VALUE     1.5    /* Maximum output voltage of the LM35 (in volts) */
#define LM35_MAX_TEMPERATURE    150    /* Maximum temperature range for LM35 (in degrees Celsius) */

/*******************************************************************************
 *                              Types Declaration                              *
 *******************************************************************************/

/* Structure representing the LM35 sensor configuration */
typedef struct
{
  uint8 port :2;          /* Port where the LM35 is connected */
  uint8 pin :3;           /* Pin on the port where the LM35 is connected */
} LM35_t;

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
extern LM35_t g_lm35_1;              /* Global variable representing the first LM35 sensor instance */

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * @brief Initializes the LM35 temperature sensor.
 *
 * This function sets up the necessary configurations for the LM35 sensor,
 * allowing it to function correctly in the application.
 *
 * @param lm35 Pointer to a structure of type `LM35_t` that holds the configuration settings for the LM35.
 */
void LM35_init(LM35_t *lm35);

/**
 * @brief Retrieves the temperature measured by the LM35 sensor.
 *
 * This function reads the analog voltage output from the LM35 sensor and converts
 * it into a temperature value.
 *
 * @param lm35 Pointer to the LM35 configuration structure.
 * @return `uint8` The temperature in degrees Celsius measured by the LM35.
 */
uint8 LM35_getTemp(LM35_t *lm35);

#endif /* ECU_LM35_LM35_H_ */
