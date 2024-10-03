/******************************************************************************
 *
 * File Name: common_macros.h
 *
 * Description: Common bit manipulation macros for registers.
 *              Includes setting, clearing, toggling, and rotating bits.
 *
 * Created on: Sep 26, 2024
 *
 * Author: Salah-Eldin
 *
 *******************************************************************************/

#ifndef MCAL_COMMON_MACROS_H_
#define MCAL_COMMON_MACROS_H_

/*******************************************************************************
 *                                Macros                                       *
 *******************************************************************************/

/**
 * @brief Set a specific bit in a register.
 * @param REG Register to modify.
 * @param BIT Bit position to set (0-based).
 */
#define SET_BIT(REG, BIT)     (REG |= (1 << BIT))

/**
 * @brief Clear a specific bit in a register.
 * @param REG Register to modify.
 * @param BIT Bit position to clear (0-based).
 */
#define CLEAR_BIT(REG, BIT)   (REG &= ~(1 << BIT))

/**
 * @brief Set or clear a specific bit based on a logic value (0 or 1).
 * @param REG Register to modify.
 * @param BIT Bit position to modify (0-based).
 * @param LOGIC Logical value (0 or 1) to set the bit.
 */
#define PUT_BIT(REG, BIT, LOGIC)  (REG = ((REG & (~(1 << BIT))) | (LOGIC << BIT)))

/**
 * @brief Toggle a specific bit in a register.
 * @param REG Register to modify.
 * @param BIT Bit position to toggle (0-based).
 */
#define TOGGLE_BIT(REG, BIT)  (REG ^= (1 << BIT))

/**
 * @brief Get the value of a specific bit in a register.
 * @param REG Register to read.
 * @param BIT Bit position to get (0-based).
 * @return The value of the bit (0 or 1).
 */
#define GET_BIT(REG, BIT)     ((REG >> BIT) & 1)

/**
 * @brief Rotate a register value to the right by a specified number of bits.
 * @param REG Register to rotate.
 * @param num Number of bit positions to rotate.
 */
#define ROR(REG, num)         (REG = (REG >> num) | (REG << (8 - num)))

/**
 * @brief Rotate a register value to the left by a specified number of bits.
 * @param REG Register to rotate.
 * @param num Number of bit positions to rotate.
 */
#define ROL(REG, num)         (REG = (REG << num) | (REG >> (8 - num)))

/**
 * @brief Check if a specific bit is set in a register.
 * @param REG Register to check.
 * @param BIT Bit position to check (0-based).
 * @return true (non-zero) if the bit is set, false (0) otherwise.
 */
#define BIT_IS_SET(REG, BIT)  (REG & (1 << BIT))

/**
 * @brief Check if a specific bit is cleared in a register.
 * @param REG Register to check.
 * @param BIT Bit position to check (0-based).
 * @return true (non-zero) if the bit is cleared, false (0) otherwise.
 */
#define BIT_IS_CLEAR(REG, BIT)    (!(REG & (1 << BIT)))

#endif /* MCAL_COMMON_MACROS_H_ */
