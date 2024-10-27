/*
 * door.c
 *
 *  Created on: Oct 26, 2024
 *      Author: dell
 */

#include "door.h"

#include "../../../Shared/shared.h"
#include "../../ECU/DCMotor/dcmotor.h"
#include "../../ECU/PIR/pir.h"
#include "../globals.h"

uint8 sendValue = 0;

void DOOR_task(void *pvParameters) {
	DCMOTOR_init(&g_dcmotor);
	DCMOTOR_stop(&g_dcmotor);
	PIR_init(g_pir1);

	for (;;) {
		if (xSemaphoreTake(g_doorSemphr, portMAX_DELAY) == pdTRUE) {
			DCMOTOR_setDir(&g_dcmotor, DCMOTOR_DIR_1);
			vTaskDelay(pdMS_TO_TICKS(1500));
			sendValue = SHARED_WAIT_PEOPLE;
			if (xQueueSend(g_xQueueSend, &sendValue, portMAX_DELAY) == pdPASS) {

			}
			DCMOTOR_stop(&g_dcmotor);
			while (PIR_getState(g_pir1) == PIR_STATE_MOTION)
				;
			DCMOTOR_setDir(&g_dcmotor, DCMOTOR_DIR_2);
			sendValue = SHARED_LOCKING_DOOR;
			if (xQueueSend(g_xQueueSend, &sendValue, portMAX_DELAY) == pdPASS) {

			}
			vTaskDelay(pdMS_TO_TICKS(1500));
			DCMOTOR_stop(&g_dcmotor);
			sendValue = SHARED_DOOR_CLOSED;
			if (xQueueSend(g_xQueueSend, &sendValue, portMAX_DELAY) == pdPASS) {

			}
		}
	}
}
