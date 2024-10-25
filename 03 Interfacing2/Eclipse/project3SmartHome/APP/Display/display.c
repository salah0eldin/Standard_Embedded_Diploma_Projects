/******************************************************************************
 *
 * Module: Display
 *
 * File Name: display.c
 *
 * Description: Source file for the display module responsible for handling the
 *              display of alarm and normal operation states on the LCD.
 *
 * Created on: Oct 5, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "display.h"
#include "../../ECU/LCD/lcd.h"

#include "../Motor/motor.h"
#include "../Light/light.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
uint8 g_changeLcdView = TRUE;

/*******************************************************************************
 *                              Functions Definition                           *
 *******************************************************************************/

/**
 * @brief Initializes the display by setting up the LCD.
 *
 * This function sets up the LCD for use by calling the LCD initialization function.
 */
void DISPLAY_init(void) {
  /* Initialize the LCD hardware module */
  LCD_init();
}

/**
 * @brief Displays an alarm message on the LCD.
 *
 * This function clears the LCD screen and displays a "Critical alert!" message
 * to indicate that an alarm condition has occurred.
 */
void DISPLAY_showAlarm(void) {
  /* Clear the screen and display a critical alert message */
  LCD_clearScreen();
  LCD_displayString("Critical alert!");
}

/**
 * @brief Displays the normal operation status on the LCD.
 *
 * This function shows the current fan status (ON or OFF), temperature, and light
 * intensity on the LCD in normal operation mode.
 */
void DISPLAY_showNormal(void) {
  /* Display motor status based on temperature */
  LCD_moveCursor(LCD_FIRST_ROW, LCD_FIRST_COL);
  /* Check temperature level and display appropriate status */
  if (g_temprature < TEMP_LEVEL1) {
    LCD_displayString("    FAN is OFF    ");
  } else {
    LCD_displayString("    FAN is ON     ");
  }

  /* Display the temperature and light intensity on the second row */
  LCD_moveCursor(LCD_SECOND_ROW, LCD_FIRST_COL);
  LCD_displayString("Temp=");
  LCD_displayNumber(g_temprature); /* Display the temperature value */

  LCD_displayString(" LDR=");
  LCD_displayNumber(g_lightIntensity); /* Display the light intensity value */
  LCD_displayString("% "); /* Add percentage symbol for light intensity */
}
