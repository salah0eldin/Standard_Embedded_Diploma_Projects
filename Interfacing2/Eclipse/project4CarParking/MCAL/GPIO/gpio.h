/******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.h
 *
 * Description: GPIO driver for controlling pins and ports on an AVR microcontroller.
 *
 * Created on: Sep 26, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef MCAL_GPIO_GPIO_H_
#define MCAL_GPIO_GPIO_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "avr/io.h"

#include "../../common_macros.h"
#include "../../std_types.h"
#include "gpio_registers.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define NUM_OF_PORTS           4  /**< Number of available ports */
#define NUM_OF_PINS_PER_PORT   8  /**< Number of pins per port */

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/**
 * @brief Enum to define the IDs of the PORTs.
 */
typedef enum {
	PORTA_ID, 	/**< Port A identifier */
	PORTB_ID, 	/**< Port B identifier */
	PORTC_ID, 	/**< Port C identifier */
	PORTD_ID		/**< Port D identifier */
} GPIO_portsIds;

/**
 * @brief Enum to define the IDs of the PINs.
 */
typedef enum {
	PIN0_ID, 	/**< Pin 0 identifier */
	PIN1_ID, 	/**< Pin 1 identifier */
	PIN2_ID, 	/**< Pin 2 identifier */
	PIN3_ID, 	/**< Pin 3 identifier */
	PIN4_ID, 	/**< Pin 4 identifier */
	PIN5_ID, 	/**< Pin 5 identifier */
	PIN6_ID, 	/**< Pin 6 identifier */
	PIN7_ID 	/**< Pin 7 identifier */
} GPIO_pinsIds;

/**
 * @brief Enum to define the direction of a pin.
 */
typedef enum {
	PIN_INPUT, /**< Pin configured as input */
	PIN_OUTPUT /**< Pin configured as output */
} GPIO_PinDirectionType;

/**
 * @brief Enum to define the direction of an entire port.
 */
typedef enum {
	PORT_INPUT, /**< All pins in the port are configured as inputs */
	PORT_OUTPUT = 0xFF /**< All pins in the port are configured as outputs */
} GPIO_PortDirectionType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/**
 * @brief Configure the direction of a specified pin (input/output).
 *
 * This function sets the direction of the provided pin as either input or output.
 * If the port number or pin number is invalid, the function does nothing.
 *
 * @param port_num Port number (0 to NUM_OF_PORTS-1).
 * @param pin_num Pin number (0 to NUM_OF_PINS_PER_PORT-1).
 * @param direction Direction of the pin (PIN_INPUT or PIN_OUTPUT).
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num,
		GPIO_PinDirectionType direction);

/**
 * @brief Write a logical value (HIGH/LOW) to a specified pin.
 *
 * This function sets the logical value of a pin to either HIGH or LOW. If the pin is configured as input,
 * writing a value enables or disables the internal pull-up resistor.
 *
 * @param port_num Port number (0 to NUM_OF_PORTS-1).
 * @param pin_num Pin number (0 to NUM_OF_PINS_PER_PORT-1).
 * @param value Value to write (LOGIC_HIGH or LOGIC_LOW).
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);

/**
 * @brief Toggle the logical value (HIGH/LOW) to a specified pin.
 *
 * This function toggles the logical value of a pin to either HIGH or LOW. If the pin is configured as input,
 * writing a value enables or disables the internal pull-up resistor.
 *
 * @param port_num Port number (0 to NUM_OF_PORTS-1).
 * @param pin_num Pin number (0 to NUM_OF_PINS_PER_PORT-1).
 */
void GPIO_togglePin(uint8 port_num, uint8 pin_num);

/**
 * @brief Read the logical value (HIGH/LOW) of a specified pin.
 *
 * This function returns the logical value (HIGH/LOW) of the given pin. If the port number or pin number is invalid,
 * the function returns LOGIC_LOW by default.
 *
 * @param port_num Port number (0 to NUM_OF_PORTS-1).
 * @param pin_num Pin number (0 to NUM_OF_PINS_PER_PORT-1).
 * @return Value of the pin (LOGIC_HIGH or LOGIC_LOW).
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);

/**
 * @brief Configure the direction of an entire port (input/output).
 *
 * This function sets the direction of all the pins in the given port to either input or output.
 * If the port number is invalid, the function does nothing.
 *
 * @param port_num Port number (0 to NUM_OF_PORTS-1).
 * @param direction Direction of the port (PORT_INPUT or PORT_OUTPUT).
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction);

/**
 * @brief Write a value to an entire port.
 *
 * This function writes a specified value to the given port. If a pin is configured as input,
 * the value written will enable or disable the internal pull-up resistor.
 *
 * @param port_num Port number (0 to NUM_OF_PORTS-1).
 * @param value Value to write to the port (0 to 255).
 */
void GPIO_writePort(uint8 port_num, uint8 value);

/**
 * @brief Read the value of an entire port.
 *
 * This function reads the value of the specified port and returns it. If the port number is invalid,
 * the function returns 0.
 *
 * @param port_num Port number (0 to NUM_OF_PORTS-1).
 * @return Value of the port (0 to 255).
 */
uint8 GPIO_readPort(uint8 port_num);

#endif /* MCAL_GPIO_GPIO_H_ */
