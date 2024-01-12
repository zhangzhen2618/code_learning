#include "cc2530.h"
#include "cc2530io_bitdef.h"
#include <stdint.h>

#define BIT0              0x01
#define BIT1              0x02
#define BIT2              0x04
#define BIT3              0x08
#define BIT4              0x10
#define BIT5              0x20
#define BIT6              0x40
#define BIT7              0x80

#define SPI0_CS           P1_2

void setSystemCLK();

void spi_0_init(void);
uint8_t spi0_write(uint8_t);

void uart1Init(void);
void uart1Send(uint8_t *txdata, uint16_t len);

uint8_t uart1_buf[16];
uint8_t uart1_wptr;
uint8_t uart1_rptr;

uint8_t spi0_buf[16];
uint8_t spi0_wptr;
uint8_t spi0_rptr;

void main(){

	setSystemCLK();

    uart1Init();

    spi_0_init();

    EA = 1;

	uint8_t tx[] = "hello world!!!!\n";
	while(1){
        // uart1Send(tx, sizeof(tx));
        spi0_write('x');

		if (uart1_rptr != uart1_wptr){
            uart1Send(uart1_buf + uart1_rptr, 1);
            spi0_write(*(uart1_buf + uart1_rptr));
            uart1_rptr++;
            uart1_rptr &= 0x0f;
        }

        if (spi0_rptr != spi0_wptr){
            uart1Send(spi0_buf + spi0_rptr, 1);
            spi0_rptr++;
            spi0_rptr &= 0x0f;
        }
	}
}

void spi_0_init(){
    // init SPI0_CS (P1_2) as output
    P1DIR |= BIT2;
    SPI0_CS = 1; // 
    // SPI0 P1_5, P1_4, P1_3 Alternative ALT2 
    PERCFG |= PERCFG_U0CFG;
    P1SEL |= BIT5 | BIT4 | BIT3;
    // SPI0 has Priority, default

    U0GCR |= U0GCR_ORDER; // MSB First
    // Configure the baudrate as 115200
    U0BAUD = 216;
    U0GCR &= ~U1GCR_BAUD_E;
    U0GCR |= 11;

    spi0_wptr = 0;
    spi0_rptr = 0;

    URX0IE = 1; // receive interrupt enable

}

uint8_t spi0_write(uint8_t byte){
    URX0IE = 0; // interrupt disabled
    SPI0_CS = 0;
    U0CSR &= ~U0CSR_TX_BYTE;
    U0DBUF = byte;
    while (!(U0CSR & U0CSR_TX_BYTE));
    SPI0_CS = 1;
    URX0IF = 0; // clear the interrupt flag
    URX0IE = 1; // enable interrupt
}

void setSystemCLK(){
	CLKCONCMD &= ~CLKCON_OSC; //设置系统时钟源为32MHz
	while( CLKCONSTA & CLKCON_OSC);
	CLKCONCMD &= ~CLKCONSTA_CLKSPD; //当前系统时钟频率为32MHz
}

void uart1Init(void){
	
	PERCFG &= ~(PERCFG_U1CFG); // Configure USART1 for Alternative 1 ==> Port P0  
    P0SEL |= BIT4 | BIT5; // configure the P0.4, P0.5 as alternative, RX=P0.5, TX=P0.4
    P2DIR |= BIT6; // P0, USART1 privit

    // Configure the baudrate as 115200
    U1BAUD = 216;
    U1GCR &= ~U1GCR_BAUD_E;
    U1GCR |= 11;

	U1CSR |= BIT7 | BIT6; // Set the mode of uart1 as uart, enable receive

    URX1IE = 1; // uart1 RX interrupt enable

    uart1_wptr = 0;
    uart1_rptr = 0;
}

void uart1Send(uint8_t *txdata, uint16_t len){
    
    // clear and pending TX interrupt request 
    U1CSR &= ~U1CSR_TX_BYTE;

    for(uint16_t i = 0; i < len; i++){
        U1DBUF = txdata[i];
        // X_U1DBUF = 0x80;
        while (!(U1CSR & U1CSR_TX_BYTE));
        U1CSR &= ~U1CSR_TX_BYTE;
    }
}

void uart1_isr(void) __interrupt(URX1_VECTOR) __using(URX1_VECTOR){
    // if (URX1IF){
    //     URX1IF = 0;
        uart1_buf[uart1_wptr++] = U1DBUF;
        uart1_wptr &= 0x0f;
    // }
}

void spi0_isr(void) __interrupt(URX0_VECTOR) __using(URX0_VECTOR){
    if (!UTX0IF){
        URX0IF = 0;
        spi0_buf[spi0_wptr++] = U0DBUF;
        spi0_wptr &= 0x0f;
    }
}