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

void setSystemCLK(){
	CLKCONCMD &= ~CLKCON_OSC; //设置系统时钟源为32MHz
	while( CLKCONSTA & CLKCON_OSC);
	CLKCONCMD &= ~CLKCONSTA_CLKSPD; //当前系统时钟频率为32MHz
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
void main(){

	setSystemCLK();
	
	PERCFG &= ~(PERCFG_U1CFG); // Configure USART1 for Alternative 1 ==> Port P0  
    P0SEL |= BIT4 | BIT5; // configure the P0.4, P0.5 as alternative, RX=P0.5, TX=P0.4
    P2DIR |= BIT6; // P0, USART1 privit

    // Configure the baudrate as 115200
    U1BAUD = 216;
    U1GCR &= ~U1GCR_BAUD_E;
    U1GCR |= 11;

	U1CSR |= BIT7; // Set the mode of uart1 as uart

	uint8_t tx[] = "hello world!!!!\n";
	while(1){
		uart1Send(tx, sizeof(tx));

		for(uint16_t i = 0; i < 0xffff; i++);
	}
}