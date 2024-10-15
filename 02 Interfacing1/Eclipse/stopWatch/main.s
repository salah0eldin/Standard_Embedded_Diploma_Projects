	.file	"main.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
.global	timer1_ticks
.global	timer1_ticks
	.section .bss
	.type	timer1_ticks, @object
	.size	timer1_ticks, 1
timer1_ticks:
	.skip 1,0
.global	paused
.global	paused
	.type	paused, @object
	.size	paused, 1
paused:
	.skip 1,0
.global	mode
.global	mode
	.type	mode, @object
	.size	mode, 1
mode:
	.skip 1,0
	.text
.global	main
	.type	main, @function
main:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	call leds_init
	call buzzer_init
	call seven_segment_pins_init
	call adjust_time_buttons_init
	call count_mode_button_init
	call reset_button_int0_init
	call pause_button_int1_init
	call resume_button_int2_init
	call timer1_init
/* #APP */
 ;  135 "main.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
.L6:
	call display_time
	lds r24,timer1_ticks
	tst r24
	breq .L2
	lds r24,timer1_ticks
	subi r24,lo8(-(-1))
	sts timer1_ticks,r24
	call update_time
.L2:
	call check_update_mode
	lds r24,paused
	tst r24
	brne .L3
	lds r24,mode
	cpi r24,lo8(1)
	brne .L3
	lds r24,time
	lds r25,(time)+1
	lds r26,(time)+2
	lds r27,(time)+3
	sbiw r24,0
	cpc r26,__zero_reg__
	cpc r27,__zero_reg__
	brne .L3
	ldi r26,lo8(50)
	ldi r27,hi8(50)
	ldi r30,lo8(50)
	ldi r31,hi8(50)
	ld r24,Z
	ori r24,lo8(1)
	st X,r24
	rjmp .L4
.L3:
	ldi r26,lo8(50)
	ldi r27,hi8(50)
	ldi r30,lo8(50)
	ldi r31,hi8(50)
	ld r24,Z
	andi r24,lo8(-2)
	st X,r24
.L4:
	lds r24,paused
	tst r24
	breq .L6
	call handle_hours_change_buttons
	call handle_minutes_change_buttons
	call handle_seconds_change_buttons
	rjmp .L6
	.size	main, .-main
	.type	leds_init, @function
leds_init:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r26,lo8(49)
	ldi r27,hi8(49)
	ldi r30,lo8(49)
	ldi r31,hi8(49)
	ld r24,Z
	ori r24,lo8(48)
	st X,r24
	ldi r26,lo8(50)
	ldi r27,hi8(50)
	ldi r30,lo8(50)
	ldi r31,hi8(50)
	ld r24,Z
	andi r24,lo8(-49)
	ori r24,lo8(16)
	st X,r24
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	leds_init, .-leds_init
	.type	buzzer_init, @function
buzzer_init:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r26,lo8(49)
	ldi r27,hi8(49)
	ldi r30,lo8(49)
	ldi r31,hi8(49)
	ld r24,Z
	ori r24,lo8(1)
	st X,r24
	ldi r26,lo8(50)
	ldi r27,hi8(50)
	ldi r30,lo8(50)
	ldi r31,hi8(50)
	ld r24,Z
	andi r24,lo8(-2)
	st X,r24
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	buzzer_init, .-buzzer_init
	.type	seven_segment_pins_init, @function
seven_segment_pins_init:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r26,lo8(52)
	ldi r27,hi8(52)
	ldi r30,lo8(52)
	ldi r31,hi8(52)
	ld r24,Z
	ori r24,lo8(15)
	st X,r24
	ldi r26,lo8(53)
	ldi r27,hi8(53)
	ldi r30,lo8(53)
	ldi r31,hi8(53)
	ld r24,Z
	andi r24,lo8(-16)
	st X,r24
	ldi r26,lo8(58)
	ldi r27,hi8(58)
	ldi r30,lo8(58)
	ldi r31,hi8(58)
	ld r24,Z
	ori r24,lo8(63)
	st X,r24
	ldi r26,lo8(59)
	ldi r27,hi8(59)
	ldi r30,lo8(59)
	ldi r31,hi8(59)
	ld r24,Z
	andi r24,lo8(-64)
	st X,r24
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	seven_segment_pins_init, .-seven_segment_pins_init
	.type	adjust_time_buttons_init, @function
adjust_time_buttons_init:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r26,lo8(55)
	ldi r27,hi8(55)
	ldi r30,lo8(55)
	ldi r31,hi8(55)
	ld r24,Z
	andi r24,lo8(-124)
	st X,r24
	ldi r26,lo8(56)
	ldi r27,hi8(56)
	ldi r30,lo8(56)
	ldi r31,hi8(56)
	ld r24,Z
	ori r24,lo8(123)
	st X,r24
	sts flags,__zero_reg__
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	adjust_time_buttons_init, .-adjust_time_buttons_init
	.type	count_mode_button_init, @function
count_mode_button_init:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r26,lo8(55)
	ldi r27,hi8(55)
	ldi r30,lo8(55)
	ldi r31,hi8(55)
	ld r24,Z
	andi r24,lo8(127)
	st X,r24
	ldi r26,lo8(56)
	ldi r27,hi8(56)
	ldi r30,lo8(56)
	ldi r31,hi8(56)
	ld r24,Z
	ori r24,lo8(-128)
	st X,r24
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	count_mode_button_init, .-count_mode_button_init
	.type	reset_button_int0_init, @function
