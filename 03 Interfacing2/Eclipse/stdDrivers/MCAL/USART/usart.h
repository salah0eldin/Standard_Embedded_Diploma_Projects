/******************************************************************************
 *
 * Module: USART
 *
 * File Name: usart.h
 *
 * Description: Header file for the AVR USART driver, containing macros,
 *              definitions, and function prototypes for initialization and
 *              handling USART communication.
 *
 * Created on: Oct 10, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef MCAL_USART_USART_H_
#define MCAL_USART_USART_H_

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/
#include "../GPIO/gpio_registers.h"
#include <avr/io.h>
#include "../../LIB/std_types.h"

/*******************************************************************************
 *                              Macros                                         *
 *******************************************************************************/

/* Optional Interrupt Enable Definitions */
/*#define USART_RX_COMPLETE_INTERRUPT_ENABLE*/
/*#define USART_TX_COMPLETE_INTERRUPT_ENABLE*/
/*#define USART_EMPTY_REGISTER_INTERRUPT_ENABLE*/

/* Multi-processor Communication Mode Enable/Disable */
#define USART_MULTI_PROCESSOR_ENABLE()   (UCSRA |= (1 << MPCM))
#define USART_MULTI_PROCESSOR_DISABLE()  (UCSRA &= ~(1 << MPCM))

/* USART Status Register Checks */
/** Macro to check if data reception is complete */
#define USART_RECEIVE_COMPLETE()         (UCSRAbits.rxc)

/** Macro to check if data transmission is complete */
#define USART_TRANSMIT_COMPLETE()        (UCSRAbits.txc)

/** Macro to check if the data register is empty */
#define USART_DATA_REGISTER_EMPTY()      (UCSRAbits.udre)

/* 9th Bit Handling (for 9-bit character size) */
#define USART_SEND_NINTH_BIT(bit)        (UCSRBbits.txb8 = bit)
#define USART_RECEIVE_NINTH_BIT()        (UCSRBbits.rxb8)

/*******************************************************************************
 *                              Enums and Structures                           *
 *******************************************************************************/

/**
 * @enum USART_mode_t
 * @brief Enum for selecting the USART operating mode
 */
typedef enum {
    USART_MODE_ASYNC,            /**< Asynchronous Mode         */
    USART_MODE_SYNC_MASTER,      /**< Synchronous Mode (Master) */
    USART_MODE_SYNC_SLAVE        /**< Synchronous Mode (Slave)  */
} USART_mode_t;

/**
 * @enum USART_asyncSpeed_t
 * @brief Enum for selecting the asynchronous speed mode
 */
typedef enum {
    USART_ASYNC_SPEED_NORMAL,       /**< Normal Speed */
    USART_ASYNC_SPEED_DOUBLE_NORMAL /**< Double Speed */
} USART_asyncSpeed_t;

/**
 * @enum USART_parityMode_t
 * @brief Enum for selecting parity mode
 */
typedef enum {
    USART_PARITY_DISABLED,        /**< Parity Disabled */
    USART_PARITY_EVEN = 2,        /**< Even Parity     */
    USART_PARITY_ODD              /**< Odd Parity      */
} USART_parityMode_t;

/**
 * @enum USART_stopBit_t
 * @brief Enum for selecting the number of stop bits
 */
typedef enum {
    USART_STOP_1BIT,              /**< 1 Stop Bit  */
    USART_STOP_2BIT               /**< 2 Stop Bits */
} USART_stopBit_t;

/**
 * @enum USART_clockPolarity_t
 * @brief Enum for clock polarity in synchronous mode
 */
typedef enum {
    USART_CHANGE_RISING_SAMPLE_FALLING, /**< Rising Edge Change, Sample on Falling Edge */
    USART_CHANGE_FALLING_SAMPLE_RISING  /**< Falling Edge Change, Sample on Rising Edge */
} USART_clockPolarity_t;

/**
 * @enum USART_characterSize_t
 * @brief Enum for selecting character size in bits
 */
typedef enum {
    USART_CHAR_SIZE_5BIT,         /**< 5-bit Character Size */
    USART_CHAR_SIZE_6BIT,         /**< 6-bit Character Size */
    USART_CHAR_SIZE_7BIT,         /**< 7-bit Character Size */
    USART_CHAR_SIZE_8BIT,         /**< 8-bit Character Size */
    USART_CHAR_SIZE_9BIT = 7      /**< 9-bit Character Size */
} USART_characterSize_t;

