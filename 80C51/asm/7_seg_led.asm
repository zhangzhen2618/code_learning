.module 7_seg_led

TIMER_RESET_VALUE = 61548;61548;2ms delay (65536-2*11966000/6/1000)
TIMER_COUNTER = 500; 500 means 500 * 2 = 1000ms
SEG_NUM = 8

.globl timer_count
.globl seg_value
.globl seg
.globl seg_ptr

.area XSEG (ABS)
.area PSEG (ABS)
.area DSEG (ABS, DATA)
.org 0X70
timer_count::
    .ds 2
seg_value::
    .ds 8
seg_ptr::
    .ds 1

.area HOME (ABS, CODE)
.org 0x0000
_int_reset:
    ljmp main
 
.org 0x000B
    ljmp TM0_ISR

.area CSEG (ABS, CODE)
.org 0x0043
seg::
    .db 0x3F, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f
TM0_ISR:
    PUSH ACC
    PUSH PSW
    MOV TL0, #<TIMER_RESET_VALUE; 取低位，注意立即数别写错了，取高低位在#号之后
    MOV TH0, #>TIMER_RESET_VALUE
    ;INC P2
    INC seg_ptr; seg_ptr++

    MOV B, #SEG_NUM; seg_ptr %= SEG_NUM
    MOV A, seg_ptr
    DIV AB
    MOV seg_ptr, B

    ANL P2, #0XE3; 清零P2.2, P2.3, P2.4, 0XE3=11100011B

    ;MOV A, seg_ptr; 计算 seg_ptr << 2 <==> seg_ptr * 4, 将结果存入P2，设置P2.2, P2.3, P2.4
    MOV A, #0x04
    MUL AB
    ORL P2, A

    ;将seg_ptr对应的数码管位段值存入P0
    MOV A, seg_ptr
    ADD A, #seg_value
    MOV R0, A
    MOV A, @R0
    MOV dptr, #seg
    MOVC A, @A+dptr
    MOV P0, A

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

    CPL P2

    MOV R0, #seg_value; seg_value 所指向的值 seg_value[i] %= 10;  i->[0, SEG_NUM]
INC_SEG_NUMBER:
    INC @R0
    MOV B, #10
    MOV A, @R0
    DIV AB
    MOV @R0, B
    INC R0
    CJNE R0, #seg_value + SEG_NUM, INC_SEG_NUMBER

    
NEXT:
    POP PSW 
    POP ACC
    RETI
    
main:
    ; 使用变址寻址，访问存储在片内flash上的静态数组
    ;MOV P2, #0X00
    ;MOV A, #0x05
    ;MOV dptr, #seg
    ;MOVC A, @A + dptr
    ;MOV P0, A
    ;设置初始值
    MOV timer_count, #<TIMER_COUNTER
    MOV timer_count + 1, #>TIMER_COUNTER
    MOV seg_ptr, 0x00;
    ; 8个数码管要显示的初始值
    MOV seg_value, #0x07 
    MOV seg_value + 1, #0x06 
    MOV seg_value + 2, #0x05 
    MOV seg_value + 3, #0x04 
    MOV seg_value + 4, #0x03 
    MOV seg_value + 5, #0x02 
    MOV seg_value + 6, #0x01 
    MOV seg_value + 7, #0x00 

    MOV TMOD, #0X01 ;设置定时器0为16bit模式
    MOV TL0, #<TIMER_RESET_VALUE ; 设置计数器的值
    MOV TH0, #>TIMER_RESET_VALUE
    SETB TR0 ; 定时器0开始
    SETB ET0 ; 定时器0中断使能
    SETB EA  ; 中断总使能
    sjmp .
