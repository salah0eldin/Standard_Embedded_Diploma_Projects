/******************************************************************************
 *
 * Module: USART
 *
 * File Name: usart.c
 *
 * Description: 
 *
 * Created on: Oct 10, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#include "usart.h"
#include "../GPIO/gpio.h"
#include <avr/interrupt.h>

USART_t g_usart = { .baudRate = 9600, .mode = USART_MODE_ASYNC, .charSize = USART_CHAR_SIZE_8BIT,
    .asyncSpeed = USART_ASYNC_SPEED_NORMAL, .parityMode = USART_PARITY_DISABLED, .stopBits =
	USART_STOP_1BIT, .txEnable = USART_TX_ENABLE, .rxEnable = USART_RX_ENABLE, .clockPolarity =
	USART_CHANGE_FALLING_SAMPLE_RISING };

#ifdef USART_RX_COMPLETE_INTERRUPT_ENABLE
static void (*USART_rxCompleteInterruptHandler)(void) = NULL_PTR;
#endif

#ifdef USART_TX_COMPLETE_INTERRUPT_ENABLE
static void (*USART_txCompleteInterruptHandler)(void) = NULL_PTR;
#endif

#ifdef USART_EMPTY_REGISTER_INTERRUPT_ENABLE
static void (*USART_emptyRegisterInterruptHandler)(void) = NULL_PTR;
#endif

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
	  ubrrTemp /= 8;
	  break;
	case USART_ASYNC_SPEED_DOUBLE_NORMAL:
	  ubrrTemp /= 4;
	  break;
	}
      break;
    case USART_MODE_SYNC_MASTER:
      CLEAR_BIT(UCSRA, MPCM);
      modeFlag = 1;

      GPIO_setupPinDirection(PORTB_ID, PIN0_ID, PIN_OUTPUT);
      break;
    case USART_MODE_SYNC_SLAVE:
      SET_BIT(UCSRA, MPCM);
      modeFlag = 1;

      GPIO_setupPinDirection(PORTB_ID, PIN0_ID, PIN_INPUT);
      break;
    }

  ubrrTemp--;

  UBRRH = (uint8) (ubrrTemp >> 8) & 0x0F;
  UBRRL = (uint8) ubrrTemp;

  /* Set interrupts */
#ifdef USART_RX_COMPLETE_INTERRUPT_ENABLE
  SET_BIT(UCSRB, RXCIE);
#endif

#ifdef USART_TX_COMPLETE_INTERRUPT_ENABLE
  SET_BIT(UCSRB, TXCIE);
#endif

#ifdef USART_EMPTY_REGISTER_INTERRUPT_ENABLE
  SET_BIT(UCSRB, UDRIE);
#endif

  /* Set Char Size ucsz2 */
  UCSRBbits.ucsz2 = usart->charSize>> 2;

  UCSRC = (1 << URSEL) |
      	  (usart->parityMode << UPM0)      |  /* Select Parity */
      	  (usart->stopBits << USBS)        |  /* Select Stop */
      	  ((usart->charSize & 3) << UCSZ0) |  /* Set Char Size ucsz0 & ocsz1 */
	  (usart->clockPolarity << UCPOL);    /* Select Clock polarity */

  /* Enable module */
  UCSRBbits.rxen = usart->rxEnable;
  UCSRBbits.txen = usart->txEnable;

}

void USART_deInit(void) {
  UCSRA = UCSRB = UBRRL = UBRRH = 0;
  UCSRC = (1 << URSEL);

#ifdef USART_RX_COMPLETE_INTERRUPT_ENABLE
  CLEAR_BIT(UCSRB, RXCIE);
#endif

#ifdef USART_TX_COMPLETE_INTERRUPT_ENABLE
  CLEAR_BIT(UCSRB, TXCIE);
#endif

#ifdef USART_EMPTY_REGISTER_INTERRUPT_ENABLE
  CLEAR_BIT(UCSRB, UDRIE);
#endif
}

boolean USART_sendCharNonBlocking(uint8 data) {
  if (USART_DATA_REGISTER_EMPTY()) {
    UDR = data;
    return TRUE;
  }
  else {
    return FALSE;
  }
}

boolean USART_receiveCharNonBlocking(uint8 *ptrData) {
  if (USART_RECEIVE_COMPLETE()) {
    *ptrData = UDR;
    return TRUE;
  }
  else {
    return FALSE;
  }
}

void USART_sendCharBlocking(uint8 data) {
  while (FALSE == USART_sendCharNonBlocking(data))
    ;
}

void USART_sendStringBlocking(uint8 *strData) {
  while (*strData != '\0') {
    USART_sendCharBlocking(*strData);
    if (*strData == '\r')
      break;
    else
      strData++;
  }
}

void USART_receiveCharBlocking(uint8 *ptrData) {
  while (FALSE == USART_receiveCharNonBlocking(ptrData))
    ;
}

void USART_recieveStringBlocking(uint8 *ptrStrData, uint8 length) {
  uint8 len = 0;
  do {
    USART_receiveCharBlocking(&ptrStrData[len++]);
  }
  while (length > len && ptrStrData[len - 1] != '\0' && ptrStrData[len - 1] != '\r');
}

#ifdef USART_RX_COMPLETE_INTERRUPT_ENABLE
void USART_setRXCompleteInterruptHandler(void (*rxCompleteInterruptHandler)(void)) {
  USART_rxCompleteInterruptHandler = rxCompleteInterruptHandler;
}
#endif

#ifdef USART_TX_COMPLETE_INTERRUPT_ENABLE
void USART_setTXCompleteInterruptHandler(void (*txCompleteInterruptHandler)(void)) {
  USART_txCompleteInterruptHandler = txCompleteInterruptHandler;
}
#endif

#ifdef USART_EMPTY_REGISTER_INTERRUPT_ENABLE
void USART_setEmptyRegisterInterruptHandler(void (*emptyRegisterInterruptHandler)(void)) {
  USART_emptyRegisterInterruptHandler = emptyRegisterInterruptHandler;
}
#endif


#ifdef USART_RX_COMPLETE_INTERRUPT_ENABLE
ISR(USART_RXC_vect) {
  if (USART_rxCompleteInterruptHandler != NULL_PTR)
    USART_rxCompleteInterruptHandler();
}
#endif

#ifdef USART_TX_COMPLETE_INTERRUPT_ENABLE
ISR(USART_TXC_vect) {
  if (USART_txCompleteInterruptHandler != NULL_PTR)
    USART_txCompleteInterruptHandler();
}
#endif

#ifdef USART_EMPTY_REGISTER_INTERRUPT_ENABLE
ISR(USART_UDRE_vect) {
  if (USART_emptyRegisterInterruptHandler != NULL_PTR)
    USART_emptyRegisterInterruptHandler();
}
#endif
