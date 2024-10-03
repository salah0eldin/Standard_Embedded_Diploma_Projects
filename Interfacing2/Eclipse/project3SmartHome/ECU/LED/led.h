 /******************************************************************************
 *
 * Module: LED
 *
 * File Name: led.h
 *
 * Description: 
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef ECU_LED_LED_H_
#define ECU_LED_LED_H_

#include "../../MCAL/std_types.h"

typedef enum{
	LED_LOGIC_POSITIVE,
	LED_LOGIC_NEGATIVE
} LED_logic_t;

typedef struct{
	uint8 port : 2;
	uint8 pin  : 3;
	uint8 ledLogic : 1;
	uint8 :0;
} LED_t;

extern LED_t g_ledRed, g_ledGreen, g_ledBlue;

void LED_init(LED_t * led);

void LED_turnOn(LED_t *led);

void LED_turnOff(LED_t *led);

void LED_toggle(LED_t *led);

#endif /* ECU_LED_LED_H_ */
