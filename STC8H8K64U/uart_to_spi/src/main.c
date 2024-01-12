#include "STC8H.h"
#include <stdint.h>
#include <stdbool.h>
#include "stc8h_bitdef.h"

#define     MAIN_Fosc       48000000L   //定义主时钟
#define     BRT             (65536 - (MAIN_Fosc / 115200 + 2) / 4)

bool busy;
bool spi_busy;
uint8_t spi_wptr;
uint8_t spi_rptr;
uint8_t wptr;
uint8_t rptr;
char buffer[16];
uint8_t spi_buf[16];

void UartInit(void);
void UartSend(char dat);
void spi_send(char dat);
void UartSendStr(char *str);

void spi_init(void);

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

    UartInit();
    spi_init();

    // Interrupt enable
    ES = 1;
    EA = 1;
    IE2 |= 0x02;

    UartSendStr("Hello STCH UART");

    while(1){
        if (rptr != wptr){
            spi_send(buffer[rptr]);
            UartSend(buffer[rptr++]);
            rptr &= 0x0f;
        }

        if (spi_rptr != spi_wptr){
            UartSend(spi_buf[spi_rptr++]);
            spi_rptr &= 0x0f;
        }
    }

}

void UartInit(void){
    SCON = 0x50; // 模式1，接收使能
    T2L = BRT;
    T2H = BRT >> 8;
    
    AUXR = 0X15;
    wptr = 0;
    rptr = 0;
    busy = 0;
}

void UartSend(char dat){
    while (busy);
    busy = 1;
    SBUF = dat; 
}

void spi_send(char dat){
    IE2 &= ~0x02;
    SPDAT = dat;
    SPSTAT = 0xC0;
    IE2 |= 0x02;
 
    
}

void UartSendStr(char *str){
    while(*str){
        UartSend(*str++);
    }
}

void spi_init(void){
    P_SW1 |= 0x04; // spi1 Port 2
    SPCTL = 0x40;
    SPSTAT = 0xC0;   
    spi_rptr = 0;
    spi_wptr = 0;
}

void spi_lsr() __interrupt(SPI_VECTOR) __using(SPI_VECTOR){
    SPSTAT = 0xC0;
    spi_buf[spi_wptr++] = SPDAT;
    spi_wptr &= 0x0f;
}

void Uartlsr() __interrupt(UART1_VECTOR) __using(UART1_VECTOR){
    if (TI){
        TI = 0;
        busy = 0;
    }

    if (RI){
        RI = 0;
        buffer[wptr++] = SBUF;
        wptr &= 0x0f;
    }
}
