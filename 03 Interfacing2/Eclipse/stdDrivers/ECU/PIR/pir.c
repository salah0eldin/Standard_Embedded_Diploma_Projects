/******************************************************************************
 *
 * Module: PIR Sensor
 *
 * File Name: pir.c
 *
 * Description: Source file for the PIR (Passive Infrared) sensor driver,
 *              containing the initialization function and motion detection
 *              state retrieval logic.
 *
 * Created on: Oct 24, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                               Includes                                      *
 *******************************************************************************/
#include "pir.h"                   /* Include PIR sensor header file */
#include "../../MCAL/GPIO/gpio.h"   /* Include GPIO driver for pin direction and state functions */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/**
 * @brief Global variable representing PIR sensor 1.
 *        Initialized with port PORTC and pin 2 (PIN2).
 */
PIR_t g_pir1 = { .port = PORTC_ID, .pin = PIN2_ID };

/*******************************************************************************
 *                           Function Definitions                              *
 *******************************************************************************/

/**
 * @brief Initializes the PIR sensor by setting the pin direction to input.
 *
 * @param[in] pir The PIR sensor configuration (port and pin).
 */
void PIR_init(PIR_t pir) {
    /* Set the PIR sensor pin as input */
    GPIO_setupPinDirection(pir.port, pir.pin, PIN_INPUT);
}

/**
 * @brief Retrieves the current state of the PIR sensor.
 *
 * @param[in] pir The PIR sensor configuration (port and pin).
 *
 * @return The current state of the PIR sensor (motion detected or no motion).
 */
uint8 PIR_getState(PIR_t pir) {
    /* Check if the PIR sensor pin is HIGH (motion detected) */
    if (LOGIC_HIGH == GPIO_readPin(pir.port, pir.pin)) {
        return PIR_STATE_MOTION;
    } else {
        return PIR_STATE_NO_MOTION;
    }
}
