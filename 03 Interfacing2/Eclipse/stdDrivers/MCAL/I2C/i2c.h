/******************************************************************************
 *
 * Module: I2C (Inter-Integrated Circuit)
 *
 * File Name: i2c.h
 *
 * Description: Header file for the I2C driver for communication in master-slave mode.
 *              Defines various status codes, configurations, and functions used
 *              for initiating I2C communication, sending/receiving data, and handling
 *              interrupts.
 *
 * Created on: Oct 24, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef MCAL_I2C_I2C_H_
#define MCAL_I2C_I2C_H_

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/
#include "../../LIB/std_types.h"

/*******************************************************************************
 *                              Macros                                         *
 *******************************************************************************/
/* Uncomment to enable I2C interrupt functionality */
//#define I2C_INTERRUPT_ENABLE

/*******************************************************************************
 *                              Enums                                          *
 *******************************************************************************/
/* I2C Master Transmitter Status Codes */
typedef enum{
  I2C_MT_START = 0x08,                  /* A START condition has been transmitted                     */
  I2C_MT_RE_START = 0x10,               /* A repeated START condition has been transmitted            */
  I2C_MT_SLA_W_ACK = 0x18,    		/* SLA+W has been transmitted & ACK has been received         */
  I2C_MT_SLA_W_NACK = 0x20,     	/* SLA+W has been transmitted & NOT ACK has been received     */
  I2C_MT_DATA_SEND_ACK_RECEIVE = 0x28,  /* Data byte has been transmitted & ACK has been received     */
  I2C_MT_DATA_SEND_NACK_RECEIVE = 0x30, /* Data byte has been transmitted & NOT ACK has been received */
  I2C_MT_LOST_ARBITRATION = 0x38,       /* Arbitration lost in SLA+W or data bytes                    */
} I2C_statusMasterTransmit;

/* I2C Master Receiver Status Codes */
typedef enum{
  I2C_MR_START = 0x08,                  /* A START condition has been transmitted                     */
  I2C_MR_RE_START = 0x10,               /* A repeated START condition has been transmitted            */
  I2C_MR_SLA_R_ACK = 0x40,              /* SLA+R has been transmitted & ACK received                  */
  I2C_MR_SLA_R_NACK = 0x48,             /* SLA+R has been transmitted & NOT ACK received              */
  I2C_MR_DATA_RECEIVE_ACK = 0x50,       /* Data byte has been received & ACK has been returned        */
  I2C_MR_DATA_RECEIVE_NACK = 0x58,      /* Data byte has been received & NOT ACK has been returned    */
  I2C_MR_LOST_ARBITRATION = 0x38        /* Arbitration lost in SLA+R or data bytes                    */
} I2C_statusMasterReceive;

/* I2C Slave Receiver Status Codes */
typedef enum{
  I2C_SR_SLA_W_RECEIVE_ACK = 0x60,    	/* Own SLA+W has been received & ACK returned                 */
  I2C_SR_ARB_LOST_SLA_W_ACK = 0x68,   	/* Arbitration lost, own SLA+W received & ACK returned        */
  I2C_SR_GCALL_RECEIVE_ACK = 0x70,    	/* General call address received & ACK returned               */
  I2C_SR_ARB_LOST_GCALL_ACK = 0x78,   	/* Arbitration lost, general call received & ACK returned     */
  I2C_SR_DATA_RECEIVE_ACK = 0x80,     	/* Data byte received & ACK returned                          */
  I2C_SR_DATA_RECEIVE_NACK = 0x88,    	/* Data byte received & NOT ACK returned                      */
  I2C_SR_GCALL_DATA_RECEIVE_ACK = 0x90,	/* Data byte after general call & ACK returned                */
  I2C_SR_GCALL_DATA_RECEIVE_NACK = 0x98,/* Data byte after general call & NOT ACK returned            */
  I2C_SR_STOP_REPEATED_START = 0xA0   	/* STOP or repeated START condition received while addressed  */
} I2C_statusSlaveReceive;

