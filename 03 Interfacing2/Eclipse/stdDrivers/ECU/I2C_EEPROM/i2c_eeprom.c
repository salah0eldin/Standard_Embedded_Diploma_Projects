/******************************************************************************
 *
 * Module: i2c_eeprom
 *
 * File Name: i2c_eeprom.c
 *
 * Description: I2C EEPROM driver implementation.
 *
 * Created on: Oct 25, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/
#include "i2c_eeprom.h"
#include "../../MCAL/I2C/i2c.h"

/*******************************************************************************
 *                              Static Function Prototypes                     *
 *******************************************************************************/

/**
 * @brief Sends the EEPROM address for read/write operations.
 *
 * @param addr The address in the EEPROM.
 * @return stdReturn Status of the operation.
 */
static inline stdReturn I2C_EEPROM_sendAddress(uint16 addr);

/**
 * @brief Sends a read request for the specified EEPROM address.
 *
 * @param addr The address in the EEPROM.
 * @return stdReturn Status of the operation.
 */
static inline stdReturn I2C_EEPROM_receiveRequist(uint16 addr);

/*******************************************************************************
 *                              Global Functions                                *
 *******************************************************************************/

/**
 * @brief Initializes the I2C EEPROM module.
 */
void I2C_EEPROM_init() {
  /* Initialize the I2C module with the global configuration */
  I2C_init(&g_i2c);
}

/**
 * @brief Sends a byte of data to the specified EEPROM address.
 *
 * @param addr The address in the EEPROM where the data will be sent.
 * @param data The byte of data to be sent.
 * @return stdReturn Status of the operation.
 */
stdReturn I2C_EEPROM_sendByte(uint16 addr, uint8 data) {
  stdReturn ret = STD_SUCCESS;

  /* Send the address where the byte will be written */
  ret &= I2C_EEPROM_sendAddress(addr);
  if (STD_FAIL == ret)
    return ret; /* Return if address sending fails */

  /* Send the byte to the EEPROM */
  I2C_sendByte(data);
  /* Check if the data was acknowledged */
  if (I2C_MT_DATA_SEND_ACK_RECEIVE != I2C_getStatus())
    return STD_FAIL; /* Return if not acknowledged */

  /* Send stop condition */
  ret &= I2C_sendStop();

  return ret; /* Return the status of the operation */
}

/**
 * @brief Sends multiple bytes of data to the specified EEPROM address.
 *
 * @param addr The starting address in the EEPROM.
 * @param data Pointer to the data array to be sent.
 * @param length The number of bytes to send.
 * @return stdReturn Status of the operation.
 */
stdReturn I2C_EEPROM_sendData(uint16 addr, uint8 *data, uint8 length) {
  stdReturn ret = STD_SUCCESS;

  /* Send the starting address for data transmission */
  ret &= I2C_EEPROM_sendAddress(addr);
  if (STD_FAIL == ret)
    return ret; /* Return if address sending fails */

  /* Send each byte in the data array */
  for (uint8 i = 0; i < length; i++) {
    I2C_sendByte(*(data + i));
    /* Check if each byte was acknowledged */
    if (I2C_MT_DATA_SEND_ACK_RECEIVE != I2C_getStatus())
      return STD_FAIL; /* Return if any byte is not acknowledged */
  }

  /* Send stop condition */
  ret &= I2C_sendStop();

  return ret; /* Return the status of the operation */
}

/**
 * @brief Receives a byte of data from the specified EEPROM address.
 *
 * @param addr The address in the EEPROM from which the data will be received.
 * @param data Pointer to store the received byte.
 * @return stdReturn Status of the operation.
 */
stdReturn I2C_EEPROM_receiveByte(uint16 addr, uint8 *data) {
  stdReturn ret = STD_SUCCESS;

  /* Send the address from which to read */
  ret &= I2C_EEPROM_sendAddress(addr);
  if (STD_FAIL == ret)
    return ret; /* Return if address sending fails */

  /* Request the byte to be read */
  ret &= I2C_EEPROM_receiveRequist(addr);
  if (STD_FAIL == ret)
    return ret; /* Return if read request fails */

  /* Read the byte from the EEPROM */
  I2C_receiveByte(data, I2C_N_ACK);
  /* Check if the data was acknowledged */
  if (I2C_MR_DATA_RECEIVE_NACK != I2C_getStatus())
    return STD_FAIL; /* Return if not acknowledged */

  /* Send stop condition */
  ret &= I2C_sendStop();

  return ret; /* Return the status of the operation */
}

