/*******************************************************************************
 *
 * Module: Main Application
 *
 * File Name: main.c
 *
 * Description: This file contains the main function that initializes queues,
 *              semaphores, and FreeRTOS tasks for the system's operation.
 *
 * Created on: Oct 24, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"

#include "HMIECUInterface/hmi.h"
#include "Door/door.h"
#include "globals.h"

/*******************************************************************************
 *                             Global Variables                                *
 *******************************************************************************/
QueueHandle_t g_xQueueReceive; 	/* Queue for receiving data */
QueueHandle_t g_xQueueSend; 	/* Queue for sending data   */
SemaphoreHandle_t g_doorSemphr; /* Semaphore for door control synchronization */

/*******************************************************************************
 *                                  Main                                       *
 *******************************************************************************/

/**
 * @brief Main function that initializes queues, semaphores, and tasks, then
 *        starts the FreeRTOS scheduler.
 *
 * @return int Returns 0 if any initialization fails, otherwise FreeRTOS takes over.
 */
int main() {
    /* Create a queue for receiving data with 5 slots, each for a uint8 item */
    g_xQueueReceive = xQueueCreate(5, sizeof(uint8));
    if (g_xQueueReceive == NULL) {
        return 0; /* Return if queue creation fails */
    }

    /* Create a queue for sending data with 10 slots, each for a uint8 item */
    g_xQueueSend = xQueueCreate(10, sizeof(uint8));
    if (g_xQueueSend == NULL) {
        return 0; /* Return if queue creation fails */
    }

    /* Create a binary semaphore for door control */
    g_doorSemphr = xSemaphoreCreateBinary();
    if (g_doorSemphr == NULL) {
        return 0; /* Return if semaphore creation fails */
    }

    /* Create the door task with a stack size of 128 and priority 1 */
    if (pdPASS != xTaskCreate(DOOR_task, "DOR", 128, NULL, 1, NULL)) {
        return 0; /* Return if task creation fails */
    }

    /* Create the USART sender task with a stack size of 64 and priority 2 */
    if (pdPASS != xTaskCreate(HMI_usartSenderTask, "HMS", 64, NULL, 2, NULL)) {
        return 0; /* Return if task creation fails */
    }

    /* Create the USART receiver task with a stack size of 800 and priority 3 */
    if (pdPASS != xTaskCreate(HMI_usartReceiverTask, "HMR", 800, NULL, 3, NULL)) {
        return 0; /* Return if task creation fails */
    }

    /* Enable global interrupts */
    __asm__("SEI");

    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    /* Return 0 if the scheduler exits (this should not happen) */
    return 0;
}
