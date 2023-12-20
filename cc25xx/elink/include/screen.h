#include "mcs51/cc2510fx.h"

//IO settings
#define EPD_PWR 	P0_0
#define BUSY_Pin    P1_3
#define RES_Pin     P2_0 
#define DC_Pin      P1_2 
#define CS_Pin      P0_1 
#define SCK_Pin     P0_5 
#define SDI_Pin     P0_3

#define LED_SW_SUM          P2_2
#define LED_SW_WHITE        P2_1

#define EPD_W21_MOSI_0  SDI_Pin = 0
#define EPD_W21_MOSI_1  SDI_Pin = 1 

#define EPD_W21_CLK_0   SCK_Pin = 0
#define EPD_W21_CLK_1   SCK_Pin = 1

#define EPD_W21_CS_0    CS_Pin = 0
#define EPD_W21_CS_1    CS_Pin = 1

#define EPD_W21_DC_0    DC_Pin = 0
#define EPD_W21_DC_1    DC_Pin = 1
#define EPD_W21_RST_0   RES_Pin = 0
#define EPD_W21_RST_1   RES_Pin = 1
#define isEPD_W21_BUSY  BUSY_Pin



void IO_init(void);

void loop(void);
