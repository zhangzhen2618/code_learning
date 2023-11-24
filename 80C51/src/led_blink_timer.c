#include "stc80c51.h"

#define TIMER_RESET_VALUE   63542
#define TIMER_COUNTER       500


void timer_isr(void) __interrupt(1) __using(1){
    static unsigned count = TIMER_COUNTER;
    static unsigned char flag = 0;
    TL0 = TIMER_RESET_VALUE;
    TH0 = TIMER_RESET_VALUE >> 8;
    if (count--){
        return;
    }

    if (P2 == 0){
        flag = 1;
    }

    if (P2 == 0xFF){
        flag = 0;
    }
    P2 <<= 1;
    P2 += flag;
    count = TIMER_COUNTER;
}

int main(){
    // 计数器0 中断
    TMOD |= 0X01;
    TL0 = TIMER_RESET_VALUE;
    TH0 = TIMER_RESET_VALUE >> 8;

    TR0 = 1;
    ET0 = 1;
    EA = 1;

    while(1);
}