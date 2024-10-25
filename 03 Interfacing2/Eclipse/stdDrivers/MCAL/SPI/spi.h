/******************************************************************************
 *
 * Module: spi
 *
 * File Name: spi.h
 *
 * Description: Header file for the SPI (Serial Peripheral Interface) module.
 *              It defines the data types, constants, and function prototypes
 *              used to configure and control the SPI peripheral.
 *
 * Created on: Oct 13, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef MCAL_SPI_SPI_H_
#define MCAL_SPI_SPI_H_

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/
#include "../../std_types.h"
#include "../GPIO/gpio_registers.h"  /* For GPIO control in SPI communication */

/*******************************************************************************
 *                              Macros Definitions                             *
 *******************************************************************************/
/* Uncomment to enable SPI interrupt */
#define SPI_INTERRUPT_ENABLE

/* Macro to check if the SPI transfer is completed (by reading the SPIF flag) */
#define SPI_IS_TRANSFER_DONE()  (SPSRbits.spif)

/*******************************************************************************
 *                              Types Declarations                             *
 *******************************************************************************/

/**
 * @brief Enum representing the mode of the SPI peripheral.
 */
typedef enum {
  SPI_MODE_SLAVE,  /* SPI operates in slave mode */
  SPI_MODE_MASTER  /* SPI operates in master mode */
} SPI_mode_t;

/**
 * @brief Enum representing the data order of the SPI transmission.
 */
typedef enum {
  SPI_DATA_MSB,  /* Most Significant Bit is transmitted first */
  SPI_DATA_LSB   /* Least Significant Bit is transmitted first */
} SPI_dataOrder_t;

/**
 * @brief Enum representing the clock polarity of the SPI.
 */
typedef enum {
  SPI_CLOCK_IDLE_LOW,   /* Clock is low when idle */
  SPI_CLOCK_IDLE_HIGH   /* Clock is high when idle */
} SPI_clockPolarity_t;

/**
 * @brief Enum representing the clock phase of the SPI.
 */
typedef enum {
  SPI_SAMPLE_LEADING,   /* Sample data on the leading edge of the clock */
  SPI_SAMPLE_TRAILING   /* Sample data on the trailing edge of the clock */
} SPI_clockPhase_t;

/**
 * @brief Enum representing the clock frequency (baud rate) of the SPI.
 */
typedef enum {
  SPI_F_OSC_DIV_4,        /* SPI clock frequency = F_OSC / 4 */
  SPI_F_OSC_DIV_16,       /* SPI clock frequency = F_OSC / 16 */
  SPI_F_OSC_DIV_64,       /* SPI clock frequency = F_OSC / 64 */
  SPI_F_OSC_DIV_128,      /* SPI clock frequency = F_OSC / 128 */

  /* Double speed settings */
  SPI_F_OSC_DIV_4_2X_2,   /* SPI clock frequency = F_OSC / 2 */
  SPI_F_OSC_DIV_16_2X_8,  /* SPI clock frequency = F_OSC / 8 */
  SPI_F_OSC_DIV_64_2X_32, /* SPI clock frequency = F_OSC / 32 */
  SPI_F_OSC_DIV_128_2X_64 /* SPI clock frequency = F_OSC / 64 */
} SPI_clockFrequency_t;

/**
 * @brief Enum representing the clock speed of the SPI.
 */
typedef enum {
  SPI_SPEED_NORMAL,  /* Normal speed */
  SPI_SPEED_DOUBLE   /* Double speed */
} SPI_clockSpeed_t;

/**
 * @brief Struct representing a slave selector (for selecting a slave device).
 *        Contains port and pin information.
 */
typedef struct {
  uint8 port :2;  /* Port number (2 bits) */
  uint8 pin :3;   /* Pin number (3 bits) */
} SPI_slaveSelector_t;

/**
 * @brief Struct representing the SPI configuration parameters.
 */
typedef struct {
  uint8 mode :1;        /* SPI mode (master/slave) */
  uint8 dataOrder :1;   /* Data order (MSB/LSB first) */
  uint8 clockIdle :1;   /* Clock polarity (idle low/high) */
  uint8 sampleOn :1;    /* Clock phase (leading/trailing) */
  uint8 frequency :3;   /* Clock frequency selection */
} SPI_t;

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

/* Global SPI configuration instance */
extern SPI_t g_spi;

/* Default slave selector (configured externally) */
extern SPI_slaveSelector_t g_defaultSlave;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/**
 * @brief Initializes the SPI peripheral with the specified configuration.
 *
 * @param spi SPI_t struct containing the desired configuration settings.
 */
void SPI_init(SPI_t spi);

/**
 * @brief Deinitializes the SPI peripheral and resets the SPI settings.
 */
void SPI_deInit(void);

/**
 * @brief Initializes the slave selector to define the slave device to communicate with.
 *
 * @param slave SPI_slaveSelector_t struct specifying the slave port and pin.
 */
void SPI_initSlaveSelector(SPI_slaveSelector_t slave);

/**
 * @brief Sends and receives a byte of data in SPI master mode.
 *
 * This function selects the specified slave device, sends a byte of data,
 * and waits for the received byte from the SPI slave.
 *
 * @param slave SPI_slaveSelector_t struct specifying the selected slave device.
 * @param sData Data byte to be sent.
 * @param rData Pointer to a variable where the received byte will be stored.
 */
void SPI_masterSendReceiveByteBlocking(SPI_slaveSelector_t slave, uint8 sData, uint8 *rData);

/**
 * @brief Sends a byte of data in SPI.
 *
 * This function transmits a single byte of data through the SPI peripheral.
 *
 * @param sData Data byte to be sent through the SPI.
 */
void SPI_sendData(uint8 sData);

/**
 * @brief Receives a byte of data in SPI.
 *
 * This function receives a byte of data through the SPI peripheral.
 *
 * @param rData Pointer to a variable where the received byte will be stored.
 */
void SPI_receiveData(uint8 *rData);

#ifdef SPI_INTERRUPT_ENABLE
/**
 * @brief Sets the interrupt handler for SPI.
 *
 * This function allows the user to set a custom interrupt handler for the SPI interrupt.
 *
 * @param spiInterruptHandler Pointer to the interrupt handler function.
 */
void SPI_setInterruptHandler(void(* spiInterruptHandler)(void));
#endif


#endif /* MCAL_SPI_SPI_H_ */
