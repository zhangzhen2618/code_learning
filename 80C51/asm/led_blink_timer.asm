.module led_blink_timer

TIMER_RESET_VALUE = 63542
TIMER_COUNTER = 500
.globl timer_count

.area XSEG (ABS)
.area PSEG (ABS)
.area DSEG (DATA)
timer_count::
    .ds 2
.area HOME (ABS, CODE)
.org 0x0000
_int_reset:
    ljmp main
 
.org 0x000B
    ljmp TM0_ISR

.area CSEG (ABS, CODE)
.org 0x0043
TM0_ISR:
    PUSH ACC
    PUSH PSW
    MOV TL0, #<TIMER_RESET_VALUE; 注意立即数别写错了，取高低位在#号之后
    MOV TH0, #>TIMER_RESET_VALUE
    CLR C; 清楚进位标志
    MOV A, timer_count;计算timer_count -= 1
    SUBB A, #1
    MOV timer_count, A
    MOV A, timer_count + 1
    SUBB A, #0
    MOV timer_count + 1, A 
    ORL A, timer_count ; 检查timer_count 是否为0
    JNZ NEXT
    MOV timer_count, #<TIMER_COUNTER ; 如果timer_count == 0， 则复位timer_count, 切换led 状态
    MOV timer_count + 1, #>TIMER_COUNTER
    MOV A, P2
    CLR C
    RLC A
    MOV P2, A
    JNZ NEXT
    MOV P2, #0xFF
NEXT:
    POP PSW 
    POP ACC
    RETI
    
main:
    MOV timer_count, #<TIMER_COUNTER
    MOV timer_count + 1, #>TIMER_COUNTER
    MOV TMOD, #0X01 
    MOV TL0, #<TIMER_RESET_VALUE
    MOV TH0, #>TIMER_RESET_VALUE
    SETB TR0
    SETB ET0
    SETB EA
    sjmp .
