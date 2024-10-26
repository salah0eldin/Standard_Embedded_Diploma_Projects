/******************************************************************************
 * Module: Seven-Segment Display
 *
 * File Name: sevenseg_cfg.h
 *
 * Description: Configuration file for Seven-Segment Display module.
 *              It defines segment type, port and pin mappings to be used
 *              across the application.
 *
 * Created on: Sep 27, 2024
 *
 * Author: Salah-Eldin
 *******************************************************************************/

#ifndef ECU_SEVENSEGMENT_SEVENSEG_CFG_H_
#define ECU_SEVENSEGMENT_SEVENSEG_CFG_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../LIB/std_types.h"
#include "../../MCAL/GPIO/gpio.h"

/*******************************************************************************
 *                           Configuration Macros                              *
 *******************************************************************************/

/* Un-comment the type of seven-segment display you're using and comment the rest.
 * SEVENSEG_DECODER_TYPE: If you're using a decoder like 74LS47
 * SEVENSEG_NORMAL_COMMON_ANODE_TYPE: For normal common anode display
 * SEVENSEG_NORMAL_COMMON_CATHODE_TYPE: For normal common cathode display
 */

//#define SEVENSEG_DECODER_TYPE
//#define SEVENSEG_NORMAL_COMMON_ANODE_TYPE
#define SEVENSEG_NORMAL_COMMON_CATHODE_TYPE  /* Using common cathode display */

/* Define the number of pins based on the seven-segment type */
#if defined(SEVENSEG_DECODER_TYPE)
#define SEVENSEG_PINS_NUM    4  /* 4 pins for decoder type */
#elif defined(SEVENSEG_NORMAL_COMMON_ANODE_TYPE) || defined(SEVENSEG_NORMAL_COMMON_CATHODE_TYPE)
#define SEVENSEG_PINS_NUM    7  /* 7 pins for normal seven-segment display */
#else
#define SEVENSEG_PINS_NUM    0  /* Invalid configuration */
#endif

/*******************************************************************************
 *                     Seven-Segment Pin/Port Configuration                    *
 *******************************************************************************/

/* Port mapping: Defines which port is used for each segment pin.
 * Example: For a common cathode seven-segment display connected to PORTA
 * with each segment connected to pin 1 through pin 7, you can adjust as needed.
 */
#define SEVENSEG_PORT_MAPPING { PORTA_ID, PORTA_ID, PORTA_ID, PORTA_ID, \
                                PORTA_ID, PORTA_ID, PORTA_ID }

/* Pin mapping: Defines which pin of the port is connected to each segment.
 * Example: Segment a -> Pin 1, Segment b -> Pin 2, etc.
 */
#define SEVENSEG_PIN_MAPPING  { 1, 2, 3, 4, 5, 6, 7 }

#endif /* ECU_SEVENSEGMENT_SEVENSEG_CFG_H_ */
