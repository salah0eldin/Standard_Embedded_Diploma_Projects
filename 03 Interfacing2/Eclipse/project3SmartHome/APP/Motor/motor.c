/******************************************************************************
 *
 * Module: Motor Control
 *
 * File Name: motor.c
 *
 * Description: Implementation of the motor control module, which adjusts the
 *              speed of a DC motor based on temperature readings from an LM35
 *              temperature sensor.
 *
 * Created on: Oct 5, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "motor.h"
#include "../../ECU/DCMotor/dcmotor.h"
#include "../../ECU/LM35/lm35.h"

/*******************************************************************************
 *                                Global Variables                             *
 *******************************************************************************/

/* Global variable to store the current temperature reading */
uint8 g_temprature;

/*******************************************************************************
 *                              Function Definitions                           *
 *******************************************************************************/

/**
 * @brief Initializes the motor control system.
 *
 * This function initializes the LM35 temperature sensor and the DC motor driver.
 * It also sets the initial direction of the motor to DCMOTOR_DIR_1.
 */
void MOTOR_init(void) {
  LM35_init(&g_lm35_1);           // Initialize the LM35 temperature sensor
  DCMOTOR_init(&g_dcmotor);       // Initialize the DC motor driver
  DCMOTOR_setDir(&g_dcmotor, DCMOTOR_DIR_1); // Set the initial motor direction
}

/**
 * @brief Adjusts the motor speed based on the current temperature.
 *
 * This function reads the current temperature from the LM35 sensor and adjusts
 * the DC motor speed according to predefined temperature thresholds.
 */
void MOTOR_handleTemperature() {
  g_temprature = LM35_getTemp(&g_lm35_1); // Get the current temperature

  // Adjust the motor speed based on temperature thresholds
  if (g_temprature < TEMP_LEVEL1) {
    DCMOTOR_setSpeed(MOTOR_SPEED_LEVEL0_STOP); // Stop the motor
  }
  else if (g_temprature < TEMP_LEVEL2) {
    DCMOTOR_setSpeed(MOTOR_SPEED_LEVEL1); // Set motor speed to 25%
  }
  else if (g_temprature < TEMP_LEVEL3) {
    DCMOTOR_setSpeed(MOTOR_SPEED_LEVEL2); // Set motor speed to 50%
  }
  else if (g_temprature < TEMP_LEVEL4) {
    DCMOTOR_setSpeed(MOTOR_SPEED_LEVEL3); // Set motor speed to 75%
  }
  else {
    DCMOTOR_setSpeed(MOTOR_SPEED_LEVEL4_MAX); // Set motor speed to 100%
  }
}
