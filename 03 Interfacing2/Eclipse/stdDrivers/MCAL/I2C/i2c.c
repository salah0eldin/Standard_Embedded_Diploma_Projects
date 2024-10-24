/******************************************************************************
 *
 * Module: i2c
 *
 * File Name: i2c.c
 *
 * Description: 
 *
 * Created on: Oct 24, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#include "i2c.h"

#ifdef I2C_INTERRUPT_ENABLE
#include <avr/interrupt.h>
#endif /* I2C_INTERRUPT_ENABLE */

#ifdef I2C_INTERRUPT_ENABLE
void (*I2C_interruptHandler)(void) = NULL_PTR;
#endif /* I2C_INTERRUPT_ENABLE */

I2C_t g_i2c = { .bitRateRegisterVal = 12, .prescaler = I2C_PRE_1, .selfAddress = 0x32,
    .generalCallState = I2C_GENERAL_CALL_DISABLE };

void I2C_init(I2C_t g_i2c) {

}

uint8 I2C_sendByte(uint8 data) {

}

uint8 I2C_receiveByte(uint8 *data) {

}

#ifdef I2C_INTERRUPT_ENABLE
void I2C_setInterruptHandler(void (*i2cInterruptHandler)(void)) {
  I2C_interruptHandler = i2cInterruptHandler;
}
#endif /* I2C_INTERRUPT_ENABLE */

#ifdef I2C_INTERRUPT_ENABLE
ISR(TWI_vect) {
  if (NULL_PTR != I2C_interruptHandler)
    (*I2C_interruptHandler)();
}
#endif /* I2C_INTERRUPT_ENABLE */
