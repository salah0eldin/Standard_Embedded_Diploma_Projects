/******************************************************************************
 *
 * Module: Light
 *
 * File Name: light.c
 *
 * Description: Source file for the light module responsible for handling light
 *              intensity measurements and controlling LEDs based on intensity levels.
 *
 * Created on: Oct 5, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "light.h"
#include "../../ECU/LED/led.h"
#include "../../ECU/LDR/ldr.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

/* Global variable to store the current light intensity */
uint8 g_lightIntensity;

/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/

/**
 * @brief Initializes the light sensor and the associated LEDs.
 *
 * This function sets up the LEDs and the light sensor (LDR) to start measuring
 * light intensity and adjusting LED states accordingly.
 */
void LIGHT_init(void) {
  /* Initialize the red LED */
  LED_init(&g_ledRed);
  /* Initialize the green LED */
  LED_init(&g_ledGreen);
  /* Initialize the blue LED */
  LED_init(&g_ledBlue);

  /* Initialize the LDR (light sensor) */
  LDR_init(&g_ldr1);
}

/**
 * @brief Handles light intensity changes and controls the LEDs.
 *
 * This function reads the current light intensity from the light sensor (LDR),
 * and based on predefined thresholds, it adjusts the state of the LEDs.
 */
void LIGHT_handleIntensity(void) {

  /* Get the current light intensity from the LDR */
  g_lightIntensity = LDR_getIntensity(&g_ldr1);

  /* Check if light intensity is below the first threshold (LIGHT_LEVEL1) */
  if (g_lightIntensity < LIGHT_LEVEL1) {
    /* If it's dark (low intensity), turn on all LEDs (Red, Green, Blue) */
    LED_turnOn(&g_ledRed);
    LED_turnOn(&g_ledGreen);
    LED_turnOn(&g_ledBlue);
  }
  /* Check if light intensity is between the first and second thresholds */
  else if (g_lightIntensity < LIGHT_LEVEL2) {
    /* Turn on Red and Green LEDs, turn off Blue LED */
    LED_turnOn(&g_ledRed);
    LED_turnOn(&g_ledGreen);
    LED_turnOff(&g_ledBlue);
  }
  /* Check if light intensity is between the second and third thresholds */
  else if (g_lightIntensity < LIGHT_LEVEL3) {
    /* Turn on Red LED, turn off Green and Blue LEDs */
    LED_turnOn(&g_ledRed);
    LED_turnOff(&g_ledGreen);
    LED_turnOff(&g_ledBlue);
  }
  /* If light intensity is above the third threshold (very bright) */
  else {
    /* Turn off all LEDs (Red, Green, Blue) */
    LED_turnOff(&g_ledRed);
    LED_turnOff(&g_ledGreen);
    LED_turnOff(&g_ledBlue);
  }
}
