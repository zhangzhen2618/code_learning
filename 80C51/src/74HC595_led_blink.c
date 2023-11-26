#include "stc80c51.h"

#define     LCK     P3_6
#define     SCK     P3_5
#define     SDI     P3_4

void delay(unsigned int count){

    for (unsigned int i = 0; i < count; i++) {
        
    }
    
}
int main(void){

    unsigned char led = 0xFF;
    int k = 9;
    while (1){
        for(unsigned char i = 0; i < 8; i++){
            LCK = 0;
            SDI = (led >> i) & 0x01;
            SCK = 0;
            LCK = 1;
            // delay(10);
            SCK = 1;
            // delay(10);

        }
        // if (led == 0xFF){
        // }
        if (k == 9){
            int j = 5;
            while(j--)
                delay(65535);
        }
        led >>= 1;
        k--;
        if (k == 0){
            k = 9;
            led = 0xFF;
        }
        delay(65535);
        P2_0 = !P2_0;
    }
    
}

