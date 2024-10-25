/******************************************************************************
 *
 * Module: extern_interrupts
 *
 * File Name: extern_interrupts.c
 *
 * Description: Source file for external interrupts module. This module
 *              provides the implementation of initialization and interrupt
 *              service routines for INT0, INT1, and INT2 interrupts.
 *
 * Created on: Oct 12, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "extern_interrupts.h"
#include "../GPIO/gpio.h"   /* For GPIO setup functions */
#include <avr/interrupt.h>  /* For AVR interrupt handling */

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

#ifdef EXTERN_INTERRUPT_INT0_ENABLE
/* Pointer to the function handling the INT0 interrupt */
static void (*EXTERN_INTERRUPT_interruptHandlerInt0)(void) = NULL_PTR;
#endif

#ifdef EXTERN_INTERRUPT_INT1_ENABLE
/* Pointer to the function handling the INT1 interrupt */
static void (*EXTERN_INTERRUPT_interruptHandlerInt1)(void) = NULL_PTR;
#endif

#ifdef EXTERN_INTERRUPT_INT2_ENABLE
/* Pointer to the function handling the INT2 interrupt */
static void (*EXTERN_INTERRUPT_interruptHandlerInt2)(void) = NULL_PTR;
#endif

/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/

#ifdef EXTERN_INTERRUPT_INT0_ENABLE
/**
 * @brief Initializes the INT0 external interrupt with the specified edge trigger type.
 *
 * @param edge Edge trigger type for INT0 (from EXTERN_INTERRUPT_edge_t).
 * @param externInterruptHandler0 Pointer to the callback function that handles the INT0 interrupt.
 */
void EXTERN_INTERRUPT_INT0_init(uint8 edge, void (*externInterruptHandler0)(void)) {
  /* Set the INT0 pin (PD2) as input */
  GPIO_setupPinDirection(PORTD_ID, PIN2_ID, PIN_INPUT);

  /* Set the edge type for INT0 based on the provided parameter */
  MCUCRbits.isc0 = edge;

  /* Enable INT0 interrupt in the general interrupt control register */
  SET_BIT(GICR, INT0);

  /* Assign the provided callback function to the interrupt handler pointer */
  EXTERN_INTERRUPT_interruptHandlerInt0 = externInterruptHandler0;
}
#endif

#ifdef EXTERN_INTERRUPT_INT1_ENABLE
/**
 * @brief Initializes the INT1 external interrupt with the specified edge trigger type.
 *
 * @param edge Edge trigger type for INT1 (from EXTERN_INTERRUPT_edge_t).
 * @param externInterruptHandler1 Pointer to the callback function that handles the INT1 interrupt.
 */
void EXTERN_INTERRUPT_INT1_init(uint8 edge, void (*externInterruptHandler1)(void)) {
  /* Set the INT1 pin (PD3) as input */
  GPIO_setupPinDirection(PORTD_ID, PIN3_ID, PIN_INPUT);

  /* Set the edge type for INT1 based on the provided parameter */
  MCUCRbits.isc1 = edge;

  /* Enable INT1 interrupt in the general interrupt control register */
  SET_BIT(GICR, INT1);

  /* Assign the provided callback function to the interrupt handler pointer */
  EXTERN_INTERRUPT_interruptHandlerInt1 = externInterruptHandler1;
}
#endif

#ifdef EXTERN_INTERRUPT_INT2_ENABLE
/**
 * @brief Initializes the INT2 external interrupt with the specified edge trigger type.
 *
 * @param edge Edge trigger type for INT2 (from EXTERN_INTERRUPT_edge_t).
 * @param externInterruptHandler2 Pointer to the callback function that handles the INT2 interrupt.
 */
void EXTERN_INTERRUPT_INT2_init(uint8 edge, void (*externInterruptHandler2)(void)) {
  /* Set the INT2 pin (PB2) as input */
  GPIO_setupPinDirection(PORTB_ID, PIN2_ID, PIN_INPUT);

  /* Enable INT2 interrupt in the general interrupt control register */
  SET_BIT(GICR, INT2);

  /* Set the edge type for INT2 (only 0 or 1 for falling/rising edge) */
  MCUCSRbits.isc2 = edge & 1;

  /* Assign the provided callback function to the interrupt handler pointer */
  EXTERN_INTERRUPT_interruptHandlerInt2 = externInterruptHandler2;
}
#endif

/*******************************************************************************
 *                           Interrupt Service Routines                        *
 *******************************************************************************/

#ifdef EXTERN_INTERRUPT_INT0_ENABLE
/**
 * @brief ISR for INT0 external interrupt.
 */
ISR(INT0_vect) {
  if (NULL_PTR != EXTERN_INTERRUPT_interruptHandlerInt0) {
    /* Call the registered handler for INT0 */
    (*EXTERN_INTERRUPT_interruptHandlerInt0)();
  }
}
#endif

#ifdef EXTERN_INTERRUPT_INT1_ENABLE
/**
 * @brief ISR for INT1 external interrupt.
 */
ISR(INT1_vect) {
  if (NULL_PTR != EXTERN_INTERRUPT_interruptHandlerInt1) {
    /* Call the registered handler for INT1 */
    (*EXTERN_INTERRUPT_interruptHandlerInt1)();
  }
}
#endif

#ifdef EXTERN_INTERRUPT_INT2_ENABLE
/**
 * @brief ISR for INT2 external interrupt.
 */
ISR(INT2_vect) {
  if (NULL_PTR != EXTERN_INTERRUPT_interruptHandlerInt2) {
    /* Call the registered handler for INT2 */
    (*EXTERN_INTERRUPT_interruptHandlerInt2)();
  }
}
#endif
