#include "stc8h_lcd.h"

#define BIT0              0x01
#define BIT1              0x02
#define BIT2              0x04
#define BIT3              0x08
#define BIT4              0x10
#define BIT5              0x20
#define BIT6              0x40
#define BIT7              0x80



int main(){
    
    P2M0 = 0xff;
    P2M1 = 0x00; 
    // P2PU = 0xff;
	LCD_Init();

	while(1){	
        LCD_Clear(RED);delay_ms(1000);	
        LCD_Clear(GREEN);delay_ms(1000);	
        LCD_Clear(BLUE);delay_ms(1000);
    }   
}