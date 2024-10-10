/******************************************************************************
 *
 * Module: Ultra-Sonic Sensor
 *
 * File Name: ultra.c
 *
 * Description: Header file for interfacing with an ultra-sonic sensor module.
 *              This file provides function declarations for initializing the
 *              sensor, triggering distance measurement, and reading the
 *              calculated distance in centimeters. It uses timer input
 *              capture to measure the time taken by the ultra-sonic signal
 *              to reflect back.
 *
 * Created on: Oct 8, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "ultra.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/Timers/timer1.h"

#include <util/delay.h>

/*******************************************************************************
 *                             Global Variables                               *
 *******************************************************************************/

uint16 g_ultra_distanceCm = 0; /**< Global variable to store the measured distance in centimeters */
uint8 g_ultra_distance_ready = FALSE; /**< Flag to indicate if the distance measurement is ready */

static uint16 g_ultra_ticks = 0; /**< Ticks measured by Timer1 for distance calculation */
static uint8 g_interruptCount = 0; /**< Counter to track the number of interrupts */

/*******************************************************************************
 *                               Constants                                    *
 *******************************************************************************/

const float32 c_tickTimeUs = 1000000 / ((float32) F_CPU / TIMER1_PRE_SCALER); /**< Time per tick in microseconds */

/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/

/**
 * @brief Initializes the Ultra-Sonic Sensor.
 *
 * This function sets up the GPIO pins for the trigger and echo, initializes Timer1,
 * and configures the Input Capture edge.
 */
void ULTRA_init(void) {
  GPIO_setupPinDirection(ULTRA_TRIG_PORT, ULTRA_TRIG_PIN, PIN_OUTPUT); /* Set trigger pin as output */
  GPIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_INPUT); /* Set echo pin as input */

  TIMER1_init(&g_timer1); /* Initialize Timer1 */

  TIMER1_IC_EdgeSelect(TIMER1_INPUT_CAPTURE_RAISING); /* Set edge for input capture to rising */

  TIMER1_set_IC_InterruptHandler(ULTRA_edgeHandler); /* Set interrupt handler for input capture */
}

/**
 * @brief Handles the edge detection for the ultra-sonic sensor.
 *
 * This function is called on input capture interrupt to determine the distance
 * based on the time taken for the ultra-sonic pulse to return.
 */
void ULTRA_edgeHandler(void) {
  if (g_interruptCount == 0) {
    g_ultra_ticks = ICR1; /* Get the captured timer value */
    TIMER1_IC_EdgeSelect(TIMER1_INPUT_CAPTURE_FALLING); /* Set edge for input capture to falling */
    g_interruptCount = 1; /* Increment interrupt count */
  }
  else {
    g_ultra_ticks = ICR1 - g_ultra_ticks; /* Get the captured timer value */
    TIMER1_DISABLE(); /* Disable Timer1 */
    g_interruptCount = 0; /* Reset interrupt count */
    g_ultra_distance_ready = TRUE; /* Indicate that distance measurement is ready */
  }
}

/**
 * @brief Starts the ultra-sonic measurement process.
 *
 * This function triggers the ultra-sonic sensor to send out a pulse and
 * begins the distance measurement.
 *
 * @return TRUE if the measurement started successfully, FALSE otherwise.
 */
boolean ULTRA_start(void) {
  if (g_ultra_distance_ready == 0) {
    TIMER1_ENABLE(); /* Enable Timer1 */
    TIMER1_setTimerValue(0); /* Reset timer value */
    TIMER1_IC_EdgeSelect(TIMER1_INPUT_CAPTURE_RAISING); /* Set edge for input capture to rising */
    GPIO_writePin(ULTRA_TRIG_PORT, ULTRA_TRIG_PIN, LOGIC_HIGH); /* Send trigger pulse */
    _delay_us(10); /* Wait for 10 microseconds */
    GPIO_writePin(ULTRA_TRIG_PORT, ULTRA_TRIG_PIN, LOGIC_LOW); /* Stop trigger pulse */
  }
  else {
    return FALSE; /* Measurement in progress, return FALSE */
  }
  return TRUE; /* Measurement started successfully, return TRUE */
}

/**
 * @brief Reads the measured distance from the ultra-sonic sensor.
 *
 * This function calculates and returns the distance in centimeters based on
 * the ticks measured by Timer1.
 *
 * @return The distance measured in centimeters.
 */
uint16 ULTRA_readDistance(void) {
  g_ultra_distanceCm = (g_ultra_ticks + ULTRA_TICKS_ERROR_ADJUST) * c_tickTimeUs
      * ULTRA_SPEED_SOUND_DIV_2_CM_US; /* Calculate distance */
  g_ultra_distance_ready = FALSE; /* Reset the distance ready flag */
  return g_ultra_distanceCm; /* Return the measured distance */
}
