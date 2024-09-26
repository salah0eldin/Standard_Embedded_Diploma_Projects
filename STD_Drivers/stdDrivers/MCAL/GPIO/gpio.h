/******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.h
 *
 * Description: gpio driver
 *
 * Created on: Sep 26, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef MCAL_GPIO_GPIO_H_
#define MCAL_GPIO_GPIO_H_

#include "avr/io.h"
#include "../common_macros.h"
#include "../std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define NUM_OF_PORTS           4  /* Number of available ports */
#define NUM_OF_PINS_PER_PORT   8  /* Number of pins per port */

/* Port IDs */
#define PORTA_ID               0  /* Port A identifier */
#define PORTB_ID               1  /* Port B identifier */
#define PORTC_ID               2  /* Port C identifier */
#define PORTD_ID               3  /* Port D identifier */

/* Pin IDs */
#define PIN0_ID                0  /* Pin 0 identifier */
#define PIN1_ID                1  /* Pin 1 identifier */
#define PIN2_ID                2  /* Pin 2 identifier */
#define PIN3_ID                3  /* Pin 3 identifier */
#define PIN4_ID                4  /* Pin 4 identifier */
#define PIN5_ID                5  /* Pin 5 identifier */
#define PIN6_ID                6  /* Pin 6 identifier */
#define PIN7_ID                7  /* Pin 7 identifier */

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/* Enum to define pin direction */
typedef enum {
	PIN_INPUT, /* Pin configured as input */
	PIN_OUTPUT /* Pin configured as output */
} GPIO_PinDirectionType;

/* Enum to define port direction */
typedef enum {
	PORT_INPUT, /* All pins in the port are inputs */
	PORT_OUTPUT = 0xFF /* All pins in the port are outputs */
} GPIO_PortDirectionType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/**
 * @brief Setup the direction of the required pin (input/output).
 *
 * This function configures the specified pin as either input or output.
 * If the port number or pin number is invalid, the function does nothing.
 *
 * @param port_num Port number (0 to NUM_OF_PORTS-1)
 * @param pin_num Pin number (0 to NUM_OF_PINS_PER_PORT-1)
 * @param direction Direction of the pin (PIN_INPUT or PIN_OUTPUT)
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num,
		GPIO_PinDirectionType direction);

/**
 * @brief Write a value (Logic High or Logic Low) on the required pin.
 *
 * This function writes a logic level (HIGH/LOW) to the specified pin. If the pin is an input pin,
 * it enables or disables the internal pull-up resistor.
 *
 * @param port_num Port number (0 to NUM_OF_PORTS-1)
 * @param pin_num Pin number (0 to NUM_OF_PINS_PER_PORT-1)
 * @param value Value to write (LOGIC_HIGH or LOGIC_LOW)
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);

/**
 * @brief Read and return the value of the required pin.
 *
 * This function reads the logic level (HIGH/LOW) of the specified pin. If the port number or
 * pin number is invalid, it returns LOGIC_LOW by default.
 *
 * @param port_num Port number (0 to NUM_OF_PORTS-1)
 * @param pin_num Pin number (0 to NUM_OF_PINS_PER_PORT-1)
 *
 * @return Value of the pin (LOGIC_HIGH or LOGIC_LOW)
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);

/**
 * @brief Setup the direction of the required port (all pins input/output).
 *
 * This function configures all the pins of the specified port as either input or output.
 * If the port number is invalid, the function does nothing.
 *
 * @param port_num Port number (0 to NUM_OF_PORTS-1)
 * @param direction Direction of the port (PORT_INPUT or PORT_OUTPUT)
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction);

/**
 * @brief Write a value to the required port.
 *
 * This function writes the specified value to the port. If a pin is set as an input pin, it activates or deactivates
 * the internal pull-up resistor.
 *
 * @param port_num Port number (0 to NUM_OF_PORTS-1)
 * @param value Value to write to the port (0 to 255)
 */
void GPIO_writePort(uint8 port_num, uint8 value);

/**
 * @brief Read and return the value of the required port.
 *
 * This function reads the value of the specified port. If the port number is invalid, it returns 0.
 *
 * @param port_num Port number (0 to NUM_OF_PORTS-1)
 *
 * @return Value of the port (0 to 255)
 */
uint8 GPIO_readPort(uint8 port_num);

#endif /* MCAL_GPIO_GPIO_H_ */
