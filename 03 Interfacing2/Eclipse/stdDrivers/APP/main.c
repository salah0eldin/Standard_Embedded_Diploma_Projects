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
#include "../ECU/LCD/lcd.h"
#include "../MCAL/I2C/i2c.h"

#include "../ECU/I2C_EEPROM/i2c_eeprom.h"

//const uint8 keypadKeys[] = { '7', '8', '9', '4', '5', '6', '1', '2', '3', ' ', '0', 13 };

int main(void) {

  I2C_EEPROM_init();

  __asm__("SEI");
  uint8 data[] = {0x12,0x23,0x44};
  uint8 rdata[3];
  _delay_ms(10);
  I2C_EEPROM_sendData(0x40,data, 3);
  _delay_ms(10);
  I2C_EEPROM_receiveData(0x40,rdata,3);

  for (;;) {

  }
}

