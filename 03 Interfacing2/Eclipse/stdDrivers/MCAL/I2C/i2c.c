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
#include "../GPIO/gpio.h"

#ifdef I2C_INTERRUPT_ENABLE
#include <avr/interrupt.h>
#endif /* I2C_INTERRUPT_ENABLE */

#ifdef I2C_INTERRUPT_ENABLE
void (*I2C_interruptHandler)(void) = NULL_PTR;
#endif /* I2C_INTERRUPT_ENABLE */

I2C_t g_i2c = { .bitRateRegisterVal = 12, .prescaler = I2C_PRE_1, .selfAddress = 0x32,
    .generalCallState = I2C_GENERAL_CALL_DISABLE };

void I2C_init(I2C_t * i2c) {
  /* Set the prescaler (TWPS bits in TWSR) */
  TWSRbits.twps = i2c->prescaler;

  /* Set the bit rate register to control the SCL frequency */
  TWBR = i2c->bitRateRegisterVal;

  /* Set the slave address in TWAR if needed */
  if (i2c->selfAddress != 0x00) {
    TWAR = (i2c->selfAddress << 1); /* Shift left to make room for the TWA0 bit */
    if (i2c->generalCallState == I2C_GENERAL_CALL_ENABLE) {
      TWAR |= (1 << TWGCE); /* Enable general call recognition */
    }
  }

#ifdef I2C_INTERRUPT_ENABLE
  /* Enable TWI interrupt */
  TWCR = (1 << TWIE) | (1 << TWEN);
#else
  /* Enable the TWI peripheral (without interrupt) */
  TWCR = (1 << TWEN);
#endif /* I2C_INTERRUPT_ENABLE */
}

uint8 I2C_getStatus(void) {
  /* Masking to keep only the status bits (TWS7:TWS3) */
  return TWSR & 0xF8;
}

i2cReturn I2C_sendStart() {
  /* Transmit a START condition */
  TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);

  /* Wait for the start condition to be transmitted */
  while (!(TWCR & (1 << TWINT))) {
  }

  /* Check the status register */
  if (I2C_getStatus() != I2C_MT_START && I2C_getStatus() != I2C_MR_START) {
    return I2C_FAIL;
  }
  return I2C_SUCCESS;
}

i2cReturn I2C_sendStop() {
  /* Transmit a STOP condition */
  TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);

  /* Wait until stop condition is executed and TWINT is cleared */
  while (TWCR & (1 << TWSTO)) {
  }

  return I2C_SUCCESS;
}

i2cReturn I2C_sendByte(uint8 data) {
  /* Load data into the data register */
  TWDR = data;

  /* Clear the interrupt flag to start transmission */
  TWCR = (1 << TWEN) | (1 << TWINT);

  /* Wait for transmission to complete */
  while (!(TWCR & (1 << TWINT))) {
  }

  /* Check the status register */
  if (I2C_getStatus() != I2C_MT_DATA_SEND_ACK_RECEIVE) {
    return I2C_FAIL;
  }

  return I2C_SUCCESS;
}

i2cReturn I2C_receiveByte(uint8 *data, uint8 ACK) {
  /* Enable ACK if requested */
  if (ACK) {
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
  }
  else {
    TWCR = (1 << TWEN) | (1 << TWINT);
  }

  /* Wait for reception to complete */
  while (!(TWCR & (1 << TWINT))) {
  }

  /* Read the received data */
  *data = TWDR;

  /* Check the status register for ACK or NACK reception */
  if ((ACK && I2C_getStatus() != I2C_MR_DATA_RECEIVE_ACK)
      || (!ACK && I2C_getStatus() != I2C_MR_DATA_RECEIVE_NACK)) {
    return I2C_FAIL;
  }

  return I2C_SUCCESS;
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
