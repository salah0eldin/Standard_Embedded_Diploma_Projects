/******************************************************************************
 *
 * Module: USART
 *
 * File Name: usart.h
 *
 * Description: 
 *
 * Created on: Oct 10, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef MCAL_USART_USART_H_
#define MCAL_USART_USART_H_

#include "../../std_types.h"
#include "../GPIO/gpio_registers.h"
#include <avr/io.h>

/*#define USART_RX_COMPLETE_INTERRUPT_ENABLE*/
/*#define USART_TX_COMPLETE_INTERRUPT_ENABLE*/
/*#define USART_EMPTY_REGISTER_INTERRUPT_ENABLE*/

#define USART_MULTI_PROCESSOR_ENABLE()	(UCSRA = UCSRA | (1 << MPCM))
#define USART_MULTI_PROCESSOR_DISABLE()	(UCSRA = UCSRA & ~(1 << MPCM))

#define USART_RECEIVE_COMPLETE()	(UCSRAbits.rxc)
#define USART_TRANSMIT_COMPLETE()	(UCSRAbits.txc)
#define USART_DATA_REGISTER_EMPTY()	(UCSRAbits.udre)

#define USART_SEND_NINGTH_BIT(bit)	(UCSRBbits.txb8 = bit)
#define USART_RECEIVE_NINGTH_BIT(bit)	(UCSRBbits.rxb8)

typedef enum {
  USART_MODE_ASYNC,
  USART_MODE_SYNC_MASTER,
  USART_MODE_SYNC_SLAVE
} USART_mode_t;

typedef enum {
  USART_ASYNC_SPEED_NORMAL,
  USART_ASYNC_SPEED_DOUBLE_NORMAL
} USART_asyncSpeed_t;

typedef enum {
  USART_PARITY_DISABLED,
  USART_PARITY_EVEN = 2,
  USART_PARITY_ODD
} USART_parityMode_t;

typedef enum {
  USART_STOP_1BIT,
  USART_STOP_2BIT
} USART_stopBit_t;

typedef enum {
  USART_CHANGE_RISING_SAMPLE_FALLING,
  USART_CHANGE_FALLING_SAMPLE_RISING
} USART_clockPolarity_t;

typedef enum {
  USART_CHAR_SIZE_5BIT,
  USART_CHAR_SIZE_6BIT,
  USART_CHAR_SIZE_7BIT,
  USART_CHAR_SIZE_8BIT,
  USART_CHAR_SIZE_9BIT = 7
} USART_characterSize_t;

typedef enum{
  USART_TX_DISABLE,
  USART_TX_ENABLE,

  USART_RX_DISABLE = 0,
  USART_RX_ENABLE
} USART_rx_tx_enable_disable_t;

typedef struct {
  uint16 baudRate;
  uint8 mode :2;
  uint8 parityMode :2;
  uint8 asyncSpeed :1;
  uint8 stopBits :1;
  uint8 clockPolarity :1;
  uint8 txEnable : 1;
  uint8 rxEnable : 1;
  uint8 charSize :3;


} USART_t;

extern USART_t g_usart;

void USART_init(USART_t *usart);

void USART_deInit(void);

boolean USART_sendCharNonBlocking(uint8 data);

boolean USART_receiveCharNonBlocking(uint8 *ptrData);

void USART_sendCharBlocking(uint8 data);

void USART_sendStringBlocking(uint8 *strData);

void USART_receiveCharBlocking(uint8 *ptrData);

void USART_recieveStringBlocking(uint8 *ptrStrData, uint8 length);

#ifdef USART_RX_COMPLETE_INTERRUPT_ENABLE
void USART_setRXCompleteInterruptHandler(void (*rxCompleteInterruptHandler)(void));
#endif

#ifdef USART_TX_COMPLETE_INTERRUPT_ENABLE
void USART_setTXCompleteInterruptHandler(void (*txCompleteInterruptHandler)(void));
#endif

#ifdef USART_EMPTY_REGISTER_INTERRUPT_ENABLE
void USART_setEmptyRegisterInterruptHandler(void (*emptyRegisterInterruptHandler)(void));
#endif

#endif /* MCAL_USART_USART_H_ */
