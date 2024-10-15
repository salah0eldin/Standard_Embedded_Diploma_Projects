/******************************************************************************
 *
 * File Name: main.c
 *
 * Description: Main file for ultrasonic distance measurement system with LCD
 *              display and buzzer alert based on proximity.
 *
 * Created on: Sep 26, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/
#include "ECU/UltraSonic/ultra.h"
#include "ECU/Buzzer/buzzer.h"
#include "ECU/LCD/lcd.h"
#include "ECU/LED/led.h"

#include <util/delay.h>

/*******************************************************************************
 *                         Static Inline Declarations                          *
 *******************************************************************************/

static inline void DisplayDistance(void);
static inline void TriggerStopWarning(void);
static inline void AdjustLEDs(void);

/*******************************************************************************
 *                               Main Function                                 *
 *******************************************************************************/

int main(void) {
  /* Initialize all modules: Ultrasonic sensor, buzzer, LCD, and LEDs */
  ULTRA_init();
  BUZZER_init(&g_buzzer1);
  LCD_init();
  LED_init(&g_ledRed);
  LED_init(&g_ledGreen);
  LED_init(&g_ledBlue);

  /* Enable global interrupts */
  __asm__("SEI");

  /* Start ultrasonic measurement */
  ULTRA_start();

  /* Wait until the first distance measurement is ready */
  while (g_ultra_distance_ready == 0)
    ;

  /* Display static string for distance on LCD */
  LCD_displayString("Distance =   cm");

  for (;;) { /* Infinite loop */
    /* Check if a new distance measurement is ready */
    if (TRUE == g_ultra_distance_ready) {
      /* Reset the distance flag and display the new distance */
      g_ultra_distance_ready = FALSE;
      DisplayDistance();
      /* Restart ultra-sonic measurement */
      ULTRA_start();
    }

    /* If the object is closer than or equal to 5 cm, trigger stop warning */
    if (5 >= g_ultra_distanceCm) {
      TriggerStopWarning();
    }
    else {
      /* Clear the stop warning from the LCD */
      LCD_moveCursor(1, 0);
      LCD_displayString("                         ");

      /* Adjust LEDs based on the proximity distance */
      AdjustLEDs();
    }
  }
}

/*******************************************************************************
 *                         Static Inline Function Definitions                  *
 *******************************************************************************/

/*
 * Function: DisplayDistance
 * Description: Moves the LCD cursor and displays the measured distance.
 */
static inline void DisplayDistance(void) {
  LCD_moveCursor(0, 10);
  LCD_displayNumber(ULTRA_readDistance());
  LCD_displayCharacter(' ');
}

/*
 * Function: TriggerStopWarning
 * Description: Displays the stop warning message, activates the buzzer,
 *              and turns on all LEDs.
 */
static inline void TriggerStopWarning(void) {
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

/*
 * Function: AdjustLEDs
 * Description: Adjusts the LED indicators based on proximity distance
 *              to provide visual feedback.
 */
static inline void AdjustLEDs(void) {
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