/**
 * @brief Receives multiple bytes of data from the specified EEPROM address.
 *
 * @param addr The starting address in the EEPROM.
 * @param data Pointer to store the received data.
 * @param length The number of bytes to receive.
 * @return stdReturn Status of the operation.
 */
stdReturn I2C_EEPROM_receiveData(uint16 addr, uint8 *data, uint8 length) {
  stdReturn ret = STD_SUCCESS;

  /* Send the starting address for data reception */
  ret &= I2C_EEPROM_sendAddress(addr);
  if (STD_FAIL == ret)
    return ret; /* Return if address sending fails */

  /* Request the bytes to be read */
  ret &= I2C_EEPROM_receiveRequist(addr);
  if (STD_FAIL == ret)
    return ret; /* Return if read request fails */

  /* Read bytes, acknowledging all but the last */
  for (uint8 i = 0; i < length - 1; i++) {
    I2C_receiveByte(data + i, I2C_ACK);
    /* Check if each byte was acknowledged */
    if (I2C_MR_DATA_RECEIVE_ACK != I2C_getStatus())
      return STD_FAIL; /* Return if any byte is not acknowledged */
  }

  /* Read the last byte without acknowledging */
  I2C_receiveByte(data + length - 1, I2C_N_ACK);
  /* Check if the last byte was acknowledged */
  if (I2C_MR_DATA_RECEIVE_NACK != I2C_getStatus())
    return STD_FAIL; /* Return if not acknowledged */

  /* Send stop condition */
  ret &= I2C_sendStop();

  return ret; /* Return the status of the operation */
}

/*******************************************************************************
 *                          Static Function Implementations                    *
 *******************************************************************************/

/**
 * @brief Sends the EEPROM address for read/write operations.
 *
 * This function sends the start condition and the EEPROM address to the device,
 * along with the read/write bit.
 *
 * @param addr The address in the EEPROM.
 * @return stdReturn Status of the operation.
 */
static inline stdReturn I2C_EEPROM_sendAddress(uint16 addr) {
  stdReturn ret = STD_SUCCESS;

  /* Send start condition */
  ret &= I2C_sendStart();
  if (STD_FAIL == ret)
    return ret; /* Return if start condition fails */

  /* Send the EEPROM address with the write bit */
  I2C_sendByte((uint8) (0xA0 | ((addr & 0x0700) >> 7)));
  /* Check if the address was acknowledged */
  if (I2C_MT_SLA_W_ACK != I2C_getStatus())
    return STD_FAIL; /* Return if not acknowledged */

  /* Send the actual address */
  I2C_sendByte((uint8) addr);
  /* Check if the address was acknowledged */
  if (I2C_MT_DATA_SEND_ACK_RECEIVE != I2C_getStatus())
    return STD_FAIL; /* Return if not acknowledged */

  return ret; /* Return the status of the operation */
}

/**
 * @brief Sends a read request for the specified EEPROM address.
 *
 * This function sends a repeated start condition and the EEPROM address with
 * the read bit.
 *
 * @param addr The address in the EEPROM.
 * @return stdReturn Status of the operation.
 */
static inline stdReturn I2C_EEPROM_receiveRequist(uint16 addr) {
  stdReturn ret = STD_SUCCESS;

  /* Send repeated start condition */
  ret &= I2C_sendReStart();
  if (STD_FAIL == ret)
    return ret; /* Return if repeated start fails */

  /* Send the EEPROM address with the read bit */
  I2C_sendByte((uint8) (0xA0 | ((addr & 0x0700) >> 7)) | 1);
  /* Check if the address was acknowledged */
  if (I2C_MR_SLA_R_ACK != I2C_getStatus())
    return STD_FAIL; /* Return if not acknowledged */

  return ret; /* Return the status of the operation */
}
