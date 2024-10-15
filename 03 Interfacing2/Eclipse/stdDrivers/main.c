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

#include <util/delay.h>
#include "MCAL/USART/usart.h"
#include "ECU/Button/button.h"
#include "ECU/LCD/lcd.h"

int main(void) {

  USART_init(&g_usart);
  BUTTON_init(&g_button1);
  LCD_init();
  uint8 flag = 0;
  uint8 data = '1';

  __asm__("SEI");

  for (;;) {
    if (BUTTON_getState(&g_button1) == BUTTON_PRESSED) {
      /* De-bouncing */
      _delay_ms(30);

      if (BUTTON_getState(&g_button1) == BUTTON_PRESSED) {

	if (flag == 0) {
	  flag = 1;

	  USART_receiveCharNonBlocking(&data);

	  LCD_displayCharacter(data);
	}
      }
    }
    else {
      flag = 0;
    }
  }
}

