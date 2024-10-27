/******************************************************************************
 *
 * Module: H-Bridge DC Motors
 *
 * File Name: dcmotor.h
 *
 * Description: Header file for the H-Bridge DC Motor driver.
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef ECU_DCMOTOR_DCMOTOR_H_
#define ECU_DCMOTOR_DCMOTOR_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../LIB/std_types.h"

/*******************************************************************************
 *                              Types Declaration                              *
 *******************************************************************************/

/* Motor direction options*/
typedef enum {
  DCMOTOR_DIR_1,  /* Motor direction 1 */
  DCMOTOR_DIR_2   /* Motor direction 2 */
} DCMOTOR_direction_t;

/* DC Motor Configuration Structure */
typedef struct {
  uint8 dirPort : 2;      /* Direction port for the motor (2 bits) */
  uint8 dirPin1 : 3;      /* Direction pin 1 for the motor (3 bits) */
  uint8 dirPin2 : 3;      /* Direction pin 2 for the motor (3 bits) */

  uint8 enableEn : 1;     /* Enable pin configuration (1 bit) */
  uint8 enPort : 2;       /* Enable port for the motor (2 bits) */
  uint8 enPin : 3;        /* Enable pin for the motor (3 bits) */
} DCMOTOR_t;

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
extern DCMOTOR_t g_dcmotor;  /* Global instance of the DC Motor configuration */

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * @brief Initializes the DC Motor according to the provided configuration.
 *
 * This function sets up the GPIO pin directions for the motor, allowing it
 * to operate based on the specified configuration settings.
 *
 * @param dcmotor Pointer to a structure of type `DCMOTOR_t` that holds the configuration settings for the DC Motor.
 */
void DCMOTOR_init(DCMOTOR_t * dcmotor);

/**
 * @brief Sets the direction of the DC Motor.
 *
 * This function changes the direction of the motor by activating the
 * appropriate pins based on the specified direction.
 *
 * @param dcmotor Pointer to the DC Motor configuration structure.
 * @param dir The direction to set for the motor (DCMOTOR_DIR_1 or DCMOTOR_DIR_2).
 */
void DCMOTOR_setDir(DCMOTOR_t * dcmotor, uint8 dir);

/**
 * @brief Stops the DC Motor.
 *
 * This function disables the motor by deactivating the control pins.
 *
 * @param dcmotor Pointer to the DC Motor configuration structure.
 */
void DCMOTOR_stop(DCMOTOR_t * dcmotor);

/**
 * @brief Sets the speed of the DC Motor.
 *
 * This function adjusts the motor speed according to the provided speed value.
 *
 * @param speed The speed value to set for the motor (typically a value between 0 and 100).
 */
//void DCMOTOR_setSpeed(uint8 speed);

#endif /* ECU_DCMOTOR_DCMOTOR_H_ */
