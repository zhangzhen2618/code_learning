#include "uart.h"

void system_clock_init(){

    //Set the system clock source to 26Mhz XSOC to support maximum transfer speed,
    SLEEP &= ~SLEEP_OSC_PD; // Power up the HS RCOSC and XSOC
    while (!(SLEEP & SLEEP_XOSC_S)); // Waiting the XOSC to stable.
    CLKCON &= ~(CLKCON_CLKSPD | CLKCON_OSC); // clear the System clock speed setting bit;
    // CLKCON = (CLKCON & ~(CLKCON_CLKSPD | CLKCON_OSC)) | CLKSPD_DIV_1;
    // When the CLKCON.OSC bit set to 0, system clock source set to the XOSC
    CLKCON |= CLKSPD_DIV_1; // The systemc clock div, set to 000, means, system clock is 26Mhz
    while(CLKCON & CLKCON_OSC); // Waiting to the system clock source from hs RCOSC to the XOSC;
    SLEEP |= SLEEP_OSC_PD; // Let the system not set by toggle the CLKCON.OSC

    // !!! Remember change the system clock source, must wait the RCOSC or XOSC to stable;!!!
}

void uart_init(){

    PERCFG &= ~PERCFG_U1CFG; // Configure USART1 for Alternative 1 ==> Port P0  
    P0SEL |= BIT4 | BIT5; // configure the P0.4, P0.5 as alternative, RX=P0.5, TX=P0.4
    // P2SEL |= P2SEL_PRI3P1;
    P2DIR |= P2DIR_PRIP0_1; // P0, USART1 privit

    // Configure the baudrate as 115200
    U1BAUD = UART_BAUD_M;
    U1GCR &= ~U1GCR_BAUD_E;
    U1GCR |= UART_BAUD_E;

    // Set the mode of uart1 as uart
    U1CSR |= U1CSR_MODE;// USART1 mode = UART
    U1UCR &= ~U1UCR_FLOW; // disable the flow control;
    U1UCR &= ~U1UCR_D9; // Even parity
    U1UCR &= ~U1UCR_BIT9; // 8bits
    U1UCR &= ~U1UCR_PARITY; // No parity
    U1UCR &= ~U1UCR_SPB; // 1 stop bit
    U1UCR |= U1UCR_STOP; // high stop bit
    U1UCR &= ~U1UCR_START; // Low start bit

    U1GCR &= ~U1GCR_ORDER; // LSB first

}
void uart1Send(uint8 *txdata, uint16 len){
    
    // clear and pending TX interrupt request 
    U1CSR &= ~U1CSR_TX_BYTE;

    for(uint16 i = 0; i < len; i++){
        U1DBUF = txdata[i];
        // X_U1DBUF = 0x80;
        while (!(U1CSR & U1CSR_TX_BYTE));
        U1CSR &= ~U1CSR_TX_BYTE;
    }
}

uint16 uart1Receive(unsigned char *rxdata){
    // Enable UART1 RX
    U1CSR |= U1CSR_RE;
    uint16 len = 0; 
    while( !(U1CSR&U1CSR_RX_BYTE) );
    while (1){
        if(U1CSR & U1CSR_RX_BYTE){
            *(rxdata + len) = U1DBUF;
            len++;
        }else{
            break;
        }
    }
    return len;
}