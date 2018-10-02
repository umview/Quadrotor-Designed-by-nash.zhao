/*
OLED 							OK
#define OLED_DC PTA24_O
#define OLED_RST PTA25_O
#define OLED_SCL PTA26_O
#define OLED_SDIN PTA27_O
*/
#ifndef __OLED_H
#define __OLED_H

#include "stm32f4xx.h"
#include "delay.h"
//#include "common.h"
//#include "include.h"
#include "sys.h"
#include "stdlib.h"

#define  u8 unsigned char
#define  u32 unsigned int

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
#define OLED_MODE 0

// OLED_CS 	 	片选
// OLED_RST 	复位
// OLED_DC 	 	数据/命令控制
// OLED_SCL  	时钟 D0(SCLK)
// OLED_SDIN	D1(MOSI) 数据


//#define OLED_DC PTA19_OUT
//#define OLED_RST PTA24_OUT
#define OLED_DC PFout(10)
#define OLED_RST PDout(13)
#define OLED_SCL PDout(4)
#define OLED_SDIN PDout(7)
//#define OLED_CS 

#define OLED_CS_Clr()  OLED_CS=0
#define OLED_CS_Set()  OLED_CS=1

#define OLED_RST_Clr() OLED_RST=0
#define OLED_RST_Set() OLED_RST=1

#define OLED_DC_Clr() OLED_DC=0
#define OLED_DC_Set() OLED_DC=1

#define OLED_SCLK_Clr() OLED_SCL=0
#define OLED_SCLK_Set() OLED_SCL=1

#define OLED_SDIN_Clr() OLED_SDIN=0
#define OLED_SDIN_Set() OLED_SDIN=1;





//OLED模式设置
//0:4线串行模式
//1:并行8080模式

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF
#define X_WIDTH 	128
#define Y_WIDTH 	64
//-----------------OLED端口定义----------------
void OLEDInit(void);
void SPI_OLED_Init(void);

void delayms(unsigned int ms);

//OLED控制用函数
void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
extern void OLEDInit(void);
void OLED_GPIO_Init(void);
void SPI_OLED_Init(void);
extern void OLEDClear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
extern void OLEDShowChar(u8 x,u8 y,u8 chr);
extern void OLEDShowNum(u8 x,u8 y,int num,u8 len,u8 size2);
extern void OLEDShowString(u8 x,u8 y, u8 *p);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
//extern void OLEDShowDecimal(u8 x,u8 y,float de_num,u8 int_len,u8 decimal_len,u8 size3);

#endif




