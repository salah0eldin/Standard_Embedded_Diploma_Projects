/******************************************************************************
 * File Name: std_types.h
 *
 * Description: Standard data types definitions for use across the project.
 *              Includes common boolean values and standard integer/floating-point
 *              data types.
 *
 * Created on: Sep 26, 2024
 *
 * Author: Salah-Eldin
 *******************************************************************************/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
/* Standard null pointer macro */
#include <stddef.h>

/*******************************************************************************
 *                                Data Types                                   *
 *******************************************************************************/

/* Boolean Data Type */
typedef unsigned char boolean;  /* Represents boolean values (TRUE/FALSE) */

/*******************************************************************************
 *                                Boolean Values                               *
 *******************************************************************************/

/* Define standard FALSE and TRUE values if not already defined */
#ifndef FALSE
#define FALSE           (0u)   /**< False value (0) */
#endif

#ifndef TRUE
#define TRUE            (1u)   /**< True value (1) */
#endif

/* Logical high and low definitions */
#define LOGIC_HIGH      (1u)   /**< Logical high (1) */
#define LOGIC_LOW       (0u)   /**< Logical low (0) */

/* Null pointer definition */
#define NULL_PTR        ((void*)0) /**< Null pointer macro */

/*******************************************************************************
 *                         Standard Integer Types                              *
 *******************************************************************************/

/* Unsigned and signed 8-bit integer */
typedef unsigned char         uint8;    /**< Unsigned 8-bit integer (0 to 255) */
typedef signed char           sint8;    /**< Signed 8-bit integer (-128 to +127) */

/* Unsigned and signed 16-bit integer */
typedef unsigned short        uint16;   /**< Unsigned 16-bit integer (0 to 65535) */
typedef signed short          sint16;   /**< Signed 16-bit integer (-32768 to +32767) */

/* Unsigned and signed 32-bit integer */
typedef unsigned long         uint32;   /**< Unsigned 32-bit integer (0 to 4294967295) */
typedef signed long           sint32;   /**< Signed 32-bit integer (-2147483648 to +2147483647) */

/* Unsigned and signed 64-bit integer */
typedef unsigned long long    uint64;   /**< Unsigned 64-bit integer (0 to 18446744073709551615) */
typedef signed long long      sint64;   /**< Signed 64-bit integer (-9223372036854775808 to +9223372036854775807) */

/*******************************************************************************
 *                         Floating Point Types                                *
 *******************************************************************************/

/* Floating-point types */
typedef float                 float32;  /**< 32-bit floating point number */
typedef double                float64;  /**< 64-bit floating point number */

#endif /* STD_TYPES_H_ */
