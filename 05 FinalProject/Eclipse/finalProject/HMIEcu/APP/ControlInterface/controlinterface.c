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
uint8 dataReceive;

void CI_usartReceiveIntHandl(void) {
	USART_receiveCharNonBlocking(&dataReceive);
//	xSemaphoreGiveFromISR(usartReceiveSemphr, NULL);
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

//void CI_usartReceiverTask(void *pvParameters) {
//	if (USART_isInit() == FALSE) {
//		USART_init(&g_usart);
//	}
//
//	usartReceiveSemphr = xSemaphoreCreateBinary();

//USART_setRXCompleteInterruptHandler(CI_usartReceiveIntHandl);

//	for (;;) {
//		if (xSemaphoreTake(usartReceiveSemphr, portMAX_DELAY) == pdTRUE) {
//
//		}
//
//		if (xQueueSend(g_xQueueReceive, &dataReceive, (TickType_t)20) == pdPASS) {
//
//		}
//	}
//}
