/*******************************************************************************
 *
 * Module: Global Variables
 *
 * File Name: globals.h
 *
 * Description: This header file contains the declarations of global queue
 *              handles and semaphores used throughout the application.
 *
 * Created on: Oct 25, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef APP_GLOBALS_H_
#define APP_GLOBALS_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/queue.h"
#include "../FreeRTOS/semphr.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

/**
 * @brief Global queue handle for receiving data.
 */
extern QueueHandle_t g_xQueueReceive;

/**
 * @brief Global queue handle for sending data.
 */
extern QueueHandle_t g_xQueueSend;

/**
 * @brief Global semaphore handle for door control synchronization.
 */
extern SemaphoreHandle_t g_doorSemphr;

#endif /* APP_GLOBALS_H_ */
