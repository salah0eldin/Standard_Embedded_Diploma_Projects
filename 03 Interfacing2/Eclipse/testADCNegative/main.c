/******************************************************************************
 *
 * File Name: main.c
 *
 * Description: Main file for the ADC to LCD display application.
 *
 * Created on: Sep 26, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

// Include necessary header files for LCD, GPIO, and ADC functionalities
#include "ECU/LCD/lcd.h"
#include "MCAL/GPIO/gpio.h"
#include "MCAL/ADC/adc.h"

// Include delay utility for managing timing
#include <util/delay.h>

volatile uint8 adcFlag = 0;

void adcInterruptHandler(void) {
	adcFlag = 1;
}

/** Initialize ADC configuration object. */
ADC_t adc_obj = { .vreffSource = ADC_SOURCE_INTERNAL_2560MV, /** Set reference voltage to internal 2.56V */
.prescaller = ADC_PRE_FOSC_DIV_128, /** Set prescaler to divide by 128 for ADC clock */
.interruptHandler = adcInterruptHandler };

/** Main function. */
int main(void) {
	/** Initialize the ADC module with the specified settings */
	ADC_init(&adc_obj);

	/** Initialize the LCD display */
	LCD_init();

	SREGbits.i = 1;

	uint16 value = 0; /** Variable to store ADC reading */

	/** Infinite loop for continuous operation */
	for (;;) {
		/** Read the value from ADC channel 0 (ADC0) */
		ADC_readChannel(ADC_CHANNEL_ADC0_ADC1_G1);

		if (adcFlag) {
			adcFlag = 0;

			value = ADC;

			/** Move the cursor to the first line of the LCD */
			LCD_moveCursor(0, 0);

			/** Display the label for the value */
			LCD_displayString("val = ");

			/** Convert ADC value to mV and display it on the LCD */
			LCD_displayNumber(-(sint32) value * 2560 / 1024);

			/** Display " mV" to indicate the unit of measurement */
			LCD_displayString(" mV     ");
		}
		/** Delay for 100 milliseconds before the next reading */
		_delay_ms(100);
	}
}
