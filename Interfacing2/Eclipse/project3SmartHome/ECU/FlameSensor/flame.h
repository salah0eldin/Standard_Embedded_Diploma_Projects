/******************************************************************************
 *
 * Module: Flame Sensor
 *
 * File Name: flame.h
 *
 * Description: 
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef ECU_FLAMESENSOR_FLAME_H_
#define ECU_FLAMESENSOR_FLAME_H_

#include "../../MCAL/std_types.h"

typedef struct
{
  uint8 port :2;
  uint8 pin :3;
  uint8 flameLogic :1;
  uint8 :0;
} FLAME_t;

extern FLAME_t g_flameSensor1;

void FLAME_init (FLAME_t *flameSensor);

uint8 FLAME_isFlame (FLAME_t *flameSensor);

#endif /* ECU_FLAMESENSOR_FLAME_H_ */
