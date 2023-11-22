#include "stc80c51.h"

void delay(unsigned char t){
    while (t--){
        for(unsigned i = 0; i != 255; i++){
            for(unsigned j = 0; j != 255; j++){

            }
        }
    }
    
}
int main(){
    P2 = 0xff;
    delay(2);
    P2 = 0x00;
    delay(2);

    return 0;
}