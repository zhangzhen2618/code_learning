#ifndef __UART_H__
#define __UART_H__

#include "cc2510fx.h"
#include "ioCCxx10_bitdef.h"

typedef signed   short  int16;
typedef unsigned short  uint16;

// Baudrate = 115200 (U0BAUD.BAUD_M = 34, U0GCR.BAUD_E = 12)
#define UART_BAUD_M       34
#define UART_BAUD_E       12

#define BIT0              0x01
#define BIT1              0x02
#define BIT2              0x04
#define BIT3              0x08
#define BIT4              0x10
#define BIT5              0x20
#define BIT6              0x40
#define BIT7              0x80

void system_clock_init();
void uart_init();
void uart1Send(const char* data, uint16 len);
uint16 uart1Receive(unsigned char *buf);
#endif