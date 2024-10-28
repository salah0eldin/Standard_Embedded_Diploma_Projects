/*******************************************************************************
 *
 * Module: Door Control
 *
 * File Name: door.h
 *
 * Description: Header file for the Door Control module in the FreeRTOS project,
 *              responsible for managing door operations and task handling.
 *
 * Created on: Oct 26, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef APP_DOOR_DOOR_H_
#define APP_DOOR_DOOR_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../LIB/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DOOR_DELAY pdMS_TO_TICKS(500)

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * @brief Task for managing door operations.
 *
 * This function runs as a FreeRTOS task to handle the logic for door control,
 * including opening, closing, and checking the state of the door.
 *
 * @param pvParameters Pointer to task parameters.
 */
void DOOR_task(void *pvParameters);

#endif /* APP_DOOR_DOOR_H_ */
