#include "STC8H.h"  

#define     MAIN_Fosc       24000000L

typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;

void  delay_ms(u8 ms);

/******************** 锟斤拷锟斤拷锟斤拷 **************************/
void main(void)
{
    P_SW2 |= 0x80;  

    P0M1 = 0x00;   P0M0 = 0x00;   
    P1M1 = 0x00;   P1M0 = 0x00;   
    P2M1 = 0x00;   P2M0 = 0x00;   
    P3M1 = 0x00;   P3M0 = 0x00;   
    P4M1 = 0x00;   P4M0 = 0x00;   
    P5M1 = 0x00;   P5M0 = 0x00;   
    P6M1 = 0x00;   P6M0 = 0x00;   
    P7M1 = 0x00;   P7M0 = 0x00;   

    while(1){

        P2_0 = 0;		//LED On
        delay_ms(100);
        P2_0 = 1;		//LED Off
        P2_1 = 0;		//LED On
        delay_ms(250);
        P2_1 = 1;		//LED Off
        P2_2 = 0;		//LED On
        delay_ms(250);
        P2_2 = 1;		//LED Off
        P2_3 = 0;		//LED On
        delay_ms(250);
        P2_3 = 1;		//LED Off
        P2_4 = 0;		//LED On
        delay_ms(250);
        P2_4 = 1;		//LED Off
        P2_5 = 0;		//LED On
        delay_ms(250);
        P2_5 = 1;		//LED Off
        P2_6 = 0;		//LED On
        delay_ms(250);
        P2_6 = 1;		//LED Off
        P2_7 = 0;		//LED On
        delay_ms(250);
        P2_7 = 1;		//LED Off
    }
}


void delay_ms(u8 ms)
{
     u16 i;
     do{
          i = MAIN_Fosc / 20000;
          while(--i);   //10T per loop
     }while(--ms);
}
