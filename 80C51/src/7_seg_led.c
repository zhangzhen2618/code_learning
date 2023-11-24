#include "stc80c51.h"

#define TIMER_RESET_VALUE       61548 // 2ms
#define NUMBER_COUNT            500
#define SEG_NUM                 8

unsigned char seg[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
unsigned char seg_value[SEG_NUM] = {0};

void timer_isr(void) __interrupt(1) __using(1){

    TL0 = TIMER_RESET_VALUE & 0XFF; // 设置计时器的高低位的值
    TH0 = TIMER_RESET_VALUE >> 8;

    // P2_0 = !P2_0;
    static unsigned char seg_ptr = 0;
    static unsigned int number_count = NUMBER_COUNT;

    P2 &= 0xE3;
    P2 |= (seg_ptr) << 2;

    P0 = seg[seg_value[seg_ptr++]];
    seg_ptr %= SEG_NUM;

    number_count--;
    if (number_count == 0){
        number_count = NUMBER_COUNT;
        for(unsigned char i = 0; i < SEG_NUM; i++){
            seg_value[i]++;
            seg_value[i] %= 10;
        }
    }


}

int main(){

    TMOD = 0X01;// 配置计数器为16位模式
    TL0 = TIMER_RESET_VALUE & 0XFF; // 设置计时器的高低位的值
    TH0 = TIMER_RESET_VALUE >> 8;

    TR0 = 1; // 定时器0使能
    ET0 = 1; // 中断1， 使能
    EA = 1; // 总中断使能
    
 
    while(1){
       
    }

}