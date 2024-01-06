#include "cc2510fx.h"
#include "ioCCxx10_bitdef.h"
#include <stdbool.h>
#include <stdint.h>

#define BV(x) (1 << (x))

#define NFC_FD P1_1
#define NFCFLASH_PWR P1_0
#define FLASH_CS P1_4
#define FLASH_MOSI P1_6
#define FLASH_MISO P1_7
#define FLASH_SCK P1_5

#define NFC_B_FD 1
#define NFCFLASH_B_PWR 0
#define FLASH_B_CS 4
#define FLASH_B_MOSI 6
#define FLASH_B_MISO 7
#define FLASH_B_SCK 5

#define LED_SW_SUM              P2_2
#define LED_SW_WHITE            P2_1
#define LED_SW_RED               P1_5
#define LED_SW_BLUE              P1_6
#define LED_SW_GREEN             P1_7

SFRX(TEST0, 0XDF25);
SFRX(TEST1, 0XDF24);
SFRX(TEST2, 0XDF23);

void write_data(char *data, unsigned char size);
void radio_init(void);
void system_clock_init(void);
void NfcFlash_IoInit(void);
void Flash_get_id(uint8_t *data_ptr);

int main(){

    system_clock_init();
    radio_init();
    NfcFlash_IoInit();

    NFCFLASH_PWR = 1;
    
    while(1){
        uint8_t id[3];
        Flash_get_id(id);
        write_data(id, 2);
        // while(!(RFTXRXIF));
        
        for(unsigned short i = 0; i < 150; i++){
            unsigned short j = 0x0fff;
            while(j--);
        }
    } 
    
}

void system_clock_init(void){
    SLEEP &= ~SLEEP_OSC_PD;
    while( !(SLEEP & SLEEP_XOSC_S) );
    CLKCON = (CLKCON & ~(CLKCON_CLKSPD | CLKCON_OSC)) | CLKSPD_DIV_1;
    while (CLKCON & CLKCON_OSC);

    SLEEP |= SLEEP_OSC_PD;
}
void radio_init(void){
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

void NfcFlash_IoInit(void)
{
    P1DIR |= BV(FLASH_B_CS);
    FLASH_CS = 1; // Flas CS
    NFCFLASH_PWR = 0;
    P1DIR |= BV(NFCFLASH_B_PWR) // NFCPWR output
        | BV(FLASH_B_SCK) 
        | BV(FLASH_B_MOSI) 
        | BV(FLASH_B_CS); 
    P1DIR &= ~(BV(FLASH_B_MISO));
    PERCFG |= 0x02;       // USART1 alternative 2 location SPI
    U1CSR = 0;             // SPI mode/master/clear flags
    P1SEL |= BV(FLASH_B_SCK) | BV(FLASH_B_MOSI) | BV(FLASH_B_MISO);                        // MISO/MOSI/CLK peripheral functions // SS仅当从机使用时才配置为外设
    U1BAUD = 0;            // baud M
    U1GCR = U1GCR_ORDER | 17; // SCK-low idle, DATA-1st clock edge, MSB first

    P1DIR &= ~BV(NFC_B_FD);
}

inline void Flash_Select(bool select)
{
    FLASH_CS = !select;
}

static uint8_t Flash_ExchangeData(uint8_t da)
{
    U1DBUF = da;
    while (U1CSR & 0x01)
    {
        *(__xdata volatile uint8_t*)0xFE00 = U1CSR;
    }
    return U1DBUF;
}

void spi_write(uint8_t da){
    U1CSR &= ~U1CSR_TX_BYTE;
    U1DBUF = da;
    while((U1CSR & U1CSR_TX_BYTE));
}

void spi_read(uint8_t *da){
    /* U1CSR |= U1CSR_RE;
    U1CSR &= ~U1CSR_RX_BYTE;
    while(!(U1CSR & U1CSR_RX_BYTE));
    *da = U1DBUF; */
    U1DBUF = 0x00;
     while (U1CSR & U1CSR_ACTIVE);
    *da = U1DBUF;

    // U1CSR &= ~U1CSR_RE;
}

void Flash_get_id(uint8_t *data_ptr){
    Flash_Select(true);
    // Flash_ExchangeData(0x90u);
    // Flash_ExchangeData(0x00u); // 3 Byte dummy
    // Flash_ExchangeData(0x00u);
    // Flash_ExchangeData(0x00u);
    spi_write(0x90u);
    spi_write(0x00u);
    spi_write(0x00u);
    spi_write(0x00u);
    // *data_ptr = Flash_ExchangeData(0xFFu); // 0xEF
    // *(data_ptr + 1) = Flash_ExchangeData(0xFFu); // 0x11
    spi_read(data_ptr);
    spi_read(data_ptr + 1);
    Flash_Select(false);
}