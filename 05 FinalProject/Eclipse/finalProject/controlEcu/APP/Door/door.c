/*******************************************************************************
 *
 * Module: Door Control
 *
 * File Name: door.c
 *
 * Description: Implementation of the Door Control module that manages door
 *              operations including opening and closing mechanisms based on
 *              sensor input in the FreeRTOS project.
 *
 * Created on: Oct 26, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "door.h"

#include "../../../Shared/shared.h"
#include "../../ECU/DCMotor/dcmotor.h"
#include "../../ECU/PIR/pir.h"
#include "../globals.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

/**
 * @brief Value to send via queue to indicate the state of the door.
 */
uint8 sendValue = 0;

/*******************************************************************************
 *                              Function Definitions                           *
 *******************************************************************************/

/**
 * @brief Task for managing door operations.
 *
 * This function controls the door mechanism, including opening and closing
 * the door based on motion detection from the PIR sensor. It uses a
 * DC motor to operate the door and communicates states via a queue.
 *
 * @param pvParameters Pointer to task parameters.
 */
void DOOR_task(void *pvParameters) {
    DCMOTOR_init(&g_dcmotor); // Initialize the DC motor.
    DCMOTOR_stop(&g_dcmotor); // Ensure the motor is stopped initially.
    PIR_init(g_pir1);         // Initialize the PIR sensor.

    for (;;) {
        // Wait for the semaphore to be available for door operation.
        if (xSemaphoreTake(g_doorSemphr, portMAX_DELAY) == pdTRUE) {
            // Set motor direction to open the door.
            DCMOTOR_setDir(&g_dcmotor, DCMOTOR_DIR_1);
            vTaskDelay(DOOR_DELAY); // Allow the door to open.

            sendValue = SHARED_WAIT_PEOPLE; // Set value for queue to indicate waiting for people.
            if (xQueueSend(g_xQueueSend, &sendValue, portMAX_DELAY) == pdPASS) {
                // Successfully sent the waiting state to the queue.
            }

            DCMOTOR_stop(&g_dcmotor); // Stop the motor after opening.

            // Wait until no motion is detected.
            while (PIR_getState(g_pir1) == PIR_STATE_MOTION)
                ;

            // Set motor direction to close the door.
            DCMOTOR_setDir(&g_dcmotor, DCMOTOR_DIR_2);
            sendValue = SHARED_LOCKING_DOOR; // Set value for queue to indicate locking the door.
            if (xQueueSend(g_xQueueSend, &sendValue, portMAX_DELAY) == pdPASS) {
                // Successfully sent the locking state to the queue.
            }

            vTaskDelay(DOOR_DELAY); // Allow time for the door to close.
            DCMOTOR_stop(&g_dcmotor); // Stop the motor after closing.

            sendValue = SHARED_DOOR_CLOSED; // Set value for queue to indicate the door is closed.
            if (xQueueSend(g_xQueueSend, &sendValue, portMAX_DELAY) == pdPASS) {
                // Successfully sent the closed state to the queue.
            }
        }
    }
}
