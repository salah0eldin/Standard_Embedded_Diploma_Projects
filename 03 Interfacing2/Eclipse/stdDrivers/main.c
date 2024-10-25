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
#include "ECU/LCD/lcd.h"
#include "MCAL/I2C/i2c.h"

const uint8 keypadKeys[] = { '7', '8', '9', '4', '5', '6', '1', '2', '3', ' ', '0', 13 };

int main(void) {

  I2C_init(&g_i2c);

  __asm__("SEI");

  for (;;) {
    _delay_ms(1000);
    I2C_sendByte('1');
  }
}

