 /******************************************************************************
 *
 * Module: Temperature Sensor LM35
 *
 * File Name: lm35.h
 *
 * Description: 
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef ECU_LM35_LM35_H_
#define ECU_LM35_LM35_H_

#include "../../MCAL/std_types.h"

#define LM35_MAX_VOLT_VALUE     1.5
#define LM35_MAX_TEMPERATURE    150

typedef struct
{
  uint8 port :2;
  uint8 pin :3;
} LM35_t;

extern LM35_t g_lm35_1;

void LM35_init(LM35_t * lm35);

uint8 LM35_getTemp(LM35_t * lm35);

#endif /* ECU_LM35_LM35_H_ */
