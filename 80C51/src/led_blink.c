#include "stc80c51.h"

void delay(unsigned char t){
    while (t--){
        for(unsigned i = 0; i != 255; i++){
            for(unsigned j = 0; j != 255; j++){

            }
        }
    }
    
}

unsigned char flag = 0;

int main(){
    while (1){

        if (P2 == 0){
            flag = 1;
        }

        if (P2 == 0xFF){
            flag = 0;
        }
        P2 <<= 1;
        P2 += flag; 
        delay(2);
    }
}