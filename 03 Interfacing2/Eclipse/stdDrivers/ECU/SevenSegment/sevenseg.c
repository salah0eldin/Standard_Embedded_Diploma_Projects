/******************************************************************************
 * Module: Seven-Segment Display
 *
 * File Name: sevenseg.c
 *
 * Description: Source file for Seven-Segment Display driver.
 *              It contains the implementation for initializing and displaying
 *              numbers on the seven-segment display.
 *
 * Created on: Sep 27, 2024
 *
 * Author: Salah-Eldin
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "sevenseg.h"
#include "sevenseg_cfg.h"
#include "../../MCAL/GPIO/gpio.h"

/*******************************************************************************
 *                                Global Variables                             *
 *******************************************************************************/

/* Initialize the port and pin mappings based on the configuration in the header */
static uint8 SEVENSEG_portMapping[SEVENSEG_PINS_NUM] = SEVENSEG_PORT_MAPPING;
static uint8 SEVENSEG_pinMapping[SEVENSEG_PINS_NUM] = SEVENSEG_PIN_MAPPING;

#if defined(SEVENSEG_NORMAL_COMMON_ANODE_TYPE) || defined(SEVENSEG_NORMAL_COMMON_CATHODE_TYPE)
/* Bit-mapping for numbers 0-9 on a seven-segment display */
static uint8 SEVENSEG_bitMapping[] = {
		0b01111110, /* 0 */
		0b00001100, /* 1 */
		0b10110110, /* 2 */
		0b10011110, /* 3 */
		0b11001100, /* 4 */
		0b11011010, /* 5 */
		0b11111010, /* 6 */
		0b00001110, /* 7 */
		0b11111110, /* 8 */
		0b11101110 /* 9 */
};
#endif

/*******************************************************************************
 *                                Functions                                    *
 *******************************************************************************/

/**
 * @brief Initialize the seven-segment display.
 *
 * This function configures the pins used for the seven-segment display as output.
 * It uses the configuration specified in the header file (port and pin mapping).
 */
void SEVENSEG_init(void) {
	uint8 it = 0;

	/* Loop through all the pins and set their direction as output */
	for (; it < SEVENSEG_PINS_NUM; it++) {
		GPIO_setupPinDirection(SEVENSEG_portMapping[it],
				SEVENSEG_pinMapping[it], PIN_OUTPUT);
	}
}

/**
 * @brief Display a number on the seven-segment display.
 *
 * This function takes a number (0-9) and displays it on the seven-segment display
 * by writing the appropriate segment values to the corresponding GPIO pins.
 *
 * @param[in] num: The number to display (valid range: 0-9).
 */
void SEVENSEG_display(uint8 num) {
	uint8 it = 0;

	if (num > 9) {
	    return;  /* Invalid number, return without doing anything */
	}

#if defined(SEVENSEG_DECODER_TYPE)
    /* If using a decoder, only 4 pins are needed to represent the number */
    for (; it < SEVENSEG_PINS_NUM; it++) {
        GPIO_writePin(SEVENSEG_portMapping[it], SEVENSEG_pinMapping[it], GET_BIT(num, it));
    }

#elif defined(SEVENSEG_NORMAL_COMMON_ANODE_TYPE)
    /* For common anode displays, invert the output (logic 1 = segment OFF) */
    for (; it < SEVENSEG_PINS_NUM; it++) {
        GPIO_writePin(SEVENSEG_portMapping[it], SEVENSEG_pinMapping[it], !GET_BIT(SEVENSEG_bitMapping[num], it + 1));
    }

#elif defined(SEVENSEG_NORMAL_COMMON_CATHODE_TYPE)
	/* For common cathode displays, direct logic (logic 1 = segment ON) */
	for (; it < SEVENSEG_PINS_NUM; it++) {
		GPIO_writePin(SEVENSEG_portMapping[it], SEVENSEG_pinMapping[it],
				GET_BIT(SEVENSEG_bitMapping[num], (it + 1)));
	}

#endif
}
