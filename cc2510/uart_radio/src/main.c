#include "uart.h"
#include "dma.h"

// Baudrate = 115200 (U0BAUD.BAUD_M = 34, U0GCR.BAUD_E = 12)
#define UART_BAUD_M             34
#define UART_BAUD_E             12

#define BIT0                    0x01
#define BIT1                    0x02
#define BIT2                    0x04
#define BIT3                    0x08
#define BIT4                    0x10
#define BIT5                    0x20
#define BIT6                    0x40
#define BIT7                    0x80

#define LED_SW_SUM              P2_2
#define LED_SW_WHITE            P2_1
#define LE_SW_RED               P1_5
#define LE_SW_BLUE              P1_6
#define LE_SW_GREEN             P1_7

typedef struct {
    uint8 SRCADDRH;
    uint8 SRCADDRL;
    uint8 DESTADDRH;
    uint8 DESTADDRL;

    uint8 LENH : 5;
    uint8 VLEN : 3;
    
    uint8 LENL : 8;

    uint8 TRIG : 5;
    uint8 TMODE : 2;
    uint8 WORDSIZE : 1;

    uint8 PRIORITY : 2;
    uint8 M8 : 1;
    uint8 IRQMASK : 1;
    uint8 DESTINC : 2;
    uint8 SRCINC : 2;
} DMA_DESC;

static DMA_DESC __xdata DMA_CH_CONFIG[5];

void uart1_tx_StartDMA( 
                    DMA_DESC *dma_config, 
                    uint8 chan_number,
                    uint8 *tx_buf,
                    uint16 buf_size);
int main(){

    system_clock_init();

    // uart_init();

    // uint8 tx[21] = {0xfe, 0xee, 0x80, 0xcc, 0x89, 0x66};
    // uint8 __xdata ax[8] = {0x07, 0x22, 0x22, 0x80, 0x81, 0x22, 0x22, 0x07};

    // for(unsigned int i = 0; i < 10; i++){
        
    //     for(unsigned int i = 0; i < 65535; i++){
    //         __asm__("NOP");
    //     }
    // }

    // // uint16 __xdata tx[8] = {0xA5B3, 0xA687, };
    // // unsigned char rx_buf[100];

    // // DMA_CH_CONFIG->SRCADDRH = (uint16)(tx) >> 8;
    // // DMA_CH_CONFIG->SRCADDRL = (uint16)(tx) & 0xff;
    // // uart1Send(ax, 8);
    // uart1_tx_StartDMA(DMA_CH_CONFIG, 0, tx, 16);
    // for(unsigned int i = 0; i < 10; i++){
        
    //     for(unsigned int i = 0; i < 65535; i++){
    //         __asm__("NOP");
    //     }
    // }
    // uart1_tx_StartDMA(DMA_CH_CONFIG, 0, tx, 16);
    // // uart1Send((uint8*)DMA_CH_CONFIG, 8);
    // unsigned short count = 0;
    FSCTRL1   = 0x0A;   // Frequency synthesizer control.
    FSCTRL0   = 0x00;   // Frequency synthesizer control.
    FREQ2     = 0x5D;   // Frequency control word, high byte.
    FREQ1     = 0x93;   // Frequency control word, middle byte.
    FREQ0     = 0xB1;   // Frequency control word, low byte.
    MDMCFG4   = 0x86;   // Modem configuration.
    MDMCFG3   = 0x83;   // Modem configuration.
    MDMCFG2   = 0x30;   // Modem configuration.
    MDMCFG1   = 0x22;   // Modem configuration.
    MDMCFG0   = 0xF8;   // Modem configuration.
    CHANNR    = 0x00;   // Channel number.
    DEVIATN   = 0x00;   // Modem deviation setting (when FSK modulation is enabled).
    FREND1    = 0x56;   // Front end RX configuration.
    FREND0    = 0x10;   // Front end RX configuration.
    MCSM0     = 0x14;   // Main Radio Control State Machine configuration.
    FOCCFG    = 0x16;   // Frequency Offset Compensation Configuration.
    BSCFG     = 0x6C;   // Bit synchronization Configuration.
    AGCCTRL2  = 0x03;   // AGC control.
    AGCCTRL1  = 0x40;   // AGC control.
    AGCCTRL0  = 0x91;   // AGC control.
    FSCAL3    = 0xA9;   // Frequency synthesizer calibration.
    FSCAL2    = 0x0A;   // Frequency synthesizer calibration.
    FSCAL1    = 0x00;   // Frequency synthesizer calibration.
    FSCAL0    = 0x11;   // Frequency synthesizer calibration.
    // TEST2     = 0x88;   // Various test settings.
    // TEST1     = 0x31;   // Various test settings.
    // TEST0     = 0x09;   // Various test settings.
    PA_TABLE0 = 0xFE;   // PA output power setting.
    PKTCTRL1  = 0x04;   // Packet automation control.
    PKTCTRL0  = 0x22;   // Packet automation control.
    ADDR      = 0x00;   // Device address.
    PKTLEN    = 0xFF;   // Packet length.

    /* Settings not from SmartRF� Studio. Setting both sync word registers to
     * 0xAA = 0b10101010, i.e., the same as the preamble pattern. Not necessary,
     * but gives control of what the radio attempts to transmit.
     */
    SYNC1     = 0xAA;
    SYNC0     = 0xAA;

    /* Put radio in TX. */
    RFST      = RFST_STX;

    /* Wait for radio to enter TX. */
    while ((MARCSTATE & MARCSTATE_MARC_STATE) != MARC_STATE_TX);

    /* Radio is now in TX. Infinite loop. */
 
    while (1){
        // ax[0] = 0x80;
        // count++;
        // tx[18] = '0' + count % 10;
        // tx[17] = '0' + count / 10 % 10;
        // tx[16] = '0' + count / 100 % 10;
        // tx[15] = '0' + count / 1000 % 10;
        // tx[14] = '0' + count / 10000;
        // uart1Send(tx, 21);
    }
    

}

