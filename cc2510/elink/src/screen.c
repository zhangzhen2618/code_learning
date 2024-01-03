#include "screen.h"
#include "picture.h"
#include "ioCCxx10_bitdef.h"

////////FUNCTION//////
void driver_delay_us(unsigned int xus);
void driver_delay_xms(unsigned long xms);
void DELAY_S(unsigned int delaytime);     
void SPI_Delay(unsigned char xrate);
void SPI_Write(unsigned char value);
void EPD_W21_WriteDATA(unsigned char command);
void EPD_W21_WriteCMD(unsigned char command);
unsigned char pgm_read_byte(void *addr){
	return *(unsigned char *)(addr);
}

//EPD
void EPD_W21_Init(void);
void EPD_init(void);
void PIC_display(const unsigned char* picData_old,const unsigned char* picData_new);
void EPD_sleep(void);
void EPD_refresh(void);
void lcd_chkstatus(void);
void PIC_display_Clean(void);
unsigned char HRES,VRES_byte1,VRES_byte2;

#define BIT0              0x01
#define BIT1              0x02
#define BIT2              0x04
#define BIT3              0x08
#define BIT4              0x10
#define BIT5              0x20
#define BIT6              0x40
#define BIT7              0x80

// Baudrate = 230400 (U0BAUD.BAUD_M = 34, U0GCR.BAUD_E = 12)
#define UART_BAUD_M       34
#define UART_BAUD_E       13

void IO_init() {
    P0DIR |= BIT0 | BIT1 ;
    P1DIR |= BIT2;
    P2DIR |= BIT0;
    P0 |= BIT0;
    EPD_PWR = 0;

    // SPI_0 connect to epd link
    P0SEL |= BIT3 | BIT5; // P0.3, P0.5 as alternative
    // Configure the baudrate as 115200
    U0BAUD = UART_BAUD_M;
    U0GCR &= ~U0GCR_BAUD_E;
    U0GCR |= UART_BAUD_E;

    U0GCR |= U0GCR_CPOL | U0GCR_ORDER;

}
//Tips//
/*When the electronic paper is refreshed in full screen, the picture flicker is a normal phenomenon, and the main function is to clear the display afterimage in the previous picture.
  When the local refresh is performed, the screen does not flash.*/
/*When you need to transplant the driver, you only need to change the corresponding IO. The BUSY pin is the input mode and the others are the output mode. */

void loop() {

    //PICTURE1
    EPD_init(); //EPD init
		PIC_display_Clean();
    PIC_display(gImage_black1,gImage_red1);//EPD_picture1
    EPD_refresh();//EPD_refresh   
    EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!
    DELAY_S(3);
    
    
    //PICTURE Clean
    //  EPD_init(); //EPD init
    // PIC_display_Clean();
    // EPD_refresh();//EPD_refresh   
    // EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!
    while(1);

  


}
/////////////////////delay//////////////////////////////////////
void driver_delay_us(unsigned int xus)  //1us
{
  for(;xus>1;xus--);
}
void driver_delay_xms(unsigned long xms) //1ms
{  
    unsigned long i = 0 , j=0;

    for(j=0;j<xms;j++)
  {
        for(i=0; i<256; i++);
    }
}
void DELAY_S(unsigned int delaytime)     
{
  int i,j,k;
  for(i=0;i<delaytime;i++)
  {
    for(j=0;j<4000;j++)           
    {
      for(k=0;k<222;k++);
                
    }
  }
}
//////////////////////SPI///////////////////////////////////
void SPI_Delay(unsigned char xrate)
{
  unsigned char i;
  while(xrate)
  {
    for(i=0;i<2;i++);
    xrate--;
  }
}


void SPI_Write(unsigned char value)                                    
{                                                           
    U0CSR &= ~U0CSR_TX_BYTE;
    U0DBUF = value;
    while(!(U0CSR & U0CSR_TX_BYTE));
}

void EPD_W21_WriteCMD(unsigned char command)
{
  SPI_Delay(1);
  EPD_W21_CS_0;                   
  EPD_W21_DC_0;   // command write
  SPI_Write(command);
  EPD_W21_CS_1;
}
void EPD_W21_WriteDATA(unsigned char command)
{
  SPI_Delay(1);
  EPD_W21_CS_0;                   
  EPD_W21_DC_1;   // command write
  SPI_Write(command);
  EPD_W21_CS_1;
}



/////////////////EPD settings Functions/////////////////////
void EPD_W21_Init(void)
{
  EPD_W21_RST_0;    // Module reset
  driver_delay_xms(10);
	//delay(100); //At least 10ms
  EPD_W21_RST_1;
  //delay(100);  
	driver_delay_xms(10);
}
void EPD_init(void)
{
    EPD_W21_Init(); //Electronic paper IC reset
    EPD_W21_WriteCMD(0x04);  
    lcd_chkstatus(); //waiting for the electronic paper IC to release the idle signal
    
    EPD_W21_WriteCMD(0x00);     //panel setting
    EPD_W21_WriteDATA(0x0f);    //LUT from OTP£¬400x300
  }
void EPD_refresh(void)
{
    EPD_W21_WriteCMD(0x12);     //DISPLAY REFRESH   
    driver_delay_xms(100);          //!!!The delay here is necessary, 200uS at least!!!     
    lcd_chkstatus();
} 
void EPD_sleep(void)
{
    EPD_W21_WriteCMD(0X50);  //VCOM AND DATA INTERVAL SETTING  
    EPD_W21_WriteDATA(0xf7);
       
    EPD_W21_WriteCMD(0X02);   //power off
    lcd_chkstatus();
    EPD_W21_WriteCMD(0X07);   //deep sleep
    EPD_W21_WriteDATA(0xA5);
}


void PIC_display(const unsigned char* picData_old,const unsigned char* picData_new)
{
    unsigned int i;
    EPD_W21_WriteCMD(0x10);        //Transfer old data
    for(i=0;i<15000;i++)      
  {
    EPD_W21_WriteDATA(pgm_read_byte((void *)(&picData_old[i])));
  }
  
    EPD_W21_WriteCMD(0x13);        //Transfer new data
    for(i=0;i<15000;i++)      
  {
    EPD_W21_WriteDATA(pgm_read_byte((void *)(&picData_new[i])));
  }
}
void PIC_display_Clean(void)
{
    unsigned int i;
    EPD_W21_WriteCMD(0x10);        //Transfer old data
    for(i=0;i<15000;i++)      
  {
    EPD_W21_WriteDATA(0xff);
  }
  
    EPD_W21_WriteCMD(0x13);        //Transfer new data
    for(i=0;i<15000;i++)      
  {
    EPD_W21_WriteDATA(0xff);
  }
}
void lcd_chkstatus(void)
{
  unsigned char busy;
  do
  {
    EPD_W21_WriteCMD(0x71);
    busy = isEPD_W21_BUSY;
    busy =!(busy & 0x01);        
  }
  while(busy);   
  driver_delay_xms(200);                       
}
//////////////////////////////////END/////////////////////////////////////////
