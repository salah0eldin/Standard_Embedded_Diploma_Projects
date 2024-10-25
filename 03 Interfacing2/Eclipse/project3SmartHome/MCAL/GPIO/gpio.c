/******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.c
 *
 * Description: gpio driver implementation
 *
 * Created on: Sep 26, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#include "gpio.h"

/*******************************************************************************
 *                              Functions Implementation                       *
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
void GPIO_setupPinDirection (uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction)
{
  /* Check if the input port or pin number is invalid */
  if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
    {
      /* Do Nothing */
    }
  else
    {
      /* Setup the pin direction as required */
      switch (port_num)
	{
	case PORTA_ID:
	  if (direction == PIN_OUTPUT)
	    {
	      SET_BIT(DDRA, pin_num);
	    }
	  else
	    {
	      CLEAR_BIT(DDRA, pin_num);
	    }
	  break;
	case PORTB_ID:
	  if (direction == PIN_OUTPUT)
	    {
	      SET_BIT(DDRB, pin_num);
	    }
	  else
	    {
	      CLEAR_BIT(DDRB, pin_num);
	    }
	  break;
	case PORTC_ID:
	  if (direction == PIN_OUTPUT)
	    {
	      SET_BIT(DDRC, pin_num);
	    }
	  else
	    {
	      CLEAR_BIT(DDRC, pin_num);
	    }
	  break;
	case PORTD_ID:
	  if (direction == PIN_OUTPUT)
	    {
	      SET_BIT(DDRD, pin_num);
	    }
	  else
	    {
	      CLEAR_BIT(DDRD, pin_num);
	    }
	  break;
	}
    }
}

/**
 * @brief Write the value Logic High or Logic Low on the required pin.
 *
 * This function writes a logic level (HIGH/LOW) to the specified pin. If the pin is an input pin,
 * it enables or disables the internal pull-up resistor.
 *
 * @param port_num Port number (0 to NUM_OF_PORTS-1)
 * @param pin_num Pin number (0 to NUM_OF_PINS_PER_PORT-1)
 * @param value Value to write (LOGIC_HIGH or LOGIC_LOW)
 */
void GPIO_writePin (uint8 port_num, uint8 pin_num, uint8 value)
{
  /* Check if the input port or pin number is invalid */
  if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
    {
      /* Do Nothing */
    }
  else
    {
      /* Write the pin value as required */
      switch (port_num)
	{
	case PORTA_ID:
	  if (value == LOGIC_HIGH)
	    {
	      SET_BIT(PORTA, pin_num);
	    }
	  else
	    {
	      CLEAR_BIT(PORTA, pin_num);
	    }
	  break;
	case PORTB_ID:
	  if (value == LOGIC_HIGH)
	    {
	      SET_BIT(PORTB, pin_num);
	    }
	  else
	    {
	      CLEAR_BIT(PORTB, pin_num);
	    }
	  break;
	case PORTC_ID:
	  if (value == LOGIC_HIGH)
	    {
	      SET_BIT(PORTC, pin_num);
	    }
	  else
	    {
	      CLEAR_BIT(PORTC, pin_num);
	    }
	  break;
	case PORTD_ID:
	  if (value == LOGIC_HIGH)
	    {
	      SET_BIT(PORTD, pin_num);
	    }
	  else
	    {
	      CLEAR_BIT(PORTD, pin_num);
	    }
	  break;
	}
    }
}

/**
 * @brief Toggle the logical value (HIGH/LOW) to a specified pin.
 *
 * This function toggles the logical value of a pin to either HIGH or LOW. If the pin is configured as input,
 * writing a value enables or disables the internal pull-up resistor.
 *
 * @param port_num Port number (0 to NUM_OF_PORTS-1).
 * @param pin_num Pin number (0 to NUM_OF_PINS_PER_PORT-1).
 */
void GPIO_togglePin (uint8 port_num, uint8 pin_num)
{
  /* Check if the input port or pin number is invalid */
  if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
    {
      /* Do Nothing */
    }
  else
    {
      /* Write the pin value as required */
      switch (port_num)
	{
	case PORTA_ID:
	  TOGGLE_BIT(PORTA, pin_num);
	  break;
	case PORTB_ID:
	  TOGGLE_BIT(PORTB, pin_num);
	  break;
	case PORTC_ID:
	  TOGGLE_BIT(PORTC, pin_num);
	  break;
	case PORTD_ID:
	  TOGGLE_BIT(PORTD, pin_num);
	  break;
	}
    }
}

