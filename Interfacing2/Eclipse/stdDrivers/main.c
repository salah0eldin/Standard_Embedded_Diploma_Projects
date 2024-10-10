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

  __asm__("SEI");


    uint8 dataR = 0;
    uint8 strData[5] = {0};
  for (;;) {

    USART_recieveStringBlocking(strData, 4);
    _delay_ms(500);
    USART_sendCharBlocking('\r');
    USART_sendStringBlocking(strData);
    _delay_ms(500);
  }
}