reset_button_int0_init:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r26,lo8(49)
	ldi r27,hi8(49)
	ldi r30,lo8(49)
	ldi r31,hi8(49)
	ld r24,Z
	andi r24,lo8(-5)
	st X,r24
	ldi r26,lo8(50)
	ldi r27,hi8(50)
	ldi r30,lo8(50)
	ldi r31,hi8(50)
	ld r24,Z
	ori r24,lo8(4)
	st X,r24
	ldi r26,lo8(91)
	ldi r27,hi8(91)
	ldi r30,lo8(91)
	ldi r31,hi8(91)
	ld r24,Z
	ori r24,lo8(64)
	st X,r24
	ldi r26,lo8(85)
	ldi r27,hi8(85)
	ldi r30,lo8(85)
	ldi r31,hi8(85)
	ld r24,Z
	ori r24,lo8(2)
	st X,r24
	ldi r26,lo8(90)
	ldi r27,hi8(90)
	ldi r30,lo8(90)
	ldi r31,hi8(90)
	ld r24,Z
	ori r24,lo8(64)
	st X,r24
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	reset_button_int0_init, .-reset_button_int0_init
	.type	pause_button_int1_init, @function
pause_button_int1_init:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r26,lo8(49)
	ldi r27,hi8(49)
	ldi r30,lo8(49)
	ldi r31,hi8(49)
	ld r24,Z
	andi r24,lo8(-9)
	st X,r24
	ldi r26,lo8(91)
	ldi r27,hi8(91)
	ldi r30,lo8(91)
	ldi r31,hi8(91)
	ld r24,Z
	ori r24,lo8(-128)
	st X,r24
	ldi r26,lo8(85)
	ldi r27,hi8(85)
	ldi r30,lo8(85)
	ldi r31,hi8(85)
	ld r24,Z
	ori r24,lo8(12)
	st X,r24
	ldi r26,lo8(90)
	ldi r27,hi8(90)
	ldi r30,lo8(90)
	ldi r31,hi8(90)
	ld r24,Z
	ori r24,lo8(-128)
	st X,r24
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	pause_button_int1_init, .-pause_button_int1_init
	.type	resume_button_int2_init, @function
resume_button_int2_init:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r26,lo8(55)
	ldi r27,hi8(55)
	ldi r30,lo8(55)
	ldi r31,hi8(55)
	ld r24,Z
	andi r24,lo8(-5)
	st X,r24
	ldi r26,lo8(56)
	ldi r27,hi8(56)
	ldi r30,lo8(56)
	ldi r31,hi8(56)
	ld r24,Z
	ori r24,lo8(4)
	st X,r24
	ldi r26,lo8(91)
	ldi r27,hi8(91)
	ldi r30,lo8(91)
	ldi r31,hi8(91)
	ld r24,Z
	ori r24,lo8(32)
	st X,r24
	ldi r26,lo8(90)
	ldi r27,hi8(90)
	ldi r30,lo8(90)
	ldi r31,hi8(90)
	ld r24,Z
	ori r24,lo8(32)
	st X,r24
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	resume_button_int2_init, .-resume_button_int2_init
	.type	timer1_init, @function
timer1_init:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r26,lo8(78)
	ldi r27,hi8(78)
	ldi r30,lo8(78)
	ldi r31,hi8(78)
	ld r24,Z
	ori r24,lo8(13)
	st X,r24
	ldi r30,lo8(76)
	ldi r31,hi8(76)
	std Z+1,__zero_reg__
	st Z,__zero_reg__
	ldi r30,lo8(74)
	ldi r31,hi8(74)
	ldi r24,lo8(15624)
	ldi r25,hi8(15624)
	std Z+1,r25
	st Z,r24
	ldi r26,lo8(89)
	ldi r27,hi8(89)
	ldi r30,lo8(89)
	ldi r31,hi8(89)
	ld r24,Z
	ori r24,lo8(16)
	st X,r24
	sts time+6,__zero_reg__
	sts time+5,__zero_reg__
	sts time+4,__zero_reg__
	sts time,__zero_reg__
	sts (time)+1,__zero_reg__
	sts (time)+2,__zero_reg__
	sts (time)+3,__zero_reg__
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	timer1_init, .-timer1_init
.global	__vector_7
	.type	__vector_7, @function
__vector_7:
	push __zero_reg__
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r24
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: Signal */
/* frame size = 0 */
	lds r24,timer1_ticks
	subi r24,lo8(-(1))
	sts timer1_ticks,r24
/* epilogue start */
	pop r28
	pop r29
	pop r24
	pop r0
	out __SREG__,r0
	pop r0
	pop __zero_reg__
	reti
	.size	__vector_7, .-__vector_7
.global	__vector_1
	.type	__vector_1, @function
__vector_1:
	push __zero_reg__
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r30
	push r31
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: Signal */
/* frame size = 0 */
	sts time,__zero_reg__
	sts (time)+1,__zero_reg__
	sts (time)+2,__zero_reg__
	sts (time)+3,__zero_reg__
	sts time+6,__zero_reg__
	sts time+5,__zero_reg__
	sts time+4,__zero_reg__
	sts timer1_ticks,__zero_reg__
	ldi r30,lo8(76)
	ldi r31,hi8(76)
	std Z+1,__zero_reg__
	st Z,__zero_reg__
/* epilogue start */
	pop r28
	pop r29
	pop r31
	pop r30
	pop r0
	out __SREG__,r0
	pop r0
	pop __zero_reg__
	reti
	.size	__vector_1, .-__vector_1
.global	__vector_2
	.type	__vector_2, @function
__vector_2:
	push __zero_reg__
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r24
	push r26
	push r27
	push r30
	push r31
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: Signal */
/* frame size = 0 */
	ldi r24,lo8(1)
	sts paused,r24
	ldi r26,lo8(78)
	ldi r27,hi8(78)
	ldi r30,lo8(78)
	ldi r31,hi8(78)
	ld r24,Z
	andi r24,lo8(-6)
	st X,r24
/* epilogue start */
	pop r28
	pop r29
	pop r31
	pop r30
	pop r27
	pop r26
	pop r24
	pop r0
	out __SREG__,r0
	pop r0
	pop __zero_reg__
	reti
	.size	__vector_2, .-__vector_2
.global	__vector_3
	.type	__vector_3, @function