/**
 * @brief Read and return the value for the required pin.
 *
 * This function reads the logic level (HIGH/LOW) of the specified pin. If the port number or
 * pin number is invalid, it returns LOGIC_LOW by default.
 *
 * @param port_num Port number (0 to NUM_OF_PORTS-1)
 * @param pin_num Pin number (0 to NUM_OF_PINS_PER_PORT-1)
 *
 * @return Value of the pin (LOGIC_HIGH or LOGIC_LOW)
 */
uint8 GPIO_readPin (uint8 port_num, uint8 pin_num)
{
  uint8 pin_value = LOGIC_LOW;

  /* Check if the input port or pin number is invalid */
  if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
    {
      /* Do Nothing */
    }
  else
    {
      /* Read the pin value as required */
      switch (port_num)
	{
	case PORTA_ID:
	  if (BIT_IS_SET(PINA, pin_num))
	    {
	      pin_value = LOGIC_HIGH;
	    }
	  break;
	case PORTB_ID:
	  if (BIT_IS_SET(PINB, pin_num))
	    {
	      pin_value = LOGIC_HIGH;
	    }
	  break;
	case PORTC_ID:
	  if (BIT_IS_SET(PINC, pin_num))
	    {
	      pin_value = LOGIC_HIGH;
	    }
	  break;
	case PORTD_ID:
	  if (BIT_IS_SET(PIND, pin_num))
	    {
	      pin_value = LOGIC_HIGH;
	    }
	  break;
	}
    }

  return pin_value;
}

/**
 * @brief Setup the direction of the required port (all pins input/output).
 *
 * This function configures all the pins of the specified port as either input or output.
 * If the port number is invalid, the function does nothing.
 *
 * @param port_num Port number (0 to NUM_OF_PORTS-1)
 * @param direction Direction of the port (PORT_INPUT or PORT_OUTPUT)
 */
void GPIO_setupPortDirection (uint8 port_num, GPIO_PortDirectionType direction)
{
  /* Check if the input port number is invalid */
  if (port_num >= NUM_OF_PORTS)
    {
      /* Do Nothing */
    }
  else
    {
      /* Setup the port direction as required */
      switch (port_num)
	{
	case PORTA_ID:
	  DDRA = direction;
	  break;
	case PORTB_ID:
	  DDRB = direction;
	  break;
	case PORTC_ID:
	  DDRC = direction;
	  break;
	case PORTD_ID:
	  DDRD = direction;
	  break;
	}
    }
}

/**
 * @brief Write the value on the required port.
 *
 * This function writes the specified value to the port. If a pin is set as an input pin, it activates or deactivates
 * the internal pull-up resistor.
 *
 * @param port_num Port number (0 to NUM_OF_PORTS-1)
 * @param value Value to write to the port (0 to 255)
 */
void GPIO_writePort (uint8 port_num, uint8 value)
{
  /* Check if the input port number is invalid */
  if (port_num >= NUM_OF_PORTS)
    {
      /* Do Nothing */
    }
  else
    {
      /* Write the port value as required */
      switch (port_num)
	{
	case PORTA_ID:
	  PORTA = value;
	  break;
	case PORTB_ID:
	  PORTB = value;
	  break;
	case PORTC_ID:
	  PORTC = value;
	  break;
	case PORTD_ID:
	  PORTD = value;
	  break;
	}
    }
}

/**
 * @brief Read and return the value of the required port.
 *
 * This function reads the value of the specified port. If the port number is invalid, it returns 0.
 *
 * @param port_num Port number (0 to NUM_OF_PORTS-1)
 *
 * @return Value of the port (0 to 255)
 */
uint8 GPIO_readPort (uint8 port_num)
{
  uint8 value = LOGIC_LOW;

  /* Check if the input port number is invalid */
  if (port_num >= NUM_OF_PORTS)
    {
      /* Do Nothing */
    }
  else
    {
      /* Read the port value as required */
      switch (port_num)
	{
	case PORTA_ID:
	  value = PINA;
	  break;
	case PORTB_ID:
	  value = PINB;
	  break;
	case PORTC_ID:
	  value = PINC;
	  break;
	case PORTD_ID:
	  value = PIND;
	  break;
	}
    }

  return value;
}
