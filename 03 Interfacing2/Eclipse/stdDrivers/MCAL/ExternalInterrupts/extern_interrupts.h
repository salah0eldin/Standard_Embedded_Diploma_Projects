/******************************************************************************
 *
 * Module: extern_interrupts
 *
 * File Name: extern_interrupts.h
 *
 * Description: Header file for the external interrupts module. This module
 *              provides initialization for INT0, INT1, and INT2 interrupts
 *              and allows setting the edge trigger type for each interrupt.
 *
 * Created on: Oct 12, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef MCAL_EXTERNALINTERRUPTS_EXTERN_INTERRUPTS_H_
#define MCAL_EXTERNALINTERRUPTS_EXTERN_INTERRUPTS_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../std_types.h" /* Standard data types definition */

/*******************************************************************************
 *                               Macro Declarations                            *
 *******************************************************************************/

/* Enable or disable external interrupts based on the project requirements */
#define EXTERN_INTERRUPT_INT0_ENABLE
#define EXTERN_INTERRUPT_INT1_ENABLE
#define EXTERN_INTERRUPT_INT2_ENABLE

/*******************************************************************************
 *                           Data Type Declarations                            *
 *******************************************************************************/

/**
 * Enum for specifying the edge trigger type for external interrupts.
 * - EXTERN_INTERRUPT_EDGE_LOWLEVEL: Interrupt triggered on low level.
 * - EXTERN_INTERRUPT_EDGE_ANY: Interrupt triggered on any edge (rising or falling).
 * - EXTERN_INTERRUPT_EDGE_FALLING: Interrupt triggered on falling edge.
 * - EXTERN_INTERRUPT_EDGE_RAISING: Interrupt triggered on rising edge.
 */
typedef enum {
  EXTERN_INTERRUPT_EDGE_LOWlEVEL,
  EXTERN_INTERRUPT_EDGE_ANY,
  EXTERN_INTERRUPT_EDGE_FALLING,
  EXTERN_INTERRUPT_EDGE_RAISING
} EXTERN_INTERRUPT_edge_t;

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

#ifdef EXTERN_INTERRUPT_INT0_ENABLE
/**
 * @brief Initializes the INT0 external interrupt with the specified edge trigger.
 *
 * @param edge Edge trigger type for the interrupt (from EXTERN_INTERRUPT_edge_t).
 * @param externInterruptHandler0 Pointer to the callback function that handles the INT0 interrupt.
 */
void EXTERN_INTERRUPT_INT0_init(uint8 edge, void (*externInterruptHandler0)(void));
#endif

#ifdef EXTERN_INTERRUPT_INT1_ENABLE
/**
 * @brief Initializes the INT1 external interrupt with the specified edge trigger.
 *
 * @param edge Edge trigger type for the interrupt (from EXTERN_INTERRUPT_edge_t).
 * @param externInterruptHandler1 Pointer to the callback function that handles the INT1 interrupt.
 */
void EXTERN_INTERRUPT_INT1_init(uint8 edge, void (*externInterruptHandler1)(void));
#endif

#ifdef EXTERN_INTERRUPT_INT2_ENABLE
/**
 * @brief Initializes the INT2 external interrupt with the specified edge trigger.
 *
 * @param edge Edge trigger type for the interrupt (from EXTERN_INTERRUPT_edge_t).
 * @param externInterruptHandler2 Pointer to the callback function that handles the INT2 interrupt.
 */
void EXTERN_INTERRUPT_INT2_init(uint8 edge, void (*externInterruptHandler2)(void));
#endif

#endif /* MCAL_EXTERNALINTERRUPTS_EXTERN_INTERRUPTS_H_ */
