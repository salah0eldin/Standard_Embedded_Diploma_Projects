/*******************************************************************************
 *
 * Module: Main Application
 *
 * File Name: main.c
 *
 * Description: Main entry point for the FreeRTOS application.
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

#include "queues.h"
#include "HumanInterface/humaninterface.h"
#include "ControlInterface/controlinterface.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
QueueHandle_t g_xQueueReceive;  /* Queue for receiving data */
QueueHandle_t g_xQueueSend;     /* Queue for sending data	*/

/*******************************************************************************
 *                              Main Function                                  *
 *******************************************************************************/

/**
 * @brief Main function that initializes queues, and tasks, then
 *        starts the FreeRTOS scheduler.
 *
 * @return int Returns 0 if any initialization fails, otherwise FreeRTOS takes over.
 */
int main() {
    /* Create the receive queue with a maximum of 5 items of size uint8 */
    g_xQueueReceive = xQueueCreate(5, sizeof(uint8));
    if (g_xQueueReceive == NULL) {
        return 0; /* Failed to create the receive queue */
    }

    /* Create the send queue with a maximum of 5 items of size uint8 */
    g_xQueueSend = xQueueCreate(5, sizeof(uint8));
    if (g_xQueueSend == NULL) {
        return 0; /* Failed to create the send queue */
    }

    /* Create the Human Interface task */
    if(pdPASS != xTaskCreate(HI_task, "HI", 1000, NULL, 1, NULL)) {
        return 0; /* Failed to create the Human Interface task */
    }

    /* Create the Control Interface USART task */
    if(pdPASS != xTaskCreate(CI_usartTask, "CIS", 80, NULL, 2, NULL)) {
        return 0; /* Failed to create the Control Interface task */
    }

    /* Enable global interrupts */
    __asm__("SEI");

    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    /* Return 0 if the scheduler exits (this should not happen) */
    return 0;
}
