/*******************************************************************************
 *
 * Module: Human Interface
 *
 * File Name: humaninterface.h
 *
 * Description: Header file for the Human Interface module in the FreeRTOS project.
 *
 * Created on: Oct 25, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef APP_HUMANINTERFACE_HUMANINTERFACE_H_
#define APP_HUMANINTERFACE_HUMANINTERFACE_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../LIB/std_types.h"

/*******************************************************************************
 *                              Macro Definitions                              *
 *******************************************************************************/
#define LOCK_DELAY_TIME pdMS_TO_TICKS(100)  /**< Time to lock the interface */
#define DELAY_TIME     pdMS_TO_TICKS(500)   /**< General delay time */

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * @brief Human Interface task for handling user interactions.
 *
 * This function runs in a FreeRTOS task to manage the human interface
 * and process user inputs or outputs.
 *
 * @param pvParameters Pointer to task parameters.
 */
void HI_task(void *pvParameters);

#endif /* APP_HUMANINTERFACE_HUMANINTERFACE_H_ */