__vector_3:
	push __zero_reg__
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r24
	push r26
	push r27
	push r30
	push r31
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: Signal */
/* frame size = 0 */
	sts paused,__zero_reg__
	ldi r26,lo8(78)
	ldi r27,hi8(78)
	ldi r30,lo8(78)
	ldi r31,hi8(78)
	ld r24,Z
	ori r24,lo8(5)
	st X,r24
/* epilogue start */
	pop r28
	pop r29
	pop r31
	pop r30
	pop r27
	pop r26
	pop r24
	pop r0
	out __SREG__,r0
	pop r0
	pop __zero_reg__
	reti
	.size	__vector_3, .-__vector_3
	.type	update_time, @function
update_time:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	lds r24,mode
	tst r24
	brne .L35
	lds r24,time
	lds r25,(time)+1
	lds r26,(time)+2
	lds r27,(time)+3
	cpi r24,lo8(86399)
	ldi r18,hi8(86399)
	cpc r25,r18
	ldi r18,hlo8(86399)
	cpc r26,r18
	ldi r18,hhi8(86399)
	cpc r27,r18
	brsh .L36
	lds r24,time
	lds r25,(time)+1
	lds r26,(time)+2
	lds r27,(time)+3
	adiw r24,1
	adc r26,__zero_reg__
	adc r27,__zero_reg__
	sts time,r24
	sts (time)+1,r25
	sts (time)+2,r26
	sts (time)+3,r27
	rjmp .L38
.L36:
	sts time,__zero_reg__
	sts (time)+1,__zero_reg__
	sts (time)+2,__zero_reg__
	sts (time)+3,__zero_reg__
	rjmp .L38
.L35:
	lds r24,mode
	cpi r24,lo8(1)
	brne .L38
	lds r24,time
	lds r25,(time)+1
	lds r26,(time)+2
	lds r27,(time)+3
	sbiw r24,0
	cpc r26,__zero_reg__
	cpc r27,__zero_reg__
	breq .L39
	lds r24,time
	lds r25,(time)+1
	lds r26,(time)+2
	lds r27,(time)+3
	sbiw r24,1
	sbc r26,__zero_reg__
	sbc r27,__zero_reg__
	sts time,r24
	sts (time)+1,r25
	sts (time)+2,r26
	sts (time)+3,r27
	rjmp .L38
.L39:
	sts time,__zero_reg__
	sts (time)+1,__zero_reg__
	sts (time)+2,__zero_reg__
	sts (time)+3,__zero_reg__
.L38:
	lds r24,time
	lds r25,(time)+1
	lds r26,(time)+2
	lds r27,(time)+3
	ldi r18,lo8(60)
	ldi r19,hi8(60)
	ldi r20,hlo8(60)
	ldi r21,hhi8(60)
	movw r22,r24
	movw r24,r26
	call __udivmodsi4
	movw r26,r24
	movw r24,r22
	sts time+4,r24
	lds r24,time
	lds r25,(time)+1
	lds r26,(time)+2
	lds r27,(time)+3
	ldi r18,lo8(60)
	ldi r19,hi8(60)
	ldi r20,hlo8(60)
	ldi r21,hhi8(60)
	movw r22,r24
	movw r24,r26
	call __udivmodsi4
	movw r26,r20
	movw r24,r18
	ldi r18,lo8(60)
	ldi r19,hi8(60)
	ldi r20,hlo8(60)
	ldi r21,hhi8(60)
	movw r22,r24
	movw r24,r26
	call __udivmodsi4
	movw r26,r24
	movw r24,r22
	sts time+5,r24
	lds r24,time
	lds r25,(time)+1
	lds r26,(time)+2
	lds r27,(time)+3
	ldi r18,lo8(3600)
	ldi r19,hi8(3600)
	ldi r20,hlo8(3600)
	ldi r21,hhi8(3600)
	movw r22,r24
	movw r24,r26
	call __udivmodsi4
	movw r26,r20
	movw r24,r18
	sts time+6,r24
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	update_time, .-update_time
	.type	display_time, @function
