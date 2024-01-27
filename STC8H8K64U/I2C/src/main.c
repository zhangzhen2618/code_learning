#include "STC8H.h"
#include "stc8h_bitdef.h"
#include <math.h>      
#include <stdio.h>   
#include <stdint.h>	
#include <stdbool.h>

#define     MAIN_Fosc       48000000L   //定义主时钟
#define     BRT             (65536 - (MAIN_Fosc / 115200 + 2) / 4)

#define	    SCL             P2_5      //IIC时钟引脚定义
#define     SDA             P2_4      //IIC数据引脚定义

#define	SlaveAddress   0xA6	  //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改
                              //ALT  ADDRESS引脚接地时地址为0xA6，接电源时地址为0x3A
uint8_t BUF[8];                         //接收数据缓存区      	
uint8_t ge,shi,bai,qian,wan;           //显示变量
int  dis_data;                      //变量

char buf[100];
volatile bool busy;
volatile bool I2C_busy;

void UartInit(void);
void UartSend(char dat);
void UartSendStr(char *str);

void delay(unsigned int k);
void Init_ADXL345(void);             //初始化ADXL345

void  Single_Write_ADXL345(uint8_t REG_Address,uint8_t REG_data);   //单个写入数据
uint8_t Single_Read_ADXL345(uint8_t REG_Address);                   //单个读取内部寄存器数据

//------------------------------------
void Delay5us();
void Delay5ms();
void ADXL345_Start();
void ADXL345_Stop();
void ADXL345_SendACK(bool ack);
bool  ADXL345_RecvACK();
void ADXL345_SendByte(uint8_t dat);
uint8_t ADXL345_RecvByte();
void Multiple_read_ADXL345(void);

//*********************************************************
//******主程序********
//*********************************************************
void main() { 
    P_SW2 |= P_SW2_EAXFR;  //扩展寄存器XFR访问使能
    P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0x00;
    P1M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P3M0 = 0x00;
    P3M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;

    P2M0 |= 3;

    P_SW2 |= 0X10;
    I2CCFG = 0xe0; // i2c master
    I2CMSST = 0x00;
    
    UartInit();
    // Interrupt enable
    ES = 1;
    EA = 1;

    uint8_t devid;
    P2_1 =! P2_1;
    Init_ADXL345();                 //初始化ADXL345
    while(1)                         //循环
    {
        P2_1 =! P2_1;
        devid=Single_Read_ADXL345(0X00);//读出的数据为0XE5,表示正确
        Multiple_read_ADXL345();
        int x = BUF[1];
        x <<= 8;
        x += BUF[0];
        x *= 39;
        int y = BUF[3];
        y <<= 8;
        y += BUF[2];
        y *= 39;
        int z = BUF[5];
        z <<= 8;
        z += BUF[4];
        z *= 39;

        sprintf(buf, "devid: 0X%X, x : %d, y: %d, z: %d,\n", devid, x, y, z);
        UartSendStr(buf);
        delay(2000);                    //延时            
    }
}

//-----------------------------------
void UartInit(void){
    SCON = 0x50; // 模式1，接收使能
    T2L = BRT;
    T2H = BRT >> 8;
    
    AUXR = 0X15;
    busy = 0;
}

void UartSend(char dat){
    while (busy);
    busy = 1;
    SBUF = dat; 
}

void UartSendStr(char *str){
    while(*str){
        UartSend(*str++);
    }
}


void Uartlsr() __interrupt(UART1_VECTOR) __using(UART1_VECTOR){
    if (TI){
        TI = 0;
        busy = 0;
    }

    if (RI){
        RI = 0;
    }
}

/*******************************/
void delay(unsigned int k)	
{						
unsigned int i,j;				
for(i=0;i<k;i++)
{			
for(j=0;j<121;j++)			
{;}}						
}
/*******************************/

/**************************************
延时5微秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数，注意时钟过快时需要修改
当改用1T的MCU时,请调整此延时函数
**************************************/
void Delay5us()
{
    for(uint8_t i = 0; i < 150; i++);
}

/**************************************
延时5毫秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数
当改用1T的MCU时,请调整此延时函数
**************************************/
void Delay5ms()
{
    uint16_t n = 10000;

    while (n--);
}

/**************************************
起始信号
**************************************/
void ADXL345_Start()
{
    // SDA = 1;                    //拉高数据线
    // SCL = 1;                    //拉高时钟线
    // Delay5us();                 //延时
    // SDA = 0;                    //产生下降沿
    // Delay5us();                 //延时
    // SCL = 0;                    //拉低时钟线
    I2C_busy = 1;
    I2CMSCR = 0x81;
    while(I2C_busy);
}

