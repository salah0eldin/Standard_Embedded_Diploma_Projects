/*
 * hmi.c
 *
 *  Created on: Oct 26, 2024
 *      Author: dell
 */

#include "hmi.h"
#include "../../../Shared/shared.h"
#include "../../FreeRTOS/FreeRTOS.h"
#include "../../FreeRTOS/semphr.h"
#include "../../ECU/I2C_EEPROM/i2c_eeprom.h"
#include "../../ECU/Buzzer/buzzer.h"
#include "../../MCAL/USART/usart.h"
#include "../queues.h"

static uint8 pass[5] = { 0 };
uint8 passTemp[5] = { 0 };
uint8 equality = FALSE;
uint8 i = 0;

SemaphoreHandle_t usartReceiveSemphr;

uint8 g_dataReceive;
uint8 g_dataSend;

void HMI_usartSenderTask(void *pvParameters) {
	if (USART_isInit() == FALSE) {
		USART_init(&g_usart);
	}
	uint8 dataSend;
	for (;;) {
		if (xQueueReceive(g_xQueueSend, &dataSend, portMAX_DELAY) == pdPASS) {
			while (!USART_sendCharNonBlocking(dataSend))
				;
		}
	}
}

void CI_usartReceiveIntHandl(void) {
	USART_receiveCharNonBlocking(&g_dataReceive);
	xSemaphoreGiveFromISR(usartReceiveSemphr, NULL);
}

void HMI_usartReceiverTask(void *pvParameters) {
	if (USART_isInit() == FALSE) {
		USART_init(&g_usart);
	}

	I2C_EEPROM_init();

	BUZZER_init(&g_buzzer1);

	usartReceiveSemphr = xSemaphoreCreateBinary();

	USART_setRXCompleteInterruptHandler(CI_usartReceiveIntHandl);

	for (;;) {
		if (xSemaphoreTake(usartReceiveSemphr, portMAX_DELAY) == pdTRUE) {

			uint8 ret;
			switch (g_dataReceive) {
			case SHARED_CHECK_PASS_EXIST:
				ret = PASSHANDLER_isPassExist();
				if (xQueueSend(g_xQueueSend, &ret, (TickType_t)20) == pdPASS) {

				}
				if (ret == SHARED_SUCCESS) {
					PASSHANDLER_checkPass();
				} else {
					PASSHANDLER_updatePass();
				}

				break;
			}

		}

	}
}

uint8 PASSHANDLER_isPassExist(void) {
	uint8 ret = FALSE;

	uint8 val;
	I2C_EEPROM_receiveByte(PASSHANDLER_IS_PASS_ADDR, &val);

	if (val == PASSHANDLER_PASS_EXIST) {
		ret = TRUE;
		I2C_EEPROM_receiveData(PASSHANDLER_PASS_ADDR, pass, 5);
	}

	return (ret == TRUE) ? SHARED_SUCCESS : SHARED_FAIL;
}

void PASSHANDLER_checkPass(void) {
	do {
		i = 0;
		equality = TRUE;
		while (i < 5) {
			if (xSemaphoreTake(usartReceiveSemphr, portMAX_DELAY) == pdTRUE) {
				equality &= (pass[i++] == g_dataReceive);
			}
		}
		if (equality == FALSE) {
			g_dataSend = SHARED_PASS_DONT_MATCH;
		} else {
			g_dataSend = SHARED_SUCCESS;
		}
		if (xQueueSend(g_xQueueSend, &g_dataSend, (TickType_t)20) == pdPASS) {

		}

	} while (equality == FALSE);
}

void PASSHANDLER_updatePass(void) {
	do {
		i = 0;
		equality = TRUE;
		while (i < 5) {
			if (xSemaphoreTake(usartReceiveSemphr, portMAX_DELAY) == pdTRUE) {
				passTemp[i++] = g_dataReceive;
			}
		}
		i = 0;
		while (i < 5) {
			if (xSemaphoreTake(usartReceiveSemphr, portMAX_DELAY) == pdTRUE) {
				equality &= (passTemp[i++] == g_dataReceive);
			}
		}
		if (equality == FALSE) {
			g_dataSend = SHARED_PASS_DONT_MATCH;
		} else {
			g_dataSend = SHARED_SUCCESS;
		}
		if (xQueueSend(g_xQueueSend, &g_dataSend, (TickType_t)20) == pdPASS) {

		}
	} while (equality == FALSE);

	I2C_EEPROM_sendByte(PASSHANDLER_IS_PASS_ADDR, PASSHANDLER_PASS_EXIST);
	vTaskDelay(pdMS_TO_TICKS(100));
	I2C_EEPROM_sendData(PASSHANDLER_PASS_ADDR, passTemp, 5);
	i = 0;
	while (i < 5) {
		pass[i] = passTemp[i];
		i++;
	}

}

