/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: Header file for the ADC driver.
 *
 * Created on: Sep 28, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../LIB/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

//#define ADC_ENABLE_INTERRUPT

#define ADC_MAXIMUM_VALUE    	1023
#define ADC_REF_VOLT_VALUE	2.56

/*******************************************************************************
 *                                Macro Functions                              *
 *******************************************************************************/

#define ADC_isDone()  (!GET_BIT(ADCSRA, ADSC))

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

extern uint16 g_adc_result;

/*******************************************************************************
 *                              Types Declaration                              *
 *******************************************************************************/

/* ADC Channel and Gain Configuration */
typedef enum {
	ADC_CHANNEL_ADC0,                /* Single Ended pin A0 */
	ADC_CHANNEL_ADC1,                /* Single Ended pin A1 */
	ADC_CHANNEL_ADC2,                /* Single Ended pin A2 */
	ADC_CHANNEL_ADC3,                /* Single Ended pin A3 */
	ADC_CHANNEL_ADC4,                /* Single Ended pin A4 */
	ADC_CHANNEL_ADC5,                /* Single Ended pin A5 */
	ADC_CHANNEL_ADC6,                /* Single Ended pin A6 */
	ADC_CHANNEL_ADC7,                /* Single Ended pin A7 */

	/************************************************
	 *  Differential channels:
	 *  First is the positive terminal and
	 *  second is the negative terminal with Gain GN
	 ************************************************/
	ADC_CHANNEL_ADC0_ADC0_G10,
	ADC_CHANNEL_ADC1_ADC0_G10,
	ADC_CHANNEL_ADC0_ADC0_G200,
	ADC_CHANNEL_ADC1_ADC0_G200,
	ADC_CHANNEL_ADC2_ADC2_G10,
	ADC_CHANNEL_ADC3_ADC2_G10,
	ADC_CHANNEL_ADC2_ADC2_G200,
	ADC_CHANNEL_ADC3_ADC2_G200,
	ADC_CHANNEL_ADC0_ADC1_G1,
	ADC_CHANNEL_ADC1_ADC1_G1,
	ADC_CHANNEL_ADC2_ADC1_G1,
	ADC_CHANNEL_ADC3_ADC1_G1,
	ADC_CHANNEL_ADC4_ADC1_G1,
	ADC_CHANNEL_ADC5_ADC1_G1,
	ADC_CHANNEL_ADC6_ADC1_G1,
	ADC_CHANNEL_ADC7_ADC1_G1,
	ADC_CHANNEL_ADC0_ADC2_G1,
	ADC_CHANNEL_ADC1_ADC2_G1,
	ADC_CHANNEL_ADC2_ADC2_G1,
	ADC_CHANNEL_ADC3_ADC2_G1,
	ADC_CHANNEL_ADC4_ADC2_G1,
	ADC_CHANNEL_ADC5_ADC2_G1,

	/* Special Testing Channels */
	ADC_CHANNEL_VBG_1V22,
	ADC_CHANNEL_GNC_0V
} ADC_channelGain_t;

/* ADC Voltage Reference Source */
typedef enum {
	ADC_SOURCE_VREFF = 0,            /* AREF, Internal Vref turned off */
	ADC_SOURCE_AVCC = 1,             /* AVCC with external capacitor at AREF pin */
	ADC_SOURCE_INTERNAL_2560MV = 3   /* Internal 2.56V Voltage Reference with external capacitor at AREF pin */
} ADC_vreffSource_t;

/* ADC Prescaler Options */
typedef enum {
	ADC_PRE_FOSC_DIV_2 = 0,
	ADC_PRE_FOSC_DIV_4 = 2,
	ADC_PRE_FOSC_DIV_8,
	ADC_PRE_FOSC_DIV_16,
	ADC_PRE_FOSC_DIV_32,
	ADC_PRE_FOSC_DIV_64,
	ADC_PRE_FOSC_DIV_128
} ADC_prescaller_t;

/* ADC Configuration Structure */
typedef struct {
	uint8 vreffSource : 2;           /* Voltage Reference Source (2 bits) */
	uint8 prescaller  : 3;           /* ADC Prescaler (3 bits) */
} ADC_t;

extern ADC_t g_adc1;

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * @brief Initializes the ADC according to the configuration settings in the ADC_t structure.
 *
 * This function sets up the ADC hardware module using the provided configuration structure,
 * allowing it to be ready for use.
 *
 * @param adc_obj Pointer to a structure of type `ADC_t` that holds the configuration settings for the ADC.
 */
void ADC_init(ADC_t * adc_obj);

#ifdef ADC_ENABLE_INTERRUPT

/**
 * @brief Sets the interrupt handler for ADC conversions.
 *
 * This function allows the user to define a custom interrupt handler function that
 * will be called when an ADC conversion completes. This is only available if
 * `ADC_ENABLE_INTERRUPT` is defined.
 *
 * @param interruptHandler Pointer to the function that will handle the ADC interrupt.
 */
void ADC_setInterruptHandler(void(*interruptHandler)(void));

#endif /* ADC_ENABLE_INTERRUPT */

/**
 * @brief Starts ADC conversion on a specific channel without blocking.
 *
 * This function initiates an ADC conversion on the specified channel and immediately returns.
 * It does not wait for the conversion to complete. The result can be retrieved later.
 *
 * @param channel The channel number on which to perform the ADC conversion.
 * @return `boolean` indicating whether the operation was successful.
 */
boolean ADC_readChannel(uint8 channel);

/**
 * @brief Starts ADC conversion on a specific channel and waits for the conversion to complete.
 *
 * This function starts an ADC conversion on the specified channel and waits until the conversion is done.
 * The converted value is returned after the operation completes.
 *
 * @param channel The channel number on which to perform the ADC conversion.
 * @return `uint16` The result of the ADC conversion.
 */
uint16 ADC_readChannelBlocking(uint8 channel);


#endif /* MCAL_ADC_ADC_H_ */
