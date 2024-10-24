 /******************************************************************************
 *
 * Module: i2c
 *
 * File Name: i2c.h
 *
 * Description: 
 *
 * Created on: Oct 24, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef MCAL_I2C_I2C_H_
#define MCAL_I2C_I2C_H_

#include "../../std_types.h"

#define I2C_INTERRUPT_ENABLE

typedef enum{
  I2C_MT_START = 0x08,                  /* A START condition has been transmitted                     */
  I2C_MT_RE_START = 0x10,               /* A repeated START condition has been transmitted            */
  I2C_MT_ACK_RECEIVE = 0x18,            /* SLA+W has been transmitted & ACK has been received         */
  I2C_MT_NACK_RECEIVE = 0x20,           /* SLA+W has been transmitted & NOT ACK has been received     */
  I2C_MT_DATA_SEND_ACK_RECEIVE = 0x28,  /* Data byte has been transmitted & ACK has been received     */
  I2C_MT_DATA_SEND_NACK_RECEIVE = 0x30, /* Data byte has been transmitted & NOT ACK has been received */
  I2C_MT_LOST_ARBITRATION = 0x38,       /* Arbitration lost in SLA+W or data bytes                    */
} I2C_statusMasterTransmit;

typedef enum{
  I2C_MR_START = 0x08,                  /* A START condition has been transmitted                     */
  I2C_MR_RE_START = 0x10,               /* A repeated START condition has been transmitted            */
  I2C_MR_SLA_R_ACK = 0x40,              /* SLA+R has been transmitted & ACK received                  */
  I2C_MR_SLA_R_NACK = 0x48,             /* SLA+R has been transmitted & NOT ACK received              */
  I2C_MR_DATA_RECEIVE_ACK = 0x50,       /* Data byte has been received & ACK has been returned        */
  I2C_MR_DATA_RECEIVE_NACK = 0x58,      /* Data byte has been received & NOT ACK has been returned    */
  I2C_MR_LOST_ARBITRATION = 0x38        /* Arbitration lost in SLA+R or data bytes                    */
} I2C_statusMasterReceive;


/*
 * Formula to calculate the I2C SCL (Serial Clock Line) frequency:
 *
 *                CPU Clock Frequency
 * SCL = -----------------------------------
 *       	16 + (2 * TWBR * 4^TWPS)
 *
 * Where:
 * - SCL: The desired I2C clock frequency.
 * - CPU Clock Frequency: The clock frequency of the microcontroller.
 * - TWBR: The value in the TWI Bit Rate Register.
 * - TWPS: The prescaler value determined by the TWI Status Register (TWSR).
 *
 * Note:
 * - TWPS can be 1, 4, or 16 depending on the prescaler bits (TWPS1 and TWPS0).
 * - Adjust TWBR and TWPS to set the appropriate I2C speed.
 */

typedef enum{
  I2C_FAIL,
  I2C_SUCCESS
} I2C_returnStatus;

typedef enum{
  I2C_PRE_1,
  I2C_PRE_4,
  I2C_PRE_16,
  I2C_PRE_64
} I2C_prescaler;

typedef enum{
  I2C_GENERAL_CALL_DISABLE,
  I2C_GENERAL_CALL_ENABLE
} I2C_generalCall;

typedef struct{
  uint8 bitRateRegisterVal;
  uint8 prescaler;
  uint8 selfAddress;
  uint8 generalCallState;
} I2C_t;

extern I2C_t g_i2c;

void I2C_init(I2C_t g_i2c);

uint8 I2C_sendByte(uint8 data);

uint8 I2C_receiveByte(uint8 *data);

#ifdef I2C_INTERRUPT_ENABLE
void I2C_setInterruptHandler(void(*i2cInterruptHandler)(void));
#endif /* I2C_INTERRUPT_ENABLE */

#endif /* MCAL_I2C_I2C_H_ */