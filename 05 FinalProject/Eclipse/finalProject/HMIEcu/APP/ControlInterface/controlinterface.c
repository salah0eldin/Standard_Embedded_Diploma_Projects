/*
 * controlinterface.c
 *
 *  Created on: Oct 25, 2024
 *      Author: dell
 */

#include "controlinterface.h"

#include "../../FreeRTOS/FreeRTOS.h"
#include "../../FreeRTOS/semphr.h"
#include "../../MCAL/USART/usart.h"
#include "../queues.h"

SemaphoreHandle_t usartReceiveSemphr;

void CI_usartReceiveIntHandl(void) {
	uint8 dataReceive;
	USART_receiveCharNonBlocking(&dataReceive);
	if (xQueueSend(g_xQueueReceive, &dataReceive, (TickType_t)20) == pdPASS) {

	}
}

void CI_usartSenderTask(void *pvParameters) {
	if (USART_isInit() == FALSE) {
		USART_init(&g_usart);
	}

	USART_setRXCompleteInterruptHandler(CI_usartReceiveIntHandl);

	uint8 dataSend;
	for (;;) {
		if (xQueueReceive(g_xQueueSend, &dataSend, portMAX_DELAY) == pdPASS) {
			while (!USART_sendCharNonBlocking(dataSend))
				;
		}
	}
}

