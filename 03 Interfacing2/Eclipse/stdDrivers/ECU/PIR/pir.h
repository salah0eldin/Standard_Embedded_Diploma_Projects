/******************************************************************************
 *
 * Module: PIR Sensor
 *
 * File Name: pir.h
 *
 * Description: Header file for the PIR (Passive Infrared) sensor driver, which
 *              includes the initialization function and motion detection state
 *              retrieval for a PIR sensor connected to a specified port and pin.
 *
 * Created on: Oct 24, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef ECU_PIR_PIR_H_
#define ECU_PIR_PIR_H_

/*******************************************************************************
 *                               Includes                                      *
 *******************************************************************************/
/* Include standard types header */
#include "../../std_types.h"

/*******************************************************************************
 *                               Enums Declaration                             *
 *******************************************************************************/

/**
 * @enum PIR_state
 * @brief Enum to represent the state of the PIR sensor.
 */
typedef enum {
  PIR_STATE_NO_MOTION, /**< No motion detected */
  PIR_STATE_MOTION     /**< Motion detected    */
} PIR_state;

/*******************************************************************************
 *                              Struct Definitions                             *
 *******************************************************************************/

/**
 * @struct PIR_t
 * @brief Struct to represent a PIR sensor configuration.
 *
 * @var PIR_t::port The port where the PIR sensor is connected (2 bits wide).
 * @var PIR_t::pin The pin on the port where the PIR sensor is connected (3 bits wide).
 */
typedef struct {
  uint8 port :2; /**< Port number (e.g., PORTA_ID, PORTB_ID) */
  uint8 pin :3;  /**< Pin number on the port (e.g., PIN0_ID, PIN1_ID) */
} PIR_t;

/*******************************************************************************
 *                               Global Variables                              *
 *******************************************************************************/

/**
 * @brief Global variable representing PIR sensor 1 configuration.
 */
extern PIR_t g_pir1;

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * @brief Initialize the PIR sensor with the specified configuration.
 *
 * @param[in] pir The PIR sensor configuration (port and pin).
 */
void PIR_init(PIR_t pir);

/**
 * @brief Get the state of the PIR sensor (motion detected or not).
 *
 * @param[in] pir The PIR sensor configuration (port and pin).
 *
 * @return The current state of the PIR sensor (PIR_STATE_MOTION or PIR_STATE_NO_MOTION).
 */
uint8 PIR_getState(PIR_t pir);

#endif /* ECU_PIR_PIR_H_ */
