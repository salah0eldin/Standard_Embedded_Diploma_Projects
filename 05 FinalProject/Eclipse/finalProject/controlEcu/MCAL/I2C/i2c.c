/******************************************************************************
 *
 * Module: i2c
 *
 * File Name: i2c.c
 *
 * Description: Source file for the I2C driver.
 *
 * Created on: Oct 24, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/
#include "i2c.h"
#include "../GPIO/gpio.h"

#ifdef I2C_INTERRUPT_ENABLE
#include <avr/interrupt.h>
#endif /* I2C_INTERRUPT_ENABLE */

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

#ifdef I2C_INTERRUPT_ENABLE
/* Global pointer to the I2C interrupt handler function */
void (*I2C_interruptHandler)(void) = NULL_PTR;
#endif /* I2C_INTERRUPT_ENABLE */

/* Global variable to store I2C configuration */
I2C_t g_i2c = { .bitRateRegisterVal = 12, .prescaler = I2C_PRE_1, .selfAddress = 0x32,
    .generalCallState = I2C_GENERAL_CALL_DISABLE };

/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/

/**
 * @brief Initializes the I2C module with the given configuration.
 *
 * @param i2c Pointer to the I2C configuration structure.
 */
void I2C_init(I2C_t *i2c) {
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

/**
 * @brief Retrieves the current status of the I2C module.
 *
 * @return uint8 Status of the I2C module.
 */
uint8 I2C_getStatus(void) {
  /* Masking to keep only the status bits (TWS7:TWS3) */
  return TWSR & 0xF8;
}

/**
 * @brief Sends a START condition on the I2C bus.
 *
 * @return stdReturn Status of the START condition operation.
 */
stdReturn I2C_sendStart() {
  /* Transmit a START condition */
  TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);

  /* Wait for the start condition to be transmitted */
  while (BIT_IS_CLEAR(TWCR, TWINT)) {
  }

  /* Check the status register */
  if (I2C_getStatus() != I2C_MT_START) {
    return STD_FAIL;
  }

  return STD_SUCCESS;
}

/**
 * @brief Sends a RESTART condition on the I2C bus.
 *
 * @return stdReturn Status of the RESTART condition operation.
 */
stdReturn I2C_sendReStart(void) {
  /* Transmit a START condition */
  TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);

  /* Wait for the start condition to be transmitted */
  while (BIT_IS_CLEAR(TWCR, TWINT)) {
  }

  /* Check the status register */
  if (I2C_getStatus() != I2C_MT_RE_START) {
    return STD_FAIL;
  }

  return STD_SUCCESS;
}

/**
 * @brief Sends a STOP condition on the I2C bus.
 *
 * @return stdReturn Status of the STOP condition operation.
 */
stdReturn I2C_sendStop() {
  /* Transmit a STOP condition */
  TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);

  return STD_SUCCESS;
}

/**
 * @brief Sends a byte of data over the I2C bus.
 *
 * @param data Byte to be transmitted.
 * @return stdReturn Status of the data transmission.
 */
void I2C_sendByte(uint8 data) {
  /* Load data into the data register */
  TWDR = data;

  /* Clear the interrupt flag to start transmission */
  TWCR = (1 << TWEN) | (1 << TWINT);

  /* Wait for transmission to complete */
  while (BIT_IS_CLEAR(TWCR, TWINT)) {
  }
}

/**
 * @brief Receives a byte of data from the I2C bus.
 *
 * @param data Pointer to store the received byte.
 * @param ACK Specify if an ACK or NACK should be returned after reception.
 * @return stdReturn Status of the data reception.
 */
void I2C_receiveByte(uint8 *data, uint8 ACK) {
  /* Enable ACK if requested */
  if (ACK) {
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
  }
  else {
    TWCR = (1 << TWEN) | (1 << TWINT);
  }

  /* Wait for reception to complete */
  while (BIT_IS_CLEAR(TWCR, TWINT)) {
  }

  /* Read the received data */
  *data = TWDR;
}

#ifdef I2C_INTERRUPT_ENABLE
/*******************************************************************************
 *                       Interrupt Service Routine (ISR)                       *
 *******************************************************************************/

/**
 * @brief Sets a custom interrupt handler for I2C interrupt.
 *
 * @param i2cInterruptHandler Pointer to the interrupt handler function.
 */
void I2C_setInterruptHandler(void (*i2cInterruptHandler)(void)) {
  I2C_interruptHandler = i2cInterruptHandler;
}

/**
 * @brief Interrupt Service Routine for I2C interrupt.
 */
ISR(TWI_vect) {
  if (NULL_PTR != I2C_interruptHandler)
    (*I2C_interruptHandler)();
}
#endif /* I2C_INTERRUPT_ENABLE */
