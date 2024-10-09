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

#include "ECU/UltraSonic/ultra.h"
#include "ECU/Buzzer/buzzer.h"
#include "ECU/LCD/lcd.h"
#include "ECU/LED/led.h"

#include <util/delay.h>

int main(void) {
  ULTRA_init();

  BUZZER_init(&g_buzzer1);

  LCD_init();

  LED_init(&g_ledRed);
  LED_init(&g_ledGreen);
  LED_init(&g_ledBlue);

  __asm__("SEI");

  ULTRA_start();
  while(g_ultra_distance_ready == 0);

  LCD_displayString("Distance =   cm");
  for (;;) {
    if (TRUE == g_ultra_distance_ready) {
      g_ultra_distance_ready = FALSE;

      LCD_moveCursor(0, 10);
      LCD_displayNumber(ULTRA_readDistance());
      LCD_displayCharacter(' ');
      ULTRA_start();

      }

      if (5 >= g_ultra_distanceCm) {
	LCD_moveCursor(1, 0);
	LCD_displayString("      STOP      ");
	BUZZER_turnOn(&g_buzzer1);
	LED_turnOn(&g_ledRed);
	LED_turnOn(&g_ledGreen);
	LED_turnOn(&g_ledBlue);
	_delay_ms(250);
	BUZZER_turnOff(&g_buzzer1);
	LED_turnOff(&g_ledRed);
	LED_turnOff(&g_ledGreen);
	LED_turnOff(&g_ledBlue);
	_delay_ms(250);
      }
      else {
	LCD_moveCursor(1, 0);
	LCD_displayString("                         ");
	if (10 >= g_ultra_distanceCm) {
	  LED_turnOn(&g_ledRed);
	  LED_turnOn(&g_ledGreen);
	  LED_turnOn(&g_ledBlue);
	}
	else if (15 >= g_ultra_distanceCm) {
	  LED_turnOn(&g_ledRed);
	  LED_turnOn(&g_ledGreen);
	  LED_turnOff(&g_ledBlue);
	}
	else if (20 >= g_ultra_distanceCm) {
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

