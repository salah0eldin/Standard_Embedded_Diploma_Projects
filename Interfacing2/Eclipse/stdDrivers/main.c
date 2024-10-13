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
#include "MCAL/SPI/spi.h"

int main(void) {

  SPI_init(g_spi);

  __asm__("SEI");

  uint8 rData;

  SPI_masterSendReceiveByteBlocking(g_defaultSlave, 'a', &rData);

  for (;;) {

  }
}

