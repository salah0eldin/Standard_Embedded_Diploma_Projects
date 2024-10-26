/*
 * main.c
 *
 *  Created on: Oct 24, 2024
 *      Author: dell
 */

#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"

#include "queues.h"

#include "HMIECUInterface/hmi.h"
#include "Door/door.h"

QueueHandle_t g_xQueueReceive;
QueueHandle_t g_xQueueSend;

int main() {
	g_xQueueReceive = xQueueCreate(5, sizeof(uint8));
	if (g_xQueueReceive == NULL) {
		return 0;
	}

	g_xQueueSend = xQueueCreate(10, sizeof(uint8));
	if (g_xQueueSend == NULL) {
		return 0;
	}

//	if (pdPASS != xTaskCreate(DOOR_task, "DOR", 128, NULL, 1, NULL)) {
//		return 0;
//	}

	if (pdPASS != xTaskCreate(HMI_usartSenderTask, "HMS", 64, NULL, 2, NULL)) {
		return 0;
	}

	if (pdPASS
			!= xTaskCreate(HMI_usartReceiverTask, "HMR", 900, NULL, 3, NULL)) {
		return 0;
	}

	vTaskStartScheduler();
}
