/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: 
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef ECU_BUZZER_BUZZER_H_
#define ECU_BUZZER_BUZZER_H_

#include "../../MCAL/std_types.h"

typedef enum
{
  BUZZER_LOGIC_POSITIVE, BUZZER_LOGIC_NEGATIVE
} BUZZER_logic_t;

typedef struct
{
  uint8 port :2;
  uint8 pin :3;
  uint8 buzzerLogic :1;
  uint8 :0;
} BUZZER_t;

extern BUZZER_t g_buzzer1;

void BUZZER_init (BUZZER_t *buzzer);

void BUZZER_turnOn (BUZZER_t *buzzer);

void BUZZER_turnOff (BUZZER_t *buzzer);

void BUZZER_toggle (BUZZER_t *buzzer);

#endif /* ECU_BUZZER_BUZZER_H_ */