display_time:
	push r16
	push r17
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
	subi r28,lo8(-(-84))
	sbci r29,hi8(-(-84))
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 84 */
	ldi r26,lo8(59)
	ldi r27,hi8(59)
	ldi r30,lo8(59)
	ldi r31,hi8(59)
	ld r24,Z
	andi r24,lo8(-64)
	ori r24,lo8(32)
	st X,r24
	ldi r26,lo8(53)
	ldi r27,hi8(53)
	ldi r30,lo8(53)
	ldi r31,hi8(53)
	ld r24,Z
	mov r18,r24
	andi r18,lo8(-16)
	lds r24,time+4
	ldi r25,lo8(10)
	mov r22,r25
	call __udivmodqi4
	mov r24,r25
	or r24,r18
	st X,r24
	movw r30,r28
	subi r30,lo8(-(81))
	sbci r31,hi8(-(81))
	ldi r24,lo8(0x40000000)
	ldi r25,hi8(0x40000000)
	ldi r26,hlo8(0x40000000)
	ldi r27,hhi8(0x40000000)
	st Z,r24
	std Z+1,r25
	std Z+2,r26
	std Z+3,r27
	movw r16,r28
	subi r16,lo8(-(77))
	sbci r17,hi8(-(77))
	movw r30,r28
	subi r30,lo8(-(81))
	sbci r31,hi8(-(81))
	ld r22,Z
	ldd r23,Z+1
	ldd r24,Z+2
	ldd r25,Z+3
	ldi r18,lo8(0x437a0000)
	ldi r19,hi8(0x437a0000)
	ldi r20,hlo8(0x437a0000)
	ldi r21,hhi8(0x437a0000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	movw r30,r16
	st Z,r24
	std Z+1,r25
	std Z+2,r26
	std Z+3,r27
	movw r30,r28
	subi r30,lo8(-(77))
	sbci r31,hi8(-(77))
	ld r22,Z
	ldd r23,Z+1
	ldd r24,Z+2
	ldd r25,Z+3
	ldi r18,lo8(0x3f800000)
	ldi r19,hi8(0x3f800000)
	ldi r20,hlo8(0x3f800000)
	ldi r21,hhi8(0x3f800000)
	call __ltsf2
	tst r24
	brge .L103
.L91:
	movw r30,r28
	subi r30,lo8(-(75))
	sbci r31,hi8(-(75))
	ldi r24,lo8(1)
	ldi r25,hi8(1)
	std Z+1,r25
	st Z,r24
	rjmp .L44
.L103:
	movw r30,r28
	subi r30,lo8(-(77))
	sbci r31,hi8(-(77))
	ld r22,Z
	ldd r23,Z+1
	ldd r24,Z+2
	ldd r25,Z+3
	ldi r18,lo8(0x477fff00)
	ldi r19,hi8(0x477fff00)
	ldi r20,hlo8(0x477fff00)
	ldi r21,hhi8(0x477fff00)
	call __gtsf2
	cp __zero_reg__,r24
	brlt .+2
	rjmp .L104
.L92:
	movw r30,r28
	subi r30,lo8(-(81))
	sbci r31,hi8(-(81))
	ld r22,Z
	ldd r23,Z+1
	ldd r24,Z+2
	ldd r25,Z+3
	ldi r18,lo8(0x41200000)
	ldi r19,hi8(0x41200000)
	ldi r20,hlo8(0x41200000)
	ldi r21,hhi8(0x41200000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	movw r16,r28
	subi r16,lo8(-(75))
	sbci r17,hi8(-(75))
	movw r22,r24
	movw r24,r26
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	movw r30,r16
	std Z+1,r25
	st Z,r24
	rjmp .L47
.L48:
	movw r30,r28
	subi r30,lo8(-(73))
	sbci r31,hi8(-(73))
	ldi r24,lo8(25)
	ldi r25,hi8(25)
	std Z+1,r25
	st Z,r24
	movw r30,r28
	subi r30,lo8(-(73))
	sbci r31,hi8(-(73))
	ld r24,Z
	ldd r25,Z+1
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	movw r30,r28
	subi r30,lo8(-(73))
	sbci r31,hi8(-(73))
	std Z+1,r25
	st Z,r24
	movw r26,r28
	subi r26,lo8(-(75))
	sbci r27,hi8(-(75))
	movw r30,r28
	subi r30,lo8(-(75))
	sbci r31,hi8(-(75))
	ld r24,Z
	ldd r25,Z+1
	sbiw r24,1
	adiw r26,1
	st X,r25
	st -X,r24
.L47:
	movw r30,r28
	subi r30,lo8(-(75))
	sbci r31,hi8(-(75))
	ld r24,Z
	ldd r25,Z+1
	sbiw r24,0
	brne .L48
	rjmp .L49
.L104:
	movw r16,r28
	subi r16,lo8(-(75))
	sbci r17,hi8(-(75))
	movw r30,r28
	subi r30,lo8(-(77))
	sbci r31,hi8(-(77))
	ld r22,Z
	ldd r23,Z+1
	ldd r24,Z+2
	ldd r25,Z+3
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	movw r30,r16
	std Z+1,r25
	st Z,r24
.L44:
	movw r26,r28
	subi r26,lo8(-(71))
	sbci r27,hi8(-(71))
	movw r30,r28
	subi r30,lo8(-(75))
	sbci r31,hi8(-(75))
	ld r24,Z
	ldd r25,Z+1
	st X+,r24
	st X,r25
	movw r30,r28
	subi r30,lo8(-(71))
	sbci r31,hi8(-(71))
	ld r24,Z
	ldd r25,Z+1
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	movw r30,r28
	subi r30,lo8(-(71))
	sbci r31,hi8(-(71))
	std Z+1,r25
	st Z,r24
.L49:
	ldi r26,lo8(59)
	ldi r27,hi8(59)
	ldi r30,lo8(59)
	ldi r31,hi8(59)
	ld r24,Z
	andi r24,lo8(-64)
	ori r24,lo8(16)
	st X,r24
	ldi r26,lo8(53)
	ldi r27,hi8(53)
	ldi r30,lo8(53)
	ldi r31,hi8(53)
	ld r24,Z
	mov r18,r24
	andi r18,lo8(-16)
	lds r24,time+4
	ldi r25,lo8(10)
	mov r22,r25
	call __udivmodqi4
	or r24,r18
	st X,r24
	movw r30,r28
	subi r30,lo8(-(67))
	sbci r31,hi8(-(67))
	ldi r24,lo8(0x40000000)
	ldi r25,hi8(0x40000000)
	ldi r26,hlo8(0x40000000)
	ldi r27,hhi8(0x40000000)
	st Z,r24
	std Z+1,r25
	std Z+2,r26
	std Z+3,r27
	movw r16,r28
	subi r16,lo8(-(63))
	sbci r17,hi8(-(63))
	movw r30,r28
	subi r30,lo8(-(67))
	sbci r31,hi8(-(67))
	ld r22,Z
	ldd r23,Z+1
	ldd r24,Z+2
	ldd r25,Z+3
	ldi r18,lo8(0x437a0000)
	ldi r19,hi8(0x437a0000)
	ldi r20,hlo8(0x437a0000)
	ldi r21,hhi8(0x437a0000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	movw r30,r16
	st Z,r24
	std Z+1,r25
	std Z+2,r26
	std Z+3,r27
	movw r30,r28
	adiw r30,63
	ld r22,Z
	ldd r23,Z+1
	ldd r24,Z+2
	ldd r25,Z+3
	ldi r18,lo8(0x3f800000)
	ldi r19,hi8(0x3f800000)
	ldi r20,hlo8(0x3f800000)
	ldi r21,hhi8(0x3f800000)
	call __ltsf2
	tst r24
	brge .L105
.L93:
	ldi r24,lo8(1)
	ldi r25,hi8(1)
	std Y+62,r25
	std Y+61,r24
	rjmp .L52
.L105:
	movw r30,r28
	adiw r30,63
	ld r22,Z
	ldd r23,Z+1
	ldd r24,Z+2
	ldd r25,Z+3
	ldi r18,lo8(0x477fff00)
	ldi r19,hi8(0x477fff00)
	ldi r20,hlo8(0x477fff00)
	ldi r21,hhi8(0x477fff00)
	call __gtsf2
	cp __zero_reg__,r24
	brge .L106
.L94:
	movw r30,r28
	subi r30,lo8(-(67))
	sbci r31,hi8(-(67))
	ld r22,Z
	ldd r23,Z+1
	ldd r24,Z+2
	ldd r25,Z+3
	ldi r18,lo8(0x41200000)
	ldi r19,hi8(0x41200000)
	ldi r20,hlo8(0x41200000)
	ldi r21,hhi8(0x41200000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	movw r22,r24
	movw r24,r26
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+62,r25
	std Y+61,r24
	rjmp .L55
.L56:
	ldi r24,lo8(25)
	ldi r25,hi8(25)
	std Y+60,r25
	std Y+59,r24
	ldd r24,Y+59
	ldd r25,Y+60
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+60,r25
	std Y+59,r24
	ldd r24,Y+61
	ldd r25,Y+62
	sbiw r24,1
	std Y+62,r25
	std Y+61,r24
.L55:
	ldd r24,Y+61
	ldd r25,Y+62
	sbiw r24,0
	brne .L56
	rjmp .L57
.L106:
	movw r30,r28
	adiw r30,63
	ld r22,Z
	ldd r23,Z+1
	ldd r24,Z+2
	ldd r25,Z+3
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+62,r25
	std Y+61,r24
.L52:
	ldd r24,Y+61
	ldd r25,Y+62
	std Y+58,r25
	std Y+57,r24
	ldd r24,Y+57
	ldd r25,Y+58
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+58,r25
	std Y+57,r24
.L57:
	ldi r26,lo8(59)
	ldi r27,hi8(59)
	ldi r30,lo8(59)
	ldi r31,hi8(59)
	ld r24,Z
	andi r24,lo8(-64)
	ori r24,lo8(8)
	st X,r24
	ldi r26,lo8(53)
	ldi r27,hi8(53)
	ldi r30,lo8(53)
	ldi r31,hi8(53)
	ld r24,Z
	mov r18,r24
	andi r18,lo8(-16)
	lds r24,time+5
	ldi r25,lo8(10)
	mov r22,r25
	call __udivmodqi4
	mov r24,r25
	or r24,r18
	st X,r24
	ldi r24,lo8(0x40000000)
	ldi r25,hi8(0x40000000)
	ldi r26,hlo8(0x40000000)
	ldi r27,hhi8(0x40000000)
	std Y+53,r24
	std Y+54,r25
	std Y+55,r26
	std Y+56,r27
	ldd r22,Y+53
	ldd r23,Y+54
	ldd r24,Y+55
	ldd r25,Y+56
	ldi r18,lo8(0x437a0000)
	ldi r19,hi8(0x437a0000)
	ldi r20,hlo8(0x437a0000)
	ldi r21,hhi8(0x437a0000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	std Y+49,r24
	std Y+50,r25
	std Y+51,r26
	std Y+52,r27
	ldd r22,Y+49
	ldd r23,Y+50
	ldd r24,Y+51
	ldd r25,Y+52
	ldi r18,lo8(0x3f800000)
	ldi r19,hi8(0x3f800000)
	ldi r20,hlo8(0x3f800000)
	ldi r21,hhi8(0x3f800000)
	call __ltsf2
	tst r24
	brge .L107
.L95:
	ldi r24,lo8(1)
	ldi r25,hi8(1)
	std Y+48,r25
	std Y+47,r24
	rjmp .L60
.L107:
	ldd r22,Y+49
	ldd r23,Y+50
	ldd r24,Y+51
	ldd r25,Y+52
	ldi r18,lo8(0x477fff00)
	ldi r19,hi8(0x477fff00)
	ldi r20,hlo8(0x477fff00)
	ldi r21,hhi8(0x477fff00)
	call __gtsf2
	cp __zero_reg__,r24
	brge .L108
.L96:
	ldd r22,Y+53
	ldd r23,Y+54
	ldd r24,Y+55
	ldd r25,Y+56
	ldi r18,lo8(0x41200000)
	ldi r19,hi8(0x41200000)
	ldi r20,hlo8(0x41200000)
	ldi r21,hhi8(0x41200000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	movw r22,r24
	movw r24,r26
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+48,r25
	std Y+47,r24
	rjmp .L63
.L64:
	ldi r24,lo8(25)
	ldi r25,hi8(25)
	std Y+46,r25
	std Y+45,r24
	ldd r24,Y+45
	ldd r25,Y+46
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+46,r25
	std Y+45,r24
	ldd r24,Y+47
	ldd r25,Y+48
	sbiw r24,1
	std Y+48,r25
	std Y+47,r24
.L63:
	ldd r24,Y+47
	ldd r25,Y+48
	sbiw r24,0
	brne .L64
	rjmp .L65
.L108:
	ldd r22,Y+49
	ldd r23,Y+50
	ldd r24,Y+51
	ldd r25,Y+52
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+48,r25
	std Y+47,r24
.L60:
	ldd r24,Y+47
	ldd r25,Y+48
	std Y+44,r25
	std Y+43,r24
	ldd r24,Y+43
	ldd r25,Y+44
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+44,r25
	std Y+43,r24
.L65:
	ldi r26,lo8(59)
	ldi r27,hi8(59)
	ldi r30,lo8(59)
	ldi r31,hi8(59)
	ld r24,Z
	andi r24,lo8(-64)
	ori r24,lo8(4)
	st X,r24
	ldi r26,lo8(53)
	ldi r27,hi8(53)
	ldi r30,lo8(53)
	ldi r31,hi8(53)
	ld r24,Z
	mov r18,r24
	andi r18,lo8(-16)
	lds r24,time+5
	ldi r25,lo8(10)
	mov r22,r25
	call __udivmodqi4
	or r24,r18
	st X,r24
	ldi r24,lo8(0x40000000)
	ldi r25,hi8(0x40000000)
	ldi r26,hlo8(0x40000000)
	ldi r27,hhi8(0x40000000)
	std Y+39,r24
	std Y+40,r25
	std Y+41,r26
	std Y+42,r27
	ldd r22,Y+39
	ldd r23,Y+40
	ldd r24,Y+41
	ldd r25,Y+42
	ldi r18,lo8(0x437a0000)
	ldi r19,hi8(0x437a0000)
	ldi r20,hlo8(0x437a0000)
	ldi r21,hhi8(0x437a0000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	std Y+35,r24
	std Y+36,r25
	std Y+37,r26
	std Y+38,r27
	ldd r22,Y+35
	ldd r23,Y+36
	ldd r24,Y+37
	ldd r25,Y+38
	ldi r18,lo8(0x3f800000)
	ldi r19,hi8(0x3f800000)
	ldi r20,hlo8(0x3f800000)
	ldi r21,hhi8(0x3f800000)
	call __ltsf2
	tst r24
	brge .L109
.L97:
	ldi r24,lo8(1)
	ldi r25,hi8(1)
	std Y+34,r25
	std Y+33,r24
	rjmp .L68
.L109:
	ldd r22,Y+35
	ldd r23,Y+36
	ldd r24,Y+37
	ldd r25,Y+38
	ldi r18,lo8(0x477fff00)
	ldi r19,hi8(0x477fff00)
	ldi r20,hlo8(0x477fff00)
	ldi r21,hhi8(0x477fff00)
	call __gtsf2
	cp __zero_reg__,r24
	brge .L110
.L98:
	ldd r22,Y+39
	ldd r23,Y+40
	ldd r24,Y+41
	ldd r25,Y+42
	ldi r18,lo8(0x41200000)
	ldi r19,hi8(0x41200000)
	ldi r20,hlo8(0x41200000)
	ldi r21,hhi8(0x41200000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	movw r22,r24
	movw r24,r26
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+34,r25
	std Y+33,r24
	rjmp .L71
.L72:
	ldi r24,lo8(25)
	ldi r25,hi8(25)
	std Y+32,r25
	std Y+31,r24
	ldd r24,Y+31
	ldd r25,Y+32
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+32,r25
	std Y+31,r24
	ldd r24,Y+33
	ldd r25,Y+34
	sbiw r24,1
	std Y+34,r25
	std Y+33,r24
.L71:
	ldd r24,Y+33
	ldd r25,Y+34
	sbiw r24,0
	brne .L72
	rjmp .L73
.L110:
	ldd r22,Y+35
	ldd r23,Y+36
	ldd r24,Y+37
	ldd r25,Y+38
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+34,r25
	std Y+33,r24
.L68:
	ldd r24,Y+33
	ldd r25,Y+34
	std Y+30,r25
	std Y+29,r24
	ldd r24,Y+29
	ldd r25,Y+30
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+30,r25
	std Y+29,r24
.L73:
	ldi r26,lo8(59)
	ldi r27,hi8(59)
	ldi r30,lo8(59)
	ldi r31,hi8(59)
	ld r24,Z
	andi r24,lo8(-64)
	ori r24,lo8(2)
	st X,r24
	ldi r26,lo8(53)
	ldi r27,hi8(53)
	ldi r30,lo8(53)
	ldi r31,hi8(53)
	ld r24,Z
	mov r18,r24
	andi r18,lo8(-16)
	lds r24,time+6
	ldi r25,lo8(10)
	mov r22,r25
	call __udivmodqi4
	mov r24,r25
	or r24,r18
	st X,r24
	ldi r24,lo8(0x40000000)
	ldi r25,hi8(0x40000000)
	ldi r26,hlo8(0x40000000)
	ldi r27,hhi8(0x40000000)
	std Y+25,r24
	std Y+26,r25
	std Y+27,r26
	std Y+28,r27
	ldd r22,Y+25
	ldd r23,Y+26
	ldd r24,Y+27
	ldd r25,Y+28
	ldi r18,lo8(0x437a0000)
	ldi r19,hi8(0x437a0000)
	ldi r20,hlo8(0x437a0000)
	ldi r21,hhi8(0x437a0000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	std Y+21,r24
	std Y+22,r25
	std Y+23,r26
	std Y+24,r27
	ldd r22,Y+21
	ldd r23,Y+22
	ldd r24,Y+23
	ldd r25,Y+24
	ldi r18,lo8(0x3f800000)
	ldi r19,hi8(0x3f800000)
	ldi r20,hlo8(0x3f800000)
	ldi r21,hhi8(0x3f800000)
	call __ltsf2
	tst r24
	brge .L111
.L99:
	ldi r24,lo8(1)
	ldi r25,hi8(1)
	std Y+20,r25
	std Y+19,r24
	rjmp .L76
.L111:
	ldd r22,Y+21
	ldd r23,Y+22
	ldd r24,Y+23
	ldd r25,Y+24
	ldi r18,lo8(0x477fff00)
	ldi r19,hi8(0x477fff00)
	ldi r20,hlo8(0x477fff00)
	ldi r21,hhi8(0x477fff00)
	call __gtsf2
	cp __zero_reg__,r24
	brge .L112
.L100:
	ldd r22,Y+25
	ldd r23,Y+26
	ldd r24,Y+27
	ldd r25,Y+28
	ldi r18,lo8(0x41200000)
	ldi r19,hi8(0x41200000)
	ldi r20,hlo8(0x41200000)
	ldi r21,hhi8(0x41200000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	movw r22,r24
	movw r24,r26
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+20,r25
	std Y+19,r24
	rjmp .L79
.L80:
	ldi r24,lo8(25)
	ldi r25,hi8(25)
	std Y+18,r25
	std Y+17,r24
	ldd r24,Y+17
	ldd r25,Y+18
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+18,r25
	std Y+17,r24
	ldd r24,Y+19
	ldd r25,Y+20
	sbiw r24,1
	std Y+20,r25
	std Y+19,r24
.L79:
	ldd r24,Y+19
	ldd r25,Y+20
	sbiw r24,0
	brne .L80
	rjmp .L81
.L112:
	ldd r22,Y+21
	ldd r23,Y+22
	ldd r24,Y+23
	ldd r25,Y+24
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+20,r25
	std Y+19,r24
.L76:
	ldd r24,Y+19
	ldd r25,Y+20
	std Y+16,r25
	std Y+15,r24
	ldd r24,Y+15
	ldd r25,Y+16
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+16,r25
	std Y+15,r24
.L81:
	ldi r26,lo8(59)
	ldi r27,hi8(59)
	ldi r30,lo8(59)
	ldi r31,hi8(59)
	ld r24,Z
	andi r24,lo8(-64)
	ori r24,lo8(1)
	st X,r24
	ldi r26,lo8(53)
	ldi r27,hi8(53)
	ldi r30,lo8(53)
	ldi r31,hi8(53)
	ld r24,Z
	mov r18,r24
	andi r18,lo8(-16)
	lds r24,time+6
	ldi r25,lo8(10)
	mov r22,r25
	call __udivmodqi4
	or r24,r18
	st X,r24
	ldi r24,lo8(0x40000000)
	ldi r25,hi8(0x40000000)
	ldi r26,hlo8(0x40000000)
	ldi r27,hhi8(0x40000000)
	std Y+11,r24
	std Y+12,r25
	std Y+13,r26
	std Y+14,r27
	ldd r22,Y+11
	ldd r23,Y+12
	ldd r24,Y+13
	ldd r25,Y+14
	ldi r18,lo8(0x437a0000)
	ldi r19,hi8(0x437a0000)
	ldi r20,hlo8(0x437a0000)
	ldi r21,hhi8(0x437a0000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	std Y+7,r24
	std Y+8,r25
	std Y+9,r26
	std Y+10,r27
	ldd r22,Y+7
	ldd r23,Y+8
	ldd r24,Y+9
	ldd r25,Y+10
	ldi r18,lo8(0x3f800000)
	ldi r19,hi8(0x3f800000)
	ldi r20,hlo8(0x3f800000)
	ldi r21,hhi8(0x3f800000)
	call __ltsf2
	tst r24
	brge .L113
.L101:
	ldi r24,lo8(1)
	ldi r25,hi8(1)
	std Y+6,r25
	std Y+5,r24
	rjmp .L84
.L113:
	ldd r22,Y+7
	ldd r23,Y+8
	ldd r24,Y+9
	ldd r25,Y+10
	ldi r18,lo8(0x477fff00)
	ldi r19,hi8(0x477fff00)
	ldi r20,hlo8(0x477fff00)
	ldi r21,hhi8(0x477fff00)
	call __gtsf2
	cp __zero_reg__,r24
	brge .L114
.L102:
	ldd r22,Y+11
	ldd r23,Y+12
	ldd r24,Y+13
	ldd r25,Y+14
	ldi r18,lo8(0x41200000)
	ldi r19,hi8(0x41200000)
	ldi r20,hlo8(0x41200000)
	ldi r21,hhi8(0x41200000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	movw r22,r24
	movw r24,r26
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+6,r25
	std Y+5,r24
	rjmp .L87
.L88:
	ldi r24,lo8(25)
	ldi r25,hi8(25)
	std Y+4,r25
	std Y+3,r24
	ldd r24,Y+3
	ldd r25,Y+4
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+4,r25
	std Y+3,r24
	ldd r24,Y+5
	ldd r25,Y+6
	sbiw r24,1
	std Y+6,r25
	std Y+5,r24
.L87:
	ldd r24,Y+5
	ldd r25,Y+6
	sbiw r24,0
	brne .L88
	rjmp .L90
.L114:
	ldd r22,Y+7
	ldd r23,Y+8
	ldd r24,Y+9
	ldd r25,Y+10
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+6,r25
	std Y+5,r24
.L84:
	ldd r24,Y+5
	ldd r25,Y+6
	std Y+2,r25
	std Y+1,r24
	ldd r24,Y+1
	ldd r25,Y+2
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+2,r25
	std Y+1,r24
.L90:
/* epilogue start */
	subi r28,lo8(-(84))
	sbci r29,hi8(-(84))
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r28
	pop r29
	pop r17
	pop r16
	ret
	.size	display_time, .-display_time
	.type	check_update_mode, @function
check_update_mode:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r30,lo8(54)
	ldi r31,hi8(54)
	ld r24,Z
	tst r24
	brlt .L116
	lds r24,flags
	andi r24,lo8(1)
	tst r24
	brne .L121
	lds r24,mode
	tst r24
	brne .L118
	ldi r24,lo8(1)
	sts mode,r24
	ldi r26,lo8(50)
	ldi r27,hi8(50)
	ldi r30,lo8(50)
	ldi r31,hi8(50)
	ld r24,Z
	andi r24,lo8(-49)
	ori r24,lo8(32)
	st X,r24
	rjmp .L119
.L118:
	sts mode,__zero_reg__
	ldi r26,lo8(50)
	ldi r27,hi8(50)
	ldi r30,lo8(50)
	ldi r31,hi8(50)
	ld r24,Z
	andi r24,lo8(-49)
	ori r24,lo8(16)
	st X,r24
.L119:
	lds r24,flags
	ori r24,lo8(1)
	sts flags,r24
	rjmp .L121
.L116:
	lds r24,flags
	andi r24,lo8(-2)
	sts flags,r24
.L121:
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	check_update_mode, .-check_update_mode
	.type	handle_hours_change_buttons, @function
handle_hours_change_buttons:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r30,lo8(54)
	ldi r31,hi8(54)
	ld r24,Z
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(2)
	andi r25,hi8(2)
	sbiw r24,0
	brne .L123
	lds r24,flags
	andi r24,lo8(2)
	tst r24
	brne .L125
	lds r24,time+6
	cpi r24,lo8(23)
	brsh .L125
	lds r24,time+6
	subi r24,lo8(-(1))
	sts time+6,r24
	lds r24,time
	lds r25,(time)+1
	lds r26,(time)+2
	lds r27,(time)+3
	subi r24,lo8(-(3600))
	sbci r25,hi8(-(3600))
	sbci r26,hlo8(-(3600))
	sbci r27,hhi8(-(3600))
	sts time,r24
	sts (time)+1,r25
	sts (time)+2,r26
	sts (time)+3,r27
	lds r24,flags
	ori r24,lo8(2)
	sts flags,r24
	rjmp .L125
.L123:
	lds r24,flags
	andi r24,lo8(-3)
	sts flags,r24
.L125:
	ldi r30,lo8(54)
	ldi r31,hi8(54)
	ld r24,Z
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(1)
	andi r25,hi8(1)
	sbiw r24,0
	brne .L126
	lds r24,flags
	andi r24,lo8(4)
	tst r24
	brne .L129
	lds r24,time+6
	tst r24
	breq .L129
	lds r24,time+6
	subi r24,lo8(-(-1))
	sts time+6,r24
	lds r24,time
	lds r25,(time)+1
	lds r26,(time)+2
	lds r27,(time)+3
	subi r24,lo8(-(-3600))
	sbci r25,hi8(-(-3600))
	sbci r26,hlo8(-(-3600))
	sbci r27,hhi8(-(-3600))
	sts time,r24
	sts (time)+1,r25
	sts (time)+2,r26
	sts (time)+3,r27
	lds r24,flags
	ori r24,lo8(4)
	sts flags,r24
	rjmp .L129
.L126:
	lds r24,flags
	andi r24,lo8(-5)
	sts flags,r24
.L129:
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	handle_hours_change_buttons, .-handle_hours_change_buttons
	.type	handle_minutes_change_buttons, @function
handle_minutes_change_buttons:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r30,lo8(54)
	ldi r31,hi8(54)
	ld r24,Z
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(16)
	andi r25,hi8(16)
	sbiw r24,0
	brne .L131
	lds r24,flags
	andi r24,lo8(8)
	tst r24
	brne .L133
	lds r24,time+5
	cpi r24,lo8(59)
	brsh .L133
	lds r24,time+5
	subi r24,lo8(-(1))
	sts time+5,r24
	lds r24,time
	lds r25,(time)+1
	lds r26,(time)+2
	lds r27,(time)+3
	adiw r24,60
	adc r26,__zero_reg__
	adc r27,__zero_reg__
	sts time,r24
	sts (time)+1,r25
	sts (time)+2,r26
	sts (time)+3,r27
	lds r24,flags
	ori r24,lo8(8)
	sts flags,r24
	rjmp .L133
.L131:
	lds r24,flags
	andi r24,lo8(-9)
	sts flags,r24
.L133:
	ldi r30,lo8(54)
	ldi r31,hi8(54)
	ld r24,Z
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(8)
	andi r25,hi8(8)
	sbiw r24,0
	brne .L134
	lds r24,flags
	andi r24,lo8(16)
	tst r24
	brne .L137
	lds r24,time+5
	tst r24
	breq .L137
	lds r24,time+5
	subi r24,lo8(-(-1))
	sts time+5,r24
	lds r24,time
	lds r25,(time)+1
	lds r26,(time)+2
	lds r27,(time)+3
	sbiw r24,60
	sbc r26,__zero_reg__
	sbc r27,__zero_reg__
	sts time,r24
	sts (time)+1,r25
	sts (time)+2,r26
	sts (time)+3,r27
	lds r24,flags
	ori r24,lo8(16)
	sts flags,r24
	rjmp .L137
.L134:
	lds r24,flags
	andi r24,lo8(-17)
	sts flags,r24
.L137:
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	handle_minutes_change_buttons, .-handle_minutes_change_buttons
	.type	handle_seconds_change_buttons, @function
handle_seconds_change_buttons:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r30,lo8(54)
	ldi r31,hi8(54)
	ld r24,Z
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(64)
	andi r25,hi8(64)
	sbiw r24,0
	brne .L139
	lds r24,flags
	andi r24,lo8(32)
	tst r24
	brne .L141
	lds r24,time+4
	cpi r24,lo8(59)
	brsh .L141
	lds r24,time+4
	subi r24,lo8(-(1))
	sts time+4,r24
	lds r24,time
	lds r25,(time)+1
	lds r26,(time)+2
	lds r27,(time)+3
	adiw r24,1
	adc r26,__zero_reg__
	adc r27,__zero_reg__
	sts time,r24
	sts (time)+1,r25
	sts (time)+2,r26
	sts (time)+3,r27
	lds r24,flags
	ori r24,lo8(32)
	sts flags,r24
	rjmp .L141
.L139:
	lds r24,flags
	andi r24,lo8(-33)
	sts flags,r24
.L141:
	ldi r30,lo8(54)
	ldi r31,hi8(54)
	ld r24,Z
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(32)
	andi r25,hi8(32)
	sbiw r24,0
	brne .L142
	lds r24,flags
	andi r24,lo8(64)
	tst r24
	brne .L145
	lds r24,time+4
	tst r24
	breq .L145
	lds r24,time+4
	subi r24,lo8(-(-1))
	sts time+4,r24
	lds r24,time
	lds r25,(time)+1
	lds r26,(time)+2
	lds r27,(time)+3
	sbiw r24,1
	sbc r26,__zero_reg__
	sbc r27,__zero_reg__
	sts time,r24
	sts (time)+1,r25
	sts (time)+2,r26
	sts (time)+3,r27
	lds r24,flags
	ori r24,lo8(64)
	sts flags,r24
	rjmp .L145
.L142:
	lds r24,flags
	andi r24,lo8(-65)
	sts flags,r24
.L145:
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	handle_seconds_change_buttons, .-handle_seconds_change_buttons
	.comm time,7,1
	.comm flags,1,1
.global __do_clear_bss
