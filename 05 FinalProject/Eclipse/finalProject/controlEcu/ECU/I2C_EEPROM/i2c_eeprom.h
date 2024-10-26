/******************************************************************************
 *
 * Module: i2c_eeprom
 *
 * File Name: i2c_eeprom.h
 *
 * Description: Header file for the I2C EEPROM driver.
 *
 * Created on: Oct 25, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef ECU_I2C_EEPROM_I2C_EEPROM_H_
#define ECU_I2C_EEPROM_I2C_EEPROM_H_

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/
#include "../../LIB/std_types.h"

/*******************************************************************************
 *                          Function Prototypes                               *
 *******************************************************************************/

/**
 * @brief Initializes the I2C EEPROM module.
 */
void I2C_EEPROM_init();

/**
 * @brief Sends a byte of data to the specified EEPROM address.
 *
 * @param addr The address in the EEPROM where the data will be sent.
 * @param data The byte of data to be sent.
 * @return stdReturn Status of the operation.
 */
stdReturn I2C_EEPROM_sendByte(uint16 addr, uint8 data);

/**
 * @brief Sends multiple bytes of data to the specified EEPROM address.
 *
 * @param addr The starting address in the EEPROM.
 * @param data Pointer to the data array to be sent.
 * @param length The number of bytes to send.
 * @return stdReturn Status of the operation.
 */
stdReturn I2C_EEPROM_sendData(uint16 addr, uint8 *data, uint8 length);

/**
 * @brief Receives a byte of data from the specified EEPROM address.
 *
 * @param addr The address in the EEPROM from which the data will be received.
 * @param data Pointer to store the received byte.
 * @return stdReturn Status of the operation.
 */
stdReturn I2C_EEPROM_receiveByte(uint16 addr, uint8 *data);

/**
 * @brief Receives multiple bytes of data from the specified EEPROM address.
 *
 * @param addr The starting address in the EEPROM.
 * @param data Pointer to store the received data.
 * @param length The number of bytes to receive.
 * @return stdReturn Status of the operation.
 */
stdReturn I2C_EEPROM_receiveData(uint16 addr, uint8 *data, uint8 length);

#endif /* ECU_I2C_EEPROM_I2C_EEPROM_H_ */
