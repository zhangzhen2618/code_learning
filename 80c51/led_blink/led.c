#include "stc80c51.h"

void led_blink(){

    TMOD = 1;
    char flag = 0xFF;
    while(1){
        TH0 = 0xfe;
        TL0 = 0xC;
        TR0 = 1;

        while (TF0 != 1);

        TR0 = 0;
        TF0 = 0;
        flag = !flag;
        P2 = flag;

    }
}