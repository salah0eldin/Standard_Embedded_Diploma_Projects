/*******************************************************************************
 *
 * Module: Control Interface
 *
 * File Name: controlinterface.h
 *
 * Description: Header file for the Control Interface USART task.
 *
 * Created on: Oct 25, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef APP_CONTROLINTERFACE_CONTROLINTERFACE_H_
#define APP_CONTROLINTERFACE_CONTROLINTERFACE_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../LIB/std_types.h"

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * @brief USART task for control interface.
 *
 * This function handles the USART communication task within the FreeRTOS
 * environment, allowing for effective data transmission and reception.
 *
 * @param pvParameters: Parameters passed to the task (not used in this implementation).
 */
void CI_usartTask(void *pvParameters);

#endif /* APP_CONTROLINTERFACE_CONTROLINTERFACE_H_ */
