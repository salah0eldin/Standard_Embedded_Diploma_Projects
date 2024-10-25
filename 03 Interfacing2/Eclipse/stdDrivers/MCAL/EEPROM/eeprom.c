/* this module doesn't work
*****************************************************************************
 *
 * Module: EEPROM
 *
 * File Name: eeprom.c
 *
 * Description: 
 *
 * Created on: Oct 10, 2024
 *
 * Author: Salah-Eldin
 *
 ******************************************************************************

#include "eeprom.h"
#include <avr/io.h>

void EEPROM_writeByte(uint16 addr, uint8 data) {

   Wait for completion of previous write
  while (EECR & (1 << EEWE))
    ;

   Store i bit state
  uint8 iBit = SREG & 0x80;

   Ensure interrupts are disabled
  SREG &= 0x7F;

   Set up address and data registers
  EEAR = addr;
  EEDR = data;

   Write logical one to EEMWE
  EECR |= (1 << EEMWE);

   Start EEPROM write by setting EEWE
  EECR |= (1 << EEWE);

  __asm__("NOP");
  __asm__("NOP");
  __asm__("NOP");

   Regain previous i Bit state
  SREG |= iBit;
}

void EEPROM_readByte(uint16 addr, uint8 *data) {

   Wait for completion of previous write
  while (EECR & (1 << EEWE))
    ;

   Store i bit state
  uint8 iBit = SREG & 0x80;

   Ensure interrupts are disabled
  SREG &= 0x7F;

   Set up address register
  EEAR = addr;

   Start EEPROM read by writing EERE
  EECR |= (1 << EERE);

   Return data from data register
  *data = EEDR;

  __asm__("NOP");
  __asm__("NOP");

   Regain previous i Bit state
  SREG |= iBit;
}
*/
