/******************************************************************************
 *
 * Module: H-Bridge DC Motors
 *
 * File Name: dcmotor.c
 *
 * Description: Source file for the H-Bridge DC Motor driver implementation.
 *
 * Created on: Oct 3, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "dcmotor.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/Timers/timer0.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
DCMOTOR_t g_dcmotor = { .dirPort = PORTB_ID, .dirPin1 = PIN0_ID, .dirPin2 = PIN1_ID, .enableEn = 1,
    .enPort = PORTB_ID, .enPin = PIN3_ID };

/*******************************************************************************
 *                              Function Definitions                           *
 *******************************************************************************/

/**
 * @brief Initializes the DC Motor according to the provided configuration.
 *
 * This function sets up the GPIO pin directions for the motor control pins,
 * allowing the motor to operate based on the specified configuration settings.
 *
 * @param dcmotor Pointer to a structure of type `DCMOTOR_t` that holds the configuration settings for the DC Motor.
 */
void DCMOTOR_init(DCMOTOR_t *dcmotor) {
  // Set the direction for the motor control pins
  GPIO_setupPinDirection(dcmotor->dirPort, dcmotor->dirPin1, PIN_OUTPUT);
  GPIO_setupPinDirection(dcmotor->dirPort, dcmotor->dirPin2, PIN_OUTPUT);

  // If enabled, set the enable pin direction
  if (dcmotor->enableEn)
    GPIO_setupPinDirection(dcmotor->enPort, dcmotor->enPin, PIN_OUTPUT);

  // Initialize the Timer for PWM control
  TIMER0_init(&g_timer0);
}

/**
 * @brief Sets the direction of the DC Motor.
 *
 * This function changes the motor direction by activating the appropriate control pins.
 *
 * @param dcmotor Pointer to the DC Motor configuration structure.
 * @param dir The direction to set for the motor (DCMOTOR_DIR_1 or DCMOTOR_DIR_2).
 */
void DCMOTOR_setDir(DCMOTOR_t *dcmotor, uint8 dir) {
  // Set the direction pins based on the specified direction
  GPIO_writePin(dcmotor->dirPort, dcmotor->dirPin1, dir);
  GPIO_writePin(dcmotor->dirPort, dcmotor->dirPin2, !dir); // Corrected: should write to dirPin2
}

/**
 * @brief Stops the DC Motor.
 *
 * This function disables the motor by setting both control pins to low.
 *
 * @param dcmotor Pointer to the DC Motor configuration structure.
 */
void DCMOTOR_stop(DCMOTOR_t *dcmotor) {
  // Set both direction pins low to stop the motor
  GPIO_writePin(dcmotor->dirPort, dcmotor->dirPin1, LOGIC_LOW);
  GPIO_writePin(dcmotor->dirPort, dcmotor->dirPin2, LOGIC_LOW); // Corrected: should write to dirPin2
}

/**
 * @brief Sets the speed of the DC Motor.
 *
 * This function adjusts the motor speed according to the provided speed value.
 * The speed is set using PWM via Timer0.
 *
 * @param speed The speed value to set for the motor (typically a value between 0 and 100).
 */
void DCMOTOR_setSpeed(uint8 speed) {
  // Set the duty cycle for the Timer to control the motor speed
  TIMER0_setDutyCycle(speed);
}
