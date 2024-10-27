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
#include "../globals.h"

static uint8 pass[SHARED_PASS_LENGTH] = { 0 };
uint8 passTemp[SHARED_PASS_LENGTH] = { 0 };
uint8 equality = FALSE;
uint8 i = 0;
uint8 passTimes = 3;
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
					while (PASSHANDLER_checkPass() == FALSE)
						;
				} else {
					while (PASSHANDLER_updatePass() == FALSE)
						;
				}

				break;
			case SHARED_OPEN_DOOR:
				if (PASSHANDLER_checkPass() == TRUE) {
					xSemaphoreGive(g_doorSemphr);
				}
				break;
			case SHARED_CHANGE_PASS:
				if (PASSHANDLER_checkPass() == TRUE) {
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
		I2C_EEPROM_receiveData(PASSHANDLER_PASS_ADDR, pass, SHARED_PASS_LENGTH);
	}

	return (ret == TRUE) ? SHARED_SUCCESS : SHARED_FAIL;
}

uint8 PASSHANDLER_checkPass(void) {
	do {
		i = 0;
		equality = TRUE;
		while (i < SHARED_PASS_LENGTH) {
			if (xSemaphoreTake(usartReceiveSemphr, portMAX_DELAY) == pdTRUE) {
				equality &= (pass[i++] == g_dataReceive);
			}
		}
		if (equality == FALSE) {
			passTimes--;
			g_dataSend = SHARED_PASS_DONT_MATCH;
		} else {
			g_dataSend = SHARED_SUCCESS;
		}
		if (xQueueSend(g_xQueueSend, &g_dataSend, (TickType_t)20) == pdPASS) {

		}
		if (passTimes == 0) {
			do {
				if (xSemaphoreTake(usartReceiveSemphr, portMAX_DELAY) == pdTRUE) {
				}
			} while (SHARED_BUZZER_ON != g_dataReceive);
			BUZZER_turnOn(&g_buzzer1);
			do {
				if (xSemaphoreTake(usartReceiveSemphr, portMAX_DELAY) == pdTRUE) {
				}
			} while (SHARED_BUZZER_OFF != g_dataReceive);
			BUZZER_turnOff(&g_buzzer1);
		}

	} while (passTimes != 0 && equality == FALSE);
	passTimes = 3;
	return equality;
}

uint8 PASSHANDLER_updatePass(void) {

	i = 0;
	equality = TRUE;
	while (i < SHARED_PASS_LENGTH) {
		if (xSemaphoreTake(usartReceiveSemphr, portMAX_DELAY) == pdTRUE) {
			passTemp[i++] = g_dataReceive;
		}
	}
	i = 0;
	while (i < SHARED_PASS_LENGTH) {
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

	if (equality == TRUE) {
		I2C_EEPROM_sendByte(PASSHANDLER_IS_PASS_ADDR, PASSHANDLER_PASS_EXIST);
		vTaskDelay(pdMS_TO_TICKS(100));
		I2C_EEPROM_sendData(PASSHANDLER_PASS_ADDR, passTemp,
		SHARED_PASS_LENGTH);
		i = 0;
		while (i < SHARED_PASS_LENGTH) {
			pass[i] = passTemp[i];
			i++;
		}
	}

	return (g_dataSend == SHARED_SUCCESS);
}