/**************************************
停止信号
**************************************/
void ADXL345_Stop()
{
    // SDA = 0;                    //拉低数据线
    // SCL = 1;                    //拉高时钟线
    // Delay5us();                 //延时
    // SDA = 1;                    //产生上升沿
    // Delay5us();                 //延时
    I2C_busy = 1;
    I2CMSCR = 0x86;
    while (I2C_busy);
}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void ADXL345_SendACK(bool ack)
{
    // SDA = ack;                  //写应答信号
    // SCL = 1;                    //拉高时钟线
    // Delay5us();                 //延时
    // SCL = 0;                    //拉低时钟线
    // Delay5us();                 //延时
    if (ack){
        I2CMSST = 0x01;
    }else{
        I2CMSST = 0x00;
    }
    I2C_busy = 1;
    I2CMSCR = 0x85;
    while(I2C_busy);
}

/**************************************
接收应答信号
**************************************/
bool ADXL345_RecvACK()
{
    // SCL = 1;                    //拉高时钟线
    // Delay5us();                 //延时
    // CY = SDA;                   //读应答信号
    // SCL = 0;                    //拉低时钟线
    // Delay5us();                 //延时
    I2C_busy = 1;
    I2CMSCR = 0x83;
    while(I2C_busy);
    return 1;
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void ADXL345_SendByte(uint8_t dat)
{
    // uint8_t i;

    // for (i=0; i<8; i++)         //8位计数器
    // {
    //     dat <<= 1;              //移出数据的最高位
    //     SDA = CY;               //送数据口
    //     SCL = 1;                //拉高时钟线
    //     Delay5us();             //延时
    //     SCL = 0;                //拉低时钟线
    //     Delay5us();             //延时
    // }
    I2CTXD = dat;
    I2C_busy = 1;
    I2CMSCR = 0x82;
    while(I2C_busy);
    ADXL345_RecvACK();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
uint8_t ADXL345_RecvByte()
{
    // uint8_t i;
    // uint8_t dat = 0;

    // SDA = 1;                    //使能内部上拉,准备读取数据,
    // for (i=0; i<8; i++){      //8位计数器
    //     dat <<= 1;
    //     SCL = 1;                //拉高时钟线
    //     Delay5us();             //延时
    //     dat |= SDA;             //读数据               
    //     SCL = 0;                //拉低时钟线
    //     Delay5us();             //延时
    // }
    I2C_busy = 1;
    I2CMSCR = 0x84;
    while(I2C_busy);
    return I2CRXD;
}

//******单字节写入*******************************************

void Single_Write_ADXL345(uint8_t REG_Address,uint8_t REG_data){
    ADXL345_Start();                  //起始信号
    ADXL345_SendByte(SlaveAddress);   //发送设备地址+写信号
    ADXL345_SendByte(REG_Address);    //内部寄存器地址，请参考中文pdf22页 
    ADXL345_SendByte(REG_data);       //内部寄存器数据，请参考中文pdf22页 
    ADXL345_Stop();                   //发送停止信号
}

//********单字节读取*****************************************
uint8_t Single_Read_ADXL345(uint8_t REG_Address){  
    uint8_t REG_data;
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress);           //发送设备地址+写信号
    ADXL345_SendByte(REG_Address);                   //发送存储单元地址，从0开始	
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress+1);         //发送设备地址+读信号
    REG_data=ADXL345_RecvByte();              //读出寄存器数据
    ADXL345_SendACK(1);   
    ADXL345_Stop();                           //停止信号
    return REG_data; 
}
//*********************************************************
//
//连续读出ADXL345内部加速度数据，地址范围0x32~0x37
//
//*********************************************************
void Multiple_read_ADXL345(void){
    
    uint8_t i;
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress);           //发送设备地址+写信号
    ADXL345_SendByte(0x32);                   //发送存储单元地址，从0x32开始	
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress+1);         //发送设备地址+读信号
    for (i=0; i<6; i++)                      //连续读取6个地址数据，存储中BUF
    {
        BUF[i] = ADXL345_RecvByte();          //BUF[0]存储0x32地址中的数据
        if (i == 5){
            ADXL345_SendACK(1);                //最后一个数据需要回NOACK
        }
        else{
            ADXL345_SendACK(0);                //回应ACK
        }
    }
    ADXL345_Stop();                          //停止信号
    Delay5ms();
}


//*****************************************************************

//初始化ADXL345，根据需要请参考pdf进行修改************************
void Init_ADXL345(){

    Single_Write_ADXL345(0x31,0x0B);   //测量范围,正负16g，13位模式
    Single_Write_ADXL345(0x2C,0x08);   //速率设定为12.5 参考pdf13页
    Single_Write_ADXL345(0x2D,0x08);   //选择电源模式   参考pdf24页
    Single_Write_ADXL345(0x2E,0x80);   //使能 DATA_READY 中断
    Single_Write_ADXL345(0x1E,0x00);   //X 偏移量 根据测试传感器的状态写入pdf29页
    Single_Write_ADXL345(0x1F,0x00);   //Y 偏移量 根据测试传感器的状态写入pdf29页
    Single_Write_ADXL345(0x20,0x05);   //Z 偏移量 根据测试传感器的状态写入pdf29页
}

void I2C_isr() __interrupt(I2C_VECTOR) __using(I2C_VECTOR){
    if (I2CMSST & 0x40){
        I2CMSST &= ~0x40;
        I2C_busy = 0;
        P2_0 =! P2_0;
    }
}