#include "cc2510fx.h"
#include "ioCCxx10_bitdef.h"

#define LED_SW_SUM          P2_2
#define LED_SW_WHITE        P2_1
#define LE_SW_RED           P1_5
#define LE_SW_BLUE           P1_6
#define LE_SW_GREEN           P1_7

void system_clock_init();

int main(){

    system_clock_init();

    P2DIR = 0XFF;
    P1DIR = 0xff;
    P0DIR = 0xff;

    P0 = 0;
    P1 = 0;
    P2 = 0;
    LED_SW_SUM = 1;

    EA = 1;
    T2IE = 1;
    T2CTL |= T2CTL_INT;

    T2PR = 1;

    // Set [T2CTL.TIP] to 64 and start Timer 2 in free running mode
    T2CTL = (T2CTL & ~T2CTL_TIP) | T2CTL_TIP_64 | T2CTL_TIG;

    T3CTL = T3CTL_DIV_128 | T3CTL_START | T3CTL_OVFIM |
        T3CTL_CLR | T3CTL_MODE_FREERUN;
    T3IE = 1;
    while(1){
       
    }
}

void system_clock_init(){

    //Set the system clock source to 26Mhz XSOC to support maximum transfer speed,
    SLEEP &= ~SLEEP_OSC_PD; // Power up the HS RCOSC and XSOC
    while (!(SLEEP & SLEEP_XOSC_S)); // Waiting the XOSC to stable.
    CLKCON &= ~(CLKCON_CLKSPD | CLKCON_OSC); // clear the System clock speed setting bit;
    // CLKCON = (CLKCON & ~(CLKCON_CLKSPD | CLKCON_OSC)) | CLKSPD_DIV_1;
    // When the CLKCON.OSC bit set to 0, system clock source set to the XOSC
    CLKCON |= CLKSPD_DIV_1 | TICKSPD_DIV_128; // The systemc clock div, set to 000, means, system clock is 26Mhz
    while(CLKCON & CLKCON_OSC); // Waiting to the system clock source from hs RCOSC to the XOSC;
    SLEEP |= SLEEP_OSC_PD; // Let the system not set by toggle the CLKCON.OSC

    // !!! Remember change the system clock source, must wait the RCOSC or XOSC to stable;!!!
}

void timer_isr_2(void) __interrupt(T2_VECTOR) __using(T2_VECTOR){
    LE_SW_RED = !LE_SW_RED;
}

int k = 256;
void timer_isr_1(void) __interrupt(T3_VECTOR) __using(T3_VECTOR){
    T3OVFIF = 0;
    T3IF = 0;
    // if (k == 0){
    //     k = 1000;
        LED_SW_WHITE = !LED_SW_WHITE;
    // }
    // k--;
}