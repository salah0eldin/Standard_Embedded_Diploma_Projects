/******************************************************************************
 *
 * Module: Calculator
 *
 * File Name: calc.h
 *
 * Description: 
 *
 * Created on: Sep 28, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef APP_CALC_H_
#define APP_CALC_H_

#include "../MCAL/std_types.h"

typedef enum {
	CALC_FIRST_NUM_INPUT,
	CALC_SECOND_NUM_INPUT,
	CALC_FINISH_CALC,
	CALC_ANS_CONTINUE,
	CALC_ANS_FINISH_CALC
} CALC_state_t;

typedef struct {
	sint32 result;
	sint16 num1;
	sint16 num2;
	uint8 operator;
} CALC_t;

void CALC_init(CALC_t * calculator);

void CALC_reset(CALC_t * calculator);

#endif /* APP_CALC_H_ */
