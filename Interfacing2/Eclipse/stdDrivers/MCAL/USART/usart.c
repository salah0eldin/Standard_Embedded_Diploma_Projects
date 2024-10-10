/******************************************************************************
 *
 * Module: USART
 *
 * File Name: usart.c
 *
 * Description: This module provides the implementation of the USART driver
 *              for handling asynchronous and synchronous serial communication.
 *
 * Created on: Oct 10, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/
#include "usart.h"
#include "../GPIO/gpio.h"
#include <avr/interrupt.h>

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
/* Global variable for USART configuration */
USART_t g_usart = {
    .baudRate = 9600,                       /** Baud rate for USART communication */
    .mode = USART_MODE_ASYNC,               /** Mode of operation (asynchronous)  */
    .charSize = USART_CHAR_SIZE_8BIT,       /** Character size (8 bits)           */
    .asyncSpeed = USART_ASYNC_SPEED_NORMAL, /** Asynchronous speed (normal)       */
    .parityMode = USART_PARITY_DISABLED,    /** Parity mode (disabled)            */
    .stopBits = USART_STOP_1BIT,            /** Number of stop bits (1 bit)       */
    .txEnable = USART_TX_ENABLE,            /** Transmitter enable flag (enabled) */
    .rxEnable = USART_RX_ENABLE,            /** Receiver enable flag (enabled)    */
    .clockPolarity = USART_CHANGE_FALLING_SAMPLE_RISING /** Clock polarity (falling edge sampling) */
};


#ifdef USART_RX_COMPLETE_INTERRUPT_ENABLE
static void (*USART_rxCompleteInterruptHandler)(void) = NULL_PTR; /**< RX Complete interrupt handler */
#endif

#ifdef USART_TX_COMPLETE_INTERRUPT_ENABLE
static void (*USART_txCompleteInterruptHandler)(void) = NULL_PTR; /**< TX Complete interrupt handler */
#endif

#ifdef USART_EMPTY_REGISTER_INTERRUPT_ENABLE
static void (*USART_emptyRegisterInterruptHandler)(void) = NULL_PTR; /**< Empty Register interrupt handler */
#endif

/*******************************************************************************
 *                              Functions Declarations                         *
 *******************************************************************************/
/**
 * @brief Initializes the USART module with the given configuration.
 *
 * This function configures the USART parameters such as baud rate, mode,
 * character size, parity, stop bits, and interrupt settings. It disables the
 * USART during configuration and enables it after setup.
 *
 * @param usart Pointer to the USART configuration structure.
 */
void USART_init(USART_t *usart) {
  uint8 modeFlag = 0; /* Async */

  /* Disable module */
  CLEAR_BIT(UCSRB, RXEN);
  CLEAR_BIT(UCSRB, TXEN);

  uint32 ubrrTemp = F_CPU / (2 * (usart->baudRate));

  /* Set Mode */
  /* Set Speed & BaudRate */
  switch (usart->mode)
    {
    case USART_MODE_ASYNC:
      CLEAR_BIT(UCSRA, MPCM);
      switch (usart->asyncSpeed)
	{
	case USART_ASYNC_SPEED_NORMAL:
	  ubrrTemp /= 8; /* Divide by 8 for normal speed */
	  break;
	case USART_ASYNC_SPEED_DOUBLE_NORMAL:
	  ubrrTemp /= 4; /* Divide by 4 for double speed */
	  break;
	}
      break;
    case USART_MODE_SYNC_MASTER:
      CLEAR_BIT(UCSRA, MPCM);
      modeFlag = 1;

      /* Configure pin for Sync Master */
      GPIO_setupPinDirection(PORTB_ID, PIN0_ID, PIN_OUTPUT);
      break;
    case USART_MODE_SYNC_SLAVE:
      SET_BIT(UCSRA, MPCM);
      modeFlag = 1;

      /* Configure pin for Sync Slave */
      GPIO_setupPinDirection(PORTB_ID, PIN0_ID, PIN_INPUT);
      break;
    }

  ubrrTemp--;

  /* Set baud rate */
  UBRRH = (uint8) (ubrrTemp >> 8) & 0x0F;
  UBRRL = (uint8) ubrrTemp;

  /* Set interrupts */
#ifdef USART_RX_COMPLETE_INTERRUPT_ENABLE
  SET_BIT(UCSRB, RXCIE); /* Enable RX Complete Interrupt */
#endif

#ifdef USART_TX_COMPLETE_INTERRUPT_ENABLE
  SET_BIT(UCSRB, TXCIE); /* Enable TX Complete Interrupt */
#endif

#ifdef USART_EMPTY_REGISTER_INTERRUPT_ENABLE
  SET_BIT(UCSRB, UDRIE); /* Enable Data Register Empty Interrupt */
#endif

  /* Set Char Size */
  UCSRBbits.ucsz2 = usart->charSize >> 2;

  UCSRC = (1 << URSEL) | (usart->parityMode << UPM0) 	| /* Select Parity */
	  (usart->stopBits << USBS) 			| /* Select Stop */
	  ((usart->charSize & 3) << UCSZ0) 		| /* Set Char Size ucsz0 & ucsz1 */
	  (usart->clockPolarity << UCPOL); 		  /* Select Clock polarity */

  /* Enable module */
  UCSRBbits.rxen = usart->rxEnable; /* Enable receiver */
  UCSRBbits.txen = usart->txEnable; /* Enable transmitter */
}

