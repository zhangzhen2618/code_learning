#include "cc2510fx.h"
#include "ioCCxx10_bitdef.h"

#define LED_SW_SUM              P2_2
#define LED_SW_WHITE            P2_1
#define LED_SW_RED               P1_5
#define LED_SW_BLUE              P1_6
#define LED_SW_GREEN             P1_7

SFRX(TEST0, 0XDF25);
SFRX(TEST1, 0XDF24);
SFRX(TEST2, 0XDF23);

void write_data(char *data, unsigned char size);

int main(){

    SLEEP &= ~SLEEP_OSC_PD;
    while( !(SLEEP & SLEEP_XOSC_S) );
    CLKCON = (CLKCON & ~(CLKCON_CLKSPD | CLKCON_OSC)) | CLKSPD_DIV_1;
    while (CLKCON & CLKCON_OSC);

    SLEEP |= SLEEP_OSC_PD;
    P2DIR |= 3 << 1;
    P1DIR = 0xff;
    LED_SW_WHITE = 0;
    LED_SW_SUM = 1;

    /* RF settings SoC: CC2510 */
    // config from smart studio 7.0 expert mode last config
    // Data rate 500kBaud Mod:MSK RX_BW: 812KHZ
    PKTCTRL0  = 0x05; // packet automation control 
    FSCTRL1   = 0x10; // frequency synthesizer control 
    FREQ2     = 0x5D; // frequency control word, high byte 
    FREQ1     = 0x93; // frequency control word, middle byte 
    FREQ0     = 0xB1; // frequency control word, low byte 
    MDMCFG4   = 0x0E; // modem configuration 
    MDMCFG3   = 0x3B; // modem configuration 
    MDMCFG2   = 0x73; // modem configuration 
    MDMCFG1   = 0x42; // modem configuration 
    DEVIATN   = 0x00; // modem deviation setting 
    MCSM0     = 0x14; // main radio control state machine configuration 
    FOCCFG    = 0x1D; // frequency offset compensation configuration 
    BSCFG     = 0x1C; // bit synchronization configuration 
    AGCCTRL2  = 0xC7; // agc control  
    AGCCTRL0  = 0xB2; // agc control  
    FSCAL3    = 0xEA; // frequency synthesizer calibration 
    FSCAL1    = 0x00; // frequency synthesizer calibration 
    FSCAL0    = 0x11; // frequency synthesizer calibration 
    TEST1     = 0x31; // various test settings 
    TEST0     = 0x09; // various test settings 
    PA_TABLE0 = 0xFE; // pa power setting 
    IOCFG2    = 0x2E; // radio test signal configuration (p1_7) 



    // PKTLEN = 0x03;
    // SYNC1 = 0XAA;
    // SYNC0 = 0XAA;
    char helo[] = "Hello cc2510 radio!!!";

    while(1){
        write_data(helo, sizeof(helo));
        // while(!(RFTXRXIF));
        
        LED_SW_WHITE = !LED_SW_WHITE;
        for(unsigned short i = 0; i < 150; i++){
            unsigned short j = 0x0fff;
            while(j--);
        }
    } 
    
}

void write_data(char *da, unsigned char size){
    // enter SIDLE
    RFST = RFST_SIDLE;
    while((MARCSTATE & MARCSTATE_MARC_STATE) != MARC_STATE_IDLE);

    // enter STX
    RFST = RFST_STX;
    while((MARCSTATE & MARCSTATE_MARC_STATE) != MARC_STATE_TX);

    // Write the packet size
    while(!(RFTXRXIF));
    RFTXRXIF = 0;
    RFD = size;

    for(unsigned i = 0; i != size; i++){
        while(!(RFTXRXIF));
        RFTXRXIF = 0;
        RFD = *(da + i);
    }

}