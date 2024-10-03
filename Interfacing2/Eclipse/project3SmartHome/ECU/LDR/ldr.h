/******************************************************************************
 *
 * Module: LDR
 *
 * File Name: ldr.h
 *
 * Description: 
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef ECU_LDR_LDR_H_
#define ECU_LDR_LDR_H_

#include "../../MCAL/std_types.h"

typedef enum
{
  LDR_LOGIC_BIGGER_IS_LIGHT, LDR_LOGIC_BIGGER_IS_DARK
} LDR_logic_t;

typedef enum
{
  LDR_LIGHT_OFF, LDR_LIGHT_ON
} LDR_state_t;

typedef struct
{
  uint8 port :2;
  uint8 pin :3;
  uint8 ldrLogic :1;
  uint16 max;
  uint16 min;
  uint16 threshold;

} LDR_t;

extern LDR_t g_ldr1;

void LDR_init (LDR_t *ldr);

uint8 LDR_isLight (LDR_t *ldr);

uint8 LDR_getIntensity (LDR_t *ldr);

#endif /* ECU_LDR_LDR_H_ */
