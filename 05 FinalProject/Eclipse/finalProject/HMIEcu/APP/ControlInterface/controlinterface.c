/*******************************************************************************
 *
 * Module: Control Interface
 *
 * File Name: controlinterface.c
 *
 * Description: Source file for the Control Interface USART task implementation.
 *
 * Created on: Oct 25, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#include "controlinterface.h"

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../FreeRTOS/FreeRTOS.h"
#include "../../FreeRTOS/semphr.h"
#include "../../MCAL/USART/usart.h"
#include "../queues.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
SemaphoreHandle_t usartReceiveSemphr;

/*******************************************************************************
 *                              Function Definitions                           *
 *******************************************************************************/

/**
 * @brief USART Receive Interrupt Handler.
 *
 * This function handles received characters from the USART. It reads the
 * character and sends it to the receiving queue.
 */
void CI_usartReceiveIntHandl(void) {
    uint8 dataReceive;
    USART_receiveCharNonBlocking(&dataReceive);
    if (xQueueSend(g_xQueueReceive, &dataReceive, (TickType_t)20) == pdPASS) {
         /*Successfully sent the received data to the queue*/
    }
}

/**
 * @brief USART Task for Control Interface.
 *
 * This FreeRTOS task initializes USART if not already done, sets the RX complete
 * interrupt handler, and continuously sends characters from the send queue
 * to the USART.
 *
 * @param pvParameters: Parameters passed to the task (not used in this implementation).
 */
void CI_usartTask(void *pvParameters) {
    if (USART_isInit() == FALSE) {
        USART_init(&g_usart);
    }

    USART_setRXCompleteInterruptHandler(CI_usartReceiveIntHandl);

    uint8 dataSend;
    for (;;) {
        if (xQueueReceive(g_xQueueSend, &dataSend, portMAX_DELAY) == pdPASS) {
            while (!USART_sendCharNonBlocking(dataSend))
                ; /*Wait until the character is sent*/
        }
    }
}
