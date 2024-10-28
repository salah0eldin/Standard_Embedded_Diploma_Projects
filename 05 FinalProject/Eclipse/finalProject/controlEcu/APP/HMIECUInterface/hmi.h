/*******************************************************************************
 *
 * Module: Human Machine Interface (HMI) ECU Interface
 *
 * File Name: hmi.h
 *
 * Description: Header file for the HMI module responsible for handling
 *              communication with the ECU via USART in the FreeRTOS project.
 *
 * Created on: Oct 26, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef APP_HMIECUINTERFACE_HMI_H_
#define APP_HMIECUINTERFACE_HMI_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../LIB/std_types.h"

/*******************************************************************************
 *                              Macro Definitions                              *
 *******************************************************************************/

/**
 * @brief Address in EEPROM for storing if the password exists.
 */
#define PASSHANDLER_IS_PASS_ADDR    0x00

/**
 * @brief Address in EEPROM for storing the password.
 */
#define PASSHANDLER_PASS_ADDR       0x08

/**
 * @brief Value indicating the password exists.
 */
#define PASSHANDLER_PASS_EXIST      0x01

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * @brief Task for sending data over USART.
 *
 * This function runs as a FreeRTOS task to handle outgoing USART communication.
 *
 * @param pvParameters Pointer to task parameters.
 */
void HMI_usartSenderTask(void *pvParameters);

/**
 * @brief Task for receiving data over USART.
 *
 * This function runs as a FreeRTOS task to handle incoming USART communication.
 *
 * @param pvParameters Pointer to task parameters.
 */
void HMI_usartReceiverTask(void *pvParameters);

#endif /* APP_HMIECUINTERFACE_HMI_H_ */
