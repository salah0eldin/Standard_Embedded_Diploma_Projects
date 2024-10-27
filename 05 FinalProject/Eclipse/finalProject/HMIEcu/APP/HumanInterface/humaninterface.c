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

uint8 timeToWait = 5;
uint8 sendValue = 0;
uint8 receiveValue = 0;
uint8 i = 0;

void HI_controlError(void) {
	LCD_displayString("Control Error");
	LCD_displayStringRowColumn(1, 0, "Try again!");
	vTaskDelay(pdMS_TO_TICKS(500));
}

void HI_enterPassword(void) {
	uint8 key;
	LCD_displayStringRowColumn(1, 0, "Pass:_____");
	LCD_moveCursor(1, 5);
	i = 0;
	while (i < SHARED_PASS_LENGTH) {
		key = KEYPAD_getPressedKeyBlocking();
		if (key >= '0' && key <= '9') {
			i++;
			LCD_displayCharacter('*');
			if (i < SHARED_PASS_LENGTH)
				if (xQueueSend(g_xQueueSend, &key, (TickType_t)20) == pdPASS) {
				}

		}
	}
	while (KEYPAD_ENTER_ASCII != KEYPAD_getPressedKeyBlocking())
		;
	if (xQueueSend(g_xQueueSend, &key, (TickType_t)20) == pdPASS) {
	}
}

uint8 HI_getAndCheckPass(void) {
	uint8 passTimes = 3;
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
			HI_controlError();
			break;
		case SHARED_PASS_DONT_MATCH:
			passTimes--;
			LCD_displayString("Wrong Pass!");
			LCD_moveCursor(1, 0);
			LCD_displayNumber(passTimes);
			LCD_displayString(" Tries Left");
			vTaskDelay(pdMS_TO_TICKS(500));
			break;
		}
		if (passTimes == 0) {
			sendValue = SHARED_BUZZER_ON;
			if (xQueueSend(g_xQueueSend, &sendValue, (TickType_t)20) == pdPASS) {
			}
			LCD_clearScreen();
			LCD_displayString("System Locked");
			LCD_displayStringRowColumn(1, 0, "Wait For");
			while (timeToWait != 0) {
				LCD_moveCursor(1, 9);
				LCD_displayNumber(timeToWait);
				LCD_displayString(" Sec ");
				vTaskDelay(pdMS_TO_TICKS(1000));
				timeToWait--;
			}
			sendValue = SHARED_BUZZER_OFF;
			if (xQueueSend(g_xQueueSend, &sendValue, (TickType_t)20) == pdPASS) {
			}
		}
	} while (passTimes != 0 && receiveValue != SHARED_SUCCESS);
	return (receiveValue == SHARED_SUCCESS);
}

uint8 HI_updatePass(void) {
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
		HI_controlError();
		break;
	case SHARED_PASS_DONT_MATCH:
		LCD_displayString("Passwords don't");
		LCD_displayStringRowColumn(1, 0, "Match!");
		vTaskDelay(pdMS_TO_TICKS(500));
		break;
	}

	return (receiveValue == SHARED_SUCCESS);
}

void HI_task(void *pvParameters) {
	LCD_init();
	KEYPAD_init();
	KEYPAD_setKeys(keypadKeys);

	LCD_displayString("Door Lock System");
	LCD_displayStringRowColumn(1, 0, "Loading...");
	_delay_ms(300);

	uint8 key;

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
		while (HI_getAndCheckPass() == FALSE)
			;
		LCD_clearScreen();
		LCD_displayString("System Un-Locked");
		LCD_displayStringRowColumn(1, 0, "Welcome!");
		vTaskDelay(pdMS_TO_TICKS(500));

	} else {
		while (HI_updatePass() == FALSE)
			;
	}

	for (;;) {
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 1, "+ : Open Door");
		LCD_displayStringRowColumn(1, 1, "- : Change Pass");
		key = KEYPAD_getPressedKeyBlocking();
		if (key == '-' || key == '+') {
			sendValue = (key == '+') ? SHARED_OPEN_DOOR : SHARED_CHANGE_PASS;
			if (xQueueSend(g_xQueueSend, &sendValue, (TickType_t)20) == pdPASS) {
			}
			if (HI_getAndCheckPass() == TRUE) {
				if (key == '+') {
					LCD_displayString("Door Unlocking");
					LCD_displayStringRowColumn(1, 0, "Please Wait...");
					receiveValue = SHARED_FAIL;
					do {
						if (xQueueReceive(g_xQueueReceive, &receiveValue,
								pdMS_TO_TICKS(300)) == pdPASS) {

						}
					} while (receiveValue != SHARED_WAIT_PEOPLE);
					LCD_clearScreen();
					LCD_displayString("Wait For People");
					LCD_displayStringRowColumn(1, 0, "To Enter");
					do {
						if (xQueueReceive(g_xQueueReceive, &receiveValue,
								pdMS_TO_TICKS(300)) == pdPASS) {

						}
					} while (receiveValue != SHARED_LOCKING_DOOR);
					LCD_clearScreen();
					LCD_displayString("Door Locking...");
					do {
						if (xQueueReceive(g_xQueueReceive, &receiveValue,
								pdMS_TO_TICKS(300)) == pdPASS) {

						}
					} while (receiveValue != SHARED_DOOR_CLOSED);

				} else {
					if (HI_updatePass() == TRUE) {
						LCD_displayString("Pass Changed");
						LCD_displayStringRowColumn(1, 0, "Successfully!");
						vTaskDelay(pdMS_TO_TICKS(300));
					}
				}
			}
		}
	}

}
