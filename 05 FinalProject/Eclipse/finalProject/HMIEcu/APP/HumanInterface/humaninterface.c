/*
 * humaninterface.c
 *
 *  Created on: Oct 25, 2024
 *      Author: dell
 */

#include <util/delay.h>
#include "../../../shared/shared.h"
#include "../../FreeRTOS/FreeRTOS.h"
#include "../../FreeRTOS/semphr.h"
#include "../../ECU/Keypad/keypad.h"
#include "../../ECU/LCD/lcd.h"
#include "../queues.h"
#include "humaninterface.h"

const uint8 keypadKeys[] = { '7', '8', '9', 0, '4', '5', '6', 0, '1', '2', '3',
		'-', 0, '0', KEYPAD_ENTER_ASCII, '+' };

uint8 timeToWait = 9;
uint8 key = KEYPAD_NO_KEY;
uint8 passTimes = 3;
uint8 sendValue = 0;
uint8 receiveValue = 0;
uint8 i = 0;

void HI_enterPassword(void) {
	LCD_displayStringRowColumn(1, 0, "Pass:_____");
	LCD_moveCursor(1, 5);
	i = 0;
	while (i < 5) {
		key = KEYPAD_getPressedKeyBlocking();
		if (key >= '0' && key <= '9') {
			i++;
			LCD_displayCharacter('*');
			if (xQueueSend(g_xQueueSend, &key, (TickType_t)20) == pdPASS) {
			}

		}
	}
	while (KEYPAD_ENTER_ASCII != KEYPAD_getPressedKeyBlocking())
		;
}

void HI_getAndCheckPass(void) {
	do {
		LCD_clearScreen();
		LCD_displayString("Enter the Pass");
		HI_enterPassword();
		receiveValue = SHARED_FAIL;
		if (xQueueReceive(g_xQueueReceive, &receiveValue,
				pdMS_TO_TICKS(300)) == pdPASS) {
		}
		LCD_clearScreen();
		switch (receiveValue) {
		case SHARED_FAIL:
			LCD_displayString("Control Error");
			LCD_displayStringRowColumn(1, 0, "Try again!");
			vTaskDelay(pdMS_TO_TICKS(500));
			break;
		case SHARED_PASS_DONT_MATCH:
			passTimes--;
			LCD_displayString("Wrong Password!");
			LCD_moveCursor(1, 0);
			LCD_displayNumber(passTimes);
			LCD_displayString(" Remaning Tries");
			vTaskDelay(pdMS_TO_TICKS(500));
			break;
		}
		if (passTimes == 0) {
			sendValue = SHARED_BUZZER_ON;
			if (xQueueSend(g_xQueueSend, &sendValue, (TickType_t)20) == pdPASS) {
			}
			LCD_clearScreen();
			LCD_displayString("System Locked");
			LCD_displayStringRowColumn(1, 0, "Wait For 1 Min");
			vTaskDelay(pdMS_TO_TICKS(1000));
			while (timeToWait != 0) {
				LCD_moveCursor(1, 9);
				LCD_displayNumber(timeToWait);
				LCD_displayString(" Sec  ");
				vTaskDelay(pdMS_TO_TICKS(1000));
				timeToWait--;
			}
			sendValue = SHARED_BUZZER_OFF;
			if (xQueueSend(g_xQueueSend, &sendValue, (TickType_t)20) == pdPASS) {
			}
			passTimes = 3;
		}
	} while (receiveValue != SHARED_SUCCESS);
	passTimes = 3;
}

void HI_updatePass(void) {
	do {
		LCD_clearScreen();
		LCD_displayString("Enter new Pass");
		HI_enterPassword();
		LCD_clearScreen();
		LCD_displayString("ReEnter new Pass");
		HI_enterPassword();
		receiveValue = SHARED_FAIL;
		if (xQueueReceive(g_xQueueReceive, &receiveValue,
				pdMS_TO_TICKS(300)) == pdPASS) {
		}
		LCD_clearScreen();
		switch (receiveValue) {
		case SHARED_FAIL:
			LCD_displayString("Control Error");
			LCD_displayStringRowColumn(1, 0, "Try again!");
			vTaskDelay(pdMS_TO_TICKS(500));
			break;
		case SHARED_PASS_DONT_MATCH:
			LCD_displayString("Passwords don't");
			LCD_displayStringRowColumn(1, 0, "Match !");
			vTaskDelay(pdMS_TO_TICKS(500));
			break;
		}
	} while (receiveValue != SHARED_SUCCESS);
}

void HI_task(void *pvParameters) {
	LCD_init();
	KEYPAD_init();
	KEYPAD_setKeys(keypadKeys);

	LCD_displayString("Door Lock System");
	LCD_displayStringRowColumn(1, 0, "Loading...");
	_delay_ms(300);

	for (;;) {
		sendValue = SHARED_CHECK_PASS_EXIST;
		if (xQueueIsQueueEmptyFromISR(
				g_xQueueSend) && xQueueSend(g_xQueueSend, &sendValue, (TickType_t)20) == pdPASS) {
		}

		if (xQueueReceive(g_xQueueReceive, &receiveValue,
				pdMS_TO_TICKS(300)) == pdPASS) {
			break;
		}
	}

	if (receiveValue == SHARED_SUCCESS) {
		HI_getAndCheckPass();
		LCD_clearScreen();
		LCD_displayString("System Un-Locked");
		LCD_displayStringRowColumn(1, 0, "Welcome !");
		vTaskDelay(pdMS_TO_TICKS(500));

	} else {
		HI_updatePass();
	}

	for (;;) {
		LCD_clearScreen();
		LCD_displayString(" + : Open Door");
		LCD_displayStringRowColumn(1, 0, " - : Change Pass");
		for (;;) {
			key = KEYPAD_getPressedKeyBlocking();
			if (key == '-' || key == '+') {
				if (xQueueSend(g_xQueueSend, &key, (TickType_t)20) == pdPASS) {
				}
				HI_getAndCheckPass();
				switch (key) {
				case '+':

					break;
				case '-':
					HI_updatePass();
					break;
				}
			}
		}
	}
}
