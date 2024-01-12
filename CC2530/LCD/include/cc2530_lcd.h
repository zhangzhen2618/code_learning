//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STC89C52RC,晶振30M  单片机工作电压3.3V
//QDtech-TFT液晶驱动 for C51
//xiao冯@ShenZhen QDtech co.,LTD
//公司网站:www.qdtft.com
//淘宝网站：http://qdtech.taobao.com
//wiki技术网站：http://www.lcdwiki.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-23594567 
//手机:15989313508（冯工） 
//邮箱:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com
//技术支持QQ:3002773612  3002778157
//技术交流QQ群:324828016
//创建日期:2018/7/7
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2018-2028
//All rights reserved
//********************************************************************************
//=========================================电源接线================================================//
//5V接DC 5V电源
//GND接地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为SPI
//液晶屏模块            单片机
// SDI(MOSI)     接       P15        //SPI写信号
// SDO(MISO)     接       P16        //SPI读信号，如果不需要读功能，此管脚可不接
//=======================================液晶屏控制线接线==========================================//
//液晶屏模块            单片机
//  CS           接       P13       //片选控制信号
//  RESET        接       P33       //复位信号
//  DC           接       P12       //数据/命令选择控制信号
//  SCK          接       P17       //SPI时钟信号
//  LED          接       P32       //背光控制信号，如果使用STC89C52RC单片机或者不需要控制，接3.3V
//=========================================触摸屏接线=========================================//
//STC89C52RC单片机ROM太小，无法运行带触摸功能的程序，所以触摸屏不需要接线
//不使用触摸或者模块本身不带触摸，则可不连接
//触摸屏使用的数据总线类型为SPI
//触摸屏模块            单片机
//  T_CLK        接       P36       //触摸屏SPI时钟信号
//  T_CS         接       P37       //触摸屏片选控制信号
//  T_DIN        接       P34       //触摸屏SPI写信号
//  T_DO         接       P35       //触摸屏SPI读信号
//  T_IRQ        接       P40       //触摸屏响应检查信号，如单片机无P4组，请自行更改其他可用IO并修改代码定义
//**************************************************************************************************/	
#ifndef __CC2530_LCD_H__
#define __CC2530_LCD_H__		

#include <cc2530.h>
#include <stdint.h>
#include "cc2530io_bitdef.h"

/////////////////////////////////////用户配置区///////////////////////////////////	 
//支持横竖屏快速定义切换
#define USE_HORIZONTAL  	0 //定义液晶屏顺时针旋转方向 	0-0度旋转，1-90度旋转，2-180度旋转，3-270度旋转
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////	  
//定义LCD的尺寸
#define LCD_W 128
#define LCD_H 128



//IO连接
#define LCD_RS 	 	 P1_7  		 //数据/命令切换
#define LCD_SDI 	 P1_5		  //SPI写
// #define LCD_SDO 	 P1_2		     //SPI读
#define LCD_CS 	 	 P1_2		//片选	
#define LCD_CLK 	 P1_3   //SPI时钟
#define LCD_RESET 	 P1_4	      //复位 
#define LCD_BL		 P1_6		//背光控制，STC89C52RC单片滑接3.3V

void delay_ms(int count);
void delay_us(int count);

//LCD的画笔颜色和背景色	   
extern uint16_t  POINT_COLOR;//默认红色    
extern uint16_t  BACK_COLOR; //背景颜色.默认为白色
//LCD重要参数集
typedef struct  
{										    
	uint16_t 	 width;			//LCD 宽度
	uint16_t 	 height;			//LCD 高度
	uint16_t 	 id;				//LCD ID
	uint8_t  	 dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。	
	uint16_t	 wramcmd;		//开始写gram指令
	uint16_t  	 setxcmd;		//设置x坐标指令
	uint16_t  	 setycmd;		//设置y坐标指令	
	uint8_t   	 xoffset;    
	uint8_t	 	 yoffset;	
}_lcd_dev; 	

//LCD参数
extern _lcd_dev lcddev;	//管理LCD重要参数

void LCD_Init(void); 
void LCD_Clear(uint16_t Color);
void spi_write_byte(uint8_t d); //通过SPI写入一个字节数据
void LCD_WR_DATA(uint8_t Data); 
void LCD_WR_REG(uint8_t Reg);
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);//设置光标位置
void LCD_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd);//设置显示窗口
void LCD_DrawPoint(uint16_t x,uint16_t y);//画点
void LCD_WriteRAM_Prepare(void);
void LCD_direction(uint8_t direction );
void LCD_WR_DATA_16Bit(uint16_t Data);


//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
#define GRAY0       	 0xEF7D 
#define GRAY1       	 0x8410      	//灰色1      00000 000000 00000
#define GRAY2       	 0x4208 
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)


					  		 
#endif  
	 
	 