/**
 * @enum USART_rx_tx_enable_disable_t
 * @brief Enum for enabling/disabling transmitter and receiver
 */
typedef enum {
    USART_TX_DISABLE,             /**< Transmitter Disable */
    USART_TX_ENABLE,              /**< Transmitter Enable  */
    USART_RX_DISABLE = 0,         /**< Receiver Disable    */
    USART_RX_ENABLE               /**< Receiver Enable     */
} USART_rx_tx_enable_disable_t;

/**
 * @struct USART_t
 * @brief Struct to configure USART settings.
 */
typedef struct {
    uint16 baudRate;             /**< Baud rate for communication                         */
    uint8 mode          : 2;     /**< USART operating mode (Async/Sync Master/Sync Slave) */
    uint8 parityMode    : 2;     /**< Parity mode (Even/Odd/Disabled)                     */
    uint8 asyncSpeed    : 1;     /**< Asynchronous speed mode (Normal/Double)             */
    uint8 stopBits      : 1;     /**< Number of stop bits (1/2)                           */
    uint8 clockPolarity : 1;     /**< Clock polarity for synchronous mode                 */
    uint8 txEnable      : 1;     /**< Transmitter enable                                  */
    uint8 rxEnable      : 1;     /**< Receiver enable                                     */
    uint8 charSize      : 3;     /**< Character size in bits (5 to 9 bits)                */
} USART_t;

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
extern USART_t g_usart; /**< Global USART configuration structure */

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * @brief Initialize the USART with the specified configuration.
 *
 * @param usart Pointer to the USART configuration structure.
 */
void USART_init(USART_t *usart);

/**
 * @brief De-initialize the USART, resetting it to its default state.
 */
void USART_deInit(void);

/**
 * @brief Send a character over USART in non-blocking mode.
 *
 * @param data The character to be sent.
 * @return boolean Returns TRUE if data was sent successfully, FALSE otherwise.
 */
boolean USART_sendCharNonBlocking(uint8 data);

/**
 * @brief Receive a character over USART in non-blocking mode.
 *
 * @param ptrData Pointer to store the received character.
 * @return boolean Returns TRUE if data was received successfully, FALSE otherwise.
 */
boolean USART_receiveCharNonBlocking(uint8 *ptrData);

/**
 * @brief Send a character over USART in blocking mode.
 *
 * @param data The character to be sent.
 */
void USART_sendCharBlocking(uint8 data);

/**
 * @brief Send a string of characters over USART in blocking mode.
 *
 * @param strData Pointer to the string to be sent.
 */
void USART_sendStringBlocking(uint8 *strData);

/**
 * @brief Receive a character over USART in blocking mode.
 *
 * @param ptrData Pointer to store the received character.
 */
void USART_receiveCharBlocking(uint8 *ptrData);

/**
 * @brief Receive a string of characters over USART in blocking mode.
 *
 * @param ptrStrData Pointer to store the received string.
 * @param length The length of the string to receive.
 */
void USART_recieveStringBlocking(uint8 *ptrStrData, uint8 length);

/* Interrupt Handlers (Optional, based on definitions) */
#ifdef USART_RX_COMPLETE_INTERRUPT_ENABLE
/**
 * @brief Set the RX Complete interrupt handler.
 *
 * @param rxCompleteInterruptHandler Function pointer to the interrupt handler.
 */
void USART_setRXCompleteInterruptHandler(void (*rxCompleteInterruptHandler)(void));
#endif

#ifdef USART_TX_COMPLETE_INTERRUPT_ENABLE
/**
 * @brief Set the TX Complete interrupt handler.
 *
 * @param txCompleteInterruptHandler Function pointer to the interrupt handler.
 */
void USART_setTXCompleteInterruptHandler(void (*txCompleteInterruptHandler)(void));
#endif

#ifdef USART_EMPTY_REGISTER_INTERRUPT_ENABLE
/**
 * @brief Set the Data Register Empty interrupt handler.
 *
 * @param emptyRegisterInterruptHandler Function pointer to the interrupt handler.
 */
void USART_setEmptyRegisterInterruptHandler(void (*emptyRegisterInterruptHandler)(void));
#endif

#endif /* MCAL_USART_USART_H_ */