/**
 * @brief Deinitializes the USART module.
 *
 * This function resets the USART registers to their default values and
 * disables all interrupts related to USART.
 */
void USART_deInit(void) {
  UCSRA = UCSRB = UBRRL = UBRRH = 0; /* Reset registers */
  UCSRC = (1 << URSEL); /* Reset UCSRC register */

#ifdef USART_RX_COMPLETE_INTERRUPT_ENABLE
  CLEAR_BIT(UCSRB, RXCIE); /* Disable RX Complete Interrupt */
#endif

#ifdef USART_TX_COMPLETE_INTERRUPT_ENABLE
  CLEAR_BIT(UCSRB, TXCIE); /* Disable TX Complete Interrupt */
#endif

#ifdef USART_EMPTY_REGISTER_INTERRUPT_ENABLE
  CLEAR_BIT(UCSRB, UDRIE); /* Disable Data Register Empty Interrupt */
#endif
}

/**
 * @brief Sends a character non-blocking.
 *
 * This function checks if the USART data register is empty and sends
 * the character if possible. Returns TRUE if successful, otherwise FALSE.
 *
 * @param data Character to be sent.
 * @return boolean TRUE if the character was sent, FALSE if the register was not empty.
 */
boolean USART_sendCharNonBlocking(uint8 data) {
  if (USART_DATA_REGISTER_EMPTY()) {
    UDR = data; /* Send data */
    return TRUE;
  }
  else {
    return FALSE; /* Data register is not empty */
  }
}

/**
 * @brief Receives a character non-blocking.
 *
 * This function checks if a character has been received and stores it
 * in the provided pointer. Returns TRUE if a character was received,
 * otherwise FALSE.
 *
 * @param ptrData Pointer to store the received character.
 * @return boolean TRUE if a character was received, FALSE otherwise.
 */
boolean USART_receiveCharNonBlocking(uint8 *ptrData) {
  if (USART_RECEIVE_COMPLETE()) {
    *ptrData = UDR; /* Read received data */
    return TRUE;
  }
  else {
    return FALSE; /* No data received */
  }
}

/**
 * @brief Sends a character blocking.
 *
 * This function continuously attempts to send a character until successful.
 *
 * @param data Character to be sent.
 */
void USART_sendCharBlocking(uint8 data) {
  while (FALSE == USART_sendCharNonBlocking(data))
    ; /* Wait until character is sent */
}

/**
 * @brief Sends a string blocking.
 *
 * This function sends a string of characters until the null terminator
 * is encountered or a carriage return is found.
 *
 * @param strData Pointer to the string to be sent.
 */
void USART_sendStringBlocking(uint8 *strData) {
  while (*strData != '\0') {
    USART_sendCharBlocking(*strData); /* Send each character */
    if (*strData == '\r')
      break; /* Stop sending if carriage return is found */
    else
      strData++; /* Move to the next character */
  }
}

