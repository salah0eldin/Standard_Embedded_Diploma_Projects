/*
 * queues.h
 *
 *  Created on: Oct 25, 2024
 *      Author: dell
 */

#ifndef APP_GLOBALS_H_
#define APP_GLOBALS_H_

#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/queue.h"
#include "../FreeRTOS/semphr.h"

extern QueueHandle_t g_xQueueReceive;
extern QueueHandle_t g_xQueueSend;

extern SemaphoreHandle_t g_doorSemphr;

#endif /* APP_GLOBALS_H_ */
