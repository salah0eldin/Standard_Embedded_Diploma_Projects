/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Implementation of the ADC driver functions.
 *
 * Created on: Sep 28, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "adc.h"
#include "../GPIO/gpio.h"
#include "../common_macros.h"
#include <avr/interrupt.h>

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
uint16 g_adc_result = 0; // Global variable to store ADC result


ADC_t g_adc1 = {
    .vreffSource = ADC_SOURCE_INTERNAL_2560MV,
    .prescaller = ADC_PRE_FOSC_DIV_128
};

#ifdef ADC_ENABLE_INTERRUPT
static void (*ADC_interruptHandler)(void) = NULL_PTR; // Pointer to interrupt handler
#endif

/*******************************************************************************
 *                              Functions Implementation                        *
 *******************************************************************************/

/*
 * Description:
 * Initializes the ADC according to the configuration settings in the ADC_t structure.
 */
void ADC_init(ADC_t *adc_obj) {
	/* Disable the ADC */
	CLEAR_BIT(ADCSRA, ADEN);

	/* Set Voltage Reference Source */
	ADMUXbits.refs = adc_obj->vreffSource;

	/* Set ADC Prescaler */
	ADCSRAbits.adps = adc_obj->prescaller;

	/* Configure Interrupts */
#ifdef ADC_ENABLE_INTERRUPT
	SET_BIT(ADCSRA, ADIE); // Enable ADC interrupt
	ADC_interruptHandler = adc_obj->interruptHandler; // Set interrupt handler
#endif

	/* Enable the ADC */
	SET_BIT(ADCSRA, ADEN);
}

/*
 * Description:
 * Starts ADC conversion on a specific channel without blocking.
 */
boolean ADC_readChannel(uint8 channel) {

	uint8 ret = 1;

	if (ADC_isDone()) {
		/* Set the ADC channel */
		ADMUXbits.mux = channel;

		/* Start ADC Conversion */
		SET_BIT(ADCSRA, ADSC);
	} else {
		ret = 0;
	}
	return ret;
}

/*
 * Description:
 * Starts ADC conversion on a specific channel and waits for conversion to complete.
 * Returns the converted value.
 */
uint16 ADC_readChannelBlocking(uint8 channel) {
	/* Start conversion */
	ADC_readChannel(channel);

	/* Wait while conversion is in progress */
	while (!GET_BIT(ADCSRA, ADIF))
		;

#ifndef ADC_ENABLE_INTERRUPT
	/* Clear flag after conversion */
	SET_BIT(ADCSRA, ADIF);
#endif

	/* Return the ADC result */
	return ADC;
}

/*******************************************************************************
 *                             Interrupt Service Routine                        *
 *******************************************************************************/
#ifdef ADC_ENABLE_INTERRUPT
ISR(ADC_vect) {
	if(NULL_PTR != ADC_interruptHandler)
		(*ADC_interruptHandler)(); // Call the registered interrupt handler
}
#endif