/**
 * @brief Receives a character blocking.
 *
 * This function continuously attempts to receive a character until successful.
 *
 * @param ptrData Pointer to store the received character.
 */
void USART_receiveCharBlocking(uint8 *ptrData) {
  while (FALSE == USART_receiveCharNonBlocking(ptrData))
    ; /* Wait until character is received */
}

/**
 * @brief Receives a string blocking.
 *
 * This function receives a string of characters up to the specified
 * length or until a null terminator or carriage return is found.
 *
 * @param ptrStrData Pointer to store the received string.
 * @param length Maximum length of the string to receive.
 */
void USART_recieveStringBlocking(uint8 *ptrStrData, uint8 length) {
  uint8 len = 0;
  do {
    USART_receiveCharBlocking(&ptrStrData[len++]); /* Receive each character */
  }
  while (length > len && ptrStrData[len - 1] != '\0' && ptrStrData[len - 1] != '\r');
}

#ifdef USART_RX_COMPLETE_INTERRUPT_ENABLE
/**
 * @brief Sets the RX Complete interrupt handler.
 *
 * This function assigns a callback function to be executed when the
 * RX Complete interrupt occurs.
 *
 * @param rxCompleteInterruptHandler Pointer to the callback function.
 */
void USART_setRXCompleteInterruptHandler(void (*rxCompleteInterruptHandler)(void)) {
  USART_rxCompleteInterruptHandler = rxCompleteInterruptHandler; /* Set handler */
}
#endif

#ifdef USART_TX_COMPLETE_INTERRUPT_ENABLE
/**
 * @brief Sets the TX Complete interrupt handler.
 *
 * This function assigns a callback function to be executed when the
 * TX Complete interrupt occurs.
 *
 * @param txCompleteInterruptHandler Pointer to the callback function.
 */
void USART_setTXCompleteInterruptHandler(void (*txCompleteInterruptHandler)(void)) {
  USART_txCompleteInterruptHandler = txCompleteInterruptHandler; /* Set handler */
}
#endif

#ifdef USART_EMPTY_REGISTER_INTERRUPT_ENABLE
/**
 * @brief Sets the Empty Register interrupt handler.
 *
 * This function assigns a callback function to be executed when the
 * Data Register Empty interrupt occurs.
 *
 * @param emptyRegisterInterruptHandler Pointer to the callback function.
 */
void USART_setEmptyRegisterInterruptHandler(void (*emptyRegisterInterruptHandler)(void)) {
  USART_emptyRegisterInterruptHandler = emptyRegisterInterruptHandler; /* Set handler */
}
#endif

#ifdef USART_RX_COMPLETE_INTERRUPT_ENABLE
/**
 * @brief USART RX Complete interrupt service routine.
 *
 * This function is called when a byte is received. It invokes the
 * registered RX Complete interrupt handler if one is set.
 */
ISR(USART_RXC_vect) {
  if (USART_rxCompleteInterruptHandler != NULL_PTR)
    USART_rxCompleteInterruptHandler(); /* Call handler */
}
#endif

#ifdef USART_TX_COMPLETE_INTERRUPT_ENABLE
/**
 * @brief USART TX Complete interrupt service routine.
 *
 * This function is called when a byte is transmitted. It invokes the
 * registered TX Complete interrupt handler if one is set.
 */
ISR(USART_TXC_vect) {
  if (USART_txCompleteInterruptHandler != NULL_PTR)
    USART_txCompleteInterruptHandler(); /* Call handler */
}
#endif

#ifdef USART_EMPTY_REGISTER_INTERRUPT_ENABLE
/**
 * @brief USART Data Register Empty interrupt service routine.
 *
 * This function is called when the data register is empty. It invokes
 * the registered Empty Register interrupt handler if one is set.
 */
ISR(USART_UDRE_vect) {
  if (USART_emptyRegisterInterruptHandler != NULL_PTR)
    USART_emptyRegisterInterruptHandler(); /* Call handler */
}
#endif
