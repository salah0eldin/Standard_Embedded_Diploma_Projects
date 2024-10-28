/*******************************************************************************
 *
 * Module: Queues
 *
 * File Name: queues.h
 *
 * Description: Header file for queue declarations used in the FreeRTOS project.
 *
 * Created on: Oct 25, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef APP_QUEUES_H_
#define APP_QUEUES_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/queue.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

/**
 * @brief Queue handle for receiving data.
 */
extern QueueHandle_t g_xQueueReceive;

/**
 * @brief Queue handle for sending data.
 */
extern QueueHandle_t g_xQueueSend;

#endif /* APP_QUEUES_H_ */
