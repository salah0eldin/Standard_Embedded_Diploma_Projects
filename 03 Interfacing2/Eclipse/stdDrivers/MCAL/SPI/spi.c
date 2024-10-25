/******************************************************************************
 *
 * Module: spi
 *
 * File Name: spi.c
 *
 * Description: Source file for the SPI (Serial Peripheral Interface) module.
 *              It contains the implementation of SPI initialization, data
 *              transfer, and de-initialization functions.
 *
 * Created on: Oct 13, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/
#include "spi.h"
#include "../GPIO/gpio.h"  /* For GPIO control in SPI communication */
#include <avr/interrupt.h>

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

/* Default SPI configuration set to Master mode, MSB first, idle low clock,
 * sample on leading edge, and clock frequency F_OSC / 2.
 */
SPI_t g_spi = { .mode = SPI_MODE_MASTER, .dataOrder = SPI_DATA_MSB, .clockIdle = SPI_CLOCK_IDLE_LOW,
    .sampleOn = SPI_SAMPLE_LEADING, .frequency = SPI_F_OSC_DIV_4_2X_2 };

/* Default slave selector configured for PORTB Pin 4 (used for SS - Slave Select) */
SPI_slaveSelector_t g_defaultSlave = { .port = PORTB_ID, .pin = PIN4_ID };

#ifdef SPI_INTERRUPT_ENABLE
/**
 * @brief Pointer to the SPI interrupt handler function.
 *
 * This static pointer holds the address of a user-defined function
 * called upon SPI interrupt. Initialized to NULL_PTR by default.
 */
static void (*SPI_interruptHandler)(void) = NULL_PTR;
#endif


/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/

/**
 * @brief Initializes the SPI module with the given configuration.
 *
 * @param spi SPI_t struct containing the desired configuration settings.
 */
void SPI_init(SPI_t spi) {
  /* Disable SPI module before configuring */
  SPCRbits.spe = 0;

  /* Configure SPI mode (Master/Slave) */
  switch (spi.mode)
    {
    case SPI_MODE_MASTER:
      /******** Configure SPI Master Pins *********
       * SS(PB4)   --> Output
       * MOSI(PB5) --> Output
       * MISO(PB6) --> Input
       * SCK(PB7)  --> Output
       ********************************************/
      GPIO_setupPinDirection(PORTB_ID, PIN4_ID, PIN_OUTPUT); /* SS */
      GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT); /* MOSI */
      GPIO_setupPinDirection(PORTB_ID, PIN6_ID, PIN_INPUT); /* MISO */
      GPIO_setupPinDirection(PORTB_ID, PIN7_ID, PIN_OUTPUT); /* SCK */

      /* Set SS pin to high (deselect slave) */
      GPIO_writePin(PORTB_ID, PIN4_ID, LOGIC_HIGH);

      /* Set SPI to master mode */
      SPCRbits.mstr = 1;
      break;

    case SPI_MODE_SLAVE:
      /******** Configure SPI Slave Pins *********
       * SS(PB4)   --> Input
       * MOSI(PB5) --> Input
       * MISO(PB6) --> Output
       * SCK(PB7)  --> Input
       ********************************************/
      GPIO_setupPinDirection(PORTB_ID, PIN4_ID, PIN_INPUT); /* SS */
      GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_INPUT); /* MOSI */
      GPIO_setupPinDirection(PORTB_ID, PIN6_ID, PIN_OUTPUT); /* MISO */
      GPIO_setupPinDirection(PORTB_ID, PIN7_ID, PIN_INPUT); /* SCK */

      /* Set SPI to slave mode */
      SPCRbits.mstr = 0;
      break;
    }

  /* Configure data order (MSB or LSB first) */
  SPCRbits.dord = spi.dataOrder;

  /* Set clock idle state (low or high) */
  SPCRbits.cpol = spi.clockIdle;

  /* Set clock phase (sample on leading or trailing edge) */
  SPCRbits.cpha = spi.sampleOn;

  /* Configure clock frequency */
  SPCRbits.spr = spi.frequency;

  /* Set double speed if applicable */
  SPSRbits.spi2x = spi.frequency >> 2;

#ifdef SPI_INTERRUPT_ENABLE
  /* Enable Interrupt if needed */
  SPCRbits.spie = 1;
#endif

  /* Enable the SPI module */
  SPCRbits.spe = 1;
}

/**
 * @brief De-initializes the SPI module by disabling it.
 */
void SPI_deInit(void) {
  SPCR = 0; /* Clear SPI control register to disable SPI */
#ifdef SPI_INTERRUPT_ENABLE
  /* Disable Interrupt if enabled */
  SPCRbits.spie = 0;
#endif
}

/**
 * @brief Configures a slave selector pin to be used for selecting the SPI slave device.
 *
 * @param slave SPI_slaveSelector_t struct containing the port and pin for slave selection.
 */
void SPI_initSlaveSelector(SPI_slaveSelector_t slave) {
  /* Set the slave select pin as output and keep it high (deselect) */
  GPIO_setupPinDirection(slave.port, slave.pin, PIN_OUTPUT);
  GPIO_writePin(slave.port, slave.pin, LOGIC_HIGH);
}

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
void SPI_masterSendReceiveByteBlocking(SPI_slaveSelector_t slave, uint8 sData, uint8 *rData) {
  /* Validate input parameter */
  if (rData == NULL_PTR) {
    return;
  }

  /* Select the slave device by setting SS low */
  GPIO_writePin(slave.port, slave.pin, LOGIC_LOW);

  /* Load data into SPI data register to start transmission */
  SPDR = sData;

  /* Wait until the transmission is complete (SPIF flag set) */
  while (0 == SPSRbits.spif)
    ;

  /* Retrieve received data */
  *rData = SPDR;

  /* Deselect the slave device by setting SS high */
  GPIO_writePin(slave.port, slave.pin, LOGIC_HIGH);
}

/**
 * @brief Sends a byte of data in SPI.
 *
 * This function transmits a single byte of data through the SPI peripheral.
 *
 * @param sData Data byte to be sent through the SPI.
 */
void SPI_sendData(uint8 sData) {
  /* Load data into SPI data register to send it */
  SPDR = sData;
}

/**
 * @brief Receives a byte of data in SPI.
 *
 * This function receives a byte of data through the SPI peripheral.
 *
 * @param rData Pointer to a variable where the received byte will be stored.
 */
void SPI_receiveData(uint8 *rData) {
  /* Read received data from SPI data register */
  *rData = SPDR;
}

#ifdef SPI_INTERRUPT_ENABLE
/**
 * @brief Sets the interrupt handler for SPI.
 *
 * This function allows the user to set a custom interrupt handler for the SPI interrupt.
 *
 * @param spiInterruptHandler Pointer to the interrupt handler function.
 */
void SPI_setInterruptHandler(void (*spiInterruptHandler)(void)) {
  SPI_interruptHandler = spiInterruptHandler;
}
#endif

#ifdef SPI_INTERRUPT_ENABLE
/**
 * @brief SPI Interrupt Service Routine (ISR).
 *
 * This ISR is triggered when the SPI transfer is complete. It checks if a
 * custom interrupt handler is set and invokes it. This allows the user
 * to handle SPI transfer completion events with a user-defined function.
 */
ISR(SPI_STC_vect) {
  if (NULL_PTR != SPI_interruptHandler)
    (*SPI_interruptHandler)();
}
#endif

