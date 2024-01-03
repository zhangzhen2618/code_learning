#include "screen.h"
#include "ioCCxx10_bitdef.h"

void system_clock_init();

void main(void){

	system_clock_init();
	
	IO_init();
	loop();
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