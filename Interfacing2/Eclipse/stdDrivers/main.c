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

int main(void) {

  USART_init(&g_usart);

/*  __asm__("SEI");*/

  for (;;) {
    USART_sendStringBlocking("Hello USART !!\r");
    _delay_ms(500);
  }
}