/* I2C Slave Transmitter Status Codes */
typedef enum{
  I2C_ST_SLA_R_RECEIVE_ACK = 0xA8,    	  /* Own SLA+R received & ACK returned                      */
  I2C_ST_ARB_LOST_SLA_R_ACK = 0xB0,   	  /* Arbitration lost, own SLA+R received & ACK returned    */
  I2C_ST_DATA_SEND_ACK_RECEIVE = 0xB8,	  /* Data byte transmitted & ACK received                   */
  I2C_ST_DATA_SEND_NACK_RECEIVE = 0xC0,	  /* Data byte transmitted & NOT ACK received               */
  I2C_ST_LAST_DATA_SEND_ACK_RECEIVE = 0xC /* Last data byte transmitted (TWEA = 0) & ACK received    */
} I2C_statusSlaveTransmit;

/*******************************************************************************
 *                              Formula                                        *
 *******************************************************************************/
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

/*******************************************************************************
 *                              Enums (continued)                              *
 *******************************************************************************/
typedef enum{
  I2C_PRE_1,        /* Prescaler value 1 */
  I2C_PRE_4,        /* Prescaler value 4 */
  I2C_PRE_16,       /* Prescaler value 16 */
  I2C_PRE_64        /* Prescaler value 64 */
} I2C_prescaler;

typedef enum{
  I2C_GENERAL_CALL_DISABLE, /* Disable general call recognition */
  I2C_GENERAL_CALL_ENABLE   /* Enable general call recognition  */
} I2C_generalCall;

typedef enum{
  I2C_N_ACK,        /* No acknowledgment */
  I2C_ACK           /* Acknowledgment received */
} I2C_ACKReceiver;


/*******************************************************************************
 *                              Structures                                     *
 *******************************************************************************/
typedef struct{
  uint8 bitRateRegisterVal; /* Value to set in the TWI Bit Rate Register */
  uint8 prescaler;          /* Prescaler value (1, 4, 16, 64) */
  uint8 selfAddress;        /* Slave address of the device */
  uint8 generalCallState;   /* General call state (enable/disable) */
} I2C_t;

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
extern I2C_t g_i2c;

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/
/**
 * @brief Initializes the I2C module with the given configuration.
 *
 * @param i2c Pointer to the I2C configuration structure.
 */
void I2C_init(I2C_t * i2c);

/**
 * @brief Retrieves the current status of the I2C module.
 *
 * @return uint8 Status of the I2C module.
 */
uint8 I2C_getStatus(void);

/**
 * @brief Sends a START condition on the I2C bus.
 *
 * @return stdReturn Status of the START condition operation.
 */
stdReturn I2C_sendStart(void);

/**
 * @brief Sends a RESTART condition on the I2C bus.
 *
 * @return stdReturn Status of the RESTART condition operation.
 */
stdReturn I2C_sendReStart(void);

/**
 * @brief Sends a STOP condition on the I2C bus.
 *
 * @return stdReturn Status of the STOP condition operation.
 */
stdReturn I2C_sendStop(void);

/**
 * @brief Sends a byte of data over the I2C bus.
 *
 * @param data Byte to be transmitted.
 * @return stdReturn Status of the data transmission.
 */
void I2C_sendByte(uint8 data);

/**
 * @brief Receives a byte of data from the I2C bus.
 *
 * @param data Pointer to store the received byte.
 * @param ACK Specify if an ACK or NACK should be returned after reception.
 * @return stdReturn Status of the data reception.
 */
void I2C_receiveByte(uint8 *data, uint8 ACK);

#ifdef I2C_INTERRUPT_ENABLE
/**
 * @brief Sets a custom interrupt handler for I2C interrupt.
 *
 * @param i2cInterruptHandler Pointer to the interrupt handler function.
 */
void I2C_setInterruptHandler(void(*i2cInterruptHandler)(void));
#endif /* I2C_INTERRUPT_ENABLE */


#endif /* MCAL_I2C_I2C_H_ */
