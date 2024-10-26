/*
 * hmi.h
 *
 *  Created on: Oct 26, 2024
 *      Author: dell
 */

#ifndef APP_HMIECUINTERFACE_HMI_H_
#define APP_HMIECUINTERFACE_HMI_H_

#include "../../LIB/std_types.h"

#define PASSHANDLER_IS_PASS_ADDR	0x00

#define PASSHANDLER_PASS_ADDR		0x08

#define PASSHANDLER_PASS_EXIST		0x01


void HMI_usartSenderTask(void *pvParameters);

void HMI_usartReceiverTask(void *pvParameters);

uint8 PASSHANDLER_isPassExist(void);

void PASSHANDLER_checkPass(void);

void PASSHANDLER_updatePass(void);

#endif /* APP_HMIECUINTERFACE_HMI_H_ */
