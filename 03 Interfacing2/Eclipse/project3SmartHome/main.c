/******************************************************************************
 *
 * File Name: main.c
 *
 * Description: smart home
 *
 * Created on: Sep 26, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "APP/Light/light.h"
#include "APP/Motor/motor.h"
#include "APP/Alarm/alarm.h"
#include "APP/Display/display.h"

/*******************************************************************************
 *                           Main Function                                     *
 *******************************************************************************/
int main(void) {

  /* Initialize system applications */
  LIGHT_init();
  MOTOR_init();
  ALARM_init();
  DISPLAY_init();

  /* Variable to store previous values *
   * to check if they were changed     */
  register uint8 preVal;

  for (;;) {

    /* Handle alarm, check if there is flame */
    preVal = g_flameFlag;
    ALARM_handleFlame();
    g_changeLcdView = (preVal != g_flameFlag);

    /* Handle temperature change, if temperature changed adjust motor speed */
    preVal = g_temprature;
    MOTOR_handleTemperature();
    g_changeLcdView |= (preVal != g_temprature);

    /* Handle light intensity change, if intensity changed adjust LEDs states */
    preVal = g_lightIntensity;
    LIGHT_handleIntensity();
    g_changeLcdView |= (preVal != g_lightIntensity);

    /* Handle LCD view if needed to change */
    if (TRUE == g_changeLcdView) {
      g_changeLcdView = FALSE;

      if (TRUE == g_flameFlag)
	DISPLAY_showAlarm();
      else
	DISPLAY_showNormal();
    }

  } /* Infinite for loop */
}

