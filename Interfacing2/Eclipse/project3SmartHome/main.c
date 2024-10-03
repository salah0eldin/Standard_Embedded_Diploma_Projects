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

int main(void) {

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

  uint8 temprature = 0;
  uint8 lightIntensity = 0;
  for (;;) {

    if (FLAME_isFlame(&g_flameSensor1)) {
      BUZZER_turnOn(&g_buzzer1);

      LCD_moveCursor(0, 0);
      LCD_displayString("Critical alert!     ");
      LCD_moveCursor(1, 0);
      LCD_displayString("                    ");
    }
    else {
      BUZZER_turnOff(&g_buzzer1);
      LCD_moveCursor(0, 0);
      LCD_displayString("    FAN is O");
      LCD_moveCursor(1, 0);
      LCD_displayString("Temp=");
      LCD_moveCursor(1, 8);
      LCD_displayString("LDR=");

      temprature = LM35_getTemp(&g_lm35_1);
      lightIntensity = LDR_getIntensity(&g_ldr1);

      LCD_moveCursor(1, 5);
      LCD_displayNumber(temprature);
      LCD_moveCursor(1, 12);
      LCD_displayNumber(lightIntensity);
      LCD_displayString("% ");

      LCD_moveCursor(0, 12);
      if (temprature < 25) {
	DCMOTOR_setSpeed(0);
	LCD_displayString("FF");
      }
      else {
	LCD_displayString("N ");
	if (temprature < 30) {
	  DCMOTOR_setSpeed(25);
	}
	else if (temprature < 35) {
	  DCMOTOR_setSpeed(50);
	}
	else if (temprature < 40) {
	  DCMOTOR_setSpeed(75);
	}
	else {
	  DCMOTOR_setSpeed(100);
	}
      }

      if (lightIntensity < 15) {
	LED_turnOn(&g_ledRed);
	LED_turnOn(&g_ledGreen);
	LED_turnOn(&g_ledBlue);
      }
      else if (lightIntensity < 50) {
	LED_turnOn(&g_ledRed);
	LED_turnOn(&g_ledGreen);
	LED_turnOff(&g_ledBlue);
      }
      else if (lightIntensity < 70) {
	LED_turnOn(&g_ledRed);
	LED_turnOff(&g_ledGreen);
	LED_turnOff(&g_ledBlue);
      }
      else {
	LED_turnOff(&g_ledRed);
	LED_turnOff(&g_ledGreen);
	LED_turnOff(&g_ledBlue);
      }
    }
  }
}

