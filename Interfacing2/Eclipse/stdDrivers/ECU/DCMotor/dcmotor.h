 /******************************************************************************
 *
 * Module: H-Brdige DC Motors
 *
 * File Name: dcmotor.h
 *
 * Description: 
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef ECU_DCMOTOR_DCMOTOR_H_
#define ECU_DCMOTOR_DCMOTOR_H_

#include "../../MCAL/std_types.h"

typedef enum{
  DCMOTOR_DIR_1,
  DCMOTOR_DIR_2
} DCMOTOR_direction_t;

typedef struct{
  uint8 dirPort :2;
  uint8 dirPin1 :3;
  uint8 dirPin2 :3;

  uint8 enableEn : 1;
  uint8 enPort :2;
  uint8 enPin :3;
} DCMOTOR_t;

extern DCMOTOR_t g_dcmotor;

void DCMOTOR_init(DCMOTOR_t * dcmotor);

void DCMOTOR_setDir(DCMOTOR_t * dcmotor, uint8 dir);

void DCMOTOR_stop(DCMOTOR_t * dcmotor);

void DCMOTOR_setSpeed(uint8 speed);

#endif /* ECU_DCMOTOR_DCMOTOR_H_ */
