/*
 * queues.h
 *
 *  Created on: Oct 25, 2024
 *      Author: dell
 */

#ifndef APP_QUEUES_H_
#define APP_QUEUES_H_

#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/queue.h"

extern QueueHandle_t g_xQueueReceive;
extern QueueHandle_t g_xQueueSend;

#endif /* APP_QUEUES_H_ */
