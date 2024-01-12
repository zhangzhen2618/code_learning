#include "cc2530_lcd.h"

#define BIT0              0x01
#define BIT1              0x02
#define BIT2              0x04
#define BIT3              0x08
#define BIT4              0x10
#define BIT5              0x20
#define BIT6              0x40
#define BIT7              0x80



int main(){
    
    CLKCONCMD &= ~CLKCON_OSC; //设置系统时钟源为32MHz
	while( CLKCONSTA & CLKCON_OSC);
	CLKCONCMD &= ~CLKCONSTA_CLKSPD; //当前系统时钟频率为32MHz

    P1DIR = 0xff;

    PERCFG |= PERCFG_U0CFG;
    P1SEL |= BIT5 | BIT3;
    // SPI0 has Priority, default

    U0GCR |= U0GCR_ORDER; // MSB First
    // Configure the baudrate as 115200
    U0BAUD = 0;
    U0GCR &= ~U0GCR_BAUD_E;
    U0GCR |= 18;

	// P1INP =	BIT7 | BIT3 | BIT5 | BIT6; 
    // P1DIR |= BIT7 | BIT3 | BIT5 | BIT6;
    
	LCD_Init();

	while(1){	
        LCD_Clear(RED);delay_ms(1000);	
        LCD_Clear(GREEN);delay_ms(1000);	
        LCD_Clear(BLUE);delay_ms(1000);
    }   
}