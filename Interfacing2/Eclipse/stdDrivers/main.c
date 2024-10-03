/******************************************************************************
 *
 * File Name: main.c
 *
 * Description: main file
 *
 * Created on: Sep 26, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#include "MCAL/GPIO/gpio.h"
#include "MCAL/ADC/adc.h"
#include "MCAL/Timers/timer0.h"

#include "ECU/FlameSensor/flame.h"
#include "ECU/DCMotor/dcmotor.h"
#include "ECU/Buzzer/buzzer.h"
#include "ECU/LM35/lm35.h"
#include "ECU/LCD/lcd.h"
#include "ECU/LED/led.h"
#include "ECU/LDR/ldr.h"

#include <util/delay.h>

int main (void)
{
  LED_init(&g_ledRed);
  LED_init(&g_ledGreen);
  LED_init(&g_ledBlue);

  BUZZER_init(&g_buzzer1);

  FLAME_init(&g_flameSensor1);

  LDR_init(&g_ldr1);

  LM35_init(&g_lm35_1);

  LCD_init();

  DCMOTOR_init(&g_dcmotor);

  DCMOTOR_setDir(&g_dcmotor, DCMOTOR_DIR_1);

  DCMOTOR_setSpeed(70);

  for (;;)
    {

    }
}

