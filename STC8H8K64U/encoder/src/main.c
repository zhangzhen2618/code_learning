#include "STC8H.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "stc8h_bitdef.h"

#define     MAIN_Fosc       48000000L   //定义主时钟
#define     BRT             (65536 - (MAIN_Fosc / 115200 + 2) / 4)



bool busy;
bool spi_busy;

char buffer[16];

unsigned short pulse;
bool B_Change;

char buf[100];
uint16_t tmp_pulse = 0;

void UartInit(void);
void UartSend(char dat);
void UartSendStr(char *str);

void PWMA_config(void);

void main(void){

    P_SW2 |= P_SW2_EAXFR;  //扩展寄存器XFR访问使能
    P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0x00;
    P1M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P3M0 = 0x00;
    P3M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;

    P2PU = 0xff;

    UartInit();
    PWMA_config();

    // Interrupt enable
    ES = 1;
    EA = 1;

    UartSendStr("Hello STCH UART");
    
    while(1){
        if (B_Change){
            B_Change = 0;
            tmp_pulse = pulse;
            sprintf(buf, "pulse : %u\n", tmp_pulse);
            UartSendStr(buf);
            // UartSend( tmp_pulse / 10000 + '0');
            // UartSend((tmp_pulse % 10000) / 1000 + '0');
            // UartSend((tmp_pulse % 1000) / 100 + '0');
            // UartSend((tmp_pulse % 100) / 10 + '0');
            // UartSend((tmp_pulse % 10) + '0');
            // UartSend('\n');

        }
    //    for(uint16_t i = 0; i < 0x8fff; i++){

    //    }
    }

}

void UartInit(void){
    SCON = 0x50; // 模式1，接收使能
    T2L = BRT;
    T2H = BRT >> 8;
    
    AUXR = 0X15;
    busy = 0;
}

void UartSend(char dat){
    while (busy);
    busy = 1;
    SBUF = dat; 
}

void UartSendStr(char *str){
    while(*str){
        UartSend(*str++);
    }
}


void Uartlsr() __interrupt(UART1_VECTOR) __using(UART1_VECTOR){
    if (TI){
        TI = 0;
        busy = 0;
    }

    if (RI){
        RI = 0;
    }
}

void PWMA_ISR(void) __interrupt(PWMA_VECTOR) __using(PWMA_VECTOR){

    if (PWMA_SR1 & 0x02){
        // pulse++;
        // pulse = PWMA_CNTR;
        // pulse++;
        // pulse = PWMA_CNTRH;
        // pulse <<= 8;
        // pulse += PWMA_CNTRL;
        // pulse = PWMA_CNTRH;

		pulse = ((uint16_t)PWMA_CNTRH << 8) + (uint16_t)PWMA_CNTRL;	//读取当前编码器计数值
        B_Change = 1;
    }

    PWMA_SR1 = 0;

    // PWMA_SR1 = 0;
    // uint8_t	sr1, sr2;
	// sr1 = PWMA_SR1;	//为了快速, 中断标志用一个局部变量处理
	// PWMA_SR1 = 0;	//清除中断标志
	// sr2 = PWMA_SR2;	//为了快速, 中断标志用一个局部变量处理
	// PWMA_SR2 = 0;	//清除中断标志
	// sr1 &= PWMA_ISR_En;	//每个通道可以单独允许中断处理

	// if(sr1 & 0x02)	//通道1 编码器中断
	// {
	// 	B_Change = 1;		//标志已有捕捉值
	// }
}

void PWMA_config(void){

    // PWMA_PSCR = 0;
    // PWMA_ARR = 0xffff;
    // PWMA_CNTR = 0;
    // PWMA_ENO = 0;

    // PWMA_CCMR1 = 0x01 + (10 << 4);
    // PWMA_CCMR2 = 0x01 + (10 << 4);

    // PWMA_SMCR = 2;

    // PWMA_CCER1 = 0x55;
    // PWMA_PS = 0x05;
    // PWMA_IER = 0x02;
    // PWMA_CR1 = 0x01;
    uint8_t	ps;

    uint8_t PWMA_ISR_En = 0;
	P2M1 = 0x00;
	P2M0 = 0x00;

	P_SW2 |= 0x80;		//SFR enable   
	PWMA_ENO    = 0;	// IO输出禁止
	PWMA_IER    = 0;	// 禁止中断
	PWMA_SR1    = 0;	// 清除状态
	PWMA_SR2    = 0;	// 清除状态
	ps    = 0;
	

	PWMA_PSCRH = 0;		// 预分频寄存器, 分频 Fck_cnt = Fck_psc/(PSCR[15:0}+1), 边沿对齐PWM频率 = SYSclk/((PSCR+1)*(AAR+1)), 中央对齐PWM频率 = SYSclk/((PSCR+1)*(AAR+1)*2).
	PWMA_PSCRL = 0;
	PWMA_ARRH  = 0xff;	// 自动重装载寄存器,  控制PWM周期
	PWMA_ARRL  = 0xff;
	PWMA_CNTRH 	= 0;	//清零编码器计数器值
	PWMA_CNTRL 	= 0;

	PWMA_CCMR1  = 0x01+(10<<4);	// 通道1模式配置, 配置成输入通道, 0~15对应输入滤波时钟数: 1 2 4 8 12 16 24 32 48 64 80 96 128 160 192 256
	PWMA_CCMR2  = 0x01+(10<<4);	// 通道2模式配置, 配置成输入通道, 0~15对应输入滤波时钟数: 1 2 4 8 12 16 24 32 48 64 80 96 128 160 192 256
	PWMA_SMCR   = 3;			// 编码器模式, 模式1或模式2: 每个脉冲两个边沿加减2.   模式3: 每个脉冲四个边沿加减4.
	PWMA_CCER1  = 0x55;			// 配置通道输入使能和极性, 允许输入, 下降沿
	ps    |= 1;					// 选择IO, 0:选择P1.0 P1.1, 1:选择P2.0 P2.1, 2:选择P6.0 P6.1, 
	ps    |= (1<<2);			// 选择IO, 0:选择P1.2 P1.3, 1:选择P2.2 P2.3, 2:选择P6.2 P6.3, 
	PWMA_ISR_En|= 0x02;			// 使能中断

	PWMA_CCR3H  = 0;			// 计数器比较值高字节(设置一个脉冲数), 匹配时刻
	PWMA_CCR3L  = 100;			// 计数器比较值低字节
	PWMA_CCMR3  = (3<<4);		// 通道1模式配置, 禁止预装载. 0: 无输出, 1:匹配时输出高, 2:匹配时输出低, 3:匹配时输出翻转.
	PWMA_CCER2  = 0x01;			// 捕获/比较使能寄存器2
	PWMA_ISR_En|= 0x08;			// 使能中断

	PWMA_PS     = ps;			// 选择IO
	PWMA_IER    = PWMA_ISR_En;	//设置允许通道1~4中断处理
	PWMA_CR1    = 0x01;		
}
