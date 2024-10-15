	.file	"eeprom.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	EEPROM_writeByte
	.type	EEPROM_writeByte, @function
EEPROM_writeByte:
	push r29
	push r28
	rcall .
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 4 */
	std Y+3,r25
	std Y+2,r24
	std Y+4,r22
.L2:
	ldi r30,lo8(60)
	ldi r31,hi8(60)
	ld r24,Z
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(2)
	andi r25,hi8(2)
	sbiw r24,0
	brne .L2
	ldi r30,lo8(95)
	ldi r31,hi8(95)
	ld r24,Z
	andi r24,lo8(-128)
	std Y+1,r24
	ldi r26,lo8(95)
	ldi r27,hi8(95)
	ldi r30,lo8(95)
	ldi r31,hi8(95)
	ld r24,Z
	andi r24,lo8(127)
	st X,r24
	ldi r30,lo8(62)
	ldi r31,hi8(62)
	ldd r24,Y+2
	ldd r25,Y+3
	std Z+1,r25
	st Z,r24
	ldi r30,lo8(61)
	ldi r31,hi8(61)
	ldd r24,Y+4
	st Z,r24
	ldi r26,lo8(60)
	ldi r27,hi8(60)
	ldi r30,lo8(60)
	ldi r31,hi8(60)
	ld r24,Z
	ori r24,lo8(4)
	st X,r24
	ldi r26,lo8(60)
	ldi r27,hi8(60)
	ldi r30,lo8(60)
	ldi r31,hi8(60)
	ld r24,Z
	ori r24,lo8(2)
	st X,r24
/* #APP */
 ;  40 "eeprom.c" 1
	NOP
 ;  0 "" 2
 ;  41 "eeprom.c" 1
	NOP
 ;  0 "" 2
 ;  42 "eeprom.c" 1
	NOP
 ;  0 "" 2
 ;  43 "eeprom.c" 1
	NOP
 ;  0 "" 2
/* #NOAPP */
	ldi r26,lo8(95)
	ldi r27,hi8(95)
	ldi r30,lo8(95)
	ldi r31,hi8(95)
	ld r25,Z
	ldd r24,Y+1
	or r24,r25
	st X,r24
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	EEPROM_writeByte, .-EEPROM_writeByte
.global	EEPROM_readByte
	.type	EEPROM_readByte, @function
EEPROM_readByte:
	push r29
	push r28
	rcall .
	rcall .
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 5 */
	std Y+3,r25
	std Y+2,r24
	std Y+5,r23
	std Y+4,r22
.L5:
	ldi r30,lo8(60)
	ldi r31,hi8(60)
	ld r24,Z
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(2)
	andi r25,hi8(2)
	sbiw r24,0
	brne .L5
	ldi r30,lo8(95)
	ldi r31,hi8(95)
	ld r24,Z
	andi r24,lo8(-128)
	std Y+1,r24
	ldi r26,lo8(95)
	ldi r27,hi8(95)
	ldi r30,lo8(95)
	ldi r31,hi8(95)
	ld r24,Z
	andi r24,lo8(127)
	st X,r24
	ldi r30,lo8(62)
	ldi r31,hi8(62)
	ldd r24,Y+2
	ldd r25,Y+3
	std Z+1,r25
	st Z,r24
	ldi r26,lo8(60)
	ldi r27,hi8(60)
	ldi r30,lo8(60)
	ldi r31,hi8(60)
	ld r24,Z
	ori r24,lo8(1)
	st X,r24
	ldi r30,lo8(61)
	ldi r31,hi8(61)
	ld r24,Z
	ldd r30,Y+4
	ldd r31,Y+5
	st Z,r24
/* #APP */
 ;  70 "eeprom.c" 1
	NOPs
 ;  0 "" 2
 ;  71 "eeprom.c" 1
	NOP
 ;  0 "" 2
/* #NOAPP */
	ldi r26,lo8(95)
	ldi r27,hi8(95)
	ldi r30,lo8(95)
	ldi r31,hi8(95)
	ld r25,Z
	ldd r24,Y+1
	or r24,r25
	st X,r24
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	EEPROM_readByte, .-EEPROM_readByte
