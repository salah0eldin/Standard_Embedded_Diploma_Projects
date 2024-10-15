/******************************************************************************
 *
 * Module: Motor Control
 *
 * File Name: motor.h
 *
 * Description: Header file for the motor control module, which adjusts motor speed
 *              based on temperature readings.
 *
 * Created on: Oct 5, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef APP_MOTOR_MOTOR_H_
#define APP_MOTOR_MOTOR_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../std_types.h"

/*******************************************************************************
 *                                Data Types                                   *
 *******************************************************************************/

/* Temperature threshold levels for adjusting motor speed */
typedef enum {
  TEMP_LEVEL1 = 25,  /* Temperature level 1 threshold at 25°C */
  TEMP_LEVEL2 = 30,  /* Temperature level 2 threshold at 30°C */
  TEMP_LEVEL3 = 35,  /* Temperature level 3 threshold at 35°C */
  TEMP_LEVEL4 = 40   /* Temperature level 4 threshold at 40°C */
} TEMP_Threshold_t;

/* Motor speed levels based on temperature */
typedef enum {
  MOTOR_SPEED_LEVEL0_STOP = 0,    /* Motor stopped */
  MOTOR_SPEED_LEVEL1 = 25,        /* Motor running at 25% speed */
  MOTOR_SPEED_LEVEL2 = 50,        /* Motor running at 50% speed */
  MOTOR_SPEED_LEVEL3 = 75,        /* Motor running at 75% speed */
  MOTOR_SPEED_LEVEL4_MAX = 100    /* Motor running at 100% (max) speed */
} MOTOR_Speed_t;

/*******************************************************************************
 *                                Global Variables                             *
 *******************************************************************************/

/* Global variable to store the current temperature reading */
extern uint8 g_temprature;

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * @brief Initializes the motor control system.
 *
 * This function sets up the necessary peripherals to control motor speed based on
 * temperature inputs. It should be called before any other motor control function.
 */
void MOTOR_init(void);

/**
 * @brief Adjusts the motor speed based on the current temperature.
 *
 * This function reads the current temperature and adjusts the motor speed accordingly.
 * The motor speed is increased as the temperature crosses defined thresholds.
 */
void MOTOR_handleTemperature(void);

#endif /* APP_MOTOR_MOTOR_H_ */