void uart1_tx_StartDMA( DMA_DESC *dma_config,
                        uint8 chan_number,
                        uint8 *tx_buf,
                        uint16 buf_size){


    // dma_config->SRCADDRH = (uint16)(tx_buf) >> 8;
    dma_config->SRCADDRH = (uint16)(tx_buf) >> 8;
    dma_config->SRCADDRL = (uint16)(tx_buf) & 0x00ff;

    dma_config->DESTADDRH = ((uint16)(&X_U1DBUF) >> 8) & 0x00ff;
    dma_config->DESTADDRL = (uint16)(&X_U1DBUF) & 0x00ff;
    dma_config->LENH = (buf_size >>8) & 0xff;
    dma_config->LENL = (buf_size) & 0xff;

    // Use fixed length DMA transfer count;
    dma_config->VLEN = DMA_VLEN_FIXED;

    // Transfer a single word after each DMA trigger;
    dma_config->WORDSIZE = DMA_WORDSIZE_BYTE;
    dma_config->TMODE = DMA_TMODE_SINGLE;

    dma_config->TRIG = DMA_TRIG_UTX1;

    dma_config->SRCINC = DMA_SRCINC_1;
    dma_config->DESTINC = DMA_DESTINC_0;

    dma_config->IRQMASK = DMA_IRQMASK_ENABLE;
    dma_config->M8 = DMA_M8_USE_8_BITS;
    dma_config->PRIORITY = DMA_PRI_LOW;

    DMA0CFGH = (uint8)((uint16)(dma_config)>>8);
    DMA0CFGL = (uint8)((uint16)(dma_config) & 0xff);

    DMAARM = 0;
    DMAARM |= DMAARM0;

    for(int i = 0; i < 45; i++){
        __asm__("NOP");
    }

    EA = 1;
    DMAIE = 1;
    DMAIF = 0;

    U1DBUF = tx_buf[0];
}
