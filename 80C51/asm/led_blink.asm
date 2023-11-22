.module blink

.area XSEG (ABS)
.area PSEG (ABS)
.area HOME (ABS, CODE)
.org 0x0000
_int_reset:
	ljmp main

.area CSEG (ABS, CODE)
.org 0x0043
main:
	;MOV A, #0XFF
	;SETB C
main_loop:
	RLC A
	CLR C
	MOV P2, A
	ACALL delay
	CJNE A, #0X00, main_loop
	MOV A, #0XFF
	sjmp main_loop
	
delay:
	mov r4, #0x00	
	mov r3, #0x00	
	mov r5, #0x02	
wait:
	djnz r4, wait
	djnz r3, wait
	djnz r5, wait
	ret